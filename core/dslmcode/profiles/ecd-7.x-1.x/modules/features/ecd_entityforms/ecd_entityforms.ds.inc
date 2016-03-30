<?php
/**
 * @file
 * ecd_entityforms.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function ecd_entityforms_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'entityform|course_access_request|form';
  $ds_layout->entity_type = 'entityform';
  $ds_layout->bundle = 'course_access_request';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_account_request',
        1 => 'field_account_email',
        2 => 'field_role',
      ),
      'right' => array(
        3 => 'group_request_details',
        8 => 'field_course_access',
        9 => 'field_duration',
      ),
      'footer' => array(
        4 => 'field_documentation',
        5 => 'group_justification',
        6 => 'field_written_justification',
        7 => 'field_access_status',
      ),
      'hidden' => array(
        10 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_account_request' => 'left',
      'field_account_email' => 'left',
      'field_role' => 'left',
      'group_request_details' => 'right',
      'field_documentation' => 'footer',
      'group_justification' => 'footer',
      'field_written_justification' => 'footer',
      'field_access_status' => 'footer',
      'field_course_access' => 'right',
      'field_duration' => 'right',
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
  $export['entityform|course_access_request|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'entityform|system_access_request|form';
  $ds_layout->entity_type = 'entityform';
  $ds_layout->bundle = 'system_access_request';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_account_request',
        1 => 'field_account_email',
        2 => 'field_role',
      ),
      'right' => array(
        3 => 'group_request_details',
        8 => 'field_ecd_systems',
        10 => 'field_duration',
      ),
      'footer' => array(
        4 => 'group_justification',
        5 => 'field_documentation',
        6 => 'field_access_status',
        7 => 'field_written_justification',
      ),
      'hidden' => array(
        9 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_account_request' => 'left',
      'field_account_email' => 'left',
      'field_role' => 'left',
      'group_request_details' => 'right',
      'group_justification' => 'footer',
      'field_documentation' => 'footer',
      'field_access_status' => 'footer',
      'field_written_justification' => 'footer',
      'field_ecd_systems' => 'right',
      '_add_existing_field' => 'hidden',
      'field_duration' => 'right',
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
  $export['entityform|system_access_request|form'] = $ds_layout;

  return $export;
}
