<?php

/**
 * @file
 * date_test_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function date_test_feature_node_info() {
  $items = array(
    'date_test' => array(
      'name' => t('Date Test'),
      'base' => 'node_content',
      'description' => t('This content type is used for demonstrating and testing migration into Date fields.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );

  // Trigger hook_node_info_alter().
  drupal_alter('node_info', $items);

  return $items;
}
