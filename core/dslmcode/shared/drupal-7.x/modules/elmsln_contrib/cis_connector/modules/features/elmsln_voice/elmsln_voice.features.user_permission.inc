<?php
/**
 * @file
 * elmsln_voice.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsln_voice_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access voice commander settings'.
  $permissions['access voice commander settings'] = array(
    'name' => 'access voice commander settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'voicecommander',
  );

  // Exported permission: 'use voice commander'.
  $permissions['use voice commander'] = array(
    'name' => 'use voice commander',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'voicecommander',
  );

  return $permissions;
}
