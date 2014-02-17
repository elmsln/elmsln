<?php
/**
 * @file
 * cle_private_files.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cle_private_files_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: field
  $overrides["field.node-cle_submission-field_images.field_config|settings|uri_scheme"] = 'private';

  return $overrides;
}
