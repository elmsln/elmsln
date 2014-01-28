<?php
/**
 * @file
 * feeds_node_helper_import.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function feeds_node_helper_import_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "feeds_tamper" && $api == "feeds_tamper_default") {
    return array("version" => "2");
  }
}
