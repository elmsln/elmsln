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
        1 => 'field_elmsln_competency',
        2 => 'title',
        3 => 'h5p_type',
        4 => 'h5p',
        5 => 'h5p_editor',
      ),
      'left' => array(
        6 => 'field_accessible_fallback',
      ),
      'right' => array(
        7 => 'field_figurelabel_ref',
        8 => 'field_tagging',
      ),
      'footer' => array(
        9 => 'og_group_ref',
      ),
      'hidden' => array(
        10 => 'path',
        11 => 'hidden_nodes',
        12 => 'author',
        13 => 'revision_information',
        14 => 'book',
        15 => 'options',
        16 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'field_elmsln_competency' => 'header',
      'title' => 'header',
      'h5p_type' => 'header',
      'h5p' => 'header',
      'h5p_editor' => 'header',
      'field_accessible_fallback' => 'left',
      'field_figurelabel_ref' => 'right',
      'field_tagging' => 'right',
      'og_group_ref' => 'footer',
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
