<?php
/**
 * @file
 * mooc_ux_defaults.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mooc_ux_defaults_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer simplify'.
  $permissions['administer simplify'] = array(
    'name' => 'administer simplify',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplify',
  );

  // Exported permission: 'view hidden fields'.
  $permissions['view hidden fields'] = array(
    'name' => 'view hidden fields',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplify',
  );

  return $permissions;
}
