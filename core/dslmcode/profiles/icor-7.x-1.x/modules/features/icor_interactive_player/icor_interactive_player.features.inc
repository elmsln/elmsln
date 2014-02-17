<?php
/**
 * @file
 * icor_interactive_player.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_interactive_player_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function icor_interactive_player_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function icor_interactive_player_node_info() {
  $items = array(
    'icor_interactive_player' => array(
      'name' => t('Interactive Player'),
      'base' => 'node_content',
      'description' => t('A list of items that the user can page through in order to make up one chain of interactive items.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
