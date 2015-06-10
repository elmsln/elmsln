<?php
/**
 * @file
 * cis_ux.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function cis_ux_defaultconfig_features() {
  return array(
    'cis_ux' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function cis_ux_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'site_403';
  $strongarm->value = 'toboggan/denied';
  $export['site_403'] = $strongarm;

  return $export;
}
