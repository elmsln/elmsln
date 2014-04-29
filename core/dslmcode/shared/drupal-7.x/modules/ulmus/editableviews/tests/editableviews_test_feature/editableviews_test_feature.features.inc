<?php
/**
 * @file
 * editableviews_test_feature.features.inc
 */

/**
 * Implements hook_views_api().
 */
function editableviews_test_feature_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function editableviews_test_feature_node_info() {
  $items = array(
    'editable_views_test_node' => array(
      'name' => t('Editable Views test node'),
      'base' => 'node_content',
      'description' => t('Test node type for Editable Views testing.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
    'editable_views_test_referencing' => array(
      'name' => t('Editable Views test referencing'),
      'base' => 'node_content',
      'description' => t('References the basic test node via an entityreference field.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
