<?php
/**
 * @file
 * yuml_type.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function yuml_type_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function yuml_type_node_info() {
  $items = array(
    'yuml_type' => array(
      'name' => t('YUML'),
      'base' => 'node_content',
      'description' => t('Yuml content type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
