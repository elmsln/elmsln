<?php
/**
 * @file
 * features_test.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function features_test_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function features_test_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_image_default_styles().
 */
function features_test_image_default_styles() {
  $styles = array();

  // Exported image style: features_test.
  $styles['features_test'] = array(
    'effects' => array(
      2 => array(
        'name' => 'image_scale',
        'data' => array(
          'width' => 100,
          'height' => 100,
          'upscale' => 0,
        ),
        'weight' => 1,
      ),
    ),
    'label' => 'features_test',
  );

  return $styles;
}

/**
 * Implements hook_node_info().
 */
function features_test_node_info() {
  $items = array(
    'features_test' => array(
      'name' => t('Testing: Features'),
      'base' => 'node_content',
      'description' => t('Content type provided for Features tests.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
