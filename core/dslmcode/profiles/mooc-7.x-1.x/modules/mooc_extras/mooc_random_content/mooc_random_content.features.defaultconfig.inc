<?php
/**
 * @file
 * mooc_random_content.features.defaultconfig.inc
 */

/**
 * Implements hook_defaultconfig_features().
 */
function mooc_random_content_defaultconfig_features() {
  return array(
    'mooc_random_content' => array(
      'strongarm' => 'strongarm',
      'user_default_permissions' => 'user_default_permissions',
    ),
  );
}

/**
 * Implements hook_defaultconfig_strongarm().
 */
function mooc_random_content_defaultconfig_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_elmsln_random_content';
  $strongarm->value = 'edit-wysiwyg-template';
  $export['additional_settings__active_tab_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_elmsln_random_content';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_elmsln_random_content';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_elmsln_random_content';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'field_bundle_settings_node__elmsln_random_content';
  $strongarm->value = array(
    'view_modes' => array(),
    'extra_fields' => array(
      'form' => array(
        'title' => array(
          'weight' => '-5',
        ),
      ),
      'display' => array(),
    ),
  );
  $export['field_bundle_settings_node__elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_elmsln_random_content';
  $strongarm->value = array();
  $export['menu_options_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_elmsln_random_content';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_elmsln_random_content';
  $strongarm->value = array(
    0 => 'status',
    1 => 'revision',
  );
  $export['node_options_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_elmsln_random_content';
  $strongarm->value = '0';
  $export['node_preview_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_elmsln_random_content';
  $strongarm->value = 0;
  $export['node_submitted_elmsln_random_content'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_elmsln_random_content';
  $strongarm->value = '';
  $export['wysiwyg_template_default_elmsln_random_content'] = $strongarm;

  return $export;
}

/**
 * Implements hook_defaultconfig_user_default_permissions().
 */
function mooc_random_content_defaultconfig_user_default_permissions() {
  $permissions = array();

  // Exported permission: 'create elmsln_random_content content'.
  $permissions['create elmsln_random_content content'] = array(
    'name' => 'create elmsln_random_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete any elmsln_random_content content'.
  $permissions['delete any elmsln_random_content content'] = array(
    'name' => 'delete any elmsln_random_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'delete own elmsln_random_content content'.
  $permissions['delete own elmsln_random_content content'] = array(
    'name' => 'delete own elmsln_random_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit any elmsln_random_content content'.
  $permissions['edit any elmsln_random_content content'] = array(
    'name' => 'edit any elmsln_random_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  // Exported permission: 'edit own elmsln_random_content content'.
  $permissions['edit own elmsln_random_content content'] = array(
    'name' => 'edit own elmsln_random_content content',
    'roles' => array(
      'administrator' => 'administrator',
      'instructor' => 'instructor',
      'staff' => 'staff',
    ),
    'module' => 'node',
  );

  return $permissions;
}
