<?php

/**
 * @file
 * User pages.
 */

/**
 * Show result page for a given result id.
 *
 * @param $result_id
 *  Result id.
 */
function quiz_user_results($result_id) {
  $quiz_result = quiz_result_load($result_id);
  $view = entity_view('quiz_result', array($quiz_result));
  if ($quiz_result->is_invalid) {
    drupal_set_message(t('This result can only be viewed temporarly and will be deleted in the near future.'), 'warning');
  }
  return $view;
}

/**
 * Submit the report form.
 */
function quiz_report_form_submit($form, &$form_state) {
  global $user;
  $quiz_result = $form_state['quiz_result'];
  $quiz = node_load($quiz_result->nid, $quiz_result->vid);

  if (!empty($form_state['values']['question'])) {
    foreach ($form_state['values']['question'] as $key => $q_values) {
      $question_node = node_load($q_values['nid'], $q_values['vid']);
      $instance = _quiz_question_response_get_instance($quiz_result->result_id, $question_node);
      if ($instance->getReportFormSubmit()) {
        $q_values['quiz'] = node_load($quiz_result->nid, $quiz_result->vid);
        call_user_func($instance->getReportFormSubmit(), $q_values);
      }
    }

    // Scores may have been changed. We take the necessary actions.
    quiz_end_scoring($quiz_result->result_id);
    $results_got_deleted = _quiz_maintain_results($quiz, $quiz_result->result_id);

    // Notify the user if results got deleted as a result of him scoring an
    // answer.
    $add = $quiz->keep_results == QUIZ_KEEP_BEST && $results_got_deleted ? ' ' . t('Note that this @quiz is set to only keep each users best answer.', array('@quiz' => QUIZ_NAME)) : '';

    $score_data = quiz_get_score_array($quiz_result->result_id, $quiz->vid, TRUE);

    module_invoke_all('quiz_scored', $quiz, $score_data, $quiz_result->result_id);

    drupal_set_message(t('The scoring data you provided has been saved.') . $add);
  }
}

/**
 * Helper function to remove the message saying the quiz haven't been scored.
 */
function _quiz_remove_unscored_message() {
  if (!empty($_SESSION['messages']['warning'])) {
    // Search for the message, and remove it if we find it.
    foreach ($_SESSION['messages']['warning'] as $key => $val) {
      if ($val == t('This @quiz has not been scored yet.', array('@quiz' => QUIZ_NAME))) {
        unset($_SESSION['messages']['warning'][$key]);
      }
    }
    // Clean up if the message array was left empty.
    if (empty($_SESSION['messages']['warning'])) {
      unset($_SESSION['messages']['warning']);
      if (empty($_SESSION['messages'])) {
        unset($_SESSION['messages']);
      }
    }
  }
}

/**
 * Returns an array of score information for a quiz.
 *
 * @param unknown_type $result_id
 * @param unknown_type $quiz_vid
 * @param unknown_type $is_evaluated
 */
function quiz_get_score_array($result_id, $quiz_vid, $is_evaluated) {
  $properties = db_query('SELECT max_score, number_of_random_questions
          FROM {quiz_node_properties}
          WHERE vid = :vid', array(':vid' => $quiz_vid))->fetchObject();
  $total_score = db_query('SELECT SUM(points_awarded)
          FROM {quiz_node_results_answers}
          WHERE result_id = :result_id', array(':result_id' => $result_id))->fetchField();

  return array(
    'question_count' => $properties->number_of_random_questions + quiz_get_number_of_questions($quiz_vid, $result_id),
    'possible_score' => $properties->max_score,
    'numeric_score' => $total_score,
    'percentage_score' => ($properties->max_score == 0) ? 0 : round(($total_score * 100) / $properties->max_score),
    'is_evaluated' => $is_evaluated,
  );
}
