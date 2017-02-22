<?php
/**
 * @file
 * mooc_flag.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_flag_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: flag
  $overrides["flag.bookmarks.flag_long"] = 'Bookmark this';
  $overrides["flag.bookmarks.flag_message"] = '';
  $overrides["flag.bookmarks.types|0"]["DELETED"] = TRUE;
  $overrides["flag.bookmarks.types|1"]["DELETED"] = TRUE;
  $overrides["flag.bookmarks.unflag_long"] = 'Remove from bookmarks';
  $overrides["flag.bookmarks.unflag_message"] = '';

  // Exported overrides for: variable
  $overrides["variable.field_bundle_settings_node__page.value|extra_fields|display|flag_bookmarks"] = array(
    'default' => array(
      'weight' => 0,
      'visible' => TRUE,
    ),
  );

 return $overrides;
}
