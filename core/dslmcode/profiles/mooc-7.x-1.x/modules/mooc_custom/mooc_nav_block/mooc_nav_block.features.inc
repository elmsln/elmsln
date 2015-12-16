<?php
/**
 * @file
 * mooc_nav_block.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_nav_block_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
}
