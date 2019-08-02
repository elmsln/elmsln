<?php

class QuizResult extends Entity {

  /**
   * Get the layout for this quiz result.
   *
   * The layout contains the questions to be delivered.
   *
   * @return QuizResultAnswer[]
   */
  public function getLayout() {
    $layouts = drupal_static('quiz_result_layout', array());

    if (!isset($layouts[$this->identifier()])) {
      $quiz_node_relationships = entity_load('quiz_question_relationship', FALSE, array(
        'parent_nid' => $this->nid,
        'parent_vid' => $this->vid,
      ));
      $relationships = array();
      foreach ($quiz_node_relationships as $quiz_node_relationship) {
        $relationships[$quiz_node_relationship->child_nid] = $quiz_node_relationship;
      }
      $layout = array();

      $quiz_result_answers = entity_load('quiz_result_answer', FALSE, array('result_id' => array($this->identifier())));
      if ($quiz_result_answers) {
        foreach ($quiz_result_answers as $quiz_result_answer) {
          if (!empty($relationships[$quiz_result_answer->question_nid])) {
            $relationship = $relationships[$quiz_result_answer->question_nid];
          }

          $layout[$quiz_result_answer->number] = array(
            'result_answer_id' => $quiz_result_answer->result_answer_id,
            'display_number' => $quiz_result_answer->display_number,
            'nid' => $quiz_result_answer->question_nid,
            'vid' => $quiz_result_answer->question_vid,
            'tid' => $quiz_result_answer->tid,
            'number' => $quiz_result_answer->number,
            'qnr_id' => isset($relationship) ? $relationship->qnr_id : NULL,
            'qnr_pid' => isset($relationship) ? $relationship->qnr_pid : NULL,
          );
        }
        ksort($layout, SORT_NUMERIC);
        $layouts[$this->identifier()] = $layout;
      }
    }

    return $layouts[$this->identifier()];
  }

  /**
   * Get the label for this quiz result.
   *
   * @return string
   */
  protected function defaultLabel() {
    $quiz = node_load($this->nid, $this->vid);
    $user = user_load($this->uid);

    return t('@user\'s @quiz result in "@title"', array(
      '@user' => format_username($user),
      '@quiz' => QUIZ_NAME, '@title' => $quiz->title,
    ));
  }

}
