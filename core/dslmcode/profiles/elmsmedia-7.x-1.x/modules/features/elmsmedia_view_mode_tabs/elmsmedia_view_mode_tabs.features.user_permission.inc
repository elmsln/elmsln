<?php
/**
 * @file
 * elmsmedia_view_mode_tabs.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsmedia_view_mode_tabs_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access view mode tab'.
  $permissions['access view mode tab'] = array(
    'name' => 'access view mode tab',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'view_mode_tab',
  );

  // Exported permission: 'administer view mode tab'.
  $permissions['administer view mode tab'] = array(
    'name' => 'administer view mode tab',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'view_mode_tab',
  );

  return $permissions;
}
