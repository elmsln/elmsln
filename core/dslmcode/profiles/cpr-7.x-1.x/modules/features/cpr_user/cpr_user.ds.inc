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
  $ds_layout->layout = 'zf_2col_stacked';
  $ds_layout->settings = array(
    'regions' => array(
      'left' => array(
        0 => 'group_account_details',
        3 => 'group_profile_admin',
        4 => 'og_user_node',
        5 => 'timezone',
        7 => 'account',
        9 => 'wysiwyg',
        10 => 'masquerade',
      ),
      'right' => array(
        1 => 'group_personal',
        2 => 'group_preferences',
        6 => 'field_accessibility_preference',
        8 => 'field_media_preference',
        11 => 'field_display_name',
        12 => 'field_first_name',
        13 => 'group_profile_name',
        14 => 'field_last_name',
        15 => 'group_profile_photo',
        16 => 'group_bio',
        17 => 'field_photo',
        18 => 'picture',
        19 => 'field_bio',
      ),
      'hidden' => array(
        20 => '_add_existing_field',
      ),
    ),
    'fields' => array(
      'group_account_details' => 'left',
      'group_personal' => 'right',
      'group_preferences' => 'right',
      'group_profile_admin' => 'left',
      'og_user_node' => 'left',
      'timezone' => 'left',
      'field_accessibility_preference' => 'right',
      'account' => 'left',
      'field_media_preference' => 'right',
      'wysiwyg' => 'left',
      'masquerade' => 'left',
      'field_display_name' => 'right',
      'field_first_name' => 'right',
      'group_profile_name' => 'right',
      'field_last_name' => 'right',
      'group_profile_photo' => 'right',
      'group_bio' => 'right',
      'field_photo' => 'right',
      'picture' => 'right',
      'field_bio' => 'right',
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
  );
  $export['user|user|form'] = $ds_layout;

  return $export;
}
