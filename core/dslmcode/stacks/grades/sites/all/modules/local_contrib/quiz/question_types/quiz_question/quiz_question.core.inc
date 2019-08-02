<?php

/**
 * @file
 * Classes used in the Quiz Question module.
 *
 * The core of the Quiz Question module is a set of abstract classes that
 * can be used to quickly and efficiently create new question types.
 *
 * Why OO?
 * Drupal has a long history of avoiding many of the traditional OO structures
 * and metaphors. However, with PHP 5, there are many good reasons to use OO
 * principles more broadly.
 *
 * The case for Quiz question types is that question types all share common
 * structure and logic. Using the standard hook-only Drupal metaphor, we are
 * forced to copy and paste large amounts of repetitive code from question
 * type to question type. By using OO principles and construction, we can
 * easily encapsulate much of that logic, while still making it easy to
 * extend the existing content.
 *
 * Where do I start?
 * To create a new question type, check out the multichoice question type for
 * instance.
 */

/**
 * A base implementation of a quiz_question.
 *
 * This class is adding a layer of abstraction between the node API, quiz API
 * and the question types.
 *
 * It is required that Question types extend this abstract class.
 *
 * This class has default behaviour that all question types must have. It also
 * handles the node API, but gives the question types opportunity to save,
 * delete and provide data specific to the question types.
 *
 * This abstract class also declares several abstract functions forcing
 * question-types to implement required methods.
 */
abstract class QuizQuestion {
  /*
   * QUESTION IMPLEMENTATION FUNCTIONS
   *
   * This part acts as a contract(/interface) between the question-types and the
   * rest of the system.
   *
   * Question types are made by extending these generic methods and abstract
   * methods.
   */

  /**
   * The current node for this question.
   */
  public $node = NULL;
  // Extra node properties.
  public $nodeProperties = NULL;

  /**
   * QuizQuestion constructor stores the node object.
   *
   * @param $node
   *   The node object
   */
  public function __construct(stdClass $node) {
    $this->node = $node;
  }

  /**
   * Allow question types to override the body field title.
   *
   * @return string
   *   The title for the body field.
   */
  public function getBodyFieldTitle() {
    return t('Question');
  }

  /**
   * Returns a node form to quiz_question_form.
   *
   * Adds default form elements, and fetches question type specific elements
   * from their implementation of getCreationForm.
   *
   * @param array $form_state
   *
   * @return array
   *   An renderable FAPI array.
   */
  public function getNodeForm(array &$form_state = NULL) {
    global $user;
    $form = array();

    // Mark this form to be processed by quiz_form_alter. quiz_form_alter will
    // among other things hide the revision fieldset if the user don't have
    // permission to control the revisioning manually.
    $form['#quiz_check_revision_access'] = TRUE;

    // Allow user to set title?
    if (user_access('edit question titles')) {
      $form['helper']['#theme'] = 'quiz_question_creation_form';
      $form['title'] = array(
        '#type' => 'textfield',
        '#title' => t('Title'),
        '#maxlength' => 255,
        '#default_value' => $this->node->title,
        '#required' => TRUE,
        '#description' => t('Add a title that will help distinguish this question from other questions. This will not be seen during the @quiz.', array('@quiz' => QUIZ_NAME)),
      );
    }
    else {
      $form['title'] = array(
        '#type' => 'value',
        '#value' => $this->node->title,
      );
    }

    // Store quiz id in the form.
    $form['quiz_nid'] = array(
      '#type' => 'hidden',
    );
    $form['quiz_vid'] = array(
      '#type' => 'hidden',
    );

    if (isset($_GET['quiz_nid']) && isset($_GET['quiz_vid'])) {
      $form['quiz_nid']['#value'] = intval($_GET['quiz_nid']);
      $form['quiz_vid']['#value'] = intval($_GET['quiz_vid']);
    }

    // Identify this node as a quiz question type so that it can be recognized
    // by other modules effectively.
    $form['is_quiz_question'] = array(
      '#type' => 'value',
      '#value' => TRUE,
    );

    if (!empty($this->node->nid)) {
      if ($properties = entity_load('quiz_question', FALSE, array('nid' => $this->node->nid, 'vid' => $this->node->vid))) {
        $quiz_question = reset($properties);
      }
    }
    $form['feedback'] = array(
      '#type' => 'text_format',
      '#title' => t('Question feedback'),
      '#default_value' => !empty($quiz_question->feedback) ? $quiz_question->feedback : '',
      '#format' => !empty($quiz_question->feedback_format) ? $quiz_question->feedback_format : filter_default_format(),
      '#description' => t('This feedback will show when configured and the user answers a question, regardless of correctness.'),
    );

    // Add question type specific content.
    $form = array_merge($form, $this->getCreationForm($form_state));

    if (variable_get('quiz_auto_revisioning', 1) && $this->hasBeenAnswered()) {
      $log = t('The current revision has been answered. We create a new revision so that the reports from the existing answers stays correct.');
      $this->node->revision = 1;
      $this->node->log = $log;
    }

    return $form;
  }

  /**
   * Retrieve information relevant for viewing the node.
   *
   * (This data is generally added to the node's extra field.)
   *
   * @return array
   *   Content array.
   */
  public function getNodeView() {
    $content = array();
    return $content;
  }

  /**
   * Getter function returning properties to be loaded when the node is loaded.
   *
   * @see load hook in quiz_question.module (quiz_question_load)
   *
   * @return array
   *   Array with all additional node properties.
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }

    $props = array();
    $result = db_query('SELECT *
      FROM {quiz_question_properties}
      WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid));
    $row = $result->fetch();

    if ($row) {
      $props['max_score'] = $row->max_score;
      $props['feedback']['value'] = $row->feedback;
      $props['feedback']['format'] = $row->feedback_format;
    }

    $props['is_quiz_question'] = TRUE;

    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Responsible for handling insert/update of question-specific data.
   *
   * This is typically called from within the Node API, so there is no need
   * to save the node.
   *
   * The $is_new flag is set to TRUE whenever the node is being initially
   * created.
   *
   * A save function is required to handle the following three situations:
   * - A new node is created ($is_new is TRUE).
   * - A new node *revision* is created ($is_new is NOT set, because the
   *   node itself is not new).
   * - An existing node revision is modified.
   *
   * @see hook_update and hook_insert in quiz_question.module
   *
   * @param bool $is_new
   *   TRUE when the node is initially created.
   */
  public function save($is_new = FALSE) {
    // We call the abstract function saveNodeProperties to save type specific
    // data.
    $this->saveNodeProperties($this->node->is_new);

    db_merge('quiz_question_properties')
      ->key(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
      ))
      ->fields(array(
        'nid' => $this->node->nid,
        'vid' => $this->node->vid,
        'max_score' => $this->getMaximumScore(),
        'feedback' => !empty($this->node->feedback['value']) ? $this->node->feedback['value'] : '',
        'feedback_format' => !empty($this->node->feedback['format']) ? $this->node->feedback['format'] : filter_default_format(),
      ))
      ->execute();

    // Save what quizzes this question belongs to.
    // @kludge the quiz nid/vid are still on the node
    if (!empty($this->node->quiz_nid)) {
      $this->saveRelationships($this->node->quiz_nid, $this->node->quiz_vid);
    }

    if (!empty($this->node->revision)) {
      // @kludge strange way of redirecting, since we do not have access to
      // $form(_state) here
      unset($_GET['destination']);
      unset($_REQUEST['edit']['destination']);
      $_REQUEST['edit']['destination'] = "node/{$this->node->nid}/question-revision-actions";
    }
  }

  /**
   * Delete question data from the database.
   *
   * Called by quiz_question_delete (hook_delete).
   *
   * Child classes must call super.
   *
   * @param bool $only_this_version
   *   If the $only_this_version flag is TRUE, then only the particular
   *   nid/vid combo should be deleted. Otherwise, all questions with the
   *   current nid can be deleted.
   */
  public function delete($only_this_version = FALSE) {
    // Delete properties.
    $delete = db_delete('quiz_question_properties')
      ->condition('nid', $this->node->nid);
    if ($only_this_version) {
      $delete->condition('vid', $this->node->vid);
    }
    $delete->execute();
  }

  /**
   * Provides validation for question before it is created.
   *
   * When a new question is created and initially submitted, this is
   * called to validate that the settings are acceptable.
   *
   * @param array $form
   *   The processed form.
   */
  abstract public function validateNode(array &$form);

  /**
   * Get the form through which the user will answer the question.
   *
   * @param array $form_state
   *   The FAPI form_state array.
   * @param int $result_id
   *   The result id.
   * @return array
   *   An renderable FAPI array.
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $form = array();
    $form['#element_validate'] = array('quiz_question_element_validate');
    return $form;
  }

  /**
   * Get the form used to create a new question.
   *
   * @param array $form_state
   *   The FAPI form_state array.
   * @return array
   *   An renderable FAPI array.
   */
  abstract public function getCreationForm(array &$form_state = NULL);

  /**
   * Get the maximum possible score for this question.
   *
   * @return int
   */
  abstract public function getMaximumScore();

  /**
   * Save question type specific node properties.
   */
  abstract public function saveNodeProperties();

  /**
   * Save this Question to the specified Quiz.
   *
   * @param $nid
   *   The node ID.
   * @param $vid
   *   The revision ID.
   */
  public function saveRelationships($nid, $vid) {
    $quiz_node = node_load($nid, $vid);

    if (variable_get('quiz_auto_revisioning', 1) && quiz_has_been_answered($quiz_node)) {
      // We need to revise the quiz node if it has been answered.
      $quiz_node->revision = 1;
      $quiz_node->log = t('The current revision has been answered. We create a new revision so that the reports from the existing answers stays correct.');
      node_save($quiz_node);
      drupal_set_message(t('New revision has been created for the @quiz %n', array('%n' => $quiz_node->title, '@quiz' => QUIZ_NAME)));
    }

    $insert_values = array();
    $insert_values['parent_nid'] = $quiz_node->nid;
    $insert_values['parent_vid'] = $quiz_node->vid;
    $insert_values['child_nid'] = $this->node->nid;
    $insert_values['child_vid'] = $this->node->vid;
    $insert_values['max_score'] = $this->getMaximumScore();
    $insert_values['auto_update_max_score'] = $this->autoUpdateMaxScore() ? 1 : 0;
    $insert_values['weight'] = 1 + db_query('SELECT MAX(weight) FROM {quiz_node_relationship} WHERE parent_vid = :vid', array(':vid' => $quiz_node->vid))->fetchField();
    $randomization = db_query('SELECT randomization FROM {quiz_node_properties} WHERE nid = :nid AND vid = :vid', array(':nid' => $quiz_node->nid, ':vid' => $quiz_node->vid))->fetchField();
    $insert_values['question_status'] = $randomization == 2 ? QUIZ_QUESTION_RANDOM : QUIZ_QUESTION_ALWAYS;
    entity_create('quiz_question_relationship', $insert_values)->save();

    // Update max_score for relationships if auto update max score is enabled
    // for question.
    $quizzes_to_update = array();
    $result = db_query(
      'SELECT parent_vid as vid from {quiz_node_relationship} where child_nid = :nid and child_vid = :vid and auto_update_max_score=1', array(':nid' => $this->node->nid, ':vid' => $this->node->vid));
    foreach ($result as $record) {
      $quizzes_to_update[] = $record->vid;
    }

    db_update('quiz_node_relationship')
      ->fields(array('max_score' => $this->getMaximumScore()))
      ->condition('child_nid', $this->node->nid)
      ->condition('child_vid', $this->node->vid)
      ->condition('auto_update_max_score', 1)
      ->execute();

    quiz_update_max_score_properties($quizzes_to_update);
    quiz_update_max_score_properties(array($quiz_node->vid));
  }

  /**
   * Finds out if a question has been answered or not.
   *
   * This function also returns TRUE if a quiz that this question belongs to
   * have been answered. Even if the question itself haven't been answered.
   * This is because the question might have been rendered and a user is about
   * to answer it...
   *
   * @return bool
   *   TRUE if question has been answered or is about to be answered...
   */
  public function hasBeenAnswered() {
    if (!isset($this->node->vid)) {
      return FALSE;
    }
    $answered = db_query_range('SELECT 1 FROM {quiz_node_results} qnres
            JOIN {quiz_node_relationship} qnrel ON (qnres.vid = qnrel.parent_vid)
            WHERE qnrel.child_vid = :child_vid', 0, 1, array(':child_vid' => $this->node->vid))->fetch();
    return $answered ? TRUE : FALSE;
  }

  /**
   * Determines if the user can view the correct answers.
   *
   * @return true|null
   *   TRUE if the view may include the correct answers to the question.
   */
  public function viewCanRevealCorrect() {
    global $user;

    $reveal_correct[] = user_access('view any quiz question correct response');
    $reveal_correct[] = ($user->uid == $this->node->uid);
    if (array_filter($reveal_correct)) {
      return TRUE;
    }
  }

  /**
   * Utility function that returns the format of the node body.
   *
   * @return string|null
   *   The format of the node body
   */
  protected function getFormat() {
    $node = isset($this->node) ? $this->node : $this->question;
    $body = field_get_items('node', $node, 'body');
    return isset($body[0]['format']) ? $body[0]['format'] : NULL;
  }

  /**
   * This may be overridden in subclasses. If it returns true,
   * it means the max_score is updated for all occurrences of
   * this question in quizzes.
   *
   * @return bool
   */
  protected function autoUpdateMaxScore() {
    return FALSE;
  }

  /**
   * Validate a user's answer.
   *
   * @param array $element
   *   The form element of this question.
   * @param mixed $value
   *   The value submitted by the user. Depending on the question type's form,
   *   the data type will vary.
   */
  public function getAnsweringFormValidate(array &$element, &$value) {

  }

  /**
   * Is this question graded?
   *
   * Questions like Quiz Directions, Quiz Page, and Scale are not.
   *
   * By default, questions are expected to be gradeable
   *
   * @return bool
   */
  public function isGraded() {
    return TRUE;
  }

  /**
   * Does this question type give feedback?
   *
   * Questions like Quiz Directions and Quiz Pages do not.
   *
   * By default, questions give feedback
   *
   * @return bool
   */
  public function hasFeedback() {
    return TRUE;
  }

  /**
   * Is this "question" an actual question?
   *
   * For example, a Quiz Page is not a question, neither is a "quiz directions".
   *
   * Returning FALSE here means that the question will not be numbered, and
   * possibly other things.
   *
   * @return bool
   */
  public function isQuestion() {
    return TRUE;
  }

}

/**
 * Each question type must store its own response data and be able to calculate
 * a score for that data.
 */
abstract class QuizQuestionResponse {

  // Result id.
  protected $result_id = 0;
  protected $is_correct = FALSE;
  protected $evaluated = TRUE;
  // The question node(not a quiz question instance).
  public $question = NULL;
  public $quizQuestion = NULL;
  protected $answer = NULL;
  protected $score;
  public $is_skipped;
  public $is_doubtful;

  /**
   * Create a new user response.
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
    $this->result_id = $result_id;
    $this->question = $question_node;
    $this->quizQuestion = _quiz_question_get_instance($question_node);
    $this->answer = $answer;
    $result = db_query('SELECT *
      FROM {quiz_node_results_answers}
      WHERE result_id = :result_id
      AND question_nid = :question_nid
      AND question_vid = :question_vid', array(
      ':result_id' => $result_id,
      ':question_nid' => $question_node->nid,
      ':question_vid' => $question_node->vid
    ))->fetch();
    if (is_object($result)) {
      foreach ($result as $key => $value) {
        $this->$key = $value;
      }
    }
  }

  /**
   * Get the question of this question response.
   *
   * @return QuizQuestion
   */
  public function getQuizQuestion() {
    return $this->quizQuestion;
  }

  /**
   * Used to refresh this instances question node in case drupal has changed it.
   *
   * @param stdClass $newNode
   *   Question node.
   */
  public function refreshQuestionNode($newNode) {
    $this->question = $newNode;
  }

  /**
   * Indicate whether the response has been evaluated (scored) yet.
   *
   * Questions that require human scoring (e.g. essays) may need to manually
   * toggle this.
   *
   * @return bool
   */
  public function isEvaluated() {
    return (bool) $this->evaluated;
  }

  /**
   * Check to see if the answer is marked as correct.
   *
   * This default version returns TRUE if the score is equal to the maximum
   * possible score. Each question type can determine on its own if the question
   * response is "correct".
   *
   * @return bool
   */
  public function isCorrect() {
    return ($this->getMaxScore(FALSE) == $this->getScore(FALSE));
  }

  /**
   * Get the score of this question response.
   *
   * @param bool $weight_adjusted
   *   If the score should be scaled based on the Quiz question max score.
   *
   * @return int
   *   The max score of this question response.
   */
  public function getScore($weight_adjusted = TRUE) {
    if ($weight_adjusted) {
      $ratio = $this->getWeightedRatio();
      return $this->score() * $ratio;
    }
    return $this->score();
  }

  /**
   * Get the max score of this question response.
   *
   * @param bool $weight_adjusted
   *   If the max score should be scaled based on the Quiz question max score.
   *
   * @return int
   *   The max score of this question response.
   */
  public function getMaxScore($weight_adjusted = TRUE) {
    if ($weight_adjusted) {
      $quiz_result = quiz_result_load($this->result_id);
      $relationships = entity_load('quiz_question_relationship', FALSE, array(
        'parent_nid' => $quiz_result->nid,
        'parent_vid' => $quiz_result->vid,
        'child_nid' => $this->question->nid,
        'child_vid' => $this->question->vid,
      ));
      if ($relationships) {
        // This is the weighted max score of the question.
        return reset($relationships)->max_score;
      }

      $quiz = node_load($quiz_result->nid);
      if ($quiz->randomization == 2) {
        // This isn't necessary, since setting a max score for random questions
        // updates them all.
      }
      if ($quiz->randomization == 3) {
        $max_score = db_select('quiz_terms', 'qt')
          ->fields('qt', array('max_score'))
          ->condition('tid', $this->tid)
          ->condition('nid', $quiz_result->nid)
          ->condition('vid', $quiz_result->vid)
          ->execute()
          ->fetchField();
        return $max_score;
      }
    }

    return $this->quizQuestion->getMaximumScore();
  }

  /**
   * Represent the response as a stdClass object.
   *
   * Convert data to an object that has the following properties:
   * - $score.
   * - $nid.
   * - $vid.
   * - $result_id.
   * - $is_correct.
   * - $is_evaluated.
   * - $is_skipped.
   * - $is_doubtful.
   * - $tid.
   *
   * @return stdClass
   */
  public function toBareObject() {
    $obj = new stdClass();
    $obj->score = $this->getScore(); // This can be 0 for unscored.
    $obj->nid = $this->question->nid;
    $obj->vid = $this->question->vid;
    $obj->result_id = $this->result_id;
    $obj->is_correct = (int) $this->isCorrect();
    $obj->is_evaluated = $this->isEvaluated();
    $obj->is_skipped = 0;
    $obj->is_doubtful = isset($_POST['is_doubtful']) ? $_POST['is_doubtful'] : 0;
    $obj->tid = $this->tid;
    return $obj;
  }

  /**
   * Get data suitable for reporting a user's score on the question.
   *
   * @return array
   */
  public function getReport() {
    // Basically, we encode internal information in a
    // legacy array format for Quiz.
    $report = array(
      'answer_id' => 0, // <-- Stupid vestige of multichoice.
      'answer' => $this->answer,
      'is_evaluated' => $this->isEvaluated(),
      'is_correct' => $this->isCorrect(),
      'score' => $this->getScore(),
      'question_vid' => $this->question->vid,
      'question_nid' => $this->question->nid,
      'result_id' => $this->result_id,
    );
    return $report;
  }

  /**
   * Creates the report form for the admin pages, and for when a user gets
   * feedback after answering questions.
   *
   * The report is a form to allow editing scores and the likes while viewing
   * the report form.
   *
   * @return array|null
   *   An renderable FAPI array
   */
  public function getReportForm() {
    // Add general data, and data from the question type implementation.
    $form = array();

    $form['nid'] = array(
      '#type' => 'value',
      '#value' => $this->question->nid,
    );
    $form['vid'] = array(
      '#type' => 'value',
      '#value' => $this->question->vid,
    );
    $form['result_id'] = array(
      '#type' => 'value',
      '#value' => $this->result_id,
    );
    $form['display_number'] = array(
      '#type' => 'value',
      '#value' => $this->display_number,
    );

    $quiz_result = quiz_result_load($this->result_id);

    if (quiz_access_to_score($quiz_result)) {

      if ($submit = $this->getReportFormSubmit()) {
        $form['score'] = $this->getReportFormScore();
        $form['answer_feedback'] = $this->getReportFormAnswerFeedback();
        $form['submit'] = array(
          '#type' => 'value',
          '#value' => $submit,
        );
      }

      return $form;
    }
  }

  /**
   * Get the response part of the report form.
   *
   * @return array
   *   Array of response data, with each item being an answer to a response. For
   *   an example, see MultichoiceResponse::getFeedbackValues(). The sub items
   *   are keyed by the feedback type. Providing a NULL option means that
   *   feedback will not be shown. See an example at
   *   LongAnswerResponse::getFeedbackValues().
   */
  public function getFeedbackValues() {
    $data = array();

    $data[] = array(
      'choice' => 'True',
      'attempt' => 'Did the user choose this?',
      'correct' => 'Was their answer correct?',
      'score' => 'Points earned for this answer',
      'answer_feedback' => 'Feedback specific to the answer',
      'question_feedback' => 'General question feedback for any answer',
      'solution' => 'Is this choice the correct solution?',
      'quiz_feedback' => 'Quiz feedback at this time',
    );

    return $data;
  }

  /**
   * Get the feedback form for the reportForm.
   *
   * @return array|false
   *   An renderable FAPI array, or FALSE if no answer form.
   */
  public function getReportFormAnswerFeedback() {
    return FALSE;
  }

  /**
   * Get the submit function for the reportForm.
   *
   * @return string|false
   *   Submit function as a string, or FALSE if no submit function.
   */
  public function getReportFormSubmit() {
    return FALSE;
  }

  /**
   * Get the validate function for the reportForm.
   *
   * @param array $element
   *   The form element of this question.
   * @param array $form_state
   *   The FAPI form_state array.
   */
  public function getReportFormValidate(&$element, &$form_state) {
    // Check to make sure that entered score is not higher than max allowed
    // score.
    if ($element['score']['#value'] && $element['score']['#value'] > $this->getMaxScore(TRUE)) {
      form_error($element['score'], t('The score needs to be a number between 0 and @max', array('@max' => $this->getMaxScore(TRUE))));
    }
  }

  /**
   * Utility function that returns the format of the node body.
   *
   * @return string|null
   *   The format of the node body
   */
  protected function getFormat() {
    $body = field_get_items('node', $this->question, 'body');
    return ($body ? $body[0]['format'] : NULL);
  }

  /**
   * Save the response for this question response.
   */
  abstract public function save();

  /**
   * Delete the response for this question response.
   */
  abstract public function delete();

  /**
   * Calculate the unscaled score in points for this question response.
   */
  abstract public function score();

  /**
   * Get the user's response.
   *
   * @return mixed
   *   The answer given by the user
   */
  abstract public function getResponse();

  /**
   * Can the quiz taker view the requested review?
   *
   * @param string $option
   *   An option key.
   *
   * @return bool
   */
  public function canReview($option) {
    $can_review = &drupal_static(__METHOD__, array());

    if (!isset($can_review[$option])) {
      $quiz_result = quiz_result_load($this->result_id);
      $can_review[$option] = quiz_feedback_can_review($option, $quiz_result);
    }

    return $can_review[$option];
  }

  /**
   * Implementation of getReportFormScore().
   *
   * @see QuizQuestionResponse::getReportFormScore()
   */
  public function getReportFormScore() {
    $score = ($this->isEvaluated()) ? $this->getScore() : '';
    return array(
      '#title' => 'Enter score',
      '#type' => 'textfield',
      '#default_value' => $score,
      '#size' => 3,
      '#attributes' => array('class' => array('quiz-report-score')),
      '#element_validate' => array('element_validate_integer'),
      '#required' => TRUE,
      '#field_suffix' => '/ ' . $this->getMaxScore(),
    );
  }

  /**
   * Set the target result answer ID for this Question response.
   *
   * Useful for cloning entire result sets.
   *
   * @param int $result_answer_id
   */
  public function setResultAnswerId($result_answer_id) {
    $this->result_answer_id = $result_answer_id;
  }

  /**
   * Get answers for a question in a result.
   *
   * This static method assists in building views for the mass export of
   * question answers.
   *
   * It is not as easy as instantiating all the question responses and returning
   * the answer. To do this in views scalably we have to gather the data
   * carefully.
   *
   * This base method provides a very poor way of gathering the data.
   *
   * @see views_handler_field_prerender_list for the expected return value.
   *
   * @see MultichoiceResponse::viewsGetAnswers() for a correct approach
   * @see TrueFalseResponse::viewsGetAnswers() for a correct approach
   */
  public static function viewsGetAnswers(array $result_answer_ids = array()) {
    $items = array();
    foreach ($result_answer_ids as $result_answer_id) {
      $ra = entity_load_single('quiz_result_answer', $result_answer_id);
      $question = node_load($ra->question_nid, $ra->question_vid);
      /* @var $ra_i QuizQuestionResponse */
      $ra_i = _quiz_question_response_get_instance($ra->result_id, $question);
      $items[$ra->result_id][] = array('answer' => $ra_i->getResponse());
    }
    return $items;
  }

  /**
   * Get the weighted score ratio.
   *
   * This returns the ratio of the weighted score of this question versus the
   * question score. For example, if the question is worth 10 points in the
   * associated quiz, but it is a 3 point multichoice question, the weighted
   * ratio is 3.33.
   *
   * @return float
   *   The weight of the question
   */
  public function getWeightedRatio() {
    if ($this->getMaxScore(FALSE) == 0) {
      return 0;
    }

    return $this->getMaxScore(TRUE) / $this->getMaxScore(FALSE);
  }

}

class QuizQuestionBroken extends QuizQuestion {

  /**
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {

  }

  /**
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {

  }

  /**
   * @see QuizQuestion::saveNodeProperties()
   */
  public function saveNodeProperties() {

  }

  /**
   * @see QuizQuestion::validateNode()
   */
  public function validateNode(array &$form) {

  }

  /**
   * @see QuizQuestion::hasFeedback()
   */
  public function hasFeedback() {
    return FALSE;
  }

}

class QuizQuestionResponseBroken extends QuizQuestionResponse {

  /**
   * @see QuizQuestionResponse::getReport()
   */
  public function getReport() {
    return array(
      'answer_id' => 0,
      'is_correct' => NULL,
    );
  }

  /**
   * Create a new user response.
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
    $this->quizQuestion = _quiz_question_get_instance($question_node);
  }

  /**
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {

  }

  /**
   * @see QuizQuestionResponse::getResponse()
   */
  public function getResponse() {

  }

  /**
   * @see QuizQuestionResponse::save()
   */
  public function save() {

  }

  /**
   * @see QuizQuestionResponse::score()
   */
  public function score() {

  }

  /**
   * @see QuizQuestionResponse::getMaxScore()
   */
  public function getMaxScore($weight_adjusted = TRUE) {
    return 0;
  }

}
