<?php
/**
 * @file
 * cis_account_required.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_account_required_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.access content.roles|anonymous user"]["DELETED"] = TRUE;
  $overrides["user_permission.view regions_right_slideout region.roles|anonymous user"]["DELETED"] = TRUE;

 return $overrides;
}
