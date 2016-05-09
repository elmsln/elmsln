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
        1 => 'group_evidence',
        2 => 'field_assignment_directions',
        3 => 'field_evidence',
        5 => 'field_elmsln_system',
        6 => 'field_xapi_statements',
      ),
      'right' => array(
        4 => 'group_logistics',
        8 => 'field_number',
        9 => 'field_cis_course_ref',
        10 => 'og_group_ref',
        11 => 'field_color',
      ),
      'hidden' => array(
        7 => 'path',
        12 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'group_evidence' => 'left',
      'field_assignment_directions' => 'left',
      'field_evidence' => 'left',
      'group_logistics' => 'right',
      'field_elmsln_system' => 'left',
      'field_xapi_statements' => 'left',
      'path' => 'hidden',
      'field_number' => 'right',
      'field_cis_course_ref' => 'right',
      'og_group_ref' => 'right',
      'field_color' => 'right',
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
  $export['node|assessment_assignment|form'] = $ds_layout;

  return $export;
}
