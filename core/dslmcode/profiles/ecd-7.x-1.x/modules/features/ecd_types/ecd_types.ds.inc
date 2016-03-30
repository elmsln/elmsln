<?php
/**
 * @file
 * ecd_types.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function ecd_types_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|ecd_documentation|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'ecd_documentation';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'submitted_by' => array(
      'weight' => '1',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
    ),
  );
  $export['node|ecd_documentation|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function ecd_types_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cis_system|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cis_system';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
      ),
      'right' => array(
        1 => 'field_machine_name',
      ),
      'hidden' => array(
        2 => 'path',
        3 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_machine_name' => 'right',
      'path' => 'hidden',
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
  $export['node|cis_system|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ecd_asset|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ecd_asset';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_course',
      ),
      'right' => array(
        1 => 'field_accessibility_verified',
        2 => 'field_copyright_verified',
        3 => 'field_quality_verified',
        7 => 'field_ecd_needs_review',
        8 => 'group_verification',
      ),
      'left' => array(
        4 => 'field_asset_type',
        5 => 'field_source',
        6 => 'group_logistics',
      ),
    ),
    'fields' => array(
      'field_course' => 'header',
      'field_accessibility_verified' => 'right',
      'field_copyright_verified' => 'right',
      'field_quality_verified' => 'right',
      'field_asset_type' => 'left',
      'field_source' => 'left',
      'group_logistics' => 'left',
      'field_ecd_needs_review' => 'right',
      'group_verification' => 'right',
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
  $export['node|ecd_asset|default'] = $ds_layout;

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
        5 => 'field_course',
        7 => 'field_source',
        10 => 'field_resource_uuid_bind',
      ),
      'right' => array(
        2 => 'field_asset_type',
        3 => 'group_verification',
        6 => 'field_accessibility_verified',
        8 => 'field_quality_verified',
        9 => 'field_copyright_verified',
        11 => 'field_ecd_needs_review',
      ),
      'hidden' => array(
        4 => 'path',
        12 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'group_logistics' => 'left',
      'field_asset_type' => 'right',
      'group_verification' => 'right',
      'path' => 'hidden',
      'field_course' => 'left',
      'field_accessibility_verified' => 'right',
      'field_source' => 'left',
      'field_quality_verified' => 'right',
      'field_copyright_verified' => 'right',
      'field_resource_uuid_bind' => 'left',
      'field_ecd_needs_review' => 'right',
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
  $export['node|ecd_asset|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ecd_documentation|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ecd_documentation';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_ecd_related_asset',
        1 => 'submitted_by',
      ),
      'left' => array(
        2 => 'field_ecd_doc_details',
      ),
      'right' => array(
        3 => 'field_copyright_justification',
        4 => 'field_ecd_supporting_documents',
      ),
    ),
    'fields' => array(
      'field_ecd_related_asset' => 'header',
      'submitted_by' => 'header',
      'field_ecd_doc_details' => 'left',
      'field_copyright_justification' => 'right',
      'field_ecd_supporting_documents' => 'right',
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
  $export['node|ecd_documentation|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|ecd_documentation|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'ecd_documentation';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
      ),
      'left' => array(
        1 => 'field_ecd_related_asset',
        2 => 'field_copyright_justification',
      ),
      'right' => array(
        3 => 'field_ecd_supporting_documents',
      ),
      'footer' => array(
        4 => 'field_ecd_doc_details',
      ),
      'hidden' => array(
        5 => 'path',
        6 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'field_ecd_related_asset' => 'left',
      'field_copyright_justification' => 'left',
      'field_ecd_supporting_documents' => 'right',
      'field_ecd_doc_details' => 'footer',
      'path' => 'hidden',
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
  $export['node|ecd_documentation|form'] = $ds_layout;

  return $export;
}
