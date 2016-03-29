<?php
/**
 * @file
 * elmsmedia_audio.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_audio_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|audio|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'audio';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'footer' => array(
        0 => 'path',
      ),
      'header' => array(
        1 => 'field_cis_course_ref',
      ),
      'left' => array(
        2 => 'title',
        3 => 'field_audio',
      ),
      'right' => array(
        4 => 'field_tagging',
      ),
      'hidden' => array(
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'path' => 'footer',
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_audio' => 'left',
      'field_tagging' => 'right',
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
  $export['node|audio|form'] = $ds_layout;

  return $export;
}
