<?php
/**
 * @file
 * features_extra_test.features.inc
 */

/**
 * Implements hook_fe_nodequeue_export_fields().
 */
function features_extra_test_fe_nodequeue_export_fields() {
  $nodequeues = array();

  // Exported nodequeues: features_extra_test_nodequeue
  $nodequeues['features_extra_test_nodequeue'] = array(
    'name' => 'features_extra_test_nodequeue',
    'title' => 'Features Extra Test Nodequeue',
    'subqueue_title' => '',
    'size' => '0',
    'link' => '',
    'link_remove' => '',
    'owner' => 'nodequeue',
    'show_in_ui' => '1',
    'show_in_tab' => '1',
    'show_in_links' => '0',
    'reference' => '0',
    'reverse' => '0',
    'i18n' => '0',
    'subqueues' => '1',
    'types' => array(
      0 => 'article',
    ),
    'roles' => array(),
    'count' => 0,
  );

  return $nodequeues;
}
