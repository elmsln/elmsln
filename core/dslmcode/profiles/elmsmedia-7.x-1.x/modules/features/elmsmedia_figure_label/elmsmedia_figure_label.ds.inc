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
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'body',
      ),
      'right' => array(
        3 => 'field_tagging',
      ),
      'footer' => array(
        4 => 'og_group_ref',
      ),
      'hidden' => array(
        5 => 'path',
        6 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'body' => 'left',
      'field_tagging' => 'right',
      'og_group_ref' => 'footer',
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
  $export['node|figurelabel|form'] = $ds_layout;

  return $export;
}
