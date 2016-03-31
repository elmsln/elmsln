<?php
/**
 * @file
 * elmsln_student_filter.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsln_student_filter_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format student_format'.
  $permissions['use text format student_format'] = array(
    'name' => 'use text format student_format',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
