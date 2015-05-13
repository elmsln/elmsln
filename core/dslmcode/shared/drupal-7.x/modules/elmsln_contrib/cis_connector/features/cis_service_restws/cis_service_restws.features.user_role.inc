<?php
/**
 * @file
 * cis_service_restws.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function cis_service_restws_user_default_roles() {
  $roles = array();

  // Exported role: SERVICE ACCOUNT.
  $roles['SERVICE ACCOUNT'] = array(
    'name' => 'SERVICE ACCOUNT',
    'weight' => 11,
  );

  return $roles;
}
