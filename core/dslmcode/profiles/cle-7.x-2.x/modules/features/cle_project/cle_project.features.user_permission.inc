<?php
/**
 * @file
 * cle_project.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_project_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create cle_project content'.
  $permissions['create cle_project content'] = array(
    'name' => 'create cle_project content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cle_project content'.
  $permissions['delete any cle_project content'] = array(
    'name' => 'delete any cle_project content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cle_project content'.
  $permissions['delete own cle_project content'] = array(
    'name' => 'delete own cle_project content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cle_project content'.
  $permissions['edit any cle_project content'] = array(
    'name' => 'edit any cle_project content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cle_project content'.
  $permissions['edit own cle_project content'] = array(
    'name' => 'edit own cle_project content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  return $permissions;
}
