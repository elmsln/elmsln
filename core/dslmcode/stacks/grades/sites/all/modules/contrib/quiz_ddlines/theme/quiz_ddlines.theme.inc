<?php

/**
 * The theme file for quiz ddlines.
 *
 * Sponsored by: Senter for IKT i utdanningen
 * Code: paalj
 *
 * @file
 * Theming functions for the ddlines question type.
 */

/**
 * Theming function for the results
 *
 * @param array $vars
 */
function theme_quiz_question_feedback__quiz_ddlines($vars) {
  static $css_added;
  if (!$css_added) {
    drupal_add_css(drupal_get_path('module', 'quiz_ddlines') . '/theme/quiz_ddlines.css');
    $css_added = TRUE;
  }

  $rows = $vars['data'];

  return theme('table', array('header' => NULL, 'rows' => $rows));;
}
