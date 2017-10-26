<?php
/**
 * @file
 * elmsln_lrs.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsln_lrs_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_content_types_view_modes';
  $strongarm->value = array(
    'full' => 'full',
    'teaser' => 0,
    'rss' => 0,
    'print' => 0,
    'diff_standard' => 0,
    'iframe' => 0,
    'token' => 0,
    'revision' => 0,
  );
  $export['tincanapi_content_types_view_modes'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_function';
  $strongarm->value = 'elmsln_core_tincanapi_send';
  $export['tincanapi_function'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_links_external';
  $strongarm->value = 1;
  $export['tincanapi_links_external'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_selector_vimeo';
  $strongarm->value = 'iframe[data-mediavideo-src^=\'https://player.vimeo.com/video\'],iframe[src^=\'https://player.vimeo.com/video\']';
  $export['tincanapi_selector_vimeo'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_selector_youtube';
  $strongarm->value = 'iframe[data-mediavideo-src^=\'https://www.youtube.com/embed\'],iframe[src^=\'https://www.youtube.com/embed\']';
  $export['tincanapi_selector_youtube'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_simplify_id';
  $strongarm->value = 0;
  $export['tincanapi_simplify_id'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'tincanapi_statement_actor';
  $strongarm->value = '[current-user:name]';
  $export['tincanapi_statement_actor'] = $strongarm;

  return $export;
}
