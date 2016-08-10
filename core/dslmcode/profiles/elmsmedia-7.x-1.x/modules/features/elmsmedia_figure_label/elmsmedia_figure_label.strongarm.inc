<?php
/**
 * @file
 * elmsmedia_figure_label.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function elmsmedia_figure_label_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_figurelabel';
  $strongarm->value = 1;
  $export['addanother_button_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_figurelabel';
  $strongarm->value = 1;
  $export['addanother_message_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_figurelabel';
  $strongarm->value = 1;
  $export['addanother_tab_edit_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_figurelabel';
  $strongarm->value = 1;
  $export['addanother_tab_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_figurelabel';
  $strongarm->value = 'edit-addanother-display';
  $export['additional_settings__active_tab_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_figurelabel';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_figurelabel';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_figurelabel';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_figurelabel'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'wysiwyg_template_default_figurelabel';
  $strongarm->value = '';
  $export['wysiwyg_template_default_figurelabel'] = $strongarm;

  return $export;
}
