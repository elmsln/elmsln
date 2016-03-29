<?php
/**
 * @file
 * icor_poll.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function icor_poll_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|poll|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'poll';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'settings',
      ),
      'right' => array(
        3 => 'choice_wrapper',
      ),
      'footer' => array(
        4 => 'path',
      ),
      'hidden' => array(
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'settings' => 'left',
      'choice_wrapper' => 'right',
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
  $export['node|poll|form'] = $ds_layout;

  return $export;
}
