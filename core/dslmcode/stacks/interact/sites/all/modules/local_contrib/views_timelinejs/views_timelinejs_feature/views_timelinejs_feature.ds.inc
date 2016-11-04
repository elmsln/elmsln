<?php
/**
 * @file
 * views_timelinejs_feature.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function views_timelinejs_feature_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|timeline_date|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'timeline_date';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
        1 => 'field_timeline_dates',
      ),
      'left' => array(
        2 => 'body',
        3 => 'field_timeline_caption_text',
        4 => 'field_timeline_credit_text',
      ),
      'right' => array(
        5 => 'field_timeline_media_link',
        6 => 'field_timeline_media_image',
      ),
      'hidden' => array(
        7 => 'path',
        8 => 'revision_information',
        9 => 'options',
        10 => 'author',
        11 => 'hidden_nodes',
        12 => 'book',
        13 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'field_timeline_dates' => 'header',
      'body' => 'left',
      'field_timeline_caption_text' => 'left',
      'field_timeline_credit_text' => 'left',
      'field_timeline_media_link' => 'right',
      'field_timeline_media_image' => 'right',
      'path' => 'hidden',
      'revision_information' => 'hidden',
      'options' => 'hidden',
      'author' => 'hidden',
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
  $export['node|timeline_date|form'] = $ds_layout;

  return $export;
}
