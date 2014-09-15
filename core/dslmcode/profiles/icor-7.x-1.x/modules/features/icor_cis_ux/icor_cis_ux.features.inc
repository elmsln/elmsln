<?php
/**
 * @file
 * icor_cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
