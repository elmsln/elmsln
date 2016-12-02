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
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'field_cis_course_ref',
        1 => 'field_elmsln_competency',
      ),
      'left' => array(
        2 => 'title',
        3 => 'field_tagging',
      ),
      'right' => array(
        4 => 'field_audio',
      ),
      'footer' => array(
        5 => 'og_group_ref',
      ),
      'hidden' => array(
        6 => 'path',
        7 => 'revision_information',
        8 => 'options',
        9 => 'author',
        10 => 'hidden_nodes',
        11 => 'book',
        12 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'field_cis_course_ref' => 'header',
      'field_elmsln_competency' => 'header',
      'title' => 'left',
      'field_tagging' => 'left',
      'field_audio' => 'right',
      'og_group_ref' => 'footer',
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
  $export['node|audio|form'] = $ds_layout;

  return $export;
}
