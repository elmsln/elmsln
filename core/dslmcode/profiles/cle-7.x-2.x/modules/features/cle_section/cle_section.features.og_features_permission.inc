<?php
/**
 * @file
 * cle_section.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function cle_section_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create cle_assignment content'
  $permissions['node:section:create cle_assignment content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:create cle_project content'
  $permissions['node:section:create cle_project content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:create cle_submission content'
  $permissions['node:section:create cle_submission content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_assignment content'
  $permissions['node:section:delete any cle_assignment content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_project content'
  $permissions['node:section:delete any cle_project content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete any cle_submission content'
  $permissions['node:section:delete any cle_submission content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own cle_assignment content'
  $permissions['node:section:delete own cle_assignment content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own cle_project content'
  $permissions['node:section:delete own cle_project content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:delete own cle_submission content'
  $permissions['node:section:delete own cle_submission content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  // Exported og permission: 'node:section:update any cle_assignment content'
  $permissions['node:section:update any cle_assignment content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update any cle_project content'
  $permissions['node:section:update any cle_project content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update any cle_submission content'
  $permissions['node:section:update any cle_submission content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own cle_assignment content'
  $permissions['node:section:update own cle_assignment content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own cle_project content'
  $permissions['node:section:update own cle_project content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
    ),
  );

  // Exported og permission: 'node:section:update own cle_submission content'
  $permissions['node:section:update own cle_submission content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
      'administrator member' => 'administrator member',
      'member' => 'member',
    ),
  );

  return $permissions;
}
