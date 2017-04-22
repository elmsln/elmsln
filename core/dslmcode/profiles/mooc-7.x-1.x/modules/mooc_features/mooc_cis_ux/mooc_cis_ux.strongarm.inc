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

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_revision_delete_cron';
  $strongarm->value = '100';
  $export['node_revision_delete_cron'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_revision_delete_last_execute';
  $strongarm->value = 0;
  $export['node_revision_delete_last_execute'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_revision_delete_time';
  $strongarm->value = 'every_2_years';
  $export['node_revision_delete_time'] = $strongarm;

  return $export;
}
