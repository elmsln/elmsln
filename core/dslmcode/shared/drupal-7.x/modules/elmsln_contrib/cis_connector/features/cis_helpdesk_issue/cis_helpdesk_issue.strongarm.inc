<?php
/**
 * @file
 * cis_helpdesk_issue.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cis_helpdesk_issue_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_cis_helpdesk_issue';
  $strongarm->value = 'edit-comment';
  $export['additional_settings__active_tab_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_cis_helpdesk_issue';
  $strongarm->value = '1';
  $export['ant_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_cis_helpdesk_issue';
  $strongarm->value = '[node:field_cis_hd_course] [node:field_cis_hd_section] [node:field_cis_hd_who]';
  $export['ant_pattern_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['ant_php_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['comment_anonymous_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_cis_helpdesk_issue';
  $strongarm->value = '0';
  $export['comment_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['comment_default_mode_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_cis_helpdesk_issue';
  $strongarm->value = '10';
  $export['comment_default_per_page_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['comment_form_location_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_cis_helpdesk_issue';
  $strongarm->value = '0';
  $export['comment_preview_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['comment_subject_field_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_cis_helpdesk_issue';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__cis_helpdesk_issue';
  $strongarm->value = array(
    'view_modes' => array(
      'teaser' => array(
        'custom_settings' => TRUE,
      ),
      'full' => array(
        'custom_settings' => FALSE,
      ),
      'rss' => array(
        'custom_settings' => FALSE,
      ),
      'search_index' => array(
        'custom_settings' => FALSE,
      ),
      'search_result' => array(
        'custom_settings' => FALSE,
      ),
      'print' => array(
        'custom_settings' => FALSE,
      ),
      'diff_standard' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '1',
        ),
        'path' => array(
          'weight' => '1',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_cis_helpdesk_issue';
  $strongarm->value = array();
  $export['menu_options_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_cis_helpdesk_issue';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeformscols_field_placements_cis_helpdesk_issue_default';
  $strongarm->value = array(
    'additional_settings' => array(
      'region' => 'right',
      'weight' => '11',
      'has_required' => FALSE,
      'title' => 'Vertical tabs',
      'hidden' => 0,
    ),
    'actions' => array(
      'region' => 'main',
      'weight' => '10',
      'has_required' => FALSE,
      'title' => 'Save',
      'hidden' => 0,
    ),
    'body' => array(
      'region' => 'main',
      'weight' => '1',
      'has_required' => TRUE,
      'title' => 'Description',
    ),
    'field_cis_hd_course' => array(
      'region' => 'main',
      'weight' => '7',
      'has_required' => FALSE,
      'title' => 'Course',
      'hidden' => 0,
    ),
    'field_cis_hd_notes' => array(
      'region' => 'main',
      'weight' => '9',
      'has_required' => FALSE,
      'title' => 'Notes',
      'hidden' => 0,
    ),
    'field_cis_hd_resolved_by' => array(
      'region' => 'main',
      'weight' => '8',
      'has_required' => FALSE,
      'title' => 'Resolved by',
      'hidden' => 0,
    ),
    'field_cis_hd_section' => array(
      'region' => 'main',
      'weight' => '5',
      'has_required' => FALSE,
      'title' => 'Section',
      'hidden' => 0,
    ),
    'field_cis_hd_specs' => array(
      'region' => 'main',
      'weight' => '3',
      'has_required' => FALSE,
      'title' => 'Specs',
      'hidden' => 0,
    ),
    'field_cis_hd_status' => array(
      'region' => 'main',
      'weight' => '6',
      'has_required' => TRUE,
      'title' => 'Status',
    ),
    'field_cis_hd_what' => array(
      'region' => 'main',
      'weight' => '0',
      'has_required' => TRUE,
      'title' => 'What',
    ),
    'field_cis_hd_where' => array(
      'region' => 'main',
      'weight' => '4',
      'has_required' => FALSE,
      'title' => 'Where',
      'hidden' => 0,
    ),
    'field_cis_hd_who' => array(
      'region' => 'main',
      'weight' => '2',
      'has_required' => FALSE,
      'title' => 'Who',
      'hidden' => 0,
    ),
  );
  $export['nodeformscols_field_placements_cis_helpdesk_issue_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_cis_helpdesk_issue';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_cis_helpdesk_issue';
  $strongarm->value = '0';
  $export['node_preview_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_cis_helpdesk_issue';
  $strongarm->value = 0;
  $export['node_submitted_cis_helpdesk_issue'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_cis_helpdesk_issue';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_cis_helpdesk_issue'] = $strongarm;

  return $export;
}
