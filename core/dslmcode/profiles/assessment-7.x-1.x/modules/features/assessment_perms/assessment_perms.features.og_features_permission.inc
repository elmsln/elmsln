<?php
/**
 * @file
 * assessment_perms.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function assessment_perms_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create assessment_assignment content'
  $permissions['node:section:create assessment_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete any assessment_assignment content'
  $permissions['node:section:delete any assessment_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own assessment_assignment content'
  $permissions['node:section:delete own assessment_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update any assessment_assignment content'
  $permissions['node:section:update any assessment_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own assessment_assignment content'
  $permissions['node:section:update own assessment_assignment content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
