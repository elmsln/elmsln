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
        9 => 'field_display_name',
        10 => 'group_profile_name',
        11 => 'field_first_name',
        12 => 'group_profile_photo',
        13 => 'field_last_name',
        14 => 'group_bio',
        15 => 'field_bio',
        16 => 'field_photo',
        17 => 'field_user_photo',
        18 => 'field_user_banner',
      ),
      'right' => array(
        3 => 'group_preferences',
        7 => 'field_accessibility_preference',
      ),
      'footer' => array(
        4 => 'group_profile_admin',
        5 => 'wysiwyg',
        6 => 'timezone',
        8 => 'og_user_node',
        19 => 'masquerade',
      ),
      'hidden' => array(
        20 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'account' => 'header',
      'group_account_details' => 'header',
      'group_personal' => 'left',
      'group_preferences' => 'right',
      'group_profile_admin' => 'footer',
      'wysiwyg' => 'footer',
      'timezone' => 'footer',
      'field_accessibility_preference' => 'right',
      'og_user_node' => 'footer',
      'field_display_name' => 'left',
      'group_profile_name' => 'left',
      'field_first_name' => 'left',
      'group_profile_photo' => 'left',
      'field_last_name' => 'left',
      'group_bio' => 'left',
      'field_bio' => 'left',
      'field_photo' => 'left',
      'field_user_photo' => 'left',
      'field_user_banner' => 'left',
      'masquerade' => 'footer',
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
  $export['user|user|form'] = $ds_layout;

  return $export;
}
