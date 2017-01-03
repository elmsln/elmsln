<?php
/**
 * @file
 * assessment_quiz.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function assessment_quiz_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'quiz_matching_form_size';
  $strongarm->value = '12';
  $export['quiz_matching_form_size'] = $strongarm;

  return $export;
}
