<?php
/**
 * @file
 * elmsln_core.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function elmsln_core_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'access admin theme'.
  $permissions['access admin theme'] = array(
    'name' => 'access admin theme',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'admin_theme',
  );

  // Exported permission: 'access administration menu'.
  $permissions['access administration menu'] = array(
    'name' => 'access administration menu',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'access administration pages'.
  $permissions['access administration pages'] = array(
    'name' => 'access administration pages',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'system',
  );

  // Exported permission: 'access ckeditor link'.
  $permissions['access ckeditor link'] = array(
    'name' => 'access ckeditor link',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'ckeditor_link',
  );

  // Exported permission: 'access elmsln administration areas'.
  $permissions['access elmsln administration areas'] = array(
    'name' => 'access elmsln administration areas',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'elmsln_core',
  );

  // Exported permission: 'access iframe version'.
  $permissions['access iframe version'] = array(
    'name' => 'access iframe version',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'entity_iframe',
  );

  // Exported permission: 'administer cis lms-less nav'.
  $permissions['administer cis lms-less nav'] = array(
    'name' => 'administer cis lms-less nav',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'cis_lmsless_nav',
  );

  // Exported permission: 'administer masquerade'.
  $permissions['administer masquerade'] = array(
    'name' => 'administer masquerade',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'administer site configuration'.
  $permissions['administer site configuration'] = array(
    'name' => 'administer site configuration',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'system',
  );

  // Exported permission: 'bypass node access'.
  $permissions['bypass node access'] = array(
    'name' => 'bypass node access',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete revisions'.
  $permissions['delete revisions'] = array(
    'name' => 'delete revisions',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'flush caches'.
  $permissions['flush caches'] = array(
    'name' => 'flush caches',
    'roles' => array(
      'administrator' => 'administrator',
      'staff' => 'staff',
    ),
    'module' => 'admin_menu',
  );

  // Exported permission: 'masquerade as admin'.
  $permissions['masquerade as admin'] = array(
    'name' => 'masquerade as admin',
    'roles' => array(
      'administrator' => 'administrator',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as any user'.
  $permissions['masquerade as any user'] = array(
    'name' => 'masquerade as any user',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'masquerade as user'.
  $permissions['masquerade as user'] = array(
    'name' => 'masquerade as user',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'masquerade',
  );

  // Exported permission: 'revert revisions'.
  $permissions['revert revisions'] = array(
    'name' => 'revert revisions',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'show format selection for node'.
  $permissions['show format selection for node'] = array(
    'name' => 'show format selection for node',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'better_formats',
  );

  // Exported permission: 'switch section context'.
  $permissions['switch section context'] = array(
    'name' => 'switch section context',
    'roles' => array(
      'administrator' => 'administrator',
      'guest' => 'guest',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'cis_service_connection',
  );

  // Exported permission: 'use text format textbook_editor'.
  $permissions['use text format textbook_editor'] = array(
    'name' => 'use text format textbook_editor',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'filter',
  );

  // Exported permission: 'view a11y simulations'.
  $permissions['view a11y simulations'] = array(
    'name' => 'view a11y simulations',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'a11y',
  );

  // Exported permission: 'view cis shortcode'.
  $permissions['view cis shortcode'] = array(
    'name' => 'view cis shortcode',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'cis_shortcodes',
  );

  // Exported permission: 'view iframe embed code'.
  $permissions['view iframe embed code'] = array(
    'name' => 'view iframe embed code',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'entity_iframe',
  );

  // Exported permission: 'view lmsless administration links'.
  $permissions['view lmsless administration links'] = array(
    'name' => 'view lmsless administration links',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
      'teaching assistant' => 'teaching assistant',
    ),
    'module' => 'cis_lmsless',
  );

  // Exported permission: 'view lmsless bar'.
  $permissions['view lmsless bar'] = array(
    'name' => 'view lmsless bar',
    'roles' => array(
      'administrator' => 'administrator',
      'anonymous user' => 'anonymous user',
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'cis_lmsless',
  );

  // Exported permission: 'view revisions'.
  $permissions['view revisions'] = array(
    'name' => 'view revisions',
    'roles' => array(
      'SERVICE ACCOUNT' => 'SERVICE ACCOUNT',
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'view the administration theme'.
  $permissions['view the administration theme'] = array(
    'name' => 'view the administration theme',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'system',
  );

  return $permissions;
}
