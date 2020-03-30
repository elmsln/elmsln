<?php
/**
 * @file
 * mooc_hax.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_hax_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|webcomponents_cmstags"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -50,
  );
  $overrides["filter.textbook_editor.filters|webcomponents_cmstags_jsonfix"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -50,
  );

 return $overrides;
}
