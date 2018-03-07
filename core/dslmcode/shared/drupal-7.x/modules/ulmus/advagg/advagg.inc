<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * These functions are needed for cache misses.
 */

/**
 * Insert/Update data in advagg tables.
 *
 * Tables: advagg_files, advagg_aggregates, advagg_aggregates_versions.
 *
 * @param array $files
 *   List of files in the aggregate as well as the aggregate name.
 * @param string $type
 *   String; css or js.
 * @param int $root
 *   Is this a root aggregate.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_update_db(array $files, $type, $root) {
  // Record if a database write was done.
  $write_done = FALSE;

  // Loop through all files.
  foreach ($files as $values) {
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
  // Info for the DB.
  $record = array(
    'aggregate_filenames_hash' => $aggregate_filenames_hash,
    'aggregate_contents_hash' => $aggregate_contents_hash,
    'atime' => 0,
    'root' => $root,
  );

  // Save new aggregate into the database if it does not exist.
  $return = db_merge('advagg_aggregates_versions')
    ->key(array(
      'aggregate_filenames_hash' => $record['aggregate_filenames_hash'],
      'aggregate_contents_hash' => $record['aggregate_contents_hash'],
    ))
    ->insertFields($record)
    ->execute();
  return $return;
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
function advagg_insert_aggregate(array $files, $aggregate_filenames_hash) {
  // Record if a database write was done.
  $write_done = FALSE;

  // Check if the aggregate is in the database.
  $files_in_db = array();
  $query = db_select('advagg_aggregates', 'aa')
    ->fields('aa', array('filename_hash'))
    ->condition('aggregate_filenames_hash', $aggregate_filenames_hash)
    ->orderBy('aa.porder', 'ASC')
    ->execute();
  foreach ($query as $row) {
    $files_in_db[$row->filename_hash] = (array) $row;
  }

  $count = 0;
  foreach ($files as $file_meta_data) {
    ++$count;

    // Skip if the file already exists in the aggregate.
    if (!empty($files_in_db[$file_meta_data['filename_hash']])) {
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
      'settings' => serialize($settings),
    );
    $return = db_merge('advagg_aggregates')
      ->key(array(
        'aggregate_filenames_hash' => $record['aggregate_filenames_hash'],
        'filename_hash' => $record['filename_hash'],
      ))
      ->insertFields($record)
      ->execute();

    if ($return) {
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
 *   String; css or js.
 *
 * @return bool
 *   Return TRUE if anything was written to the database.
 */
function advagg_insert_update_files(array $files, $type) {
  // Record if a database write was done.
  $write_done = FALSE;

  $filename_hashes = array();
  foreach ($files as $file_meta_data) {
    $filename_hashes[] = $file_meta_data['filename_hash'];
  }

  $files_in_db = array();
  if (!empty($filename_hashes)) {
    $query = db_select('advagg_files', 'af')
      ->fields('af')
      ->condition('filename_hash', $filename_hashes)
      ->execute();
    foreach ($query as $row) {
      $files_in_db[$row->filename] = (array) $row;
    }
  }

  // Make drupal_get_installed_schema_version() available.
  include_once DRUPAL_ROOT . '/includes/install.inc';
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
    try {
      // Check the file in the database.
      if (empty($files_in_db[$filename])) {
        // Add in filesize_processed if the schema is 7210 or higher.
        if (drupal_get_installed_schema_version('advagg') >= 7210) {
          $record['filesize_processed'] = (int) advagg_generate_filesize_processed($filename, $type);
        }
        // Add in use_strict if the schema is 7212 or higher.
        if (drupal_get_installed_schema_version('advagg') >= 7212) {
          $record['use_strict'] = 0;
          if ($type === 'js') {
            $record['use_strict'] = (int) advagg_does_js_start_with_use_strict($filename);
          }
        }

        // Insert into database.
        $record['changes'] = 1;

        $return = db_merge('advagg_files')
          ->key(array(
            'filename_hash' => $record['filename_hash'],
          ))
          ->insertFields($record)
          ->execute();
        if ($return) {
          if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
            watchdog('advagg-debug', 'Inserting into db <pre>@record</pre>.', array('@record' => print_r($record, TRUE)), WATCHDOG_DEBUG);
          }
          $write_done = TRUE;
        }
      }
      else {
        // Take changes counter out of the diff equation.
        $changes = $files_in_db[$filename]['changes'];
        unset($files_in_db[$filename]['changes']);
        // If not in strict mode, only use mtime if newer than the existing one.
        if (!variable_get('advagg_strict_mtime_check', ADVAGG_STRICT_MTIME_CHECK)) {
          // Make sure mtime only moves forward.
          if ($record['mtime'] <= $files_in_db[$filename]['mtime']) {
            $record['mtime'] = $files_in_db[$filename]['mtime'];
          }
        }

        // If something is different, update.
        $diff = array_diff_assoc($record, $files_in_db[$filename]);
        if (!empty($diff)) {
          $diff['changes'] = $changes + 1;
          $diff['filename_hash'] = $record['filename_hash'];

          // Add in filesize_processed if the schema is 7210 or higher.
          if (drupal_get_installed_schema_version('advagg') >= 7210) {
            $diff['filesize_processed'] = (int) advagg_generate_filesize_processed($filename, $type);
          }
          if (drupal_get_installed_schema_version('advagg') >= 7212) {
            $diff['use_strict'] = 0;
            if ($type === 'js') {
              $diff['use_strict'] = (int) advagg_does_js_start_with_use_strict($filename);
              if (empty($diff['use_strict'])) {
                $diff['use_strict'] = 0;
              }
            }
          }

          $return = db_merge('advagg_files')
            ->key(array(
              'filename_hash' => $diff['filename_hash'],
            ))
            ->fields($diff)
            ->execute();
          if ($return) {
            if (variable_get('advagg_debug', ADVAGG_DEBUG) >= 2) {
              watchdog('advagg-debug', 'Updating db <pre>@diff</pre>.', array('@diff' => print_r($diff, TRUE)), WATCHDOG_DEBUG);
            }
            $write_done = TRUE;
          }
        }
      }
    }
    catch (PDOException $e) {
      // If it fails we don't care, the file was added to the table by another
      // process then.
      // Still log it if in development mode.
      if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
        watchdog('advagg', 'Development Mode - Caught PDO Exception: <code>@info</code>', array('@info' => $e));
      }
    }
  }
  return $write_done;
}

/**
 * Given a filename calculate the processed filesize.
 *
 * @param string $filename
 *   String; filename containing path information as well.
 * @param string $type
 *   String; css or js.
 *
 * @return int
 *   Processed filesize.
 */
function advagg_generate_filesize_processed($filename, $type) {
  $files = &drupal_static(__FUNCTION__, array());
  if (!isset($files[$type][$filename])) {
    // Make advagg_get_*_aggregate_contents() available.
    module_load_include('inc', 'advagg', 'advagg.missing');
    $aggregate_settings = advagg_current_hooks_hash_array();

    $file_aggregate = array($filename => array());
    if ($type === 'css') {
      list($contents) = advagg_get_css_aggregate_contents($file_aggregate, $aggregate_settings);
    }
    elseif ($type === 'js') {
      list($contents) = advagg_get_js_aggregate_contents($file_aggregate, $aggregate_settings);
    }
    if (!empty($contents)) {
      $files[$type][$filename] = strlen(gzencode($contents, 9, FORCE_GZIP));
    }
    else {
      $files[$type][$filename] = 0;
    }
  }
  return $files[$type][$filename];
}

/**
 * Given a js string, see if "use strict"; is the first thing ran.
 *
 * @param string $filename
 *   String; filename containing path information as well.
 *
 * @return bool
 *   True if "use strict"; is the first thing ran.
 */
function advagg_does_js_start_with_use_strict($filename) {
  $files = &drupal_static(__FUNCTION__, array());
  if (!isset($files[$filename])) {
    // Make advagg_get_*_aggregate_contents() available.
    module_load_include('inc', 'advagg', 'advagg.missing');
    $aggregate_settings = advagg_current_hooks_hash_array();

    $file_aggregate = array($filename => array());
    list($contents) = advagg_get_js_aggregate_contents($file_aggregate, $aggregate_settings);

    // See if the js file starts with "use strict";.
    // Trim the JS down to 24kb.
    $length = variable_get('advagg_js_header_length', ADVAGG_JS_HEADER_LENGTH);
    $header = advagg_get_js_header($contents, $length);

    // Look for the string.
    $use_strict = stripos($header, '"use strict";');
    $strict_js = FALSE;
    if ($use_strict === FALSE) {
      $use_strict = stripos($header, "'use strict';");
    }
    if ($use_strict !== FALSE) {
      if ($use_strict == 0) {
        $strict_js = TRUE;
      }
      else {
        // Get all text before "use strict";.
        $substr = substr($header, 0, $use_strict);
        // Check if there are any comments.
        $single_line_comment = strpos($substr, '//');
        $multi_line_comment = strpos($substr, '/*');
        $in_function = strpos($substr, '{');
        if ($single_line_comment !== FALSE || $multi_line_comment !== FALSE) {
          // Remove js comments and try again.
          advagg_remove_js_comments($header);

          // Look for the string.
          $use_strict = stripos($header, '"use strict";');
          if ($use_strict === FALSE) {
            $use_strict = stripos($header, "'use strict';");
          }
          // Get all text before "use strict"; with comments removed.
          $substr = substr($header, 0, $use_strict);
          // Check if there is a function before use strict.
          $in_function = strpos($substr, '{');
        }
        if ($in_function === FALSE) {
          $strict_js = TRUE;
        }
      }
    }

    $files[$filename] = $strict_js;
  }
  return $files[$filename];
}

/**
 * Read only the first 8192 bytes to get the file header.
 *
 * @param string $content
 *   JS string to cut.
 * @param int $length
 *   The number of bytes to grab. See advagg_js_header_length variable.
 *
 * @return string
 *   The shortened JS string.
 */
function advagg_get_js_header($content, $length) {
  $content = trim($content);
  // Only grab the first X bytes.
  if (function_exists('mb_strcut')) {
    $header = mb_strcut($content, 0, $length);
  }
  else {
    $header = substr($content, 0, $length);
  }

  return $header;
}

/**
 * Remove comments from JavaScript.
 *
 * @param string $content
 *   JS string to minify.
 */
function advagg_remove_js_comments(&$content) {
  // Remove comments.
  $content = preg_replace('/(?:(?:\/\*(?:[^*]|(?:\*+[^*\/]))*\*+\/)|(?:(?<!\:|\\\|\'|\")\/\/.*))/', '', $content);
  // Remove space after colons.
  // Remove space before equal signs.
  // Remove space after equal signs.
  $content = str_replace(
    array(': ', ' =', '= '),
    array(':', '=', '='),
    $content
  );
  // Remove excessive whitespace.
  $content = str_replace(
    array("\r\n\r\n", "\n\n", "\r\r", '\t', '  ', '    ', '    '),
    '',
    $content
  );
}

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
function advagg_generate_filenames(array $groups, $type) {
  $files = array();
  foreach ($groups as $data) {
    foreach ($data as $files_with_meta_data) {

      // Get the aggregate filename and info about each file.
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
function advagg_get_aggregate_info_from_files($type, array $files_with_meta_data) {
  $filename_hashes = array();
  $content_hashes = array();
  $filenames = array();

  $files_info_filenames = array();
  foreach ($files_with_meta_data as $info) {
    if (!empty($info['data']) && is_string($info['data'])) {
      $files_info_filenames[] = $info['data'];
    }
    else {
      watchdog('advagg', 'Bad data key. File info: <code>@finfo</code>', array(
        '@finfo' => var_export($info, TRUE),
      ));
    }
  }

  // Get filesystem data.
  $files_info = advagg_get_info_on_files($files_info_filenames);

  foreach ($files_with_meta_data as $info) {
    // Skip if not a string or key doesn't exist.
    if (!is_string($info['data']) || !array_key_exists($info['data'], $files_info)) {
      continue;
    }

    $filename = $info['data'];
    $info += $files_info[$filename];
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
 * Load cache bin file info in static cache.
 *
 * @param array $files
 *   Array; array of filenames.
 *
 * @return array
 *   $cached_data. key is $cache_id; value is an array which contains
 *
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
function &advagg_load_files_info_into_static_cache(array $files) {
  // Get the static cache of this data.
  $cached_data = &drupal_static('advagg_get_info_on_file');

  // Get the statically cached data for all the given files.
  $cache_ids = array();
  foreach ($files as $file) {
    $cache_id = 'advagg:file:' . advagg_drupal_hash_base64($file);
    if (!empty($cached_data)
      && !empty($cached_data[$cache_id])
    ) {
      // Make sure the cache_id is included.
      $cached_data[$cache_id]['cache_id'] = $cache_id;
    }
    else {
      $cache_ids[$file] = $cache_id;
    }
  }
  // Get info from the cache back-end next.
  if (!empty($cache_ids)) {
    $values = array_values($cache_ids);
    $cache_hits = cache_get_multiple($values, 'cache_advagg_info');
    if (!empty($cache_hits)) {
      foreach ($cache_hits as $hit) {
        if (!empty($hit->data['data'])) {
          // Make sure the cache_id is included.
          $hit->data['cache_id'] = $hit->cid;
          // Add to static cache.
          $cached_data[$hit->cid] = $hit->data;
        }
      }
    }
  }
  return $cached_data;
}

/**
 * Given a filename calculate the hash for it. Uses static cache.
 *
 * @param string $file
 *   Filename.
 *
 * @return string
 *   hash of filename.
 */
function advagg_drupal_hash_base64($file) {
  // Get the static cache of this data.
  $cached_data = &drupal_static('advagg_drupal_hash_base64', array());
  if (!array_key_exists($file, $cached_data)) {
    $cached_data[$file] = drupal_hash_base64($file);
  }
  return $cached_data[$file];
}

/**
 * Given a filename calculate various hashes and gather meta data.
 *
 * @param array $files
 *   Array; array of filenames containing path information as well.
 * @param bool $bypass_cache
 *   Bool: TRUE to bypass the cache.
 *
 * @return array
 *   $return['filename'] which contains
 *
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
function advagg_get_info_on_files(array $files, $bypass_cache = FALSE, $run_alter = TRUE) {
  // Get the cached data.
  $cached_data = &advagg_load_files_info_into_static_cache($files);

  // Get basic info on the files.
  $return = array();
  foreach ($files as $file) {
    $filename_hash = advagg_drupal_hash_base64($file);
    $cache_id = 'advagg:file:' . $filename_hash;
    // If we are not bypassing the cache add cached data.
    if ($bypass_cache == FALSE
      && is_array($cached_data)
      && array_key_exists($cache_id, $cached_data)
    ) {
      $return[$file] = $cached_data[$cache_id];
      continue;
    }

    // Clear PHP's internal file status cache.
    advagg_clearstatcache($file);

    // Remove file in the cache if it does not exist.
    if (!file_exists($file) || is_dir($file)) {
      if (isset($cached_data[$cache_id])) {
        cache_clear_all($cache_id, 'cache_advagg_info', FALSE);
      }
      // Return filename_hash and data. Empty values for the other keys.
      $return[$file] = array(
        'filesize' => 0,
        'mtime' => 0,
        'filename_hash' => $filename_hash,
        'content_hash' => '',
        'linecount' => 0,
        'data' => $file,
        'cache_id' => $cache_id,
        '#no_cache' => TRUE,
      );
      continue;
    }

    // Get the file contents.
    $file_contents = (string) @advagg_file_get_contents($file);

    $ext = strtolower(pathinfo($file, PATHINFO_EXTENSION));
    if ($ext !== 'css' && $ext !== 'js') {
      // Get the $ext from the database.
      $row = db_select('advagg_files', 'af')
        ->fields('af')
        ->condition('filename', $file)
        ->execute()->fetchAssoc();
      if (!empty($row['filetype'])) {
        $ext = $row['filetype'];
      }
      if ($ext === 'less') {
        $ext = 'css';
      }
    }

    if ($ext === 'css') {
      // Get the number of selectors.
      $linecount = advagg_count_css_selectors($file_contents);
    }
    else {
      // Get the number of lines.
      $linecount = substr_count($file_contents, "\n");
    }

    // Build meta data array and set cache.
    $return[$file] = array(
      'filesize' => (int) @filesize($file),
      'mtime' => @filemtime($file),
      'filename_hash' => $filename_hash,
      'content_hash' => drupal_hash_base64($file_contents),
      'linecount' => $linecount,
      'data' => $file,
      'fileext' => $ext,
      'cache_id' => $cache_id,
    );
    if (isset($cached_data[$cache_id])) {
      $return[$file] += $cached_data[$cache_id];
    }
  }

  if ($run_alter) {
    // Run hook so other modules can modify the data on these files.
    // Call hook_advagg_get_info_on_files_alter().
    drupal_alter('advagg_get_info_on_files', $return, $cached_data, $bypass_cache);

    // Set the cache and populate return array.
    foreach ($return as $info) {
      // If no cache is empty add/update the cached entry.
      // Update the cache if it is new or something changed.
      if (empty($info['#no_cache'])
        && !empty($info['cache_id'])
        && (empty($cached_data[$info['cache_id']]) || $info !== $cached_data[$info['cache_id']])
      ) {
        // CACHE_PERMANENT isn't good here. Use 2 weeks from now + 0-45 days.
        // The random 0 to 45 day addition is to prevent a cache stampede.
        cache_set($info['cache_id'], $info, 'cache_advagg_info', round(REQUEST_TIME + 1209600 + mt_rand(0, 3888000), -3));
      }

      // Update static cache.
      $cached_data[$info['cache_id']] = $info;
    }
  }

  return $return;
}

/**
 * Given a filename calculate various hashes and gather meta data.
 *
 * @param string $filename
 *   String; filename containing path information.
 * @param bool $bypass_cache
 *   (optional) Bool: TRUE to bypass the cache.
 * @param bool $run_alter
 *   (optional) Bool: FALSE to not run drupal_alter.
 *
 * @return array
 *   Array containing key value pairs.
 *
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
function advagg_get_info_on_file($filename, $bypass_cache = FALSE, $run_alter = TRUE) {
  $files_info = advagg_get_info_on_files(array($filename), $bypass_cache, $run_alter);
  return $files_info[$filename];
}

/**
 * Build the filename.
 *
 * @param string $type
 *   String; css or js.
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
function advagg_build_filename($type, $aggregate_filenames_hash, $aggregate_contents_hash, $hooks_hash = '') {
  if (empty($hooks_hash)) {
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

/**
 * Group the CSS/JS into the biggest buckets possible.
 *
 * @param array $files_to_aggregate
 *   An array of CSS/JS groups.
 * @param string $type
 *   String; css or js.
 *
 * @return array
 *   New version of groups.
 */
function advagg_generate_groups(array $files_to_aggregate, $type) {
  $groups = array();
  $count = 0;
  $location = 0;

  $media = '';
  $defer = '';
  $async = '';
  $cache = '';
  $scope = '';
  $use_strict = 0;
  $browsers = array();
  $selector_count = 0;
  // Get CSS limit value.
  $limit_value = variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE);

  if (variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER)
    || variable_get('advagg_resource_hints_dns_prefetch', ADVAGG_RESOURCE_HINTS_DNS_PREFETCH)
    || variable_get('advagg_resource_hints_preconnect', ADVAGG_RESOURCE_HINTS_PRECONNECT)
    || variable_get('advagg_resource_hints_preload', ADVAGG_RESOURCE_HINTS_PRELOAD)
  ) {
    $filenames = array();
    foreach ($files_to_aggregate as $data) {
      foreach ($data as $values) {
        foreach ($values['items'] as $file_info) {
          if (!empty($file_info['data']) && is_string($file_info['data'])) {
            $filenames[] = $file_info['data'];
          }
          else {
            watchdog('advagg', 'Bad data key. File info: <code>@finfo</code> Group info: <code>@ginfo</code>', array(
              '@finfo' => var_export($file_info, TRUE),
              '@ginfo' => var_export($values, TRUE),
            ));
          }
        }
      }
    }

    // Get filesystem data.
    $files_info = advagg_get_info_on_files($filenames, TRUE);
  }

  $strict_files = array();
  if ($type == 'js') {
    // Make drupal_get_installed_schema_version() available.
    include_once DRUPAL_ROOT . '/includes/install.inc';
    if (drupal_get_installed_schema_version('advagg') >= 7213) {
      $query = db_select('advagg_files', 'af')
        ->fields('af', array('filename', 'use_strict'))
        ->condition('use_strict', 1)
        ->execute();
      foreach ($query as $row) {
        $strict_files[$row->filename] = $row->use_strict;
      }
    }
  }

  foreach ($files_to_aggregate as $data) {
    foreach ($data as $values) {

      // Group into the biggest buckets possible.
      $last_ext = '';
      foreach ($values['items'] as $file_info) {
        $parts = array();
        // Check to see if media, browsers, defer, async, cache, or scope has
        // changed from the previous run of this loop.
        $changed = FALSE;
        $ext = isset($file_info['fileext']) ? $file_info['fileext'] : pathinfo($file_info['data'], PATHINFO_EXTENSION);
        $ext = strtolower($ext);
        if ($ext !== 'css' && $ext !== 'js') {
          if (empty($last_ext)) {
            // Get the $ext from the database.
            $row = db_select('advagg_files', 'af')
              ->fields('af')
              ->condition('filename', $file_info['data'])
              ->execute()->fetchAssoc();
            $ext = $row['filetype'];
          }
          else {
            $ext = $last_ext;
          }
        }
        $last_ext = $ext;
        if ($ext === 'css') {
          if (isset($file_info['media'])) {
            if (variable_get('advagg_combine_css_media', ADVAGG_COMBINE_CSS_MEDIA)) {
              $file_info['media_query'] = $file_info['media'];
            }
            elseif ($media != $file_info['media']) {
              // Media changed.
              $changed = TRUE;
              $media = $file_info['media'];
            }
          }
          if (empty($file_info['media']) && !empty($media)) {
            // Media changed to empty.
            $changed = TRUE;
            $media = '';
          }
        }
        if (isset($file_info['browsers'])) {
          // Browsers changed.
          $diff = array_merge(array_diff_assoc($file_info['browsers'], $browsers), array_diff_assoc($browsers, $file_info['browsers']));
          if (!empty($diff)) {
            $changed = TRUE;
            $browsers = $file_info['browsers'];
          }
        }
        if (empty($file_info['browsers']) && !empty($browsers)) {
          // Browsers changed to empty.
          $changed = TRUE;
          $browsers = array();
        }

        if (!empty($strict_files[$file_info['data']]) && $use_strict != $strict_files[$file_info['data']]) {
          // use_strict value changed to 1.
          $changed = TRUE;
          $use_strict = 1;
        }
        if (!empty($use_strict) && empty($strict_files[$file_info['data']])) {
          // use_strict value changed to 0.
          $changed = TRUE;
          $use_strict = 0;
        }
        if (isset($file_info['defer']) && $defer != $file_info['defer']) {
          // Defer value changed.
          $changed = TRUE;
          $defer = $file_info['defer'];
        }
        if (!empty($defer) && empty($file_info['defer'])) {
          // Defer value changed to empty.
          $changed = TRUE;
          $defer = '';
        }
        if (isset($file_info['async']) && $async != $file_info['async']) {
          // Async value changed.
          $changed = TRUE;
          $async = $file_info['async'];
        }
        if (!empty($async) && empty($file_info['async'])) {
          // Async value changed to empty.
          $changed = TRUE;
          $async = '';
        }
        if (isset($file_info['cache']) && $cache != $file_info['cache']) {
          // Cache value changed.
          $changed = TRUE;
          $cache = $file_info['cache'];
        }
        if (!empty($cache) && empty($file_info['cache'])) {
          // Cache value changed to empty.
          $changed = TRUE;
          $cache = '';
        }
        if (isset($file_info['scope']) && $scope != $file_info['scope']) {
          // Scope value changed.
          $changed = TRUE;
          $scope = $file_info['scope'];
        }
        if (!empty($scope) && empty($file_info['scope'])) {
          // Scope value changed to empty.
          $changed = TRUE;
          $scope = '';
        }

        if (variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER)
          && array_key_exists('data', $file_info)
          && is_string($file_info['data'])
          && array_key_exists($file_info['data'], $files_info)
        ) {
          $file_info += $files_info[$file_info['data']];
          // Prevent CSS rules exceeding 4095 due to limits with IE9 and below.
          if ($ext === 'css') {
            $selector_count += $file_info['linecount'];
            if ($selector_count > $limit_value) {
              $changed = TRUE;
              $selector_count = $file_info['linecount'];

              // Break large file into multiple smaller files.
              if ($file_info['linecount'] > $limit_value) {
                $parts = advagg_split_css_file($file_info);
              }
            }
          }
        }

        // Merge in dns_prefetch.
        if ((variable_get('advagg_resource_hints_dns_prefetch', ADVAGG_RESOURCE_HINTS_DNS_PREFETCH)
          || variable_get('advagg_resource_hints_preconnect', ADVAGG_RESOURCE_HINTS_PRECONNECT))
          && isset($files_info[$file_info['data']]['dns_prefetch'])
        ) {
          if (!isset($file_info['dns_prefetch'])) {
            $file_info['dns_prefetch'] = array();
          }
          if (!empty($file_info['dns_prefetch']) && is_string($file_info['dns_prefetch'])) {
            $temp = $file_info['dns_prefetch'];
            unset($file_info['dns_prefetch']);
            $file_info['dns_prefetch'] = array($temp);
          }
          $file_info['dns_prefetch'] = array_filter(array_unique(array_merge($file_info['dns_prefetch'], $files_info[$file_info['data']]['dns_prefetch'])));
        }

        // Merge in preload.
        if (variable_get('advagg_resource_hints_preload', ADVAGG_RESOURCE_HINTS_PRELOAD)
          && isset($files_info[$file_info['data']]['preload'])
        ) {
          if (!isset($file_info['preload'])) {
            $file_info['preload'] = array();
          }
          if (!empty($file_info['preload']) && is_string($file_info['preload'])) {
            $temp = $file_info['preload'];
            unset($file_info['preload']);
            $file_info['preload'] = array($temp);
          }
          $file_info['preload'] = array_filter(array_unique(array_merge($file_info['preload'], $files_info[$file_info['data']]['preload'])));
        }

        // If one of the above options changed, it needs to be in a different
        // aggregate.
        if (!empty($parts)) {
          foreach ($parts as $part) {
            ++$count;
            $groups[$location][$count][] = $part;
          }
        }
        else {
          if ($changed) {
            ++$count;
          }
          $groups[$location][$count][] = $file_info;
        }
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
 * @param string $file_contents
 *   CSS file contents.
 *
 * @return array
 *   Array with advagg_get_info_on_file data and split data.
 */
function advagg_split_css_file(array $file_info, $file_contents = '') {
  // Make advagg_parse_media_blocks() available.
  module_load_include('inc', 'advagg', 'advagg.missing');

  // Get the CSS file and break up by media queries.
  if (empty($file_contents)) {
    $file_contents = (string) @advagg_file_get_contents($file_info['data']);
  }
  $media_blocks = advagg_parse_media_blocks($file_contents);

  // Get the advagg_ie_css_selector_limiter_value.
  $selector_limit = (int) max(variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE), 100);

  // Group media queries together.
  $part_selector_count = 0;
  $counter = 0;
  $values = array();
  foreach ($media_blocks as $media_block) {
    // Get the number of selectors.
    $selector_count = advagg_count_css_selectors($media_block);

    // This chunk is bigger than $selector_limit. It needs to be split.
    if ($selector_count > $selector_limit) {
      $inner_selector_count = 0;
      // Split css string.
      list($media_query, $split_css_strings) = advagg_split_css_string($media_block, $selector_limit);
      foreach ($split_css_strings as $split_css_strings) {
        $counter_changed = FALSE;
        if (empty($split_css_strings)) {
          continue;
        }

        // Make sure selector count doesn't go over selector limit.
        $inner_selector_count = advagg_count_css_selectors($split_css_strings);
        $part_selector_count += $inner_selector_count;
        if ($part_selector_count > $selector_limit) {
          if (!empty($values[$counter])) {
            ++$counter;
          }
          $counter_changed = TRUE;
          $part_selector_count = $inner_selector_count;
        }

        // Add to output array.
        if (isset($values[$counter])) {
          if (!empty($media_query)) {
            $values[$counter] .= "\n$media_query { $split_css_strings } ";
          }
          else {
            $values[$counter] .= "$split_css_strings";
          }
        }
        else {
          if (!empty($media_query)) {
            $values[$counter] = "$media_query { $split_css_strings } ";
          }
          else {
            $values[$counter] = $split_css_strings;
          }
        }
      }
      // Add to current selector counter and go to the next value.
      if (!$counter_changed) {
        $part_selector_count += $inner_selector_count;
      }
      continue;
    }

    $part_selector_count += $selector_count;
    if ($part_selector_count > $selector_limit) {
      if (!empty($values[$counter])) {
        ++$counter;
      }
      $values[$counter] = $media_block;
      $part_selector_count = $selector_count;
    }
    else {
      if (isset($values[$counter])) {
        $values[$counter] .= "\n$media_block";
      }
      else {
        $values[$counter] = $media_block;
      }
    }
  }

  // Save data.
  $parts = array();
  $overall_counter = 0;
  foreach ($values as $key => $value) {
    $last_chunk = FALSE;
    $file_info['split_last_part'] = FALSE;
    if (count($values) - 1 == $key) {
      $last_chunk = TRUE;
    }
    if ($last_chunk) {
      $file_info['split_last_part'] = TRUE;
    }

    // Get the number of selectors.
    $selector_count = advagg_count_css_selectors($value);
    $overall_counter += $selector_count;

    // Save file.
    $subfile = advagg_create_subfile($value, $overall_counter, $file_info);
    if (empty($subfile)) {
      // Something broke; do not create a subfile.
      watchdog('advagg', 'Spliting up a CSS file failed. File info: <code>@info</code>', array('@info' => var_export($file_info, TRUE)));
      return array();
    }
    $parts[] = $subfile;
  }
  return $parts;
}

/**
 * Count the number of selectors inside of a CSS string.
 *
 * @param string $css_string
 *   CSS string.
 *
 * @return int
 *   The number of CSS selectors.
 */
function advagg_count_css_selectors($css_string) {
  return substr_count($css_string, ',') + substr_count($css_string, '{') - substr_count($css_string, '@media');
}

/**
 * Given a css string it will split it if it's over the selector limit.
 *
 * @param string $css_string
 *   CSS string.
 * @param int $selector_limit
 *   How many selectors can be grouped together.
 *
 * @return array
 *   Array that contains the $media_query and the $css_array.
 */
function advagg_split_css_string($css_string, $selector_limit) {
  // See if this css string is wrapped in a @media statement.
  $media_query = '';
  $media_query_pos = strpos($css_string, '@media');
  if ($media_query_pos !== FALSE) {
    // Get the opening bracket.
    $open_bracket_pos = strpos($css_string, "{", $media_query_pos);
    // Skip if there is a syntax error.
    if ($open_bracket_pos === FALSE) {
      return array();
    }
    $media_query = substr($css_string, $media_query_pos, $open_bracket_pos - $media_query_pos);
    $css_string_inside = substr($css_string, $open_bracket_pos + 1);
  }
  else {
    $css_string_inside = $css_string;
  }

  // Split CSS into selector chunks.
  $split = preg_split('/(\{.+?\}|,)/si', $css_string_inside, -1, PREG_SPLIT_DELIM_CAPTURE);

  $new_css_chunk = array(0 => '');
  $selector_chunk_counter = 0;
  $counter = 0;
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

  // Generate output array in this function.
  $css_array = array();
  $keys = array_keys($new_css_chunk);
  $counter = 0;
  $chunk_counter = 0;
  foreach (array_keys($keys) as $key) {
    // Get out of loop if at the end of the array.
    if (!isset($keys[$key + 1])) {
      break;
    }

    // Get values, keys and counts.
    $this_value = $new_css_chunk[$keys[$key]];
    $this_key = $keys[$key];
    $next_key = $keys[$key + 1];
    $this_selector_count = $next_key - $this_key;

    // Single rule is bigger than the selector limit.
    if ($this_selector_count > $selector_limit) {
      // Get css rules for these selectors.
      $open_bracket_pos = strpos($this_value, "{");
      $css_rule = ' ' . substr($this_value, $open_bracket_pos);

      // Split on selectors.
      $split = preg_split('/(\,)/si', $this_value, NULL, PREG_SPLIT_OFFSET_CAPTURE);
      $index = 0;
      $counter = 0;
      while (isset($split[$index][1])) {
        // Get starting and ending positions of the selectors given the selector
        // limit.
        $next_index = $index + $selector_limit - 1;
        $start = $split[$index][1];
        if (isset($split[$next_index][1])) {
          $end = $split[$next_index][1];
        }
        else {
          // Last one.
          $temp = end($split);
          $split_key = key($split);
          $counter = $split_key % $selector_limit;
          $end_open_bracket_pos = (int) strpos($temp[0], "{");
          $end = $temp[1] + $end_open_bracket_pos;
        }

        // Extract substr.
        $sub_this_value = substr($this_value, $start, $end - $start - 1) . $css_rule;

        // Save substr.
        ++$chunk_counter;
        $key_output = $selector_limit;
        if (!empty($counter)) {
          $key_output = $selector_limit - $counter;
        }
        $css_array["$chunk_counter $key_output"] = '';

        if (!isset($css_array[$chunk_counter])) {
          $css_array[$chunk_counter] = $sub_this_value;
        }
        else {
          $css_array[$chunk_counter] .= $sub_this_value;
        }

        // Move counter.
        $index = $next_index;
      }
      continue;
    }

    $counter += $this_selector_count;
    if ($counter > $selector_limit) {
      $key_output = $counter - $this_selector_count;
      $css_array["$chunk_counter $key_output"] = '';
      $counter = $next_key - $this_key;
      ++$chunk_counter;
    }
    if (!isset($css_array[$chunk_counter])) {
      $css_array[$chunk_counter] = $this_value;
    }
    else {
      $css_array[$chunk_counter] .= $this_value;
    }
  }

  // Group into sets smaller than $selector_limit.
  return array($media_query, $css_array);
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
 *   Array with advagg_get_info_on_file data and split data; FALSE on failure.
 */
function advagg_create_subfile($css, $overall_split, array $file_info) {
  static $parts_uri;
  static $parts_path;
  if (!isset($parts_uri)) {
    list($css_path) = advagg_get_root_files_dir();
    $parts_uri = $css_path[0] . '/parts';
    $parts_path = $css_path[1] . '/parts';

    // Create the public://advagg_css/parts dir.
    file_prepare_directory($parts_uri, FILE_CREATE_DIRECTORY);

    // Make advagg_save_data() available.
    module_load_include('inc', 'advagg', 'advagg.missing');
  }

  // Get the path from $file_info['data'].
  $uri_path = advagg_get_relative_path($file_info['data']);
  if (!file_exists($uri_path) || is_dir($uri_path)) {
    return FALSE;
  }

  // Write the current chunk of the CSS into a file.
  $new_filename = str_ireplace('.css', '.' . $overall_split . '.css', $uri_path);

  // Fix for things that write dynamically to the public file system.
  $scheme = file_uri_scheme($new_filename);
  if ($scheme) {
    $wrapper = file_stream_wrapper_get_instance_by_scheme($scheme);
    if ($wrapper && method_exists($wrapper, 'getDirectoryPath')) {
      // Use the wrappers directory path.
      $new_filename = $wrapper->getDirectoryPath() . '/' . file_uri_target($new_filename);
    }
    else {
      // If the scheme does not have a wrapper; prefix file with the scheme.
      $new_filename = $scheme . '/' . file_uri_target($new_filename);
    }
  }

  $part_uri = $parts_uri . '/' . $new_filename;
  $dirname = drupal_dirname($part_uri);
  file_prepare_directory($dirname, FILE_CREATE_DIRECTORY);

  // Get info on the file that was just created.
  $part = advagg_get_info_on_file($parts_path . '/' . $new_filename, TRUE) + $file_info;
  $part['split'] = TRUE;
  $part['split_location'] = $overall_split;
  $part['split_original'] = $file_info['data'];

  // Overwrite/create file if hash doesn't match.
  $hash = drupal_hash_base64($css);
  if ($part['content_hash'] !== $hash) {
    advagg_save_data($part_uri, $css, TRUE);
    $part = advagg_get_info_on_file($parts_path . '/' . $new_filename, TRUE) + $file_info;
    $part['split'] = TRUE;
    $part['split_location'] = $overall_split;
    $part['split_original'] = $file_info['data'];
  }

  return $part;
}

/**
 * Replacement for drupal_build_css_cache() and drupal_build_js_cache().
 *
 * @param array $files_to_aggregate
 *   An array of CSS/JS groups.
 * @param string $type
 *   String; css or js.
 *
 * @return array
 *   array of aggregate files.
 */
function advagg_build_aggregate_plans(array $files_to_aggregate, $type) {
  if ($type !== 'css' && $type !== 'js') {
    return array();
  }

  // Place into biggest grouping possible.
  $groups = advagg_generate_groups($files_to_aggregate, $type);

  // Get filenames.
  $files = advagg_generate_filenames($groups, $type);

  // Insert/Update Database.
  advagg_insert_update_db($files, $type, 1);
  // Update atimes for root.
  advagg_multi_update_atime($files);

  // Run hooks to modify the aggregate.
  // Call hook_advagg_build_aggregate_plans_alter().
  $modified = FALSE;
  drupal_alter('advagg_build_aggregate_plans', $files, $modified, $type);

  // If the hook above modified anything, re-insert into database.
  if ($modified) {
    // Insert/Update Database.
    advagg_insert_update_db($files, $type, 0);
    // Update atimes for non root.
    advagg_multi_update_atime($files);
  }

  // Get file paths.
  list($css_path, $js_path) = advagg_get_root_files_dir();

  // Build the plan.
  $plans = array();

  foreach ($files as $agg_filename => $values) {
    if ($type === 'css') {
      $mixed_media = FALSE;
      $media = NULL;
      foreach ($values['files'] as $value) {
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

    $onload = array();
    $onerror = array();
    $attributes = array();
    $onloadcss = array();
    foreach ($values['files'] as &$items) {
      // Get onload.
      if (!empty($items['onload'])) {
        $onload[] = $items['onload'];
      }
      // Get attributes onload.
      if (!empty($items['attributes']['onload'])) {
        $onload[] = $items['attributes']['onload'];
        unset($items['attributes']['onload']);
      }
      // Get onerror.
      if (!empty($items['onerror'])) {
        $onload[] = $items['onerror'];
      }
      // Get attributes onerror.
      if (!empty($items['attributes']['onerror'])) {
        $onload[] = $items['attributes']['onerror'];
        unset($items['attributes']['onerror']);
      }
      // Get attributes onloadCSS.
      if (!empty($items['onloadCSS'])) {
        $onloadcss[] = $items['onloadCSS'];
      }
      // Get attributes onloadCSS.
      if (!empty($items['attributes']['onloadCSS'])) {
        $onloadcss[] = $items['attributes']['onloadCSS'];
        unset($items['attributes']['onloadCSS']);
      }
      // Get attributes.
      if (!empty($items['attributes'])) {
        $attributes += $items['attributes'];
      }
    }
    $onload = implode(';', array_unique(array_filter($onload)));
    $onerror = implode(';', array_unique(array_filter($onerror)));
    $onloadcss = implode(';', array_unique(array_filter($onloadcss)));

    $first = reset($values['files']);
    if (!empty($mixed_media)) {
      $first['media'] = 'all';
    }
    $url = ($type === 'css') ? $css_path[0] : $js_path[0];
    $path = ($type === 'css') ? $css_path[1] : $js_path[1];
    $plans[$agg_filename] = array(
      'data' => $url . '/' . $agg_filename,
      'media' => isset($first['media']) ? $first['media'] : '',
      'defer' => isset($first['defer']) ? $first['defer'] : '',
      'async' => isset($first['async']) ? $first['async'] : '',
      'onload' => $onload,
      'onerror' => $onerror,
      'browsers' => isset($first['browsers']) ? $first['browsers'] : array(),
      'cache' => isset($first['cache']) ? $first['cache'] : TRUE,
      'type' => $first['type'],
      'items' => $values,
      'filepath' => $path . '/' . $agg_filename,
      'filename' => $agg_filename,
      'attributes' => $attributes,
    );
    if (!empty($onloadcss)) {
      $plans[$agg_filename]['attributes']['onloadCSS'] = $onloadcss;
    }
  }
  $plans = array_values($plans);

  // Create the aggregate files.
  if (variable_get('advagg_pregenerate_aggregate_files', ADVAGG_PREGENERATE_AGGREGATE_FILES)) {
    advagg_create_aggregate_files($plans, $type);
  }

  // Run hooks to modify the plans.
  // Call hook_advagg_build_aggregate_plans_post_alter().
  drupal_alter('advagg_build_aggregate_plans_post', $plans, $type);

  return $plans;
}

/**
 * Create the aggregate if it does not exist; using HTTPRL if possible.
 *
 * @param array $plans
 *   An array of aggregate file names.
 * @param string $type
 *   String; css or js.
 *
 * @return array
 *   An array of what was done when generating the file.
 */
function advagg_create_aggregate_files(array $plans, $type) {
  $filenames = array();
  $return = array();
  foreach ($plans as $plan) {
    $filenames[] = $plan['filename'];
  }

  // If the httprl module exists and we want to use it.
  if (module_exists('httprl')
    && variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL)
    && (is_callable('httprl_is_background_callback_capable')
      && httprl_is_background_callback_capable()
      || !is_callable('httprl_is_background_callback_capable')
      )
  ) {
    if (variable_get('advagg_fast_filesystem', ADVAGG_FAST_FILESYSTEM)) {
      list($css_path, $js_path) = advagg_get_root_files_dir();
      foreach ($filenames as $key => $filename) {
        if ($type === 'css') {
          $uri = $css_path[0] . '/' . $filename;
        }
        elseif ($type === 'js') {
          $uri = $js_path[0] . '/' . $filename;
        }
        if (file_exists($uri)) {
          unset($filenames[$key]);
        }
      }
    }
    if (!empty($filenames)) {
      // Setup callback options array; call function in the background.
      $callback_options = array(
        array(
          'function' => 'advagg_build_aggregates',
        ),
        $filenames, $type,
      );
      // Queue up the request.
      httprl_queue_background_callback($callback_options);
      // Execute request.
      $return = httprl_send_request();
    }
  }
  else {
    $return = advagg_build_aggregates($filenames, $type);
  }
  return $return;
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
 *   Array of settings.
 *
 * @return string
 *   Contents of the stylesheet, including any resolved @import commands.
 */
function advagg_load_css_stylesheet($file, $optimize = TRUE, array $aggregate_settings = array(), $contents = '') {
  $old_base_path = $GLOBALS['base_path'];

  // Change context to that of when this aggregate was created.
  advagg_context_switch($aggregate_settings, 0);

  // Get the stylesheets contents.
  $contents = advagg_load_stylesheet($file, $optimize, TRUE, $contents);

  // Resolve public:// if needed.
  if (!advagg_is_external($file) && file_uri_scheme($file)) {
    $file = advagg_get_relative_path($file);
  }

  // Get the parent directory of this file, relative to the Drupal root.
  $css_base_url = substr($file, 0, strrpos($file, '/'));

  // Handle split css files.
  list($css_path) = advagg_get_root_files_dir();
  $parts_path = $css_path[1] . '/parts/';
  $url_parts = strpos($css_base_url, $parts_path);
  // If this CSS file is actually a part of a previously split larger CSS file,
  // don't use it to construct relative paths within the CSS file for
  // 'url(...)' bits.
  if ($url_parts !== FALSE) {
    $css_base_url = substr($css_base_url, $url_parts + strlen($parts_path));
  }

  // Replace the old base path with the one that was passed in.
  if (advagg_is_external($css_base_url) || variable_get('advagg_skip_file_create_url_inside_css', ADVAGG_SKIP_FILE_CREATE_URL_INSIDE_CSS)) {
    $pos = strpos($css_base_url, $old_base_path);
    if ($pos !== FALSE) {
      $parsed_url = parse_url($css_base_url);
      if (!empty($parsed_url['path'])) {
        // Remove any double slash in path.
        $parsed_url['path'] = str_replace('//', '/', $parsed_url['path']);

        // Get newly recalculated position.
        $pos = strpos($parsed_url['path'], $old_base_path);

        // Replace.
        if (strpos($parsed_url['path'], '/') !== 0 && $old_base_path === '/') {
          // Special case if going to a subdir.
          $parsed_url['path'] = $GLOBALS['base_path'] . $parsed_url['path'];
        }
        else {
          $parsed_url['path'] = substr_replace($parsed_url['path'], $GLOBALS['base_path'], $pos, strlen($old_base_path));
        }

        $css_base_url = advagg_glue_url($parsed_url);
      }
    }
  }

  _advagg_build_css_path(array(), $css_base_url . '/', $aggregate_settings);
  // Anchor all paths in the CSS with its base URL, ignoring external,
  // absolute paths, and urls that start with # or %23 (SVG).
  $contents = preg_replace_callback('%url\(\s*+[\'"]?+(?![a-z]++:|/|\#|\%23+)([^\'"\)]++)[\'"]?+\s*+\)%i', '_advagg_build_css_path', $contents);

  // Change context back.
  advagg_context_switch($aggregate_settings, 1);

  // Return the stylesheets contents.
  return $contents;
}

/**
 * Changes context when generating CSS or JS files.
 *
 * @param array $aggregate_settings
 *   Array of settings.
 * @param int $mode
 *   Use 0 to change context to what is inside of $aggregate_settings.
 *   Use 1 to change context back.
 */
function advagg_context_switch(array $aggregate_settings, $mode) {
  $original = &drupal_static(__FUNCTION__);

  // Use current $aggregate_settings if none was passed in.
  if (empty($aggregate_settings)) {
    $aggregate_settings = advagg_current_hooks_hash_array();
  }

  // Call hook_advagg_context_alter().
  drupal_alter('advagg_context', $original, $aggregate_settings, $mode);
}

/**
 * Prefixes all paths within a CSS file for drupal_build_css_cache().
 *
 * @param array $matches
 *   Array of matched items from preg_replace_callback().
 * @param string $base
 *   Base path.
 * @param array $aggregate_settings
 *   Array of settings.
 *
 * @return string
 *   New version of the url() string from the css.
 *
 * @see _drupal_build_css_path()
 * @see https://drupal.org/node/1961340#comment-7735815
 * @see https://drupal.org/node/1514182#comment-7875489
 */
function _advagg_build_css_path(array $matches, $base = '', array $aggregate_settings = array()) {
  $_base = &drupal_static(__FUNCTION__, '');
  $_aggregate_settings = &drupal_static(__FUNCTION__ . '_aggregate_settings', array());
  // Store base path for preg_replace_callback.
  if (!empty($base)) {
    $_base = $base;
  }
  if (!empty($aggregate_settings)) {
    $_aggregate_settings = $aggregate_settings;
  }
  // Short circuit if no matches were passed in.
  if (empty($matches)) {
    return '';
  }

  // Prefix with base.
  $url = $_base . $matches[1];

  // If advagg_file_create_url() is not being used and the $url is local, redo
  // the $url taking the base_path into account.
  if (!advagg_is_external($url) && variable_get('advagg_skip_file_create_url_inside_css', ADVAGG_SKIP_FILE_CREATE_URL_INSIDE_CSS)) {
    $new_base_path = $GLOBALS['base_path'];
    if (isset($_aggregate_settings['variables']['base_path'])) {
      $new_base_path = $_aggregate_settings['variables']['base_path'];
    }
    // Remove first /.
    $new_base_path = ltrim($new_base_path, '/');
    $pos = FALSE;
    // See if base_path is in the passed in $_base.
    if (!empty($new_base_path)) {
      $pos = strpos($_base, $new_base_path);
    }
    if ($pos !== FALSE) {
      $url = substr($_base, $pos) . $matches[1];
    }
    else {
      $url = $new_base_path . $_base . $matches[1];
    }
  }
  // Remove '../' segments where possible.
  $last = '';
  while ($url != $last) {
    $last = $url;
    $url = preg_replace('`(^|/)(?!\.\./)([^/]+)/\.\./`', '$1', $url);
  }

  // Parse and build back the url without the query and fragment parts.
  $parsed_url = parse_url($url);
  $base_url = advagg_glue_url($parsed_url, TRUE);

  $query = isset($parsed_url['query']) ? $parsed_url['query'] : '';
  // In the case of certain URLs, we may have simply a '?' character without
  // further parameters. parse_url() misses this and leaves 'query' blank, so
  // need to this back in.
  // See http://www.fontspring.com/blog/the-new-bulletproof-font-face-syntax
  // for more information.
  if ($query != '' || strpos($url, $base_url . '?') === 0) {
    $query = '?' . $query;
  }
  $fragment = isset($parsed_url['fragment']) ? '#' . $parsed_url['fragment'] : '';

  $run_file_create_url = FALSE;
  if (!variable_get('advagg_skip_file_create_url_inside_css', ADVAGG_SKIP_FILE_CREATE_URL_INSIDE_CSS)) {
    $run_file_create_url = TRUE;
  }
  if (empty($parsed_url['host'])) {
    $base_url = ltrim($base_url, '/');
  }
  $base_url = advagg_file_create_url($base_url, $_aggregate_settings, $run_file_create_url, 'css');

  return 'url(' . $base_url . $query . $fragment . ')';
}
