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
        0 => 'group_pushpin',
        1 => 'author',
        2 => 'field_cle_crit_sub_ref',
        3 => 'group_feedback',
        4 => 'field_cle_crit_feedback',
      ),
    ),
    'fields' => array(
      'group_pushpin' => 'ds_content',
      'author' => 'ds_content',
      'field_cle_crit_sub_ref' => 'ds_content',
      'group_feedback' => 'ds_content',
      'field_cle_crit_feedback' => 'ds_content',
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
        1 => 'group_critiqueform',
        2 => 'field_assignment',
        3 => 'body',
        4 => 'field_images',
        5 => 'field_video',
        6 => 'field_links',
        7 => 'field_files',
      ),
    ),
    'fields' => array(
      'group_info' => 'ds_content',
      'group_critiqueform' => 'ds_content',
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
        0 => 'submission_progress',
        1 => 'group_info',
        2 => 'body',
        3 => 'field_links',
        4 => 'group_ferpacontent',
        5 => 'field_assignment',
        6 => 'comments',
        7 => 'submitted_by',
        8 => 'field_images',
        9 => 'field_submission_state',
        10 => 'field_video',
        11 => 'field_files',
      ),
    ),
    'fields' => array(
      'submission_progress' => 'ds_content',
      'group_info' => 'ds_content',
      'body' => 'ds_content',
      'field_links' => 'ds_content',
      'group_ferpacontent' => 'ds_content',
      'field_assignment' => 'ds_content',
      'comments' => 'ds_content',
      'submitted_by' => 'ds_content',
      'field_images' => 'ds_content',
      'field_submission_state' => 'ds_content',
      'field_video' => 'ds_content',
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
