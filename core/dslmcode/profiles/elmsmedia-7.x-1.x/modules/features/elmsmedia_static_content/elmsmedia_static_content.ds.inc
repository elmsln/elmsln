<?php
/**
 * @file
 * elmsmedia_static_content.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_static_content_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|static_content|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'static_content';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
        2 => 'body',
      ),
      'footer' => array(
        3 => 'og_group_ref',
      ),
      'hidden' => array(
        4 => 'author',
        5 => 'options',
        6 => 'revision_information',
        7 => 'hidden_nodes',
        8 => 'book',
        9 => 'path',
        10 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'body' => 'header',
      'og_group_ref' => 'footer',
      'author' => 'hidden',
      'options' => 'hidden',
      'revision_information' => 'hidden',
      'hidden_nodes' => 'hidden',
      'book' => 'hidden',
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
    'layout_disable_css' => 0,
  );
  $export['node|static_content|form'] = $ds_layout;

  return $export;
}
