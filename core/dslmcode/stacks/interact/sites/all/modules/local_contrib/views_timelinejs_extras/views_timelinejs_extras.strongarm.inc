<?php
/**
 * @file
 * views_timelinejs_extras.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function views_timelinejs_extras_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__timeline';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'entityreference_view_widget' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '3',
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
      'display' => array(
        'timeline_content_type_entity_view_1' => array(
          'default' => array(
            'weight' => '2',
            'visible' => TRUE,
          ),
          'iframe' => array(
            'weight' => '1',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_timeline';
  $strongarm->value = array();
  $export['menu_options_timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_timeline';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_timeline';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_timeline';
  $strongarm->value = '0';
  $export['node_preview_timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_timeline';
  $strongarm->value = 0;
  $export['node_submitted_timeline'] = $strongarm;

  return $export;
}
