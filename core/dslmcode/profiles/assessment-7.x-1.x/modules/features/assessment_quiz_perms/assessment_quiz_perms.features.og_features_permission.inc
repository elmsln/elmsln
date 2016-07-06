<?php
/**
 * @file
 * assessment_quiz_perms.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function assessment_quiz_perms_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create quiz content'
  $permissions['node:section:create quiz content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete any quiz content'
  $permissions['node:section:delete any quiz content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete own quiz content'
  $permissions['node:section:delete own quiz content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update any quiz content'
  $permissions['node:section:update any quiz content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update own quiz content'
  $permissions['node:section:update own quiz content'] = array(
    'roles' => array(
      'administrator member' => 'administrator member',
    ),
  );

  return $permissions;
}
