<?php
/**
 * @file
 * mooc_helper.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function mooc_helper_user_default_roles() {
  $roles = array();

  // Exported role: activation code holder.
  $roles['activation code holder'] = array(
    'name' => 'activation code holder',
    'weight' => 10,
    'machine_name' => 'activation_code_holder',
  );

  return $roles;
}
