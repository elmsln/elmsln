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
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
      ),
      'left' => array(
        2 => 'choice_wrapper',
      ),
      'right' => array(
        3 => 'settings',
      ),
      'hidden' => array(
        4 => 'path',
        5 => 'revision_information',
        6 => 'options',
        7 => 'author',
        8 => 'hidden_nodes',
        9 => 'book',
        10 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'choice_wrapper' => 'left',
      'settings' => 'right',
      'path' => 'hidden',
      'revision_information' => 'hidden',
      'options' => 'hidden',
      'author' => 'hidden',
      'hidden_nodes' => 'hidden',
      'book' => 'hidden',
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
  $export['node|poll|form'] = $ds_layout;

  return $export;
}
