<?php
/**
 * @file
 * cle_project.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_project_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cle_project_node_info() {
  $items = array(
    'cle_project' => array(
      'name' => t('Project'),
      'base' => 'node_content',
      'description' => t('A project is an organizer for assignments that relates them together to form a larger assignment.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
