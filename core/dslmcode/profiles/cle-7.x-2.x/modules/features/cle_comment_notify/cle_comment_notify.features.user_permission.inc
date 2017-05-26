<?php
/**
 * @file
 * cle_comment_notify.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_comment_notify_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer comment notify'.
  $permissions['administer comment notify'] = array(
    'name' => 'administer comment notify',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'comment_notify',
  );

  // Exported permission: 'subscribe to comments'.
  $permissions['subscribe to comments'] = array(
    'name' => 'subscribe to comments',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'comment_notify',
  );

  return $permissions;
}
