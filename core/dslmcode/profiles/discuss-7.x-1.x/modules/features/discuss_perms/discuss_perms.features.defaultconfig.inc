<?php
/**
 * @file
 * discuss_perms.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function discuss_perms_defaultconfig_features() {
  return array(
    'discuss_perms' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function discuss_perms_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access harmony admin pages'.
  $permissions['access harmony admin pages'] = array(
    'name' => 'access harmony admin pages',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'access harmony rebuild actions'.
  $permissions['access harmony rebuild actions'] = array(
    'name' => 'access harmony rebuild actions',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer forum content'.
  $permissions['administer forum content'] = array(
    'name' => 'administer forum content',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer harmony settings'.
  $permissions['administer harmony settings'] = array(
    'name' => 'administer harmony settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer harmony_access settings'.
  $permissions['administer harmony_access settings'] = array(
    'name' => 'administer harmony_access settings',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_access',
  );

  // Exported permission: 'administer harmony_post entity'.
  $permissions['administer harmony_post entity'] = array(
    'name' => 'administer harmony_post entity',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer harmony_thread_types'.
  $permissions['administer harmony_thread_types'] = array(
    'name' => 'administer harmony_thread_types',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'bypass harmony forum access control'.
  $permissions['bypass harmony forum access control'] = array(
    'name' => 'bypass harmony forum access control',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'create harmony_posts'.
  $permissions['create harmony_posts'] = array(
    'name' => 'create harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'create harmony_thread harmony threads'.
  $permissions['create harmony_thread harmony threads'] = array(
    'name' => 'create harmony_thread harmony threads',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_post'.
  $permissions['delete any harmony_post'] = array(
    'name' => 'delete any harmony_post',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_post revisions'.
  $permissions['delete any harmony_post revisions'] = array(
    'name' => 'delete any harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_thread'.
  $permissions['delete any harmony_thread'] = array(
    'name' => 'delete any harmony_thread',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_post revisions'.
  $permissions['delete own harmony_post revisions'] = array(
    'name' => 'delete own harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_posts'.
  $permissions['delete own harmony_posts'] = array(
    'name' => 'delete own harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_threads'.
  $permissions['delete own harmony_threads'] = array(
    'name' => 'delete own harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'disable new harmony content'.
  $permissions['disable new harmony content'] = array(
    'name' => 'disable new harmony content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit any harmony_post'.
  $permissions['edit any harmony_post'] = array(
    'name' => 'edit any harmony_post',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit any harmony_thread'.
  $permissions['edit any harmony_thread'] = array(
    'name' => 'edit any harmony_thread',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit locked harmony_posts'.
  $permissions['edit locked harmony_posts'] = array(
    'name' => 'edit locked harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit locked harmony_threads'.
  $permissions['edit locked harmony_threads'] = array(
    'name' => 'edit locked harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit own harmony_posts'.
  $permissions['edit own harmony_posts'] = array(
    'name' => 'edit own harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit own harmony_threads'.
  $permissions['edit own harmony_threads'] = array(
    'name' => 'edit own harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'flag harmony_likes'.
  $permissions['flag harmony_likes'] = array(
    'name' => 'flag harmony_likes',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'rebuild harmony_access records'.
  $permissions['rebuild harmony_access records'] = array(
    'name' => 'rebuild harmony_access records',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_access',
  );

  // Exported permission: 'reply as new harmony_thread'.
  $permissions['reply as new harmony_thread'] = array(
    'name' => 'reply as new harmony_thread',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'revert any harmony_post revisions'.
  $permissions['revert any harmony_post revisions'] = array(
    'name' => 'revert any harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'revert own harmony_post revisions'.
  $permissions['revert own harmony_post revisions'] = array(
    'name' => 'revert own harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'unflag harmony_likes'.
  $permissions['unflag harmony_likes'] = array(
    'name' => 'unflag harmony_likes',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use text format harmony_filtered'.
  $permissions['use text format harmony_filtered'] = array(
    'name' => 'use text format harmony_filtered',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view harmony_post revisions'.
  $permissions['view harmony_post revisions'] = array(
    'name' => 'view harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view harmony_posts'.
  $permissions['view harmony_posts'] = array(
    'name' => 'view harmony_posts',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view harmony_threads'.
  $permissions['view harmony_threads'] = array(
    'name' => 'view harmony_threads',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own harmony_post revisions'.
  $permissions['view own harmony_post revisions'] = array(
    'name' => 'view own harmony_post revisions',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own unpublished harmony_posts'.
  $permissions['view own unpublished harmony_posts'] = array(
    'name' => 'view own unpublished harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own unpublished harmony_threads'.
  $permissions['view own unpublished harmony_threads'] = array(
    'name' => 'view own unpublished harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view unpublished harmony_posts'.
  $permissions['view unpublished harmony_posts'] = array(
    'name' => 'view unpublished harmony_posts',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view unpublished harmony_threads'.
  $permissions['view unpublished harmony_threads'] = array(
    'name' => 'view unpublished harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'harmony_core',
  );

  return $permissions;
}
