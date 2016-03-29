<?php
/**
 * @file
 * elmsmedia_external_video.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_external_video_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_external_video';
  $strongarm->value = 1;
  $export['addanother_button_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_external_video';
  $strongarm->value = 1;
  $export['addanother_message_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_external_video';
  $strongarm->value = 1;
  $export['addanother_tab_edit_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_external_video';
  $strongarm->value = 1;
  $export['addanother_tab_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_external_video';
  $strongarm->value = 'edit-view-mode-tab';
  $export['additional_settings__active_tab_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_external_video';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_external_video';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_external_video'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_external_video';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_external_video'] = $strongarm;

  return $export;
}
