<?php
/**
 * @file
 * mooc_theme_aurora.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_theme_aurora_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
