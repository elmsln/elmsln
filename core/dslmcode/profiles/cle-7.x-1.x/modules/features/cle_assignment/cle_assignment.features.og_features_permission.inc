<?php
/**
 * @file
 * cle_assignment.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cle_assignment_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create cle_assignment content'
  $permissions['node:section:create cle_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_assignment content'
  $permissions['node:section:delete any cle_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own cle_assignment content'
  $permissions['node:section:delete own cle_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update any cle_assignment content'
  $permissions['node:section:update any cle_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own cle_assignment content'
  $permissions['node:section:update own cle_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
