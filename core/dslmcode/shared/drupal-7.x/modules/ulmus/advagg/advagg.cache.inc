<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * Functions used for clearing caches and killing files.
 */

/**
 * Uses the database to scan CSS/JS files for changes.
 *
 * @return array
 *   Array of files that have changed.
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
      $changed = array();
      foreach ($keys_to_compare as $key) {
        if ($row[$key] != $info[$key]) {
          $changed[] = $key . ' db:' . $row[$key] . ' file:' . $info[$key];
          break;
        }
      }
      // Compare mtime if it is not zero.
      if (empty($info['split']) && !empty($info['mtime'])) {
        if (variable_get('advagg_strict_mtime_check', ADVAGG_STRICT_MTIME_CHECK) && $row['mtime'] != $info['mtime']) {
          $changed[] = 'mtime db:' . $row['mtime'] . ' file:' . $info['mtime'];
        }
        elseif ($row['mtime'] < $info['mtime']) {
          $changed[] = 'mtime db:' . $row['mtime'] . ' file:' . $info['mtime'];
        }
      }

      if (empty($changed)) {
        // Call hook_advagg_scan_for_changes().
        $changes_array = module_invoke_all('advagg_scan_for_changes', $row['filename']);
        if (is_array($changes_array)) {
          foreach ($changes_array as $value) {
            if (!empty($value)) {
              $changed[] = $value;
              break;
            }
          }
        }
      }

      // If file has changed, add it to the array.
      if (!empty($changed)) {
        $info['changes'] = $changed;
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
 *   Array of files that have changed and caches flushed.
 */
function advagg_push_new_changes(array $files = array()) {
  $results = array();
  // Scan the file system for changes to CSS/JS files.
  if (empty($files)) {
    $files = advagg_scan_for_changes();
    if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
      watchdog('advagg-debug', 'Changes detected in <pre>@files</pre>.', array('@files' => print_r($files, TRUE)), WATCHDOG_DEBUG);
    }
  }

  // Clear some static caches.
  drupal_static_reset('advagg_get_info_on_file');
  drupal_static_reset('advagg_drupal_hash_base64');
  drupal_static_reset('advagg_current_hooks_hash_array');
  drupal_static_reset('advagg_get_current_hooks_hash');

  if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
    // Exception used to get a compact stack trace.
    $e = new Exception();
    watchdog('advagg-debug', 'New changes called by: <pre>@changes</pre>', array('@changes' => print_r($e->getTraceAsString(), TRUE)), WATCHDOG_DEBUG);
  }

  // If something changed, flush the correct caches so that change goes out.
  if (!empty($files)) {
    $types = array();
    module_load_include('inc', 'advagg', 'advagg');
    foreach ($files as $filename => $meta_data) {
      // Lookup the aggregates/cache ids that use this file.
      $cache_ids = advagg_get_aggregates_using_file($meta_data['filename_hash'], TRUE);
      $cache_hits = array();
      $ext = strtolower(pathinfo($filename, PATHINFO_EXTENSION));
      $types[$ext] = TRUE;

      if (!empty($cache_ids)) {
        $cache_hits = cache_get_multiple($cache_ids, 'cache_advagg_info');
        foreach ($cache_hits as $cid => $data) {
          if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
            watchdog('advagg-debug', 'Clearing cache @cid.', array('@cid' => $cid), WATCHDOG_DEBUG);
          }
          cache_clear_all($cid, 'cache_advagg_info', FALSE);
        }
      }

      $changes = array();
      if (!empty($meta_data['changes'])) {
        $changes = $meta_data['changes'];
        unset($meta_data['changes']);
      }

      $results[$filename] = array(
        count($cache_ids),
        count($cache_hits),
        $changes,
      );

      // Update database.
      advagg_insert_update_files(array($filename => $meta_data), $ext);
    }

    // Change query-strings on css/js files to enforce reload for all users.
    // Change css_js_query_string variable.
    _drupal_flush_css_js();

    // Let other modules know about the changed files.
    // Call hook_advagg_changed_files().
    module_invoke_all('advagg_changed_files', $files, $types);

    // Clear out the full aggregates cache.
    foreach ($types as $ext => $bool) {
      if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
        watchdog('advagg-debug', 'Clearing cache advagg:@ext: in cache_advagg_aggregates.', array('@ext' => print_r($ext, TRUE)), WATCHDOG_DEBUG);
      }
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
 *   Hash of the filename.
 * @param bool $cid_only
 *   Set to TRUE to only have cache ids returned.
 *
 * @return array
 *   Array of aggregates that use this file.
 */
function advagg_get_aggregates_using_file($filename_hash, $cid_only = FALSE) {
  // Create main query for the advagg_aggregates table.
  $query = db_select('advagg_aggregates', 'aa')
    ->condition('aa.filename_hash', $filename_hash);
  // Create join query for the advagg_aggregates_versions table.
  $query->join('advagg_aggregates_versions', 'aav', 'aa.aggregate_filenames_hash = aav.aggregate_filenames_hash AND aav.atime > 0');
  $query = $query->fields('aav', array('aggregate_filenames_hash', 'aggregate_contents_hash'));
  $query->comment('Query called from ' . __FUNCTION__ . '()');
  $results = $query->execute();

  // Put results into $aggregates array.
  $aggregates = array();
  foreach ($results as $row) {
    $row = (array) $row;
    $cid = 'advagg:db:' . $row['aggregate_filenames_hash'] . ADVAGG_SPACE . $row['aggregate_contents_hash'];
    if ($cid_only) {
      $aggregates[] = $cid;
    }
    else {
      $row['cid'] = $cid;
      $aggregates[] = $row;
    }
  }
  return $aggregates;
}

/**
 * Get all CSS/JS advagg files.
 *
 * @param array $options
 *   Array of options to pass along to file_scan_directory().
 *
 * @return array
 *   Array of css and js files.
 */
function advagg_get_all_files(array $options = array()) {
  list($css_path, $js_path) = advagg_get_root_files_dir();
  $options += array('nomask' => '/(\.\.?|CVS|\.gz|\.br)$/');

  // Get a list of files.
  $css_files = file_scan_directory($css_path[0], '/.*/', $options);
  $js_files = file_scan_directory($js_path[0], '/.*/', $options);
  return array($css_files, $js_files);
}

/**
 * Scan CSS/JS advagg dir and remove that file if atime is grater than 30 days.
 *
 * @return array
 *   Array of files that got removed.
 */
function advagg_delete_stale_aggregates() {
  list($css_files, $js_files) = advagg_get_all_files();

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
 *   Array of files that got removed.
 */
function advagg_delete_files_if_stale(array $files) {
  // Array used to record what files were deleted.
  $kill_list = array();

  foreach ($files as $uri => $file) {
    // Get info on file.
    $filename = $file->filename;
    $data = advagg_get_hashes_from_filename($filename);
    if (is_array($data)) {
      list(, $aggregate_filenames_hash, $aggregate_contents_hash) = $data;
    }
    else {
      // Can not get data on file, remove it.
      $kill_list[] = advagg_delete_file_by_uri($uri);
      continue;
    }

    // Get atime of file.
    $atime = advagg_get_atime($aggregate_filenames_hash, $aggregate_contents_hash, $uri);
    if (empty($atime)) {
      $kill_list[] = advagg_delete_file_by_uri($uri);
      continue;
    }

    // Default stale file threshold is 30 days.
    if (REQUEST_TIME - $atime > variable_get('drupal_stale_file_threshold', 2592000)) {
      $kill_list[] = advagg_delete_file_by_uri($uri);
      continue;
    }

  }
  // Let other modules know about the removed files.
  // Call hook_advagg_removed_aggregates().
  module_invoke_all('advagg_removed_aggregates', $kill_list);
  return $kill_list;
}

/**
 * Scan CSS/JS advagg dir and remove that file if it is empty.
 *
 * @return array
 *   Array of files that got removed.
 */
function advagg_delete_empty_aggregates() {
  list($css_files, $js_files) = advagg_get_all_files();
  $css_files = advagg_delete_files_if_empty($css_files);
  $js_files = advagg_delete_files_if_empty($js_files);
  return array($css_files, $js_files);
}

/**
 * Given an array of files remove that file if it is empty.
 *
 * @param array $files
 *   Array of files returned by file_scan_directory.
 *
 * @return array
 *   Array of files that got removed.
 */
function advagg_delete_files_if_empty(array $files) {
  // Array used to record what files were deleted.
  $kill_list = array();

  foreach ($files as $uri => $file) {
    // Ignore temp files.  There's a separate process for cleaning those up.
    if (strpos($uri, '/advagg_file_') !== FALSE) {
      continue;
    }
    $size = filesize($uri);
    if ($size === 0) {
      $kill_list[] = advagg_delete_file_by_uri($uri);
      continue;
    }
  }
  // Let other modules know about the removed files.
  // Call hook_advagg_removed_aggregates().
  module_invoke_all('advagg_removed_aggregates', $kill_list);
  return $kill_list;
}

/**
 * Delete a file, and any compressed versions.
 *
 * @param string $uri
 *   URI of the file to delete.
 *
 * @return string
 *   The given URI.
 */
function advagg_delete_file_by_uri($uri) {
  if (file_exists($uri)) {
    file_unmanaged_delete($uri);
  }
  if (file_exists($uri . '.gz')) {
    file_unmanaged_delete($uri . '.gz');
  }
  if (file_exists($uri . '.br')) {
    file_unmanaged_delete($uri . '.br');
  }
  return $uri;
}

/**
 * Perform a cache_clear_all on all bins returned by advagg_flush_caches(TRUE).
 *
 * @param bool $push_new_changes
 *   FALSE: Do not scan for changes.
 */
function advagg_flush_all_cache_bins($push_new_changes = TRUE) {
  $bins = advagg_flush_caches(TRUE, $push_new_changes);
  foreach ($bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
  }
}

/**
 * Remove all files from the advagg CSS/JS directories.
 *
 * @param bool $kill_htaccess
 *   Set to TRUE to remove the htaccess files as well.
 *
 * @return array
 *   Array of all files removed.
 */
function advagg_remove_all_aggregated_files($kill_htaccess = FALSE) {
  $options = array(
    'callback' => 'file_unmanaged_delete',
    'nomask' => '/(\.\.?|CVS)$/',
  );
  list($css_files, $js_files) = advagg_get_all_files($options);
  // Let other modules know about the removed files.
  // Call hook_advagg_removed_aggregates().
  module_invoke_all('advagg_removed_aggregates', $css_files);
  module_invoke_all('advagg_removed_aggregates', $js_files);

  // Remove the htaccess files as well.
  if ($kill_htaccess) {
    list($css_path, $js_path) = advagg_get_root_files_dir();
    if (file_exists($css_path[0] . '/.htaccess')) {
      file_unmanaged_delete($css_path[0] . '/.htaccess');
      $css_files[] = $css_path[0] . '/.htaccess';
    }
    if (file_exists($js_path[0] . '/.htaccess')) {
      file_unmanaged_delete($js_path[0] . '/.htaccess');
      $js_files[] = $js_path[0] . '/.htaccess';
    }
  }
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
    $ext = strtolower(pathinfo($filename, PATHINFO_EXTENSION));
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

      // Add info to array.
      if (!empty($advagg_files_del)
        || !empty($advagg_aggregates_versions_del)
        || !empty($advagg_aggregates_del)
      ) {
        $types[$ext] = TRUE;
        $deleted[$filename] = array(
          'advagg_files' => $advagg_files_del,
          'advagg_aggregates_versions' => $advagg_aggregates_versions_del,
          'advagg_aggregates' => $advagg_aggregates_del,
        );
      }
    }
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
 * Scan CSS/JS advagg dir and remove file if there is no associated db record.
 *
 * @return array
 *   Array of files that got removed.
 */
function advagg_delete_orphaned_aggregates() {
  list($css_files, $js_files) = advagg_get_all_files();

  // Make the advagg_get_hashes_from_filename() function available.
  module_load_include('inc', 'advagg', 'advagg.missing');
  $css_files = advagg_delete_files_if_orphaned($css_files);
  $js_files = advagg_delete_files_if_orphaned($js_files);
  return array($css_files, $js_files);
}

/**
 * Given an array of files remove that file if there is no associated db record.
 *
 * @param array $files
 *   Array of files returned by file_scan_directory.
 *
 * @return array
 *   Array of files that got removed.
 */
function advagg_delete_files_if_orphaned(array $files) {
  // Get the uri for the advagg_css/parts directory.
  list($css_path) = advagg_get_root_files_dir();
  $parts_uri = $css_path[0] . '/parts/';

  // Array used to record what files were deleted.
  $kill_list = $keyed_file_list = array();

  // Create a listing of all file names and associated hashes.
  foreach ($files as $uri => $file) {
    // Get info on file.
    $data = advagg_get_hashes_from_filename($file->filename, TRUE);
    if (is_array($data)) {
      list(, $aggregate_filenames_hash) = $data;
      // Check to see if the file is in the database.
      $keyed_file_list[$aggregate_filenames_hash] = $uri;
    }
    else {
      // Check to see if this is a parts css file.
      $start = strpos($file->uri, $parts_uri);
      if ($start !== FALSE) {
        // Get the original filename.
        $original_file = substr($file->uri, $start + strlen($parts_uri));
        $original_file = preg_replace('/(.\\d+\\.css)$/i', '.css', $original_file);
        if (file_exists($original_file)) {
          // Original file exists, do not delete.
          continue;
        }
      }

      // Can not get data on file, remove it.
      $kill_list[] = $uri;
      continue;
    }
  }

  if (!empty($keyed_file_list)) {
    $filenames_hash = array_keys($keyed_file_list);
    $aggregates_in_database = array();
    // Process in chunks when a large array is passed.
    do {
      // Check if the aggregate_filenames_hash exists in the database.
      $aggregates_in_database += db_select('advagg_aggregates_versions', 'av')
        ->fields('av', array('aggregate_filenames_hash'))
        ->condition('av.aggregate_filenames_hash', array_splice($filenames_hash, 0, 1000), 'IN')
        ->distinct()
        ->execute()
        ->fetchAllAssoc('aggregate_filenames_hash');
    } while (count($filenames_hash));

    // Get values not found in the database.
    $to_delete = array_values(array_diff_key($keyed_file_list, $aggregates_in_database));
    // Add the file uri to the kill list.
    $kill_list = array_merge($kill_list, $to_delete);
  }

  if (!empty($kill_list)) {
    foreach ($kill_list as $uri) {
      advagg_delete_file_by_uri($uri);
    }
  }

  // Let other modules know about the removed files.
  // Call hook_advagg_removed_aggregates().
  module_invoke_all('advagg_removed_aggregates', $kill_list);
  return $kill_list;
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
  // Create main query.
  $query = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav', array('aggregate_filenames_hash'))
    ->groupBy('aav.aggregate_filenames_hash');
  // Create join and add in query comment.
  $query->leftjoin('advagg_aggregates', 'aa', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
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
  // Create main query.
  $query = db_select('advagg_aggregates', 'aa')
    ->fields('aa', array('aggregate_filenames_hash'))
    ->groupBy('aa.aggregate_filenames_hash');
  // Create join and add in query comment.
  $query->leftjoin('advagg_aggregates_versions', 'aav', 'aa.aggregate_filenames_hash=aav.aggregate_filenames_hash');
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

/**
 * Delete leftover temp files.
 *
 * @return int
 *   Count of the number of files removed
 */
function advagg_remove_temp_files() {
  // Make sure advagg_get_root_files_dir() is available.
  drupal_load('module', 'advagg');
  // Make sure advagg_install_delete_empty_file_if_stale() is available.
  module_load_include('install', 'advagg', 'advagg');

  // Get the advagg paths.
  $advagg_path = advagg_get_root_files_dir();
  $total_count = 0;
  // Get the top level path.
  $top_level = substr($advagg_path[0][0], 0, strpos($advagg_path[0][0], 'advagg_css'));

  // Remove empty temp files from public://.
  $files = file_scan_directory($top_level, '/file.*|fil.*\.tmp/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_install_delete_empty_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_css.
  $files = file_scan_directory($advagg_path[0][0], '/file.*|fil.*\.tmp/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_install_delete_empty_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_js.
  $files = file_scan_directory($advagg_path[1][0], '/file.*|fil.*\.tmp/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_install_delete_empty_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://.
  $files = file_scan_directory($top_level, '/file_advagg_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_css.
  $files = file_scan_directory($advagg_path[0][0], '/file_advagg_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_js.
  $files = file_scan_directory($advagg_path[1][0], '/file_advagg_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://.
  $files = file_scan_directory($top_level, '/advagg_file_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_css.
  $files = file_scan_directory($advagg_path[0][0], '/advagg_file_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Remove empty temp files from public://advagg_js.
  $files = file_scan_directory($advagg_path[1][0], '/advagg_file_.*/', array(
    'recurse' => FALSE,
    'callback' => 'advagg_delete_temp_file_if_stale',
  ));
  foreach ($files as $key => $file) {
    if (file_exists($file->uri)) {
      unset($files[$key]);
    }
  }
  $total_count += count($files);

  // Output info.
  return $total_count;
}

/**
 * Refresh all locale files.
 *
 * @return int
 *   Count of the number of files removed
 */
function advagg_refresh_all_locale_files() {
  $locale_files = array();
  if (!module_exists('locale')) {
    return $locale_files;
  }

  $results = db_select('advagg_files', 'af')
    ->fields('af')
    ->condition('af.filetype', 'js')
    ->condition('af.filesize', 0, '>')
    ->execute();
  $javascript = array();
  foreach ($results as $row) {
    $javascript[] = array(
      'type' => 'file',
      'data' => $row->filename,
    );
  }

  if (!empty($javascript)) {
    $javascript_before = $javascript;
    $language_before = $GLOBALS['language'];
    $language_list = language_list();
    foreach ($language_list as $lang) {
      if ($lang->enabled) {
        $GLOBALS['language'] = $lang;
        $javascript = $javascript_before;
        locale_js_alter($javascript);
        $locale_file = array_diff_key($javascript, $javascript_before);
        $locale_files += $locale_file;
      }
    }
    $GLOBALS['language'] = $language_before;
  }
  return $locale_files;
}

/**
 * Callback to delete files if modified more than 60 seconds ago.
 *
 * @param string $uri
 *   Location of the file to check.
 */
function advagg_delete_temp_file_if_stale($uri) {
  // Set stale file threshold to 60 seconds.
  if (REQUEST_TIME - filemtime($uri) > 60) {
    file_unmanaged_delete($uri);
  }
}

/**
 * See if any of the subfiles has changed.
 *
 * @param string $filename
 *   Name of the file that is related to the subfiles.
 * @param array $subfiles
 *   An array of files to check for changes.
 * @param string $keyname
 *   Under what key to save the info on the files.
 * @param bool $save_changes
 *   If TRUE then the changes will be updated in the cache.
 *
 * @return bool
 *   TRUE if one of the subfiles has changed.
 */
function advagg_detect_subfile_changes($filename, array $subfiles, $keyname, $save_changes = FALSE) {
  // Get the info on this file from the cache.
  module_load_include('inc', 'advagg', 'advagg');
  $info = advagg_get_info_on_file($filename);
  $hash_id = 'advagg:subfiles:' . $keyname . ':' . $info['filename_hash'];
  if (!isset($info[$keyname])) {
    // Pull up the info from the database if missing from the cache.
    $info[$keyname] = advagg_get_hash_settings($hash_id);
  }

  $subfile_changed = array();
  // Check every subfile seeing if they have changed.
  foreach ($subfiles as $subfile) {
    $current_file_info = $defaults = array(
      'hash' => '',
      'size' => 0,
      'mtime' => 0,
    );

    // Get the currently saved info on this file.
    $saved_file_info = isset($info[$keyname][$subfile]) ? $info[$keyname][$subfile] : array();
    $saved_file_info += $defaults;

    // Get the current info on the file.
    if (file_exists($subfile)) {
      $current_file_info = array(
        'hash' => drupal_hash_base64((string) @advagg_file_get_contents($subfile)),
        'size' => filesize($subfile),
        'mtime' => filemtime($subfile),
      );
    }

    // Set the info in case a save happens.
    $info[$keyname][$subfile] = $current_file_info;

    // Check for any differences.
    $diff = array_diff_assoc($saved_file_info, $current_file_info);
    if (!empty($diff)) {
      $subfile_changed[$subfile] = $diff;
    }
  }
  if (!empty($subfile_changed) && $save_changes) {
    $cache_id = 'advagg:file:' . $info['filename_hash'];

    // Set static cache.
    $filename_hashes = &drupal_static('advagg_get_info_on_file');
    $filename_hashes[$cache_id] = $info;

    // Set drupal cache.
    cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);

    // Save to database.
    advagg_set_hash_settings($hash_id, $info[$keyname]);
  }
  return $subfile_changed;
}
