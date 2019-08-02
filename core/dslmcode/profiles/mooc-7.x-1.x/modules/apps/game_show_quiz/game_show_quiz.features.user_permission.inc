<?php
/**
 * @file
 * game_show_quiz.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function game_show_quiz_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access game-show-scoreboard app'.
  $permissions['access game-show-scoreboard app'] = array(
    'name' => 'access game-show-scoreboard app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  return $permissions;
}
