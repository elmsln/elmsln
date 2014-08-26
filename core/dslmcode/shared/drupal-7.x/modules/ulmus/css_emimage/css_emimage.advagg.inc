<?php

/**
 * @file
 * CSS Embedded Images module.
 */

// AdvAgg Hooks.
/**
 * Implement hook_advagg_get_css_aggregate_contents_alter().
 */
function css_emimage_advagg_get_css_aggregate_contents_alter(&$data, $files, $aggregate_settings) {
  if (empty($aggregate_settings['variables']['css_emimage_mode']) || $aggregate_settings['variables']['css_emimage_mode'] == 'orginal') {
    return;
  }
  if ($aggregate_settings['variables']['css_emimage_mode'] != 'base' && $aggregate_settings['variables']['css_emimage_mode'] != 'emimage') {
    return;
  }

  $key = drupal_hash_base64(implode('', array_keys($files)));

  _css_emimage_text_processor($data, $key, $aggregate_settings['variables']['css_emimage_mode']);

  // Make sure data sent back is not empty.
  // Workaround needed so we don't write a blank file.
  // 99% of the time this isn't needed.
  if (empty($data)) {
    $data = 'html {display:block;}';
  }
}

/**
 * Implements hook_advagg_build_aggregate_plans_alter().
 */
function css_emimage_advagg_build_aggregate_plans_alter(&$files, &$modified, $type) {
  if ($type != 'css') {
    return;
  }
  if (!variable_get('css_emimage_files', CSS_EMIMAGE_FILES)) {
    return;
  }

  // Save all 3 operating modes into hooks hash.
  $modes = array('base' => '', 'emimage' => '', 'orginal' => '');
  foreach ($modes as $mode => &$value) {
    $GLOBALS['conf']['css_emimage_mode'] = $mode;
    drupal_static_reset('advagg_get_current_hooks_hash');
    drupal_static_reset('advagg_current_hooks_hash_array');
    $value = advagg_get_current_hooks_hash();
  }
  $filename_hashes = &drupal_static('advagg_get_info_on_file');

  $new_files = array();
  foreach ($files as $filename => $data) {
    $total_base64_size = 0;
    foreach ($data['files'] as $fileinfo) {
      // Only run if css is not browser specific.
      if (!empty($fileinfo['browsers']) && ($fileinfo['browsers']['!IE'] !== TRUE || $fileinfo['browsers']['IE'] !== TRUE)) {
        continue;
      }
      if (!isset($fileinfo['css_emimage']) || !is_array($fileinfo['css_emimage'])) {
        css_emimage_advagg_scan_for_changes($fileinfo['data'], TRUE);
        // Cache info.
        $cache_id = 'advagg:file:' . $fileinfo['filename_hash'];
        $fileinfo = isset($filename_hashes[$cache_id]) ? $filename_hashes[$cache_id] : NULL;
      }
      // Skip if no css images are in here.
      if (empty($fileinfo['css_emimage'])) {
        continue;
      }

      foreach ($fileinfo['css_emimage'] as $image_name => $image_info) {
        $total_base64_size += $image_info['base64_size'];
      }
    }
    // No css images; skip.
    if (empty($total_base64_size)) {
      $new_files[$filename] = $data;
      continue;
    }
    // Create new files to handle the extra data.

    // Add in the base file.
    if ($total_base64_size > variable_get('css_emimage_inline_datauri_limit', CSS_EMIMAGE_INLINE_DATAURI_LIMIT)) {
      $base_filename = css_emimage_replace_filename($filename, $modes['base']);
      $new_files[$base_filename] = $data;
      foreach ($new_files[$base_filename]['files'] as $key => $fileinfo) {
        $new_files[$base_filename]['files'][$key]['browsers'] = array('IE' => 'gte IE 8');
      }
    }

    // Add in the css embedded file.
    $emimage_filename = css_emimage_replace_filename($filename, $modes['emimage']);
    $new_files[$emimage_filename] = $data;
    foreach ($new_files[$emimage_filename]['files'] as $key => $fileinfo) {
      $new_files[$emimage_filename]['files'][$key]['browsers'] = array('IE' => 'gte IE 8');
    }

    // Add in the IE fallback file (orginal file).
    $new_files[$filename] = $data;
    foreach ($new_files[$filename]['files'] as $key => $fileinfo) {
      $new_files[$filename]['files'][$key]['browsers'] = array('!IE' => FALSE, 'IE' => 'lte IE 7');
    }
  }
  $files = $new_files;
}

/**
 * Implements hook_advagg_changed_files().
 */
function css_emimage_advagg_changed_files($files, $types) {
  // Only care about css files.
  if (empty($types['css'])) {
    return;
  }
  $return = array();
  foreach ($files as $filename => $meta_data) {
    // Only care about js files.
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    if ($ext != 'css') {
      continue;
    }

    $return[$filename] = css_emimage_advagg_scan_for_changes($filename, TRUE);
  }
  return $return;
}

/**
 * Implements hook_advagg_scan_for_changes().
 */
function css_emimage_advagg_scan_for_changes($filename, $save_changes = FALSE) {
  $ext = pathinfo($filename, PATHINFO_EXTENSION);
  if ($ext != 'css') {
    return FALSE;
  }

  // Get the info on this file.
  module_load_include('inc', 'advagg', 'advagg');
  $info = advagg_get_info_on_file($filename);

  // Cache info.
  $filename_hashes = &drupal_static('advagg_get_info_on_file');
  $cache_id = 'advagg:file:' . $info['filename_hash'];
  $hash_id = 'css_emimage:' . $info['filename_hash'];
  $cache_is_empty = FALSE;
  if (!isset($info['css_emimage'])) {
    $info['css_emimage'] = advagg_get_hash_settings($hash_id);
    $cache_is_empty = TRUE;
  }

  // Load file.
  $optimize = TRUE;
  $contents = advagg_load_css_stylesheet($filename, $optimize);

  // Check if this file links to any images.
  $images = css_emimage_string_contains_images($contents);

  // If no images bail out here.
  if (empty($images)) {
    if (empty($info['css_emimage'])) {
      // File never had any images.
      if (!isset($info['css_emimage'])) {
        // Save results.
        if ($save_changes) {
          $info['css_emimage'] = array();
          $filename_hashes[$cache_id] = $info;
          cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);
          advagg_set_hash_settings($hash_id, $info['css_emimage']);
        }
      }
      return FALSE;
    }
    else {
      // File used to have images, but no longer does.
      // Save results.
      if ($save_changes) {
        $info['css_emimage'] = array();
        $filename_hashes[$cache_id] = $info;
        cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);
        advagg_set_hash_settings($hash_id, $info['css_emimage']);
      }
      return TRUE;
    }
  }

  // See if any of the images has changed.
  $changed = FALSE;
  foreach ($images as $image_filename) {
    if (empty($image_filename)) {
      continue;
    }
    // Strip base path from filename.
    $image_filename = preg_replace('/^' . preg_quote($GLOBALS['base_path'], '/') . '/i', '', $image_filename);
    if (file_exists($image_filename) == FALSE) {
      continue;
    }

    $image_hash = drupal_hash_base64(file_get_contents($image_filename));

    if (empty($info['css_emimage'][$image_filename]) || $info['css_emimage'][$image_filename]['hash'] != $image_hash) {
      // Save results.
      if ($save_changes) {
        $info['css_emimage'][$image_filename] = array(
          'hash' => $image_hash,
          'filesize' => filesize($image_filename),
          'base64_size' => strlen(base64_encode(file_get_contents($image_filename))),
        );
        $filename_hashes[$cache_id] = $info;
        cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);
        advagg_set_hash_settings($hash_id, $info['css_emimage']);
      }
      $changed = TRUE;
    }
    elseif ($save_changes) {
      // Still put info into static cache.
      $filename_hashes[$cache_id] = $info;
      if ($cache_is_empty) {
        cache_set($cache_id, $info, 'cache_advagg_info', CACHE_PERMANENT);
      }
    }
  }
  return $changed;
}

// Helper functions.
/**
 * Given a filename, replace the 3rd hash with the given hash.
 *
 * @param $filename
 *   Filename.
 * @param $hash
 *   Hash.
 * @return
 *   New filename.
 */
function css_emimage_replace_filename($filename, $hash) {
  module_load_include('inc', 'advagg', 'advagg.missing');
  list($type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings) = advagg_get_hashes_from_filename($filename);
  return advagg_build_filename($type, $aggregate_filenames_hash, $aggregate_contents_hash, $hash);
}

/**
 * Given a CSS string, return an array of images referenced inside of it.
 *
 * @param $contents
 *   CSS String.
 * @return
 *   Array of images, or empty array if none found.
 */
function css_emimage_string_contains_images($contents) {
  // See if CSS file contains an image.
  $images = array();
  $pattern = '/(background(?:-image)?|list-style(?:-image)?):[^{};)]*?((?:none|url\([\'"]?(.+?)[\'"]?\)))([^{};]*)/i';
  if (preg_match_all($pattern, $contents, $matches) > 0) {
    $images = array_filter($matches[3]);
  }
  return $images;
}

// Processing function.
/**
 * Process the css text and replace it with image data where necessary.
 *
 * @param $data
 *    CSS text data to process over.
 * @param $key
 *    Used for a static cache.
 * @param $type
 *    The type of css wanted back, base or emimage.
 */
function _css_emimage_text_processor(&$data, $key, $type) {
  static $values = array();

  // This only processes base & emimage types.
  if ($type != 'base' && $type != 'emimage') {
    return;
  }

  module_load_include('inc', 'css_emimage', 'css_emimage');

  if (empty($values[$key][$type])) {
    // Do magic; code could be improved.
    _css_emimage_collect_static(array(array(), array())); // Reset the processed declarations.
    $contents = $data;
    $datauri_css = '';

    $pattern = '/([^{}]+){([^{}]*?(background(?:-image)?|list-style(?:-image)?):[^{};)]*?(?:none|url\([\'"]?.+?[\'"]?\))[^{}]*)}/i';
    $contents = preg_replace_callback($pattern, '_css_emimage_replace', $contents);
    $media_blocks = parse_media_blocks($contents);

    if (!is_null($contents)) {
      list($declarations, $file_stats) = _css_emimage_collect_static();

      // Check for duplicate images and exclude those exceeding our duplication limit.
      // Sum the amount of data being embedded.
      $datauri_total_length = 0;
      foreach ($file_stats as $fs) {
        if (count($fs['indices']) > 1 && $fs['total_length'] > variable_get('css_emimage_duplicate_embed_limit', CSS_EMIMAGE_DUPLICATE_EMBED_LIMIT)) {
          foreach ($fs['indices'] as $fsi) {
            $declarations[$fsi]['base64'] = '';
          }
        }
        else {
          $datauri_total_length += $fs['total_length'];
        }
      }

      // Handle media queries.
      if (!empty($media_blocks)) {
        foreach ($declarations as $a => $b) {
          foreach ($media_blocks as $c) {
            // Skip if token is not in the media block.
            if (strpos($c, $b['token']) === FALSE) {
              continue;
            }
            $declarations[$a]['media_query'] = substr($c, 0, strpos($c, '{'));
            break;
          }
        }
      }

      list($ext_contents, $ext_data) = _css_emimage_build_external($contents, $declarations);

      // If the amount of data being embedded is within the inline limit, inline the data URIs;
      // otherwise, store the data URIs in a separate CSS file.
      if (variable_get('css_emimage_force_inline', 0) || ($datauri_total_length && $datauri_total_length <= variable_get('css_emimage_inline_datauri_limit', CSS_EMIMAGE_INLINE_DATAURI_LIMIT))) {
        $inline = _css_emimage_build_inline($contents, $declarations);
        if (strlen($inline) < (strlen($ext_contents) + strlen($ext_data))) {
          $datauri_css = $inline;
        }
        else {
          $datauri_css = "$ext_contents\n$ext_data";
        }
        $contents = '';
      }
      else {
        $contents = $ext_contents;
        $datauri_css = $ext_data;
      }
    }
    else {
      $error_code = preg_last_error();
      $error_messages = array(PREG_NO_ERROR => 'NO_ERROR', PREG_INTERNAL_ERROR => 'INTERNAL_ERROR', PREG_BACKTRACK_LIMIT_ERROR => 'BACKTRACK_LIMIT_ERROR', PREG_RECURSION_LIMIT_ERROR => 'RECURSION_LIMIT_ERROR', PREG_BAD_UTF8_ERROR => 'BAD_UTF8_ERROR', PREG_BAD_UTF8_OFFSET_ERROR => 'BAD_UTF8_OFFSET_ERROR');
      watchdog('css_emimage', 'Error while trying to embed images in your CSS, falling back to unmodified CSS. PCRE error was: !error.',
        array('!error' => array_key_exists($error_code, $error_messages) ? $error_messages[$error_code] : $error_code), WATCHDOG_ERROR);
      return;
    }
    $values[$key]['base'] = $contents;
    $values[$key]['emimage'] = $datauri_css;
  }

  // Send data back.
  $data = $values[$key][$type];
  // Free memory, values only gets used once.
  unset($values[$key][$type]);
}
