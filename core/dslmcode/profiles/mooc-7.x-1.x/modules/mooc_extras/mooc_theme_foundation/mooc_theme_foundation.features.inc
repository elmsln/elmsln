<?php
/**
 * @file
 * mooc_theme_foundation.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_theme_foundation_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "boxes" && $api == "box") {
    return array("version" => "1");
  }
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
