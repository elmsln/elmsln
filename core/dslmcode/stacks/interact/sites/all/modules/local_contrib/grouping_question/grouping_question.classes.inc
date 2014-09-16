<?php

/**
 * @file
 * Defines the classes necessary for a Grouping type question
 */

/**
 * Extension of QuizQuestion.
 * @param int $a
 */
class GroupingQuestion extends QuizQuestion {

  /**
   * @see QuizQuestion::saveNodeProperties()
   */
  public function saveNodeProperties($is_new = FALSE) {

    $result = _grouping_question_save($this->node, $is_new);

    // We fetch ids for the existing groups belonging to this question
    // We need to figure out if an existing group has been changed or deleted.
    $res = db_select('quiz_grouping_question_group', 'q')
      ->fields('q', array('id'))
      ->condition('question_nid', $this->node->nid)
      ->condition('question_vid', $this->node->vid)
      ->execute();

    // We start by assuming that all existing alternatives needs to be deleted.
    $ids_to_delete = array();
    foreach ($res as $res_o) {
      $ids_to_delete[] = $res_o->id;
    }

    for ($i = 1; isset($this->node->groups[$i]); $i++) {
      $short = $this->node->groups[$i];
      if (drupal_strlen($short['name']) > 0) {
        if (!is_numeric($short['id'])) {
          // New group.
          $this->insertStatement($i);
        }
        else {
          // Existing group. Check if it is a new revision.
          $key = array_search($short['id'], $ids_to_delete);
          if ($key === FALSE) {
            // New revision.
            $this->insertStatement($i);
          }
          else {
            $this->updateStatement($i);
            // Make sure this alternative isn't deleted.
            $ids_to_delete[$key] = FALSE;
          }
        }
      }
    }

    foreach ($ids_to_delete as $id_to_delete) {
      if ($id_to_delete) {
        db_delete('quiz_grouping_question_group')
          ->condition('id', $id_to_delete)
          ->execute();
      }
    }
  }

  /**
   * Helper function. Saves new group
   *
   * @param int $i
   *   The numerical index of the group to save
   */
  public function insertStatement($i) {
    $short = $this->node->groups[$i];
    $record = new stdClass();
    $record->name = $short['name'];
    $record->members = _grouping_question_clean_csv($short['members']);
    $record->feedback = $short['feedback']['value'];
    $record->feedback_format = $short['feedback']['format'];
    $record->question_nid = $this->node->nid;
    $record->question_vid = $this->node->vid;
    $result = drupal_write_record('quiz_grouping_question_group', $record);
    if ($result !== SAVED_NEW) {
      watchdog('grouping_question',
        'Failed to save properties of grouping question with nid %nid and vid %vid',
        array('%nid' => $this->node->nid, '%vid' => $this->node->vid),
        WATCHDOG_ERROR);
    }
  }

  /**
   * Helper function. Update existing group.
   *
   * @param int $i
   *   The numerical index of the group to save.
   */
  public function updateStatement($i) {
    $short = $this->node->groups[$i];
    $record = new stdClass();
    $record->id = $short['id'];
    $record->name = $short['name'];
    $record->members = _grouping_question_clean_csv($short['members']);
    $record->feedback = $short['feedback']['value'];
    $record->feedback_format = $short['feedback']['format'];
    $record->question_nid = $this->node->nid;
    $record->question_vid = $this->node->vid;
    $result = drupal_write_record('quiz_grouping_question_group', $record, 'id');

    if ($result !== SAVED_UPDATED) {
      watchdog('grouping_question',
        'Failed to update properties of grouping question with nid %nid and vid %vid',
        array('%nid' => $this->node->nid, '%vid' => $this->node->vid),
        WATCHDOG_ERROR);
    }
  }

  /**
   * @see QuizQuestion::validateNode()
   */
  public function validateNode(array &$form) {
    // TODO: validate that each member only exists in one place.
  }

  /**
   * @see QuizQuestion::delete()
   */
  public function delete($only_this_version = FALSE) {
    $delete_properties = db_delete('quiz_grouping_question_properties')
      ->condition('nid', $this->node->nid);

    $delete_targets = db_delete('quiz_grouping_question_group')
      ->condition('question_nid', $this->node->nid);

    $db_del_results = db_delete('quiz_grouping_question_user_answers')
      ->condition('question_nid', $this->node->nid);

    if ($only_this_version) {
      $delete_properties->condition('vid', $this->node->vid);
      $db_del_results->condition('question_vid', $this->node->vid);
      $delete_targets->condition('question_vid', $this->node->vid);
    }

    $delete_properties->execute();
    $delete_targets->execute();
    $db_del_results->execute();

    $user_answer_id = array();

    $query = db_select('quiz_grouping_question_user_answers', 'a')
      ->fields('a', array('id'))
      ->condition('question_nid', $this->node->nid)
      ->condition('result_id', $this->rid);

    if ($only_this_version) {
      $query->condition('question_vid', $this->node->vid);
    }

    $query->execute();

    while ($user_answer = $query->fetch()) {
      $user_answer_id[] = $user_answer->id;
    }

    if (count($user_answer_id)) {
      db_delete('quiz_grouping_question_user_answer_multi')
        ->condition('user_answer_id', $user_answer_id, 'IN')
        ->execute();
    }

    parent::delete($only_this_version);
  }

  /**
   * @see QuizQuestion::getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    // Load the properties.
    $res = db_select('quiz_grouping_question_properties', 'q')
      ->fields('q')
      ->condition('nid', $this->node->nid)
      ->condition('vid', $this->node->vid)
      ->execute()
      ->fetchAssoc();

    if (is_array($res)) {
      $props = array_merge($props, $res);
    }

    // Load the groups.
    $res = db_select('quiz_grouping_question_group', 'q')
      ->fields('q')
      ->condition('question_nid', $this->node->nid)
      ->condition('question_vid', $this->node->vid)
      ->orderBy('id')
      ->execute();

    $props['groups'] = array();

    $i = 1;
    while ($res_arr = $res->fetchAssoc()) {
      $props['groups'][$i] = $res_arr;
      $i++;
    }

    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * @see QuizQuestion::getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();

    if (!$this->viewCanRevealCorrect()) {
      $content['answers'] = array(
        '#markup' => '<div class="quiz-members-hidden">Answer hidden</div>',
        '#weight' => 2,
      );
      return $content;
    }

    if (empty($this->node->groups)) {
      $content['nogroups'] = array(
        '#markup' => t('No groups have been set for this Grouping question.'),
      );
      return $content;
    }

    $i = 1;
    while (isset($this->node->groups[$i])) {
      $short = $this->node->groups[$i];
      if (drupal_strlen(check_plain($short['name'])) > 0) {
        $data[$i]['name'] = check_plain($short['name']);
        $data[$i]['correct_answers'] = $short['members'];
        $data[$i]['feedback'] = check_markup($short['feedback'], $short['feedback_format']);
      }
      $i++;
    }

    $general_feedback = check_markup($this->node->feedback, $this->node->feedback_format);

    // Return themed output.
    $content['answers'] = array(
      '#markup' => theme('grouping_question_response',
        array(
          'data' => $data,
          'display_user_answers' => FALSE,
          'general_feedback' => $general_feedback,
          'showpoints' => TRUE,
          'showfeedback' => TRUE,
        )
      ),
    );

    return $content;
  }

  /**
   * @see QuizQuestion::getAnsweringForm()
   */
  public function getAnsweringForm(array $form_state, $rid) {
    $form = parent::getAnsweringForm($form_state, $rid);

    if (isset($rid)) {
      // This question has already been answered.
      $response = new GroupingResponse($rid, $this->node);
      if (is_array($response->getResponse())) {
        $previous_answer = $response->getResponse();
      }
    }

    $members = array();

    foreach ($this->node->groups as $group) {
      $new_members = explode(',', $group['members']);
      foreach ($new_members as $id => $new_member) {
        $new_member = trim($new_member);
        if (strlen($new_member) < 1) {
          unset($new_members[$id]);
        }
      }
      $members = array_merge($members, $new_members);
    }
    shuffle($members);

    $form['tries'] = array(
      '#type' => 'fieldset',
      '#title' => '',
      '#collapsible' => FALSE,
      '#tree' => TRUE,
    );

    $form['tries']['#theme'] = 'grouping_question_answer_form_groups';

    $form['tries']['members'] = array(
      '#type' => 'value',
      '#value' => $members,
    );

    for ($i = 1; isset($this->node->groups[$i]); $i++) {
      $short = $this->node->groups[$i];

      $form['tries'][$i]['id'] = array(
        '#type' => 'value',
        '#value' => $short['id'],
      );

      $form['tries'][$i]['user_answers'] = array(
        '#title' => $short['name'],
        '#type' => 'hidden',
        '#attributes' => array('class' => 'quiz-grouping-answer-field'),
        '#default_value' => (isset($previous_answer) ? $previous_answer[$i]['user_answer'] : ''),
        '#required' => FALSE,
      );
    }
    return $form;
  }

  /**
   * @see QuizQuestion::getBodyFieldTitle()
   */
  public function getBodyFieldTitle() {
    return t('Instructions');
  }

  /**
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {
    $form = array();

    $form['groups'] = array(
      '#type' => 'fieldset',
      '#title' => t('Groups'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -4,
      '#tree' => TRUE,
    );

    $form['groups']['#theme'][] = 'grouping_question_creation';

    for ($i = 1; $i <= 10; $i++) {

      $short = isset($this->node->groups[$i]) ? $this->node->groups[$i] : NULL;

      // We add id to be able to update the correct alternatives if the node is
      // updated, without destroying existing members reports.
      $form['groups'][$i]['id'] = array(
        '#type' => 'value',
        '#value' => $short['id'],
      );

      $form['groups'][$i]['name'] = array(
        '#type' => 'textfield',
        '#default_value' => isset($short['name']) ? $short['name'] : '',
        '#required' => FALSE,
        '#size' => 100,
        '#maxlength' => 128,
      );

      $form['groups'][$i]['members'] = array(
        '#type' => 'textarea',
        '#default_value' => isset($short['members']) ? $short['members'] : '',
        '#required' => FALSE,
      );

      $form['groups'][$i]['feedback'] = array(
        '#type' => 'text_format',
        '#base_type' => 'textarea',
        '#required' => FALSE,
        '#default_value' => isset($short['feedback']) ? $short['feedback'] : '',
        '#format' => isset($short['feedback_format']) ? $short['feedback_format'] : filter_default_format(),
      );
    }

    $form['feedback'] = array(
      '#title' => t('General feedback'),
      '#description' => t('Enter the general feedback the users will see on the report at the end of the quiz.'),
      '#type' => 'text_format',
      '#base_type' => 'textarea',
      '#required' => FALSE,
      '#default_value' => isset($this->node->feedback) ? $this->node->feedback : '',
      '#format' => isset($this->node->feedback_format) ? $this->node->feedback_format : filter_default_format(),
      '#rows' => 4,
    );

    return $form;
  }

  /**
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {
    $max = 0;
    for ($i = 1; isset($this->node->groups[$i]); $i++) {
      $short = $this->node->groups[$i];
      if (drupal_strlen($short['name']) > 0) {
        $members = explode(',', $short['members']);
        $max += max(count($members), 1);
      }
    }
    return max($max, 1);
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class GroupingResponse extends QuizQuestionResponse {

  /**
   * array $userAnswers
   *   The user's answers to a grouping question keyed by group id.
   */
  protected $userAnswers;

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $tries = NULL) {
    parent::__construct($result_id, $question_node, $tries);
    $this->userAnswers = array();

    if (is_array($tries)) {
      $responses = isset($tries['answer_id']) ? $tries['answer'] : $tries;
      foreach ($responses as $id => $response) {
        $this->userAnswers[$id]['user_answer'] = _grouping_question_clean_csv($response['user_answers']);
        $this->userAnswers[$id]['group_id'] = $question_node->groups[$id]['id'];
      }
    }
    else {
      $res = db_select('quiz_grouping_question_user_answers', 'ua')
        ->condition('result_id', $result_id)
        ->condition('question_nid', $this->question->nid)
        ->condition('question_vid', $this->question->vid);
      $res->leftJoin('quiz_grouping_question_user_answer_multi', 'uam', 'ua.id = uam.user_answer_id');
      $res->fields('ua')->fields('uam');
      $res = $res->execute();

      $i = 1;
      while ($res_o = $res->fetchAssoc()) {
        $this->userAnswers[$i] = $res_o;
        $i++;
      }
    }
  }

  /**
   * @see QuizQuestionResponse::isValid()
   */
  public function isValid() {
    $answer_counts = array();
    foreach ($this->userAnswers as $id => $answers) {
      $user_answers = explode(',', $answers['user_answer']);
      foreach ($user_answers as $answer) {
        if (!isset($answer_counts[$answer])) {
          $answer_counts[$answer] = array('user_count' => 0, 'correct_count' => 0);
        }
        $answer_counts[$answer]['user_count']++;
      }
    }
    foreach ($this->question->groups as $group) {
      $correct_answers = explode(',', $group['members']);
      foreach ($correct_answers as $correct_answer) {
        if (!isset($answer_counts[$correct_answer])) {
          $answer_counts[$correct_answer] = array('user_count' => 0, 'correct_count' => 0);
        }
        $answer_counts[$correct_answer]['correct_count']++;
      }
    }

    foreach ($answer_counts as $answer => $answer_count) {
      if ($answer_count['correct_count'] > 0 && $answer_count['user_count'] > $answer_count['correct_count']) {
        // If an answer is an answer but has been used more times than it
        // appears in groups, the user must have entered the same element into
        // more than one group. This stops them putting every answer in
        // every group.
        return t('Too many "' . $answer . '" entered');
      }
    }

    return TRUE;
  }

  /**
   * @see QuizQuestionResponse::save()
   */
  public function save() {
    $user_answer = new stdClass();
    $user_answer->question_nid = $this->question->nid;
    $user_answer->question_vid = $this->question->vid;
    $user_answer->result_id = $this->rid;
    drupal_write_record('quiz_grouping_question_user_answers', $user_answer);

    for ($i = 1; $i <= count($this->userAnswers); $i++) {
      $record = new stdClass();
      $record->user_answer_id = $user_answer->id;
      $record->group_id = $this->userAnswers[$i]['group_id'];
      $record->user_answer = $this->userAnswers[$i]['user_answer'];
      drupal_write_record('quiz_grouping_question_user_answer_multi', $record);
    }
  }

  /**
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {
    $user_answer_id = array();

    $query = db_select('quiz_grouping_question_user_answers', 'a')
      ->fields('a', array('id'))
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->rid)
      ->execute();

    while ($user_answer = $query->fetch()) {
      $user_answer_id[] = $user_answer->id;
    }

    if (!empty($user_answer_id)) {
      db_delete('quiz_grouping_question_user_answer_multi')
        ->condition('user_answer_id', $user_answer_id, 'IN')
        ->execute();
    }

    db_delete('quiz_grouping_question_user_answers')
      ->condition('result_id', $this->rid)
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->execute();
  }

  /**
   * @see QuizQuestionResponse::score()
   */
  public function score() {
    $score = 0;
    if ($this->isValid() !== TRUE) {
      return 0;
    }

    foreach ($this->question->groups as $key => $group) {
      $correct_answers = explode(',', $group['members']);
      $user_answers = explode(',', $this->userAnswers[$key]['user_answer']);
      foreach ($user_answers as $user_answer) {
        if (in_array($user_answer, $correct_answers)) {
          $score++;
        }
      }
    }
    return max($score, 0);
  }

  /**
   * @see QuizQuestionResponse::getResponse()
   */
  public function getResponse() {
    return $this->userAnswers;
  }

  /**
   * @see QuizQuestionResponse::getReportFormResponse()
   */
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    if (empty($this->question->groups)) {
      return array(
        '#type' => 'markup',
        '#value' => t('No groups have been set for this Grouping question.'),
      );
    }

    $data = array();

    $i = 1;
    while (isset($this->question->groups[$i])) {
      $short = $this->question->groups[$i];
      if (drupal_strlen(check_plain($short['name'])) > 0) {
        $data[$i]['name'] = check_plain($short['name']);
        $data[$i]['correct_answers'] = $short['members'];
        $data[$i]['user_answers'] = $this->userAnswers[$i]['user_answer'];
        $data[$i]['feedback'] = check_markup($short['feedback'], $short['feedback_format']);
      }
      $i++;
    }

    $general_feedback = check_markup($this->question->feedback, $this->question->feedback_format);

    // Return themed output.
    return array(
      '#markup' => theme('grouping_question_response',
        array(
          'data' => $data,
          'display_user_answers' => TRUE,
          'general_feedback' => $general_feedback,
          'showpoints' => $showpoints,
          'showfeedback' => $showfeedback,
        )
      ),
    );
  }

}
