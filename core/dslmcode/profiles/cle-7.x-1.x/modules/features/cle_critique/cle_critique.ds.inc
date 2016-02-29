<?php
/**
 * @file
 * cle_critique.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function cle_critique_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_submission|critique';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_submission';
  $ds_layout->view_mode = 'critique';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'field_assignment',
        1 => 'body',
        2 => 'field_images',
        3 => 'field_video',
        4 => 'field_links',
        5 => 'field_files',
      ),
    ),
    'fields' => array(
      'field_assignment' => 'ds_content',
      'body' => 'ds_content',
      'field_images' => 'ds_content',
      'field_video' => 'ds_content',
      'field_links' => 'ds_content',
      'field_files' => 'ds_content',
    ),
    'classes' => array(),
    'wrappers' => array(
      'ds_content' => 'div',
    ),
    'layout_wrapper' => 'div',
    'layout_attributes' => '',
    'layout_attributes_merge' => 1,
    'layout_link_attribute' => '',
    'layout_link_custom' => '',
  );
  $export['node|cle_submission|critique'] = $ds_layout;

  return $export;
}

/**
 * Implements hook_ds_view_modes_info().
 */
function cle_critique_ds_view_modes_info() {
  $export = array();

  $ds_view_mode = new stdClass();
  $ds_view_mode->api_version = 1;
  $ds_view_mode->view_mode = 'critique';
  $ds_view_mode->label = 'Critique';
  $ds_view_mode->entities = array(
    'node' => 'node',
  );
  $export['critique'] = $ds_view_mode;

  return $export;
}
