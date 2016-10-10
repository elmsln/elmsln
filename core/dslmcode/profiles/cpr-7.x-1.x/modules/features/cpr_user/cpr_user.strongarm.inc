<?php
/**
 * @file
 * cpr_user.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cpr_user_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_picture_default';
  $strongarm->value = '';
  $export['user_picture_default'] = $strongarm;

  return $export;
}
