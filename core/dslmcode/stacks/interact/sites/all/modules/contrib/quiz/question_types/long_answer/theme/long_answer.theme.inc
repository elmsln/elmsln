<?php

/**
 * @file
 * Theme functions for long_answer.
 */


/**
 * Theme the list of unscored long answer questions.
 *
 * @param $unscored
 *  An array of objects, each with the question_nid, question_vid, and result_id of an unscored question.
 */
function theme_long_answer_view_unscored($variables) {
  $unscored = $variables['unscored'];
  $output = '';
  $header = array(
    t('Question'),
    t('Finished'),
    t('Action')
  );
  $rows = array();

  foreach ($unscored as $item) {
    if ($item->time_end > 0) {
      $rows[] = array(
        check_plain($item->title),
        date('Y-m-d H:i', $item->time_end),
        l(t('Score this response'), 'admin/quiz/reports/score-long-answer/' . $item->question_vid . '/' . $item->result_id),
      );
    }
  }
  $output .= !empty($rows) ? theme('table', array('header' => $header, 'rows' => $rows)) : t('There are no unscored essays.');
  return $output;
}

/**
 * Theme the long_answer response form
 *
 * @param $form
 *  The response form
 */
function theme_long_answer_response_form($variables) {
  $form = $variables['form'];
  return drupal_render_children($form);
}
