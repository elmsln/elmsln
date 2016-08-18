<?php
/**
 * @file
 * cis_course_service.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_course_service_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
