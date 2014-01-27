<?php

/**
 * @file
 * Advanced CSS/JS aggregation module.
 *
 * File used to store hook_advagg_* hooks.
 */

/**
 * Implements hook_advagg_save_aggregate_alter().
 *
 * Used to add in a .gz file if none exits.
 *
 * @param $files_to_save
 *   array($uri => $contents)
 * @param $aggregate_settings
 *   array of settings.
 * @param $other_parameters
 *   array of containing $files & $type.
 */
function advagg_advagg_save_aggregate_alter(&$files_to_save, $aggregate_settings, $other_parameters) {
  // Return if gzip is disabled.
  if (empty($aggregate_settings['variables']['advagg_gzip'])) {
    return;
  }

  // See if a .gz file already exists.
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
 * Implements hook_advagg_build_aggregate_plans_alter().
 *
 * Used to alter the plan so it has the same grouping as cores.
 *
 * @param $files
 *   List of files in the aggregate as well as the aggregate name.
 * @param $modified
 *   Change this to TRUE if $files has been changed.
 * @param $type
 *   css or js.
 */
function advagg_advagg_build_aggregate_plans_alter(&$files, &$modified, $type) {
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
        $counter++;
        $group = $fileinfo['group'];
        $every_page = $fileinfo['every_page'];
        $modified = TRUE;
      }
      $temp_new_files[$counter][] = $fileinfo;
    }
    $counter++;
  }

  // Replace $files array with new aggregate filenames.
  $files = advagg_generate_filenames(array($temp_new_files), $type);
}


/**
 * Implement hook_advagg_context_alter().
 */
function advagg_advagg_context_alter(&$original, $aggregate_settings, $mode) {
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

