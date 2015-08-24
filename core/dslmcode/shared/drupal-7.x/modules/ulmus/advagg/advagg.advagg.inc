<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * File used to store hook_advagg_* hooks.
 */

// @ignore sniffer_commenting_functioncomment_hookparamdoc:11
/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Used to add in a .gz file if none exits.
 *
 * @param array $files_to_save
 *   Array($uri => $contents).
 * @param array $aggregate_settings
 *   Array of settings.
 * @param array $other_parameters
 *   Array of containing $files and $type.
 */
function advagg_advagg_save_aggregate_alter(array &$files_to_save, array $aggregate_settings, array $other_parameters) {
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

// @ignore sniffer_commenting_functioncomment_hookparamdoc:10
/**
 * Implements hook_advagg_build_aggregate_plans_alter().
 *
 * Used to alter the plan so it has the same grouping as cores.
 *
 * @param array $files
 *   List of files in the aggregate as well as the aggregate name.
 * @param bool $modified
 *   Change this to TRUE if $files has been changed.
 * @param string $type
 *   String containing css or js.
 */
function advagg_advagg_build_aggregate_plans_alter(array &$files, &$modified, $type) {
  // Do nothing if core grouping is disabled.
  if (!variable_get('advagg_core_groups', ADVAGG_CORE_GROUPS)) {
    return;
  }

  $temp_new_files = array();
  $counter = 0;
  foreach ($files as $data) {
    $group = NULL;
    $every_page = NULL;
    foreach ($data['files'] as $fileinfo) {
      // Grouped by group and every_page variables.
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
 * Implements hook_advagg_context_alter().
 */
function advagg_advagg_context_alter(&$original, $aggregate_settings, $mode) {
  if ($mode == 0) {
    // Change context.
    $original['base_root'] = $GLOBALS['base_root'];
    $original['base_url'] = $GLOBALS['base_url'];
    $original['base_path'] = $GLOBALS['base_path'];
    $original['is_https'] = $GLOBALS['is_https'];
    $original['language'] = isset($GLOBALS['language']) ? $GLOBALS['language'] : NULL;

    $GLOBALS['is_https'] = $aggregate_settings['variables']['is_https'];
    if ($aggregate_settings['variables']['is_https']) {
      $GLOBALS['base_root'] = str_replace('http://', 'https://', $GLOBALS['base_root']);
    }
    else {
      $GLOBALS['base_root'] = str_replace('https://', 'http://', $GLOBALS['base_root']);
    }
    $GLOBALS['base_path'] = $aggregate_settings['variables']['base_path'];
    $GLOBALS['base_url'] = rtrim($GLOBALS['base_root'] . $GLOBALS['base_path'], '/');

    if (isset($aggregate_settings['variables']['language'])) {
      $languages = language_list();
      if (isset($languages[$aggregate_settings['variables']['language']])) {
        $GLOBALS['language'] = $languages[$aggregate_settings['variables']['language']];
      }
    }
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
    if (isset($original['language'])) {
      $GLOBALS['language'] = $original['language'];
    }
  }

  // Moved this in here due to incomplete bug reports from
  // https://www.drupal.org/node/1942230. I can not reproduce the reported
  // issues with the patch for the CDN module so I've moved the code into
  // advagg.
  if (!function_exists('cdn_advagg_context_alter') && module_exists('cdn')) {
    if ($mode == 0) {
      // Save original context.
      $original[CDN_MODE_VARIABLE] = variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC);
      $original[CDN_BASIC_FARFUTURE_VARIABLE] = variable_get(CDN_BASIC_FARFUTURE_VARIABLE, CDN_BASIC_FARFUTURE_DEFAULT);
      $original[CDN_HTTPS_SUPPORT_VARIABLE] = variable_get(CDN_HTTPS_SUPPORT_VARIABLE, FALSE);
      $original[CDN_STATUS_VARIABLE] = variable_get(CDN_STATUS_VARIABLE, CDN_DISABLED);

      // Set context for file_create_url()/cdn_file_url_alter().
      $GLOBALS['conf'][CDN_MODE_VARIABLE] = isset($aggregate_settings['variables'][CDN_MODE_VARIABLE])
        ? $aggregate_settings['variables'][CDN_MODE_VARIABLE]
        : variable_get(CDN_MODE_VARIABLE, CDN_MODE_BASIC);
      $GLOBALS['conf'][CDN_BASIC_FARFUTURE_VARIABLE] = isset($aggregate_settings['variables'][CDN_BASIC_FARFUTURE_VARIABLE])
        ? $aggregate_settings['variables'][CDN_BASIC_FARFUTURE_VARIABLE]
        : variable_get(CDN_BASIC_FARFUTURE_VARIABLE, CDN_BASIC_FARFUTURE_DEFAULT);
      $GLOBALS['conf'][CDN_HTTPS_SUPPORT_VARIABLE] = isset($aggregate_settings['variables'][CDN_HTTPS_SUPPORT_VARIABLE])
        ? $aggregate_settings['variables'][CDN_HTTPS_SUPPORT_VARIABLE]
        : variable_get(CDN_HTTPS_SUPPORT_VARIABLE, FALSE);
      $GLOBALS['conf'][CDN_STATUS_VARIABLE] = isset($aggregate_settings['variables'][CDN_STATUS_VARIABLE])
        ? $aggregate_settings['variables'][CDN_STATUS_VARIABLE]
        : variable_get(CDN_STATUS_VARIABLE, CDN_DISABLED);

      // Disable CDN if cdn_check_drupal_path is FALSE.
      if (empty($aggregate_settings['variables']['cdn_check_drupal_path'])) {
        $original[CDN_STATUS_VARIABLE] = CDN_DISABLED;
      }

      // Handle HTTPS.
      if (!empty($aggregate_settings['variables']['cdn_request_is_https']) && !cdn_request_is_https()) {
        if (isset($_SERVER['HTTPS'])) {
          $original['HTTPS'] = $_SERVER['HTTPS'];
        }
        else {
          $original['HTTPS'] = FALSE;
        }
        $_SERVER['HTTPS'] = 'on';
      }
    }
    elseif ($mode == 1) {
      // Set context back.
      $GLOBALS['conf'][CDN_MODE_VARIABLE] = $original[CDN_MODE_VARIABLE];
      $GLOBALS['conf'][CDN_BASIC_FARFUTURE_VARIABLE] = $original[CDN_BASIC_FARFUTURE_VARIABLE];
      $GLOBALS['conf'][CDN_HTTPS_SUPPORT_VARIABLE] = $original[CDN_HTTPS_SUPPORT_VARIABLE];
      $GLOBALS['conf'][CDN_STATUS_VARIABLE] = $original[CDN_STATUS_VARIABLE];

      // Handle HTTPS.
      if (isset($original['HTTPS']) && !is_null($original['HTTPS'])) {
        $_SERVER['HTTPS'] = $original['HTTPS'];
      }
    }
  }
}

/**
 * Implements hook_advagg_get_info_on_files_alter().
 *
 * Used to make sure the info is up to date in the cache.
 */
function advagg_advagg_get_info_on_files_alter(&$return, $cached_data, $bypass_cache) {
  // Check for the ie_css_selector_limiter.
  if (variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER)) {
    $limit_value = variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE);

    // Get the css path.
    list($css_path) = advagg_get_root_files_dir();
    $parts_path = $css_path[1] . '/parts/';

    foreach ($return as &$info) {
      // Skip if not a css file.
      if (empty($info['fileext']) || $info['fileext'] !== 'css') {
        continue;
      }

      // Check if this is a split css file.
      if (strpos($info['data'], $parts_path) !== FALSE) {
        $info['split'] = TRUE;
      }
      // Break large file into multiple small files if needed.
      elseif ($info['linecount'] > $limit_value) {
        advagg_split_css_file($info);
      }
    }
    unset($info);
  }
  // Capture hosts for DNS prefetching.
  if (variable_get('advagg_browser_dns_prefetch', ADVAGG_BROWSER_DNS_PREFETCH)) {
    foreach ($return as &$info) {
      // Skip if not a css file.
      if (empty($info['fileext']) || $info['fileext'] !== 'css') {
        continue;
      }
      // Get the file contents.
      $file_contents = (string) @file_get_contents($info['data']);

      // Get domain names in this css file.
      $matches = array();
      $pattern = '%url\(\s*+[\'"]?+(http:\/\/|https:\/\/|\/\/)([^\'"()\s]++)[\'"]?+\s*+\)%i';
      preg_match_all($pattern, $file_contents, $matches);
      $urls = array();
      if (!empty($matches[1])) {
        foreach ($matches[1] as $key => $match) {
          $parse = @parse_url($match . $matches[2][$key]);
          if (!empty($parse['host']) && empty($urls[$parse['host']])) {
            $urls[$parse['host']] = $match . $parse['host'] . '/';
          }
        }
        $urls = array_values($urls);
      }
      if (!empty($urls)) {
        $info['dns_prefetch'] = $urls;
      }
    }
    unset($info);
  }

}

/**
 * Implements hook_advagg_changed_files().
 *
 * If the color module is enabled regenerate color module css when it changes.
 * If a responsive file inside an adaptive theme has changed, regenerate it.
 *
 * @param array $files
 *   List of files that have changed.
 * @param array $types
 *   Array with the css and or the js key.
 */
function advagg_advagg_changed_files(array $files, array $types) {
  // Keep track of what themes have been done.
  static $themes_done;
  if (!isset($themes_done)) {
    $themes_done = array();
  }

  // Skip if no css changed.
  if (empty($types['css'])) {
    return;
  }

  foreach ($files as $filename => $meta_data) {
    // Only care about css files.
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    if ($ext != 'css') {
      continue;
    }
    advagg_advagg_scan_for_changes($filename, TRUE);
  }

  // Save error states and clear them.
  $errors_before = drupal_static('form_set_error', array());
  form_clear_error();

  // See if the css file is used the theme.
  $themes = list_themes();
  $changed_files = array_keys($files);

  $submit_ran = FALSE;
  foreach ($themes as $theme_name => $theme_values) {
    $files_in_theme = array();
    foreach ($changed_files as $css_file) {
      // Skip if we already did a form submit for this theme.
      if (!empty($themes_done[$theme_name])) {
        continue;
      }

      // Skip if the file that was changed is not in this themes directory.
      $theme_path = drupal_get_path('theme', $theme_name);
      if (strpos($css_file, $theme_path) !== 0) {
        continue;
      }
      $files_in_theme[] = $css_file;
    }

    // Skip the theme if none of the changed files live in here.
    if (empty($files_in_theme)) {
      continue;
    }

    // Get the form for this theme.
    $router_item = menu_get_item('admin/appearance/settings/' . $theme_name);
    if ($router_item['include_file']) {
      require_once DRUPAL_ROOT . '/' . $router_item['include_file'];
    }
    $form = drupal_get_form('system_theme_settings', $theme_name);
    // Get the form defaults.
    $defaults = array();
    advagg_get_defaults_from_form($defaults, $form);

    $rebuild = FALSE;
    if (isset($defaults['atcore_version_test'])) {
      // Rebuild if the theme is an adaptive theme.
      $rebuild = TRUE;
    }
    if (!$rebuild && module_exists('color')) {
      foreach ($files_in_theme as $css_file) {
        if (isset($form['color'])) {
          // Rebuild if the file that was changed is a color module file.
          foreach ($defaults['info']['css'] as $theme_file) {
            if ($theme_path . '/' . $theme_file === $css_file) {
              $rebuild = TRUE;
              break 2;
            }
          }
        }
      }
    }

    // Skip if themes css does not need to be generated dynamically.
    if (empty($rebuild)) {
      continue;
    }

    // Build the palette value.
    $palette = array();
    if (isset($form['color'])) {
      foreach (element_children($form['color']['palette']) as $key) {
        $palette[$key] = $form['color']['palette'][$key]['#value'];
      }
    }

    // Build the form state array.
    $form_state = array(
      'values' => array('palette' => $palette),
      'build_info' => array('args' => array(0 => $theme_name)),
    );
    $form_state['values'] += $defaults;

    if (isset($defaults['atcore_version_test'])) {
      // Validate form.
      at_core_settings_validate($form, $form_state);
      $errors = form_set_error();
      if (empty($errors)) {
        // Only submit if no errors.
        at_core_settings_submit($form, $form_state);
        $themes_done[$theme_name] = TRUE;
        $submit_ran = TRUE;
      }
    }
    elseif (isset($form['color'])) {
      // Validate form.
      color_scheme_form_validate($form, $form_state);
      $errors = form_set_error();
      if (empty($errors)) {
        // Only submit if no errors.
        color_scheme_form_submit($form, $form_state);
        $themes_done[$theme_name] = TRUE;
        $submit_ran = TRUE;
      }
    }
    // Reset form errors.
    form_clear_error();
  }
  // Save error states back.
  $form_set_error = &drupal_static('form_set_error', array());
  $form_set_error = $errors_before;

  // Rescan again as the submit will generate new files in the css dir.
  if ($submit_ran) {
    advagg_push_new_changes();
  }
}

/**
 * Implements hook_advagg_scan_for_changes().
 *
 * Used to see if the responsive files inside an adaptive theme has changed.
 */
function advagg_advagg_scan_for_changes($filename, $save_changes = FALSE) {
  // Skip if this file is not a css file.
  $ext = pathinfo($filename, PATHINFO_EXTENSION);
  if ($ext !== 'css') {
    return FALSE;
  }

  // Skip if the file is not in an adaptive theme.
  $adaptivethemes = array();
  $themes = list_themes();
  foreach ($themes as $theme_name => $theme_values) {
    $path = variable_get('theme_' . $theme_name . '_files_directory', '');
    if (!empty($path) && strpos($filename, $path) !== FALSE) {
      $adaptivethemes[$theme_name] = $path;
    }
  }
  if (empty($adaptivethemes)) {
    return;
  }

  $this_file_changed = FALSE;
  foreach ($adaptivethemes as $theme_name => $path) {
    // Set up some paths we use to get and save files.
    $path_to_responsive_css = drupal_get_path('theme', $theme_name) . '/css/';
    $path_to_panels_css = drupal_get_path('theme', 'adaptivetheme') . '/layouts/css/';

    // Map files to generated file names.
    $file_map = array(
      "$path/$theme_name.responsive.styles.css" => array(
        $path_to_responsive_css . 'responsive.custom.css',
        $path_to_responsive_css . 'responsive.smalltouch.portrait.css',
        $path_to_responsive_css . 'responsive.smartphone.portrait.css',
        $path_to_responsive_css . 'responsive.smalltouch.landscape.css',
        $path_to_responsive_css . 'responsive.smartphone.landscape.css',
        $path_to_responsive_css . 'responsive.tablet.portrait.css',
        $path_to_responsive_css . 'responsive.tablet.landscape.css',
        $path_to_responsive_css . 'responsive.desktop.css',
      ),
      "$path/$theme_name.lt-ie8.layout.css" => array(
        $path_to_panels_css . 'ie_defaults.css',
      ),
    );
    if (!isset($file_map[$filename])) {
      continue;
    }

    // See if anything has changed.
    if (advagg_detect_subfile_changes($filename, $file_map[$filename], 'adaptivetheme', $save_changes)) {
      $this_file_changed = TRUE;
    }
  }

  return $this_file_changed;
}

/**
 * Given a form get the default values from it.
 *
 * @param array $defaults
 *   An empty array used to populate the default values.
 * @param array $form
 *   The form returned from drupal_get_form().
 * @param string $parent_key
 *   The key name of the parent.
 */
function advagg_get_defaults_from_form(array &$defaults, array $form, $parent_key = '') {
  foreach (element_children($form) as $key) {
    $values = $form[$key];
    if (isset($values['#value'])) {
      // Grab defaults at this level.
      if (!isset($defaults[$key])) {
        $defaults[$key] = $values['#value'];
      }
      else {
        $defaults[$parent_key . '-' . $key] = $values['#value'];
      }
    }
    elseif (isset($values['#default_value'])) {
      // Grab defaults at this level.
      if (!isset($defaults[$key])) {
        $defaults[$key] = $values['#default_value'];
      }
      else {
        $defaults[$parent_key . '-' . $key] = $values['#default_value'];
      }
    }
    elseif (is_array($values)) {
      // Go deeper if needed.
      advagg_get_defaults_from_form($defaults, $values, $key);
    }
  }
}
