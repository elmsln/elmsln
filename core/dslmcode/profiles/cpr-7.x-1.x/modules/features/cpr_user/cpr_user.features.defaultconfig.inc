<?php
/**
 * @file
 * cpr_user.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function cpr_user_defaultconfig_features() {
  return array(
    'cpr_user' => array(
      'strongarm' => 'strongarm',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function cpr_user_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_default';
  $strongarm->value = '';
  $export['user_picture_default'] = $strongarm;

  return $export;
}
