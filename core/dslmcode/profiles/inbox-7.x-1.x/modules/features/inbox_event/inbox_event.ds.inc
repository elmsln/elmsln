<?php
/**
 * @file
 * inbox_event.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function inbox_event_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|inbox_event|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'inbox_event';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
        1 => 'field_inbox_date',
      ),
      'right' => array(
        2 => 'og_group_ref',
        3 => 'field_inbox_details',
      ),
      'hidden' => array(
        4 => 'path',
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_inbox_date' => 'left',
      'og_group_ref' => 'right',
      'field_inbox_details' => 'right',
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
  $export['node|inbox_event|form'] = $ds_layout;

  return $export;
}
