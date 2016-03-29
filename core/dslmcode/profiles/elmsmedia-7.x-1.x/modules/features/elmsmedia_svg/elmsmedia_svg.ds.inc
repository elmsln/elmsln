<?php
/**
 * @file
 * elmsmedia_svg.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_svg_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|svg|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'svg';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'field_svg',
      ),
      'right' => array(
        3 => 'field_svg_alttext',
        4 => 'field_figurelabel_ref',
      ),
      'hidden' => array(
        5 => 'path',
        6 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_svg' => 'left',
      'field_svg_alttext' => 'right',
      'field_figurelabel_ref' => 'right',
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
  $export['node|svg|form'] = $ds_layout;

  return $export;
}
