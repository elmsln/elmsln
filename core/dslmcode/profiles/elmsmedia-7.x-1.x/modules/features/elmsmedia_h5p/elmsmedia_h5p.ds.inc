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
      ),
      'left' => array(
        1 => 'title',
        2 => 'h5p_type',
      ),
      'right' => array(
        3 => 'field_tagging',
      ),
      'footer' => array(
        4 => 'h5p',
        5 => 'h5p_editor',
      ),
      'hidden' => array(
        6 => 'path',
        7 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'h5p_type' => 'left',
      'field_tagging' => 'right',
      'h5p' => 'footer',
      'h5p_editor' => 'footer',
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
  );
  $export['node|h5p_content|form'] = $ds_layout;

  return $export;
}
