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
  $ds_layout->id = 'assessment_item|graded_item|default';
  $ds_layout->entity_type = 'assessment_item';
  $ds_layout->bundle = 'graded_item';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'zf_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_grade_tabgroup',
        1 => 'og_group_ref',
        2 => 'group_gradessubmission',
        3 => 'group_gradesassessment',
        4 => 'group_gradesstudent',
        5 => 'group_gradesassignment',
        6 => 'field_assignment_ref',
        7 => 'field_evaluation_ref',
        8 => 'group_gradesdetails',
        9 => 'group_grade_debug',
      ),
    ),
    'fields' => array(
      'group_grade_tabgroup' => 'ds_content',
      'og_group_ref' => 'ds_content',
      'group_gradessubmission' => 'ds_content',
      'group_gradesassessment' => 'ds_content',
      'group_gradesstudent' => 'ds_content',
      'group_gradesassignment' => 'ds_content',
      'field_assignment_ref' => 'ds_content',
      'field_evaluation_ref' => 'ds_content',
      'group_gradesdetails' => 'ds_content',
      'group_grade_debug' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['assessment_item|graded_item|default'] = $ds_layout;

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
        1 => 'field_evaluation_ref',
      ),
      'right' => array(
        2 => 'og_group_ref',
      ),
      'hidden' => array(
        3 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_assignment_ref' => 'left',
      'field_evaluation_ref' => 'left',
      'og_group_ref' => 'right',
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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'assessment_item|graded_item|gradebook_viewer';
  $ds_layout->entity_type = 'assessment_item';
  $ds_layout->bundle = 'graded_item';
  $ds_layout->view_mode = 'gradebook_viewer';
  $ds_layout->layout = 'zf_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_grade_tabgroup',
        1 => 'field_grades_student',
        2 => 'og_group_ref',
        3 => 'field_remote_item_uuid',
        4 => 'group_gradessubmission',
        5 => 'field_grades_point_value',
        6 => 'field_remote_submission',
        7 => 'field_grades_instructor',
        8 => 'group_gradesassessment',
        9 => 'field_assessment_status',
        10 => 'group_gradesstudent',
        11 => 'group_gradesassignment',
        12 => 'field_assignment_ref',
        13 => 'group_gradesdetails',
        14 => 'group_grade_debug',
      ),
    ),
    'fields' => array(
      'group_grade_tabgroup' => 'ds_content',
      'field_grades_student' => 'ds_content',
      'og_group_ref' => 'ds_content',
      'field_remote_item_uuid' => 'ds_content',
      'group_gradessubmission' => 'ds_content',
      'field_grades_point_value' => 'ds_content',
      'field_remote_submission' => 'ds_content',
      'field_grades_instructor' => 'ds_content',
      'group_gradesassessment' => 'ds_content',
      'field_assessment_status' => 'ds_content',
      'group_gradesstudent' => 'ds_content',
      'group_gradesassignment' => 'ds_content',
      'field_assignment_ref' => 'ds_content',
      'group_gradesdetails' => 'ds_content',
      'group_grade_debug' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['assessment_item|graded_item|gradebook_viewer'] = $ds_layout;

  return $export;
}
