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
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'field_cle_crit_sub_ref',
      ),
      'right' => array(
        1 => 'field_cle_crit_feedback',
      ),
    ),
    'fields' => array(
      'field_cle_crit_sub_ref' => 'left',
      'field_cle_crit_feedback' => 'right',
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

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|cle_submission|full';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'cle_submission';
  $ds_layout->view_mode = 'full';
  $ds_layout->layout = 'zf_2col_bricks';
  $ds_layout->settings = array(
    'regions' => array(
      'above_left' => array(
        0 => 'group_ferpacontent',
        2 => 'body',
        3 => 'field_links',
        6 => 'field_images',
        7 => 'field_video',
        10 => 'field_files',
      ),
      'above_right' => array(
        1 => 'field_assignment',
        4 => 'submitted_by',
        5 => 'critique_evas_entity_view_2',
        8 => 'critique_evas_entity_view_1',
        9 => 'comments',
      ),
    ),
    'fields' => array(
      'group_ferpacontent' => 'above_left',
      'field_assignment' => 'above_right',
      'body' => 'above_left',
      'field_links' => 'above_left',
      'submitted_by' => 'above_right',
      'critique_evas_entity_view_2' => 'above_right',
      'field_images' => 'above_left',
      'field_video' => 'above_left',
      'critique_evas_entity_view_1' => 'above_right',
      'comments' => 'above_right',
      'field_files' => 'above_left',
    ),
    'classes' => array(),
    'wrappers' => array(
      'top' => 'div',
      'above_left' => 'div',
      'above_right' => 'div',
      'middle' => 'div',
      'below_left' => 'div',
      'below_right' => 'div',
      'bottom' => 'div',
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
