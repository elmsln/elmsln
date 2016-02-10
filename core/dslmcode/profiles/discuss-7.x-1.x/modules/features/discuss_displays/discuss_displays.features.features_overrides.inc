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
  $overrides["views_view.harmony_thread_listing.display|default|display_options|fields|field_harmony_category|exclude"] = TRUE;
  $overrides["views_view.harmony_thread_listing.display|default|display_options|fields|picture"]["DELETED"] = TRUE;
  $overrides["views_view.harmony_thread_listing.display|default|display_options|sorts|field_harmony_category_tid"] = array(
    'id' => 'field_harmony_category_tid',
    'table' => 'field_data_field_harmony_category',
    'field' => 'field_harmony_category_tid',
  );
  $overrides["views_view.harmony_thread_listing.display|default|display_options|sorts|updated"]["DELETED"] = TRUE;
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|menu|name"] = 'menu-elmsln-main-navigation';
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|menu|title"] = 'All Discussion boards';
  $overrides["views_view.harmony_thread_listing.display|page_1|display_options|title"] = 'Discussion Boards';

 return $overrides;
}
