<?php

/**
 * @file
 * haxcms_cache_headers.http_response_headers_default_rule.inc
 */

/**
 * Implements hook_http_response_headers_default_rule().
 */
function haxcms_cache_headers_http_response_headers_default_rule() {
  $export = array();

  $header_rule = new HttpResponseHeadersRule();
  $header_rule->disabled = FALSE; /* Edit this to true to make a default pool disabled initially */
  $header_rule->api_version = 1;
  $header_rule->machine_name = "haxapi_cache";
  $header_rule->description = "HAXapi cache";
  $header_rule->header = "Cache-Control";
  $header_rule->header_value = "public, max-age=86400";
  $header_rule->visibility = "1";
  $header_rule->pages = "haxapi/getNodeContent/*
haxapi/loadJOS/*";
  $header_rule->types = "";
  $header_rule->roles = "";
  $export['haxapi_cache'] = $header_rule;

  return $export;
}
