<?php
/**
 * @file
 * elmsmedia_h5p.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function elmsmedia_h5p_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "ds" && $api == "ds") {
    return array("version" => "1");
  }
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
