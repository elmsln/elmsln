<?php
/**
 * @file
 * cle_encyclopedia.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cle_encyclopedia_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create cle_encyclopedia_entry content'
  $permissions['node:section:create cle_encyclopedia_entry content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_encyclopedia_entry content'
  $permissions['node:section:delete any cle_encyclopedia_entry content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own cle_encyclopedia_entry content'
  $permissions['node:section:delete own cle_encyclopedia_entry content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:update any cle_encyclopedia_entry content'
  $permissions['node:section:update any cle_encyclopedia_entry content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own cle_encyclopedia_entry content'
  $permissions['node:section:update own cle_encyclopedia_entry content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
