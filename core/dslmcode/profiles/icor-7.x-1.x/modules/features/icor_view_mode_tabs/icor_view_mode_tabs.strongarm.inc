<?php
/**
 * @file
 * icor_view_mode_tabs.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function icor_view_mode_tabs_strongarm() {
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
  $strongarm->name = 'view_mode_tab_settings__icor_interactive_player';
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
  $export['view_mode_tab_settings__icor_interactive_player'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__jmol';
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
  $export['view_mode_tab_settings__jmol'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__map';
  $strongarm->value = array(
    'full' => 1,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'entityreference_view_widget' => 0,
    'iframe' => 1,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__map'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__map_point';
  $strongarm->value = array(
    'full' => 1,
    'teaser' => 0,
    'rss' => 0,
    'diff_standard' => 0,
    'entityreference_view_widget' => 0,
    'iframe' => 1,
    'token' => 0,
    'revision' => 0,
  );
  $export['view_mode_tab_settings__map_point'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__poll';
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
  $export['view_mode_tab_settings__poll'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__timeline';
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
  $export['view_mode_tab_settings__timeline'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'view_mode_tab_settings__timeline_date';
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
  $export['view_mode_tab_settings__timeline_date'] = $strongarm;

  return $export;
}
