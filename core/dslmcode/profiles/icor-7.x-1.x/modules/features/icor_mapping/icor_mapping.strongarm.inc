<?php
/**
 * @file
 * icor_mapping.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function icor_mapping_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__map';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '100',
        ),
        'hidden_nodes' => array(
          'weight' => '100',
        ),
        'book' => array(
          'weight' => '100',
        ),
        'options' => array(
          'weight' => '100',
        ),
        'author' => array(
          'weight' => '100',
        ),
        'revision_information' => array(
          'weight' => '100',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__map_point';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
        'path' => array(
          'weight' => '100',
        ),
        'hidden_nodes' => array(
          'weight' => '100',
        ),
        'book' => array(
          'weight' => '100',
        ),
        'options' => array(
          'weight' => '100',
        ),
        'author' => array(
          'weight' => '100',
        ),
        'revision_information' => array(
          'weight' => '100',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_map';
  $strongarm->value = array();
  $export['menu_options_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_map_point';
  $strongarm->value = array();
  $export['menu_options_map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_map';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_map_point';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_map';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_map_point';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_map';
  $strongarm->value = '0';
  $export['node_preview_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_map_point';
  $strongarm->value = '0';
  $export['node_preview_map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_map';
  $strongarm->value = 0;
  $export['node_submitted_map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_map_point';
  $strongarm->value = 0;
  $export['node_submitted_map_point'] = $strongarm;

  return $export;
}
