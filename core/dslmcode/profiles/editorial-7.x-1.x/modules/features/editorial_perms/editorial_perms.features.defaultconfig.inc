<?php
/**
 * @file
 * editorial_perms.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function editorial_perms_defaultconfig_features() {
  return array(
    'editorial_perms' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function editorial_perms_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

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

  // Exported permission: 'create editorial_journal_entry content'.
  $permissions['create editorial_journal_entry content'] = array(
    'name' => 'create editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'create story_seeds content'.
  $permissions['create story_seeds content'] = array(
    'name' => 'create story_seeds content',
    'roles' => array(),
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

  // Exported permission: 'delete any editorial_journal_entry content'.
  $permissions['delete any editorial_journal_entry content'] = array(
    'name' => 'delete any editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any story_seeds content'.
  $permissions['delete any story_seeds content'] = array(
    'name' => 'delete any story_seeds content',
    'roles' => array(),
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

  // Exported permission: 'delete own editorial_journal_entry content'.
  $permissions['delete own editorial_journal_entry content'] = array(
    'name' => 'delete own editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own story_seeds content'.
  $permissions['delete own story_seeds content'] = array(
    'name' => 'delete own story_seeds content',
    'roles' => array(),
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

  // Exported permission: 'edit any editorial_journal_entry content'.
  $permissions['edit any editorial_journal_entry content'] = array(
    'name' => 'edit any editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any story_seeds content'.
  $permissions['edit any story_seeds content'] = array(
    'name' => 'edit any story_seeds content',
    'roles' => array(),
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

  // Exported permission: 'edit own editorial_journal_entry content'.
  $permissions['edit own editorial_journal_entry content'] = array(
    'name' => 'edit own editorial_journal_entry content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own story_seeds content'.
  $permissions['edit own story_seeds content'] = array(
    'name' => 'edit own story_seeds content',
    'roles' => array(),
    'module' => 'node',
  );

  // Exported permission: 'view own unpublished content'.
  $permissions['view own unpublished content'] = array(
    'name' => 'view own unpublished content',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'node',
  );

  return $permissions;
}
