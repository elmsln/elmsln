<?php

/**
 * @file
 * Advanced CSS/JS aggregation js compression module.
 */

if (defined('PHP_VERSION_ID') && constant('PHP_VERSION_ID') >= 50300) {
  // Include functions that use namespaces.
  module_load_include('inc', 'advagg_js_compress', 'advagg_js_compress.php53');
}

/**
 * @addtogroup advagg_hooks
 * @{
 */

/**
 * Implements hook_advagg_get_info_on_files_alter().
 *
 * Used to make sure the info is up to date in the cache.
 */
function advagg_js_compress_advagg_get_info_on_files_alter(&$return, $cached_data, $bypass_cache) {
  $compressor_list = advagg_js_compress_get_enabled_compressors(array(), -1);

  // Get cache ids.
  $cache_ids = array();
  foreach ($return as $filename => &$info) {
    if (empty($info['fileext']) || $info['fileext'] !== 'js') {
      continue;
    }
    // Check the cache.
    $cache_id = 'advagg:js_compress:info:' . $info['filename_hash'];
    $cache_id .= !empty($info['content_hash']) ? ':' . $info['content_hash'] : '';
    $cache_ids[$filename] = $cache_id;

    // Verify current data.
    $advagg_js_compress = array();
    if (!empty($info['advagg_js_compress'])) {
      foreach ($info['advagg_js_compress'] as $values) {
        $array_key = array_search($values['name'], $compressor_list);
        if ($array_key !== FALSE) {
          $cache_hits_data[$array_key] = $values;
        }
      }
    }
    ksort($advagg_js_compress);
    $info['advagg_js_compress'] = $advagg_js_compress;
  }

  unset($info);
  // If no cache ids are found bail out.
  if (empty($cache_ids)) {
    return;
  }

  // Get cached values.
  $values = array_values($cache_ids);
  $cache_hits = cache_get_multiple($values, 'cache_advagg_info');
  $compressors = advagg_js_compress_get_enabled_compressors();
  $advagg_get_info_on_file_cached_data = drupal_static('advagg_get_info_on_file');

  // Add cached values into $return.
  $filenames_info = array();
  foreach ($cache_ids as $filename => $cache_id) {
    $info = &$return[$filename];

    // Add in cached values.
    if (!empty($cache_hits[$cache_id])) {
      // Verify cache data.
      $cache_hits_data = array();
      foreach ($cache_hits[$cache_id]->data as $values) {
        $array_key = array_search($values['name'], $compressor_list);
        if ($array_key !== FALSE) {
          $cache_hits_data[$array_key] = $values;
        }
      }
      ksort($cache_hits_data);

      $info['advagg_js_compress'] = array_replace($info['advagg_js_compress'], $cache_hits_data);
    }

    // Generate missing values if needed.
    foreach ($compressors as $id => $name) {
      if (empty($info['advagg_js_compress'][$id])) {
        $filenames_info[$filename] = $info;
        break;
      }
      // Generate values if bypass cache is set and hashes do not match.
      if ($bypass_cache
        && (empty($advagg_get_info_on_file_cached_data[$info['cache_id']]['content_hash'])
          || $info['content_hash'] !== $advagg_get_info_on_file_cached_data[$info['cache_id']]['content_hash']
        )
      ) {
        $filenames_info[$filename] = $info;
        break;
      }
    }
  }

  // Do nothing if compressors are disabled or cache level does not equal 0.
  if (empty($compressors) || variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) != 0) {
    return;
  }

  if (!empty($filenames_info)) {
    $results = advagg_js_compress_run_mutiple_tests($filenames_info, $compressors);
    foreach ($results as $filename => $data) {
      $info = &$return[$filename];
      if (!empty($info['advagg_js_compress'])) {
        $data += $info['advagg_js_compress'];
      }
      $info['advagg_js_compress'] = $data;
    }
  }
}

/**
 * Implements hook_advagg_get_js_file_contents_alter().
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
    if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) == 0
      || variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) == 1
    ) {
      $compressors_to_test = advagg_js_compress_get_enabled_compressors($aggregate_settings);
      $info['advagg_js_compress'] = advagg_js_compress_run_test($filename, $info, $compressors_to_test);
    }
  }

  // Compress it if it passes the test.
  if (!empty($info['advagg_js_compress'][$compressor]['code'])
    && $info['advagg_js_compress'][$compressor]['code'] == 1
    && $info['advagg_js_compress'][$compressor]['ratio'] > variable_get('advagg_js_compress_ratio', ADVAGG_JS_COMPRESS_RATIO)
    && $info['advagg_js_compress'][$compressor]['ratio'] < variable_get('advagg_js_compress_max_ratio', ADVAGG_JS_COMPRESS_MAX_RATIO)
  ) {
    advagg_js_compress_prep($contents, $filename, $aggregate_settings);
  }
}

/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Used to add in a .gz file if none exits and use packer on non gzip file.
 */
function advagg_js_compress_advagg_save_aggregate_alter(&$files_to_save, $aggregate_settings, $other_parameters) {
  list($files, $type) = $other_parameters;

  // Return if gzip and brotli are disabled.
  // Return if packer is disabled.
  // Return if type is not js.
  if ((empty($aggregate_settings['variables']['advagg_gzip']) && empty($aggregate_settings['variables']['advagg_brotli']))
    || empty($aggregate_settings['variables']['advagg_js_compress_packer'])
    || $type !== 'js'
  ) {
    return;
  }

  // Use the first file in the array.
  $data = reset($files_to_save);
  $uri = key($files_to_save);
  // Use packer on non gzip/brotli js files.
  $compressor = 2;

  module_load_include('inc', 'advagg', 'advagg');
  // Make sure all files in this aggregate are compatible with packer.
  foreach ($files as $file => $settings) {
    $info = advagg_get_info_on_file($file);
    if (!isset($info['advagg_js_compress'][$compressor]['code'])) {
      // Add in selected compressor.
      $compressors = advagg_js_compress_get_enabled_compressors(array(), $compressor);
      // Test file here on the spot.
      $info['advagg_js_compress'] = advagg_js_compress_run_test($file, $info, $compressors);
    }
    // If this file causes php to bomb or the ratio is way too good then do not
    // use packer on this aggregate.
    if (!isset($info['advagg_js_compress'][$compressor]['code'])
      || $info['advagg_js_compress'][$compressor]['code'] == -1
      || $info['advagg_js_compress'][$compressor]['code'] == -3
    ) {
      return;
    }
  }

  // Use packer on non gzip/brotli JS data.
  $aggregate_settings['variables']['advagg_js_compressor'] = $compressor;
  advagg_js_compress_prep($data, $uri, $aggregate_settings, FALSE);
  $files_to_save[$uri] = $data;
}

/**
 * @} End of "addtogroup advagg_hooks".
 */

/**
 * Get a list of enabled compressors.
 *
 * @param array $aggregate_settings
 *   (Optional) aggregate_settings array.
 * @param int $compressor
 *   (Optional) get info about a particular compressor.
 */
function advagg_js_compress_get_enabled_compressors(array $aggregate_settings = array(), $compressor = 0) {
  // Create array.
  list(, , $compressors) = advagg_js_compress_configuration();
  if ($compressor == -1) {
    return $compressors;
  }

  $return_compressors = array();
  if (!empty($compressor)) {
    $return_compressors = array($compressor => $compressors[$compressor]);
  }
  else {
    // Get variables.
    if (isset($aggregate_settings['variables']['advagg_js_compressor'])) {
      $file = $aggregate_settings['variables']['advagg_js_compressor'];
    }
    else {
      $file = variable_get('advagg_js_compressor', ADVAGG_JS_COMPRESSOR);
    }
    if (isset($aggregate_settings['variables']['advagg_js_compress_packer'])) {
      $packer = $aggregate_settings['variables']['advagg_js_compress_packer'];
    }
    else {
      $packer = variable_get('advagg_js_compress_packer', ADVAGG_JS_COMPRESS_PACKER);
    }

    if (isset($compressors[$file])) {
      $return_compressors[$file] = $compressors[$file];
    }
    if ($packer) {
      $return_compressors[2] = $compressors[2];
    }
    if ($file == 3) {
      // Jsmin check.
      if (isset($compressors[3])) {
        $return_compressors[3] = $compressors[3];
      }
      // Fallback to jsqueeze.
      elseif (isset($compressors[5])) {
        $return_compressors[5] = $compressors[5];
      }
      // Fallback to jsmin+.
      else {
        $return_compressors[1] = $compressors[1];
      }
    }
  }

  return $return_compressors;
}

/**
 * Compress a JS string.
 *
 * @param string $contents
 *   Javascript string.
 * @param string $filename
 *   Filename.
 * @param array $aggregate_settings
 *   The aggregate_settings array.
 * @param bool $add_licensing
 *   FALSE to remove Source and licensing information comment.
 * @param bool $log_errors
 *   FALSE to disable logging to watchdog on failure.
 * @param bool $test_ratios
 *   FALSE to disable compression ratio testing.
 * @param bool $force_run
 *   TRUE to skip cache and force the compression test.
 */
function advagg_js_compress_prep(&$contents, $filename, array $aggregate_settings, $add_licensing = TRUE, $log_errors = TRUE, $test_ratios = TRUE, $force_run = FALSE) {
  $no_errors = TRUE;
  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');
  $compressor = $aggregate_settings['variables']['advagg_js_compressor'];

  if ($compressor == 0) {
    return;
  }
  // Do nothing if the file is already minified.
  $semicolon_count = substr_count($contents, ';');
  if ($compressor != 2
    && $semicolon_count > 10
    && $semicolon_count > (substr_count($contents, "\n", strpos($contents, ';')) * 5)
    && !$force_run
  ) {
    $add_license_setting
      = isset($aggregate_settings['variables']['advagg_js_compress_add_license']) ?
      $aggregate_settings['variables']['advagg_js_compress_add_license'] :
      variable_get('advagg_js_compress_add_license', ADVAGG_JS_COMPRESS_ADD_LICENSE);
    if ($add_licensing && ($add_license_setting == 1 || $add_license_setting == 3)) {
      $url = file_create_url($filename);
      $contents = "/* Source and licensing information for the line(s) below can be found at $url. */\n" . $contents . ";\n/* Source and licensing information for the above line(s) can be found at $url. */\n";
      return;
    }
  }

  // Get the JS string length before the compression operation.
  $contents_before = $contents;
  $before = strlen($contents);

  // Do not use jsmin() if the function can not be called.
  if ($compressor == 3 && !function_exists('jsmin')) {
    if (defined('PHP_VERSION_ID') && constant('PHP_VERSION_ID') >= 50300) {
      $compressor = 5;
      watchdog('advagg_js_compress', 'The jsmin function does not exist. Using JSqueeze.');
    }
    else {
      $compressor = 1;
      watchdog('advagg_js_compress', 'The jsmin function does not exist. Using JSmin+.');
    }
  }

  // Jsmin doesn't handle multi-byte characters before version 2, fall back to
  // different compressor if jsmin version < 2 and $contents contains multi-
  // byte characters.
  if ($compressor == 3 && (version_compare(phpversion('jsmin'), '2.0.0', '<') && advagg_js_compress_string_contains_multibyte_characters($contents))) {
    if (defined('PHP_VERSION_ID') && constant('PHP_VERSION_ID') >= 50300) {
      $compressor = 5;
      watchdog('advagg_js_compress', 'The currently installed jsmin version does not handle multibyte characters, you may consider to upgrade the jsmin extension. Using JSqueeze fallback.');
    }
    else {
      $compressor = 1;
      watchdog('advagg_js_compress', 'The currently installed jsmin version does not handle multibyte characters, you may consider to upgrade the jsmin extension. Using JSmin+ fallback.');
    }
  }

  // Try cache.
  $info = advagg_get_info_on_files(array($filename), FALSE, FALSE);
  $info = $info[$filename];
  $content_hash = !empty($info['content_hash']) ? ":{$info['content_hash']}" : '';
  $cache_id = "advagg:js_compress:{$compressor}:{$info['filename_hash']}:{$content_hash}";

  $cache = cache_get($cache_id, 'cache_advagg_aggregates');
  $force_run = variable_get('advagg_js_compress_force_run', $force_run);
  if (!$force_run && !empty($cache->data)) {
    $contents = $cache->data;
  }
  else {
    // Strip Byte Order Marks (BOM's), preg_* cannot parse these well.
    $contents = str_replace(pack("CCC", 0xef, 0xbb, 0xbf), "", $contents);
    // Jsmin may have errors (incorrectly determining EOLs) with mixed tabs
    // and spaces. An example: jQuery.Cycle 3.0.3 - http://jquery.malsup.com/
    if ($compressor == 3) {
      $contents = str_replace("\t", " ", $contents);
    }

    // Use the compressor.
    list(, , , $functions) = advagg_js_compress_configuration();
    if (isset($functions[$compressor])) {
      $run = $functions[$compressor];
      if (function_exists($run)) {
        $no_errors = $run($contents, $log_errors, $aggregate_settings);
      }
    }
    else {
      return;
    }

    // Under some unknown/rare circumstances, JSMin and JSqueeze can add 2-3
    // extraneous/wrong chars at the end of the string. This work-around will
    // remove these chars if necessary. See https://www.drupal.org/node/2627468.
    // Also see https://github.com/sqmk/pecl-jsmin/issues/46.
    if ($compressor == 3 || $compressor == 5) {
      $a = strrpos($contents, ';');
      $b = strrpos($contents, '}');
      $c = strrpos($contents, ')');

      // Simple scripts can just end, check to make sure there's a
      // match before cutting.
      if ($a !== FALSE || $b !== FALSE || $c !== FALSE) {
        $contents = substr($contents, 0, 1 + max($a, $b, $c));
      }
    }

    // Ensure that $contents ends with ; or }.
    if (strpbrk(substr(trim($contents), -1), ';}') === FALSE) {
      // ; or } not found, add in ; to the end of $contents.
      $contents = trim($contents) . ';';
    }

    if (empty($info['#no_cache'])) {
      // Cache minified data for 1 week.
      cache_set($cache_id, $contents, 'cache_advagg_aggregates', REQUEST_TIME + (86400 * 7));
    }
    else {
      // Cache minified inline data for 1 hour.
      cache_set($cache_id, $contents, 'cache_advagg_aggregates', REQUEST_TIME + 3600);
    }
  }

  // Make sure compression ratios are good.
  $after = strlen($contents);
  $ratio = 0;
  if ($before != 0) {
    $ratio = ($before - $after) / $before;
  }

  if ($test_ratios) {
    // Get ratios and license settings.
    $aggregate_settings['variables']['advagg_js_compress_max_ratio']
      = isset($aggregate_settings['variables']['advagg_js_compress_max_ratio']) ?
      $aggregate_settings['variables']['advagg_js_compress_max_ratio'] :
      variable_get('advagg_js_compress_max_ratio', ADVAGG_JS_COMPRESS_MAX_RATIO);
    $aggregate_settings['variables']['advagg_js_compress_ratio']
      = isset($aggregate_settings['variables']['advagg_js_compress_ratio']) ?
      $aggregate_settings['variables']['advagg_js_compress_ratio'] :
      variable_get('advagg_js_compress_ratio', ADVAGG_JS_COMPRESS_RATIO);
    $add_license_setting
      = isset($aggregate_settings['variables']['advagg_js_compress_add_license']) ?
      $aggregate_settings['variables']['advagg_js_compress_add_license'] :
      variable_get('advagg_js_compress_add_license', ADVAGG_JS_COMPRESS_ADD_LICENSE);
    // Make sure the returned string is not empty or has a VERY high
    // compression ratio.
    if (empty($contents)
      || empty($ratio)
      || $ratio < $aggregate_settings['variables']['advagg_js_compress_ratio']
      || $ratio > $aggregate_settings['variables']['advagg_js_compress_max_ratio']
    ) {
      $contents = $contents_before;
    }
    elseif ($add_licensing && ($add_license_setting == 1 || $add_license_setting == 3)) {
      $url = file_create_url($filename);
      $contents = "/* Source and licensing information for the line(s) below can be found at $url. */\n" . $contents . ";\n/* Source and licensing information for the above line(s) can be found at $url. */\n";
    }
  }

  // Reset if cache settings are set to Development.
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0 && !$force_run) {
    $contents = $contents_before;
  }
  return $no_errors;
}

/**
 * Checks if string contains multibyte characters.
 *
 * @param string $string
 *   String to check.
 *
 * @return bool
 *   TRUE if string contains multibyte character.
 */
function advagg_js_compress_string_contains_multibyte_characters($string) {
  // Check if there are multy-byte characters: If the UTF-8 encoded string has
  // multybytes strlen() will return a byte-count greater than the actual
  // character count, returned by drupal_strlen().
  if (strlen($string) == drupal_strlen($string)) {
    return FALSE;
  }

  return TRUE;
}

/**
 * Compress a JS string using jsmin+.
 *
 * @param string $contents
 *   Javascript string.
 * @param bool $log_errors
 *   FALSE to disable logging to watchdog on failure.
 */
function advagg_js_compress_jsminplus(&$contents, $log_errors = TRUE) {
  $no_errors = TRUE;
  $contents_before = $contents;
  $old_error = error_get_last();

  // Set max nesting level.
  if (!class_exists('JSMinPlus')) {
    $nesting_level = ini_get('xdebug.max_nesting_level');
    if (!empty($nesting_level) && $nesting_level < 200) {
      ini_set('xdebug.max_nesting_level', 200);
    }
  }

  // Try libraries for jsminplus.
  if (is_callable('libraries_load')) {
    libraries_load('jsminplus');
  }
  // Only include jsminplus.inc if the JSMinPlus class doesn't exist.
  if (!class_exists('JSMinPlus')) {
    include drupal_get_path('module', 'advagg_js_compress') . '/jsminplus.inc';
  }

  ob_start();
  try {
    // JSMin+ the contents of the aggregated file.
    $contents = @JSMinPlus::minify($contents);

    // Capture any output from JSMinPlus.
    $error = trim(ob_get_contents());
    if (!empty($error)) {
      $no_errors = FALSE;
      throw new Exception($error);
    }
    $recent_error = error_get_last();
    if (!empty($recent_error) && serialize($recent_error) !== serialize($old_error)) {
      $no_errors = FALSE;
      $error = print_r($recent_error, TRUE);
      throw new Exception($error);
    }
  }
  catch (Exception $e) {
    $no_errors = FALSE;
    // Log the exception thrown by JSMin+ and roll back to uncompressed content.
    if ($log_errors) {
      watchdog('advagg_js_compress', '@message <pre> @contents </pre>', array(
        '@message' => $e->getMessage(),
        '@contents' => $contents_before,
      ), WATCHDOG_WARNING);
    }
    $contents = $contents_before;
  }
  ob_end_clean();
  return $no_errors;
}

/**
 * Compress a JS string using packer.
 *
 * @param string $contents
 *   Javascript string.
 * @param bool $log_errors
 *   FALSE to disable logging to watchdog on failure.
 */
function advagg_js_compress_jspacker(&$contents, $log_errors = TRUE) {
  $no_errors = TRUE;
  $contents_before = $contents;

  // Try libraries for jspacker.
  if (is_callable('libraries_load')) {
    libraries_load('jspacker');
  }
  if (!class_exists('JavaScriptPacker')) {
    include drupal_get_path('module', 'advagg_js_compress') . '/jspacker.inc';
  }

  // Add semicolons to the end of lines if missing.
  $contents = str_replace("}\n", "};\n", $contents);
  $contents = str_replace("\nfunction", ";\nfunction", $contents);

  // Use Packer on the contents of the aggregated file.
  try {
    $packer = new JavaScriptPacker($contents, 62, TRUE, FALSE);
    $contents = $packer->pack();
  }
  catch (Exception $e) {
    $no_errors = FALSE;
    // Log the exception thrown by JSMin+ and roll back to uncompressed content.
    if ($log_errors) {
      watchdog('advagg_js_compress', '@message <pre> @contents </pre>', array(
        '@message' => $e->getMessage(),
        '@contents' => $contents_before,
      ), WATCHDOG_WARNING);
    }
    $contents = $contents_before;
  }
  return $no_errors;
}

/**
 * Compress a JS string using jsmin.
 *
 * @param string $contents
 *   Javascript string.
 * @param bool $log_errors
 *   FALSE to disable logging to watchdog on failure.
 */
function advagg_js_compress_jsmin(&$contents, $log_errors = TRUE) {
  $no_errors = TRUE;
  $contents_before = $contents;

  try {
    $contents = jsmin($contents);
  }
  catch (Exception $e) {
    $no_errors = FALSE;
    // Log the exception thrown by JSMin+ and roll back to uncompressed content.
    if ($log_errors) {
      watchdog('advagg_js_compress', '@message <pre> @contents </pre>', array(
        '@message' => $e->getMessage(),
        '@contents' => $contents_before,
      ), WATCHDOG_WARNING);
    }
    $contents = $contents_before;
  }
  return $no_errors;
}

/**
 * Test a JS file to see if it compresses well.
 *
 * @param string $filename
 *   Path and filename of JS file.
 * @param array $info
 *   (Optional) advagg_get_info_on_file().
 * @param array $compressors
 *   (Optional) List of compressors to test.
 *
 * @return array
 *   info about the file.
 */
function advagg_js_compress_run_test($filename, array $info = array(), array $compressors = array()) {
  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');
  if (empty($info)) {
    $info = advagg_get_info_on_file($filename, FALSE, FALSE);
  }
  $cache_id = 'advagg:js_compress:info:' . $info['filename_hash'];
  $cache_id .= !empty($info['content_hash']) ? ':' . $info['content_hash'] : '';

  $compressor_list = advagg_js_compress_get_enabled_compressors(array(), -1);
  // Build list of compressors.
  if (empty($compressors)) {
    $compressors = $compressor_list;
  }

  // Set to 0 if file doesn't exist.
  if (empty($info['content_hash'])) {
    foreach ($compressor_list as $key => $name) {
      $results[$key] = array('code' => 0, 'ratio' => 0, 'name' => $name);
    }
  }
  else {
    // Set to "-1" so if php bombs, the file will be marked as bad.
    foreach ($compressor_list as $key => $name) {
      $results[$key] = array('code' => -1, 'ratio' => 0, 'name' => $name);
    }
    $run_locally = TRUE;
    // Run this via httprl if possible.
    if (module_exists('httprl') && httprl_is_background_callback_capable()) {
      $run_locally = FALSE;
      // Setup callback options array.
      $callback_options = array(
        array(
          'function' => 'advagg_js_compress_test_file',
          'return' => &$results,
        ),
        $filename, $compressors, $cache_id,
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
            $filename, array($key => $value['name']), $cache_id,
          );
          // Queue up the request.
          httprl_queue_background_callback($callback_options);
          // Execute request.
          httprl_send_request();

          $results[$key] = $sub_result[$key];
        }
      }

      // Try locally if all return back -1 (something wrong with httprl).
      foreach ($results as $key => $value) {
        if ($value['code'] != -1) {
          $run_locally = TRUE;
          break;
        }
      }
    }
    if ($run_locally) {
      // Save results, so if PHP bombs, this file is marked as bad.
      // CACHE_PERMANENT isn't good here. Use 2 weeks from now + 0-45 days.
      // The random 0 to 45 day addition is to prevent a cache stampeed.
      cache_set($cache_id, $results, 'cache_advagg_info', round(REQUEST_TIME + 1209600 + mt_rand(0, 3888000), -3));

      // Test the file.
      $results = advagg_js_compress_test_file($filename, $compressors, $cache_id);
    }
  }

  // Save and return results.
  // Save results, so if PHP bombs, this file is marked as bad.
  // CACHE_PERMANENT isn't good here. Use 2 weeks from now + 0-45 days.
  // The random 0 to 45 day addition is to prevent a cache stampeed.
  cache_set($cache_id, $results, 'cache_advagg_info', round(REQUEST_TIME + 1209600 + mt_rand(0, 3888000), -3));
  return $results;
}

/**
 * Test a JS file to see if it compresses well.
 *
 * @param array $filenames_info
 *   Array of filenames and info from advagg_get_info_on_file().
 * @param array $compressors
 *   (Optional) List of compressors to test.
 *
 * @return array
 *   Info about the file.
 */
function advagg_js_compress_run_mutiple_tests(array $filenames_info, array $compressors = array()) {
  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');

  $compressor_list = advagg_js_compress_get_enabled_compressors(array(), -1);
  // Build list of compressors.
  if (empty($compressors)) {
    $compressors = $compressor_list;
  }

  // Prevent PHP from running out of time if working with a lot of files.
  if (count($filenames_info) > 5) {
    // Set to max time if running from the command line.
    if (drupal_is_cli()) {
      drupal_set_time_limit(0);
    }
    else {
      $max_execution_time = ini_get('max_execution_time');
      if ($max_execution_time != 0) {
        $current_time = 5;
        if (is_callable('getrusage')) {
          $dat = getrusage();
          $current_time = $dat["ru_utime.tv_sec"];
        }
        $max_time = max(30, ini_get('max_execution_time'));
        $time_left = $max_time - $current_time;
        // Give every file 3 seconds.
        drupal_set_time_limit(count($filenames_info) * 3 + $time_left);
      }
    }
  }

  $return = array();
  foreach ($filenames_info as $filename => $info) {
    if (!module_exists('httprl') || !httprl_is_background_callback_capable()) {
      $return[$filename] = advagg_js_compress_run_test($filename, $info, $compressors);
      continue;
    }

    // Setup this run.
    $results = array();
    if (empty($info)) {
      $info = advagg_get_info_on_file($filename, FALSE, FALSE);
    }

    // Set to 0 if file doesn't exist.
    if (empty($info['content_hash'])) {
      foreach ($compressor_list as $key => $name) {
        $results[$key] = array('code' => 0, 'ratio' => 0, 'name' => $name);
      }
      $return[$filename] = $results;
      continue;
    }

    $results = &$return[$filename];
    // Set to "-1" so if php bombs, the file will be marked as bad.
    foreach ($compressor_list as $key => $name) {
      $results[$key] = array('code' => -1, 'ratio' => 0, 'name' => $name);
    }
    // Get cache id.
    $cache_id = 'advagg:js_compress:info:' . $info['filename_hash'];
    $cache_id .= !empty($info['content_hash']) ? ':' . $info['content_hash'] : '';

    // Setup callback options array.
    $callback_options = array(
      array(
        'function' => 'advagg_js_compress_test_file',
        'return' => &$results,
      ),
      $filename, $compressors, $cache_id,
    );
    // Queue up the request.
    httprl_queue_background_callback($callback_options);
  }

  if (module_exists('httprl') && httprl_is_background_callback_capable()) {
    // Execute request.
    httprl_send_request();

    foreach ($return as $filename => &$results) {
      if (!empty($results)) {
        // If we have one bad set, we need to retest all.
        foreach ($results as $key => $value) {
          if ($value['code'] == -1) {
            unset($results);
            $results = array();
            break;
          }
        }
      }

      // If php bombs out, try each compressor individually.
      if (empty($results)) {
        foreach ($compressor_list as $key => $name) {
          $info = $filenames_info[$filename];
          $cache_id = 'advagg:js_compress:info:' . $info['filename_hash'];
          $cache_id .= !empty($info['content_hash']) ? ':' . $info['content_hash'] : '';

          $sub_result = array();
          $sub_result[$key] = '';
          // Setup callback options array.
          $callback_options = array(
            array(
              'function' => 'advagg_js_compress_test_file',
              'return' => &$sub_result,
            ),
            $filename, array($key => $name), $cache_id,
          );
          // Queue up the request.
          httprl_queue_background_callback($callback_options);
          // Execute request.
          httprl_send_request();

          if (!empty($sub_result[$key])) {
            $results[$key] = $sub_result[$key];
          }
          else {
            // Set to "-1" as php bombed, the file will be marked as bad.
            $results[$key] = array('code' => -1, 'ratio' => 0, 'name' => $name);
          }
        }
      }
    }
    unset($results);
  }

  return $return;
}
