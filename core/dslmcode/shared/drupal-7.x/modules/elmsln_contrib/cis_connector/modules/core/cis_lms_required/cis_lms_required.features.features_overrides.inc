<?php
/**
 * @file
 * cis_lms_required.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_lms_required_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.access content.roles|authenticated user"]["DELETED"] = TRUE;
  $overrides["user_permission.access content.roles|guest"] = 'guest';
  $overrides["user_permission.access content.roles|instructor"] = 'instructor';
  $overrides["user_permission.access content.roles|past student"] = 'past student';
  $overrides["user_permission.access content.roles|staff"] = 'staff';
  $overrides["user_permission.access content.roles|student"] = 'student';
  $overrides["user_permission.access content.roles|teaching assistant"] = 'teaching assistant';
  $overrides["user_permission.view regions_right_slideout region.roles|authenticated user"]["DELETED"] = TRUE;
  $overrides["user_permission.view regions_right_slideout region.roles|guest"] = 'guest';
  $overrides["user_permission.view regions_right_slideout region.roles|instructor"] = 'instructor';
  $overrides["user_permission.view regions_right_slideout region.roles|past student"] = 'past student';
  $overrides["user_permission.view regions_right_slideout region.roles|staff"] = 'staff';
  $overrides["user_permission.view regions_right_slideout region.roles|student"] = 'student';
  $overrides["user_permission.view regions_right_slideout region.roles|teaching assistant"] = 'teaching assistant';

 return $overrides;
}
