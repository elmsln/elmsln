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

  // Exported permission: 'switch section context'.
  $permissions['switch section context'] = array(
    'name' => 'switch section context',
    'roles' => array(
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'cis_service_connection',
  );

  return $permissions;
}
