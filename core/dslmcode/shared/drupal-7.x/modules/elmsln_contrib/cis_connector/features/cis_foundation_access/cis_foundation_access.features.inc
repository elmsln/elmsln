<?php
/**
 * @file
 * cis_foundation_access.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_foundation_access_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
