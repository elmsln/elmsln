<?php
/**
 * @file
 * cle_rate.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function cle_rate_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'rate_widgets';
  $strongarm->value = array(
    1 => (object) array(
      'name' => 'like',
      'tag' => 'like',
      'title' => 'Like',
      'node_types' => array(
        0 => 'cle_submission',
      ),
      'comment_types' => array(
        0 => 'cle_submission',
      ),
      'options' => array(
        0 => array(
          0 => 1,
          1 => 'up',
        ),
      ),
      'template' => 'thumbs_up',
      'node_display' => '2',
      'teaser_display' => FALSE,
      'comment_display' => '2',
      'node_display_mode' => '1',
      'teaser_display_mode' => '1',
      'comment_display_mode' => '1',
      'roles' => array(
        30037204 => '30037204',
        75987638 => '75987638',
        166149871 => '166149871',
        66784200 => '66784200',
        67296478 => '67296478',
        1 => 0,
        2 => 0,
        6065076 => 0,
        135574917 => 0,
        76550217 => 0,
      ),
      'allow_voting_by_author' => 0,
      'noperm_behaviour' => '4',
      'displayed' => '1',
      'displayed_just_voted' => '2',
      'description' => '',
      'description_in_compact' => TRUE,
      'delete_vote_on_second_click' => '1',
      'use_source_translation' => TRUE,
      'value_type' => 'points',
      'theme' => 'rate_template_thumbs_up',
      'css' => 'sites/all/modules/local_contrib/rate/templates/thumbs-up/thumbs-up.css',
      'translate' => FALSE,
    ),
  );
  $export['rate_widgets'] = $strongarm;

  return $export;
}
