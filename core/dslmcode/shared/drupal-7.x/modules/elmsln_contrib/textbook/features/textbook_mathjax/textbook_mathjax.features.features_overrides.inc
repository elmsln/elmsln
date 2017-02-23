<?php
/**
 * @file
 * textbook_mathjax.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function textbook_mathjax_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|filter_mathjax"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => 50,
  );

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|mathjax"] = array(
    'Mathjax' => 1,
  );

 return $overrides;
}
