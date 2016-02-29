<?php
/**
 * @file
 * mooc_textbook.features.features_overrides.inc
 */

/**
 * Implements hook_features_override_default_overrides().
 */
function mooc_textbook_features_override_default_overrides() {
  // This code is only used for UI in features. Exported alters hooks do the magic.
  $overrides = array();

  // Exported overrides for: filter
  $overrides["filter.textbook_editor.filters|cis_filter"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -49,
  );
  $overrides["filter.textbook_editor.filters|ckeditor_link_filter|weight"] = -44;
  $overrides["filter.textbook_editor.filters|filter_footnotes"] = array(
    'settings' => array(
      'footnotes_collapse' => 0,
    ),
    'status' => 1,
    'weight' => -40,
  );
  $overrides["filter.textbook_editor.filters|filter_tokens"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -42,
  );

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|drupal"] = array(
    'rendered_entity' => 1,
  );
  $overrides["wysiwyg.textbook_editor.settings|buttons|footnotes"] = array(
    'footnotes' => 1,
  );

 return $overrides;
}
