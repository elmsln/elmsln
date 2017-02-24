<?php
/**
 * @file
 * mooc_revision_delete.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function mooc_revision_delete_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
