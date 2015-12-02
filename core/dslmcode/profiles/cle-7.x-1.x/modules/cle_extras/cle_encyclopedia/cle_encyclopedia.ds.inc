<?php
/**
 * @file
 * cle_encyclopedia.ds.inc
 */

/**
 * Implements hook_ds_field_settings_info().
 */
function cle_encyclopedia_ds_field_settings_info() {
  $export = array();

  $ds_fieldsetting = new stdClass();
  $ds_fieldsetting->api_version = 1;
  $ds_fieldsetting->id = 'node|cle_encyclopedia_entry|default';
  $ds_fieldsetting->entity_type = 'node';
  $ds_fieldsetting->bundle = 'cle_encyclopedia_entry';
  $ds_fieldsetting->view_mode = 'default';
  $ds_fieldsetting->settings = array(
    'title' => array(
      'weight' => '0',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'comments' => array(
      'weight' => '6',
      'label' => 'hidden',
      'format' => 'default',
    ),
    'post_date' => array(
      'weight' => '4',
      'label' => 'hidden',
      'format' => 'ds_post_date_long',
    ),
    'submitted_by' => array(
      'weight' => '3',
      'label' => 'hidden',
      'format' => 'ds_time_ago',
    ),
  );
  $export['node|cle_encyclopedia_entry|default'] = $ds_fieldsetting;

  return $export;
}

/**
 * Implements hook_ds_layout_settings_info().
 */
function cle_encyclopedia_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_encyclopedia_entry|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_encyclopedia_entry';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'zf_2col_bricks';
  $ds_layout->settings = array(
    'regions' => array(
      'top' => array(
        0 => 'title',
      ),
      'above_left' => array(
        1 => 'body',
      ),
      'above_right' => array(
        2 => 'field_images',
      ),
      'middle' => array(
        3 => 'submitted_by',
        4 => 'post_date',
        5 => 'og_group_ref',
        6 => 'comments',
      ),
    ),
    'fields' => array(
      'title' => 'top',
      'body' => 'above_left',
      'field_images' => 'above_right',
      'submitted_by' => 'middle',
      'post_date' => 'middle',
      'og_group_ref' => 'middle',
      'comments' => 'middle',
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
  $export['node|cle_encyclopedia_entry|default'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_encyclopedia_entry|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_encyclopedia_entry';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_bricks';
  $ds_layout->settings = array(
    'regions' => array(
      'top' => array(
        0 => 'title',
      ),
      'above_left' => array(
        1 => 'body',
      ),
      'above_right' => array(
        2 => 'field_images',
      ),
      'bottom' => array(
        3 => 'og_group_ref',
      ),
      'hidden' => array(
        4 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'top',
      'body' => 'above_left',
      'field_images' => 'above_right',
      'og_group_ref' => 'bottom',
      '_add_existing_field' => 'hidden',
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
  $export['node|cle_encyclopedia_entry|form'] = $ds_layout;

  return $export;
}
