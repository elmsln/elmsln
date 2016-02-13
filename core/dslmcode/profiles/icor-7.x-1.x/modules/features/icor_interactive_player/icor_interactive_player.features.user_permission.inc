<?php
/**
 * @file
 * icor_interactive_player.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function icor_interactive_player_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create icor_interactive_player content'.
  $permissions['create icor_interactive_player content'] = array(
    'name' => 'create icor_interactive_player content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any icor_interactive_player content'.
  $permissions['delete any icor_interactive_player content'] = array(
    'name' => 'delete any icor_interactive_player content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own icor_interactive_player content'.
  $permissions['delete own icor_interactive_player content'] = array(
    'name' => 'delete own icor_interactive_player content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any icor_interactive_player content'.
  $permissions['edit any icor_interactive_player content'] = array(
    'name' => 'edit any icor_interactive_player content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own icor_interactive_player content'.
  $permissions['edit own icor_interactive_player content'] = array(
    'name' => 'edit own icor_interactive_player content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  return $permissions;
}
