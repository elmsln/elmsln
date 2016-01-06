<?php
/**
 * @file
 * mooc_cis_ux.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_cis_ux_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hidden_nodes_types';
  $strongarm->value = array(
    'mooc_container' => 'mooc_container',
    'page' => 'page',
  );
  $export['hidden_nodes_types'] = $strongarm;

  return $export;
}
