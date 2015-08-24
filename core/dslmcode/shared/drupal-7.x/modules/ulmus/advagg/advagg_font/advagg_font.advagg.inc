<?php

/**
 * @file
 * Advanced aggregation css compression module.
 */

/**
 * Implements hook_advagg_get_css_file_contents_alter().
 */
function advagg_font_advagg_get_css_file_contents_alter(&$contents, $file, $aggregate_settings) {
  // Do nothing if this is disabled.
  if (empty($aggregate_settings['variables']['advagg_font_fontfaceobserver'])) {
    return;
  }

  $replacements = advagg_font_get_replacements_array($contents);
  foreach ($replacements as $replace) {
    $contents = str_replace($replace[0], $replace[1] . $replace[2], $contents);
  }
}

/**
 * Implements hook_advagg_get_info_on_files_alter().
 *
 * Used to add external font info for css file.
 */
function advagg_font_advagg_get_info_on_files_alter(&$return, $cached_data, $bypass_cache) {
  $advagg_font_ffo = variable_get('advagg_font_fontfaceobserver', ADVAGG_FONT_FONTFACEOBSERVER);
  if (!empty($advagg_font_ffo)) {
    foreach ($return as &$info) {
      // Skip if not a css file.
      if (empty($info['fileext']) || $info['fileext'] !== 'css') {
        continue;
      }
      // Get the file contents.
      $file_contents = file_get_contents($info['data']);
      // Get font names.
      $replacements = advagg_font_get_replacements_array($file_contents);

      // Remove old values.
      if (isset($info['advagg_font'])) {
        unset($info['advagg_font']);
      }
      // Add in new values.
      foreach ($replacements as $replace) {
        $info['advagg_font'][$replace[4]] = str_replace(array('"', "'"), '', $replace[3]);
      }
    }
    unset($info);
  }
}
