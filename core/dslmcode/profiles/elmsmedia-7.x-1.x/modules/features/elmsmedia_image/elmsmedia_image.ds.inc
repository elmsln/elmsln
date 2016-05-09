<?php
/**
 * @file
 * elmsmedia_image.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_image_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|elmsmedia_image|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'elmsmedia_image';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'field_image',
        3 => 'field_image_caption',
      ),
      'right' => array(
        4 => 'field_tagging',
        5 => 'field_citation',
        6 => 'field_figurelabel_ref',
      ),
      'footer' => array(
        7 => 'og_group_ref',
      ),
      'hidden' => array(
        8 => 'path',
        9 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_image' => 'left',
      'field_image_caption' => 'left',
      'field_tagging' => 'right',
      'field_citation' => 'right',
      'field_figurelabel_ref' => 'right',
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
  $export['node|elmsmedia_image|form'] = $ds_layout;

  return $export;
}
