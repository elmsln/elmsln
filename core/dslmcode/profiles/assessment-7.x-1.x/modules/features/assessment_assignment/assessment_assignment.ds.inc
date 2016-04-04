<?php
/**
 * @file
 * assessment_assignment.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function assessment_assignment_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|assessment_assignment|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'assessment_assignment';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_assignment_directions',
      ),
      'right' => array(
        1 => 'field_evidence',
        2 => 'field_xapi_statements',
        3 => 'field_elmsln_system',
      ),
      'footer' => array(
        4 => 'og_group_ref',
      ),
    ),
    'fields' => array(
      'field_assignment_directions' => 'left',
      'field_evidence' => 'right',
      'field_xapi_statements' => 'right',
      'field_elmsln_system' => 'right',
      'og_group_ref' => 'footer',
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
  $export['node|assessment_assignment|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|assessment_assignment|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'assessment_assignment';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'field_assignment_directions',
      ),
      'right' => array(
        2 => 'group_evidence',
        3 => 'field_evidence',
        5 => 'field_elmsln_system',
        6 => 'field_xapi_statements',
      ),
      'footer' => array(
        4 => 'group_logistics',
        8 => 'field_grades_course_ref',
        9 => 'og_group_ref',
        10 => 'field_number',
        12 => 'field_color',
      ),
      'hidden' => array(
        7 => 'path',
        11 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_assignment_directions' => 'left',
      'group_evidence' => 'right',
      'field_evidence' => 'right',
      'group_logistics' => 'footer',
      'field_elmsln_system' => 'right',
      'field_xapi_statements' => 'right',
      'path' => 'hidden',
      'field_grades_course_ref' => 'footer',
      'og_group_ref' => 'footer',
      'field_number' => 'footer',
      '_add_existing_field' => 'hidden',
      'field_color' => 'footer',
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
  $export['node|assessment_assignment|form'] = $ds_layout;

  return $export;
}
