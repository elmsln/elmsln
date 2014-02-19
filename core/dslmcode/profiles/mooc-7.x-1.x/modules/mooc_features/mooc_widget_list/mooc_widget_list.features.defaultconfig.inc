<?php
/**
 * @file
 * mooc_widget_list.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function mooc_widget_list_defaultconfig_features() {
  return array(
    'mooc_widget_list' => array(
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function mooc_widget_list_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create mooc_list_widget content'.
  $permissions['create mooc_list_widget content'] = array(
    'name' => 'create mooc_list_widget content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any mooc_list_widget content'.
  $permissions['delete any mooc_list_widget content'] = array(
    'name' => 'delete any mooc_list_widget content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own mooc_list_widget content'.
  $permissions['delete own mooc_list_widget content'] = array(
    'name' => 'delete own mooc_list_widget content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any mooc_list_widget content'.
  $permissions['edit any mooc_list_widget content'] = array(
    'name' => 'edit any mooc_list_widget content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own mooc_list_widget content'.
  $permissions['edit own mooc_list_widget content'] = array(
    'name' => 'edit own mooc_list_widget content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  return $permissions;
}
