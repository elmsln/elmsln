<?php
/**
 * @file
 * mooc_ux_defaults.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function mooc_ux_defaults_defaultconfig_features() {
  return array(
    'mooc_ux_defaults' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function mooc_ux_defaults_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplify_blocks_global';
  $strongarm->value = array(
    0 => 'format',
  );
  $export['simplify_blocks_global'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplify_nodes_global';
  $strongarm->value = array(
    0 => 'author',
    1 => 'format',
    2 => 'revision',
    3 => 'book',
    4 => 'menu',
  );
  $export['simplify_nodes_global'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplify_user1';
  $strongarm->value = 0;
  $export['simplify_user1'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'simplify_users_global';
  $strongarm->value = array(
    0 => 'format',
  );
  $export['simplify_users_global'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function mooc_ux_defaults_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'administer simplify'.
  $permissions['administer simplify'] = array(
    'name' => 'administer simplify',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'simplify',
  );

  return $permissions;
}
