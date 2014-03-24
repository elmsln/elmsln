<?php
/**
 * @file
 * icor_timeline_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_timeline_type_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function icor_timeline_type_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function icor_timeline_type_node_info() {
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
  return $items;
}
