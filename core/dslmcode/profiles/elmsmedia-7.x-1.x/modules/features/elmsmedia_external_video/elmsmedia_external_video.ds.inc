<?php
/**
 * @file
 * elmsmedia_external_video.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function elmsmedia_external_video_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|external_video|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'external_video';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'field_elmsln_competency',
      ),
      'left' => array(
        2 => 'title',
        3 => 'field_citation',
        4 => 'field_external_media',
        5 => '_add_existing_field',
      ),
      'right' => array(
        6 => 'field_poster',
      ),
      'footer' => array(
        7 => 'field_tagging',
        8 => 'field_figurelabel_ref',
      ),
      'hidden' => array(
        9 => 'path',
        10 => 'revision_information',
        11 => 'options',
        12 => 'author',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'field_elmsln_competency' => 'header',
      'title' => 'left',
      'field_citation' => 'left',
      'field_external_media' => 'left',
      '_add_existing_field' => 'left',
      'field_poster' => 'right',
      'field_tagging' => 'footer',
      'field_figurelabel_ref' => 'footer',
      'path' => 'hidden',
      'revision_information' => 'hidden',
      'options' => 'hidden',
      'author' => 'hidden',
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
  $export['node|external_video|form'] = $ds_layout;

  return $export;
}
