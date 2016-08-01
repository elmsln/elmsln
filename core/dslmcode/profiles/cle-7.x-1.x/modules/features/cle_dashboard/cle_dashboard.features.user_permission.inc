<?php
/**
 * @file
 * cle_dashboard.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_dashboard_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access cle dashboard'.
  $permissions['access cle dashboard'] = array(
    'name' => 'access cle dashboard',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'cle_dashboard',
  );

  return $permissions;
}
