<?php

/**
 * @file
 * Advanced CSS/JS aggregation module
 *
 * These functions are needed for cache misses.
 */

// Database operations.
// @ignore sniffer_commenting_functioncomment_shortsingleline:2
/**
 * Insert/Update data in advagg_files, advagg_aggregates, &
 * advagg_aggregates_versions tables.
 *
 * @param array $files
 *   List of files in the aggregate as well as the aggregate name.
 * @param string $type
 *   css or js.
 * @param int $root
 *   Is this a root aggregate.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_update_db($files, $type, $root) {
  // Record if a database write was done.
  $write_done = FALSE;

  // Loop through all files.
  foreach ($files as $aggregate_file_name => $values) {
    // Build lock name variable.
    $lock_name = 'advagg_insert_update_db:' . $values['aggregate_filenames_hash'] . ADVAGG_SPACE . $values['aggregate_contents_hash'];

    // If lock is already acquired, return here.
    if (!lock_acquire($lock_name, 5)) {
      continue;
    }

    // Insert files into the advagg_files table if it doesn't exist.
    // Update if needed.
    if (advagg_insert_update_files($values['files'], $type)) {
      $write_done = TRUE;
    }

    // Insert aggregate into the advagg_aggregates table if it doesn't exist.
    if (advagg_insert_aggregate($values['files'], $values['aggregate_filenames_hash'])) {
      $write_done = TRUE;
    }

    // Insert aggregate version information into advagg_aggregates_versions.
    if (advagg_insert_aggregate_version($values['aggregate_filenames_hash'], $values['aggregate_contents_hash'], $root)) {
      $write_done = TRUE;
    }

    // Release Lock.
    lock_release($lock_name);
  }
  return $write_done;
}

/**
 * Insert data in the advagg_aggregates_versions table.
 *
 * @param string $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param string $aggregate_contents_hash
 *   Hash of the files contents.
 * @param int $root
 *   Is this a root aggregate.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_aggregate_version($aggregate_filenames_hash, $aggregate_contents_hash, $root) {
  // Build query checking if this aggregate exists in the
  // advagg_aggregates_versions table.
  $aggregate_exists = db_select('advagg_aggregates_versions', 'aav')
    ->fields('aav')
    ->condition('aggregate_filenames_hash', $aggregate_filenames_hash)
    ->condition('aggregate_contents_hash', $aggregate_contents_hash)
    ->execute()
    ->fetchAssoc();
  // If this aggregate version already exists, return FALSE here.
  if (!empty($aggregate_exists)) {
    return FALSE;
  }

  // Save new aggregate into the database.
  $record = array(
    'aggregate_filenames_hash' => $aggregate_filenames_hash,
    'aggregate_contents_hash' => $aggregate_contents_hash,
    'atime' => 0,
    'root' => $root,
  );
  return drupal_write_record('advagg_aggregates_versions', $record);
}

/**
 * Insert/Update data in the advagg_aggregates table.
 *
 * @param array $files
 *   List of files in the aggregate including files meta data.
 * @param string $aggregate_filenames_hash
 *   Hash of the groupings of files.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_aggregate($files, $aggregate_filenames_hash) {
  // Record if a database write was done.
  $write_done = FALSE;

  $count = 0;
  foreach ($files as $file_meta_data) {
    ++$count;
    // Check if the aggregate is in the database.
    $file_exists = db_select('advagg_aggregates', 'aa')
      ->fields('aa')
      ->condition('aggregate_filenames_hash', $aggregate_filenames_hash)
      ->condition('filename_hash', $file_meta_data['filename_hash'])
      ->execute()
      ->fetchAssoc();
    // Skip if it already exists.
    if (!empty($file_exists)) {
      continue;
    }

    // Store settings for this file that depend on how it was added.
    $settings = array();
    if (isset($file_meta_data['media_query'])) {
      $settings['media'] = $file_meta_data['media_query'];
    }

    // Write record into the database.
    $record = array(
      'aggregate_filenames_hash' => $aggregate_filenames_hash,
      'filename_hash' => $file_meta_data['filename_hash'],
      'porder' => $count,
      'settings' => $settings,
    );
    if (drupal_write_record('advagg_aggregates', $record)) {
      $write_done = TRUE;
    }
  }
  return $write_done;
}

/**
 * Insert/Update data in the advagg_files table.
 *
 * @param array $files
 *   List of files in the aggregate including files meta data.
 * @param string $type
 *   css or js.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_update_files($files, $type) {
  // Record if a database write was done.
  $write_done = FALSE;

  foreach ($files as $filename => $file_meta_data) {
    // Create record.
    $record = array(
      'filename' => $filename,
      'filename_hash' => $file_meta_data['filename_hash'],
      'content_hash' => $file_meta_data['content_hash'],
      'filetype' => $type,
      'filesize' => $file_meta_data['filesize'],
      'mtime' => $file_meta_data['mtime'],
      'linecount' => $file_meta_data['linecount'],
    );

    // Check the file in the database.
    $file_exists = db_select('advagg_files', 'af')
      ->fields('af')
      ->condition('filename_hash', $file_meta_data['filename_hash'])
      ->execute()
      ->fetchAssoc();
    if (empty($file_exists)) {
      // Insert into database.
      $record['changes'] = 1;
      if (drupal_write_record('advagg_files', $record)) {
        $write_done = TRUE;
      }
    }
    else {
      // Take changes counter out of the diff equation.
      $changes = $file_exists['changes'];
      unset($file_exists['changes']);

      // If something is different, update.
      $diff = array_diff_assoc($record, $file_exists);
      if (!empty($diff)) {
        $diff['changes'] = $changes + 1;
        $diff['filename_hash'] = $record['filename_hash'];
        if (drupal_write_record('advagg_files', $diff, array('filename_hash'))) {
          $write_done = TRUE;
        }
      }
    }
  }
  return $write_done;
}

/**
 * Update atime advagg_aggregates_versions table & cache_advagg_info cache bin.
 *
 * @param array $files
 *   List of files in the aggregate as well as the aggregate name.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_update_all_atimes($files) {
  // Record if a database write was done.
  $write_done = FALSE;

  // Loop through all files.
  foreach ($files as $aggregate_file_name => $values) {
    // Build lock name variable.
    if (advagg_update_atime($values['aggregate_filenames_hash'], $values['aggregate_contents_hash'])) {
      $write_done = TRUE;
    }
  }

  return $write_done;
}

// File operations.
/**
 * Given a group of files calculate what the aggregate filename will be.
 *
 * @param array $groups
 *   An array of CSS/JS groups.
 * @param string $type
 *   String; css or js.
 *
 * @return array
 *   Files array.
 */
function advagg_generate_filenames($groups, $type) {
  $files = array();
  foreach ($groups as $key => $data) {
    foreach ($data as $files_with_meta_data) {

      // Get the aggregate filename & info about each file.
      $aggregate_info = advagg_get_aggregate_info_from_files($type, $files_with_meta_data);
      $values['files'] = $aggregate_info[1];
      $values['aggregate_filenames_hash'] = $aggregate_info[2];
      $values['aggregate_contents_hash'] = $aggregate_info[3];

      // Add information to the files array.
      $files[$aggregate_info[0]] = $values;
    }
  }
  return $files;
}

/**
 * Given a group of files calculate various hashes and gather meta data.
 *
 * @param string $type
 *   String; css or js.
 * @param array $files_with_meta_data
 *   An array of CSS/JS files.
 *
 * @return array
 *   array containing $aggregate_filename, $filenames,
 *   $aggregate_filenames_hash, $aggregate_contents_hash
 */
function advagg_get_aggregate_info_from_files($type, $files_with_meta_data) {
  $filename_hashes = array();
  $content_hashes = array();
  $filenames = array();
  foreach ($files_with_meta_data as $info) {
    $filename = $info['data'];
    $info += advagg_get_info_on_file($filename);
    // Skip if file doesn't exist.
    if (empty($info['content_hash'])) {
      continue;
    }

    // Add info to arrays.
    $filename_hashes[] = $info['filename_hash'];
    $content_hashes[] = $info['content_hash'];
    $filenames[$filename] = $info;
  }

  // Generate filename.
  $aggregate_filenames_hash = drupal_hash_base64(implode('', $filename_hashes));
  $aggregate_contents_hash = drupal_hash_base64(implode('', $content_hashes));
  $aggregate_filename = advagg_build_filename($type, $aggregate_filenames_hash, $aggregate_contents_hash);
  return array(
    $aggregate_filename,
    $filenames,
    $aggregate_filenames_hash,
    $aggregate_contents_hash,
  );
}

/**
 * Given a filename calculate various hashes and gather meta data.
 *
 * @param string $filename
 *   String; filename containing path information
 * @param bool $bypass_cache
 *   Bool: TRUE to bypass the cache; this will not do a cache_set as well.
 *
 * @return array
 *   $filename_hashes[$cache_id] which contains
 * @code
 *   'filesize' => filesize($filename),
 *   'mtime' => @filemtime($filename),
 *   'filename_hash' => $filename_hash,
 *   'content_hash' => drupal_hash_base64($file_contents),
 *   'linecount' => $linecount,
 *   'data' => $filename,
 *   'fileext' => $ext,
 * @endcode
 */
function advagg_get_info_on_file($filename, $bypass_cache = FALSE) {
  $filename_hash = drupal_hash_base64($filename);
  $filename_hashes = &drupal_static('advagg_get_info_on_file');

  // Use caching to avoid hitting disk if possible.
  $cache_id = 'advagg:file:' . $filename_hash;
  if (!$bypass_cache) {
    // Try static cache first.
    // @ignore sniffer_whitespace_openbracketspacing_openingwhitespace
    if (   !empty($filename_hashes)
        && array_key_exists($cache_id, $filename_hashes)
        && !empty($filename_hashes[$cache_id])
        ) {
      return $filename_hashes[$cache_id];
    }

    // Try cache back-end next.
    $cache = cache_get($cache_id, 'cache_advagg_info');
    if (!empty($cache->data)) {
      return $cache->data;
    }
  }
  else {
    // Sill load cached data for advagg contrib.
    $cache = cache_get($cache_id, 'cache_advagg_info');
    if (!empty($cache->data)) {
      $filename_hashes[$cache_id] = $cache->data;
    }
  }
  // @ignore sniffer_controlstructures_controlsignature
  if (empty($filename_hashes[$cache_id]) || !is_array($filename_hashes[$cache_id]))  {
    $filename_hashes[$cache_id] = array();
  }

  // Clear PHP's internal file status cache.
  advagg_clearstatcache($filename);

  // Remove file in the cache if it does not exist.
  if (!file_exists($filename)) {
    cache_clear_all($cache_id, 'cache_advagg_info', FALSE);
    // Return filename_hash & data. Empty values for the other keys.
    return array(
      'filesize' => 0,
      'mtime' => 0,
      'filename_hash' => $filename_hash,
      'content_hash' => '',
      'linecount' => 0,
      'data' => $filename,
    );
  }

  // Get the file contents.
  $file_contents = file_get_contents($filename);

  $ext = pathinfo($filename, PATHINFO_EXTENSION);
  if ($ext == 'css') {
    // Get the number of selectors.
    // @ignore sniffer_files_linelength_toolong
    // http://stackoverflow.com/questions/12567000/regex-matching-for-counting-css-selectors/12567381#12567381
    $linecount = preg_match_all('/\{.+?\}|,/s', $file_contents, $matched);
  }
  else {
    // Get the number of lines.
    $linecount = substr_count($file_contents, "\n");
  }

  // Build meta data array and set cache.
  $filename_hashes[$cache_id] = array_merge($filename_hashes[$cache_id], array(
    'filesize' => filesize($filename),
    'mtime' => @filemtime($filename),
    'filename_hash' => $filename_hash,
    'content_hash' => drupal_hash_base64($file_contents),
    'linecount' => $linecount,
    'data' => $filename,
    'fileext' => $ext,
  ));
  if (!$bypass_cache) {
    cache_set($cache_id, $filename_hashes[$cache_id], 'cache_advagg_info', CACHE_PERMANENT);
  }
  return $filename_hashes[$cache_id];
}

/**
 * Build the filename.
 *
 * @param string $type
 *   css or js.
 * @param string $aggregate_filenames_hash
 *   Hash of the groupings of files.
 * @param string $aggregate_contents_hash
 *   Hash of the files contents.
 * @param string $hooks_hash
 *   Hash value from advagg_get_current_hooks_hash().
 *
 * @return string
 *   String: The filename. No path info.
 */
function advagg_build_filename($type, $aggregate_filenames_hash, $aggregate_contents_hash, $hooks_hash = NULL) {
  if (is_null($hooks_hash)) {
    $hooks_hash = advagg_get_current_hooks_hash();
  }
  return $type . ADVAGG_SPACE .
    $aggregate_filenames_hash . ADVAGG_SPACE .
    $aggregate_contents_hash . ADVAGG_SPACE .
    $hooks_hash . '.' . $type;
}

/**
 * Wrapper around clearstatcache so it can use php 5.3's new features.
 *
 * @param string $filename
 *   String.
 *
 * @return null
 *   value from clearstatcache().
 */
function advagg_clearstatcache($filename = NULL) {
  static $php530;
  if (!isset($php530)) {
    $php530 = version_compare(PHP_VERSION, '5.3.0', '>=');
  }

  if ($php530) {
    return clearstatcache(TRUE, $filename);
  }
  else {
    return clearstatcache();
  }
}

// Modify CSS/JS arrays.
/**
 * Group the CSS/JS into the biggest buckets possible.
 *
 * @param array $files_to_aggregate
 *   An array of CSS/JS groups.
 *
 * @return array
 *   New version of groups.
 */
function advagg_generate_groups($files_to_aggregate) {
  $groups = array();
  $count = 0;
  $location = 0;

  $media = '';
  $defer = '';
  $async = '';
  $cache = '';
  $scope = '';
  $browsers = array();
  $selector_count = 0;
  // Get CSS limit value.
  $limit_value = variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE);
  foreach ($files_to_aggregate as $data) {
    foreach ($data as $values) {

      // Group into the biggest buckets possible.
      $onload = array();
      foreach ($values['items'] as $file_info) {
        $parts = array();
        // Check to see if media, browsers, defer, async, cache, or scope has
        // changed from the previous run of this loop.
        $changed = FALSE;
        if (isset($file_info['media'])) {
          if (variable_get('advagg_combine_css_media', ADVAGG_COMBINE_CSS_MEDIA)) {
            $file_info['media_query'] = $file_info['media'];
          }
          elseif ($media != $file_info['media']) {
            $changed = TRUE;
            $media = $file_info['media'];
          }
        }
        if (isset($file_info['browsers'])) {
          $diff = array_merge(array_diff_assoc($file_info['browsers'], $browsers), array_diff_assoc($browsers, $file_info['browsers']));
          if (!empty($diff)) {
            $changed = TRUE;
            $browsers = $file_info['browsers'];
          }
        }
        if (isset($file_info['defer']) && $defer != $file_info['defer']) {
          $changed = TRUE;
          $defer = $file_info['defer'];
        }
        if (isset($file_info['async']) && $async != $file_info['async']) {
          $changed = TRUE;
          $async = $file_info['async'];
        }
        if (isset($file_info['cache']) && $cache != $file_info['cache']) {
          $changed = TRUE;
          $cache = $file_info['cache'];
        }
        if (isset($file_info['scope']) && $scope != $file_info['scope']) {
          $changed = TRUE;
          $scope = $file_info['scope'];
        }
        if (isset($file_info['onload'])) {
          $onload[] = trim(rtrim($file_info['onload'], ';'));
        }
        if (variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER)) {
          $file_info += advagg_get_info_on_file($file_info['data']);
          // Prevent CSS rules exceeding 4095 due to limits with IE9 and below.
          $ext = isset($file_info['fileext']) ? $file_info['fileext'] : pathinfo($file_info['data'], PATHINFO_EXTENSION);
          if ($ext == 'css') {
            $selector_count += $file_info['linecount'];
            if ($selector_count > 4095) {
              $changed = TRUE;
              $selector_count = $file_info['linecount'];

              // Break large file into multiple small files.
              if ($file_info['linecount'] > 4095) {
                $parts = advagg_split_css_file($file_info);
              }
            }
          }
        }

        // If one of the above options changed, it needs to be in a different
        // aggregate.
        if (!empty($parts)) {
          $onload_local = array_filter(array_unique($onload));
          foreach ($parts as $part) {
            ++$count;
            $groups[$location][$count][] = $part;
            if (!empty($onload_local)) {
              $groups[$location][$count][0]['onload'] = implode(';', $onload) . ';';
            }
          }
        }
        else {
          if ($changed) {
            ++$count;
          }
          $groups[$location][$count][] = $file_info;
        }
      }
      $onload = array_filter(array_unique($onload));
      if (!empty($onload)) {
        $groups[$location][$count][0]['onload'] = implode(';', $onload) . ';';
      }
    }
    // Grouping if inline is mixed between files.
    ++$location;
  }
  return $groups;
}

/**
 * Given a file info array it will split the file up.
 *
 * @param array $file_info
 *   File info array from advagg_get_info_on_file().
 *
 * @return array
 *   array array with advagg_get_info_on_file data & split data.
 */
function advagg_split_css_file($file_info) {
  // Make advagg_parse_media_blocks() available.
  module_load_include('inc', 'advagg', 'advagg.missing');

  // Get the CSS file and break up by media queries.
  $file_contents = file_get_contents($file_info['data']);
  $media_blocks = advagg_parse_media_blocks($file_contents);

  // Get 98% of the advagg_ie_css_selector_limiter_value; usually 4013.
  $selector_split_value = (int) max(floor(variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE) * 0.98), 100);
  $part_selector_count = 0;
  $major_chunks = array();
  $counter = 0;
  // Group media queries together.
  foreach ($media_blocks as $media_block) {
    $matched = array();
    // @ignore sniffer_files_linelength_toolong:2
    // Get the number of selectors.
    // http://stackoverflow.com/questions/12567000/regex-matching-for-counting-css-selectors/12567381#12567381
    $selector_count = preg_match_all('/\{.+?\}|,/s', $media_block, $matched);
    $part_selector_count += $selector_count;

    if ($part_selector_count > $selector_split_value) {
      if (isset($major_chunks[$counter])) {
        ++$counter;
        $major_chunks[$counter] = $media_block;
      }
      else {
        $major_chunks[$counter] = $media_block;
      }
      ++$counter;
      $part_selector_count = 0;
    }
    else {
      if (isset($major_chunks[$counter])) {
        $major_chunks[$counter] .= "\n" . $media_block;
      }
      else {
        $major_chunks[$counter] = $media_block;
      }
    }
  }

  $parts = array();
  $overall_split = 0;
  $split_at = $selector_split_value;
  foreach ($major_chunks as $chunk_key => $chunks) {
    $last_chunk = FALSE;
    if (count($major_chunks) - 1 == $chunk_key) {
      $last_chunk = TRUE;
    }

    // Get the number of selectors.
    $matches = array();
    $selector_count = preg_match_all('/\{.+?\}|,/s', $chunks, $matches);

    // Pass through if selector count is low.
    if ($selector_count < $selector_split_value) {
      $overall_split += $selector_count;
      if ($last_chunk) {
        $file_info['split_last_part'] = TRUE;
      }
      $parts[] = advagg_create_subfile($chunks, $overall_split, $file_info);
      continue;
    }

    $media_query = '';
    if (strpos($chunks, '@media') !== FALSE) {
      $media_query_pos = strpos($chunks, '{');
      $media_query = substr($chunks, 0, $media_query_pos);
      $chunks = substr($chunks, $media_query_pos + 1);
    }

    // Split CSS into selector chunks.
    $split = preg_split('/(\{.+?\}|,)/si', $chunks, -1, PREG_SPLIT_DELIM_CAPTURE);

    // Setup and handle media queries.
    $new_css_chunk = array(0 => '');
    $selector_chunk_counter = 0;
    $counter = 0;
    if (!empty($media_query)) {
      $new_css_chunk[0] = $media_query . '{';
      $new_css_chunk[1] = '';
      ++$selector_chunk_counter;
      ++$counter;
    }
    // Have the key value be the running selector count and put split array semi
    // back together.
    foreach ($split as $value) {
      $new_css_chunk[$counter] .= $value;
      if (strpos($value, '}') === FALSE) {
        ++$selector_chunk_counter;
      }
      else {
        if ($counter + 1 < $selector_chunk_counter) {
          $selector_chunk_counter += ($counter - $selector_chunk_counter + 1) / 2;
        }
        $counter = $selector_chunk_counter;
        if (!isset($new_css_chunk[$counter])) {
          $new_css_chunk[$counter] = '';
        }
      }
    }

    // Group selectors.
    $first = TRUE;
    while (!empty($new_css_chunk)) {
      // Find where to split the array.
      $string_to_write = '';
      while (array_key_exists($split_at, $new_css_chunk) === FALSE) {
        --$split_at;
      }

      // Combine parts of the so that it can be saved to disk.
      foreach ($new_css_chunk as $key => $value) {
        $string_to_write .= $value;
        unset($new_css_chunk[$key]);
        if ($key == $split_at) {
          $overall_split = $split_at;
          $split_at += $selector_split_value;
          break;
        }
      }

      // Handle media queries.
      if (!empty($media_query)) {
        // See if brackets need a new line.
        if (strpos($string_to_write, "\n") === 0) {
          $open_bracket = '{';
        }
        else {
          $open_bracket = "{\n";
        }
        if (strrpos($string_to_write, "\n") === strlen($string_to_write)) {
          $close_bracket = '}';
        }
        else {
          $close_bracket = "\n}";
        }

        // Fix syntax around media queries.
        if ($first) {
          $string_to_write .= $close_bracket;
        }
        elseif (empty($new_css_chunk)) {
          $string_to_write = $media_query . $open_bracket . $string_to_write;
        }
        else {
          $string_to_write = $media_query . $open_bracket . $string_to_write . $close_bracket;
        }
      }
      // Handle the last split part.
      if (empty($new_css_chunk) && $last_chunk) {
        $file_info['split_last_part'] = TRUE;
      }
      // Write the data.
      $parts[] = advagg_create_subfile($string_to_write, $overall_split, $file_info);
      $first = FALSE;
    }
  }
  return $parts;
}

/**
 * Write CSS parts to disk; used when CSS selectors in one file is > 4096.
 *
 * @param string $css
 *   CSS data to write to disk.
 * @param int $overall_split
 *   Running count of what selector we are from the original file.
 * @param array $file_info
 *   File info array from advagg_get_info_on_file().
 *
 * @return array
 *   array with advagg_get_info_on_file data & split data.
 */
function advagg_create_subfile($css, $overall_split, $file_info) {
  static $parts_uri;
  static $parts_path;
  if (!isset($parts_uri)) {
    list($css_path, $js_path) = advagg_get_root_files_dir();
    $parts_uri = $css_path[0] . '/parts';
    $parts_path = $css_path[1] . '/parts';

    // Create the public://advagg_css/parts dir.
    file_prepare_directory($parts_uri, FILE_CREATE_DIRECTORY);

    // Make advagg_save_data() available.
    module_load_include('inc', 'advagg', 'advagg.missing');
  }

  // Write the current chunk of the CSS into a file.
  $new_filename = str_ireplace('.css', '.' . $overall_split . '.css', $file_info['data']);
  $part_uri = $parts_uri . '/' . $new_filename;
  $dirname = drupal_dirname($part_uri);
  file_prepare_directory($dirname, FILE_CREATE_DIRECTORY);
  advagg_save_data($part_uri, $css, TRUE);

  // Get info on the file that was just created.
  $part = advagg_get_info_on_file($parts_path . '/' . $new_filename) + $file_info;
  $part['split'] = TRUE;
  $part['split_location'] = $overall_split;
  $part['split_original'] = $file_info['data'];

  return $part;
}

/**
 * Replacement for drupal_build_css_cache() and drupal_build_js_cache().
 *
 * @param array $files_to_aggregate
 *   An array of CSS/JS groups.
 * @param array $type
 *   css or js.
 *
 * @return array
 *   array of aggregate files.
 */
function advagg_build_aggregate_plans($files_to_aggregate, $type) {
  // Place into biggest grouping possible.
  $groups = advagg_generate_groups($files_to_aggregate);

  // Get filenames.
  $files = advagg_generate_filenames($groups, $type);

  // Insert/Update Database.
  advagg_insert_update_db($files, $type, 1);
  // Update atimes for root.
  advagg_update_all_atimes($files);

  // Run hooks to modify the aggregate.
  // Call hook_advagg_build_aggregate_plans_alter().
  $modified = FALSE;
  drupal_alter('advagg_build_aggregate_plans', $files, $modified, $type);

  // If the hook above modified anything, re-insert into database.
  if ($modified) {
    // Insert/Update Database.
    advagg_insert_update_db($files, $type, 0);
    // Update atimes for non root.
    advagg_update_all_atimes($files);
  }

  // Get file paths.
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Build the plan.
  $plans = array();

  foreach ($files as $agg_filename => $values) {
    if ($type == 'css') {
      $mixed_media = FALSE;
      $media = NULL;
      foreach ($values['files'] as $key => $value) {
        if (!isset($value['media'])) {
          continue;
        }
        if (is_null($media)) {
          $media = $value['media'];
        }
        if ($media != $value['media']) {
          $mixed_media = TRUE;
        }
      }
    }

    $first = reset($values['files']);
    if (!empty($mixed_media)) {
      $first['media'] = 'all';
    }
    $url = ($type == 'css') ? $css_path[0] : $js_path[0];
    $path = ($type == 'css') ? $css_path[1] : $js_path[1];
    $plans[] = array(
      'data' => $url . '/' . $agg_filename,
      'media' => isset($first['media']) ? $first['media'] : '',
      'defer' => isset($first['defer']) ? $first['defer'] : '',
      'async' => isset($first['async']) ? $first['async'] : '',
      'onload' => isset($first['onload']) ? $first['onload'] : '',
      'browsers' => isset($first['browsers']) ? $first['browsers'] : array(),
      'type' => $first['type'],
      'items' => $values,
      'filepath' => $path . '/' . $agg_filename,
      'filename' => $agg_filename,
    );
  }

  // Create the aggregate files.
  advagg_create_aggregate_files($plans);

  return $plans;
}

/**
 * Create the aggregate if it does not exist; using HTTPRL if possible.
 *
 * @param array $plans
 *   An array of aggregate file names.
 */
function advagg_create_aggregate_files($plans) {
  $filenames = array();
  foreach ($plans as $plan) {
    $filenames[] = $plan['filename'];
  }

  // If the httprl module exists and we want to use it.
  // @ignore sniffer_whitespace_openbracketspacing_openingwhitespace
  if (   module_exists('httprl')
      && variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL)
      && (is_callable('httprl_is_background_callback_capable') && httprl_is_background_callback_capable() || !is_callable('httprl_is_background_callback_capable'))
      ) {
    // Setup callback options array; call function in the background.
    $callback_options = array(
      array(
        'function' => 'advagg_build_aggregates',
      ),
      $filenames,
    );
    // Queue up the request.
    httprl_queue_background_callback($callback_options);
    // Execute request.
    $return = httprl_send_request();
  }
  else {
    $return = advagg_build_aggregates($filenames);
  }
}

/**
 * Loads the stylesheet and resolves all @import commands.
 *
 * Loads a stylesheet and replaces @import commands with the contents of the
 * imported file. Use this instead of file_get_contents when processing
 * stylesheets.
 *
 * The returned contents are compressed removing white space and comments only
 * when CSS aggregation is enabled. This optimization will not apply for
 * color.module enabled themes with CSS aggregation turned off.
 *
 * @param string $file
 *   Name of the stylesheet to be processed.
 * @param bool $optimize
 *   Defines if CSS contents should be compressed or not.
 * @param array $aggregate_settings
 *   array of settings.
 *
 * @return string
 *   Contents of the stylesheet, including any resolved @import commands.
 */
function advagg_load_css_stylesheet($file, $optimize, $aggregate_settings = NULL) {
  // Change context to that of when this aggregate was created.
  advagg_context_css($aggregate_settings, 0);

  // Get the stylesheets contents.
  $contents = drupal_load_stylesheet($file, $optimize);

  // Get the parent directory of this file, relative to the Drupal root.
  $css_base_url = substr($file, 0, strrpos($file, '/'));
  $url_parts = explode('advagg_css/parts/', $css_base_url);
  // If this CSS file is actually a part of a previously split larger CSS file,
  // don't use it to construct relative paths within the CSS file for
  // 'url( ... )' bits.
  if (count($url_parts) === 2) {
    $css_base_url = $url_parts[1];
  }
  _advagg_build_css_path(NULL, $css_base_url . '/');

  // Anchor all paths in the CSS with its base URL, ignoring external and
  // absolute paths.
  $contents = preg_replace_callback('/url\(\s*[\'"]?(?![a-z]+:|\/+)([^\'")]+)[\'"]?\s*\)/i', '_advagg_build_css_path', $contents);

  // Change context back.
  advagg_context_css($aggregate_settings, 1);

  // Return the stylesheets contents.
  return $contents;
}

/**
 * Changes context when generating CSS.
 *
 * @param array $aggregate_settings
 *   array of settings.
 * @param int $mode
 *   0 to change context to what is inside of $aggregate_settings.
 *   1 to change context back.
 */
function advagg_context_css($aggregate_settings, $mode) {
  $original = &drupal_static(__FUNCTION__);

  // Use current $aggregate_settings if none was passed in.
  if (is_null($aggregate_settings)) {
    $aggregate_settings = advagg_current_hooks_hash_array();
  }

  // Call hook_advagg_context_alter().
  drupal_alter('advagg_context', $original, $aggregate_settings, $mode);
}

/**
 * Prefixes all paths within a CSS file for drupal_build_css_cache().
 *
 * @see _drupal_build_css_path()
 * @see https://drupal.org/node/1961340#comment-7735815
 * @see https://drupal.org/node/1514182#comment-7875489
 */
function _advagg_build_css_path($matches, $base = NULL) {
  $_base = &drupal_static(__FUNCTION__);
  // Store base path for preg_replace_callback.
  if (isset($base)) {
    $_base = $base;
  }

  // Prefix with base and remove '../' segments where possible.
  $path = $_base . $matches[1];
  $last = '';
  while ($path != $last) {
    $last = $path;
    $path = preg_replace('`(^|/)(?!\.\./)([^/]+)/\.\./`', '$1', $path);
  }

  $path = file_create_url($path);
  // Decoding path because some browsers can not handle encoded urls inside of
  // CSS. file_create_url() -> drupal_encode_path() -> rawurlencode().
  $path = rawurldecode($path);
  return 'url(' . $path . ')';
}
