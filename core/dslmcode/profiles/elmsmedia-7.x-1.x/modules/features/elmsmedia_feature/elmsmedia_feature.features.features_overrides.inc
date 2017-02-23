<?php
/**
 * @file
 * elmsmedia_feature.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function elmsmedia_feature_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.cache"] = 1;
  $overrides["filter.textbook_editor.filters|cis_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -49,
  );
  $overrides["filter.textbook_editor.filters|ckeditor_link_filter|weight"] = -46;
  $overrides["filter.textbook_editor.filters|filter_htmlcorrector|weight"] = -47;
  $overrides["filter.textbook_editor.filters|video_filter|weight"] = -50;

 return $overrides;
}
