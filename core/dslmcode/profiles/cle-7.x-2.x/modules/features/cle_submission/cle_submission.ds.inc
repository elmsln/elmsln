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
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'submitted_by' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'ds_post_date_medium',
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
  $ds_layout->layout = 'zf_2col_bricks';
  $ds_layout->settings = array(
    'regions' => array(
      'above_left' => array(
        0 => 'body',
        1 => 'group_images',
        2 => 'group_media',
        3 => 'group_video',
        6 => 'group_files',
        8 => 'group_links',
        9 => 'field_links',
        10 => 'field_images',
        11 => 'field_files',
        12 => 'field_video',
      ),
      'above_right' => array(
        4 => 'field_assignment',
        5 => 'submitted_by',
        7 => 'comments',
      ),
    ),
    'fields' => array(
      'body' => 'above_left',
      'group_images' => 'above_left',
      'group_media' => 'above_left',
      'group_video' => 'above_left',
      'field_assignment' => 'above_right',
      'submitted_by' => 'above_right',
      'group_files' => 'above_left',
      'comments' => 'above_right',
      'group_links' => 'above_left',
      'field_links' => 'above_left',
      'field_images' => 'above_left',
      'field_files' => 'above_left',
      'field_video' => 'above_left',
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
  $export['node|cle_submission|default'] = $ds_layout;

  return $export;
}
