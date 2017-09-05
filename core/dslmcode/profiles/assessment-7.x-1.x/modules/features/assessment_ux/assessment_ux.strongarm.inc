<?php
/**
 * @file
 * assessment_ux.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function assessment_ux_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_assessment_assignment';
  $strongarm->value = 1;
  $export['addanother_button_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_assessment_assignment';
  $strongarm->value = 1;
  $export['addanother_message_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_assessment_assignment';
  $strongarm->value = 1;
  $export['addanother_tab_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_assessment_assignment';
  $strongarm->value = 1;
  $export['addanother_tab_edit_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_assessment_assignment';
  $strongarm->value = 'edit-wysiwyg-template';
  $export['additional_settings__active_tab_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_assessment_assignment';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_assessment_assignment';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_assessment_assignment';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_assessment_item__graded_item';
  $strongarm->value = array(
    'view_modes' => array(
      'gradebook_viewer' => array(
        'custom_settings' => TRUE,
      ),
      'iframe' => array(
        'custom_settings' => FALSE,
      ),
      'token' => array(
        'custom_settings' => FALSE,
      ),
    ),
    'extra_fields' => array(
      'form' => array(),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_assessment_item__graded_item'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_assessment_assignment';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_assessment_assignment'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_assessment_assignment';
  $strongarm->value = '';
  $export['wysiwyg_template_default_assessment_assignment'] = $strongarm;

  return $export;
}
