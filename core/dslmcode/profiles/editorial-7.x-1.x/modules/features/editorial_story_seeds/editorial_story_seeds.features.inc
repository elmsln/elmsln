<?php
/**
 * @file
 * editorial_story_seeds.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function editorial_story_seeds_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function editorial_story_seeds_node_info() {
  $items = array(
    'editorial_story_seeds' => array(
      'name' => t('Story Seeds'),
      'base' => 'node_content',
      'description' => t('Story Seeds'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
