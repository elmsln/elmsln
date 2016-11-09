<?php
/**
 * @file
 * elmsmedia_document.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_document_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|document|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'document';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'field_tagging',
      ),
      'right' => array(
        3 => 'field_document_file',
      ),
      'footer' => array(
        4 => 'og_group_ref',
      ),
      'hidden' => array(
        5 => 'path',
        6 => 'revision_information',
        7 => 'options',
        8 => 'author',
        9 => 'hidden_nodes',
        10 => 'book',
        11 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_tagging' => 'left',
      'field_document_file' => 'right',
      'og_group_ref' => 'footer',
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
  $export['node|document|form'] = $ds_layout;

  return $export;
}
