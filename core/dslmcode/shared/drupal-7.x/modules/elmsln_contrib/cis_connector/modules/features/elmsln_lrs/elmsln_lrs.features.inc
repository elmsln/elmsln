<?php
/**
 * @file
 * elmsln_lrs.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsln_lrs_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
