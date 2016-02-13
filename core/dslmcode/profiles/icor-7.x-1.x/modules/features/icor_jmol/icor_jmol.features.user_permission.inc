<?php
/**
 * @file
 * icor_jmol.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function icor_jmol_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create jmol content'.
  $permissions['create jmol content'] = array(
    'name' => 'create jmol content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any jmol content'.
  $permissions['delete any jmol content'] = array(
    'name' => 'delete any jmol content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own jmol content'.
  $permissions['delete own jmol content'] = array(
    'name' => 'delete own jmol content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any jmol content'.
  $permissions['edit any jmol content'] = array(
    'name' => 'edit any jmol content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own jmol content'.
  $permissions['edit own jmol content'] = array(
    'name' => 'edit own jmol content',
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
