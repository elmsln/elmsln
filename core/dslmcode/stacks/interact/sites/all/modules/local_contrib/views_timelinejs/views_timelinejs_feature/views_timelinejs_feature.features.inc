<?php
/**
 * @file
 * views_timelinejs_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function views_timelinejs_feature_ctools_plugin_api($module = NULL, $api = NULL) {
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
function views_timelinejs_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function views_timelinejs_feature_node_info() {
  $items = array(
    'timeline_date' => array(
      'name' => t('Timeline Date'),
      'base' => 'node_content',
      'description' => t('A <em>timeline date</em> is an event on a timeline. This content type is optimized for use with Timeline JS.'),
      'has_title' => '1',
      'title_label' => t('Headline'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
