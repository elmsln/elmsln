<?php
/**
 * @file
 * elmsmedia_image.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsmedia_image_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create bulk photo nodes'.
  $permissions['create bulk photo nodes'] = array(
    'name' => 'create bulk photo nodes',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'bulk_photo_nodes',
  );

  return $permissions;
}
