<?php
/**
 * @file
 * cle_assignment_advanced.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_assignment_advanced_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function cle_assignment_advanced_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
