<?php
/**
 * @file
 * cle_critique.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_critique_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create cle_critique content'.
  $permissions['create cle_critique content'] = array(
    'name' => 'create cle_critique content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cle_critique content'.
  $permissions['delete any cle_critique content'] = array(
    'name' => 'delete any cle_critique content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cle_critique content'.
  $permissions['delete own cle_critique content'] = array(
    'name' => 'delete own cle_critique content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cle_critique content'.
  $permissions['edit any cle_critique content'] = array(
    'name' => 'edit any cle_critique content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cle_critique content'.
  $permissions['edit own cle_critique content'] = array(
    'name' => 'edit own cle_critique content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  return $permissions;
}
