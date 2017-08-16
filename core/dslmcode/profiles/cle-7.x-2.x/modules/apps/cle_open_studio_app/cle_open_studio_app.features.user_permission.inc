<?php
/**
 * @file
 * cle_open_studio_app.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function cle_open_studio_app_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access lrnapp-gallery-grid app'.
  $permissions['access lrnapp-gallery-grid app'] = array(
    'name' => 'access lrnapp-gallery-grid app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  // Exported permission: 'access lrnapp-media-upload app'.
  $permissions['access lrnapp-media-upload app'] = array(
    'name' => 'access lrnapp-media-upload app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  // Exported permission: 'access lrnapp-open-studio app'.
  $permissions['access lrnapp-open-studio app'] = array(
    'name' => 'access lrnapp-open-studio app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  // Exported permission: 'access lrnapp-studio-dashboard app'.
  $permissions['access lrnapp-studio-dashboard app'] = array(
    'name' => 'access lrnapp-studio-dashboard app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  // Exported permission: 'access lrnapp-studio-kanban app'.
  $permissions['access lrnapp-studio-kanban app'] = array(
    'name' => 'access lrnapp-studio-kanban app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  // Exported permission: 'access lrnapp-studio-submission app'.
  $permissions['access lrnapp-studio-submission app'] = array(
    'name' => 'access lrnapp-studio-submission app',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'past student' => 'past student',
      'staff' => 'staff',
      'student' => 'student',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'webcomponents_app',
  );

  return $permissions;
}
