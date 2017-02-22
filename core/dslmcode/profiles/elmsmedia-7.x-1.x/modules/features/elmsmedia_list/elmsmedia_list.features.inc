<?php
/**
 * @file
 * elmsmedia_list.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_list_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function elmsmedia_list_node_info() {
  $items = array(
    'elmsmedia_list' => array(
      'name' => t('Media list'),
      'base' => 'node_content',
      'description' => t('A list of any kind of element in the system, useful for forming playlists and random media widgets.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
