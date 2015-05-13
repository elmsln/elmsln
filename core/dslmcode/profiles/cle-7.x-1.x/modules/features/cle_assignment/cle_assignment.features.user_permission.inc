<?php
/**
 * @file
 * cle_assignment.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_assignment_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create cle_assignment content'.
  $permissions['create cle_assignment content'] = array(
    'name' => 'create cle_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cle_assignment content'.
  $permissions['delete any cle_assignment content'] = array(
    'name' => 'delete any cle_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cle_assignment content'.
  $permissions['delete own cle_assignment content'] = array(
    'name' => 'delete own cle_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cle_assignment content'.
  $permissions['edit any cle_assignment content'] = array(
    'name' => 'edit any cle_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cle_assignment content'.
  $permissions['edit own cle_assignment content'] = array(
    'name' => 'edit own cle_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  return $permissions;
}
