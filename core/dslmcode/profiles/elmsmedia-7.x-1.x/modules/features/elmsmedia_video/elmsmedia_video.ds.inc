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
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'title',
      ),
      'left' => array(
        2 => 'field_video',
        4 => 'field_caption',
      ),
      'right' => array(
        3 => 'field_poster',
        5 => 'field_transcript',
      ),
      'footer' => array(
        6 => 'field_tagging',
        7 => 'og_group_ref',
      ),
      'hidden' => array(
        8 => 'author',
        9 => 'revision_information',
        10 => 'options',
        11 => 'book',
        12 => 'hidden_nodes',
        13 => 'path',
        14 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'title' => 'header',
      'field_video' => 'left',
      'field_poster' => 'right',
      'field_caption' => 'left',
      'field_transcript' => 'right',
      'field_tagging' => 'footer',
      'og_group_ref' => 'footer',
      'author' => 'hidden',
      'revision_information' => 'hidden',
      'options' => 'hidden',
      'book' => 'hidden',
      'hidden_nodes' => 'hidden',
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
    'layout_disable_css' => 0,
  );
  $export['node|video|form'] = $ds_layout;

  return $export;
}
