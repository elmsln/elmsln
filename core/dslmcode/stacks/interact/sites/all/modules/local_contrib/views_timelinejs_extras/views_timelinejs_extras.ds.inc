<?php
/**
 * @file
 * views_timelinejs_extras.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function views_timelinejs_extras_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|timeline|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'timeline';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
        2 => 'field_time_points',
      ),
      'hidden' => array(
        3 => 'path',
        4 => 'author',
        5 => 'revision_information',
        6 => 'book',
        7 => 'hidden_nodes',
        8 => 'options',
        9 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'field_time_points' => 'header',
      'path' => 'hidden',
      'author' => 'hidden',
      'revision_information' => 'hidden',
      'book' => 'hidden',
      'hidden_nodes' => 'hidden',
      'options' => 'hidden',
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
    'layout_disable_css' => 0,
  );
  $export['node|timeline|form'] = $ds_layout;

  return $export;
}
