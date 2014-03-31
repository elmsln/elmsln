<?php
/**
 * @file
 * cis_service_restws.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_service_restws_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: user_permission
  $overrides["user_permission.access content.roles|SERVICE ACCOUNT"] = 'SERVICE ACCOUNT';
  $overrides["user_permission.bypass node access.roles|SERVICE ACCOUNT"] = 'SERVICE ACCOUNT';

  return $overrides;
}
