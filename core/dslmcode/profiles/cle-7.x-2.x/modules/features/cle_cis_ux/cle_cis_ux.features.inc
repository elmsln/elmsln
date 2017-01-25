<?php
/**
 * @file
 * cle_cis_ux.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_cis_ux_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
