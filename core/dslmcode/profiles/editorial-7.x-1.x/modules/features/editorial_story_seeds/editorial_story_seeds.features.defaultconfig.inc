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
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function editorial_story_seeds_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_editorial_story_seeds';
  $strongarm->value = array(
    0 => 'main-menu',
  );
  $export['menu_options_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_editorial_story_seeds';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_editorial_story_seeds';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_editorial_story_seeds';
  $strongarm->value = '0';
  $export['node_preview_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_editorial_story_seeds';
  $strongarm->value = 1;
  $export['node_submitted_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'save_continue_story_seeds';
  $strongarm->value = 'Save and add fields';
  $export['save_continue_story_seeds'] = $strongarm;

  return $export;
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
