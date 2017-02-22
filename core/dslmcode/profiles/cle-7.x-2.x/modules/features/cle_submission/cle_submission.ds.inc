<?php
/**
 * @file
 * cle_submission.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function cle_submission_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|cle_submission|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'cle_submission';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'comments' => array(
      'weight' => '7',
      'label' => 'hidden',
      'format' => 'default',
    ),
  );
  $export['node|cle_submission|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function cle_submission_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_submission|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_submission';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_assignment',
      ),
      'left' => array(
        1 => 'field_images',
        2 => 'field_submission_text',
        3 => 'field_files',
        4 => 'field_video',
        5 => 'field_links',
      ),
      'right' => array(
        6 => 'comments',
      ),
    ),
    'fields' => array(
      'field_assignment' => 'header',
      'field_images' => 'left',
      'field_submission_text' => 'left',
      'field_files' => 'left',
      'field_video' => 'left',
      'field_links' => 'left',
      'comments' => 'right',
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
    'layout_disable_css' => 0,
  );
  $export['node|cle_submission|default'] = $ds_layout;

  return $export;
}
