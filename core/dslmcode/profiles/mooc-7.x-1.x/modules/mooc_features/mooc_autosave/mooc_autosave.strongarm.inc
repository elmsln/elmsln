<?php
/**
 * @file
 * mooc_autosave.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function mooc_autosave_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_form_ids';
  $strongarm->value = 'hax_page_edit_form';
  $export['autosave_form_ids'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_hidden';
  $strongarm->value = 0;
  $export['autosave_hidden'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_ignore_behavior';
  $strongarm->value = 0;
  $export['autosave_ignore_behavior'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_mooc_container';
  $strongarm->value = 1;
  $export['autosave_mooc_container'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_page';
  $strongarm->value = 1;
  $export['autosave_page'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_period';
  $strongarm->value = '10';
  $export['autosave_period'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'autosave_timeout';
  $strongarm->value = '0';
  $export['autosave_timeout'] = $strongarm;

  return $export;
}
