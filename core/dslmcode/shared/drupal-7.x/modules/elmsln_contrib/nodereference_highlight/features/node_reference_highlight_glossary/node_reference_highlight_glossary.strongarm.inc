<?php
/**
 * @file
 * node_reference_highlight_glossary.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function node_reference_highlight_glossary_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__nrhi_term';
  $strongarm->value = array();
  $export['field_bundle_settings_node__nrhi_term'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_nrhi_term';
  $strongarm->value = array();
  $export['menu_options_nrhi_term'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_nrhi_term';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_nrhi_term'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_nrhi_term';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_nrhi_term'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_nrhi_term';
  $strongarm->value = '0';
  $export['node_preview_nrhi_term'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_nrhi_term';
  $strongarm->value = 0;
  $export['node_submitted_nrhi_term'] = $strongarm;

  return $export;
}
