<?php
/**
 * @file
 * cis_course_authority.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_course_authority_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_node_info().
 */
function cis_course_authority_node_info() {
  $items = array(
    'cis_course' => array(
      'name' => t('Course'),
      'base' => 'node_content',
      'description' => t('Course node generated from CIS linked item'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
