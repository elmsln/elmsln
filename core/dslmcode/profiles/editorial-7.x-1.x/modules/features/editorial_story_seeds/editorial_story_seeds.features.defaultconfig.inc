<?php
/**
 * @file
 * editorial_story_seeds.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function editorial_story_seeds_defaultconfig_features() {
  return array(
    'editorial_story_seeds' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function editorial_story_seeds_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create editorial_story_seeds content'.
  $permissions['create editorial_story_seeds content'] = array(
    'name' => 'create editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any editorial_story_seeds content'.
  $permissions['delete any editorial_story_seeds content'] = array(
    'name' => 'delete any editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own editorial_story_seeds content'.
  $permissions['delete own editorial_story_seeds content'] = array(
    'name' => 'delete own editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any editorial_story_seeds content'.
  $permissions['edit any editorial_story_seeds content'] = array(
    'name' => 'edit any editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own editorial_story_seeds content'.
  $permissions['edit own editorial_story_seeds content'] = array(
    'name' => 'edit own editorial_story_seeds content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  return $permissions;
}
