<?php
/**
 * @file
 * elmsmedia_h5p.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function elmsmedia_h5p_defaultconfig_features() {
  return array(
    'elmsmedia_h5p' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function elmsmedia_h5p_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'h5p_copyright';
  $strongarm->value = 1;
  $export['h5p_copyright'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'h5p_embed';
  $strongarm->value = 0;
  $export['h5p_embed'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'h5p_export';
  $strongarm->value = 0;
  $export['h5p_export'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'h5p_frame';
  $strongarm->value = 1;
  $export['h5p_frame'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'h5p_icon_in_action_bar';
  $strongarm->value = 0;
  $export['h5p_icon_in_action_bar'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function elmsmedia_h5p_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access all h5p results'.
  $permissions['access all h5p results'] = array(
    'name' => 'access all h5p results',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'h5p',
  );

  // Exported permission: 'access h5p results for own content'.
  $permissions['access h5p results for own content'] = array(
    'name' => 'access h5p results for own content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'h5p',
  );

  // Exported permission: 'access own h5p results'.
  $permissions['access own h5p results'] = array(
    'name' => 'access own h5p results',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'h5p',
  );

  // Exported permission: 'create h5p_content content'.
  $permissions['create h5p_content content'] = array(
    'name' => 'create h5p_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create restricted h5p content types'.
  $permissions['create restricted h5p content types'] = array(
    'name' => 'create restricted h5p content types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'h5p',
  );

  // Exported permission: 'delete any h5p_content content'.
  $permissions['delete any h5p_content content'] = array(
    'name' => 'delete any h5p_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own h5p_content content'.
  $permissions['delete own h5p_content content'] = array(
    'name' => 'delete own h5p_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any h5p_content content'.
  $permissions['edit any h5p_content content'] = array(
    'name' => 'edit any h5p_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own h5p_content content'.
  $permissions['edit own h5p_content content'] = array(
    'name' => 'edit own h5p_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'update h5p libraries'.
  $permissions['update h5p libraries'] = array(
    'name' => 'update h5p libraries',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'h5p',
  );

  return $permissions;
}
