<?php
/**
 * @file
 * mooc_cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function mooc_cis_ux_views_api($module = NULL, $api = NULL) {
  return array("api" => "3.0");
}
