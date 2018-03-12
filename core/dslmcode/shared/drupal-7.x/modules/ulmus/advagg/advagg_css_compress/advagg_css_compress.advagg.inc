<?php

/**
 * @file
 * Advanced aggregation css compression module.
 */

/**
 * @addtogroup advagg_hooks
 * @{
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
 * @} End of "addtogroup advagg_hooks".
 */

/**
 * Use the CSSmin library from YUI to compress the CSS.
 */
function advagg_css_compress_yui_cssmin(&$data) {
  // Try libraries for YUI.
  if (is_callable('libraries_load')) {
    libraries_load('YUI-CSS-compressor-PHP-port');
    if (class_exists('tubalmartin\CssMin\Minifier')) {
      // The "use" alias requires php 5.3.
      // @codingStandardsIgnoreLine
      $cssmin = new tubalmartin\CssMin\Minifier();
    }
    elseif (class_exists('CSSmin')) {
      $cssmin = new CSSmin();
    }
  }
  if (!isset($cssmin)) {
    // Load CSSMin.inc if the CSSmin class variable is not set.
    if (!class_exists('CSSmin')) {
      include drupal_get_path('module', 'advagg_css_compress') . '/yui/CSSMin.inc';
    }
    $cssmin = new CSSmin();
  }
  if (!isset($cssmin)) {
    return;
  }

  // Set line break to 4k of text.
  if (method_exists($cssmin, 'setLineBreakPosition')) {
    $cssmin->setLineBreakPosition(4096);
  }
  // Compress the CSS splitting lines after 4k of text.
  if (method_exists($cssmin, 'run')) {
    $compressed = $cssmin->run($data, 4096);
  }
  if (!empty($compressed)) {
    $data = $compressed;
  }
}
