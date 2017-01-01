<?php
/**
 * @file
 * mooc_textbook.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_textbook_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function mooc_textbook_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_filter_default_formats_alter().
 */
function mooc_textbook_filter_default_formats_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['filters']['cis_filter'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -49,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['filter_footnotes'] = array(
      'settings' => array(
        'footnotes_collapse' => 0,
      ),
      'status' => 1,
      'weight' => -40,
    ); /* WAS: '' */
    $data['textbook_editor']['filters']['filter_tokens'] = array(
      'settings' => array(),
      'status' => 1,
      'weight' => -42,
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_wysiwyg_default_profiles_alter().
 */
function mooc_textbook_wysiwyg_default_profiles_alter(&$data) {
  if (isset($data['textbook_editor'])) {
    $data['textbook_editor']['settings']['buttons']['drupal'] = array(
      'rendered_entity' => 1,
    ); /* WAS: '' */
    $data['textbook_editor']['settings']['buttons']['footnotes'] = array(
      'footnotes' => 1,
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function mooc_textbook_flag_default_flags() {
  $flags = array();
  // Exported flag: "Bookmarks".
  $flags['bookmarks'] = array(
    'entity_type' => 'node',
    'title' => 'Bookmarks',
    'global' => 0,
    'types' => array(
      0 => 'mooc_container',
      1 => 'page',
    ),
    'flag_short' => 'Bookmark this',
    'flag_long' => 'Add this post to your bookmarks',
    'flag_message' => 'This post has been added to your bookmarks',
    'unflag_short' => 'Unbookmark this',
    'unflag_long' => 'Remove this post from your bookmarks',
    'unflag_message' => 'This post has been removed from your bookmarks',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'weight' => 0,
    'show_in_links' => array(
      'full' => 'full',
      'teaser' => 'teaser',
      'rss' => 0,
      'print' => 0,
      'diff_standard' => 0,
      'iframe' => 0,
      'token' => 0,
      'revision' => 0,
    ),
    'show_as_field' => 1,
    'show_on_form' => 1,
    'access_author' => '',
    'show_contextual_link' => 0,
    'i18n' => 0,
    'api_version' => 3,
    'module' => 'mooc_textbook',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
