<?php
/**
 * @file
 * elmsln_voice.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsln_voice_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'voicecommander_menu';
  $strongarm->value = array(
    'menu-elmsln-add' => 'menu-elmsln-add',
    'menu-elmsln-navigation' => 'menu-elmsln-navigation',
    'menu-elmsln-settings' => 'menu-elmsln-settings',
  );
  $export['voicecommander_menu'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'voicecommander_mobile';
  $strongarm->value = 1;
  $export['voicecommander_mobile'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'voicecommander_optional_prefix';
  $strongarm->value = 1;
  $export['voicecommander_optional_prefix'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'voicecommander_prefix';
  $strongarm->value = 'elms';
  $export['voicecommander_prefix'] = $strongarm;

  return $export;
}
