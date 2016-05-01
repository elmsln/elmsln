<?php
/**
 * @file
 * cis_course_authority.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function cis_course_authority_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cis_course|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cis_course';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
      ),
      'right' => array(
        1 => 'field_course_machine_name',
        2 => 'field_cis_course_uuid',
      ),
      'footer' => array(
        3 => 'field_course_sections_ref',
        4 => 'path',
      ),
      'hidden' => array(
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_course_machine_name' => 'right',
      'field_cis_course_uuid' => 'right',
      'field_course_sections_ref' => 'footer',
      'path' => 'footer',
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
  $export['node|cis_course|form'] = $ds_layout;

  return $export;
}
