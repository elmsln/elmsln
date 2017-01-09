<?php
/**
 * @file
 * assessment_perms.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function assessment_perms_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access content'.
  $permissions['access content'] = array(
    'name' => 'access content',
    'roles' => array(
      'administrator' => 'administrator',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: 'administer Assessment Item'.
  $permissions['administer Assessment Item'] = array(
    'name' => 'administer Assessment Item',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'assessment_item',
  );

  // Exported permission: 'administer Assessment Item types'.
  $permissions['administer Assessment Item types'] = array(
    'name' => 'administer Assessment Item types',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'assessment_item',
  );

  // Exported permission: 'create assessment_assignment content'.
  $permissions['create assessment_assignment content'] = array(
    'name' => 'create assessment_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any assessment_assignment content'.
  $permissions['delete any assessment_assignment content'] = array(
    'name' => 'delete any assessment_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own assessment_assignment content'.
  $permissions['delete own assessment_assignment content'] = array(
    'name' => 'delete own assessment_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any assessment_assignment content'.
  $permissions['edit any assessment_assignment content'] = array(
    'name' => 'edit any assessment_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any cis_course content'.
  $permissions['edit any cis_course content'] = array(
    'name' => 'edit any cis_course content',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any graded_item Assessment Item'.
  $permissions['edit any graded_item Assessment Item'] = array(
    'name' => 'edit any graded_item Assessment Item',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'assessment_item',
  );

  // Exported permission: 'edit own assessment_assignment content'.
  $permissions['edit own assessment_assignment content'] = array(
    'name' => 'edit own assessment_assignment content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own cis_course content'.
  $permissions['edit own cis_course content'] = array(
    'name' => 'edit own cis_course content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'export quiz results'.
  $permissions['export quiz results'] = array(
    'name' => 'export quiz results',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'assessment_helper',
  );

  // Exported permission: 'show format selection for assessment_item'.
  $permissions['show format selection for assessment_item'] = array(
    'name' => 'show format selection for assessment_item',
    'roles' => array(),
    'module' => 'better_formats',
  );

  // Exported permission: 'view any graded_item Assessment Item'.
  $permissions['view any graded_item Assessment Item'] = array(
    'name' => 'view any graded_item Assessment Item',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'assessment_item',
  );

  return $permissions;
}
