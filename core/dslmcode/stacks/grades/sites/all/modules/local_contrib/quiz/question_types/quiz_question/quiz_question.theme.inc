<?php

/**
 * @file
 * Themes for the quiz question module.
 */

/**
 * Theme the question creation form.
 *
 * @param array $variables
 */
function theme_quiz_question_creation_form($variables) {
  $form = $variables['form'];
  module_load_include('inc', 'quiz', 'quiz.admin');
  quiz_set_auto_title();
}

/**
 * Theme the question navigation area.
 *
 * @param array $variables
 */
function theme_quiz_question_navigation_form($variables) {

}
