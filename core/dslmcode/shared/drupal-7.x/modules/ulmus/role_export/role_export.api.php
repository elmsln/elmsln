<?php

/**
 * @file
 * Install, Uninstall, Schema and Update functions for role_export
 */

/**
 * Implements hook_role_export_role_id_change().
 * @param  object $role   fully loaded role object
 * @param  int    $newrid new roleid to be applied
 * @return null
 */
function hook_role_export_role_id_change($role, $newrid) {
  // change a variable to the new
  $admin_roles = variable_get('masquerade_admin_roles', array());
  foreach ($admin_roles as $key => $status) {
    if ($role->rid == $status) {
      $admin_roles[$newrid] = $newrid;
      $admin_roles[$key] = 0;
    }
  }
  variable_set('masquerade_admin_roles', $admin_roles);
}