<?php
/**
 * @file
 * cle_critique.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cle_critique_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create cle_critique content'
  $permissions['node:section:create cle_critique content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_critique content'
  $permissions['node:section:delete any cle_critique content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete own cle_critique content'
  $permissions['node:section:delete own cle_critique content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update any cle_critique content'
  $permissions['node:section:update any cle_critique content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update own cle_critique content'
  $permissions['node:section:update own cle_critique content'] = array(
    'roles' => array(
      'member' => 'member',
    ),
  );

  return $permissions;
}
