<?php
/**
 * @file
 * rubric_feature.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function rubric_feature_ctools_plugin_api($module = NULL, $api = NULL) {
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
function rubric_feature_node_info() {
  $items = array(
    'elms_rubric' => array(
      'name' => t('Rubric'),
      'base' => 'node_content',
      'description' => t('Rubric content type that contains the structure and rules by which a rubric has to abide.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
