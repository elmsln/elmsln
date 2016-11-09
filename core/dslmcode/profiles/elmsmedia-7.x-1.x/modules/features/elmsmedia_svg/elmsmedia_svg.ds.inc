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
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
        2 => 'field_svg',
      ),
      'left' => array(
        3 => 'field_svg_alttext',
        4 => 'field_accessible_fallback',
      ),
      'right' => array(
        5 => 'field_tagging',
        6 => 'field_figurelabel_ref',
      ),
      'footer' => array(
        7 => 'og_group_ref',
      ),
      'hidden' => array(
        8 => 'author',
        9 => 'revision_information',
        10 => 'options',
        11 => 'path',
        12 => 'hidden_nodes',
        13 => 'book',
        14 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'field_svg' => 'header',
      'field_svg_alttext' => 'left',
      'field_accessible_fallback' => 'left',
      'field_tagging' => 'right',
      'field_figurelabel_ref' => 'right',
      'og_group_ref' => 'footer',
      'author' => 'hidden',
      'revision_information' => 'hidden',
      'options' => 'hidden',
      'path' => 'hidden',
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
  $export['node|svg|form'] = $ds_layout;

  return $export;
}
