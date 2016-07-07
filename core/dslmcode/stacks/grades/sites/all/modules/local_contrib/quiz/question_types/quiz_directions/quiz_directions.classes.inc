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
   * Implementation of validateNode
   *
   * @see QuizQuestion#validateNode($form)
   */
  public function validateNode(array &$form) {

  }

  /**
   * Implementation of saveNodeProperties
   *
   * @see QuizQuestion#saveNodeProperties($is_new)
   */
  public function saveNodeProperties($is_new = FALSE) {

  }

  /**
   * Implementation of getAnsweringForm
   *
   * @see QuizQuestion#getAnsweringForm($form_state, $result_id)
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $form = parent::getAnsweringForm($form_state, $result_id);

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

  public function isGraded() {
    return FALSE;
  }

  public function hasFeedback() {
    return FALSE;
  }

  public function isQuestion() {
    return FALSE;
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
  public function save() {

  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {

  }

  /**
   * Implementation of score
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
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
   * @see QuizQuestionResponse#getReportForm()
   */
  public function getReportForm() {
    return array(
      '#no_report' => TRUE,
    );
  }

}
