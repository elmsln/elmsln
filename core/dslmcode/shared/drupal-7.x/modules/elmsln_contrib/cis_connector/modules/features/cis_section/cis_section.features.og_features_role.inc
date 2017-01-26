<?php
/**
 * @file
 * cis_section.features.og_features_role.inc
 */

/**
 * Implements hook_og_features_default_roles().
 */
function cis_section_og_features_default_roles() {
  $roles = array();

  // Exported OG Role: 'node:section:instructor'.
  $roles['node:section:instructor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'instructor',
  );

  // Exported OG Role: 'node:section:lead instructor'.
  $roles['node:section:lead instructor'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'lead instructor',
  );

  // Exported OG Role: 'node:section:past student'.
  $roles['node:section:past student'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'past student',
  );

  // Exported OG Role: 'node:section:staff'.
  $roles['node:section:staff'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'staff',
  );

  // Exported OG Role: 'node:section:student'.
  $roles['node:section:student'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'student',
  );

  // Exported OG Role: 'node:section:teaching assistant'.
  $roles['node:section:teaching assistant'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'teaching assistant',
  );

  return $roles;
}
