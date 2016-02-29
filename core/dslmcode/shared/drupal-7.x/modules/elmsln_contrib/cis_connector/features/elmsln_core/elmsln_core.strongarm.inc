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
  $strongarm->value = 0;
  $export['entity_iframe_embed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_link';
  $strongarm->value = 0;
  $export['entity_iframe_link'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'entity_iframe_theme';
  $strongarm->value = 'foundation_access_iframe';
  $export['entity_iframe_theme'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'masquerade_admin_roles';
  $strongarm->value = array(
    166149871 => '166149871',
    30037204 => '30037204',
    76550217 => '76550217',
    1 => 0,
    2 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    90720314 => 0,
  );
  $export['masquerade_admin_roles'] = $strongarm;

  return $export;
}
