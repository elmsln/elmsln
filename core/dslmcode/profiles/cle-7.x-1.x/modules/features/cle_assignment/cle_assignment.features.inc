<?php
/**
 * @file
 * cle_assignment.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_assignment_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cle_assignment_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cle_assignment_node_info() {
  $items = array(
    'cle_assignment' => array(
      'name' => t('Assignment'),
      'base' => 'node_content',
      'description' => t('Assignment to communicate to students. They also use this to associate their work to a submission.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
