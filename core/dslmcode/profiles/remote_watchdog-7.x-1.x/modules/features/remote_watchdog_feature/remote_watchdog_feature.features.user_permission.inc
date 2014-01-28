<?php
/**
 * @file
 * remote_watchdog_feature.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function remote_watchdog_feature_user_default_permissions() {
  $permissions = array();

  // Exported permission: access resource watchdog.
  $permissions['access resource watchdog'] = array(
    'name' => 'access resource watchdog',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
    ),
    'module' => 'restws',
  );

  // Exported permission: access site reports.
  $permissions['access site reports'] = array(
    'name' => 'access site reports',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: delete entity_watchdog.
  $permissions['delete entity_watchdog'] = array(
    'name' => 'delete entity_watchdog',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'entity_watchdog',
  );

  // Exported permission: view entity_watchdog.
  $permissions['view entity_watchdog'] = array(
    'name' => 'view entity_watchdog',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'entity_watchdog',
  );

  return $permissions;
}
