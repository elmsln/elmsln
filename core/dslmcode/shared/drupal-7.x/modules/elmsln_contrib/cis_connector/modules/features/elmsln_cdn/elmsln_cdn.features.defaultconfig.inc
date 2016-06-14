<?php
/**
 * @file
 * elmsln_cdn.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function elmsln_cdn_defaultconfig_features() {
  return array(
    'elmsln_cdn' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function elmsln_cdn_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cdn_https_support';
  $strongarm->value = 1;
  $export['cdn_https_support'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cdn_mode';
  $strongarm->value = 'basic';
  $export['cdn_mode'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'cdn_status';
  $strongarm->value = '2';
  $export['cdn_status'] = $strongarm;

  return $export;
}

