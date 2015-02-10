<?php
/**
 * @file
 * rubric_feedback.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function rubric_feedback_ctools_plugin_api($module = NULL, $api = NULL) {
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
function rubric_feedback_node_info() {
  $items = array(
    'rubric_submission_assessment' => array(
      'name' => t('Submission Assessment'),
      'base' => 'node_content',
      'description' => t('A rubric assessment methodology where the person filling out the rubric is assessing the work of learners.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
