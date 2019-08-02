<?php

/**
 * @file
 * Quiz page classes.
 *
 * This module uses the question interface to define something which is
 * actually not a question.
 *
 * A Quiz page node is a placeholder for presenting multiple questions
 * on the same page.
 */

/**
 * Extension of QuizQuestion.
 */
class QuizPagesQuestion extends QuizQuestion {

  /**
   * Implementation of validateNode().
   *
   * @see QuizQuestion::validateNode()
   */
  public function validateNode(array &$form) {

  }

  /**
   * Implementation of saveNodeProperties().
   *
   * @see QuizQuestion::saveNodeProperties()
   */
  public function saveNodeProperties($is_new = FALSE) {

  }

  /**
   * Implementation of getAnsweringForm().
   *
   * @see QuizQuestion::getAnsweringForm()
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $element = array(
      '#type' => 'hidden',
    );
    return $element;
  }

  /**
   * Implementation of getBodyFieldTitle().
   *
   * @see QuizQuestion::getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('Page');
  }

  /**
   * Implementation of getCreationForm().
   *
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    return array();
  }

  /**
   * Implementation of getMaximumScore().
   *
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {
    return 0;
  }

  /**
   * Implementation of isGraded().
   *
   * @see QuizQuestion::isGraded()
   */
  public function isGraded() {
    return FALSE;
  }

  /**
   * Implementation of hasFeedback().
   *
   * @see QuizQuestion::hasFeedback()
   */
  public function hasFeedback() {
    return FALSE;
  }

  /**
   * Implementation of isQuestion().
   *
   * @see QuizQuestion::hasFeedback()
   */
  public function isQuestion() {
    return FALSE;
  }

}

/**
 * Extension of QuizQuestionResponse.
 */
class QuizPagesResponse extends QuizQuestionResponse {

  /**
   * Implementation of save().
   *
   * @see QuizQuestionResponse::save()
   */
  public function save() {

  }

  /**
   * Implementation of delete().
   *
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {

  }

  /**
   * Implementation of score().
   *
   * @see QuizQuestionResponse::score()
   */
  public function score() {

  }

  /**
   * Implementation of isCorrect().
   *
   * @see QuizQuestionResponse::isCorrect()
   */
  public function isCorrect() {
    return TRUE;
  }

  /**
   * Implementation of getResponse().
   *
   * @see QuizQuestionResponse::getResponse()
   */
  public function getResponse() {
    return $this->answer;
  }

  /**
   * Implementation of getReportForm().
   *
   * @see QuizQuestionResponse::getReportForm()
   */
  public function getReportForm() {
    return array(
      '#no_report' => TRUE,
    );
  }

}
