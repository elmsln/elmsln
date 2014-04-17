<?php
/**
 * @file
 * icor_file_entities.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_file_entities_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "file_entity" && $api == "file_type") {
    return array("version" => "1");
  }
}
