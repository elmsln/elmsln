<?php
/**
 * @file
 * features_extra_test.features.fe_block_boxes.inc
 */

/**
 * Implements hook_default_fe_block_boxes().
 */
function features_extra_test_default_fe_block_boxes() {
  $export = array();

  $fe_block_boxes = new stdClass();
  $fe_block_boxes->info = 'Features Extra Test Block';
  $fe_block_boxes->format = 'plain_text';
  $fe_block_boxes->machine_name = 'features_extra_test_block';
  $fe_block_boxes->body = 'This block is used in automated testing for the Features Extra module.';

  $export['features_extra_test_block'] = $fe_block_boxes;

  return $export;
}
