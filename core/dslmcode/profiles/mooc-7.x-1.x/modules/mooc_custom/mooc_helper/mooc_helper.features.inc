<?php
/**
 * @file
 * mooc_helper.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_helper_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
