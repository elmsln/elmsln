<?php
/**
 * @file
 * elmsmedia_video.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_video_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|video|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'video';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
      ),
      'left' => array(
        1 => 'title',
        2 => 'field_video',
        3 => 'field_poster',
      ),
      'right' => array(
        4 => 'field_tagging',
        5 => 'field_caption',
        6 => 'field_transcript',
      ),
      'hidden' => array(
        7 => 'path',
        8 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'left',
      'field_video' => 'left',
      'field_poster' => 'left',
      'field_tagging' => 'right',
      'field_caption' => 'right',
      'field_transcript' => 'right',
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
  $export['node|video|form'] = $ds_layout;

  return $export;
}
