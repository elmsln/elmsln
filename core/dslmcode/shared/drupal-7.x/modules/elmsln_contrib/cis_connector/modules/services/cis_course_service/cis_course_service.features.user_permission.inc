<?php
/**
 * @file
 * cis_course_service.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cis_course_service_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create url aliases'.
  $permissions['create url aliases'] = array(
    'name' => 'create url aliases',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'path',
  );

  // Exported permission: 'notify of path changes'.
  $permissions['notify of path changes'] = array(
    'name' => 'notify of path changes',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'pathauto',
  );

  return $permissions;
}
