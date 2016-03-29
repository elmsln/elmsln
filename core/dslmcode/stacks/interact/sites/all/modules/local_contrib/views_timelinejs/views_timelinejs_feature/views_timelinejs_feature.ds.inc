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
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'title',
      ),
      'left' => array(
        1 => 'field_timeline_dates',
        2 => 'field_timeline_media_link',
        3 => 'field_timeline_media_image',
      ),
      'right' => array(
        4 => 'body',
        5 => 'field_timeline_credit_text',
        6 => 'field_timeline_caption_text',
      ),
      'footer' => array(
        7 => 'path',
      ),
      'hidden' => array(
        8 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'header',
      'field_timeline_dates' => 'left',
      'field_timeline_media_link' => 'left',
      'field_timeline_media_image' => 'left',
      'body' => 'right',
      'field_timeline_credit_text' => 'right',
      'field_timeline_caption_text' => 'right',
      'path' => 'footer',
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
  $export['node|timeline_date|form'] = $ds_layout;

  return $export;
}
