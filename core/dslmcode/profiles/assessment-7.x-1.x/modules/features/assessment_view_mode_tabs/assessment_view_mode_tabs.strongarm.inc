<?php
/**
 * @file
 * assessment_view_mode_tabs.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function assessment_view_mode_tabs_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_enable_by_default';
  $strongarm->value = 0;
  $export['view_mode_enable_by_default'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__assessment_quiz';
  $strongarm->value = array(
    'full' => 0,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'entityreference_view_widget' => 0,
    'iframe' => 1,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__assessment_quiz'] = $strongarm;

  return $export;
}
