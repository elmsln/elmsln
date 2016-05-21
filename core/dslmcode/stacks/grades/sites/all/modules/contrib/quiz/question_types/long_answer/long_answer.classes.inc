<?php

/**
 * Long answer classes.
 *
 * @file
 *  Classes modelling the long answer question and the long answer question response
 */

/**
 * Extension of QuizQuestion.
 */
class LongAnswerQuestion extends QuizQuestion {

  /**
   * Implementation of saveNodeProperties
   * @see QuizQuestion#saveNodeProperties()
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
        'rubric' => $this->node->rubric,
      ))
      ->execute();
  }

  /**
   * Implementation of validateNode
   *
   * @see QuizQuestion#validateNode($form)
   */
  public function validateNode(array &$form) {

  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestion#delete($only_this_version)
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
   * Implementation of getNodeProperties
   *
   * @see QuizQuestion#getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    $res_a = db_query('SELECT rubric FROM {quiz_long_answer_node_properties}
      WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();

    if (is_array($res_a)) {
      $props = array_merge($props, $res_a);
    }

    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Implementation of getNodeView
   *
   * @see QuizQuestion#getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();
    if ($this->viewCanRevealCorrect()) {
      $content['answers'] = array(
        '#type' => 'item',
        '#title' => t('Rubric'),
        '#markup' => '<div class="quiz-solution">' . check_markup($this->node->rubric, $this->getFormat()) . '</div>',
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
   * Implementation of getAnweringForm
   *
   * @see QuizQuestion#getAnsweringForm($form_state, $result_id)
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $element = parent::getAnsweringForm($form_state, $result_id);

    $element += array(
      '#type' => 'textarea',
      '#title' => t('Answer'),
      '#description' => t('Enter your answer here. If you need more space, click on the grey bar at the bottom of this area and drag it down.'),
      '#rows' => 15,
      '#cols' => 60,
      //'#theme' =>'long_answer_answering_form',
    );
    if (isset($result_id)) {
      $response = new LongAnswerResponse($result_id, $this->node);
      $element['#default_value'] = $response->getResponse();
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
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm($form_state)
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form['rubric'] = array(
      '#type' => 'textarea',
      '#title' => t('Rubric'),
      '#description' => t('Specify the criteria for grading the response.'),
      '#default_value' => isset($this->node->rubric) ? $this->node->rubric : '',
      '#size' => 60,
      '#required' => FALSE,
    );
    return $form;
  }

  /**
   * Implementation of getMaximumScore
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    return variable_get('long_answer_default_max_score', 10);
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class LongAnswerResponse extends QuizQuestionResponse {

  /**
   * Get all scores that have not yet been evaluated.
   *
   * @param $count
   *  Number of items to return (default: 50).
   * @param $offset
   *  Where in the results we should start (default: 0).
   *
   * @return
   *  Array of objects describing unanswered questions. Each object will have result_id, question_nid, and question_vid.
   */
  public static function fetchAllUnscoredAnswers($count = 50, $offset = 0) {
    global $user;
    $query = db_select('quiz_long_answer_user_answers', 'a');
    $query->fields('a', array('answer_feedback', 'answer_feedback_format'));
    $query->fields('r', array('title'));
    $query->fields('qnr', array('time_end', 'time_start', 'uid'));
    $query->fields('qnra', array('result_id', 'question_nid', 'question_vid'));
    $query->join('quiz_node_results_answers', 'qnra', 'a.result_answer_id = qnra.result_answer_id');
    $query->join('node_revision', 'r', 'qnra.question_vid = r.vid');
    $query->join('quiz_node_results', 'qnr', 'qnra.result_id = qnr.result_id');
    $query->join('node', 'n', 'qnr.nid = n.nid');
    $query->condition('a.is_evaluated', 0);
    if (user_access('score own quiz') && user_access('score taken quiz answer')) {
      $query->condition(db_or()->condition('n.uid', $user->uid)->condition('qnr.uid', $user->uid));
    }
    elseif (user_access('score own quiz')) {
      $query->condition('n.uid', $user->uid);
    }
    elseif (user_access('score taken quiz answer')) {
      $query->condition('qnr.uid', $user->uid);
    }
    $results = $query->execute();
    $unscored = array();
    foreach ($results as $row) {
      $unscored[] = $row;
    }
    return $unscored;
  }

  /**
   * Given a quiz, return a list of all of the unscored answers.
   *
   * @param $nid
   *  Node ID for the quiz to check.
   * @param $vid
   *  Version ID for the quiz to check.
   * @param $count
   *  Number of items to return (default: 50).
   * @param $offset
   *  Where in the results we should start (default: 0).
   *
   * @return
   *  Indexed array of result IDs that need to be scored.
   */
  public static function fetchUnscoredAnswersByQuestion($nid, $vid, $count = 50, $offset = 0) {
    $results = db_query('SELECT result_id FROM {quiz_long_answer_user_answers}
      WHERE is_evaluated = :is_evaluated
      AND question_nid = :question_nid
      AND question_vid = :question_vid', array(':is_evaluated' => 0, ':question_nid' => $nid, ':question_vid' => $vid));
    $unscored = array();
    foreach ($results as $row) {
      $unscored[] = $row->result_id;
    }
    return $unscored;
  }

  /**
   * ID of the answer.
   */
  protected $answer_id = 0;
  private $answer_feedback;
  private $answer_feedback_format;

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $answer = NULL) {
    parent::__construct($result_id, $question_node, $answer);

    if (!isset($answer)) {
      // Question has been answered allready. We fetch the answer data from the database.
      $r = db_query('SELECT *
        FROM {quiz_long_answer_user_answers}
        WHERE result_answer_id = :raid', array(':raid' => $this->result_answer_id))->fetch();

      if (!empty($r)) {
        $this->answer = $r->answer;
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
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {
    db_merge('quiz_long_answer_user_answers')
      ->key(array('result_answer_id' => $this->result_answer_id))
      ->fields(array(
        'answer' => $this->answer,
        'result_answer_id' => $this->result_answer_id,
      ))
      ->execute();
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
    db_delete('quiz_long_answer_user_answers')
      ->condition('result_answer_id', $this->result_answer_id)
      ->execute();
  }

  /**
   * Implementation of score
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    return (int) db_query('SELECT score FROM {quiz_long_answer_user_answers}
      WHERE result_answer_id = :raid', array(':raid' => $this->result_answer_id))->fetchField();
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
   * Implementation of getReportFormResponse
   */
  public function getFeedbackValues() {
    $data = array();

    $data[] = array(
      // Hide this column. Does not make sense for long answer as there are no choices.
      'choice' => NULL,
      'attempt' => $this->answer,
      'correct' => $this->question->answers[0]['is_correct'] ? quiz_icon('correct') : quiz_icon(''),
      'score' => !$this->evaluated ? t('This answer has not yet been scored.') : $this->getScore(),
      'answer_feedback' => check_markup($this->answer_feedback, $this->answer_feedback_format),
      'solution' => $this->question->rubric,
    );

    return $data;
  }

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
   * Implementation of getReportFormSubmit
   *
   * @see QuizQuestionResponse#getReportFormSubmit()
   */
  public function getReportFormSubmit() {
    return 'long_answer_report_submit';
  }

}
