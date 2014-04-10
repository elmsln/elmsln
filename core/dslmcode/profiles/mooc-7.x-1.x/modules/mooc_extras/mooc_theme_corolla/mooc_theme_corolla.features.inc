<?php
/**
 * @file
 * mooc_theme_corolla.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_theme_corolla_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
}
