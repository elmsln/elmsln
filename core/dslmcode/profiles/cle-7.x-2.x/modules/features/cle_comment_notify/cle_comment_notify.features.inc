<?php
/**
 * @file
 * cle_comment_notify.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cle_comment_notify_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
