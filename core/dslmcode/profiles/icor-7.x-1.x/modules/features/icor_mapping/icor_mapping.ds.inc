<?php
/**
 * @file
 * icor_mapping.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function icor_mapping_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|map_point|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'map_point';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
        1 => 'field_location_description',
        2 => 'field_location',
      ),
      'footer' => array(
        3 => 'group_admin',
        4 => 'author',
        6 => 'options',
        7 => 'book',
        8 => 'revision_information',
        9 => 'hidden_nodes',
        10 => 'path',
      ),
      'hidden' => array(
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'field_location_description' => 'header',
      'field_location' => 'header',
      'group_admin' => 'footer',
      'author' => 'footer',
      '_add_existing_field' => 'hidden',
      'options' => 'footer',
      'book' => 'footer',
      'revision_information' => 'footer',
      'hidden_nodes' => 'footer',
      'path' => 'footer',
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
  $export['node|map_point|form'] = $ds_layout;

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|map|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'map';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
        1 => 'field_map_points',
      ),
      'footer' => array(
        2 => 'book',
        3 => 'author',
        4 => 'revision_information',
        5 => 'hidden_nodes',
        6 => 'options',
        7 => 'path',
      ),
      'hidden' => array(
        8 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'field_map_points' => 'header',
      'book' => 'footer',
      'author' => 'footer',
      'revision_information' => 'footer',
      'hidden_nodes' => 'footer',
      'options' => 'footer',
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
    'layout_disable_css' => 0,
  );
  $export['node|map|form'] = $ds_layout;

  return $export;
}
