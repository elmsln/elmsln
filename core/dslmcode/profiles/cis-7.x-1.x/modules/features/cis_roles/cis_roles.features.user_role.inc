<?php
/**
 * @file
 * cis_roles.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cis_roles_user_default_roles() {
  $roles = array();

  // Exported role: Coordinator.
  $roles['Coordinator'] = array(
    'name' => 'Coordinator',
    'weight' => 7,
  );

  // Exported role: Dean.
  $roles['Dean'] = array(
    'name' => 'Dean',
    'weight' => 4,
  );

  // Exported role: Instructor.
  $roles['Instructor'] = array(
    'name' => 'Instructor',
    'weight' => 6,
  );

  // Exported role: Learning Designer.
  $roles['Learning Designer'] = array(
    'name' => 'Learning Designer',
    'weight' => 8,
  );

  // Exported role: SERVICE ACCOUNT.
  $roles['SERVICE ACCOUNT'] = array(
    'name' => 'SERVICE ACCOUNT',
    'weight' => 11,
  );

  // Exported role: Staff.
  $roles['Staff'] = array(
    'name' => 'Staff',
    'weight' => 9,
  );

  // Exported role: Teaching Assistant.
  $roles['Teaching Assistant'] = array(
    'name' => 'Teaching Assistant',
    'weight' => 2,
  );

  // Exported role: Unit Head.
  $roles['Unit Head'] = array(
    'name' => 'Unit Head',
    'weight' => 5,
  );

  // Exported role: administrator.
  $roles['administrator'] = array(
    'name' => 'administrator',
    'weight' => 10,
  );

  return $roles;
}
