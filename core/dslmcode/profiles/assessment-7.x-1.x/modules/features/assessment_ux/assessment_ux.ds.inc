<?php
/**
 * @file
 * assessment_ux.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function assessment_ux_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'assessment_item|graded_item|form';
  $ds_layout->entity_type = 'assessment_item';
  $ds_layout->bundle = 'graded_item';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_assignment_ref',
        1 => 'field_remote_submission',
        2 => 'field_assessment_status',
        3 => 'field_grades_point_value',
      ),
      'right' => array(
        4 => 'field_grades_student',
        5 => 'field_grades_instructor',
        6 => 'og_group_ref',
        7 => 'field_remote_item_uuid',
      ),
      'hidden' => array(
        8 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_assignment_ref' => 'left',
      'field_remote_submission' => 'left',
      'field_assessment_status' => 'left',
      'field_grades_point_value' => 'left',
      'field_grades_student' => 'right',
      'field_grades_instructor' => 'right',
      'og_group_ref' => 'right',
      'field_remote_item_uuid' => 'right',
      '_add_existing_field' => 'hidden',
    ),
    'classes' => array(),
    'wrappers' => array(
      'header' => 'div',
      'left' => 'div',
      'right' => 'div',
      'footer' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['assessment_item|graded_item|form'] = $ds_layout;

  return $export;
}
