<?php
/**
 * @file
 * harmony_default_permissions.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function harmony_default_permissions_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access harmony_post show replies'.
  $permissions['access harmony_post show replies'] = array(
    'name' => 'access harmony_post show replies',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer harmony forum content'.
  $permissions['administer harmony forum content'] = array(
    'name' => 'administer harmony forum content',
    'roles' => array(
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

  // Exported permission: 'administer harmony_post entity'.
  $permissions['administer harmony_post entity'] = array(
    'name' => 'administer harmony_post entity',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'administer harmony_thread_types'.
  $permissions['administer harmony_thread_types'] = array(
    'name' => 'administer harmony_thread_types',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'bypass harmony forum access control'.
  $permissions['bypass harmony forum access control'] = array(
    'name' => 'bypass harmony forum access control',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'create harmony_posts'.
  $permissions['create harmony_posts'] = array(
    'name' => 'create harmony_posts',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'create harmony_thread harmony threads'.
  $permissions['create harmony_thread harmony threads'] = array(
    'name' => 'create harmony_thread harmony threads',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_post'.
  $permissions['delete any harmony_post'] = array(
    'name' => 'delete any harmony_post',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_post revisions'.
  $permissions['delete any harmony_post revisions'] = array(
    'name' => 'delete any harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete any harmony_thread'.
  $permissions['delete any harmony_thread'] = array(
    'name' => 'delete any harmony_thread',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_post revisions'.
  $permissions['delete own harmony_post revisions'] = array(
    'name' => 'delete own harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_posts'.
  $permissions['delete own harmony_posts'] = array(
    'name' => 'delete own harmony_posts',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'delete own harmony_threads'.
  $permissions['delete own harmony_threads'] = array(
    'name' => 'delete own harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit any harmony_post'.
  $permissions['edit any harmony_post'] = array(
    'name' => 'edit any harmony_post',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit any harmony_thread'.
  $permissions['edit any harmony_thread'] = array(
    'name' => 'edit any harmony_thread',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit locked harmony_posts'.
  $permissions['edit locked harmony_posts'] = array(
    'name' => 'edit locked harmony_posts',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit locked harmony_threads'.
  $permissions['edit locked harmony_threads'] = array(
    'name' => 'edit locked harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit own harmony_posts'.
  $permissions['edit own harmony_posts'] = array(
    'name' => 'edit own harmony_posts',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'edit own harmony_threads'.
  $permissions['edit own harmony_threads'] = array(
    'name' => 'edit own harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'flag harmony_likes'.
  $permissions['flag harmony_likes'] = array(
    'name' => 'flag harmony_likes',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'reply as new harmony_thread'.
  $permissions['reply as new harmony_thread'] = array(
    'name' => 'reply as new harmony_thread',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'revert any harmony_post revisions'.
  $permissions['revert any harmony_post revisions'] = array(
    'name' => 'revert any harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'revert own harmony_post revisions'.
  $permissions['revert own harmony_post revisions'] = array(
    'name' => 'revert own harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'unflag harmony_likes'.
  $permissions['unflag harmony_likes'] = array(
    'name' => 'unflag harmony_likes',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'flag',
  );

  // Exported permission: 'use text format harmony_filtered'.
  $permissions['use text format harmony_filtered'] = array(
    'name' => 'use text format harmony_filtered',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view harmony_post revisions'.
  $permissions['view harmony_post revisions'] = array(
    'name' => 'view harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view harmony_posts'.
  $permissions['view harmony_posts'] = array(
    'name' => 'view harmony_posts',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view harmony_threads'.
  $permissions['view harmony_threads'] = array(
    'name' => 'view harmony_threads',
    'roles' => array(
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own harmony_post revisions'.
  $permissions['view own harmony_post revisions'] = array(
    'name' => 'view own harmony_post revisions',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own unpublished harmony_posts'.
  $permissions['view own unpublished harmony_posts'] = array(
    'name' => 'view own unpublished harmony_posts',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view own unpublished harmony_threads'.
  $permissions['view own unpublished harmony_threads'] = array(
    'name' => 'view own unpublished harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view unpublished harmony_posts'.
  $permissions['view unpublished harmony_posts'] = array(
    'name' => 'view unpublished harmony_posts',
    'roles' => array(),
    'module' => 'harmony_core',
  );

  // Exported permission: 'view unpublished harmony_threads'.
  $permissions['view unpublished harmony_threads'] = array(
    'name' => 'view unpublished harmony_threads',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'harmony_core',
  );

  return $permissions;
}
