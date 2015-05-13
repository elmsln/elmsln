<?php

/**
 * Implements hook_gradebook_status_indicators().
 */
function hook_gradebook_status_indicators() {
  $path = drupal_get_path('module', 'cle_gradebook') . '/images/assessment/';
  return array(
  	'status_light' => array(
      'title' => t('Status name'),
      'icon' => $path . 'status_light.png',
    ),
  );
}

/**
 * Implements hook_gradebook_status_indicators().
 */
function hook_gradebook_status_indicators_alter(&$indicators) {
}