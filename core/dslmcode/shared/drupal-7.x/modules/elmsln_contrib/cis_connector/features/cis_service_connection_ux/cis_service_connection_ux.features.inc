<?php
/**
 * @file
 * cis_service_connection_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_service_connection_ux_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
