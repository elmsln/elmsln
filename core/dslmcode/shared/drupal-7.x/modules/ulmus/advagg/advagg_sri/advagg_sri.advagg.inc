<?php

/**
 * @file
 * Advanced aggregation sri module.
 */

/**
 * @addtogroup advagg_hooks
 * @{
 */

/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Save the hash of the file.
 */
function advagg_sri_advagg_save_aggregate_alter(array &$files_to_save, array $aggregate_settings, array $other_parameters) {
  // * @param array $files_to_save
  // *   Array($uri => $contents).
  // * @param array $aggregate_settings
  // *   Array of settings.
  // * @param array $other_parameters
  // *   Array of containing $files and $type.
  foreach ($files_to_save as $uri => $contents) {
    // Skip gzip/brotli files.
    $ext = strtolower(pathinfo($uri, PATHINFO_EXTENSION));
    if ($ext === 'gz' || $ext === 'br') {
      continue;
    }

    $hashes = advagg_sri_compute_hashes($contents);

    // Save to the database.
    $filename = basename($uri);
    advagg_sri_set_filename_hashes($filename, $hashes);
  }
}

/**
 * Implements hook_advagg_build_aggregate_plans_post_alter().
 */
function advagg_sri_advagg_build_aggregate_plans_post_alter(array &$plans) {
  // * @param array $plans
  // *   Array of aggregate files.
  $advagg_sri = variable_get('advagg_sri', ADVAGG_SRI);
  if (empty($advagg_sri)) {
    return;
  }
  if ($advagg_sri == 1) {
    $sha_bits = 'sha256';
  }
  if ($advagg_sri == 2) {
    $sha_bits = 'sha384';
  }
  if ($advagg_sri == 3) {
    $sha_bits = 'sha512';
  }

  // Get all aggregates.
  $files = array();
  $filenames = array();
  foreach ($plans as $key => $values) {
    if ($values['type'] !== 'file' || empty($values['cache'])) {
      continue;
    }
    $files[$values['filename']] = $key;
    $filenames[$values['filepath']] = $values['filename'];
  }

  // Lookup hashes.
  $hashes = array();
  if (!empty($filenames)) {
    $hashes = advagg_sri_get_filenames_hashes($filenames);
  }

  // Set attributes.
  foreach ($hashes as $filename => $hash) {
    if (isset($files[$filename]) && isset($plans[$files[$filename]])) {
      $plans[$files[$filename]]['attributes']['integrity'] = $sha_bits . '-' . $hash[$sha_bits];
    }
  }
}

/**
 * Implements hook_advagg_build_aggregate_plans_alter().
 */
function advagg_sri_advagg_build_aggregate_plans_alter() {
  if (module_exists('httprl') && variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL) && variable_get('advagg_sri_file_generation', ADVAGG_SRI_FILE_GENERATION)) {
    $GLOBALS['conf']['advagg_use_httprl'] = FALSE;
  }
}

/**
 * Implements hook_advagg_missing_root_file().
 */
function advagg_sri_advagg_missing_root_file($aggregate_filename, $filename, $cache) {
  // Remove entries from the DB.
  if (!empty($aggregate_filename) && !empty($cache)) {
    advagg_sri_del_filename_hashes($aggregate_filename);
  }
  // Remove entries from the Cache.
  $ext = strtolower(pathinfo($aggregate_filename, PATHINFO_EXTENSION));
  $cid = "advagg:$ext:";
  cache_clear_all($cid, 'cache_advagg_aggregates', TRUE);
}

/**
 * Implements hook_advagg_removed_aggregates().
 */
function advagg_sri_advagg_removed_aggregates($kill_list) {
  foreach ($kill_list as $uri) {
    if (is_object($uri) && property_exists($uri, 'uri')) {
      $temp = $uri->uri;
      unset($uri);
      $uri = $temp;
    }
    // Skip gzip/brotli files.
    $ext = strtolower(pathinfo($uri, PATHINFO_EXTENSION));
    if ($ext === 'gz' || $ext === 'br') {
      continue;
    }
    $filename = basename($uri);
    advagg_sri_del_filename_hashes($filename);
  }
}

/**
 * @} End of "addtogroup advagg_hooks".
 */

/**
 * Store settings associated with hash.
 *
 * @param string $filename
 *   The name of the aggregated filename.
 * @param array $hashes
 *   An array of SHA hashes of the contents of this filename.
 *
 * @return MergeQuery
 *   value from db_merge
 */
function advagg_sri_set_filename_hashes($filename, array $hashes) {
  return db_merge('advagg_sri')
    ->key(array('filename' => $filename))
    ->fields(array(
      'filename' => $filename,
      'hashes' => serialize($hashes),
    ))
    ->execute();
}

/**
 * Store settings associated with hash.
 *
 * @param string $filename
 *   The name of the aggregated filename.
 *
 * @return DeleteQuery
 *   value from db_delete
 */
function advagg_sri_del_filename_hashes($filename) {
  return db_delete('advagg_sri')
    ->condition('filename', $filename)
    ->execute();
}

/**
 * Returns the hashes settings.
 *
 * @param array $filenames
 *   An array of filenames.
 *
 * @return array
 *   The hashes for the given filenames.
 */
function advagg_sri_get_filenames_hashes(array $filenames) {
  $hashes = array();
  // Do not use the DB if in development mode.
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $rows = db_select('advagg_sri', 'advagg_sri')
      ->fields('advagg_sri', array('filename', 'hashes'))
      ->condition('filename', $filenames, 'IN')
      ->execute();
    foreach ($rows as $row) {
      $hashes[$row->filename] = unserialize($row->hashes);
    }
  }

  // If the hash is not in the database, generate it on demand.
  $db_filenames = array_keys($hashes);
  $not_in_db = array_diff($filenames, $db_filenames);
  foreach ($not_in_db as $file) {
    $filepath = array_search($file, $filenames);
    if (is_readable($filepath)) {
      // Do not use advagg_file_get_contents here.
      $contents = (string) @file_get_contents($filepath);
      if (!empty($contents)) {
        $hashes[$file] = advagg_sri_compute_hashes($contents);
        advagg_sri_set_filename_hashes($file, $hashes[$file]);
      }
    }
  }

  // Check to make sure we have all hashes.
  $all_hashes = array_keys($hashes);
  $not_hashed = array_diff($filenames, $all_hashes);
  if (!empty($not_hashed)) {
    drupal_page_is_cacheable(FALSE);
    // Disable saving to the cache if a sri is missing.
    if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) > 1) {
      $GLOBALS['conf']['advagg_cache_level'] = 0;
    }

    if (!module_exists('httprl') || !variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL)) {
      watchdog('advagg_sri', 'The subresource integrity hashes could not be generated for these files: %files', array('%files' => print_r($not_hashed, TRUE)));
    }
  }

  return $hashes;
}

/**
 * Returns an array of hashes.
 *
 * @param string $contents
 *   The string to hash.
 *
 * @return array
 *   The hashes for the given string.
 */
function advagg_sri_compute_hashes($contents) {
  // Generate hashes.
  $hashes = array(
    'sha512' => base64_encode(hash('sha512', $contents, TRUE)),
    'sha384' => base64_encode(hash('sha384', $contents, TRUE)),
    'sha256' => base64_encode(hash('sha256', $contents, TRUE)),
  );
  return $hashes;
}
