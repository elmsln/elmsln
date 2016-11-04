<?php
/**
 * @file
 * elmsmedia_figure_label.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_figure_label_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|figurelabel|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'figurelabel';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
        2 => 'body',
      ),
      'header' => array(
        1 => 'field_cis_course_ref',
      ),
      'right' => array(
        3 => 'field_tagging',
      ),
      'footer' => array(
        4 => 'og_group_ref',
      ),
      'hidden' => array(
        5 => 'author',
        6 => 'options',
        7 => 'revision_information',
        8 => 'hidden_nodes',
        9 => 'path',
        10 => 'book',
        11 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_cis_course_ref' => 'header',
      'body' => 'left',
      'field_tagging' => 'right',
      'og_group_ref' => 'footer',
      'author' => 'hidden',
      'options' => 'hidden',
      'revision_information' => 'hidden',
      'hidden_nodes' => 'hidden',
      'path' => 'hidden',
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
  $export['node|figurelabel|form'] = $ds_layout;

  return $export;
}
