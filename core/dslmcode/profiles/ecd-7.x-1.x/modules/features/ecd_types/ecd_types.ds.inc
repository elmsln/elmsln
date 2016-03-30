<?php
/**
 * @file
 * ecd_types.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function ecd_types_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ecd_asset|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ecd_asset';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'group_logistics',
        6 => 'field_course',
        8 => 'field_source',
        10 => 'field_resource_uuid_bind',
        11 => 'field_student_count',
      ),
      'right' => array(
        2 => 'group_verification',
        5 => 'field_accessibility_verified',
        7 => 'field_quality_verified',
        9 => 'field_copyright_verified',
      ),
      'hidden' => array(
        3 => 'path',
        4 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'group_logistics' => 'left',
      'group_verification' => 'right',
      'path' => 'hidden',
      '_add_existing_field' => 'hidden',
      'field_accessibility_verified' => 'right',
      'field_course' => 'left',
      'field_quality_verified' => 'right',
      'field_source' => 'left',
      'field_copyright_verified' => 'right',
      'field_resource_uuid_bind' => 'left',
      'field_student_count' => 'left',
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
  $export['node|ecd_asset|form'] = $ds_layout;

  return $export;
}
