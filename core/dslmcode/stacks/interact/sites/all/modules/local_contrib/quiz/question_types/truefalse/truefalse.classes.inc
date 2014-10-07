<?php

/**
 * Defines the classes necessary for a True/False quiz.
 *
 * @file
 */

/**
 * Extension of QuizQuestion.
 */
class TrueFalseQuestion extends QuizQuestion {

  /**
   * Implementation of saveNodeProperties
   *
   * @see QuizQuestion#saveNodeProperties($is_new)
   */
  public function saveNodeProperties($is_new = FALSE) {
    if (!isset($this->node->feedback)) {
      $this->node->feedback = '';
    }
    if ($is_new || $this->node->revision == 1) {
      $id = db_insert('quiz_truefalse_node')
        ->fields(array(
          'nid' => $this->node->nid,
          'vid' => $this->node->vid,
          'correct_answer' => $this->node->correct_answer,
          'feedback' => $this->node->feedback,
        ))
        ->execute();
    }
    else {
      db_update('quiz_truefalse_node')
        ->fields(array(
          'correct_answer' => (int) $this->node->correct_answer,
          'feedback' => $this->node->feedback,
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
    // This space intentionally left blank. :)
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestion#delete($only_this_version)
   */
  public function delete($only_this_version = FALSE) {
    parent::delete($only_this_version);

    $delete_ans = db_delete('quiz_truefalse_user_answers');
    $delete_ans->condition('question_nid', $this->node->nid);

    $delete_node = db_delete('quiz_truefalse_node');
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

    $res_a = db_query('SELECT correct_answer, feedback FROM {quiz_truefalse_node} WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();

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
   * Implementation of getAnsweringForm
   *
   * @see QuizQuestion#getAnsweringForm($form_state, $result_id)
   */
  public function getAnsweringForm(array $form_state = NULL, $result_id) {
    $element = parent::getAnsweringForm($form_state, $result_id);
    //$form['#theme'] = 'truefalse_answering_form';
    // 'tries' is unfortunately required by quiz.module
    $element += array(
      '#type' => 'radios',
      '#title' => t('Choose one'),
      '#options' => array(
        1 => t('True'),
        0 => t('False')
      ),
      '#default_value' => NULL, // prevent default value set to NULL
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
  public function getAnsweringFormValidate(array &$form, array &$form_state = NULL) {
    if (is_null($form_state['values']['question'][$this->node->nid])) {
      form_set_error('', t('You must provide an answer.'));
    }
  }

  /**
   * Implementation of getBodyFieldTitle
   *
   * @see QuizQuestion#getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('True/false statement');
  }

  /**
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm($form_state)
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
      '#description' => t('Choose if the correct answer for this question is "true" or "false".')
    );
    $form['feedback_fields'] = array(
      '#type' => 'fieldset',
      '#title' => t('Feedback Settings'),
      '#description' => t('Settings pertaining to feedback given along with results.'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => -3,
    );
    $form['feedback_fields']['feedback'] = array(// @todo: Does this make sense?
      '#type' => 'textarea',
      '#title' => t('Feedback Text'),
      '#description' => t('Text to be displayed when the results are displayed'),
      '#rows' => 5,
      '#cols' => 60,
      '#required' => FALSE,
      '#default_value' => isset($this->node->feedback) ? $this->node->feedback : '',
    );
    return $form;
  }

  /**
   * Implementation of getMaximumScore
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    return 1;
  }

  /**
   * Get the answer to this question.
   *
   * This is a utility function. It is not defined in the interface.
   */
  public function getCorrectAnswer() {
    return db_query('SELECT correct_answer FROM {quiz_truefalse_node} WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchField();
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class TrueFalseResponse extends QuizQuestionResponse {

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $answer = NULL) {
    parent::__construct($result_id, $question_node, $answer);
    if (!isset($answer)) {
      $r = $this->getCorrectAnswer();
      if (!empty($r)) {
        $this->answer = $r->answer;
        $this->score = $r->score;
      }
    }
    else {
      $this->answer = $answer;
    }
  }

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {
    db_insert('quiz_truefalse_user_answers')
      ->fields(array(
        'question_nid' => $this->question->nid,
        'question_vid' => $this->question->vid,
        'result_id' => $this->result_id,
        'answer' => (int) $this->answer,
        'score' => (int) $this->getScore(),
      ))
      ->execute();
  }

  /**
   * Implementation of delete
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
    db_delete('quiz_truefalse_user_answers')
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->result_id)
      ->execute();
  }

  /**
   * Implementation of score
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    $tfQuestion = new TrueFalseQuestion($this->question);
    return ($this->getResponse() == $tfQuestion->getCorrectAnswer()) ? 1 : 0;
  }

  /**
   * Implementation of getResponse
   *
   * @see QuizQuestionResponse#getResponse()
   */
  public function getResponse() {
    if (!isset($this->answer)) {
      $correct_answer = $this->getCorrectAnswer();
      $this->answer = isset($correct_answer->answer) ? $correct_answer->answer : NULL;
    }
    return $this->answer;
  }

  /**
   * Implementation of getCorrectAnswer
   */
  public function getCorrectAnswer() {
    return db_query('SELECT answer, score FROM {quiz_truefalse_user_answers} WHERE question_vid = :qvid AND result_id = :rid', array(':qvid' => $this->question->vid, ':rid' => $this->result_id))->fetch();
  }

  /**
   * Implementation of getReportFormResponse
   */
  public function getReportFormResponse() {

    $answer = $this->question->answers[0]['answer'];
    $correct_answer = $this->question->correct_answer;

    $data = array();
    $data[] = array(
      'choice' => 'True',
      'attempt' => $answer ? quiz_icon('selected') : '',
      'correct' => $answer == 1 ? quiz_icon($correct_answer ? 'correct' : 'incorrect') : '',
      'score' => intval($correct_answer == 1 && $answer == 1),
      'answer_feedback' => $answer ? check_markup($this->question->feedback, $this->getFormat()) : '',
      'solution' => $correct_answer == 1 ? quiz_icon('should') : '',
      'quiz_feedback' => "Quiz feedback",
    );

    $data[] = array(
      'choice' => 'False',
      'attempt' => !$answer ? quiz_icon('selected') : '',
      'correct' => $answer == 0 ? (quiz_icon(!$correct_answer ? 'correct' : 'incorrect')) : '',
      'score' => intval($correct_answer == 0 && $answer == 0),
      'answer_feedback' => !$answer ? check_markup($this->question->feedback, $this->getFormat()) : '',
      'solution' => $correct_answer == 0 ? quiz_icon('should') : '',
      'quiz_feedback' => "Quiz feedback",
    );

    return $data;
  }

}
