<?php
/**
 * @file
 * cis_example_cis.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cis_example_cis_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cis_build_authenticated';
  $strongarm->value = 'cis_account_required';
  $export['cis_build_authenticated'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cis_build_code';
  $strongarm->value = 'cis_account_required,cis_lms_required';
  $export['cis_build_code'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cis_build_lms';
  $strongarm->value = 'cis_account_required,cis_lms_required';
  $export['cis_build_lms'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cis_build_open';
  $strongarm->value = '';
  $export['cis_build_open'] = $strongarm;

  return $export;
}
