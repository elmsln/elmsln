<?php
/**
 * @file
 * elmsmedia_h5p.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_h5p_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|h5p_content|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'h5p_content';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
        2 => 'h5p_type',
        3 => 'h5p',
        4 => 'h5p_editor',
      ),
      'right' => array(
        5 => 'field_figurelabel_ref',
        8 => 'field_tagging',
      ),
      'left' => array(
        6 => 'field_accessible_fallback',
      ),
      'footer' => array(
        7 => 'og_group_ref',
      ),
      'hidden' => array(
        9 => 'path',
        10 => 'hidden_nodes',
        11 => 'author',
        12 => 'revision_information',
        13 => 'book',
        14 => 'options',
        15 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'h5p_type' => 'header',
      'h5p' => 'header',
      'h5p_editor' => 'header',
      'field_figurelabel_ref' => 'right',
      'field_accessible_fallback' => 'left',
      'og_group_ref' => 'footer',
      'field_tagging' => 'right',
      'path' => 'hidden',
      'hidden_nodes' => 'hidden',
      'author' => 'hidden',
      'revision_information' => 'hidden',
      'book' => 'hidden',
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
  $export['node|h5p_content|form'] = $ds_layout;

  return $export;
}
