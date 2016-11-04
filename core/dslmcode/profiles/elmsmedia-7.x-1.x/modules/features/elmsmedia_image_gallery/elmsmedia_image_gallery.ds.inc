<?php
/**
 * @file
 * elmsmedia_image_gallery.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_image_gallery_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|image_gallery|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'image_gallery';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'title',
      ),
      'right' => array(
        1 => 'field_images',
      ),
      'footer' => array(
        2 => 'og_group_ref',
      ),
      'hidden' => array(
        3 => 'author',
        4 => 'options',
        5 => 'revision_information',
        6 => 'hidden_nodes',
        7 => 'book',
        8 => 'path',
        10 => '_add_existing_field',
      ),
      'header' => array(
        9 => 'field_cis_course_ref',
      ),
    ),
    'fields' => array(
      'title' => 'left',
      'field_images' => 'right',
      'og_group_ref' => 'footer',
      'author' => 'hidden',
      'options' => 'hidden',
      'revision_information' => 'hidden',
      'hidden_nodes' => 'hidden',
      'book' => 'hidden',
      'path' => 'hidden',
      'field_cis_course_ref' => 'header',
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
  $export['node|image_gallery|form'] = $ds_layout;

  return $export;
}
