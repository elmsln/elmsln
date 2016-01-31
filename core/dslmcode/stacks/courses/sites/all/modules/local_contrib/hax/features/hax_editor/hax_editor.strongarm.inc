<?php
/**
 * @file
 * hax_editor.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function hax_editor_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'hax_inline_editor';
  $strongarm->value = 'hax_editor';
  $export['hax_inline_editor'] = $strongarm;

  return $export;
}
