<?php

/**
 * @file
 * date_all_day_test_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function date_all_day_test_feature_node_info() {
  $items = array(
    'date_all_day_test' => array(
      'name' => t('Date Test'),
      'base' => 'node_content',
      'description' => t('This content type is used for testing the Date All Day module.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );

  // Trigger hook_node_info_alter().
  drupal_alter('node_info', $items);

  return $items;
}
