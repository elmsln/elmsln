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

  // Exported role: SERVICE ACCOUNT.
  $roles['SERVICE ACCOUNT'] = array(
    'name' => 'SERVICE ACCOUNT',
    'weight' => 9,
    'machine_name' => 'service_account',
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 8,
    'machine_name' => 'administrator',
  );

  // Exported role: guest.
  $roles['guest'] = array(
    'name' => 'guest',
    'weight' => 2,
    'machine_name' => 'guest',
  );

  // Exported role: instructor.
  $roles['instructor'] = array(
    'name' => 'instructor',
    'weight' => 6,
    'machine_name' => 'instructor',
  );

  // Exported role: past student.
  $roles['past student'] = array(
    'name' => 'past student',
    'weight' => 3,
    'machine_name' => 'past_student',
  );

  // Exported role: staff.
  $roles['staff'] = array(
    'name' => 'staff',
    'weight' => 7,
    'machine_name' => 'staff',
  );

  // Exported role: student.
  $roles['student'] = array(
    'name' => 'student',
    'weight' => 4,
    'machine_name' => 'student',
  );

  // Exported role: teaching assistant.
  $roles['teaching assistant'] = array(
    'name' => 'teaching assistant',
    'weight' => 5,
    'machine_name' => 'teaching_assistant',
  );

  return $roles;
}
