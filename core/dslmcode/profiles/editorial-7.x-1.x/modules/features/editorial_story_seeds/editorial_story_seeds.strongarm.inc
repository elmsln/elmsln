<?php
/**
 * @file
 * editorial_story_seeds.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function editorial_story_seeds_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_button_editorial_story_seeds';
  $strongarm->value = 0;
  $export['addanother_button_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_message_editorial_story_seeds';
  $strongarm->value = 0;
  $export['addanother_message_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_editorial_story_seeds';
  $strongarm->value = 0;
  $export['addanother_tab_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'addanother_tab_edit_editorial_story_seeds';
  $strongarm->value = 0;
  $export['addanother_tab_edit_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'additional_settings__active_tab_editorial_story_seeds';
  $strongarm->value = 'edit-wysiwyg-template';
  $export['additional_settings__active_tab_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_editorial_story_seeds';
  $strongarm->value = '1';
  $export['ant_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_pattern_editorial_story_seeds';
  $strongarm->value = '[current-user:name] story seeds';
  $export['ant_pattern_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'ant_php_editorial_story_seeds';
  $strongarm->value = 0;
  $export['ant_php_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_enable_revisions_page_node_editorial_story_seeds';
  $strongarm->value = 0;
  $export['diff_enable_revisions_page_node_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_show_preview_changes_node_editorial_story_seeds';
  $strongarm->value = 0;
  $export['diff_show_preview_changes_node_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'diff_view_mode_preview_node_editorial_story_seeds';
  $strongarm->value = 'full';
  $export['diff_view_mode_preview_node_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_options_editorial_story_seeds';
  $strongarm->value = array();
  $export['menu_options_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'menu_parent_editorial_story_seeds';
  $strongarm->value = 'main-menu:0';
  $export['menu_parent_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_editorial_story_seeds';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_preview_editorial_story_seeds';
  $strongarm->value = '0';
  $export['node_preview_editorial_story_seeds'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_submitted_editorial_story_seeds';
  $strongarm->value = 0;
  $export['node_submitted_editorial_story_seeds'] = $strongarm;

  return $export;
}
