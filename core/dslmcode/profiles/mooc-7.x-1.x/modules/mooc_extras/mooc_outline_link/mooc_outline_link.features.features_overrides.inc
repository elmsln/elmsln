<?php
/**
 * @file
 * mooc_outline_link.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_outline_link_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: variable
  $overrides["variable.book_allowed_types.value|0"] = 'mooc_link';
  $overrides["variable.book_allowed_types.value|1"] = 'page';

 return $overrides;
}
