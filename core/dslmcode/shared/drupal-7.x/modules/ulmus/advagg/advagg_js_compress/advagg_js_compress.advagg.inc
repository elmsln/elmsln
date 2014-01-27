<?php

/**
 * @file
 * Advanced CSS/JS aggregation js compression module.
 */

/**
 * Implement hook_advagg_get_js_file_contents_alter().
 *
 * Used to compress a js file.
 */
function advagg_js_compress_advagg_get_js_file_contents_alter(&$contents, $filename, $aggregate_settings) {
  // Get per file settings.
  if (!empty($aggregate_settings['variables']['advagg_js_compressor_file_settings'])) {
    $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $filename);
    if (isset($aggregate_settings['variables']['advagg_js_compressor_file_settings'][$form_api_filename])) {
      $aggregate_settings['variables']['advagg_js_compressor'] = $aggregate_settings['variables']['advagg_js_compressor_file_settings'][$form_api_filename];
    }
  }

  // Do nothing if js file compression is disabled.
  if (empty($aggregate_settings['variables']['advagg_js_compressor'])) {
    return;
  }

  // Make sure this file has been tested.
  $compressor = $aggregate_settings['variables']['advagg_js_compressor'];
  module_load_include('inc', 'advagg', 'advagg');
  $info = advagg_get_info_on_file($filename);
  if (!isset($info['advagg_js_compress'][$compressor]['code'])) {
    // Test file here on the spot.
    if (!module_exists('httprl') || !httprl_is_background_callback_capable()) {
      $info = advagg_js_compress_run_test($filename);
    }
    else {
      $compressors = array(1 => 'jsminplus', 2 => 'packer', 3 => 'jsmin');
      // Add in selected compressor.
      $compressors_to_test = array($compressor => $compressors[$compressor]);
      // Add in packer if enabled.
      if (!empty($aggregate_settings['variables']['advagg_js_compress_packer'])) {
        $compressors_to_test[2] = 'packer';
        ksort($compressors_to_test);
      }
      $info = advagg_js_compress_run_test($filename, $compressors_to_test);
    }
  }

  // Compress it if it passes the test.
  if (!empty($info['advagg_js_compress'][$compressor]['code']) && $info['advagg_js_compress'][$compressor]['code'] == 1) {
    advagg_js_compress_prep($contents, $filename, $aggregate_settings);
  }
}

/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Used to add in a .gz file if none exits & use packer on non gzip file.
 *
 * @param $files_to_save
 *   array($uri => $contents)
 * @param $aggregate_settings
 *   array of settings.
 * @param $other_parameters
 *   array of containing $files & $type.
 */
function advagg_js_compress_advagg_save_aggregate_alter(&$files_to_save, $aggregate_settings, $other_parameters) {
  list($files, $type) = $other_parameters;
  // Use packer on non gzip js files.
  $compressor = 2;

  // Return if gzip is disabled.
  // Return if packer is disabled.
  // Return if type is not js.
  if (   empty($aggregate_settings['variables']['advagg_gzip'])
      || empty($aggregate_settings['variables']['advagg_js_compress_packer'])
      || $type != 'js'
        ) {
    return;
  }
  module_load_include('inc', 'advagg', 'advagg');
  // Make sure all files in this aggregate are compatible with packer.
  foreach ($files as $file => $settings) {
    $info = advagg_get_info_on_file($file);
    if (!isset($info['advagg_js_compress'][$compressor]['code'])) {
      // Test file here on the spot.
      if (!module_exists('httprl') || !httprl_is_background_callback_capable()) {
        $info = advagg_js_compress_run_test($file);
      }
      else {
        // Add in selected compressor.
        $compressors = array(1 => 'jsminplus', 2 => 'packer', 3 => 'jsmin');
        $info = advagg_js_compress_run_test($file, array($compressor => $compressors[$compressor]));
      }
    }
    // If this file causes php to bomb or the ratio is way too good then do not
    // use packer on this aggregate.
    if (   !isset($info['advagg_js_compress'][$compressor]['code'])
        || $info['advagg_js_compress'][$compressor]['code'] == -1
        || $info['advagg_js_compress'][$compressor]['code'] == -3
          ) {
      return;
    }
  }

  // See if a .gz file of this aggregate already exists.
  $gzip_exists = FALSE;
  foreach ($files_to_save as $uri => $contents) {
    // See if this uri contains .gz near the end of it.
    $pos = strripos($uri, '.gz', 91 + strlen(ADVAGG_SPACE)*3);
    if (!empty($pos)) {
      $len = strlen($uri);
      // .gz file exists, exit loop.
      if ($pos == $len-3) {
        $gzip_exists = TRUE;
        break;
      }
    }
  }

  // Use the first file in the array.
  $data = reset($files_to_save);
  $uri = key($files_to_save);

  // If a .gz file does not exist, create one.
  if (!$gzip_exists) {
    // Compress it and add it to the $files_to_save array.
    $compressed = gzencode($data, 9, FORCE_GZIP);
    $files_to_save[$uri . '.gz'] = $compressed;
  }

  // Use packer on non gzip JS data.
  $aggregate_settings['variables']['advagg_js_compressor'] = $compressor;
  advagg_js_compress_prep($data, $uri, $aggregate_settings, FALSE);
  $files_to_save[$uri] = $data;
}

/**
 * Implement hook_advagg_changed_files().
 *
 * Used to retest js files when they change.
 */
function advagg_js_compress_advagg_changed_files($files, $types) {
  // Only care about js files.
  if (empty($types['js'])) {
    return;
  }
  $return = array();
  foreach ($files as $filename => $meta_data) {
    // Only care about js files.
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    if ($ext != 'js') {
      continue;
    }

    $return[$filename] = advagg_js_compress_run_test($filename);
  }
  return $return;
}

/**
 * Compress a JS string
 *
 * @param $contents
 *   Javascript string.
 * @param $filename
 *   filename.
 * @param $add_licensing
 *   FALSE to remove Source and licensing information comment.
 * @param $log_errors
 *   FALSE to disable logging to watchdog on failure.
 * @param $test_ratios
 *   FALSE to disable compression ratio testing.
 */
function advagg_js_compress_prep(&$contents, $filename, $aggregate_settings, $add_licensing = TRUE, $log_errors = TRUE, $test_ratios = TRUE) {
  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');
  $compressor = $aggregate_settings['variables']['advagg_js_compressor'];

  if ($compressor == 0) {
    return;
  }

  // Get the JS string length before the compression operation.
  $contents_before = $contents;
  $before = strlen($contents);

  // Try cache.
  $info = advagg_get_info_on_file($filename);
  $cache_id = 'advagg:js_compress:' . $compressor . ':' . $info['filename_hash'];
  $cache_id .= !empty($info['content_hash']) ? ':' . $info['content_hash'] : '';
  $cache = cache_get($cache_id, 'cache_advagg_info');
  if (!empty($cache->data)) {
    $contents = $cache->data;
  }
  else {
    // Strip Byte Order Marks (BOM's), preg_* cannot parse these well.
    $contents = str_replace(pack("CCC", 0xef, 0xbb, 0xbf), "", $contents);
    // Use the compressor.
    if ($compressor == 1) {
      advagg_js_compress_jsminplus($contents, $log_errors);
    }
    elseif ($compressor == 2) {
      advagg_js_compress_jspacker($contents);
    }
    elseif ($compressor == 3) {
      $contents = jsmin($contents);
    }

    // Cache minified data for at least 1 day.
    cache_set($cache_id, $contents, 'cache_advagg_info', REQUEST_TIME+86400);
  }

  if ($test_ratios) {
    // Make sure compression ratios are good.
    $after = strlen($contents);
    $ratio = 0;
    if ($before != 0) {
      $ratio = ($before - $after) / $before;
    }
    // Make sure the returned string is not empty or has a VERY high
    // compression ratio.
    if (empty($contents) || empty($ratio) || $ratio > $aggregate_settings['variables']['advagg_js_max_compress_ratio'] || $ratio < 0) {
      $contents = $contents_before;
    }
    elseif ($add_licensing) {
      $url = url($filename, array('absolute' => TRUE));
      $contents = "/* Source and licensing information for the line(s) below can be found at $url. */\n" . $contents . ";\n/* Source and licensing information for the above line(s) can be found at $url. */\n";
    }
  }
}

/**
 * Compress a JS string using jsmin+
 *
 * @param $contents
 *   Javascript string.
 * @param $log_errors
 *   FALSE to disable logging to watchdog on failure.
 */
function advagg_js_compress_jsminplus(&$contents, $log_errors = TRUE) {
  $contents_before = $contents;

  // Only include jsminplus.inc if the JSMinPlus class doesn't exist.
  if (!class_exists('JSMinPlus')) {
    include(drupal_get_path('module', 'advagg_js_compress') . '/jsminplus.inc');
  }
  ob_start();
  try {
    // JSMin+ the contents of the aggregated file.
    $contents = JSMinPlus::minify($contents);

    // Capture any output from JSMinPlus.
    $error = trim(ob_get_contents());
    if (!empty($error)) {
      throw new Exception($error);
    }
  }
  catch (Exception $e) {
    // Log the exception thrown by JSMin+ and roll back to uncompressed content.
    if ($log_errors) {
      watchdog('advagg_js_compress', $e->getMessage() . '<pre>' . $contents_before . '</pre>', NULL, WATCHDOG_WARNING);
    }
    $contents = $contents_before;
  }
  ob_end_clean();
}

/**
 * Compress a JS string using packer.
 *
 * @param $contents
 *   Javascript string.
 */
function advagg_js_compress_jspacker(&$contents) {
  // Use Packer on the contents of the aggregated file.
  if (!class_exists('JavaScriptPacker')) {
    include(drupal_get_path('module', 'advagg_js_compress') . '/jspacker.inc');
  }

  // Add semicolons to the end of lines if missing.
  $contents = str_replace("}\n", "};\n", $contents);
  $contents = str_replace("\nfunction", ";\nfunction", $contents);

  $packer = new JavaScriptPacker($contents, 62, TRUE, FALSE);
  $contents = $packer->pack();
}

/**
 * Test a JS file to see if it compresses well.
 *
 * @param $filename
 *   Path and filename of JS file.
 * @param $compressors
 *   (optional) List of compressors to test.
 */
function advagg_js_compress_run_test($filename, $compressors = array()) {
  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');
  $info = advagg_get_info_on_file($filename);
  // Cache info.
  $filename_hashes = &drupal_static('advagg_get_info_on_file');
  $cache_id = 'advagg:file:' . $info['filename_hash'];
  $httprl_used = FALSE;
  $compressor_list = array(1 => 'jsminplus', 2 => 'packer');
  if (function_exists('jsmin')) {
    $compressor_list[3] = 'jsmin';
    ksort($compressor_list);
  }

  // Build list of compressors.
  if (empty($compressors)) {
    $compressors = $compressor_list;
  }
  elseif (count($compressors) != count($compressor_list)) {
    // Schedule full test in a shutdown function later on.
    register_shutdown_function('advagg_js_compress_run_test_shutdown', $filename);
  }

  // Set to 0 if file doesn't exist.
  if (empty($info['content_hash'])) {
    $results = array(
      1 => array('code' => 0, 'ratio' => 0, 'name' => 'jsminplus'),
      2 => array('code' => 0, 'ratio' => 0, 'name' => 'packer'),
      3 => array('code' => 0, 'ratio' => 0, 'name' => 'jsmin'),
    );
  }
  else {
    // Set to "-1" so if php bombs, the file will be marked as bad.
    $results = array(
      1 => array('code' => -1, 'ratio' => 0, 'name' => 'jsminplus'),
      2 => array('code' => -1, 'ratio' => 0, 'name' => 'packer'),
      3 => array('code' => -1, 'ratio' => 0, 'name' => 'jsmin'),
    );
    // Run this via httprl if possible.
    if (!module_exists('httprl') || !httprl_is_background_callback_capable()) {
      // Place results into array.
      $info['advagg_js_compress'] = $results;
      // Save results, so if PHP bombs, this file is marked as bad.
      $filename_hashes[$cache_id] = $info;
      cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);

      // Test the file.
      $results = advagg_js_compress_test_file($filename, $compressors);
      $httprl_used = FALSE;
    }
    else {
      $httprl_used = TRUE;
      // Setup callback options array.
      $callback_options = array(
        array(
          'function' => 'advagg_js_compress_test_file',
          'return' => &$results,
        ),
        $filename, $compressors,
      );
      // Queue up the request.
      httprl_queue_background_callback($callback_options);
      // Execute request.
      httprl_send_request();

      // If php bombs out, try each compressor individually.
      foreach ($results as $key => $value) {
        if ($value['code'] == -1) {
          $sub_result = array();
          $sub_result[$key] = $value;
          // Setup callback options array.
          $callback_options = array(
            array(
              'function' => 'advagg_js_compress_test_file',
              'return' => &$sub_result,
            ),
            $filename, array($key => $value['name']),
          );
          // Queue up the request.
          httprl_queue_background_callback($callback_options);
          // Execute request.
          httprl_send_request();

          $results[$key] = $sub_result[$key];
        }
      }
    }
  }

  // Place results into array.
  $info['advagg_js_compress'] = $results;

  // Save results.
  $filename_hashes[$cache_id] = $info;
  cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);
  return $info;
}

/**
 * Test a JS file to see if it compresses well; called from a shutdown function.
 *
 * @param $filename
 *   Path and filename of JS file.
 */
function advagg_js_compress_run_test_shutdown($filename) {
  $been_called = &drupal_static(__FUNCTION__);

  // Only run this once per filename.
  if (!empty($been_called[$filename])) {
    return;
  }
  $been_called[$filename] = TRUE;

  if (module_exists('httprl') && httprl_is_background_callback_capable()) {
    // Setup callback options array.
    $callback_options = array(
      array(
        'function' => 'advagg_js_compress_run_test_httprl',
      ),
      $filename,
    );
    // Queue up the request.
    httprl_queue_background_callback($callback_options);
    // Execute request.
    httprl_send_request();
  }
  else {
    advagg_js_compress_run_test($filename);
  }
}
