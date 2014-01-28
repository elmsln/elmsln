<?php
/**
 * @file
 * cis_service_icor.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function cis_service_icor_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|icor"] = array(
    'icor' => 1,
  );

  return $overrides;
}
