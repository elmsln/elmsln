<?php

/**
 * @file quiz_page.classes.inc
 * Support class for Quiz pages.
 */

/**
 * Extension of QuizQuestion.
 */
class QuizPagesQuestion extends QuizQuestion {

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
   * Implementation of getBodyFieldTitle
   *
   * @see QuizQuestion#getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('Page');
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

  function getAnsweringForm(array $form_state = NULL, $result_id) {
    $element = array(
      '#type' => 'hidden',
    );
    return $element;
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class QuizPagesResponse extends QuizQuestionResponse {

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
