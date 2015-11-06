<?php
/**
 * @file
 * cle_gradebook_ux.features.inc
 */

/**
 * Implements hook_default_assessment_entity_type().
 */
function cle_gradebook_ux_default_assessment_entity_type() {
  $items = array();
  $items['submission_evaluation'] = entity_import('assessment_entity_type', '{
    "type" : "submission_evaluation",
    "label" : "Submission evaluation",
    "weight" : "0"
  }');
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_gradebook_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cle_gradebook_ux_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
