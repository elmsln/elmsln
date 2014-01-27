<?php
/**
 * @file
 * This include file implements coder functionality for 7.x -> 8.x upgrades.
 */

/**
 * Implements hook_reviews().
 */
function coder_review_8x_reviews() {
  $rules[] = array(
  );

  $review = array(
    '#title' => 'Converting 7.x modules to 8.x',
    '#link' => 'http://drupal.org/list-changes/drupal?to_branch=8.x',
    '#rules' => $rules,
    '#severity' => 'critical',
    '#version' => 2,
    '#image' => 'images/8.png',
  );

  return array('upgrade8x' => $review);
}
