<?php
/**
 * @file
 * elmsmedia_section_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsmedia_section_perms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer group'.
  $permissions['administer group'] = array(
    'name' => 'administer group',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'og',
  );

  return $permissions;
}
