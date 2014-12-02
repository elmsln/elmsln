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
  $overrides["filter.textbook_editor.filters|ckeditor_link_filter|weight"] = -45;
  $overrides["filter.textbook_editor.filters|filter_footnotes"] = array(
    'settings' => array(
      'footnotes_collapse' => 0,
    ),
    'status' => 1,
    'weight' => -39,
  );
  $overrides["filter.textbook_editor.filters|filter_tokens"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -42,
  );
  $overrides["filter.textbook_editor.filters|shortcode"] = array(
    'settings' => array(
      'box' => 1,
      'button' => 1,
      'col' => 1,
      'contact' => 1,
      'divider' => 1,
      'dropcap' => 1,
      'dropshadow' => 1,
      'highlight' => 1,
      'icon-list' => 0,
      'social' => 1,
      'teaser' => 0,
      'toggle' => 0,
    ),
    'status' => 1,
    'weight' => -46,
  );
  $overrides["filter.textbook_editor.filters|shortcode_text_corrector"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -47,
  );
  $overrides["filter.textbook_editor.filters|typogrify|weight"] = -41;

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|drupal"] = array(
    'rendered_entity' => 1,
    'shortcode_wysiwyg' => 1,
    'token_insert_wysiwyg' => 1,
  );
  $overrides["wysiwyg.textbook_editor.settings|buttons|footnotes"] = array(
    'footnotes' => 1,
  );

 return $overrides;
}
