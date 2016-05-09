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

  // Exported OG Role: 'node:section:Faculty'.
  $roles['node:section:Faculty'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'Faculty',
  );

  // Exported OG Role: 'node:section:Lead Faculty'.
  $roles['node:section:Lead Faculty'] = array(
    'gid' => 0,
    'group_type' => 'node',
    'group_bundle' => 'section',
    'name' => 'Lead Faculty',
  );

  return $roles;
}
