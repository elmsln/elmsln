<?php

/**
 * short_answer.admin
 *
 * @file
 */

/**
 * Generate a view of all unscored short_answer questions.
 *
 * @see theme_short_answer_view_unscored()
 */
function short_answer_view_unscored() {
  $unscored = ShortAnswerResponse::fetchAllUnscoredAnswers();
  return theme('short_answer_view_unscored', array('unscored' => $unscored));
}

/**
 * Page handler for displaying a scoring form.
 * This function is called directly from the menu router. It generates a form for
 * scoring a quiz.
 *
 * @param $vid
 *  The VID of the question and answer to load.
 * @param $result_id
 *  The result ID of the answer to load.
 * @return
 *  Text to display.
 */
function short_answer_edit_score($vid, $result_id) {
  return drupal_get_form('short_answer_score_form', $vid, $result_id);
}

function short_answer_score_form($form, $form_state, $vid, $result_id) {
  $nid = db_query('SELECT nid FROM {node_revision} WHERE vid = :vid', array(':vid' => $vid))->fetchField();
  $node = node_load($nid, $vid);
  drupal_set_title(t('Score answer to "@title"', array('@title' => $node->title)), PASS_THROUGH);
  $quizQuestionResponse = _quiz_question_response_get_instance($result_id, $node);
  $form += $quizQuestionResponse->getReportForm();
  $form['actions']['submit']['#type'] = 'submit';
  $form['actions']['submit']['#value'] = t('Save score');
  $form['#validate'][] = 'quiz_report_form_element_validate';
  return $form;
}

/**
 * Submit handler for the short answer score form
 */
function short_answer_score_form_submit($form, &$form_state) {
  $vid = $form_state['build_info']['args'][0];
  $nid = db_query('SELECT nid FROM {node_revision} WHERE vid = :vid', array(':vid' => $vid))->fetchField();
  $result_id = $form_state['build_info']['args'][1];
  $quiz_result = quiz_result_load($result_id);

  short_answer_score_an_answer(array(
    'quiz' => node_load($quiz_result->nid, $quiz_result->vid),
    'nid' => $nid,
    'vid' => $vid,
    'result_id' => $result_id,
    'score' => $form_state['values']['score'],
    'answer_feedback' => $form_state['values']['answer_feedback']
  ));

  drupal_set_message(t('The score has been saved.'));
}
