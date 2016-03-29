<?php
/**
 * @file
 * elmsmedia_svg.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_svg_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_svg';
  $strongarm->value = 1;
  $export['addanother_button_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_svg';
  $strongarm->value = 1;
  $export['addanother_message_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_svg';
  $strongarm->value = 1;
  $export['addanother_tab_edit_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_svg';
  $strongarm->value = 1;
  $export['addanother_tab_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_svg';
  $strongarm->value = 'edit-wysiwyg-template';
  $export['additional_settings__active_tab_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_svg';
  $strongarm->value = 1;
  $export['diff_enable_revisions_page_node_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_svg';
  $strongarm->value = 1;
  $export['diff_show_preview_changes_node_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_svg';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_svg'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'svg_sanitizer_allowedattrs';
  $strongarm->value = array(
    0 => 'viewBox',
  );
  $export['svg_sanitizer_allowedattrs'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'svg_sanitizer_allowedtags';
  $strongarm->value = array(
    0 => '',
  );
  $export['svg_sanitizer_allowedtags'] = $strongarm;

  return $export;
}
