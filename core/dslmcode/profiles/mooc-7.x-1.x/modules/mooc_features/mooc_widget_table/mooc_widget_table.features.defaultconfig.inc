<?php
/**
 * @file
 * mooc_widget_table.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function mooc_widget_table_defaultconfig_features() {
  return array(
    'mooc_widget_table' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function mooc_widget_table_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'configure tablefield'.
  $permissions['configure tablefield'] = array(
    'name' => 'configure tablefield',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'tablefield',
  );

  // Exported permission: 'create mooc_table content'.
  $permissions['create mooc_table content'] = array(
    'name' => 'create mooc_table content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any mooc_table content'.
  $permissions['delete any mooc_table content'] = array(
    'name' => 'delete any mooc_table content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own mooc_table content'.
  $permissions['delete own mooc_table content'] = array(
    'name' => 'delete own mooc_table content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any mooc_table content'.
  $permissions['edit any mooc_table content'] = array(
    'name' => 'edit any mooc_table content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own mooc_table content'.
  $permissions['edit own mooc_table content'] = array(
    'name' => 'edit own mooc_table content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'export tablefield'.
  $permissions['export tablefield'] = array(
    'name' => 'export tablefield',
    'roles' => array(
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'tablefield',
  );

  // Exported permission: 'rebuild tablefield'.
  $permissions['rebuild tablefield'] = array(
    'name' => 'rebuild tablefield',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'tablefield',
  );

  return $permissions;
}
