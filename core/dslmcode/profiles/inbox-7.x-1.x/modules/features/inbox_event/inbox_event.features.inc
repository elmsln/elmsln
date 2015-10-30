<?php
/**
 * @file
 * inbox_event.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function inbox_event_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function inbox_event_node_info() {
  $items = array(
    'inbox_event' => array(
      'name' => t('Inbox Event'),
      'base' => 'node_content',
      'description' => t('An actionable event for students which should appear in their inbox in a timely manner.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
