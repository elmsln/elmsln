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
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'og_group_ref',
      ),
      'left' => array(
        2 => 'title',
        3 => 'h5p_type',
      ),
      'right' => array(
        4 => 'field_tagging',
      ),
      'footer' => array(
        5 => 'h5p',
        6 => 'h5p_editor',
      ),
      'hidden' => array(
        7 => 'path',
        8 => 'hidden_nodes',
        9 => 'author',
        10 => 'revision_information',
        11 => 'book',
        12 => 'options',
        13 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'og_group_ref' => 'header',
      'title' => 'left',
      'h5p_type' => 'left',
      'field_tagging' => 'right',
      'h5p' => 'footer',
      'h5p_editor' => 'footer',
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
  );
  $export['node|h5p_content|form'] = $ds_layout;

  return $export;
}
