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
  $ds_layout->id = 'node|cle_critique|default';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_critique';
  $ds_layout->view_mode = 'default';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_info',
        1 => 'author',
        2 => 'field_cle_crit_feedback',
        3 => 'field_cle_crit_sub_ref',
        4 => 'group_feedback',
      ),
    ),
    'fields' => array(
      'group_info' => 'ds_content',
      'author' => 'ds_content',
      'field_cle_crit_feedback' => 'ds_content',
      'field_cle_crit_sub_ref' => 'ds_content',
      'group_feedback' => 'ds_content',
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
  $export['node|cle_critique|default'] = $ds_layout;

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
        0 => 'group_info',
        1 => 'field_assignment',
        2 => 'body',
        3 => 'field_images',
        4 => 'field_video',
        5 => 'field_links',
        6 => 'field_files',
      ),
    ),
    'fields' => array(
      'group_info' => 'ds_content',
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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_submission|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_submission';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'group_info',
        1 => 'body',
        2 => 'group_ferpacontent',
        3 => 'field_assignment',
        4 => 'field_links',
        5 => 'submitted_by',
        6 => 'field_images',
        7 => 'critique_evas_entity_view_2',
        8 => 'field_video',
        9 => 'field_submission_state',
        10 => 'critique_evas_entity_view_1',
        11 => 'field_files',
        12 => 'comments',
      ),
    ),
    'fields' => array(
      'group_info' => 'ds_content',
      'body' => 'ds_content',
      'group_ferpacontent' => 'ds_content',
      'field_assignment' => 'ds_content',
      'field_links' => 'ds_content',
      'submitted_by' => 'ds_content',
      'field_images' => 'ds_content',
      'critique_evas_entity_view_2' => 'ds_content',
      'field_video' => 'ds_content',
      'field_submission_state' => 'ds_content',
      'critique_evas_entity_view_1' => 'ds_content',
      'field_files' => 'ds_content',
      'comments' => 'ds_content',
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
  $export['node|cle_submission|full'] = $ds_layout;

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
