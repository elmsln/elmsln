<?php
/**
 * @file
 * assessment_gradebook_ux.ds.inc
 */

/**
 * Implements hook_ds_custom_fields_info().
 */
function assessment_gradebook_ux_ds_custom_fields_info() {
  $export = array();

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'assignment_block';
  $ds_field->label = 'Assignment Block';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'cle_submission|gradebook_viewer';
  $ds_field->properties = array(
    'block' => 'views|2d4926fc1fc7624f18c76a4dd55d9c6a',
    'block_render' => '3',
  );
  $export['assignment_block'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'other_submissions';
  $ds_field->label = 'Other submissions';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'cle_submission|gradebook_viewer';
  $ds_field->properties = array(
    'block' => 'views|gradebook_other_work-block',
    'block_render' => '3',
  );
  $export['other_submissions'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'submission_evaluation_form';
  $ds_field->label = 'Submission evaluation form';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'cle_submission|gradebook_viewer';
  $ds_field->properties = array(
    'block' => 'assessment_gradebook|cle_submission_evaluation',
    'block_render' => '3',
  );
  $export['submission_evaluation_form'] = $ds_field;

  $ds_field = new stdClass();
  $ds_field->api_version = 1;
  $ds_field->field = 'textbook_magellan';
  $ds_field->label = 'Textbook Magellan';
  $ds_field->field_type = 6;
  $ds_field->entities = array(
    'node' => 'node',
  );
  $ds_field->ui_limit = 'assessment_assignment|full';
  $ds_field->properties = array(
    'block' => 'textbook|textbook-magellan',
    'block_render' => '3',
  );
  $export['textbook_magellan'] = $ds_field;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function assessment_gradebook_ux_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|assessment_assignment|gradebook_viewer';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'assessment_assignment';
  $ds_layout->view_mode = 'gradebook_viewer';
  $ds_layout->layout = 'zf_2col_bricks';
  $ds_layout->settings = array(
    'regions' => array(
      'above_left' => array(
        0 => 'group_details',
        3 => 'field_number',
        4 => 'field_sub_number',
        6 => 'field_due_date',
        8 => 'field_media_requirements',
      ),
      'top' => array(
        1 => 'field_color',
      ),
      'above_right' => array(
        2 => 'group_logistics',
        9 => 'field_visibility',
        10 => 'field_cle_require_submission',
        11 => 'field_cle_assign_depend',
      ),
      'middle' => array(
        5 => 'body',
        7 => 'group_assignment_description',
      ),
    ),
    'fields' => array(
      'group_details' => 'above_left',
      'field_color' => 'top',
      'group_logistics' => 'above_right',
      'field_number' => 'above_left',
      'field_sub_number' => 'above_left',
      'body' => 'middle',
      'field_due_date' => 'above_left',
      'group_assignment_description' => 'middle',
      'field_media_requirements' => 'above_left',
      'field_visibility' => 'above_right',
      'field_cle_require_submission' => 'above_right',
      'field_cle_assign_depend' => 'above_right',
    ),
    'classes' => array(),
    'wrappers' => array(
      'top' => 'div',
      'above_left' => 'div',
      'above_right' => 'div',
      'middle' => 'div',
      'below_left' => 'div',
      'below_right' => 'div',
      'bottom' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|assessment_assignment|gradebook_viewer'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function assessment_gradebook_ux_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'gradebook_viewer';
  $ds_view_mode->label = 'Gradebook Viewer';
  $ds_view_mode->entities = array(
    'assessment_item' => 'assessment_item',
    'node' => 'node',
    'user' => 'user',
  );
  $export['gradebook_viewer'] = $ds_view_mode;

  return $export;
}
