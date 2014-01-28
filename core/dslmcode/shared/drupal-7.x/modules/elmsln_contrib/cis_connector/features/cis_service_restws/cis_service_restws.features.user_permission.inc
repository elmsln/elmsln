<?php
/**
 * @file
 * cis_service_restws.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cis_service_restws_user_default_permissions() {
  $permissions = array();

  // Exported permission: access resource node.
  $permissions['access resource node'] = array(
    'name' => 'access resource node',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
    ),
    'module' => 'restws',
  );

  return $permissions;
}
