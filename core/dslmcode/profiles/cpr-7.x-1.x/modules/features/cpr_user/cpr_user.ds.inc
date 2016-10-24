<?php
/**
 * @file
 * cpr_user.ds.inc
 */

/**
 * Implements hook_ds_layout_settings_info().
 */
function cpr_user_ds_layout_settings_info() {
  $export = array();

  $ds_layout = new stdClass();
  $ds_layout->api_version = 1;
  $ds_layout->id = 'user|user|form';
  $ds_layout->entity_type = 'user';
  $ds_layout->bundle = 'user';
  $ds_layout->view_mode = 'form';
  $ds_layout->layout = 'ds_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'header' => array(
        0 => 'account',
        1 => 'group_account_details',
      ),
      'left' => array(
        2 => 'group_personal',
        11 => 'field_display_name',
        12 => 'group_profile_name',
        13 => 'field_first_name',
        14 => 'field_last_name',
        15 => 'group_profile_photo',
        16 => 'group_bio',
        17 => 'field_photo',
        18 => 'field_bio',
      ),
      'right' => array(
        3 => 'group_preferences',
        7 => 'field_accessibility_preference',
      ),
      'footer' => array(
        4 => 'group_profile_admin',
        6 => 'wysiwyg',
        8 => 'timezone',
        9 => 'masquerade',
        10 => 'og_user_node1',
      ),
      'hidden' => array(
        5 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'account' => 'header',
      'group_account_details' => 'header',
      'group_personal' => 'left',
      'group_preferences' => 'right',
      'group_profile_admin' => 'footer',
      '_add_existing_field' => 'hidden',
      'wysiwyg' => 'footer',
      'field_accessibility_preference' => 'right',
      'timezone' => 'footer',
      'masquerade' => 'footer',
      'og_user_node1' => 'footer',
      'field_display_name' => 'left',
      'group_profile_name' => 'left',
      'field_first_name' => 'left',
      'field_last_name' => 'left',
      'group_profile_photo' => 'left',
      'group_bio' => 'left',
      'field_photo' => 'left',
      'field_bio' => 'left',
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
  $export['user|user|form'] = $ds_layout;

  return $export;
}
