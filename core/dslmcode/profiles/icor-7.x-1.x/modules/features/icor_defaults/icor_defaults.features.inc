<?php
/**
 * @file
 * icor_defaults.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function icor_defaults_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function icor_defaults_views_api() {
  return array("api" => "3.0");
}
