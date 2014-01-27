<?php
/**
 * @file
 * features_extra_test.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function features_extra_test_default_fe_block_settings() {
  $export = array();

  $export['version'] = '2.0';

  $export['block-features_extra_test_block'] = array(
    'cache' => -1,
    'css_class' => 'test-class',
    'custom' => '0',
    'machine_name' => 'features_extra_test_block',
    'module' => 'block',
    'node_types' => array(),
    'pages' => '',
    'roles' => array(),
    'themes' => array(
      'bartik' => array(
        'region' => 'content',
        'status' => '1',
        'theme' => 'bartik',
        'weight' => '0',
      ),
    ),
    'title' => 'Features Extra',
    'visibility' => '0',
  );

  return $export;
}
