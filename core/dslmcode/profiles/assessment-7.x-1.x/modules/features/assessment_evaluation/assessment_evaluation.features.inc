<?php
/**
 * @file
 * assessment_evaluation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function assessment_evaluation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function assessment_evaluation_node_info() {
  $items = array(
    'assessment_evaluation' => array(
      'name' => t('Evaluation'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
