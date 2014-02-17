<?php

/**
 * The main classes for the cloze question type.
 * These inherit or implement code found in quiz_question.classes.inc.
 *
 * @file
 */

/**
 * Extension of QuizQuestion.
 *
 * This could have extended long answer, except that that would have entailed
 * adding long answer as a dependency.
 */
class ClozeQuestion extends QuizQuestion {

  /**
   * Implementation of saveNodeProperties
   *
   * @see QuizQuestion#saveNodeProperties($is_new)
   */
  public function saveNodeProperties($is_new = FALSE) {
    // no special property for cloze question node
  }

  /**
   * Implementation of validateNode
   *
   * @see QuizQuestion#validateNode($form)
   */
  public function validateNode(array &$form) {
    if (substr_count($this->node->body[LANGUAGE_NONE]['0']['value'], '[') !== substr_count($this->node->body[LANGUAGE_NONE]['0']['value'], ']')) {
      form_set_error('body', t('Please check the question format.'));
    }
  }

  /**
   * Implementation of delete()
   *
   * @see QuizQuestion#delete($only_this_version)
   */
  public function delete($only_this_version = FALSE) {
    parent::delete($only_this_version);
    $delete_ans = db_delete('quiz_cloze_user_answers');
    $delete_ans->condition('question_nid', $this->node->nid);
    if ($only_this_version) {
      $delete_ans->condition('question_vid', $this->node->vid);
    }
    $delete_ans->execute();
  }

  /**
   * Implementation of getNodeProperties()
   *
   * @see QuizQuestion#getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();
    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Implementation of getNodeView()
   *
   * @see QuizQuestion#getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();
    $content['#attached']['css'] = array(
      drupal_get_path('module', 'cloze') . '/theme/cloze.css'
    );
    $question = $this->node->body[LANGUAGE_NONE][0]['value'];
    $chunks = _cloze_get_question_chunks($question);
    if ($this->viewCanRevealCorrect() && !empty($chunks)) {
      $solution = $this->node->body[LANGUAGE_NONE][0]['value'];
      foreach ($chunks as $position => $chunk) {
        if (strpos($chunk, '[') === FALSE) {
          continue;
        }
        $chunk = str_replace(array('[', ']'), '', $chunk);
        $choices = explode(',', $chunk);
        $replace = '<span class="correct answer user-answer">' . $choices[0] . '</span>';
        $solution = str_replace($chunks[$position], $replace, $solution);
      }
      $content['answers'] = array(
        '#markup' => '<div class="quiz-solution cloze-question">' . $solution . '</div>',
        '#weight' => 5,
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
    $form['#theme'] = 'cloze_answering_form';
    $form['#attached']['css'] = array(
      drupal_get_path('module', 'cloze') . '/theme/cloze.css'
    );
    $form['open_wrapper'] = array(
      '#markup' => '<div class="cloze-question">',
    );
    foreach (_cloze_get_question_chunks($this->node->body[LANGUAGE_NONE]['0']['value']) as $position => $chunk) {
      if (strpos($chunk, '[') === FALSE) {
        // this "tries[foobar]" hack is needed becaues question handler engine checks for input field
        // with name tries
        $form['tries['. $position .']'] = array(
          '#markup' => str_replace("\n", "<br/>", $chunk),
          '#prefix' => '<div class="form-item">',
          '#suffix' => '</div>',
        );
      }
      else {
        $chunk = str_replace(array('[', ']'), '', $chunk);
        $choices = explode(',', $chunk);
        if (count($choices) > 1) {
          $form['tries['. $position .']'] = array(
            '#type' => 'select',
            '#title' => '',
            '#options' => _cloze_shuffle_choices(drupal_map_assoc($choices)),
            '#required' => FALSE,
          );
        }
        else {
          $form['tries['. $position .']'] = array(
            '#type' => 'textfield',
            '#title' => '',
            '#size' => 32,
            '#required' => FALSE,
            '#attributes' => array(
              'autocomplete' => 'off',
            ),
          );
        }
      }
    }
    $form['close_wrapper'] = array(
      '#markup' => '</div>',
    );
    if (isset($rid)) {
      $cloze_esponse = new ClozeResponse($rid, $this->node);
      $response = $cloze_esponse->getResponse();
      if (is_array($response)) {
        foreach ($response as $key => $value) {
          $form["tries[$key]"]['#default_value'] = $value;
        }
      }
    }
    return $form;
  }

  /**
   * Implementation of getCreationForm
   *
   * @see QuizQuestion#getCreationForm($form_state)
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form['#attached']['css'] = array(
      drupal_get_path('module', 'cloze') . '/theme/cloze.css',
    );
    $form['instructions'] = array(
      '#markup' => '<div class="cloze-instruction">' .
      t('For free text cloze, mention the correct ansewr inside the square bracket. For multichoice cloze, provide the options separated by commas with correct answer as first. <br/>Example question: [The] Sun raises in the [east, west, north, south]. <br/>Answer: <span class="answer correct correct-answer">The</span> sun raises the <span class="answer correct correct-answer">east</span>.') .
      '</div>',
      '#weight' => -10,
    );
    return $form;
  }

  /**
   * Implementation of getMaximumScore
   *
   * @see QuizQuestion#getMaximumScore()
   */
  public function getMaximumScore() {
    //TODO: Add admin settings for this
    return 10;
  }

  /**
   * Evaluate the correctness of an answer based on the correct answer and evaluation method.
   */
  public function evaluateAnswer($user_answer) {
    $correct_answer = _cloze_get_correct_answer_chunks($this->node->body[LANGUAGE_NONE]['0']['value']);
    $total_answer = count($correct_answer);
    $correct_answer_count = 0;
    if ($total_answer == 0) {
      return $this->getMaximumScore();
    }
    foreach ($correct_answer as $key => $value) {
      if (drupal_strtolower($correct_answer[$key]) == drupal_strtolower($user_answer[$key])) {
        $correct_answer_count++;
      }
    }
    $score = $correct_answer_count / $total_answer * $this->getMaximumScore();
    return round($score);
  }
}

/**
 * Extension of QuizQuestionResponse
 */
class ClozeResponse extends QuizQuestionResponse {
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
      $r = db_query("SELECT answer_id, answer, score, question_vid, question_nid, result_id FROM {quiz_cloze_user_answers} WHERE question_nid = :question_nid AND question_vid = :question_vid AND result_id = :result_id", array(':question_nid' => $question_node->nid, ':question_vid'=>$question_node->vid, ':result_id' => $result_id))->fetch();
      if (!empty($r)) {
	$this->answer = unserialize($r->answer);
	$this->score = $r->score;
	$this->answer_id = $r->answer_id;
      }
    }
    else {
      $this->answer = $answer;
    }
  }

  /**
   * Implementation of isValid
   *
   * @see QuizQuestionResponse#isValid()
   */
  public function isValid() {
    return TRUE;
  }

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse#save()
   */
  public function save() {
    $this->answer_id = db_insert('quiz_cloze_user_answers')
      ->fields(array(
        'answer' => serialize($this->answer),
        'question_nid' => $this->question->nid,
        'question_vid' => $this->question->vid,
        'result_id' => $this->rid,
        'score' => $this->getScore(FALSE),
      ))
      ->execute();
  }

  /**
   * Implementation of delete()
   *
   * @see QuizQuestionResponse#delete()
   */
  public function delete() {
    db_delete('quiz_cloze_user_answers')
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->rid)
      ->execute();
  }

  /**
   * Implementation of score()
   *
   * @see QuizQuestionResponse#score()
   */
  public function score() {
    $shortAnswer = new ClozeQuestion($this->question);
    $score = $shortAnswer->evaluateAnswer($this->answer);
    return $score;
  }

  /**
   * Implementation of getResponse()
   *
   * @see QuizQuestionResponse#getResponse()
   */
  public function getResponse() {
    return $this->answer;
  }

  /**
   * Implementation of getReportForm()
   *
   * @see QuizQuestionResponse#getReportForm($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportForm($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $form = parent::getReportForm($showpoints, $showfeedback, $allow_scoring);
    $question = strip_tags($form['question']['#markup']);
    $question_form['open_wrapper'] = array(
      '#markup' => '<div class="cloze-question">',
    );
    foreach (_cloze_get_question_chunks($question) as $position => $chunk) {
      if (strpos($chunk, '[') === FALSE) {
        // this "tries[foobar]" hack is needed becaues question handler engine checks for input field
        // with name tries
        $question_form['tries['. $position .']'] = array(
          '#markup' => str_replace("\n", "<br/>", $chunk),
          '#prefix' => '<div class="form-item">',
          '#suffix' => '</div>',
        );
      }
      else {
        $chunk = str_replace(array('[', ']'), '', $chunk);
        $choices = explode(',', $chunk);
        if (count($choices) > 1) {
          $question_form['tries['. $position .']'] = array(
            '#type' => 'select',
            '#title' => '',
            '#options' => _cloze_shuffle_choices(drupal_map_assoc($choices)),
            '#required' => FALSE,
          );
        }
        else {
          $question_form['tries['. $position .']'] = array(
            '#type' => 'textfield',
            '#title' => '',
            '#size' => 32,
            '#required' => FALSE,
            '#attributes' => array(
              'autocomplete' => 'off',
            ),
          );
        }
      }
    }
    $question_form['close_wrapper'] = array(
      '#markup' => '</div>',
    );
    $form['question']['#markup'] = drupal_render($question_form);
    return $form;
  }

  /**
   * Implementation of getReportFormResponse()
   *
   * @see QuizQuestionResponse#getReportFormResponse($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $form = array();
    $form['#theme'] = 'cloze_response_form';
    $form['#attached']['css'] = array(
      drupal_get_path('module', 'cloze') . '/theme/cloze.css'
    );
    if (($this->question) && !empty($this->question->answers)) {
      $answer = (object) current($this->question->answers);
    }
    else {
      return $form;
    }
    $this->question = node_load($this->question->nid);
    $question = $this->question->body[LANGUAGE_NONE][0]['value'];
    $correct_answer = _cloze_get_correct_answer($question);
    $user_answer = _cloze_get_user_answer($question, $this->answer);
    $form['answer'] = array(
      '#markup' => theme('cloze_user_answer', array('answer' => $user_answer, 'correct' => $correct_answer)),
    );
    return $form;
  }

  /**
   * Implementation of getReportFormScore()
   *
   * @see QuizQuestionResponse#getReportFormScore($showpoints, $showfeedback, $allow_scoring)
   */
  public function getReportFormScore($showfeedback = TRUE, $showpoints = TRUE, $allow_scoring = FALSE) {
    return array(
     '#markup' => $this->getScore(),
    );
  }
}
