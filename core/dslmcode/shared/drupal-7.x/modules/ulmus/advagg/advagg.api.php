<?php

/**
 * @file
 * Hooks provided by the AdvAgg module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Allow modules to modify the aggregate plan.
 *
 * @param array $files
 *   An associative array.
 *    filename - data
 * @param bool $modified
 *   Set this to TRUE if the $files structure has been changed.
 * @param string $type
 *   css or js.
 *
 * @see advagg_build_aggregate_plans()
 * @see advagg_advagg_build_aggregate_plans_alter()
 */
function hook_advagg_build_aggregate_plans_alter(&$files, &$modified, $type) {
  // Do nothing if core grouping is disabled.
  if (!variable_get('advagg_core_groups', ADVAGG_CORE_GROUPS)) {
    return;
  }

  $temp_new_files = array();
  $counter = 0;
  foreach ($files as $filename => $data) {
    $group = NULL;
    $every_page = NULL;
    foreach ($data['files'] as $fileinfo) {
      // Grouped by group & every_page variables.
      if (is_null($group)) {
        $group = $fileinfo['group'];
      }
      if (is_null($every_page)) {
        $every_page = $fileinfo['every_page'];
      }

      // Bump Counter if group/every_page has changed from the last one.
      if ($group != $fileinfo['group'] || $every_page != $fileinfo['every_page']) {
        ++$counter;
        $group = $fileinfo['group'];
        $every_page = $fileinfo['every_page'];
        $modified = TRUE;
      }
      $temp_new_files[$counter][] = $fileinfo;
    }
    ++$counter;
  }

  // Replace $files array with new aggregate filenames.
  $files = advagg_generate_filenames(array($temp_new_files), $type);
}

/**
 * Let other modules know about the changed files.
 *
 * @param array $files
 *   An associative array.
 *    filename - meta_data
 * @param array $types
 *   Array containing css and/or js.
 *
 * @return array
 *   Not used currently.
 *
 * @see advagg_push_new_changes()
 * @see advagg_js_compress_advagg_changed_files()
 */
function hook_advagg_changed_files($files, $types) {
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
 * Allow other modules to add in their own settings and hooks.
 *
 * @param array $aggregate_settings
 *   An associative array of hooks and settings used.
 *
 * @see advagg_current_hooks_hash_array()
 * @see advagg_js_compress_advagg_current_hooks_hash_array_alter()
 */
function hook_advagg_current_hooks_hash_array_alter(&$aggregate_settings) {
  $aggregate_settings['variables']['advagg_js_compressor'] = variable_get('advagg_js_compressor', ADVAGG_JS_COMPRESSOR);
  $aggregate_settings['variables']['advagg_js_compress_packer'] = variable_get('advagg_js_compress_packer', ADVAGG_JS_COMPRESS_PACKER);
  $aggregate_settings['variables']['advagg_js_max_compress_ratio'] = variable_get('advagg_js_max_compress_ratio', ADVAGG_JS_MAX_COMPRESS_RATIO);
}

/**
 * Allow other modules to alter the contents and add new files to save (.gz).
 *
 * @param array $files_to_save
 *   array($uri => $contents)
 * @param array $aggregate_settings
 *   array of settings.
 * @param array $other_parameters
 *   array of containing $files & $type.
 *
 * @see advagg_save_aggregate()
 * @see advagg_advagg_save_aggregate_alter()
 */
function hook_advagg_save_aggregate_alter(&$files_to_save, $aggregate_settings, $other_parameters) {
  // Return if gzip is disabled.
  if (empty($aggregate_settings['variables']['advagg_gzip'])) {
    return;
  }

  // See if a .gz file already exists.
  $gzip_exists = FALSE;
  foreach ($files_to_save as $uri => $contents) {
    // See if this uri contains .gz near the end of it.
    $pos = strripos($uri, '.gz', 91 + strlen(ADVAGG_SPACE) * 3);
    if (!empty($pos)) {
      $len = strlen($uri);
      // .gz file exists, exit loop.
      if ($pos == $len - 3) {
        $gzip_exists = TRUE;
        break;
      }
    }
  }

  // If a .gz file does not exist, create one.
  if (!$gzip_exists) {
    // Use the first file in the array.
    $data = reset($files_to_save);
    $uri = key($files_to_save);
    // Compress it and add it to the $files_to_save array.
    $compressed = gzencode($data, 9, FORCE_GZIP);
    $files_to_save[$uri . '.gz'] = $compressed;
  }
}

/**
 * Allow other modules to alter css and js paths.
 *
 * @param array $css_paths
 *   Array containing the local path and url path.
 * @param array $js_paths
 *   Array containing the local path and url path.
 *
 * @see advagg_get_root_files_dir()
 * @see advagg_mod_advagg_get_root_files_dir_alter()
 */
function hook_advagg_get_root_files_dir(&$css_paths, &$js_paths) {
  $dir = rtrim(variable_get('advagg_mod_unified_multisite_dir', ''), '/');
  if (empty($dir) || !file_exists($dir) || !is_dir($dir)) {
    return;
  }
  // Change directory.
  $css_paths[0] = $dir . '/advagg_css';
  $js_paths[0] = $dir . '/advagg_js';

  file_prepare_directory($css_paths[0], FILE_CREATE_DIRECTORY);
  file_prepare_directory($js_paths[0], FILE_CREATE_DIRECTORY);

  // Set the URI of the directory.
  $css_paths[1] = parse_url(file_create_url($css_paths[0]), PHP_URL_PATH);
  if (substr($css_paths[1], 0, strlen($GLOBALS['base_path'])) == $GLOBALS['base_path']) {
    $css_paths[1] = substr($css_paths[1], strlen($GLOBALS['base_path']));
  }
  $js_paths[1] = parse_url(file_create_url($js_paths[0]), PHP_URL_PATH);
  if (substr($js_paths[1], 0, strlen($GLOBALS['base_path'])) == $GLOBALS['base_path']) {
    $js_paths[1] = substr($js_paths[1], strlen($GLOBALS['base_path']));
  }
}

/**
 * Allow other modules to modify this aggregates contents.
 *
 * @param string $data
 *   Raw CSS data.
 * @param array $files
 *   List of files used to create this aggregate.
 * @param array $aggregate_settings
 *   An associative array of hooks and settings used.
 *
 * @see advagg_get_css_aggregate_contents()
 * @see advagg_css_compress_advagg_get_css_aggregate_contents_alter()
 */
function hook_advagg_get_css_aggregate_contents_alter(&$data, $files, $aggregate_settings) {
  if (empty($aggregate_settings['variables']['advagg_css_compressor'])) {
    return;
  }

  if ($aggregate_settings['variables']['advagg_css_compressor'] == 2) {
    advagg_css_compress_yui_cssmin($data);
  }
}

/**
 * Allow other modules to modify this aggregates contents.
 *
 * @param string $data
 *   Raw JS data.
 * @param array $files
 *   List of files used to create this aggregate.
 * @param array $aggregate_settings
 *   An associative array of hooks and settings used.
 *
 * @see advagg_get_css_aggregate_contents()
 * @see advagg_css_compress_advagg_get_css_aggregate_contents_alter()
 */
function hook_advagg_get_js_aggregate_contents_alter(&$data, $files, $aggregate_settings) {
  // Do nothing if js file compression is disabled.
  if (empty($aggregate_settings['variables']['advagg_js_compressor'])) {
    return;
  }

  // Compress it.
  $filename = drupal_hash_base64(serialize($files));
  advagg_js_compress_prep($data, $filename, $aggregate_settings, FALSE);
}

/**
 * Allow other modules to modify this files contents.
 *
 * @param string $contents
 *   Raw file data.
 * @param string $file
 *   Filename
 * @param array $aggregate_settings
 *   An associative array of hooks and settings used.
 *
 * @see advagg_get_css_aggregate_contents()
 * @see advagg_css_compress_advagg_get_css_aggregate_contents_alter()
 */
function hook_advagg_get_css_file_contents_alter(&$contents, $file, $aggregate_settings) {
  if (empty($aggregate_settings['variables']['advagg_css_compressor'])) {
    return;
  }

  if ($aggregate_settings['variables']['advagg_css_compressor'] == 2) {
    advagg_css_compress_yui_cssmin($contents);
  }
}

/**
 * Allow other modules to modify this files contents.
 *
 * @param string $contents
 *   Raw file data.
 * @param string $file
 *   Filename
 * @param array $aggregate_settings
 *   An associative array of hooks and settings used.
 *
 * @see advagg_get_css_aggregate_contents()
 * @see advagg_css_compress_advagg_get_css_aggregate_contents_alter()
 */
function hook_advagg_get_js_file_contents_alter(&$contents, $file, $aggregate_settings) {
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
    $info = advagg_js_compress_run_test($filename);
  }

  // Compress it if it passes the test.
  if (!empty($info['advagg_js_compress'][$compressor]['code']) && $info['advagg_js_compress'][$compressor]['code'] == 1) {
    advagg_js_compress_prep($contents, $filename, $aggregate_settings);
  }
}

/**
 * Allow other modules to modify $css_groups right before it is processed.
 *
 * @param array $css_groups
 *   An associative array.
 *    key - group
 * @param bool $preprocess_css
 *   TRUE if preprocessing is enabled.
 *
 * @see _advagg_aggregate_css()
 * @see advagg_css_cdn_advagg_css_groups_alter()
 */
function hook_advagg_css_groups_alter(&$css_groups, $preprocess_css) {
  // Work around a bug with seven_css_alter.
  // http://drupal.org/node/1937860
  $theme_keys[] = $GLOBALS['theme'];
  if (!empty($GLOBALS['base_theme_info'])) {
    foreach ($GLOBALS['base_theme_info'] as $base) {
      $theme_keys[] = $base->name;
    }
  }
  $match = FALSE;
  foreach ($theme_keys as $name) {
    if ($name == 'seven') {
      $match = TRUE;
    }
  }
  if (empty($match)) {
    return;
  }

  $target = FALSE;
  $last_group = FALSE;
  $last_key = FALSE;
  $kill_key = FALSE;
  $replaced = FALSE;
  foreach ($css_groups as $key => $group) {
    if (empty($target)) {
      if ($group['type'] == 'external' && $group['preprocess'] && $preprocess_css) {
        foreach ($group['items'] as $k => $value) {
          if ($value['data'] == 'themes/seven/jquery.ui.theme.css') {
            // Type should be file and not external (core bug).
            $value['type'] = 'file';
            $target = $value;
            unset($css_groups[$key]['items'][$k]);
            if (empty($css_groups[$key]['items'])) {
              unset($css_groups[$key]);
              $kill_key = $key;
            }
          }
        }
      }
    }
    else {
      $diff = array_merge(array_diff_assoc($group['browsers'], $target['browsers']), array_diff_assoc($target['browsers'], $group['browsers']));
      // @ignore sniffer_whitespace_openbracketspacing_openingwhitespace
      if (   $group['type'] != $target['type']
          || $group['group'] != $target['group']
          || $group['every_page'] != $target['every_page']
          || $group['media'] != $target['media']
          || $group['media'] != $target['media']
          || $group['preprocess'] != $target['preprocess']
          || !empty($diff)
          ) {
        if (!empty($last_group)) {
          $diff = array_merge(array_diff_assoc($last_group['browsers'], $target['browsers']), array_diff_assoc($target['browsers'], $last_group['browsers']));
          // @ignore sniffer_whitespace_openbracketspacing_openingwhitespace
          if (   $last_group['type'] != $target['type']
              || $last_group['group'] != $target['group']
              || $last_group['every_page'] != $target['every_page']
              || $last_group['media'] != $target['media']
              || $last_group['media'] != $target['media']
              || $last_group['preprocess'] != $target['preprocess']
              || !empty($diff)
              ) {
            // Insert New.
            $css_groups[$kill_key] = array(
              'group' => $target['group'],
              'type' => $target['type'],
              'every_page' => $target['every_page'],
              'media' => $target['media'],
              'preprocess' => $target['preprocess'],
              'browsers' => $target['browsers'],
              'items' => array($target),
            );
            $replaced = TRUE;
          }
          else {
            // Insert above.
            $css_groups[$last_key]['items'][] = $target;
            $replaced = TRUE;
          }
        }
      }
      else {
        // Insert below.
        array_unshift($css_groups[$key]['items'], $target);
        $replaced = TRUE;
      }
    }
    $last_group = $group;
    $last_key = $key;
    if ($replaced) {
      break;
    }
  }
  ksort($css_groups);
}

/**
 * Allow other modules to modify $js_groups right before it is processed.
 *
 * @param array $js_groups
 *   An associative array.
 *    key - group
 * @param bool $preprocess_js
 *   TRUE if preprocessing is enabled.
 *
 * @see _advagg_aggregate_js()
 * @see labjs_advagg_js_groups_alter()
 */
function hook_advagg_js_groups_alter(&$js_groups, $preprocess_js) {
  if (!$preprocess_js) {
    return;
  }
  $labjs_location = labjs_get_path();

  foreach ($js_groups as &$data) {
    foreach ($data['items'] as &$values) {
      if ($values['data'] == $labjs_location) {
        // Strictly enforce preprocess = FALSE for labjs.
        $values['preprocess'] = FALSE;
        $data['preprocess'] = FALSE;
        break 2;
      }
    }
  }
}

/**
 * Allow other modules to modify $children & $elements before they are rendered.
 *
 * @param array $children
 *   An array of children elements.
 * @param array $elements
 *   A render array containing:
 *   - #items: The CSS items as returned by drupal_add_css() and
 *     altered by drupal_get_css().
 *   - #group_callback: A function to call to group #items. Following
 *     this function, #aggregate_callback is called to aggregate items within
 *     the same group into a single file.
 *   - #aggregate_callback: A function to call to aggregate the items within
 *     the groups arranged by the #group_callback function.
 *
 * @see advagg_modify_css_pre_render()
 * @see advagg_css_compress_advagg_modify_css_pre_render_alter()
 */
function hook_advagg_modify_css_pre_render_alter(&$children, &$elements) {
  // Get variables.
  $compressor = variable_get('advagg_css_inline_compressor', ADVAGG_CSS_INLINE_COMPRESSOR);

  // Do nothing if the compressor is disabled.
  if (empty($compressor)) {
    return;
  }

  // Do nothing if the page is not cacheable and inline compress if not
  // cacheable is not checked.
  if (!variable_get('advagg_css_inline_compress_if_not_cacheable', ADVAGG_CSS_INLINE_COMPRESS_IF_NOT_CACHEABLE) && !drupal_page_is_cacheable()) {
    return;
  }

  module_load_include('inc', 'advagg_css_compress', 'advagg_css_compress.advagg');
  if ($compressor == 2) {
    // Compress any inline CSS with YUI.
    foreach ($children as $key => &$values) {
      if (!empty($values['#value'])) {
        advagg_css_compress_yui_cssmin($values['#value']);
      }
    }
  }
}

/**
 * Allow other modules to modify $children & $elements before they are rendered.
 *
 * @param array $children
 *   An array of children elements.
 * @param array $elements
 *   A render array containing:
 *   - #items: The JavaScript items as returned by drupal_add_js() and
 *     altered by drupal_get_js().
 *   - #group_callback: A function to call to group #items. Following
 *     this function, #aggregate_callback is called to aggregate items within
 *     the same group into a single file.
 *   - #aggregate_callback: A function to call to aggregate the items within
 *     the groups arranged by the #group_callback function.
 *
 * @see advagg_modify_js_pre_render()
 * @see advagg_js_compress_advagg_modify_js_pre_render_alter()
 */
function hook_advagg_modify_js_pre_render_alter(&$children, &$elements) {
  // Get variables.
  $aggregate_settings['variables']['advagg_js_compressor'] = variable_get('advagg_js_inline_compressor', ADVAGG_JS_INLINE_COMPRESSOR);
  $aggregate_settings['variables']['advagg_js_max_compress_ratio'] = variable_get('advagg_js_max_compress_ratio', ADVAGG_JS_MAX_COMPRESS_RATIO);

  // Do nothing if the compressor is disabled.
  if (empty($aggregate_settings['variables']['advagg_js_compressor'])) {
    return;
  }

  // Do nothing if the page is not cacheable and inline compress if not
  // cacheable is not checked.
  if (!variable_get('advagg_js_inline_compress_if_not_cacheable', ADVAGG_JS_INLINE_COMPRESS_IF_NOT_CACHEABLE) && !drupal_page_is_cacheable()) {
    return;
  }

  // Compress any inline JS.
  module_load_include('inc', 'advagg_js_compress', 'advagg_js_compress.advagg');
  foreach ($children as $key => &$values) {
    if (!empty($values['#value'])) {
      $contents = $values['#value'];
      $filename = drupal_hash_base64($contents);
      advagg_js_compress_prep($contents, $filename, $aggregate_settings, FALSE);
      $values['#value'] = $contents;
    }
  }
}

/**
 * Allow other modules to modify $css_groups right before it is processed.
 *
 * @param array $original
 *   array of original settings.
 * @param array $aggregate_settings
 *   array of contextual settings.
 * @param int $mode
 *   0 to change context to what is inside of $aggregate_settings.
 *   1 to change context back.
 *
 * @see advagg_context_css()
 * @see advagg_advagg_context_alter()
 */
function hook_advagg_context_alter(&$original, $aggregate_settings, $mode) {
  if ($mode == 0) {
    // Change context.
    $original['base_root'] = $GLOBALS['base_root'];
    $original['base_url'] = $GLOBALS['base_url'];
    $original['base_path'] = $GLOBALS['base_path'];
    $original['is_https'] = $GLOBALS['is_https'];
    $GLOBALS['is_https'] = $aggregate_settings['variables']['is_https'];
    if ($aggregate_settings['variables']['is_https']) {
      $GLOBALS['base_root'] = str_replace('http://', 'https://', $GLOBALS['base_root']);
      $GLOBALS['base_url'] = str_replace('http://', 'https://', $GLOBALS['base_url']);
    }
    else {
      $GLOBALS['base_root'] = str_replace('https://', 'http://', $GLOBALS['base_root']);
      $GLOBALS['base_url'] = str_replace('https://', 'http://', $GLOBALS['base_url']);
    }
    $GLOBALS['base_path'] = $aggregate_settings['variables']['base_path'];
  }
  elseif ($mode == 1) {
    // Change context back.
    if (isset($original['base_root'])) {
      $GLOBALS['base_root'] = $original['base_root'];
    }
    if (isset($original['base_url'])) {
      $GLOBALS['base_url'] = $original['base_url'];
    }
    if (isset($original['base_path'])) {
      $GLOBALS['base_path'] = $original['base_path'];
    }
    if (isset($original['is_https'])) {
      $GLOBALS['is_https'] = $original['is_https'];
    }
  }
}

/**
 * @} End of "addtogroup hooks".
 */
