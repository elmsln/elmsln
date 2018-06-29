<?php
/**
 * @file
 * cis_ux.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cis_ux_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access lrnapp-cis app'.
  $permissions['access lrnapp-cis app'] = array(
    'name' => 'access lrnapp-cis app',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  return $permissions;
}
