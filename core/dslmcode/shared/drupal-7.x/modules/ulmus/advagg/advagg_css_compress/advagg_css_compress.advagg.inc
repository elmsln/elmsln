<?php

/**
 * @file
 * Advanced aggregation css compression module.
 */

/**
 * Implements hook_advagg_get_css_file_contents_pre_alter().
 */
function advagg_css_compress_advagg_get_css_file_contents_pre_alter(&$file, &$optimize, &$aggregate_settings) {
  // Get per file settings.
  if (!empty($aggregate_settings['variables']['advagg_css_compressor_file_settings'])) {
    $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $file);
    if (isset($aggregate_settings['variables']['advagg_css_compressor_file_settings'][$form_api_filename])) {
      $aggregate_settings['variables']['advagg_css_compressor'] = $aggregate_settings['variables']['advagg_css_compressor_file_settings'][$form_api_filename];
    }
  }

  if (isset($aggregate_settings['variables']['advagg_css_compressor']) && $aggregate_settings['variables']['advagg_css_compressor'] == -1) {
    $optimize = FALSE;
  }
}

/**
 * Implements hook_advagg_get_css_aggregate_contents_alter().
 */
function advagg_css_compress_advagg_get_css_aggregate_contents_alter(&$data, $files, $aggregate_settings) {
  // Get per file settings.
  foreach ($files as $filename => $settings) {
    if (!empty($aggregate_settings['variables']['advagg_css_compressor_file_settings'])) {
      $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $filename);
      if (isset($aggregate_settings['variables']['advagg_css_compressor_file_settings'][$form_api_filename])) {
        $aggregate_settings['variables']['advagg_css_compressor'] = $aggregate_settings['variables']['advagg_css_compressor_file_settings'][$form_api_filename];
        // If one file can not be compressed then the whole aggregrate can not
        // be compressed.
        if ($aggregate_settings['variables']['advagg_css_compressor'] == 0) {
          break;
        }
      }
    }
  }

  // Do nothing if the compressor is disabled.
  if (empty($aggregate_settings['variables']['advagg_css_compressor'])) {
    return;
  }
  // Do nothing if the cache settings are set to Development.
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    return;
  }

  list(, , , $functions) = advagg_css_compress_configuration();

  if (isset($functions[$aggregate_settings['variables']['advagg_css_compressor']])) {
    $run = $functions[$aggregate_settings['variables']['advagg_css_compressor']];
    if (function_exists($run)) {
      $functions[$aggregate_settings['variables']['advagg_css_compressor']]($data);
    }
  }
}

/**
 * Use the CSSmin library from YUI to compress the CSS.
 */
function advagg_css_compress_yui_cssmin(&$data) {
  // Only include CSSMin.inc if the CSSmin class doesn't exist.
  if (!class_exists('CSSmin')) {
    include drupal_get_path('module', 'advagg_css_compress') . '/yui/CSSMin.inc';
  }

  $cssmin = new CSSmin(TRUE);
  // Compress the CSS splitting lines after 4k of text.
  $data = $cssmin->run($data, 4096);
}
