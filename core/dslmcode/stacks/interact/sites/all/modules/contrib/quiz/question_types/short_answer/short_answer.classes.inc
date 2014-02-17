<?php


/**
 * The main classes for the short answer question type.
 *
 * These inherit or implement code found in quiz_question.classes.inc.
 *
 * If you are developing your own question type, the easiest place to start is with
 * multichoice.classes.inc. short_answer and long_answer are good for understanding
 * question types that involve textual answers.
 *
 * @file
 */

/**
 * Extension of QuizQuestion.
 *
 * This could have extended long answer, except that that would have entailed
 * adding long answer as a dependency.
 */
class ShortAnswerQuestion extends QuizQuestion {

  // Constants for answer matching options
  const ANSWER_MATCH = 0;
  const ANSWER_INSENSITIVE_MATCH = 1;
  const ANSWER_REGEX = 2;
  const ANSWER_MANUAL = 3;

  /**
   * Implementation of saveNodeProperties
   *
   * @see QuizQuestion#saveNodeProperties($is_new)
   */
  public function saveNodeProperties($is_new = FALSE) {
    if ($is_new || $this->node->revision == 1) {
      $id = db_insert('quiz_short_answer_node_properties')
        ->fields(array(
          'nid' => $this->node->nid,
          'vid' => $this->node->vid,
          'correct_answer' => $this->node->correct_answer,
          'correct_answer_evaluation' => $this->node->correct_answer_evaluation,
        ))
        ->execute();
    }
    else {

      db_update('quiz_short_answer_node_properties')
        ->fields(array(
          'correct_answer' => $this->node->correct_answer,
          'correct_answer_evaluation' => $this->node->correct_answer_evaluation,
        ))
        ->condition('nid', $this->node->nid)
        ->condition('vid', $this->node->vid)
        ->execute();
    }
  }

  /**
   * Implementation of validateNode
   *
   * @see QuizQuestion#validateNode($form)
   */
  public function validateNode(array &$form) {
    if ($this->node->correct_answer_evaluation != self::ANSWER_MANUAL && empty($this->node->correct_answer)) {
      form_set_error('correct_answer', t('An answer must be specified for any evaluation type other than manual scoring.'));
    }
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestion#delete($only_this_version)
   */
  public function delete($only_this_version = FALSE) {
    parent::delete($only_this_version);
    $delete_ans = db_delete('quiz_short_answer_user_answers');
    $delete_ans->condition('question_nid', $this->node->nid);

    $delete_node = db_delete('quiz_short_answer_node_properties');
    $delete_node->condition('nid', $this->node->nid);

    if ($only_this_version) {
      $delete_ans->condition('question_vid', $this->node->vid);
      $delete_node->condition('vid', $this->node->vid);
    }

    $delete_ans->execute();
    $delete_node->execute();
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
    $res_a = db_query('SELECT correct_answer, correct_answer_evaluation FROM {quiz_short_answer_node_properties}
      WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();
    $this->nodeProperties = (is_array($res_a)) ? array_merge($props, $res_a) : $props;
    return $this->nodeProperties;
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
        '#markup' => '<div class="quiz-solution">' . check_plain($this->node->correct_answer) . '</div>',
        '#weight' => 2,
      );
    }
    else {
      $content['answers'] = array(
        '#markup' => '<div class="quiz-answer-hidden">Answer hidden</div>',
        '#weight' => 2,
      );
    }
    return $content;
  }

  /**
   * Implementation of getAnsweringForm
   *
   * @see QuizQuestion#getAnsweringForm($form_state, $rid)
   */
  public function getAnsweringForm(array $form_state = NULL, $rid) {
    $form = parent::getAnsweringForm($form_state, $rid);
    //$form['#theme'] = 'short_answer_answering_form';

    $form['tries'] = array(
      '#type' => 'textfield',
      '#title' => t('Answer'),
      '#description' => t('Enter your answer here'),
      '#default_value' => '',
      '#size' => 60,
      '#maxlength' => 256,
      '#required' => FALSE,
      '#attributes' => array('autocomplete' => 'off'),
    );

    if (isset($rid)) {
      $response = new ShortAnswerResponse($rid, $this->node);
      $form['tries']['#default_value'] = $response->getResponse();
    }

    return $form;
  }

  /**
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm($form_state)
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form['answer'] = array(
      '#type' => 'fieldset',
      '#title' => t('Answer'),
      '#description' => t('Provide the answer and the method by which the answer will be evaluated.'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -4,
    );

    $options = array(
      self::ANSWER_MATCH => t('Automatic and case sensitive'),
      self::ANSWER_INSENSITIVE_MATCH => t('Automatic. Not case sensitive'),
    );
    $access_regex = user_access('use regex for short answer');
    if ($access_regex) {
      $options[self::ANSWER_REGEX] = t('Match against a regular expression (answer must match the supplied regular expression)');
    }
    $options[self::ANSWER_MANUAL] = t('Manual');

    $form['answer']['correct_answer_evaluation'] = array(
      '#type' => 'radios',
      '#title' => t('Pick an evaluation method'),
      '#description' => t('Choose how the answer shall be evaluated.'),
      '#options' => $options,
      '#default_value' => isset($this->node->correct_answer_evaluation) ? $this->node->correct_answer_evaluation : self::ANSWER_MATCH,
      '#required' => FALSE,
    );
    if ($access_regex) {
      $form['answer']['regex_box'] = array(
        '#type' => 'fieldset',
        '#title' => t('About regular expressions'),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );

      $form['answer']['regex_box']['regex_help'] = array(
        '#markup' => '<p>' .
      t('Regular expressions are an advanced syntax for pattern matching. They allow you to create a concise set of rules that must be met before a value can be considered a match.') .
         '</p><p>' .
      t('For more on regular expression syntax, visit !url.', array('!url' => l('the PHP regular expressions documentation', 'http://www.php.net/manual/en/book.pcre.php'))) .
         '</p>',
      );
    }

    $form['answer']['correct_answer'] = array(
       '#type' => 'textfield',
       '#title' => t('Correct answer'),
       '#description' => t('Specify the answer. If this question is manually scored, no answer needs to be supplied.'),
       '#default_value' => isset($this->node->correct_answer) ? $this->node->correct_answer : '',
       '#size' => 60,
       '#maxlength' => 256,
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
    return variable_get('short_answer_default_max_score', 5);
  }

  /**
   * Evaluate the correctness of an answer based on the correct answer and evaluation method.
   */
  public function evaluateAnswer($user_answer) {
    $score = 0;
    switch ($this->node->correct_answer_evaluation) {
      case self::ANSWER_MATCH:
        if ($user_answer == $this->node->correct_answer) {
          $score = $this->node->max_score;
        }
        break;
      case self::ANSWER_INSENSITIVE_MATCH:
        if (drupal_strtolower($user_answer) == drupal_strtolower($this->node->correct_answer)) {
          $score = $this->node->max_score;
        }
        break;
      case self::ANSWER_REGEX:
        if (preg_match($this->node->correct_answer, $user_answer) > 0) {
          $score = $this->node->max_score;
        }
        break;
    }
    return $score;
  }
}

/**
 * Extension of QuizQuestionResponse
 */
class ShortAnswerResponse extends QuizQuestionResponse {
  /**
   * Get all quiz scores that haven't been evaluated yet.
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
    $query = db_select('quiz_short_answer_user_answers', 'a');
    $query->fields('a', array('result_id', 'question_nid', 'question_vid', 'answer_feedback'));
    $query->fields('r', array('title'));
    $query->fields('qnr', array('time_end', 'time_start', 'uid'));
    $query->join('node_revision', 'r', 'a.question_vid = r.vid');
    $query->join('quiz_node_results', 'qnr', 'a.result_id = qnr.result_id');
    $query->join('node', 'n', 'qnr.nid = n.nid');
    $query->condition('a.is_evaluated', 0);

    if (user_access('score own quiz') && user_access('score taken quiz answer')) {
      $query->condition(db_or()->condition('n.uid', $user->uid)->condition('qnr.uid', $user->uid));
    }
    else if (user_access('score own quiz')) {
      $query->condition('n.uid', $user->uid);
    }
    else if (user_access('score taken quiz answer')) {
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
   * Given a question, return a list of all of the unscored answers.
   *
   * @param $nid
   *  Node ID for the question to check.
   * @param $vid
   *  Version ID for the question to check.
   * @param $count
   *  Number of items to return (default: 50).
   * @param $offset
   *  Where in the results we should start (default: 0).
   *
   * @return
   *  Indexed array of result IDs that need to be scored.
   */
  public static function fetchUnscoredAnswersByQuestion($nid, $vid, $count = 50, $offset = 0) {
    return db_query('SELECT result_id FROM {quiz_short_answer_user_answers}
      WHERE is_evaluated = :is_evaluated AND question_nid = :question_nid AND question_vid = :question_vid',
      array(':is_evaluated' => 0, ':question_nid' => $nid, ':question_vid' => $vid)
    )->fetchCol();

  }

  /**
   * ID of the answer.
   */
  protected $answer_id = 0;

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $answer = NULL) {
    parent::__construct($result_id, $question_node, $answer);
    if (!isset($answer)) {
      $r = db_query('SELECT answer_id, answer, is_evaluated, score, question_vid, question_nid, result_id, answer_feedback
        FROM {quiz_short_answer_user_answers}
        WHERE question_nid = :qnid AND question_vid = :qvid AND result_id = :rid',
        array(':qnid' => $question_node->nid, ':qvid' => $question_node->vid, ':rid' => $result_id)
      )->fetch();

      if (!empty($r)) {
        $this->answer = $r->answer;
        $this->score = $r->score;
        $this->evaluated = $r->is_evaluated;
        $this->answer_id = $r->answer_id;
        $this->answer_feedback = $r->answer_feedback;
      }
    }
    else {
      if (is_array($answer)) {
        $this->answer = $answer['answer'];
      }
      else {
        $this->answer = $answer;
        $this->evaluated = $this->question->correct_answer_evaluation != ShortAnswerQuestion::ANSWER_MANUAL;
      }
    }
  }

  /**
   * Implementation of isValid
   *
   * @see QuizQuestionResponse#isValid()
   */
  public function isValid() {
    if (trim($this->answer) == '') {
      return t('You must provide an answer');
    }
    return TRUE;
  }

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {
    // We need to set is_evaluated depending on whether the type requires evaluation.
    $this->is_evaluated = (int) ($this->question->correct_answer_evaluation != ShortAnswerQuestion::ANSWER_MANUAL);
    $this->answer_id = db_insert('quiz_short_answer_user_answers')
      ->fields(array(
        'answer' => $this->answer,
        'question_nid' => $this->question->nid,
        'question_vid' => $this->question->vid,
        'result_id' => $this->rid,
        'score' => $this->getScore(FALSE),
        'is_evaluated' => $this->is_evaluated,
      ))
      ->execute();
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
    db_delete('quiz_short_answer_user_answers')
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->rid)
      ->execute();
  }

  /**
   * Implementation of score
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    // Manual scoring means we go with what is in the DB.
    if ($this->question->correct_answer_evaluation == ShortAnswerQuestion::ANSWER_MANUAL) {
      $score = db_query('SELECT score FROM {quiz_short_answer_user_answers} WHERE result_id = :result_id AND question_vid = :question_vid', array(':result_id' => $this->rid, ':question_vid' => $this->question->vid))->fetchField();
      if(!$score) {
        $score = 0;
      }
    }
    // Otherwise, we run the scoring automatically.
    else {
      $shortAnswer = new ShortAnswerQuestion($this->question);
      $score = $shortAnswer->evaluateAnswer($this->getResponse());
    }
    return $score;
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
   *
   * @see QuizQuestionResponse#getReportFormResponse($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $form = array();
    $form['#theme'] = 'short_answer_response_form';
    if ($this->question && !empty($this->question->answers)) {
      $answer = (object) current($this->question->answers);
    }
    else {
      return $form;
    }

    $form['answer'] = array(
      '#markup' => theme('short_answer_user_answer', array('answer' => check_plain($answer->answer), 'correct' => check_plain($this->question->correct_answer))),
    );

    if ($answer->is_evaluated == 1) {
      // Show feedback, if any.
      if ($showfeedback && !empty($answer->feedback)) { // @todo: Feedback doesn't seem to be in use anymore...
        $feedback = check_markup($answer->feedback);
      }
    }
    else {
      $feedback = t('This answer has not yet been scored.') .
        '<br/>' .
      t('Until the answer is scored, the total score will not be correct.');
    }

    if (!$allow_scoring && !empty($this->answer_feedback)) {
      $form['answer_feedback'] = array(
        '#title' => t('Feedback'),
        '#type' => 'item',
        '#markup' => '<span class="quiz_answer_feedback">' . $this->answer_feedback . '</span>',
      );
    }
    if (!empty($feedback)) {
      $form['feedback'] = array(
        '#markup' => '<span class="quiz_answer_feedback">' . $feedback . '</span>',
      );
    }
    return $form;
  }

  /**
   * Implementation of getReportFormScore
   *
   * @see QuizQuestionResponse#getReportFormScore($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportFormScore($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    $score = ($this->isEvaluated()) ? $this->getScore() : '?';
    if (quiz_access_to_score() && $allow_scoring) {
      return array(
        '#type' => 'textfield',
        '#default_value' => $score,
        '#size' => 3,
        '#maxlength' => 3,
        '#attributes' => array('class' => array('quiz-report-score')),
      );
    }
    else {
      return array(
        '#markup' => $score,
      );
    }
  }

  public function getReportFormAnswerFeedback($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    if (quiz_access_to_score() && $allow_scoring && $this->question->correct_answer_evaluation == ShortAnswerQuestion::ANSWER_MANUAL) {
      return array(
        '#title' => t('Enter feedback'),
        '#type' => 'textarea',
        '#default_value' => $this->answer_feedback,
        '#attributes' => array('class' => array('quiz-report-score')),
      );
    }
    return FALSE;
  }

  /**
   * Implementation of getReportFormSubmit
   *
   * @see QuizQuestionResponse#getReportFormSubmit($showfeedback, $showpoints, $allow_scoring)
   */
  public function getReportFormSubmit($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    if (quiz_access_to_score() && $allow_scoring) {
      return $allow_scoring ? 'short_answer_report_submit' : FALSE;
    }
    return FALSE;
  }

  /**
   * Implementation of getReportFormValidate
   *
   * @see QuizQuestionResponse#getReportFormValidate($showfeedback, $showpoints, $allow_scoring)
   */
  public function getReportFormValidate($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    if (quiz_access_to_score() && $allow_scoring) {
      return $allow_scoring ? 'short_answer_report_validate' : FALSE;
    }
    return FALSE;
  }
}
