<?php
/**
 * @file
 * views_timelinejs_feature.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function views_timelinejs_feature_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__timeline_date';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '0',
        ),
        'path' => array(
          'weight' => '7',
        ),
        'hidden_nodes' => array(
          'weight' => '11',
        ),
        'book' => array(
          'weight' => '12',
        ),
        'options' => array(
          'weight' => '9',
        ),
        'author' => array(
          'weight' => '10',
        ),
        'revision_information' => array(
          'weight' => '8',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_timeline_date';
  $strongarm->value = array();
  $export['menu_options_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_timeline_date';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_timeline_date';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_timeline_date';
  $strongarm->value = '0';
  $export['node_preview_timeline_date'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_timeline_date';
  $strongarm->value = 0;
  $export['node_submitted_timeline_date'] = $strongarm;

  return $export;
}
