<?php
/**
 * @file
 * editorial_perms.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function editorial_perms_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create editorial_blog_post content'
  $permissions['node:section:create editorial_blog_post content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:create editorial_journal_entry content'
  $permissions['node:section:create editorial_journal_entry content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:delete any editorial_blog_post content'
  $permissions['node:section:delete any editorial_blog_post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete any editorial_journal_entry content'
  $permissions['node:section:delete any editorial_journal_entry content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete own editorial_blog_post content'
  $permissions['node:section:delete own editorial_blog_post content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:delete own editorial_journal_entry content'
  $permissions['node:section:delete own editorial_journal_entry content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:update any editorial_blog_post content'
  $permissions['node:section:update any editorial_blog_post content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update any editorial_journal_entry content'
  $permissions['node:section:update any editorial_journal_entry content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update own editorial_blog_post content'
  $permissions['node:section:update own editorial_blog_post content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:update own editorial_journal_entry content'
  $permissions['node:section:update own editorial_journal_entry content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  return $permissions;
}
