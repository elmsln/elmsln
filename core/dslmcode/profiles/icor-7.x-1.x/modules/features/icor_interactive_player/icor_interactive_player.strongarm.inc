<?php
/**
 * @file
 * icor_interactive_player.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function icor_interactive_player_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__icor_interactive_player';
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
          'weight' => '4',
        ),
        'hidden_nodes' => array(
          'weight' => '8',
        ),
        'book' => array(
          'weight' => '9',
        ),
        'options' => array(
          'weight' => '6',
        ),
        'author' => array(
          'weight' => '7',
        ),
        'revision_information' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(
        'icor_player_eva_entity_view_1' => array(
          'default' => array(
            'weight' => '1',
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
  $export['field_bundle_settings_node__icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_icor_interactive_player';
  $strongarm->value = array();
  $export['menu_options_icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_icor_interactive_player';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_icor_interactive_player';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_icor_interactive_player';
  $strongarm->value = '0';
  $export['node_preview_icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_icor_interactive_player';
  $strongarm->value = 0;
  $export['node_submitted_icor_interactive_player'] = $strongarm;

  return $export;
}
