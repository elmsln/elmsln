<?php
/**
 * @file
 * mooc_container_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_container_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function mooc_container_type_node_info() {
  $items = array(
    'mooc_container' => array(
      'name' => t('Container'),
      'base' => 'node_content',
      'description' => t('Purely navigational element. This type doesn\'t have content of its own, it is used to structure and present other content.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
