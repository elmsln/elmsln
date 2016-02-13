<?php
/**
 * @file
 * icor_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function icor_perms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create timeline content'.
  $permissions['create timeline content'] = array(
    'name' => 'create timeline content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create timeline_date content'.
  $permissions['create timeline_date content'] = array(
    'name' => 'create timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any timeline content'.
  $permissions['delete any timeline content'] = array(
    'name' => 'delete any timeline content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any timeline_date content'.
  $permissions['delete any timeline_date content'] = array(
    'name' => 'delete any timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own timeline content'.
  $permissions['delete own timeline content'] = array(
    'name' => 'delete own timeline content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own timeline_date content'.
  $permissions['delete own timeline_date content'] = array(
    'name' => 'delete own timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any timeline content'.
  $permissions['edit any timeline content'] = array(
    'name' => 'edit any timeline content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any timeline_date content'.
  $permissions['edit any timeline_date content'] = array(
    'name' => 'edit any timeline_date content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own timeline content'.
  $permissions['edit own timeline content'] = array(
    'name' => 'edit own timeline content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own timeline_date content'.
  $permissions['edit own timeline_date content'] = array(
    'name' => 'edit own timeline_date content',
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
