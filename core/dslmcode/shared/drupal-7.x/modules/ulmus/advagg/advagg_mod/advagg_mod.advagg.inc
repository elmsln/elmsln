<?php

/**
 * @file
 * Advanced CSS/JS aggregation modifier module.
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
    // @ignore sniffer_whitespace_openbracketspacing_openingwhitespace
    if ( empty($cached_data[$info['cache_id']])
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
  // @ignore sniffer_semantics_functioncall_notliteralstring
  $after = t($before);
  // Put back.
  return str_replace($matches[1], str_replace($before, $after, $matches[1]), $matches[0]);
}
