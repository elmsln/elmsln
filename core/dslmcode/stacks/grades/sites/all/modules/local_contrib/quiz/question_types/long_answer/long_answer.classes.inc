<?php

/**
 * @file
 * Long answer classes.
 *
 * This module uses the question interface to define the long_answer question
 * type.
 */

/**
 * Extension of QuizQuestion.
 */
class LongAnswerQuestion extends QuizQuestion {

  /**
   * Implementation of saveNodeProperties().
   *
   * @see QuizQuestion::saveNodeProperties()
   */
  public function saveNodeProperties($is_new = FALSE) {
    db_merge('quiz_long_answer_node_properties')
      ->key(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
      ))
      ->fields(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
        'rubric' => $this->node->rubric['value'],
        'rubric_format' => $this->node->rubric['format'],
        'answer_text_processing' => $this->node->answer_text_processing,
      ))
      ->execute();
  }

  /**
   * Implementation of validateNode().
   *
   * @see QuizQuestion::validateNode()
   */
  public function validateNode(array &$form) {

  }

  /**
   * Implementation of delete().
   *
   * @see QuizQuestion::delete()
   */
  public function delete($only_this_version = FALSE) {
    $delete_node = db_delete('quiz_long_answer_node_properties');
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

    $res_a = db_query('SELECT rubric as value, rubric_format as format, answer_text_processing FROM {quiz_long_answer_node_properties}
      WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();

    if (is_array($res_a)) {
      $props = array(
        'rubric' => array(
          'value' => $res_a['value'],
          'format' => $res_a['format'],
        ),
        'answer_text_processing' => $res_a['answer_text_processing'],
      );
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
      $content['answers'] = array(
        '#type' => 'item',
        '#title' => t('Rubric'),
        '#markup' => '<div class="quiz-solution">' . check_markup($this->node->rubric['value'], $this->node->rubric['format']) . '</div>',
        '#weight' => 1,
      );
    }
    else {
      $content['answers'] = array(
        '#markup' => '<div class="quiz-answer-hidden">Answer hidden</div>',
        '#weight' => 1,
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
      '#title' => t('Answer'),
      '#description' => t('Enter your answer here. If you need more space, click on the grey bar at the bottom of this area and drag it down.'),
      '#rows' => 15,
      '#cols' => 60,
    );

    if ($this->node->answer_text_processing) {
      $element['#type'] = 'text_format';
    }
    else {
      $element['#type'] = 'textarea';
    }

    if (isset($result_id)) {
      if ($response = _quiz_question_response_get_instance($result_id, $this->node)) {
        if ($user_response = $response->getResponse()) {
          $element['#default_value'] = $user_response;
          $element['#format'] = $response->answer_format;
        }
      }
    }
    return $element;
  }

  /**
   * Question response validator.
   */
  public function getAnsweringFormValidate(array &$element, &$value) {
    if ($value == '') {
      form_error($element, t('You must provide an answer.'));
    }
  }

  /**
   * Implementation of getCreationForm().
   *
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form = array();

    $form['rubric'] = array(
      '#type' => 'text_format',
      '#title' => t('Rubric'),
      '#description' => t('Specify the criteria for grading the response.'),
      '#default_value' => isset($this->node->rubric['value']) ? $this->node->rubric['value'] : '',
      '#format' => isset($this->node->rubric['format']) ? $this->node->rubric['format'] : filter_default_format(),
      '#size' => 60,
      '#required' => FALSE,
    );

    $form['answer_text_processing'] = array(
      '#title' => t('Answer text processing'),
      '#description' => t('Allowing filtered text may enable the user to input HTML tags in their answer.'),
      '#type' => 'radios',
      '#options' => array(
        0 => t('Plain text'),
        1 => t('Filtered text (user selects text format)'),
      ),
      '#default_value' => isset($this->node->answer_text_processing) ? $this->node->answer_text_processing : 0,
    );

    return $form;
  }

  /**
   * Implementation of getMaximumScore().
   *
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {
    return variable_get('long_answer_default_max_score', 10);
  }

}

/**
 * Extension of QuizQuestionResponse.
 */
class LongAnswerResponse extends QuizQuestionResponse {

  /**
   * ID of the answer.
   */
  protected $answer_id = 0;
  private $answer_feedback;
  private $answer_feedback_format;

  /**
   * Constructor.
   *
   * @param int $result_id
   *   The result ID for the user's result set. There is one result ID per time
   *   the user takes a quiz.
   * @param stdClass $question_node
   *   The question node.
   * @param mixed $answer
   *   The answer (dependent on question type).
   */
  public function __construct($result_id, stdClass $question_node, $answer = NULL) {
    parent::__construct($result_id, $question_node, $answer);

    if (!isset($answer)) {
      // Question has been answered already. We fetch the answer data from the
      // database.
      $r = db_query('SELECT *
        FROM {quiz_long_answer_user_answers}
        WHERE result_answer_id = :raid', array(':raid' => $this->result_answer_id))->fetch();

      if (!empty($r)) {
        $this->answer = $r->answer;
        $this->answer_format = $r->answer_format;
        $this->score = $r->score;
        $this->evaluated = $r->is_evaluated;
        $this->answer_id = $r->answer_id;
        $this->answer_feedback = $r->answer_feedback;
        $this->answer_feedback_format = $r->answer_feedback_format;
      }
    }
    else {
      $this->answer = $answer;
      $this->evaluated = FALSE;
    }
  }

  /**
   * Implementation of save().
   *
   * @see QuizQuestionResponse::save()
   */
  public function save() {
    if (!$this->quizQuestion->node->answer_text_processing) {
      $answer = $this->answer;
      $this->answer = array();
      $this->answer['value'] = $answer;
      $this->answer['format'] = 'plain_text';
    }
    db_merge('quiz_long_answer_user_answers')
      ->key(array('result_answer_id' => $this->result_answer_id))
      ->fields(array(
        'answer' => $this->answer['value'],
        'answer_format' => $this->answer['format'],
        'result_answer_id' => $this->result_answer_id,
      ))
      ->execute();
  }

  /**
   * Implementation of delete().
   *
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {
    db_delete('quiz_long_answer_user_answers')
      ->condition('result_answer_id', $this->result_answer_id)
      ->execute();
  }

  /**
   * Implementation of score().
   *
   * @see QuizQuestionResponse::score()
   */
  public function score() {
    return (int) db_query('SELECT score FROM {quiz_long_answer_user_answers}
      WHERE result_answer_id = :raid', array(':raid' => $this->result_answer_id))->fetchField();
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
   * Implementation of getFeedbackValues().
   *
   * @see QuizQuestionResponse::getFeedbackValues()
   */
  public function getFeedbackValues() {
    $data = array();

    $data[] = array(
      // Hide this column. Does not make sense for long answer as there are no
      // choices.
      'choice' => NULL,
      'attempt' => check_markup($this->answer, $this->answer_format),
      'correct' => $this->question->answers[0]['is_correct'] ? quiz_icon('correct') : '',
      'score' => !$this->evaluated ? t('This answer has not yet been scored.') : $this->getScore(),
      'answer_feedback' => check_markup($this->answer_feedback, $this->answer_feedback_format),
      'solution' => check_markup($this->question->rubric['value'], $this->question->rubric['format']),
    );

    return $data;
  }

  /**
   * Implementation of getReportFormAnswerFeedback().
   *
   * @see QuizQuestionResponse::getReportFormAnswerFeedback()
   */
  public function getReportFormAnswerFeedback() {
    return array(
      '#title' => t('Enter feedback'),
      '#type' => 'text_format',
      '#default_value' => isset($this->answer_feedback) ? check_markup($this->answer_feedback, $this->answer_feedback_format) : '',
      '#format' => isset($this->answer_feedback_format) ? $this->answer_feedback_format : filter_default_format(),
      '#attributes' => array('class' => array('quiz-report-score')),
    );
  }

  /**
   * Implementation of getReportFormSubmit().
   *
   * @see QuizQuestionResponse::getReportFormSubmit()
   */
  public function getReportFormSubmit() {
    return 'long_answer_report_submit';
  }

}
