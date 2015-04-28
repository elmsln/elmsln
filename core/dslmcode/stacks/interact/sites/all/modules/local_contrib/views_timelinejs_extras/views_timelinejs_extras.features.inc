<?php
/**
 * @file
 * views_timelinejs_extras.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function views_timelinejs_extras_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function views_timelinejs_extras_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function views_timelinejs_extras_node_info() {
  $items = array(
    'timeline' => array(
      'name' => t('Timeline'),
      'base' => 'node_content',
      'description' => t('Select the timeline Dates you want to display on a single timeline.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
