<?php
/**
 * @file
 * mooc_cis_ux.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mooc_cis_ux_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer read time'.
  $permissions['administer read time'] = array(
    'name' => 'administer read time',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'read_time',
  );

  // Exported permission: 'view read time'.
  $permissions['view read time'] = array(
    'name' => 'view read time',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'read_time',
  );

  return $permissions;
}
