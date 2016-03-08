<?php
/**
 * @file
 * mooc_markdown.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mooc_markdown_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'use text format git_book_markdown'.
  $permissions['use text format git_book_markdown'] = array(
    'name' => 'use text format git_book_markdown',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'filter',
  );

  return $permissions;
}
