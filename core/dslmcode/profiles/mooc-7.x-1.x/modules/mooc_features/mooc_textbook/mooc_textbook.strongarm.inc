<?php
/**
 * @file
 * mooc_textbook.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_textbook_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_content_show_toggle';
  $strongarm->value = 1;
  $export['accessibility_content_show_toggle'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_content_toggle_message_off';
  $strongarm->value = 'Check accessibility';
  $export['accessibility_content_toggle_message_off'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'accessibility_content_toggle_message_on';
  $strongarm->value = 'Hide checks';
  $export['accessibility_content_toggle_message_on'] = $strongarm;

  return $export;
}
