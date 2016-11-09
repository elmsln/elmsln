<?php
/**
 * @file
 * cle_encyclopedia.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_encyclopedia_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create cle_encyclopedia_entry content'.
  $permissions['create cle_encyclopedia_entry content'] = array(
    'name' => 'create cle_encyclopedia_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any cle_encyclopedia_entry content'.
  $permissions['delete any cle_encyclopedia_entry content'] = array(
    'name' => 'delete any cle_encyclopedia_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own cle_encyclopedia_entry content'.
  $permissions['delete own cle_encyclopedia_entry content'] = array(
    'name' => 'delete own cle_encyclopedia_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cle_encyclopedia_entry content'.
  $permissions['edit any cle_encyclopedia_entry content'] = array(
    'name' => 'edit any cle_encyclopedia_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cle_encyclopedia_entry content'.
  $permissions['edit own cle_encyclopedia_entry content'] = array(
    'name' => 'edit own cle_encyclopedia_entry content',
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
