<?php
/**
 * @file
 * elmsln_core.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsln_core_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_embed';
  $strongarm->value = '0';
  $export['entity_iframe_embed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_link';
  $strongarm->value = '0';
  $export['entity_iframe_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_theme';
  $strongarm->value = 'foundation_access_iframe';
  $export['entity_iframe_theme'] = $strongarm;

  return $export;
}
