<?php

/**
 * @file
 * haxcms_cache_headers.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function haxcms_cache_headers_ctools_plugin_api($module = NULL, $api = NULL) {
  if ($module == "http_response_headers" && $api == "http_response_headers_default_rule") {
    return array("version" => "1");
  }
}
