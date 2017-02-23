<?php
/**
 * @file
 * mooc_flag.features.inc
 */

/**
 * Implements hook_views_api().
 */
function mooc_flag_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags_alter().
 */
function mooc_flag_flag_default_flags_alter(&$data) {
  if (isset($data['bookmarks'])) {
    $data['bookmarks']['flag_long'] = 'Bookmark this'; /* WAS: 'Add this post to your bookmarks' */
    $data['bookmarks']['flag_message'] = ''; /* WAS: 'This post has been added to your bookmarks' */
    $data['bookmarks']['unflag_long'] = 'Remove from bookmarks'; /* WAS: 'Remove this post from your bookmarks' */
    $data['bookmarks']['unflag_message'] = ''; /* WAS: 'This post has been removed from your bookmarks' */
    unset($data['bookmarks']['types'][0]);
    unset($data['bookmarks']['types'][1]);
  }
}

/**
 * Implements hook_strongarm_alter().
 */
function mooc_flag_strongarm_alter(&$data) {
  if (isset($data['field_bundle_settings_node__page'])) {
    $data['field_bundle_settings_node__page']->value['extra_fields']['display']['flag_bookmarks'] = array(
      'default' => array(
        'weight' => 0,
        'visible' => TRUE,
      ),
    ); /* WAS: '' */
  }
}

/**
 * Implements hook_flag_default_flags().
 */
function mooc_flag_flag_default_flags() {
  $flags = array();
  // Exported flag: "Bookmarks".
  $flags['bookmarks'] = array(
    'entity_type' => 'node',
    'title' => 'Bookmarks',
    'global' => 0,
    'types' => array(),
    'flag_short' => 'Bookmark this',
    'flag_long' => 'Bookmark this',
    'flag_message' => '',
    'unflag_short' => 'Unbookmark this',
    'unflag_long' => 'Remove from bookmarks',
    'unflag_message' => '',
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
    'module' => 'mooc_flag',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 3,
  );
  return $flags;

}
