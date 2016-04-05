<?php
/**
 * @file
 * assessment_ux.features.inc
 */

/**
 * Implements hook_default_assessment_item_type().
 */
function assessment_ux_default_assessment_item_type() {
  $items = array();
  $items['graded_item'] = entity_import('assessment_item_type', '{ "type" : "graded_item", "label" : "Graded item", "weight" : "0" }');
  return $items;
}

/**
 * Implements hook_ctools_plugin_api().
 */
function assessment_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
