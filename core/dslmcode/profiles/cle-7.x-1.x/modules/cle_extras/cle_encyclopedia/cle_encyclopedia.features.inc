<?php
/**
 * @file
 * cle_encyclopedia.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_encyclopedia_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cle_encyclopedia_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cle_encyclopedia_node_info() {
  $items = array(
    'cle_encyclopedia_entry' => array(
      'name' => t('Encyclopedia entry'),
      'base' => 'node_content',
      'description' => t('Entry for submission into the class encyclopedia.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
