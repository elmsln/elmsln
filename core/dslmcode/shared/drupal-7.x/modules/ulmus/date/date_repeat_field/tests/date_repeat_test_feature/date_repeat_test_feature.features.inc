<?php

/**
 * @file
 * date_repeat_test_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function date_repeat_test_feature_node_info() {
  $items = array(
    'date_repeat_test' => array(
      'name' => t('Date Repeat Test'),
      'base' => 'node_content',
      'description' => t('This content type is used for demonstrating and testing migration into Date fields.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
