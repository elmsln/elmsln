<?php
/**
 * @file
 * cis_service_lti.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function cis_service_lti_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}
