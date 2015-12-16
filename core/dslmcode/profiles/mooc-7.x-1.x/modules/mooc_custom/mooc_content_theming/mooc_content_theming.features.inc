<?php
/**
 * @file
 * mooc_content_theming.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_content_theming_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
