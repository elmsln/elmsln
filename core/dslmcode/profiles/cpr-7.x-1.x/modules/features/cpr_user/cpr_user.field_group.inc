<?php
/**
 * @file
 * cpr_user.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function cpr_user_field_group_info() {
  $field_groups = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_account_details|user|user|form';
  $field_group->group_name = 'group_account_details';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Account details',
    'weight' => '0',
    'children' => array(
      0 => 'account',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Account details',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-account-details field-group-fieldset',
        'description' => 'User account settings',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_account_details|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_bio|user|user|form';
  $field_group->group_name = 'group_bio';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_personal';
  $field_group->data = array(
    'label' => 'Bio',
    'weight' => '12',
    'children' => array(
      0 => 'field_bio',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Bio',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-bio field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_bio|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_personal|user|user|form';
  $field_group->group_name = 'group_personal';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Personal',
    'weight' => '1',
    'children' => array(
      0 => 'group_bio',
      1 => 'group_profile_name',
      2 => 'group_profile_photo',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Personal',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-personal field-group-fieldset',
        'description' => 'Personal profile',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_personal|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_preferences|user|user|form';
  $field_group->group_name = 'group_preferences';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Preferences',
    'weight' => '2',
    'children' => array(
      0 => 'field_accessibility_preference',
      1 => 'field_media_preference',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Preferences',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-preferences field-group-fieldset',
        'description' => 'Content, media and system preferences.',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_preferences|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_admin|user|user|form';
  $field_group->group_name = 'group_profile_admin';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Admin',
    'weight' => '3',
    'children' => array(
      0 => 'masquerade',
      1 => 'timezone',
      2 => 'wysiwyg',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Admin',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-profile-admin field-group-fieldset',
        'description' => 'Administration settings about a user',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_profile_admin|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_name|user|user|form';
  $field_group->group_name = 'group_profile_name';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_personal';
  $field_group->data = array(
    'label' => 'Name',
    'weight' => '10',
    'children' => array(
      0 => 'field_display_name',
      1 => 'field_first_name',
      2 => 'field_last_name',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Name',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-profile-name field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_profile_name|user|user|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_profile_photo|user|user|form';
  $field_group->group_name = 'group_profile_photo';
  $field_group->entity_type = 'user';
  $field_group->bundle = 'user';
  $field_group->mode = 'form';
  $field_group->parent_name = 'group_personal';
  $field_group->data = array(
    'label' => 'Photo',
    'weight' => '11',
    'children' => array(
      0 => 'field_photo',
      1 => 'field_banner_pic',
      2 => 'picture',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Photo',
      'instance_settings' => array(
        'required_fields' => 1,
        'id' => '',
        'classes' => 'group-profile-photo field-group-fieldset',
        'description' => '',
      ),
      'formatter' => 'collapsed',
    ),
  );
  $field_groups['group_profile_photo|user|user|form'] = $field_group;

  // Translatables
  // Included for use with string extractors like potx.
  t('Account details');
  t('Admin');
  t('Bio');
  t('Name');
  t('Personal');
  t('Photo');
  t('Preferences');

  return $field_groups;
}
