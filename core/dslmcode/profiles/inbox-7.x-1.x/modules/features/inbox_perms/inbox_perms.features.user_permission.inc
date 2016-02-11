<?php
/**
 * @file
 * inbox_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function inbox_perms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create inbox_event content'.
  $permissions['create inbox_event content'] = array(
    'name' => 'create inbox_event content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any inbox_event content'.
  $permissions['delete any inbox_event content'] = array(
    'name' => 'delete any inbox_event content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own inbox_event content'.
  $permissions['delete own inbox_event content'] = array(
    'name' => 'delete own inbox_event content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any inbox_event content'.
  $permissions['edit any inbox_event content'] = array(
    'name' => 'edit any inbox_event content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own inbox_event content'.
  $permissions['edit own inbox_event content'] = array(
    'name' => 'edit own inbox_event content',
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
