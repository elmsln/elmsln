<?php
/**
 * @file
 * assessment_gradebook_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function assessment_gradebook_ux_ctools_plugin_api($module = NULL, $api = NULL) {
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
function assessment_gradebook_ux_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
