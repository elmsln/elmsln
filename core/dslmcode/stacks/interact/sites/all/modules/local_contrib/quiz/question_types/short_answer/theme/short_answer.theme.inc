<?php

/**
 * @file
 * Theme functions for short_answer.
 */

/**
 * Theme the list of unscored short answer questions.
 *
 * @param $unscored
 *  An array of objects with information about the unscored questions
 */
function theme_short_answer_view_unscored($variables) {
  $unscored = $variables['unscored'];
  $output = '';
  $header = array(
    t('Question'),
    t('Time Finished'),
    t('Action')
  );
  $rows = array();

  foreach ($unscored as $item) {
    if ($item->time_end > 0) {
      $rows[] = array(
        $item->title,
        date('Y-m-d H:i', $item->time_end),
        l(t('score this response'), 'admin/quiz/reports/score-short-answer/' . $item->question_vid . '/' . $item->result_id),
      );
    }
  }

  if (!empty($rows)) {
    $output .= theme('table', array('header' => $header, 'rows' => $rows));
  }
  else {
    $output .= t('There are no unscored essays.');
  }
  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function theme_short_answer_user_answer($variables) {
  $answer = $variables['answer'];
  $correct = $variables['correct'];
  $header = array(t('Correct Answer'), t('User Answer'));
  $row = array(array($correct, $answer));
  return theme('table', array('header' => $header, 'rows' => $row));
}

/**
 * Theme the short_answer response form
 *
 * @param $form
 *  The response form
 */
function theme_short_answer_response_form($variables) {
  $form = $variables['form'];
  return drupal_render_children($form);
}
