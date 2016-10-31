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

  // Exported permission: 'access resource node'.
  $permissions['access resource node'] = array(
    'name' => 'access resource node',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'restws',
  );

  return $permissions;
}
