<?php
/**
 * @file
 * editorial_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function editorial_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
