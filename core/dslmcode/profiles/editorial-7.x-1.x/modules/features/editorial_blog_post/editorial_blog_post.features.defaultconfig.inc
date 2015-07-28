<?php
/**
 * @file
 * editorial_blog_post.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function editorial_blog_post_defaultconfig_features() {
  return array(
    'editorial_blog_post' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function editorial_blog_post_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create editorial_blog_post content'.
  $permissions['create editorial_blog_post content'] = array(
    'name' => 'create editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any editorial_blog_post content'.
  $permissions['delete any editorial_blog_post content'] = array(
    'name' => 'delete any editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own editorial_blog_post content'.
  $permissions['delete own editorial_blog_post content'] = array(
    'name' => 'delete own editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any editorial_blog_post content'.
  $permissions['edit any editorial_blog_post content'] = array(
    'name' => 'edit any editorial_blog_post content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own editorial_blog_post content'.
  $permissions['edit own editorial_blog_post content'] = array(
    'name' => 'edit own editorial_blog_post content',
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
