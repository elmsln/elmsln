<?php
/**
 * @file
 * cis_service_connection_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_service_connection_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
