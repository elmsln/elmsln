<?php
/**
 * @file
 * book_player.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function book_player_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access lrnapp-book app'.
  $permissions['access lrnapp-book app'] = array(
    'name' => 'access lrnapp-book app',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  return $permissions;
}
