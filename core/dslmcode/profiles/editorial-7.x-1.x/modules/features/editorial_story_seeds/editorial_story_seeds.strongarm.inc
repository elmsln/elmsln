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
