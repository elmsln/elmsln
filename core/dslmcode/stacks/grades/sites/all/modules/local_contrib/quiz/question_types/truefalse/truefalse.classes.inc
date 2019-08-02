<?php

/**
 * @file
 * TrueFalse classes.
 *
 * This module uses the question interface to define the True/False question
 * type.
 */

/**
 * Extension of QuizQuestion.
 */
class TrueFalseQuestion extends QuizQuestion {

  /**
   * Implementation of saveNodeProperties().
   *
   * @see QuizQuestion::saveNodeProperties()
   */
  public function saveNodeProperties($is_new = FALSE) {
    db_merge('quiz_truefalse_node')
      ->key(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
      ))
      ->fields(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
        'correct_answer' => $this->node->correct_answer,
      ))
      ->execute();
  }

  /**
   * Implementation of validateNode().
   *
   * @see QuizQuestion::validateNode()
   */
  public function validateNode(array &$form) {
    // This space intentionally left blank. :)
  }

  /**
   * Implementation of delete().
   *
   * @see QuizQuestion::delete()
   */
  public function delete($only_this_version = FALSE) {
    $delete_node = db_delete('quiz_truefalse_node');
    $delete_node->condition('nid', $this->node->nid);
    if ($only_this_version) {
      $delete_node->condition('vid', $this->node->vid);
    }
    $delete_node->execute();

    parent::delete($only_this_version);
  }

  /**
   * Implementation of getNodeProperties().
   *
   * @see QuizQuestion::getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    $res_a = db_query('SELECT correct_answer FROM {quiz_truefalse_node} WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();

    if (is_array($res_a)) {
      $props = array_merge($props, $res_a);
    }
    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Implementation of getNodeView().
   *
   * @see QuizQuestion::getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();
    if ($this->viewCanRevealCorrect()) {
      $answer = ($this->node->correct_answer) ? t('True') : t('False');
      $content['answers']['#markup'] = '<div class="quiz-solution">' . $answer . '</div>';
      $content['answers']['#weight'] = 2;
    }
    else {
      $content['answers'] = array(
        '#markup' => '<div class="quiz-answer-hidden">' . t('Answer hidden') . '</div>',
        '#weight' => 2,
      );
    }
    return $content;
  }

  /**
   * Implementation of getAnsweringForm().
   *
   * @see QuizQuestion::getAnsweringForm()
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $element = parent::getAnsweringForm($form_state, $result_id);
    $element += array(
      '#type' => 'radios',
      '#title' => t('Choose one'),
      '#options' => array(
        1 => t('True'),
        0 => t('False'),
      ),
    );

    if (isset($result_id)) {
      $response = new TrueFalseResponse($result_id, $this->node);
      $default = $response->getResponse();
      $element['#default_value'] = is_null($default) ? NULL : $default;
    }

    return $element;
  }

  /**
   * Question response validator.
   */
  public function getAnsweringFormValidate(array &$element, &$value) {
    if (is_null($value)) {
      form_error($element, t('You must provide an answer.'));
    }
  }

  /**
   * Implementation of getBodyFieldTitle().
   *
   * @see QuizQuestion::getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('True/false statement');
  }

  /**
   * Implementation of getCreationForm().
   *
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form['correct_answer'] = array(
      '#type' => 'radios',
      '#title' => t('Correct answer'),
      '#options' => array(
        1 => t('True'),
        0 => t('False'),
      ),
      '#default_value' => isset($this->node->correct_answer) ? $this->node->correct_answer : 1,
      '#required' => TRUE,
      '#weight' => -4,
      '#description' => t('Choose if the correct answer for this question is "true" or "false".'),
    );
    return $form;
  }

  /**
   * Implementation of getMaximumScore().
   *
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {
    return 1;
  }

  /**
   * Get the correct answer to this question.
   *
   * This is a utility function. It is not defined in the interface.
   *
   * @return bool
   *   Boolean indicating if the correct answer is TRUE or FALSE
   */
  public function getCorrectAnswer() {
    return db_query('SELECT correct_answer FROM {quiz_truefalse_node} WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchField();
  }

}

/**
 * Extension of QuizQuestionResponse.
 */
class TrueFalseResponse extends QuizQuestionResponse {

  /**
   * Constructor.
   *
   * @param int $result_id
   *   The result ID for the user's result set. There is one result ID per time
   *   the user takes a quiz.
   * @param stdClass $question_node
   *   The question node.
   * @param mixed $answer
   *   The answer.
   */
  public function __construct($result_id, stdClass $question_node, $answer = NULL) {
    parent::__construct($result_id, $question_node, $answer);
    if (!isset($answer)) {
      // Get from DB.
      $r = $this->getUserAnswer();
      if (!empty($r)) {
        $this->answer = $r->answer;
        $this->score = $r->score;
      }
    }
    else {
      // Load from input.
      $this->answer = $answer;
    }
  }

  /**
   * Implementation of save().
   *
   * @see QuizQuestionResponse::save()
   */
  public function save() {
    db_merge('quiz_truefalse_user_answers')
      ->key(array('result_answer_id' => $this->result_answer_id))
      ->fields(array(
        'result_answer_id' => $this->result_answer_id,
        'answer' => (int) $this->answer,
        'score' => (int) $this->getScore(),
      ))
      ->execute();
  }

  /**
   * Implementation of delete().
   *
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {
    db_delete('quiz_truefalse_user_answers')
      ->condition('result_answer_id', $this->result_answer_id)
      ->execute();
  }

  /**
   * Implementation of score().
   *
   * @see QuizQuestionResponse::score()
   */
  public function score() {
    $tfQuestion = new TrueFalseQuestion($this->question);
    return ($this->getResponse() == $tfQuestion->getCorrectAnswer()) ? 1 : 0;
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
   * Get the user's answer from the database.
   *
   * @return array
   *   An array containing both the answer and the score
   */
  public function getUserAnswer() {
    if (isset($this->result_answer_id)) {
      return db_query('SELECT answer, score FROM {quiz_truefalse_user_answers} WHERE result_answer_id = :raid', array(':raid' => $this->result_answer_id))->fetch();
    }
  }

  /**
   * Implementation of getFeedbackValues().
   *
   * @see QuizQuestionResponse::getFeedbackValues()
   */
  public function getFeedbackValues() {

    $answer = $this->question->answers[0]['answer'];
    if (!is_null($answer)) {
      $answer = intval($answer);
    }
    $correct_answer = intval($this->question->correct_answer);

    $data = array();
    $data[] = array(
      'choice' => t('True'),
      'attempt' => $answer === 1 ? quiz_icon('selected') : '',
      'correct' => $answer === 1 ? quiz_icon($correct_answer ? 'correct' : 'incorrect') : '',
      'score' => intval($correct_answer === 1 && $answer === 1),
      'answer_feedback' => '',
      'solution' => $correct_answer === 1 ? quiz_icon('should') : '',
    );

    $data[] = array(
      'choice' => t('False'),
      'attempt' => $answer === 0 ? quiz_icon('selected') : '',
      'correct' => $answer === 0 ? (quiz_icon(!$correct_answer ? 'correct' : 'incorrect')) : '',
      'score' => intval($correct_answer === 0 && $answer === 0),
      'answer_feedback' => '',
      'solution' => $correct_answer === 0 ? quiz_icon('should') : '',
    );

    return $data;
  }

  /**
   * Get answers for a question in a result.
   *
   * This static method assists in building views for the mass export of
   * question answers.
   *
   * @see views_handler_field_prerender_list for the expected return value.
   */
  public static function viewsGetAnswers(array $result_answer_ids = array()) {
    $items = array();
    foreach ($result_answer_ids as $result_answer_id) {
      $ra = entity_load_single('quiz_result_answer', $result_answer_id);
      $question = node_load($ra->question_nid, $ra->question_vid);
      /* @var $ra_i QuizQuestionResponse */
      $ra_i = _quiz_question_response_get_instance($ra->result_id, $question);
      $items[$ra->result_id][] = array('answer' => $ra_i->getResponse() ? t('True') : t('False'));
    }
    return $items;
  }

}
