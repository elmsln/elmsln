<?php
/**
 * @file
 * mooc_page.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function mooc_page_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'node|page|form';
  $ds_layout->entity_type = 'node';
  $ds_layout->bundle = 'page';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'zf_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'body',
        2 => 'group_visual_identifiers',
        3 => 'group_cis_tag_group',
        4 => 'field_instructional_significance',
        5 => 'field_cis_tag',
        6 => 'field_mooc_image',
      ),
      'hidden' => array(
        7 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'body' => 'ds_content',
      'group_visual_identifiers' => 'ds_content',
      'group_cis_tag_group' => 'ds_content',
      'field_instructional_significance' => 'ds_content',
      'field_cis_tag' => 'ds_content',
      'field_mooc_image' => 'ds_content',
      '_add_existing_field' => 'hidden',
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
  $export['node|page|form'] = $ds_layout;

  return $export;
}
