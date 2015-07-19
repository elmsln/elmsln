<?php
/**
 * @file
 * ecd_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function ecd_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
