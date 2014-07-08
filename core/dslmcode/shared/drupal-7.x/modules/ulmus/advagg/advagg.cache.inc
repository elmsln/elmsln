<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * Functions used for clearing caches and killing files.
 */

// Cache and file flushing.
/**
 * Uses the database to scan CSS/JS files for changes.
 *
 * @return array
 *   array of files that have changed.
 */
function advagg_scan_for_changes() {
  // Get all files stored in the database and filesystem.
  $files_that_have_changed = array();
  $result = db_select('advagg_files', 'af')
    ->fields('af')
    ->execute();
  if (!empty($result)) {
    module_load_include('inc', 'advagg', 'advagg');
    $filenames = array();

    $data = array();
    foreach ($result as $row) {
      $filenames[] = $row->filename;
      $data[$row->filename] = (array) $row;
    }

    // Get filesystem data.
    $files_info = advagg_get_info_on_files($filenames, TRUE);
    foreach ($files_info as $info) {
      if (!isset($data[$info['data']])) {
        continue;
      }
      $row = $data[$info['data']];

      // Select the keys to compare.
      $keys_to_compare = array(
        'filesize',
        'content_hash',
        'linecount',
      );
      $changed = FALSE;
      foreach ($keys_to_compare as $key) {
        if ($row[$key] != $info[$key]) {
          $changed = TRUE;
          break;
        }
      }
      // Compare mtime if it is not zero.
      if (!$changed && empty($info['split']) && !empty($info['mtime']) && $row['mtime'] != $info['mtime']) {
        $changed = TRUE;
      }

      if (!$changed) {
        // Call hook_advagg_scan_for_changes().
        $changes_array = module_invoke_all('advagg_scan_for_changes', $row['filename']);
        if (is_array($changes_array)) {
          foreach ($changes_array as $value) {
            if (!empty($value)) {
              $changed = TRUE;
              break;
            }
          }
        }
      }

      // If file has changed, add it to the array.
      if ($changed) {
        $files_that_have_changed[$row['filename']] = $info;
      }
    }
  }

  return $files_that_have_changed;
}

/**
 * Flush the correct caches so CSS/JS changes go live.
 *
 * @return array
 *   array of files that have changed and caches flushed.
 */
function advagg_push_new_changes() {
  // Scan the file system for changes to CSS/JS files.
  $files = advagg_scan_for_changes();
  $results = array();

  // If something changed, flush the correct caches so that change goes out.
  if (!empty($files)) {
    $types = array();
    module_load_include('inc', 'advagg', 'advagg');
    foreach ($files as $filename => $meta_data) {
      $ext = pathinfo($filename, PATHINFO_EXTENSION);
      // Lookup the aggregates that use this file.
      $aggregates = advagg_get_aggregates_using_file($meta_data['filename_hash']);

      // Get the cache ids.
      $cache_ids = array();
      foreach ($aggregates as $row) {
        $cache_ids[] = $row['cid'];
      }
      $cache_hits = cache_get_multiple($cache_ids, 'cache_advagg_info');
      if (!empty($cache_hits)) {
        foreach ($cache_hits as $cid => $data) {
          cache_clear_all($cid, 'cache_advagg_info', FALSE);
        }
      }
      $types[$ext] = TRUE;
      $results[$filename] = array($aggregates, $cache_hits);

      // Update database.
      advagg_insert_update_files(array($filename => $meta_data), $ext);
    }

    // Let other modules know about the changed files.
    // Call hook_advagg_changed_files().
    module_invoke_all('advagg_changed_files', $files, $types);

    // Clear out the full aggregates cache.
    foreach ($types as $ext => $bool) {
      cache_clear_all('advagg:' . $ext . ':', 'cache_advagg_aggregates', TRUE);
    }
  }
  // Return what was done.
  return $results;
}

/**
 * Given a filename hash get back all aggregates that include it.
 *
 * @param string $filename_hash
 *   hash of the filename.
 *
 * @return array
 *   array of aggregates that use this file.
 */
function advagg_get_aggregates_using_file($filename_hash) {
  // Create join query for the advagg_aggregates_versions table.
  $subquery_aggregates_versions = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav')
    ->condition('aav.atime', 0, '>');

  // Create main query for the advagg_aggregates table.
  $query = db_select('advagg_aggregates', 'aa')
    ->condition('aa.filename_hash', $filename_hash);
  $query->join($subquery_aggregates_versions, 'aav', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $query = $query->fields('aav', array('aggregate_filenames_hash', 'aggregate_contents_hash'))
    ->execute();

  // Put results into $aggregates array.
  $aggregates = array();
  foreach ($query as $row) {
    $row = (array) $row;
    $row['cid'] = 'advagg:db:' . $row['aggregate_filenames_hash'] . ADVAGG_SPACE . $row['aggregate_contents_hash'];
    $aggregates[] = $row;
  }
  return $aggregates;
}

/**
 * Scan CSS/JS advagg dir & remove that file if atime is grater than 30 days.
 *
 * @return array
 *   array of files that got removed.
 */
function advagg_delete_stale_aggregates() {
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Get a list of files.
  $css_files = file_scan_directory($css_path[0], '/.*/', array('nomask' => '/(\.\.?|CVS|\.gz)$/'));
  $js_files = file_scan_directory($js_path[0], '/.*/', array('nomask' => '/(\.\.?|CVS|\.gz)/'));

  // Make the advagg_get_hashes_from_filename() function available.
  module_load_include('inc', 'advagg', 'advagg.missing');
  $css_files = advagg_delete_files_if_stale($css_files);
  $js_files = advagg_delete_files_if_stale($js_files);
  return array($css_files, $js_files);
}

/**
 * Given an array of files remove that file if atime is grater than 30 days.
 *
 * @param array $files
 *   Array of files returned by file_scan_directory.
 *
 * @return array
 *   array of files that got removed.
 */
function advagg_delete_files_if_stale($files) {
  // Array used to record what files were deleted.
  $kill_list = array();

  foreach ($files as $uri => $file) {
    // Get info on file.
    $filename = $file->filename;
    $data = advagg_get_hashes_from_filename($filename);
    if (is_array($data)) {
      list($type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings) = $data;
    }
    else {
      // Can not get data on file, remove it.
      file_unmanaged_delete($uri);
      if (file_exists($uri . '.gz')) {
        file_unmanaged_delete($uri . '.gz');
      }
      $kill_list[] = $uri;
      continue;
    }

    // Get atime of file.
    $atime = advagg_get_atime($aggregate_filenames_hash, $aggregate_contents_hash, $uri);
    if (empty($atime)) {
      file_unmanaged_delete($uri);
      if (file_exists($uri . '.gz')) {
        file_unmanaged_delete($uri . '.gz');
      }
      $kill_list[] = $uri;
      continue;
    }

    // Default stale file threshold is 30 days.
    if (REQUEST_TIME - $atime > variable_get('drupal_stale_file_threshold', 2592000)) {
      file_unmanaged_delete($uri);
      if (file_exists($uri . '.gz')) {
        file_unmanaged_delete($uri . '.gz');
      }
      $kill_list[] = $uri;
    }
  }
  return $kill_list;
}

/**
 * Perform a cache_clear_all on all bins returned by advagg_flush_caches(TRUE).
 */
function advagg_flush_all_cache_bins() {
  $bins = advagg_flush_caches(TRUE);
  foreach ($bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
  }
}

/**
 * Remove all files from the advagg CSS/JS directories.
 *
 * @return array
 *   array of all files removed.
 */
function advagg_remove_all_aggregated_files() {
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Find all files in the advagg CSS/JS directories and delete them.
  $css_files = file_scan_directory($css_path[0], '/.*/', array('callback' => 'file_unmanaged_delete'));
  $js_files = file_scan_directory($js_path[0], '/.*/', array('callback' => 'file_unmanaged_delete'));
  return array($css_files, $js_files);
}

/**
 * Increment the advagg_global_counter variable by one.
 *
 * @todo Allow this value to be kept in sync across a multisite.
 *
 * @return int
 *   New value of advagg_global_counter.
 */
function advagg_increment_global_counter() {
  $new_value = advagg_get_global_counter() + 1;
  variable_set('advagg_global_counter', $new_value);
  return $new_value;
}

/**
 * Scan for missing files and remove the associated entries in the database.
 *
 * @return array
 *   Array of what files were cleared out of the database.
 */
function advagg_remove_missing_files_from_db() {
  $missing_files = array();
  $deleted = array();

  // Get all files stored in the database.
  $result = db_select('advagg_files', 'af')
    ->fields('af')
    ->execute();
  if (empty($result)) {
    return $deleted;
  }

  // Find missing files.
  module_load_include('inc', 'advagg', 'advagg');
  foreach ($result as $row) {
    $row = (array) $row;
    $info = advagg_get_info_on_file($row['filename'], TRUE);

    // Make sure file exists.
    if (empty($info['content_hash'])) {
      $info += advagg_get_aggregates_using_file($info['filename_hash']);
      $missing_files[$row['filename']] = $info;
      continue;
    }
  }
  if (empty($missing_files)) {
    return $deleted;
  }

  // Remove missing file database entries.
  $types = array();
  foreach ($missing_files as $filename => $data) {
    // Setup this run.
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    $advagg_files_del = 0;
    $advagg_aggregates_del = 0;
    $advagg_aggregates_versions_del = 0;
    $clean_sweep = TRUE;
    $filename_hash = '';

    // Scan the data.
    foreach ($data as $key => $values) {
      if (!is_numeric($key)) {
        $filename_hash = $values;
      }
      else {
        // Remove the entry from the database if this aggregate has not been
        // accessed in the last 2 weeks.
        $can_delete = db_delete('advagg_aggregates_versions')
          ->condition('aggregate_filenames_hash', $values['aggregate_filenames_hash'])
          ->condition('atime', REQUEST_TIME - variable_get('advagg_remove_missing_files_from_db_time', ADVAGG_REMOVE_MISSING_FILES_FROM_DB_TIME), '<')
          ->execute();
        if ($can_delete > 0) {
          $advagg_aggregates_versions_del += $can_delete;
          $advagg_aggregates_del += db_delete('advagg_aggregates')
            ->condition('aggregate_filenames_hash', $values['aggregate_filenames_hash'])
            ->execute();
        }
        else {
          $clean_sweep = FALSE;
        }
        // Clear the cache.
        cache_clear_all($values['cid'], 'cache_advagg_info', FALSE);
      }
    }

    // Remove the file entry if all aggregates referencing it have been removed.
    if ($clean_sweep) {
      $advagg_files_del += db_delete('advagg_files')
        ->condition('filename_hash', $filename_hash)
        ->execute();
    }

    // Add info to array.
    $types[$ext] = TRUE;
    $deleted[$filename] = array(
      'advagg_files' => $advagg_files_del,
      'advagg_aggregates_versions' => $advagg_aggregates_versions_del,
      'advagg_aggregates' => $advagg_aggregates_del,
    );
  }

  // If something was deleted, clear the full aggregates cache.
  if (!empty($deleted)) {
    foreach ($types as $ext => $bool) {
      cache_clear_all('advagg:' . $ext . ':', 'cache_advagg_aggregates', TRUE);
    }
  }

  // Return what was deleted.
  return $deleted;
}

/**
 * Delete aggregates that have not been accessed in the last 6 weeks.
 *
 * @return int
 *   Count of the number of rows removed from the databases.
 */
function advagg_remove_old_unused_aggregates() {
  $advagg_aggregates_versions_del = 0;
  $advagg_aggregates_del = 0;

  // Find orphaned aggregate versions entries.
  // Create join query.
  $subquery_aggregates = db_select('advagg_aggregates', 'aa')
    ->fields('aa', array('aggregate_filenames_hash'));
  // Create main query.
  $query = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav', array('aggregate_filenames_hash'))
    ->groupBy('aav.aggregate_filenames_hash');
  $query->leftjoin($subquery_aggregates, 'aa', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
  $query->isNull('aa.aggregate_filenames_hash');
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();
  // If we have an orphaned db entry, delete it.
  if (!empty($results)) {
    foreach ($results as $row) {
      $advagg_aggregates_versions_del += db_delete('advagg_aggregates_versions')
        ->condition('aggregate_filenames_hash', $row->aggregate_filenames_hash)
        ->execute();
    }
  }

  // Delete aggregate versions that have not been accessed in the last 45 days.
  $advagg_aggregates_versions_del += db_delete('advagg_aggregates_versions')
    ->condition('atime', REQUEST_TIME - variable_get('advagg_remove_old_unused_aggregates_time', ADVAGG_REMOVE_OLD_UNUSED_AGGREGATES_TIME), '<')
    ->execute();

  // See if any aggregates are orphaned now.
  // Create join query.
  $subquery_aggregates_versions = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav', array('aggregate_filenames_hash'));
  // Create main query.
  $query = db_select('advagg_aggregates', 'aa')
    ->fields('aa', array('aggregate_filenames_hash'))
    ->groupBy('aa.aggregate_filenames_hash');
  $query->leftjoin($subquery_aggregates_versions, 'aav', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
  $query->isNull('aav.aggregate_filenames_hash');
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();

  // If we have an orphaned db entry, delete it.
  if (!empty($results)) {
    foreach ($results as $row) {
      $advagg_aggregates_del += db_delete('advagg_aggregates')
        ->condition('aggregate_filenames_hash', $row->aggregate_filenames_hash)
        ->execute();
    }
  }

  // Return the total count of entires removed from the database.
  return $advagg_aggregates_versions_del + $advagg_aggregates_del;
}

/**
 * Delete orphaned/expired advagg locks from the semaphore database table.
 *
 * @return int
 *   Count of the number of rows removed from the databases.
 */
function advagg_cleanup_semaphore_table() {
  // Let expiration times vary by 5 minutes.
  $fuzz_factor = 300;
  $results = db_delete('semaphore')
    ->condition('name', db_like('advagg_') . '%', 'LIKE')
    ->condition('expire', REQUEST_TIME - $fuzz_factor, '<')
    ->execute();
  return $results;
}
