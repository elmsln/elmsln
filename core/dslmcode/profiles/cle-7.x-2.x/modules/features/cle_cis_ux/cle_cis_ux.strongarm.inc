<?php
/**
 * @file
 * cle_cis_ux.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cle_cis_ux_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageinfo_cache_field_assignment_image';
  $strongarm->value = array(
    'elmsln_gray' => 'elmsln_gray',
    'elmsln_normalize' => 'elmsln_normalize',
  );
  $export['imageinfo_cache_field_assignment_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageinfo_cache_field_images';
  $strongarm->value = array(
    'elmsln_gray' => 'elmsln_gray',
    'elmsln_normalize' => 'elmsln_normalize',
  );
  $export['imageinfo_cache_field_images'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageinfo_cache_field_project_image';
  $strongarm->value = array(
    'elmsln_gray' => 'elmsln_gray',
    'elmsln_normalize' => 'elmsln_normalize',
  );
  $export['imageinfo_cache_field_project_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageinfo_cache_strip_image_token';
  $strongarm->value = 1;
  $export['imageinfo_cache_strip_image_token'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'imageinfo_cache_use_httprl';
  $strongarm->value = 1;
  $export['imageinfo_cache_use_httprl'] = $strongarm;

  return $export;
}
