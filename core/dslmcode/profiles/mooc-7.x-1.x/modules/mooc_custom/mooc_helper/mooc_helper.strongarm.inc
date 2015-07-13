<?php
/**
 * @file
 * mooc_helper.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_helper_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scanner_body_field_revision_body_page';
  $strongarm->value = 1;
  $export['scanner_body_field_revision_body_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'scanner_title_node_revision_page';
  $strongarm->value = 1;
  $export['scanner_title_node_revision_page'] = $strongarm;

  return $export;
}
