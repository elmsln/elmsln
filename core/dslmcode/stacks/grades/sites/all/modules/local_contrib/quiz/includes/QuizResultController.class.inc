<?php

class QuizResultController extends EntityAPIController {

  public function delete($ids, \DatabaseTransaction $transaction = NULL) {
    foreach ($ids as $result_id) {
      // Fire the question types' implementations of question attempts deletion.
      $sql = 'SELECT result_id, question_nid, question_vid FROM {quiz_node_results_answers}
          WHERE result_id = (:result_id)';
      $result = db_query($sql, array(':result_id' => $result_id));
      foreach ($result as $record) {
        if ($response = _quiz_question_response_get_instance($result_id, NULL, NULL, $record->question_nid, $record->question_vid)) {
          $response->delete();
        }
      }

      // Delete Quiz's records of any attempts at a question.
      db_delete('quiz_node_results_answers')
        ->condition('result_id', $result_id)
        ->execute();
    }
    parent::delete($ids, $transaction);
  }

  /**
   * Save the Quiz result and do any post-processing to the result.
   *
   * @param type $entity
   * @param \DatabaseTransaction $transaction
   *
   * @return bool
   */
  public function save($entity, \DatabaseTransaction $transaction = NULL) {
    if (empty($entity->time_start)) {
      $entity->time_start = REQUEST_TIME;
    }

    $new = !empty($entity->is_new);

    if (!isset($entity->attempt)) {
      if ($entity->uid == 0) {
        $entity->attempt = 1;
      }
      else {
        $efq = new EntityFieldQuery();
        $result = $efq->entityCondition('entity_type', 'quiz_result')
          ->propertyCondition('nid', $entity->nid)
          ->propertyCondition('uid', $entity->uid)
          ->propertyOrderBy('attempt', 'DESC')
          ->range(0, 1)
          ->execute();
        if (!empty($result['quiz_result'])) {
          $keys = array_keys($result['quiz_result']);
          $existing = quiz_result_load(reset($keys));
          $entity->attempt = $existing->attempt + 1;
        }
      }
    }

    // Save the Quiz result.
    parent::save($entity, $transaction);

    // Post process the result.
    if ($new) {
      $quiz = node_load($entity->nid, $entity->vid);

      // Call @deprecated hook_quiz_begin().
      module_invoke_all('quiz_begin', $quiz, $entity->result_id);

      // Create question list.
      $questions = quiz_build_question_list($quiz);
      if ($questions === FALSE) {
        drupal_set_message(t('Not enough random questions were found. Please add more questions before trying to take this @quiz.', array('@quiz' => QUIZ_NAME)), 'error');
        return FALSE;
      }

      if (count($questions) == 0) {
        drupal_set_message(t('No questions were found. Please !assign_questions before trying to take this @quiz.', array('@quiz' => QUIZ_NAME, '!assign_questions' => l(t('assign questions'), 'node/' . $quiz->nid . '/quiz/questions'))), 'error');
        return FALSE;
      }

      $i = 0;
      $j = 0;
      foreach ($questions as $question) {
        $quizQuestion = _quiz_question_get_instance((object) $question);
        $quiz_result_answer = entity_create('quiz_result_answer', array(
          'result_id' => $entity->result_id,
          'question_nid' => $question['nid'],
          'question_vid' => $question['vid'],
          'tid' => !empty($question['tid']) ? $question['tid'] : NULL,
          'number' => ++$i,
          'display_number' => $quizQuestion->isQuestion() ? ++$j : NULL,
        ));
        entity_save('quiz_result_answer', $quiz_result_answer);
      }

      if (!empty($entity->build_on_last)) {
        // Build on the last attempt the user took. If this quiz has build on
        // last attempt set, we need to search for a previous attempt with the
        // same version of the current quiz.
        $quiz_result_old = self::findOldResult($entity);
        // Now clone the answers on top of the new result.
        quiz_clone_quiz_result($quiz_result_old, $entity);
      }
    }
  }

  /**
   * Find a result that is not the same as the passed result.
   *
   * Note: the Quiz result does not have an actually exist - in that case, it
   * will return the first completed result found.
   */
  public static function findOldResult($quiz_result) {
    $efq = new EntityFieldQuery();
    $result = $efq->entityCondition('entity_type', 'quiz_result')
      ->propertyCondition('uid', $quiz_result->uid)
      ->propertyCondition('nid', $quiz_result->nid)
      ->propertyCondition('vid', $quiz_result->vid)
      ->propertyCondition('result_id', isset($quiz_result->result_id) ? $quiz_result->result_id : 0, '!=')
      ->propertyCondition('time_start', 0, '>')
      ->propertyOrderBy('time_start', 'DESC')
      ->range(0, 1)
      ->execute();
    if (!empty($result['quiz_result'])) {
      $old_quiz_result = reset($result['quiz_result']);
      return quiz_result_load($old_quiz_result->result_id);
    }
    return FALSE;
  }

  public function buildContent($entity, $view_mode = 'full', $langcode = NULL, $content = array()) {
    $out = parent::buildContent($entity, $view_mode, $langcode, $content);

    if (!$entity->is_evaluated && empty($_POST)) {
      $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final.', array('@quiz' => QUIZ_NAME));
      drupal_set_message($msg, 'warning');
    }

    $score = quiz_calculate_score($entity->result_id);
    $account = user_load($entity->uid);

    $params = array(
      '%num_correct' => $score['numeric_score'],
      '%question_count' => $score['possible_score'],
      '!username' => ($account->uid == $account->uid) ? t('You') : theme('username', array('account' => $account)),
      '@score' => $score['percentage_score'],
      '!yourtotal' => ($account->uid == $account->uid) ? t('Your') : t('Total'),
    );

    $questions = array();

    foreach ($entity->getLayout() as $question) {
      // Loop through all the questions and get their feedback.
      $question_node = node_load($question['nid'], $question['vid']);

      $instance = _quiz_question_response_get_instance($entity->result_id, $question_node);
      if ($instance->getQuizQuestion()->hasFeedback()) {
        $qras = entity_load('quiz_result_answer', FALSE, array(
          'result_id' => $entity->result_id,
          'question_nid' => $question_node->nid,
          'question_vid' => $question_node->vid,
        ));
        $qra = reset($qras);

        $feedback = $qra->view();
        if (element_children($feedback['quiz_result_answer'][$instance->result_answer_id])) {
          $questions[$question_node->nid] = array(
            '#title' => t('Question @num', array('@num' => $question['display_number'])),
            '#type' => 'fieldset',
            'feedback' => $feedback,
            '#weight' => $question['number'],
          );
        }
      }
    }

    if ($questions) {
      $out['questions'] = $questions;
    }

    $quiz_feedback['#markup'] = '';
    if (quiz_feedback_can_review('quiz_feedback', $entity)) {
      $summary = _quiz_get_summary_text($entity);
      // Show quiz feedback.
      if (!empty($summary['passfail'])) {
        $quiz_feedback['#markup'] .= '<div id="quiz-summary">' . $summary['passfail'] . '</div>';
      }
      if (!empty($summary['result'])) {
        $quiz_feedback['#markup'] .= '<div id="quiz-summary">' . $summary['result'] . '</div>';
      }
    }
    if ($quiz_feedback['#markup']) {
      $out['summary'] = $quiz_feedback;
    }

    if (quiz_feedback_can_review('score', $entity)) {
      // Show score.
      $out['score']['#markup'] = '<div id="quiz_score_possible">' . t('!username got %num_correct of %question_count possible points.', $params) . '</div>' . "\n";
      $out['score']['#markup'] .= '<div id="quiz_score_percent">' . t('!yourtotal score: @score%', $params) . '</div>';
    }

    if (!element_children($out)) {
      $out['no_feedback_text']['#markup'] = t('You have finished this @quiz.', array('@quiz' => QUIZ_NAME));
    }

    return $out;
  }

}
