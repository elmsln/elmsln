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
        2 => 'group_settings',
        5 => 'field_fa_primary_color',
        6 => 'field_fa_secondary_color',
        7 => 'field_mooc_nav_style',
        8 => 'field_mooc_nav_display',
        9 => 'field_mooc_nav_type',
        10 => 'field_mooc_nav_label',
        11 => 'field_mooc_nav_custom_text',
        12 => 'field_cis_tag',
        13 => 'hidden_nodes',
        14 => 'options',
        15 => 'group_advanced_tabs',
        16 => 'group_outline',
        17 => 'group_tag',
        18 => 'field_mooc_image',
        19 => 'group_author',
        20 => 'book',
        21 => 'author',
        22 => 'revision_information',
        24 => 'field_instructional_significance',
        27 => 'group_inst_strat',
        28 => 'group_interface',
        29 => 'group_topic_banner',
        30 => 'group_navigation_block',
        31 => 'group_colors',
        32 => 'group_visibility',
        33 => 'group_advanced',
      ),
      'hidden' => array(
        3 => 'group_cis_tag_group',
        4 => 'group_visual_identifiers',
        23 => 'group_pedagogy',
        25 => 'group_visuals',
        26 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'title' => 'ds_content',
      'body' => 'ds_content',
      'group_settings' => 'ds_content',
      'group_cis_tag_group' => 'hidden',
      'group_visual_identifiers' => 'hidden',
      'field_fa_primary_color' => 'ds_content',
      'field_fa_secondary_color' => 'ds_content',
      'field_mooc_nav_style' => 'ds_content',
      'field_mooc_nav_display' => 'ds_content',
      'field_mooc_nav_type' => 'ds_content',
      'field_mooc_nav_label' => 'ds_content',
      'field_mooc_nav_custom_text' => 'ds_content',
      'field_cis_tag' => 'ds_content',
      'hidden_nodes' => 'ds_content',
      'options' => 'ds_content',
      'group_advanced_tabs' => 'ds_content',
      'group_outline' => 'ds_content',
      'group_tag' => 'ds_content',
      'field_mooc_image' => 'ds_content',
      'group_author' => 'ds_content',
      'book' => 'ds_content',
      'author' => 'ds_content',
      'revision_information' => 'ds_content',
      'group_pedagogy' => 'hidden',
      'field_instructional_significance' => 'ds_content',
      'group_visuals' => 'hidden',
      '_add_existing_field' => 'hidden',
      'group_inst_strat' => 'ds_content',
      'group_interface' => 'ds_content',
      'group_topic_banner' => 'ds_content',
      'group_navigation_block' => 'ds_content',
      'group_colors' => 'ds_content',
      'group_visibility' => 'ds_content',
      'group_advanced' => 'ds_content',
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
