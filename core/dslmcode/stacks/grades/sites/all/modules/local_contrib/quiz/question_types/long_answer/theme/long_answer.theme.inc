<?php

/**
 * @file
 * Theme functions for the long_answer question type.
 */

/**
 * Theme the long_answer response form.
 *
 * @param array $variables
 *
 * @return string
 *   An HTML string.
 */
function theme_long_answer_response_form($variables) {
  $form = $variables['form'];
  return drupal_render_children($form);
}
