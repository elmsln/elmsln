<?php
/**
 * @file
 * editorial_ux.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function editorial_ux_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_comment_settings';
  $strongarm->value = array(
    'editorial_blog_post' => 'editorial_blog_post',
    'section' => 'section',
    'editorial_journal_entry' => 'editorial_journal_entry',
    'editorial_story_seeds' => 'editorial_story_seeds',
  );
  $export['jammer_comment_settings'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_revision_information';
  $strongarm->value = array(
    'editorial_blog_post' => 'editorial_blog_post',
    'section' => 'section',
    'editorial_journal_entry' => 'editorial_journal_entry',
    'editorial_story_seeds' => 'editorial_story_seeds',
  );
  $export['jammer_revision_information'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_revision_log_textarea_unset_node_types';
  $strongarm->value = array(
    'editorial_blog_post' => 'editorial_blog_post',
    'section' => 'section',
    'editorial_journal_entry' => 'editorial_journal_entry',
    'editorial_story_seeds' => 'editorial_story_seeds',
  );
  $export['jammer_revision_log_textarea_unset_node_types'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jammer_teaser_controls_unset_node_types';
  $strongarm->value = array(
    'editorial_blog_post' => 'editorial_blog_post',
    'section' => 'section',
    'editorial_journal_entry' => 'editorial_journal_entry',
    'editorial_story_seeds' => 'editorial_story_seeds',
  );
  $export['jammer_teaser_controls_unset_node_types'] = $strongarm;

  return $export;
}
