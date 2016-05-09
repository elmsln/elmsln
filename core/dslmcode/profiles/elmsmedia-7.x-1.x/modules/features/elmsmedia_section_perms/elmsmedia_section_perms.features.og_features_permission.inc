<?php
/**
 * @file
 * elmsmedia_section_perms.features.og_features_permission.inc
 */

/**
 * Implements hook_og_features_default_permissions().
 */
function elmsmedia_section_perms_og_features_default_permissions() {
  $permissions = array();

  // Exported og permission: 'node:section:create audio content'
  $permissions['node:section:create audio content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create document content'
  $permissions['node:section:create document content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create elmsmedia_image content'
  $permissions['node:section:create elmsmedia_image content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create external_video content'
  $permissions['node:section:create external_video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create figurelabel content'
  $permissions['node:section:create figurelabel content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create svg content'
  $permissions['node:section:create svg content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:create video content'
  $permissions['node:section:create video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any audio content'
  $permissions['node:section:delete any audio content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any document content'
  $permissions['node:section:delete any document content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any elmsmedia_image content'
  $permissions['node:section:delete any elmsmedia_image content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any external_video content'
  $permissions['node:section:delete any external_video content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any figurelabel content'
  $permissions['node:section:delete any figurelabel content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any svg content'
  $permissions['node:section:delete any svg content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete any video content'
  $permissions['node:section:delete any video content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own audio content'
  $permissions['node:section:delete own audio content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own document content'
  $permissions['node:section:delete own document content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own elmsmedia_image content'
  $permissions['node:section:delete own elmsmedia_image content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own external_video content'
  $permissions['node:section:delete own external_video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own figurelabel content'
  $permissions['node:section:delete own figurelabel content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own svg content'
  $permissions['node:section:delete own svg content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:delete own video content'
  $permissions['node:section:delete own video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any audio content'
  $permissions['node:section:update any audio content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any document content'
  $permissions['node:section:update any document content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any elmsmedia_image content'
  $permissions['node:section:update any elmsmedia_image content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any external_video content'
  $permissions['node:section:update any external_video content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any figurelabel content'
  $permissions['node:section:update any figurelabel content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any svg content'
  $permissions['node:section:update any svg content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update any video content'
  $permissions['node:section:update any video content'] = array(
    'roles' => array(
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own audio content'
  $permissions['node:section:update own audio content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own document content'
  $permissions['node:section:update own document content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own elmsmedia_image content'
  $permissions['node:section:update own elmsmedia_image content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own external_video content'
  $permissions['node:section:update own external_video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own figurelabel content'
  $permissions['node:section:update own figurelabel content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own svg content'
  $permissions['node:section:update own svg content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  // Exported og permission: 'node:section:update own video content'
  $permissions['node:section:update own video content'] = array(
    'roles' => array(
      'Faculty' => 'Faculty',
      'Lead Faculty' => 'Lead Faculty',
    ),
  );

  return $permissions;
}
