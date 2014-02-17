<?php

/**
 * @file
 * image_target_question.class.inc
 * Question type, enabling the creation of image_target_question questions
 */

/**
 * Extension of QuizQuestion.
 */
class ImageTargetQuestion extends QuizQuestion {

  /**
   * Run check_markup() on the field of the specified choice alternative.
   *
   * @param int $alternative_index
   *   The index of the alternative in the alternatives array.
   * @param string $field
   *   The name of the field we want to check markup on
   * @param boolean $check_user_access
   *   Whether or not to check for user access to the filter
   *
   * @return string
   *   HTML markup
   */
  public function checkMarkup($alternative_index, $field, $check_user_access = TRUE) {
    $alternative = $this->node->alternatives[$alternative_index];
    return check_markup($alternative[$field], $alternative[$field . '_format'], $check_user_access);
  }

  /**
   * Implementation of save
   * Stores the question in the database.
   *
   * @param boolean $is_new
   *   TRUE if - if the node is a new node
   *
   * @see QuizQuestion->save()
   */
  public function saveNodeProperties($is_new = FALSE) {
    $is_new = $is_new || $this->node->revision == 1;

    $file = image_target_question_save_image('alternatives');

    if ($file) {
      $this->node->fid = $file->fid;
      $this->node->width = $file->width;
      $this->node->height = $file->height;
    }

    _image_target_question_properties_save($this->node, $is_new);

    if ($is_new) {

      for ($i = 1; isset($this->node->alternatives['targets'][$i]); $i++) {
        if (drupal_strlen($this->node->alternatives['targets'][$i]['targettext']) > 0) {
          $this->insertAlternative($i);
        }
      }
    }
    else {
      // We fetch ids for the existing answers belonging to this question
      // We need to figure out if an existing alternative has been changed
      // or deleted.
      $res = db_select('quiz_image_target_question_target', 't')
        ->fields('t', array('id'))
        ->condition('question_nid', $this->node->nid)
        ->condition('question_vid', $this->node->vid)
        ->execute();

      // Start by assuming that all existing alternatives needs to be deleted.
      $ids_to_delete = array();
      foreach ($res as $res_o) {
        $ids_to_delete[] = $res_o->id;
      }

      for ($i = 1; isset($this->node->alternatives['targets'][$i]); $i++) {
        $short = $this->node->alternatives['targets'][$i];
        if (drupal_strlen($this->node->alternatives['targets'][$i]['targettext']) > 0) {
          if (!is_numeric($short['id'])) {
            // If new alternative.
            $this->insertAlternative($i);
          }
          else {
            // If existing alternative.
            $this->updateAlternative($i);
            // Make sure this alternative isn't deleted.
            $key = array_search($short['id'], $ids_to_delete);
            $ids_to_delete[$key] = FALSE;
          }
        }
      }
      foreach ($ids_to_delete as $id_to_delete) {
        if ($id_to_delete) {
          db_delete('quiz_image_target_question_target')
            ->condition('id', $id_to_delete)
            ->execute();
        }
      }
    }
  }

  /**
   * Helper function. Saves new alternatives
   *
   * @param int $i
   *   The alternative index.
   *
   * @return int|boolean
   *   SAVED_NEW or FALSE on error.
   */
  public function insertAlternative($i) {
    $short = $this->node->alternatives['targets'][$i];
    $position = explode(',', $short['region']);

    $record = new stdClass();
    $record->targettext = $short['targettext'];
    $record->top = $position[0];
    $record->leftpx = $position[1];
    $record->width = $position[2];
    $record->height = $position[3];
    $record->score_if_correct = $short['score_if_correct'];
    $record->score_if_not_correct = $short['score_if_not_correct'];
    $record->question_nid = $this->node->nid;
    $record->question_vid = $this->node->vid;

    return drupal_write_record('quiz_image_target_question_target', $record);
  }

  /**
   * Helper function. Updates existing alternatives
   *
   * @param int $i
   *   The alternative index
   *
   * @return int|boolean
   *   SAVED_UPDATED or FALSE on error.
   */
  public function updateAlternative($i) {
    $short = $this->node->alternatives['targets'][$i];
    $position = explode(',', $short['region']);

    $record = new stdClass();
    $record->id = $short['id'];
    $record->targettext = $short['targettext'];
    $record->top = $position[0];
    $record->leftpx = $position[1];
    $record->width = $position[2];
    $record->height = $position[3];
    $record->score_if_correct = $short['score_if_correct'];
    $record->score_if_not_correct = $short['score_if_not_correct'];
    $record->question_nid = $this->node->nid;
    $record->question_vid = $this->node->vid;

    return drupal_write_record('quiz_image_target_question_target', $record, 'id');
  }

  /**
   * Implementation of validate
   */
  public function validateNode(array &$form) {
    if ($this->node->revision == 1) {
      // TODO: check a file was uploaded if new.
    }


    for ($i = 1; isset($this->node->alternatives['targets'][$i]); $i++) {
      $short = $this->node->alternatives['targets'][$i];
      // TODO: check the positional elements are correct and sane.
    }
  }

  /**
   * Implementation of delete
   * @see QuizQuestion::delete()
   *
   * @param boolean $only_this_version
   *   TRUE to only delete the current version of the question.
   */
  public function delete($only_this_version = FALSE) {
    $delete_properties = db_delete('quiz_image_target_question_properties')->condition('nid', $this->node->nid);
    $delete_answers = db_delete('quiz_image_target_question_target')->condition('question_nid', $this->node->nid);
    $delete_results = db_delete('quiz_image_target_question_user_answers')->condition('question_nid', $this->node->nid);

    if ($only_this_version) {
      $delete_properties->condition('vid', $this->node->vid);
      $delete_answers->condition('question_vid', $this->node->vid);
      $delete_results->condition('question_vid', $this->node->vid);
    }

    $delete_properties->execute();
    $delete_answers->execute();
    $delete_results->execute();

    // Delete from table quiz_image_target_question_user_answer_targets.
    $user_answer_ids = array();
    if ($only_this_version) {
      $query = db_select('quiz_image_target_question_user_answers', 'at')
       ->fields('at', array('id'))
       ->condition('question_nid', $this->node->nid)
       ->condition('question_vid', $this->node->vid)
       ->condition('result_id', $this->rid)
       ->execute();
    }
    else {
      $query = db_select('quiz_image_target_question_user_answers', 'at')
        ->fields('at', array('id'))
        ->condition('question_nid', $this->node->nid)
        ->condition('result_id', $this->rid)
        ->execute();
    }

    while ($user_answer = $query->fetch()) {
      $user_answer_id[] = $user_answer->id;
    }

    if (count($user_answer_id)) {
      db_delete('quiz_image_target_question_user_answer_targets')
        ->condition('user_answer_id', $user_answer_id, 'IN')
        ->execute();
    }

    parent::delete($only_this_version);
  }

  /**
   * Implementation of getNodeProperties
   * @see QuizQuestion::getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties)) {
      return $this->nodeProperties;
    }

    $props = parent::getNodeProperties();

    // Load the properties.
    $res_a = db_select('quiz_image_target_question_properties', 'p')
      ->fields('p')
      ->condition('nid', $this->node->nid)
      ->condition('vid', $this->node->vid)
      ->execute()
      ->fetchAssoc();

    if (is_array($res_a)) {
      $props = array_merge($props, $res_a);
    }

    // Load the targets.
    $res = db_select('quiz_image_target_question_target', 't')
      ->fields('t')
      ->condition('question_nid', $this->node->nid)
      ->condition('question_vid', $this->node->vid)
      ->orderBy('id')
      ->execute();

    $props['alternatives']['targets'] = array();

    $i = 1;
    while ($res_arr = $res->fetchAssoc()) {
      $props['alternatives']['targets'][$i] = $res_arr;
      $i++;
    }

    $this->nodeProperties = $props;
    return $props;
  }

  /**
   * Implementation of getNodeView
   * @see QuizQuestion::getNodeView()
   */
  public function getNodeView() {
    $content = parent::getNodeView();

    if (user_access('edit any quiz') && !isset($this->node->alternatives['targets'])) {
      drupal_set_message(t('There are no targets set on this image'));
      $content['answers'] = array(
        '#value' => '',
        '#weight' => 2,
      );
    }
    else {
      // Return themed output.
      $content['answers'] = array(
        '#markup' => theme('image_target_question_answer_node_view', array(
          'alternatives' => $this->node->alternatives['targets'],
          'show_correct' => $this->viewCanRevealCorrect(),
          'fid' => $this->node->fid,
        )),
        '#weight' => 2,
      );
    }

    return $content;
  }

  /**
   * Generates the question form.
   *
   * This is called whenever a question is rendered, either
   * to an administrator or to a quiz taker.
   */
  public function getAnsweringForm(array $form_state, $rid) {
    $form = parent::getAnsweringForm($form_state, $rid);

    if (user_access('edit any quiz') && empty($this->node->alternatives['targets'])) {
      drupal_set_message(t('You need to set some targets on this image'), 'warning');
    }

    $form['#theme'] = 'image_target_question_answering_form';

    $form['image_target_question_image'] = $this->generateImageMarkupFormElement();

    $res = '0,0';

    for($i = 1; $i < count($this->node->alternatives['targets']); $i++){
      $res .= ':0,0';
    }

    if (isset($rid)) {
      // This question has already been answered. We load the answer.
      $response = new ImageTargetResponse($rid, $this->node);
      $response = $response->getResponse();
      $res = array();
      foreach ($response as $id => $r) {
        $res[] = $r['top'] . ',' . $r['leftpx'];
      }
      $res = implode(':', $res);
    }

    $form['tries[answer]'] = array(
      '#type' => user_access('access devel information') ? 'hidden' : 'hidden',
      '#default_value' => isset($res) ? $res : 'here',
      '#size' => 10,
      '#attributes' => array('class' => array('image_target_question-target', 'answer-box')),
    );

    $form['targets'] = array(
      '#type' => 'fieldset',
      '#title' => t('Answer'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -4,
      '#tree' => TRUE,
    );

    for ($i = 1; isset($this->node->alternatives['targets'][$i]); $i++) {
      $short = $this->node->alternatives['targets'][$i];

      $form['targets'][$i]['id'] = array(
        '#type' => 'value',
        '#value' => $short['id'],
      );

      $form['targets'][$i]['targettext'] = array(
        '#markup' => check_plain($short['targettext']),
      );

      $form['targets'][$i]['selected_target'] = array(
        '#type' => 'button',
        '#value' => t('Set target !i', array('!i' => $i)),
        '#attributes' => array('class' => array('image_target_question-select-region')),
        );
    }

    return $form;
  }

  /**
   * Implementation of getCreationForm
   * @see QuizQuestion::getCreationForm()
   */
  public function getCreationForm(array &$form_state = NULL) {

    // Ajax may have added an image.
    if (isset($form_state['values']['fid'])) {
      $this->node->fid = $form_state['values']['fid'];
      $this->node->width = $form_state['values']['width'];
      $this->node->height = $form_state['values']['height'];
    }

    $form = array();
    $type = node_type_get_type($this->node);
    $form['#attributes'] = array('enctype' => "multipart/form-data");

    // We add #action to the form because of the use of ajax.
    $options = array();
    $get = $_GET;
    unset($get['q']);
    if (!empty($get)) {
      $options['query'] = $get;
    }

    $action = url('node/add/image-target-question', $options);
    if (isset($this->node->nid)) {
      $action = url('node/' . $this->node->nid . '/edit', $options);
    }

    $form['#action'] = $action;

    if (isset($this->node->fid)) {

      $form['fid'] = array(
        '#type' => 'value',
        '#value' => $this->node->fid,
      );

      $form['width'] = array(
        '#type' => 'value',
        '#value' => $this->node->width,
      );

      $form['height'] = array(
        '#type' => 'value',
        '#value' => $this->node->height,
      );
    }

    $form['alternatives'] = array(
      '#type' => 'fieldset',
      '#title' => t('Answer'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -4,
      '#tree' => TRUE,
      '#prefix' => '<div id="image_target_question_alternatives">',
      '#suffix' => '</div>',
    );

    $form['alternatives']['upload'] = array(
      '#type' => 'file',
      '#title' => t('Attach a new image file'),
      '#description' => t('After adding the image, save the question then come back to set the targets.'),
    );

    $form['alternatives']['upload_now'] = array(
      '#type' => 'submit',
      '#value' => 'Upload',
      '#submit' => array('image_target_question_upload_image_submit'),
      '#limit_validation_errors' => array(),
      '#ajax' => array(
        'callback' => 'image_target_question_ajax_upload_image',
        'wrapper' => 'image_target_question_alternatives',
        'effect' => 'fade',
        'method' => 'replace',
        'progress' => array('type' => 'bar', 'message' => t('Please wait...')),
      ),
    );

    $form['alternatives']['image_target_question_image'] = $this->generateImageMarkupFormElement();

    $form['alternatives']['#theme'][] = 'image_target_question_creation_form';

    // The choice_count might be stored in the form_state after ajax callback.
    if (isset($form_state['choice_count'])) {
      $choice_count = $form_state['choice_count'];
    }
    else {
      $choice_count = max(variable_get('image_target_question_def_num_of_alts', 10), isset($this->node->alternatives['targets']) ? count($this->node->alternatives['targets']) : 0);
    }

    // We only add the targets if there is an image set.
    if (isset($this->node->fid)) {

      for ($i = 1; $i <= $choice_count; $i++) {
        $short = isset($this->node->alternatives['targets'][$i]) ? $this->node->alternatives['targets'][$i] : NULL;

        $form['alternatives']['targets'][$i]['id'] = array(
          '#type' => 'value',
          '#value' => $short['id'],
        );

        $form['alternatives']['targets'][$i]["targettext"] = array(
          '#type' => 'textfield',
          '#default_value' => $short['targettext'],
        );

        $form['alternatives']['targets'][$i]['selected_region'] = array(
          '#type' => 'button',
          '#value' => t('Set region !i', array('!i' => $i)),
          '#attributes' => array('class' => array('image_target_question-select-region')),
        );

        $form['alternatives']['targets'][$i]['region'] = array(
          '#type' => user_access('access devel information') ? 'hidden' : 'hidden',
          '#default_value' => ( isset($short) ? "{$short['top']},{$short['leftpx']},{$short['width']},{$short['height']}" : ''),
          '#size' => 10,
          '#attributes' => array(
            'class' => array('image_target_question-region'),
            'id' => 'edit-alternatives-targets-' . $i . '-region',
          ),
        );

        $form['alternatives']['targets'][$i]['score_if_correct'] = array(
          '#type' => 'textfield',
          '#size' => 2,
          '#maxlength' => 2,
          '#default_value' => isset($short['score_if_correct']) ? $short['score_if_correct'] : 1,
        );

        $form['alternatives']['targets'][$i]['score_if_not_correct'] = array(
          '#type' => 'textfield',
          '#size' => 4,
          '#maxlength' => 4,
          '#default_value' => isset($short['score_if_not_correct']) ? $short['score_if_not_correct'] : 0,
        );
      }
    }

    $form['feedback'] = array(
      '#type' => 'text_format',
      '#base_type' => 'textarea',
      '#title' => t('Feedback'),
      '#description' => t('Enter the feedback the users will see on the report at the end of the quiz'),
      '#default_value' => isset($this->node->feedback) ? $this->node->feedback : '',
      '#format' => isset($this->node->feedback_format) ? $this->node->feedback_format : filter_default_format(),
    );

    return $form;
  }

  /**
   * Helper function to generate the image in the form
   */
  public function generateImageMarkupFormElement() {
    $default_settings = $this->getDefaultAltSettings();

    $fileimg = '';
    $height = '';
    if ($default_settings['fid']) {
      $file = file_load($default_settings['fid']);
      if ($file) {
        $imgurl = '';
        if (image_target_question_get_image_style()) {
          $imgurl = image_style_url(image_target_question_get_image_style()->name, $file->uri);
        }
        else {
          $scheme = file_uri_scheme($file->uri);
          $wrapper = file_stream_wrapper_get_instance_by_scheme($scheme);
          $imgurl = url($wrapper->getDirectoryPath() . '/' . file_uri_target($file->uri));
        }
        $fileimg = theme('image', array(
          'path' => $imgurl,
          'title' => 'Image target',
          'alt' => 'Drag and drop image target.',
          'attributes' => array('style' => 'position: absolute;'),
        ));
        $height = ' height: ' . (intval($default_settings['height']) + 25) . 'px;';
      }
    }

    return array(
      '#markup' => "<div id=\"image_target_question_image\" style=\"position: relative;{$height}\">{$fileimg}</div>",
    );
  }

  /**
   * Helper function provding the default settings for the creation form.
   *
   * @return array
   *   Array with the default settings
   */
  public function getDefaultAltSettings() {
    return array(
      'fid' => isset($this->node->fid) ? $this->node->fid : 0,
      'width' => isset($this->node->width) ? $this->node->width : 0,
      'height' => isset($this->node->fid) ? image_target_question_get_image_height($this->node->fid) : 0,
      'feedback' => isset($this->node->feedback) ? $this->node->feedback : '',
      'feedback_format' => isset($this->node->feedback_format) ? $this->node->feedback_format : filter_default_format(),
    );
  }

  /**
   * Implementation of getMaximumScore.
   * Calculate the maximum score for this question
   * @return int
   *   The maximum score possible on this question
   * @see QuizQuestion::getMaximumScore()
   */
  public function getMaximumScore() {
    $max = 0;
    for ($i = 1; isset($this->node->alternatives['targets'][$i]); $i++) {
      if (drupal_strlen($this->node->alternatives['targets'][$i]['targettext']) > 0) {
        $short = $this->node->alternatives['targets'][$i];
        $max += max($short['score_if_correct'], $short['score_if_not_correct']);
      }
    }
    return max($max, 1);
  }

}

/**
 * Extension of QuizQuestionResponse
 */
class ImageTargetResponse extends QuizQuestionResponse {

  /**
   * array $userAnswers
   *   IDs of the user supplied answers.
   */
  protected $userAnswers;

  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $tries = NULL) {
    parent::__construct($result_id, $question_node, $tries);
    $this->userAnswers = array();

    if (is_array($tries)) {
      $answer = is_array($tries['answer']) ? $tries['answer']['answer'] : $tries['answer'];
      $targets = explode(":", $answer);
      $i = 1;
      foreach ($targets as $target) {
        $coords = explode(',', $target);
        $this->userAnswers[$i] = array(
          'top' => $coords[0],
          'leftpx' => $coords[1],
          'target_id' => $question_node->alternatives['targets'][$i]['id'],
        );
        $i++;
      }
    }
    else {
      $res = db_select('quiz_image_target_question_user_answers', 'ua')
        ->condition('result_id', $result_id)
        ->condition('question_nid', $this->question->nid)
        ->condition('question_vid', $this->question->vid);

      $res->leftJoin('quiz_image_target_question_user_answer_targets', 'uam', 'uam.user_answer_id = ua.id');
      $res->fields('uam', array('target_id', 'top', 'leftpx'));
      $res = $res->execute();

      $i = 1;
      while ($res_o = $res->fetchAssoc()) {
        $this->userAnswers[$i] = $res_o;
        $i++;
      }
    }
  }

  /**
   * Implementation of isValid
   *
   * @see QuizQuestionResponse::isValid()
   */
  public function isValid() {
    if (empty($this->userAnswers)) {
      return t('You place every target');
    }

    foreach ($this->userAnswers as $coords) {
      if (count($coords) != 2 || !is_numeric($coords[0]) || !is_numeric($coords[1])) {
        // TODO: Should they place every target?
      }
    }
    return TRUE;
  }

  /**
   * Implementation of save
   *
   * @see QuizQuestionResponse::save()
   */
  public function save() {
    $answer = new stdClass();
    $answer->result_id = $this->rid;
    $answer->question_nid = $this->question->nid;
    $answer->question_vid = $this->question->vid;
    drupal_write_record('quiz_image_target_question_user_answers', $answer);

    for ($i = 1; $i <= count($this->userAnswers); $i++) {
      $answer_target = new stdClass();
      $answer_target->user_answer_id = $answer->id;
      $answer_target->target_id = $this->userAnswers[$i]['target_id'];
      $answer_target->top = $this->userAnswers[$i]['top'];
      $answer_target->leftpx =  $this->userAnswers[$i]['leftpx'];
      drupal_write_record('quiz_image_target_question_user_answer_targets', $answer_target);
    }
  }

  /**
   * @see QuizQuestionResponse::delete()
   */
  public function delete() {
    $user_answer_id = array();
    $query = db_select('quiz_image_target_question_user_answers', 'a')
      ->fields('a', array('id'))
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->condition('result_id', $this->rid)
      ->execute();

    while ($user_answer = $query->fetch()) {
      $user_answer_id[] = $user_answer->id;
    }

    if (!empty($user_answer_id)) {
      db_delete('quiz_image_target_question_user_answer_targets')
        ->condition('user_answer_id', $user_answer_id, 'IN')
        ->execute();
    }

    db_delete('quiz_image_target_question_user_answers')
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
    foreach ($this->question->alternatives['targets'] as $key => $region) {
      if (isset($this->userAnswers[$key])) {
        if ($this->checkTargetInRegion($this->userAnswers[$key], $region)) {
          $score += $region['score_if_correct'];
        }
        else {
          $score += $region['score_if_not_correct'];
        }
      }
    }
    return $score;
  }

  /**
   * Given a target and region, checks that the target is in the region
   *
   * @param array $target
   *   Values are in px ['top', 'leftpx']
   * @param array $region
   *   Values in px ['top', 'leftpx', 'width', 'height']
   *
   * @return boolean
   *   TRUE if target is inside the region, FALSE if outside
   */
  public function checkTargetInRegion($target, $region) {
    return  ($target['leftpx'] >= $region['leftpx'] && $target['leftpx'] <= ($region['leftpx'] + $region['width'])
      && $target['top'] >= $region['top'] && $target['top'] <= ($region['top'] + $region['height']));
  }

  /**
   * Implementation of getResponse
   */
  public function getResponse() {
    return $this->userAnswers;
  }

  /**
   * Implementation of getReportFormResponse
   */
  public function getReportFormResponse($showcorrect = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    $feedback = $this->checkMarkup($this->question->feedback, $this->question->feedback_format);

    $answers = array();
    foreach ($this->question->alternatives['targets'] as $i => $short) {
      if (drupal_strlen(check_plain($short['targettext'])) > 0) {
        $answers[$i]['targettext'] = $short['targettext'];
        $answers[$i]['score'] = $this->checkTargetInRegion($this->userAnswers[$i], $short) ? $short['score_if_correct'] : $short['score_if_not_correct'];
        $answers[$i]['correct'] = $answers[$i]['score'] > 0;
        $answers[$i]['region'] = $short;
        $answers[$i]['target'] = $this->userAnswers[$i];
      }
    }

    return array(
      '#markup' => theme('image_target_question_response', array(
        'fid' => $this->question->fid,
        'answers' => $answers,
        'feedback' => $feedback,
        'showcorrect' => $showcorrect,
        'showfeedback' => $showfeedback,
      )),
    );
  }

  /**
   * Run check_markup() on the field of the specified choice alternative
   *
   * @param string $alternative
   *   text to be checked
   * @param int $format
   *   The input format to be used
   * @param boolean $check_user_access
   *   Whether or not we are to check the users access to the chosen format
   *
   * @return string
   *   The clean HTML markup
   */
  public function checkMarkup($alternative, $format, $check_user_access = FALSE) {
    if (drupal_strlen($alternative) == 0) {
      return '';
    }
    return check_markup($alternative, $format, $check_user_access);
  }
}
