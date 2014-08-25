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
    'weight' => -50,
  );
  $overrides["filter.textbook_editor.filters|filter_footnotes"] = array(
    'settings' => array(
      'footnotes_collapse' => 0,
    ),
    'status' => 1,
    'weight' => -20,
  );
  $overrides["filter.textbook_editor.filters|filter_html|settings|allowed_html"] = '<div> <legend> <fieldset> <h2> <h3> <h4> <h5> <h6> <em> <iframe> <video> <strong> <img> <br> <blockquote> <cite> <sup> <sub> <p> <ul> <ol> <li> <dl> <dt> <dd> <a> <table> <tr> <td> <th> <tbody> <thead> <tfoot> <colgroup> <caption> <hr> <fn>';
  $overrides["filter.textbook_editor.filters|filter_html|weight"] = -49;
  $overrides["filter.textbook_editor.filters|filter_tokens"] = array(
    'settings' => array(),
    'status' => 1,
    'weight' => -44,
  );
  $overrides["filter.textbook_editor.filters|typogrify|weight"] = -43;

  // Exported overrides for: wysiwyg
  $overrides["wysiwyg.textbook_editor.settings|buttons|drupal"] = array(
    'rendered_entity' => 1,
    'token_insert_wysiwyg' => 1,
  );
  $overrides["wysiwyg.textbook_editor.settings|buttons|footnotes"] = array(
    'footnotes' => 1,
  );

 return $overrides;
}
