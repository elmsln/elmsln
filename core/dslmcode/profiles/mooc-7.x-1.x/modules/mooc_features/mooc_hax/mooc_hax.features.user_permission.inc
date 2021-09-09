<?php

/**
 * @file
 * mooc_hax.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function mooc_hax_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer haxcms settings'.
  $permissions['administer haxcms settings'] = array(
    'name' => 'administer haxcms settings',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'haxcms',
  );

  // Exported permission: 'use hax'.
  $permissions['use hax'] = array(
    'name' => 'use hax',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'hax',
  );

  return $permissions;
}
