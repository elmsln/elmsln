<?php
/**
 * @file
 * cle_perms.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cle_perms_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_compression_type';
  $strongarm->value = 'none';
  $export['jquery_update_compression_type'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_admin_version';
  $strongarm->value = 'default';
  $export['jquery_update_jquery_admin_version'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_cdn';
  $strongarm->value = 'none';
  $export['jquery_update_jquery_cdn'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_jquery_version';
  $strongarm->value = '1.7';
  $export['jquery_update_jquery_version'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_pages';
  $strongarm->value = 'admin
admin/*';
  $export['jquery_update_pages'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'jquery_update_visibility';
  $strongarm->value = '0';
  $export['jquery_update_visibility'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rate_bot_botscout_key';
  $strongarm->value = '';
  $export['rate_bot_botscout_key'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rate_bot_hour_threshold';
  $strongarm->value = '250';
  $export['rate_bot_hour_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rate_bot_minute_threshold';
  $strongarm->value = '25';
  $export['rate_bot_minute_threshold'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rate_widgets';
  $strongarm->value = array(
    1 => (object) array(
      'name' => 'cle_submission_like',
      'tag' => 'vote',
      'title' => 'Like',
      'node_types' => array(
        0 => 'cle_submission',
      ),
      'comment_types' => array(),
      'options' => array(
        0 => array(
          0 => 1,
          1 => 'up',
        ),
      ),
      'template' => 'thumbs_up',
      'node_display' => '2',
      'teaser_display' => FALSE,
      'comment_display' => '0',
      'node_display_mode' => '1',
      'teaser_display_mode' => '1',
      'comment_display_mode' => '1',
      'roles' => array(
        9 => '9',
        3 => '3',
        5 => '5',
        7 => '7',
        8 => '8',
        1 => 0,
        2 => 0,
        4 => 0,
        10 => 0,
        6 => 0,
      ),
      'allow_voting_by_author' => 1,
      'noperm_behaviour' => '4',
      'displayed' => '1',
      'displayed_just_voted' => '1',
      'description' => '',
      'description_in_compact' => FALSE,
      'delete_vote_on_second_click' => '1',
      'use_source_translation' => TRUE,
      'value_type' => 'points',
      'theme' => 'rate_template_thumbs_up',
      'css' => 'sites/all/modules/local_contrib/rate/templates/thumbs-up/thumbs-up.css',
      'translate' => TRUE,
    ),
    2 => (object) array(
      'name' => 'evoke',
      'tag' => 'emotion',
      'title' => 'Evoke',
      'node_types' => array(
        0 => 'cle_submission',
      ),
      'comment_types' => array(
        0 => 'cle_submission',
      ),
      'options' => array(
        0 => array(
          0 => '1',
          1 => 'funny',
        ),
        1 => array(
          0 => '2',
          1 => 'silly',
        ),
        2 => array(
          0 => '3',
          1 => 'angry',
        ),
        3 => array(
          0 => '4',
          1 => 'sad',
        ),
        4 => array(
          0 => '5',
          1 => 'inspiring',
        ),
        5 => array(
          0 => '6',
          1 => 'inappropriate',
        ),
        6 => array(
          0 => '7',
          1 => 'happy',
        ),
      ),
      'template' => 'emotion',
      'node_display' => '2',
      'teaser_display' => FALSE,
      'comment_display' => '2',
      'node_display_mode' => '1',
      'teaser_display_mode' => '1',
      'comment_display_mode' => '1',
      'roles' => array(
        9 => '9',
        3 => '3',
        5 => '5',
        7 => '7',
        8 => '8',
        1 => 0,
        2 => 0,
        4 => 0,
        10 => 0,
        6 => 0,
      ),
      'allow_voting_by_author' => 1,
      'noperm_behaviour' => '4',
      'displayed' => '1',
      'displayed_just_voted' => '1',
      'description' => 'How did this make you feel?',
      'description_in_compact' => FALSE,
      'delete_vote_on_second_click' => '1',
      'use_source_translation' => TRUE,
      'value_type' => 'option',
      'theme' => 'rate_template_emotion',
      'css' => 'sites/all/modules/local_contrib/rate/templates/emotion/emotion.css',
      'translate' => TRUE,
    ),
  );
  $export['rate_widgets'] = $strongarm;

  return $export;
}
