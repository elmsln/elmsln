<?php
/**
 * @file
 * cle_submission.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cle_submission_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_cle_submission';
  $strongarm->value = 'edit-unique-field';
  $export['additional_settings__active_tab_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_cle_submission';
  $strongarm->value = 0;
  $export['comment_anonymous_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_cle_submission';
  $strongarm->value = '2';
  $export['comment_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_cle_submission';
  $strongarm->value = 1;
  $export['comment_default_mode_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_cle_submission';
  $strongarm->value = '50';
  $export['comment_default_per_page_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_cle_submission';
  $strongarm->value = 1;
  $export['comment_form_location_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_cle_submission';
  $strongarm->value = '0';
  $export['comment_preview_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_cle_submission';
  $strongarm->value = 0;
  $export['comment_subject_field_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__cle_submission';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => FALSE,
      ),
      'full' => array(
        'custom_settings' => TRUE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'iframe' => array(
        'custom_settings' => FALSE,
      ),
      'revision' => array(
        'custom_settings' => FALSE,
      ),
      'gradebook_viewer' => array(
        'custom_settings' => TRUE,
      ),
      'critique' => array(
        'custom_settings' => TRUE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '16',
        ),
        'hidden_nodes' => array(
          'weight' => '15',
        ),
        'book' => array(
          'weight' => '17',
        ),
        'options' => array(
          'weight' => '18',
        ),
        'author' => array(
          'weight' => '14',
        ),
        'revision_information' => array(
          'weight' => '13',
        ),
      ),
      'display' => array(
        'critique_evas_entity_view_1' => array(
          'critique' => array(
            'weight' => '2',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '4',
            'visible' => TRUE,
          ),
        ),
        'critique_evas_entity_view_2' => array(
          'critique' => array(
            'weight' => '1',
            'visible' => FALSE,
          ),
          'default' => array(
            'weight' => '10',
            'visible' => FALSE,
          ),
          'full' => array(
            'weight' => '3',
            'visible' => TRUE,
          ),
        ),
      ),
    ),
  );
  $export['field_bundle_settings_node__cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_cle_submission';
  $strongarm->value = array();
  $export['menu_options_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_cle_submission';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_cle_submission';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_cle_submission';
  $strongarm->value = '0';
  $export['node_preview_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_cle_submission';
  $strongarm->value = 1;
  $export['node_submitted_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_cle_submission';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unique_field_comp_cle_submission';
  $strongarm->value = 'all';
  $export['unique_field_comp_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unique_field_fields_cle_submission';
  $strongarm->value = array(
    0 => 'name',
    1 => 'field_assignment',
  );
  $export['unique_field_fields_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unique_field_scope_cle_submission';
  $strongarm->value = 'type';
  $export['unique_field_scope_cle_submission'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'unique_field_show_matches_cle_submission';
  $strongarm->value = array(
    0 => 'show_matches',
  );
  $export['unique_field_show_matches_cle_submission'] = $strongarm;

  return $export;
}
