<?php
/**
 * @file
 * cle_gradebook_ux.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_gradebook_ux_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access gradebook'.
  $permissions['access gradebook'] = array(
    'name' => 'access gradebook',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'cle_gradebook',
  );

  return $permissions;
}
