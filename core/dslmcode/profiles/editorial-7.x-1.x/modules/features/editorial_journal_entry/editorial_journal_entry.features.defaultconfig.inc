<?php
/**
 * @file
 * editorial_journal_entry.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function editorial_journal_entry_defaultconfig_features() {
  return array(
    'editorial_journal_entry' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function editorial_journal_entry_defaultconfig_user_default_permissions() {
  $permissions = array();

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

  return $permissions;
}
