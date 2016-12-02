<?php
/**
 * @file
 * mooc_markdown.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_markdown_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.git_book_markdown.filters|cis_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => 10,
  );

 return $overrides;
}
