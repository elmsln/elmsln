<?php
/**
 * @file
 * mooc_textbook_nrhi.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_textbook_nrhi_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|nrhi"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -42,
  );
 return $overrides;
}
