<?php
/**
 * @file
 * discuss_displays.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function discuss_displays_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: views_view
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|menu|name"] = 'menu-discuss-navigation';
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|menu|title"] = 'All Discussion boards';
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|title"] = 'Discussion Boards';

 return $overrides;
}
