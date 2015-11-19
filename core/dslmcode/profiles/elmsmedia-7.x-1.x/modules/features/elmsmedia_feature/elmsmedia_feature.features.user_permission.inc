<?php
/**
 * @file
 * elmsmedia_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsmedia_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access view mode tab'.
  $permissions['access view mode tab'] = array(
    'name' => 'access view mode tab',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'view_mode_tab',
  );

  // Exported permission: 'administer svg sanitizer'.
  $permissions['administer svg sanitizer'] = array(
    'name' => 'administer svg sanitizer',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'svg_sanitizer',
  );

  // Exported permission: 'administer view mode tab'.
  $permissions['administer view mode tab'] = array(
    'name' => 'administer view mode tab',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'view_mode_tab',
  );

  // Exported permission: 'create svg content'.
  $permissions['create svg content'] = array(
    'name' => 'create svg content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any svg content'.
  $permissions['delete any svg content'] = array(
    'name' => 'delete any svg content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own svg content'.
  $permissions['delete own svg content'] = array(
    'name' => 'delete own svg content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any svg content'.
  $permissions['edit any svg content'] = array(
    'name' => 'edit any svg content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own svg content'.
  $permissions['edit own svg content'] = array(
    'name' => 'edit own svg content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  return $permissions;
}
