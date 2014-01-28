<?php
/**
 * @file
 * cis_users.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cis_users_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_user__user';
  $strongarm->value = array(
    'view_modes' => array(
      'full' => array(
        'custom_settings' => 'false',
      ),
      'token' => array(
        'custom_settings' => 'false',
      ),
    ),
    'extra_fields' => array(
      'form' => array(
        'account' => array(
          'weight' => '0',
        ),
        'timezone' => array(
          'weight' => '7',
        ),
        'picture' => array(
          'weight' => '1',
        ),
        'overlay_control' => array(
          'weight' => '6',
        ),
        'wysiwyg' => array(
          'weight' => '5',
        ),
      ),
      'display' => array(
        'summary' => array(
          'default' => 'array (',
        ),
      ),
    ),
  );
  $export['field_bundle_settings_user__user'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_user_delete_hide_button';
  $strongarm->value = '1';
  $export['jammer_user_delete_hide_button'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'lti_tool_provider_user_attribute_mapping';
  $strongarm->value = array(
    'lis_person_name_given' => 'field_first_name',
    'lis_person_name_family' => 'field_last_name',
    'lis_person_name_full' => 'none',
  );
  $export['lti_tool_provider_user_attribute_mapping'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'nodeaccess_userreference';
  $strongarm->value = array(
    'academic_unit' => array(
      'field_unit_head' => array(
        'referenced' => array(
          'update' => 'update',
        ),
        'author' => array(
          'update' => 'update',
        ),
        'all' => array(
          'view' => 'view',
        ),
        'unused' => '1',
      ),
      'field_coordinators' => array(
        'referenced' => array(
          'update' => 'update',
        ),
        'author' => array(
          'update' => 'update',
        ),
        'all' => array(
          'view' => 'view',
        ),
        'unused' => '1',
      ),
    ),
  );
  $export['nodeaccess_userreference'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_admin_role';
  $strongarm->value = '3';
  $export['user_admin_role'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'user_cancel_method';
  $strongarm->value = 'user_cancel_block';
  $export['user_cancel_method'] = $strongarm;

  return $export;
}
