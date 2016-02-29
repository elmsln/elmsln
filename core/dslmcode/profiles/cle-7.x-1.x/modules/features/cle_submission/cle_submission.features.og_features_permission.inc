<?php
/**
 * @file
 * cle_submission.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cle_submission_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create cle_submission content'
  $permissions['node:section:create cle_submission content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete any cle_submission content'
  $permissions['node:section:delete any cle_submission content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:delete own cle_submission content'
  $permissions['node:section:delete own cle_submission content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update any cle_submission content'
  $permissions['node:section:update any cle_submission content'] = array(
    'roles' => array(),
  );

  // Exported og permission: 'node:section:update own cle_submission content'
  $permissions['node:section:update own cle_submission content'] = array(
    'roles' => array(),
  );

  return $permissions;
}
