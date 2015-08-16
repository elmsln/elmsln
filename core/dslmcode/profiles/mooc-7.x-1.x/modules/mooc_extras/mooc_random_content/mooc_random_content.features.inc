<?php
/**
 * @file
 * mooc_random_content.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_random_content_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function mooc_random_content_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function mooc_random_content_node_info() {
  $items = array(
    'elmsln_random_content' => array(
      'name' => t('Random Content'),
      'base' => 'node_content',
      'description' => t('Random content of the day'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
