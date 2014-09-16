<?php
/**
 * @file
 * views_timelinejs_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function views_timelinejs_feature_views_api() {
  return array("version" => "3.0");
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
  return $items;
}
