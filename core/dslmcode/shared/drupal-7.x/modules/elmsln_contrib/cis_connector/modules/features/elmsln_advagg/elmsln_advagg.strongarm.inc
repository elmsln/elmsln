<?php
/**
 * @file
 * elmsln_advagg.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsln_advagg_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'advagg_resource_hints_dns_prefetch';
  $strongarm->value = 1;
  $export['advagg_resource_hints_dns_prefetch'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'advagg_resource_hints_location';
  $strongarm->value = '1';
  $export['advagg_resource_hints_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'advagg_resource_hints_preconnect';
  $strongarm->value = 1;
  $export['advagg_resource_hints_preconnect'] = $strongarm;

  return $export;
}
