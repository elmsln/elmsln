<?php
/**
 * @file
 * cis_service_roles.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cis_service_roles_user_default_roles() {
  $roles = array();

  // Exported role: guest.
  $roles['guest'] = array(
    'name' => 'guest',
    'weight' => '3',
  );

  // Exported role: instructor.
  $roles['instructor'] = array(
    'name' => 'instructor',
    'weight' => '6',
  );

  // Exported role: past student.
  $roles['past student'] = array(
    'name' => 'past student',
    'weight' => '2',
  );

  // Exported role: staff.
  $roles['staff'] = array(
    'name' => 'staff',
    'weight' => '7',
  );

  // Exported role: student.
  $roles['student'] = array(
    'name' => 'student',
    'weight' => '4',
  );

  // Exported role: teaching assistant.
  $roles['teaching assistant'] = array(
    'name' => 'teaching assistant',
    'weight' => '5',
  );

  return $roles;
}
