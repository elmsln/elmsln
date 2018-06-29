<?php

/**
 * @file
 * Advanced CSS/JS aggregation modifier module.
 */

/**
 * @addtogroup advagg_hooks
 * @{
 */

/**
 * Implements hook_advagg_get_info_on_files_alter().
 *
 * Used to make sure the info is up to date in the cache.
 */
function advagg_mod_advagg_get_info_on_files_alter(&$return, $cached_data, $bypass_cache) {
  foreach ($return as &$info) {
    if (empty($info['fileext']) || $info['fileext'] !== 'js') {
      continue;
    }
    // New or updated data or no advagg_js_compress data.
    if (empty($cached_data[$info['cache_id']])
      || empty($info['advagg_mod'])
      || $info['content_hash'] != $cached_data[$info['cache_id']]['content_hash']
    ) {
      // Check the cache.
      $info['advagg_mod'] = advagg_mod_js_contains_jquery_drupal($info['data']);
    }
  }
  unset($info);
}

/**
 * Implements hook_advagg_get_js_file_contents_alter().
 */
function advagg_mod_advagg_get_js_file_contents_alter(&$contents, $filename, $aggregate_settings) {
  // Fix adminimal_admin_menu js issues with admin menu.
  if (module_exists('adminimal_admin_menu')) {
    advagg_mod_fix_js_adminimal_admin_menu($contents, $filename);
  }
}

/**
 * Implements hook_advagg_get_css_file_contents_alter().
 *
 * Used to run strings inside of quotes of the content attribute through the t
 * function.
 *
 * @see drupal_load_stylesheet_content()
 */
function advagg_mod_advagg_get_css_file_contents_alter(&$contents, $filename, $aggregate_settings) {
  if (empty($aggregate_settings['variables']['advagg_mod_css_translate'])) {
    return;
  }

  // Code taken from drupal_load_stylesheet_content().
  // Regexp to match double quoted strings.
  $double_quot = '"[^"\\\\]*(?:\\\\.[^"\\\\]*)*"';
  // Regexp to match single quoted strings.
  $single_quot = "'[^'\\\\]*(?:\\\\.[^'\\\\]*)*'";
  // Extract all content inside of quotes.
  $css_content_pattern = "/content:.*?($double_quot|$single_quot|(?:\\;|\\})).*?(?:\\;|\\})/";

  // Run strings inside of quotes of the content attribute through the t
  // function.
  $contents = preg_replace_callback($css_content_pattern, 'advagg_mod_advagg_css_content_t_replace_callback', $contents);
}

/**
 * @} End of "addtogroup advagg_hooks".
 */

/**
 * Run preg matches through the t() function.
 *
 * @param array $matches
 *   Array of matches from preg_replace_callback().
 *
 * @return string
 *   Replaced String.
 */
function advagg_mod_advagg_css_content_t_replace_callback(array $matches) {
  // Skip if equal to ; or }.
  if ($matches[1] === ';' || $matches[1] === '}') {
    return $matches[0];
  }
  // Remove quotes for t function.
  $before = substr($matches[1], 1, -1);
  // Only run if it contains A-Za-z.
  if (!preg_match('/[A-Za-z]/', $before)) {
    return $matches[0];
  }
  // Only run if it contains characters other than unicode.
  $css_unicode_pattern = '/\\\\[0-9a-fA-F]{1,6}(?:\\r\\n|[ \\t\\r\\n\\f])?/';
  $unicode_removed = preg_replace($css_unicode_pattern, '', $before);
  if (empty($unicode_removed)) {
    return $matches[0];
  }

  // Run t function.
  // @codingStandardsIgnoreLine
  $after = t($before);
  // Put back.
  return str_replace($matches[1], str_replace($before, $after, $matches[1]), $matches[0]);
}

/**
 * Fix admin menu.
 *
 * @param string $contents
 *   The contents of the js file.
 * @param string $filename
 *   The filename.
 */
function advagg_mod_fix_js_adminimal_admin_menu(&$contents, $filename) {
  // Get adminimal_admin_menu path.
  $adminimal_admin_menu_path = drupal_get_path('module', 'adminimal_admin_menu');
  // Only match slicknav js.
  if ($filename !== "$adminimal_admin_menu_path/js/slicknav/jquery.slicknav.js"
    && $filename !== "$adminimal_admin_menu_path/js/slicknav/jquery-no-conflict.slicknav.js"
  ) {
    return;
  }

  // Lines to look for.
  $inserted_string_1 = "Drupal.admin = Drupal.admin || {};\n";
  $inserted_string_2 = "Drupal.admin.behaviors = Drupal.admin.behaviors || {};\n";
  if (strpos($contents, $inserted_string_1) !== FALSE
    && strpos($contents, $inserted_string_2) !== FALSE
  ) {
    // Do nothing if the lines already exist.
    return;
  }

  // Get length of slicknav javascript.
  $strlen = strlen($contents);
  // Get the first occurrence of the problem string.
  $end = strpos($contents, 'Drupal.admin.behaviors.responsivemenu');
  if ($end === FALSE) {
    return;
  }
  // Get the start of this code block.
  $start = strrpos($contents, '(function($)', $end - $strlen);
  if ($start === FALSE) {
    return;
  }
  // Get the lcoation of {.
  $middle = strpos($contents, "{\n", $start);
  if ($middle === FALSE) {
    $middle = strpos($contents, "{", $start);
    if ($middle === FALSE) {
      return;
    }
    else {
      $middle += 1;
    }
  }
  else {
    $middle += 2;
  }

  // Insert new js code.
  $contents = substr_replace($contents, $inserted_string_1 . $inserted_string_2, $middle, 0);
}
