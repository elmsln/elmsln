<?php

/**
 * The main classes for the drag and drop with lines question type.
 *
 * These inherit or implement code found in quiz_question.classes.inc.
 *
 * Sponsored by: Senter for IKT i utdanningen
 * Code: paalj
 *
 * Based on:
 * Other question types in the quiz framework.
 *
 * @file
 * Question type, enabling the creation of dragging a choice to the correct location in an image
 */

/**
 * Extension of QuizQuestion.
 */
class DDLinesQuestion extends QuizQuestion {
   /**
   * Get the form used to create a new question.
   *
   * @param
   *  FAPI form state
   * @return
   *  Must return a FAPI array.
   */
    
  public function getCreationForm(array &$form_state = NULL) {
    
    $elements = '';
    if(isset($this->node->translation_source)) {
      $elements = $this->node->translation_source->ddlines_elements;
    }
    elseif(isset($this->node->ddlines_elements)) {
      $elements = $this->node->ddlines_elements;
    }
    
    $form['ddlines_elements'] = array(
      '#type' => 'hidden',
      '#default_value' => $elements,
    );
    
    $default_settings = $this->getDefaultAltSettings();
    
    $form['settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      '#weight' => -3,
    );
    $form['settings']['feedback_enabled'] = array(
      '#type' => 'checkbox',
      '#title' => t('Enable feedback'),
      '#description' => t('When taking the test, and this option is enabled, a wrong placement of an alternative, will make it jump back. Also, this makes it possible to add comments to both correct and wrong answers.'),
      '#default_value' => isset($this->node->translation_source) ? $this->node->translation_source->feedback_enabled : $default_settings['feedback']['enabled'],
      '#parents' => array('feedback_enabled'),
    );
    $form['settings']['hotspot_radius'] = array(
      '#type' => 'textfield',
      '#title' => t('Hotspot radius'),
      '#description' => t('The radius of the hotspot in pixels'),
      '#default_value' => isset($this->node->translation_source) ? $this->node->translation_source->hotspot_radius : $default_settings['hotspot']['radius'],
      '#parents' => array('hotspot_radius'),
    );    
    
    $form['settings']['execution_mode'] = array(
      '#type' => 'radios',
      '#title' => t('Execution mode'),
      '#description' => t('The mode for taking the test.'),
      '#default_value' => isset($this->node->translation_source) ? $this->node->translation_source->execution_mode : $default_settings['execution_mode'],
      '#options' => array (
        0 => t('With lines'),
        1 => t('Drag label'),
      ),
      '#parents' => array('execution_mode'),
    );    
    
    drupal_add_library('system','ui.resizable');
    
    $default_settings['mode'] = 'edit';
    $default_settings['editmode'] = isset($this->node->nid) ? 'update' : 'add';
    $form['#attached']['js'][] = array(
  		'data' => array(
    		'quiz_ddlines' => $default_settings
        ),
  		'type' => 'setting'
    );
    
    _quiz_ddlines_add_js_and_css();
    
    return $form;
  }
  
  /**
   * This makes max_score beeing updated for all occurrences of
   * this question in quizzes.
   */
  protected function autoUpdateMaxScore() {
    return true;
  }
  
  /**
   * Helper function provding the default settings for the creation form.
   *
   * @return
   *  Array with the default settings
   */
  private function getDefaultAltSettings() {
    $settings = array();
    
    // If the node exists, use saved value
    if (isset($this->node->nid)) {      
      $settings['feedback']['enabled'] = $this->node->feedback_enabled;
      $settings['hotspot']['radius'] = $this->node->hotspot_radius;
      $settings['execution_mode'] = $this->node->execution_mode;
    }      
    else {      
      $settings['feedback']['enabled'] = 0;
      $settings['hotspot']['radius'] = variable_get('quiz_ddlines_hotspot_radius', Defaults::HOTSPOT_RADIUS);
      $settings['execution_mode'] = 0;
    }

    // Pick these from settings:
    $settings['feedback']['correct'] = variable_get('quiz_ddlines_feedback_correct', t('Correct'));
    $settings['feedback']['wrong'] = variable_get('quiz_ddlines_feedback_wrong', t('Wrong'));
    $settings['canvas']['width'] = variable_get('quiz_ddlines_canvas_width', Defaults::CANVAS_WIDTH);
    $settings['canvas']['height'] = variable_get('quiz_ddlines_canvas_height', Defaults::CANVAS_HEIGHT); 
    $settings['pointer']['radius'] = variable_get('quiz_ddlines_pointer_radius', Defaults::POINTER_RADIUS);
    
    return $settings;
  }
  
  /**
   * Generates the question form.
   *
   * This is called whenever a question is rendered, either
   * to an administrator or to a quiz taker.
   */
  public function getAnsweringForm(array $form_state = NULL, $rid) {
    
    $form = parent::getAnsweringForm($form_state, $rid);
    
    $form['helptext'] = array(
      '#markup' => t('Answer this question by dragging each rectangular label to the correct circular hotspot.'),
      '#weight' => 0,
    );
    
    // Form element containing the correct answers    
    $form['ddlines_elements'] = array(
      '#type' => 'hidden',
      '#default_value' => isset($this->node->ddlines_elements) ? $this->node->ddlines_elements : '',
    );
    
    // Form element containing the user answers
    // The quiz module requires this element to be named "tries":
    $form['tries'] = array (
      '#type' => 'hidden',
      '#default_value' => '',
    );
    
    $image_uri = $this->node->field_image['und'][0]['uri'];
    $image_url = image_style_url('large',$image_uri);
    
    $form['image'] = array (      
      '#markup' => '<div class="image-preview">'.theme('image', array('path' => $image_url)).'</div>',
      /*'#weight' => 0,*/
    );
    
    $default_settings = $this->getDefaultAltSettings();
    $default_settings['mode'] = 'take';
    $form['#attached']['js'][] = array(
  		'data' => array(
    		'quiz_ddlines' => $default_settings
        ),
  		'type' => 'setting'
    );
    
    _quiz_ddlines_add_js_and_css();
    
    return $form;
  }

  /**
   * Get the maximum possible score for this question.
   */
  public function getMaximumScore() {
    // 1 point per correct hotspot location    
    $ddlines_elements = json_decode($this->node->ddlines_elements);
    
    $max_score = isset($ddlines_elements->elements) ? sizeof($ddlines_elements->elements) : 0;
    
    return $max_score;
  }

  /**
   * Save question type specific node properties
   */
  public function saveNodeProperties($is_new = FALSE) {
    if ($is_new || $this->node->revision == 1) {
      $id = db_insert('quiz_ddlines_node')
        ->fields(array(
          'nid' => $this->node->nid,
          'vid' => $this->node->vid,
          'feedback_enabled' => $this->node->feedback_enabled,
          'hotspot_radius' => $this->node->hotspot_radius,
          'ddlines_elements' => $this->node->ddlines_elements,
          'execution_mode' => $this->node->execution_mode,
        ))
        ->execute();
    }
    else {
      db_update('quiz_ddlines_node')
        ->fields(array(
          'ddlines_elements' => $this->node->ddlines_elements,
          'hotspot_radius' => $this->node->hotspot_radius,
          'feedback_enabled' => $this->node->feedback_enabled,
          'execution_mode' => $this->node->execution_mode,
        ))
        ->condition('nid', $this->node->nid)
        ->condition('vid', $this->node->vid)
        ->execute();
    }
  }
  
  /**
   * Implementation of getNodeProperties
   *
   * @see QuizQuestion#getNodeProperties()
   */
  public function getNodeProperties() {
    if (isset($this->nodeProperties) && !empty($this->nodeProperties)) {
      return $this->nodeProperties;
    }
    $props = parent::getNodeProperties();

    $res_a = db_query('SELECT feedback_enabled, hotspot_radius, ddlines_elements, execution_mode FROM {quiz_ddlines_node} WHERE nid = :nid AND vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid))->fetchAssoc();

    if (is_array($res_a)) {
      $props = array_merge($props, $res_a);
    }
    $this->nodeProperties = $props;
    return $props;
  }
  
  /**
   * Provides validation for question before it is created.
   *
   * When a new question is created and initially submited, this is
   * called to validate that the settings are acceptible.
   *
   * @param $form
   *  The processed form.
   */
  public function validateNode(array &$form) {
    // Nothing todo here
  }
  
/**
   * Implementation of delete
   *
   * @see QuizQuestion#delete()
   */
  public function delete($only_this_version = FALSE) {
    $delete_node = db_delete('quiz_ddlines_node')->condition('nid', $this->node->nid);    
    $delete_results = db_delete('quiz_ddlines_user_answers')->condition('question_nid', $this->node->nid);

    if ($only_this_version) {
      $delete_node->condition('vid', $this->node->vid);
      $delete_results->condition('question_vid', $this->node->vid);
    }

    // Delete from table quiz_ddlines_user_answer_multi
    $user_answer_ids = array();
    if ($only_this_version) {
      $query = db_query('SELECT id FROM {quiz_ddlines_user_answers} WHERE question_nid = :nid AND question_vid = :vid', array(':nid' => $this->node->nid, ':vid' => $this->node->vid));
    }
    else {
      $query = db_query('SELECT id FROM {quiz_ddlines_user_answers} WHERE question_nid = :nid', array(':nid' => $this->node->nid));
    }
    while ($user_answer = $query->fetch()) {    
      $user_answer_ids[] = $user_answer->id;
    }

    if (count($user_answer_ids)) {
      db_delete('quiz_ddlines_user_answer_multi')
        ->condition('user_answer_id', $user_answer_ids, 'IN')
        ->execute();
    }
    
    $delete_node->execute();    
    $delete_results->execute();
    parent::delete($only_this_version);
  }
}

/**
 * Extension of QuizQuestionResponse
 */
class DDLinesResponse extends QuizQuestionResponse {
  
  // Contains a assoc array with label-ID as key 
  // and hotspot-ID as value:
  protected $user_answers = array();
  
  /**
   * Constructor
   */
  public function __construct($result_id, stdClass $question_node, $tries = NULL) {
    parent::__construct($result_id, $question_node, $tries);
    
    // Is answers set in form?
    if (isset($tries)) {
      // Tries contains the answer decoded as JSON:
      // {"label_id":x,"hotspot_id":y},{...}
      $decoded = json_decode($tries);
      if(is_array($decoded)) {
        foreach ($decoded as $answer) {
          $this->user_answers[$answer->label_id] = $answer->hotspot_id;  
        }
      }
    }
    // Load from database
    else {
      $res = db_query('SELECT label_id, hotspot_id FROM {quiz_ddlines_user_answers} ua
              LEFT OUTER JOIN {quiz_ddlines_user_answer_multi} uam ON(uam.user_answer_id = ua.id)
              WHERE ua.result_id = :result_id AND ua.question_nid = :question_nid AND ua.question_vid = :question_vid', array(':result_id' => $result_id, ':question_nid' => $this->question->nid, ':question_vid' => $this->question->vid));
      while ($row = $res->fetch()) {
        $this->user_answers[$row->label_id] = $row->hotspot_id;
      }
    }
  }
  
  /**
   * Save the current response.
   */
  public function save() {
    $user_answer_id = db_insert('quiz_ddlines_user_answers')
      ->fields(array(
        'question_nid' => $this->question->nid,
        'question_vid' => $this->question->vid,
        'result_id' => $this->rid,
      ))
      ->execute();
      
    // Each alternative is inserted as a separate row
    $query = db_insert('quiz_ddlines_user_answer_multi')
      ->fields(array('user_answer_id', 'label_id', 'hotspot_id'));
    foreach ($this->user_answers as $key => $value) {
      $query->values(array($user_answer_id, $key, $value));
    }
    $query->execute();
   
  }

  /**
   * Delete the response.
   */
  public function delete() {

    $user_answer_ids = array();
    $query = db_query('SELECT id FROM {quiz_ddlines_user_answers} WHERE question_nid = :nid AND question_vid = :vid AND result_id = :result_id', array(':nid' => $this->question->nid, ':vid' => $this->question->vid, ':result_id' => $this->rid));
    while ($answer = $query->fetch()) {
      $user_answer_ids[] = $answer->id;
    }

    if (!empty($user_answer_ids)) {
      db_delete('quiz_ddlines_user_answer_multi')
        ->condition('user_answer_id', $user_answer_ids, 'IN')
        ->execute();
    }

    db_delete('quiz_ddlines_user_answers')
      ->condition('result_id', $this->rid)
      ->condition('question_nid', $this->question->nid)
      ->condition('question_vid', $this->question->vid)
      ->execute();
  }

  /**
   * Calculate the score for the response.
   */
  public function score() {    
    $results = $this->getDragDropResults();
    
    // Count number of correct answers:
    $correct_count = 0;
    
    foreach($results as $result) {
      $correct_count += ($result == AnswerStatus::CORRECT) ? 1 : 0;
    } 
    
    return $correct_count;
  }

  /**
   * Get the user's response.
   */
  public function getResponse() {
    return $this->user_answers;
  }
  
  public function getReportFormResponse($showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
    // Have to do node_load, since quiz does not do this. Need the field_image... 
    $img_field = field_get_items('node', node_load($this->question->nid), 'field_image');
    $img_rendered = theme('image', array('path' => image_style_url('large',$img_field[0]['uri'])));
    
    $image_path = base_path() . drupal_get_path('module', 'quiz_ddlines').'/theme/images/';
    
    $html = '<h3>'.t('Your answers').'</h3>';
    $html .= '<div class="icon-descriptions"><div><img src="'.$image_path.'icon_ok.gif">'.t('Means alternative is placed on the correct spot').'</div>';
    $html .= '<div><img src="'.$image_path.'icon_wrong.gif">'.t('Means alternative is placed on the wrong spot, or not placed at all'). '</div></div>';
    $html .= '<div class="quiz-ddlines-user-answers" id="'.$this->question->nid.'">';
    $html .= $img_rendered;
    $html .= '</div>';
    $html .= '<h3>'.t('Correct answers').'</h3>';
    $html .= '<div class="quiz-ddlines-correct-answers" id="'.$this->question->nid.'">';
    $html .= $img_rendered;
    $html .= '</div>';
    
    // No form to put things in, are therefore using the js settings instead
    $settings = array();
    $correct_id = "correct-{$this->question->nid}";
    $settings[$correct_id] = json_decode($this->question->ddlines_elements);
    $elements = $settings[$correct_id]->elements;
    
    // Convert the user's answers to the same format as the correct answers
    $answers = clone $settings[$correct_id]; 
    // Keep everything except the elements:
    $answers->elements = array();    
    
    $elements_answered = array();
    
    foreach ($this->user_answers as $label_id => $hotspot_id ) {
      
      if(!isset($hotspot_id)) {
        continue;
      }
      
      // Find correct answer:
      $element = array(
        'feedback_wrong' => '',
        'feedback_correct' => '',
        'color' => $this->getElementColor($elements, $label_id)
      );
      
      $label = $this->getLabel($elements, $label_id);
      $hotspot = $this->getHotspot($elements, $hotspot_id);
      
      if(isset($hotspot)) {
        $elements_answered[] = $hotspot->id;
        $element['hotspot'] = $hotspot;
      }
      
      if(isset($label)) {
        $elements_answered[] = $label->id;
        $element['label'] = $label;
      }
      
      $element['correct'] = $this->isAnswerCorrect($elements, $label_id, $hotspot_id);
      $answers->elements[] = $element;
    }
    
    // Need to add the alternatives not answered by the user. 
    // Create dummy elements for these:
    foreach ($elements as $el) {
      if(!in_array($el->label->id, $elements_answered)) {
        $element = array(
        	'feedback_wrong' => '',
        	'feedback_correct' => '',
        	'color' => $el->color,
            'label' => $el->label,
        );
        $answers->elements[] = $element;
      }
     
      if(!in_array($el->hotspot->id, $elements_answered)) {
        $element = array(
        	'feedback_wrong' => '',
        	'feedback_correct' => '',
        	'color' => $el->color,
            'hotspot' => $el->hotspot,
        );
        $answers->elements[] = $element;
      }
    }
    
    $settings["answers-{$this->question->nid}"] = $answers;
    $settings['mode'] = 'result';
    $settings['execution_mode'] = $this->question->execution_mode;
    $settings['hotspot']['radius'] = $this->question->hotspot_radius;
    
    // Image path:
    $settings['quiz_imagepath'] = base_path() . drupal_get_path('module', 'quiz_ddlines').'/theme/images/';
    
    drupal_add_js(array('quiz_ddlines' => $settings), 'setting');
    
    _quiz_ddlines_add_js_and_css();
    
    return array('#markup' => $html);
  }
  
  private function getElementColor($list, $id) {
    foreach($list as $element) {
      if ($element->label->id == $id) {
        return $element->color;
      }
    }
  }
  
  private function getHotspot($list, $id) {
    foreach($list as $element) {
      if ($element->hotspot->id == $id) {
        return $element->hotspot;
      }
    }
  }
  
  private function getLabel($list, $id) {
    foreach($list as $element) {
      if ($element->label->id == $id) {
        return $element->label;
      }
    }
  }
  
  private function isAnswerCorrect($list, $label_id, $hotspot_id) {
    foreach ($list as $element) {
      if($element->label->id == $label_id) {
        return ($element->hotspot->id == $hotspot_id);
      }
    }
    
    return false;
  }
  
  /**
   * 
   * Get a list of the labels, tagged correct, false, or no answer
   */
  private function getDragDropResults() {
    $results = array();
    
    // Iterate through the correct answers, and check 
    // the users answer:    
    foreach(json_decode($this->question->ddlines_elements)->elements as $element) {
      $source_id = $element->label->id;
      
      if(isset($this->user_answers[$source_id])) {
        $results[$element->label->id] = ($this->user_answers[$source_id] == $element->hotspot->id) ? AnswerStatus::CORRECT : AnswerStatus::WRONG;
      }
      else {
        $results[$element->label->id] = AnswerStatus::NO_ANSWER;
      }
    }
    
    return $results;
  }
}
