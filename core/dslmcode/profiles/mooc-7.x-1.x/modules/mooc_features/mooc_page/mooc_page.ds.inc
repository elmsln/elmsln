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
  $ds_layout->layout = 'ds_1col';
  $ds_layout->settings = array(
    'regions' => array(
      'ds_content' => array(
        0 => 'title',
        1 => 'body',
        2 => 'group_settings',
        3 => 'field_fa_primary_color',
        4 => 'field_fa_secondary_color',
        5 => 'field_mooc_nav_label',
        6 => 'field_mooc_nav_custom_text',
        7 => 'field_cis_tag',
        8 => 'path',
        9 => 'hidden_nodes',
        10 => 'options',
        11 => 'group_advanced_tabs',
        12 => 'group_outline',
        13 => 'group_tag',
        14 => 'book',
        15 => 'group_author',
        16 => 'author',
        17 => 'revision_information',
        18 => 'field_elmsln_competency',
        19 => 'field_instructional_significance',
        20 => 'group_inst_strat',
        21 => 'group_interface',
        22 => 'group_visibility',
        23 => 'group_advanced',
        24 => 'field_mooc_image',
        25 => 'group_topic_banner',
        27 => 'group_colors',
        28 => 'group_navigation_block',
      ),
      'hidden' => array(
        26 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'body' => 'ds_content',
      'group_settings' => 'ds_content',
      'field_fa_primary_color' => 'ds_content',
      'field_fa_secondary_color' => 'ds_content',
      'field_mooc_nav_label' => 'ds_content',
      'field_mooc_nav_custom_text' => 'ds_content',
      'field_cis_tag' => 'ds_content',
      'path' => 'ds_content',
      'hidden_nodes' => 'ds_content',
      'options' => 'ds_content',
      'group_advanced_tabs' => 'ds_content',
      'group_outline' => 'ds_content',
      'group_tag' => 'ds_content',
      'book' => 'ds_content',
      'group_author' => 'ds_content',
      'author' => 'ds_content',
      'revision_information' => 'ds_content',
      'field_elmsln_competency' => 'ds_content',
      'field_instructional_significance' => 'ds_content',
      'group_inst_strat' => 'ds_content',
      'group_interface' => 'ds_content',
      'group_visibility' => 'ds_content',
      'group_advanced' => 'ds_content',
      'field_mooc_image' => 'ds_content',
      'group_topic_banner' => 'ds_content',
      '_add_existing_field' => 'hidden',
      'group_colors' => 'ds_content',
      'group_navigation_block' => 'ds_content',
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
