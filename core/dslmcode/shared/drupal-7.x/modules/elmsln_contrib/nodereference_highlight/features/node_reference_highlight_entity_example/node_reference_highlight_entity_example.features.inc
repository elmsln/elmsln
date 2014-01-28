<?php
/**
 * @file
 * node_reference_highlight_entity_example.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function node_reference_highlight_entity_example_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function node_reference_highlight_entity_example_node_info() {
  $items = array(
    'nrhi_person' => array(
      'name' => t('Person'),
      'base' => 'node_content',
      'description' => t('An example person type'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
