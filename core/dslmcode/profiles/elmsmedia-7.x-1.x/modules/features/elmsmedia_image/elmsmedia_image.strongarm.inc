<?php
/**
 * @file
 * elmsmedia_image.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_image_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_elmsmedia_image';
  $strongarm->value = 1;
  $export['addanother_button_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_elmsmedia_image';
  $strongarm->value = 1;
  $export['addanother_message_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_elmsmedia_image';
  $strongarm->value = 1;
  $export['addanother_tab_edit_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_elmsmedia_image';
  $strongarm->value = 1;
  $export['addanother_tab_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_elmsmedia_image';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_elmsmedia_image';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_elmsmedia_image'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_elmsmedia_image';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_elmsmedia_image'] = $strongarm;

  return $export;
}
