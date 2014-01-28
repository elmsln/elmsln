<?php
/**
 * @file
 * mooc_widget_table.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_widget_table_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function mooc_widget_table_node_info() {
  $items = array(
    'mooc_table' => array(
      'name' => t('Table type'),
      'base' => 'node_content',
      'description' => t('Type to add a well made table'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
