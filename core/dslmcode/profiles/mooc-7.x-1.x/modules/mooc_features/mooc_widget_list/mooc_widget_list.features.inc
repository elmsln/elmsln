<?php
/**
 * @file
 * mooc_widget_list.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_widget_list_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function mooc_widget_list_node_info() {
  $items = array(
    'mooc_list_widget' => array(
      'name' => t('MOOC List Widget'),
      'base' => 'node_content',
      'description' => t('Special listing widget to display field information either as tabs or fieldsets'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
