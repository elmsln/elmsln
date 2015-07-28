<?php
/**
 * @file
 * discuss_displays.features.inc
 */

/**
 * Implements hook_views_api().
 */
function discuss_displays_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_views_default_views_alter().
 */
function discuss_displays_views_default_views_alter(&$data) {
  if (isset($data['harmony_thread_listing'])) {
    $data['harmony_thread_listing']->display['page_1']->display_options['menu']['name'] = 'menu-discuss-navigation'; /* WAS: '' */
    $data['harmony_thread_listing']->display['page_1']->display_options['menu']['title'] = 'All Discussion boards'; /* WAS: 'Forum' */
    $data['harmony_thread_listing']->display['page_1']->display_options['title'] = 'Discussion Boards'; /* WAS: 'Forum' */
  }
}
