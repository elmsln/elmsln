<?php

/**
 * quiz_directions.classes
 *
 * This module uses the question interface to define something which is actually not a question.
 *
 * A Quiz Directions node is a placeholder for adding directions to a quiz. It can be inserted any number
 * of times into a quiz. Example uses may include:
 *
 * - Initial quiz-wide directions
 * - Section directions, e.g. "The next five questions are multiple choice, please..." (Won't work if the question order is randomized)
 * - Final confirmation, e.g. "You have answered all questions. Click submit to submit this quiz."
 *
 * @file
 */

/**
 * Extension of QuizQuestion.
 */
class QuizDirectionsQuestion extends QuizQuestion {

  /**
   * Constructor
   */
  public function __construct(stdClass $node) {
    parent::__construct($node);
    $this->node->no_skip_button = TRUE; // No skip button
    $this->node->not_a_question = TRUE;
  }

  /**
   * Implementation of validateNode
   *
   * @see QuizQuestion#validateNode($form)
   */
  public function validateNode(array &$form) { }

  /**
   * Implementation of saveNodeProperties
   *
   * @see QuizQuestion#saveNodeProperties($is_new)
   */
  public function saveNodeProperties($is_new = FALSE) { }

  /**
   * Implementation of getAnsweringForm
   *
   * @see QuizQuestion#getAnsweringForm($form_state, $rid)
   */
  public function getAnsweringForm(array $form_state = NULL, $rid) {
    $form = parent::getAnsweringForm($form_state, $rid);

    $form['tries'] = array(
      '#type' => 'hidden',
      '#value' => 0,
    );
    $form['empty_space'] = array(
      '#type' => 'markup',
      '#value' => '<br/>',
    );
    return $form;
  }

  /**
   * Implementation of getBodyFieldTitle
   *
   * @see QuizQuestion#getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('Direction');
  }

  /**
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm($form_state)
   */
  public function getCreationForm(array &$form_state = NULL) {
    return array();
  }

  /**
   * Implementation of getMaximumScore
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    return 0;
  }
}

/**
 * Extension of QuizQuestionResponse
 */
class QuizDirectionsResponse extends QuizQuestionResponse {

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() { }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() { }

  /**
   * Implementation of score
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    // First, due to popular demand, if the directions are at the beginning of
    // the quiz, we restart the timer after the user has read the question.
    $quiz_nid = arg(1);
    $quiz_key = 'quiz_' . $quiz_nid;
    if (isset($_SESSION[$quiz_key]['previous_quiz_questions']) && count($_SESSION[$quiz_key]['previous_quiz_questions']) === 1) {
      // reset the timer.
      $sql = 'UPDATE {quiz_node_results} SET time_start=%d WHERE result_id = %d';
      // TODO Please review the conversion of this statement to the D7 database API syntax.
      /* db_query($sql, REQUEST_TIME, $this->rid) */
      db_update('quiz_node_results')
  ->fields(array(
    'time_start' => REQUEST_TIME,
  ))
  ->condition('result_id', $this->rid)
  ->execute();
    }

    // Set the score
    $this->score = 0;
    return 0;
  }

  /**
   * Implementation of isCorrect
   *
   * @see QuizQuestionResponse#isCorrect()
   */
  public function isCorrect() {
    return TRUE;
  }

  /**
   * Implementation of getResponse
   *
   * @see QuizQuestionResponse#getResponse()
   */
  public function getResponse() {
    return $this->answer;
  }

  /**
   * Implementation of getReportForm
   *
   * @see QuizQuestionResponse#getReportForm($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportForm($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    return array(
      '#no_report' => TRUE,
    );
  }
}




