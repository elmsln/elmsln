<?php
/**
 * @file
 * icor_jmol.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function icor_jmol_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|jmol|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'jmol';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
      ),
      'right' => array(
        2 => 'field_jmol_file',
      ),
      'hidden' => array(
        3 => 'path',
        4 => 'revision_information',
        5 => 'options',
        6 => 'author',
        7 => 'hidden_nodes',
        8 => 'book',
        9 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_jmol_file' => 'right',
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
  $export['node|jmol|form'] = $ds_layout;

  return $export;
}
