<?php
/**
 * @file
 * cis_competencies.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_competencies_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cis_competencies_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function cis_competencies_node_info() {
  $items = array(
    'elmsln_competency' => array(
      'name' => t('Competency'),
      'base' => 'node_content',
      'description' => t('What students are achieving, learning, and experiencing by taking courses. These can be applied across curricula though most likely will be unique to the experiences created in each course.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
