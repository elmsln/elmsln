<?php
/**
 * @file
 * elmsln_voice.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsln_voice_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
