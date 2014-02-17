<?php

/**
 * Administrator interface for Quiz module.
 *
 * @file
 */


// QUIZ ADMIN

// Quiz Admin Settings

/**
 * This builds the main settings form for the quiz module.
 */
function quiz_admin_settings($form, &$form_state) {
  $form = array();

  $form['quiz_global_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Configuration'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Control aspects of the Quiz module\'s display'),
  );

  $form['quiz_global_settings']['quiz_auto_revisioning'] = array(
    '#type' => 'checkbox',
    '#title' => t('Auto revisioning'),
    '#default_value' => variable_get('quiz_auto_revisioning', 1),
    '#description' => t('It is strongly recommended that auto revisioning is always on. It makes sure that when a question or quiz is changed a new revision is created if the current revision has been answered. If this feature is switched off result reports might be broken because a users saved answer might be connected to a wrong version of the quiz and/or question she was answering. All sorts of errors might appear.'),
  );

  $form['quiz_global_settings']['quiz_durod'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete results when a user is deleted'),
    '#default_value' => variable_get('quiz_durod', 0),
    '#description' => t('When a user is deleted delete any and all results for that user.'),
  );

  $form['quiz_global_settings']['quiz_index_questions'] = array(
    '#type' => 'checkbox',
    '#title' => t('Index questions'),
    '#default_value' => variable_get('quiz_index_questions', 1),
    '#description' => t('If you turn this off questions will not show up in search results.'),
  );

  $form['quiz_global_settings']['quiz_default_close'] = array(
    '#type' => 'textfield',
    '#title' => t('Default number of days before a @quiz is closed', array('@quiz' => QUIZ_NAME)),
    '#default_value' => variable_get('quiz_default_close', 30),
    '#size' => 4,
    '#maxlength' => 4,
    '#description' => t('Supply a number of days to calculate the default close date for new quizzes.'),
  );

  $form['quiz_global_settings']['quiz_use_passfail'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow quiz creators to set a pass/fail option when creating a @quiz.', array('@quiz' => strtolower(QUIZ_NAME))),
    '#default_value' => variable_get('quiz_use_passfail', 1),
    '#description' => t('Check this to display the pass/fail options in the @quiz form. If you want to prohibit other quiz creators from changing the default pass/fail percentage, uncheck this option.', array('@quiz' => QUIZ_NAME)),
  );

  $form['quiz_global_settings']['quiz_max_result_options'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum Result Options'),
    '#description' => t('Set the maximum number of result options (categorizations for scoring a quiz). Set to 0 to disable result options.'),
    '#default_value' => variable_get('quiz_max_result_options', 5),
    '#size' => 2,
    '#maxlength' => 2,
    '#required' => FALSE,
  );

  $form['quiz_global_settings']['quiz_remove_partial_quiz_record'] = array(
    '#type' => 'select',
    '#title' => t('Remove Incomplete Quiz Records (older than)'),
    '#options' => quiz_remove_partial_quiz_record_value(),
    '#description' => t('Number of days that you like to keep the incomplete quiz records'),
    '#default_value' => variable_get('quiz_remove_partial_quiz_record', quiz_remove_partial_quiz_record_value()),
  );

  $form['quiz_global_settings']['quiz_autotitle_length'] = array(
    '#type' => 'textfield',
    '#title' => t('Length of automatically set question titles'),
    '#size' => 3,
    '#maxlength' => 3,
    '#description' => t('Integer between 0 and 128. If the question creator doesn\'t set a question title the system will make a title automatically. Here you can decide how long the autotitle can be.'),
    '#default_value' => variable_get('quiz_autotitle_length', 50),
  );

  $target = array(
    'attributes' => array(
      'target' => '_blank'
    ),
  );

  $links = array(
    '!views' => l(t('Views'), 'http://drupal.org/project/views', $target),
    '!cck' => l(t('CCK'), 'http://drupal.org/project/cck', $target),
    '!jquery_countdown' => l(t('JQuery Countdown'), 'http://drupal.org/project/jquery_countdown', $target),
    '!userpoints' => l(t('UserPoints'), 'http://drupal.org/project/userpoints', $target),
    '@quiz' => QUIZ_NAME,
  );

  $form['quiz_addons'] = array(
    '#type' => 'fieldset',
    '#title' => t('Addons Configuration'),
    '#description' => t('Quiz can integrate with other d.o modules like !views, !cck, !userpoints and !jquery_countdown. Here you can configure the way Quiz integrates with other modules. Disabled checkboxes indicates that modules are not enabled/installed', $links),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['quiz_addons']['quiz_has_userpoints'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable UserPoints Module Integration'),
    '#default_value' => variable_get('quiz_has_userpoints', 0),
    '#description' => t('!userpoints is an <strong>optional</strong> module for Quiz. It provides ways for users to gain or lose points for performing certain actions on your site like attending @quiz. You will need to install the !userpoints module to use this feature.', $links),
    '#disabled' => !module_exists('userpoints'),
  );

  $form['quiz_addons']['quiz_has_timer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display Timer for Timed Quiz'),
    '#default_value' => variable_get('quiz_has_timer', 0),
    '#description' => t("!jquery_countdown is an <strong>optional</strong> module for Quiz. It is used to display a timer when taking a quiz. Without this timer, the user will not know how long he or she has left to complete the @quiz", $links),
    '#disabled' => !function_exists('jquery_countdown_add'),
  );

  $form['quiz_look_feel'] = array(
    '#type' => 'fieldset',
    '#title' => t('Look and Feel Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Control aspects of the Quiz module\'s display'),
  );

  $form['quiz_look_feel']['quiz_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Display name'),
    '#default_value' => QUIZ_NAME,
    '#description' => t('Change the name of the quiz type. Do you call it <em>test</em> or <em>assessment</em> instead? Change the display name of the module to something else. Currently, it is called @quiz. By default, it is called <em>Quiz</em>.',
      array('@quiz' => QUIZ_NAME)),
    '#required' => TRUE,
  );

  $form['quiz_email_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email Settings'),
    '#description' => t('Send results to quiz author/attendee via e-mail. Configure e-mail subject and body.'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['quiz_email_settings']['taker'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail for Quiz Takers'),
    '#collapsible' => FALSE,
  );

  $form['quiz_email_settings']['taker']['quiz_email_results'] = array(
    '#type' => 'checkbox',
    '#title' => t('E-mail results to quiz takers'),
    '#default_value' => variable_get('quiz_email_results', 0),
    '#description' => t('Check this to send users their results at the end of a quiz.')
  );

  $form['quiz_email_settings']['taker']['quiz_email_results_subject_taker'] = array(
    '#type' => 'textfield',
    '#title' => t('Configure E-mail Subject'),
    '#description' => t('This format will be used when sending quiz results at the end of a quiz.'),
    '#default_value' => variable_get('quiz_email_results_subject_taker', quiz_email_results_format('subject', 'taker')),
  );

  $form['quiz_email_settings']['taker']['quiz_email_results_body_taker'] = array(
    '#type' => 'textarea',
    '#title' => t('Configure E-mail Format'),
    '#description' => t('This format will be used when sending quiz results at the end of a quiz. !title(quiz title), !sitename, !taker(quiz takers username), !date(time when quiz was finished), !minutes(How many minutes the quiz taker spent taking the quiz), !desc(description of the quiz), !correct(points attained), !total(max score for the quiz), !percentage(percentage score), !url(url to the result page) and !author are placeholders.'),
    '#default_value' => variable_get('quiz_email_results_body_taker', quiz_email_results_format('body', 'taker')),
  );

  $form['quiz_email_settings']['author'] = array(
    '#type' => 'fieldset',
    '#title' => t('E-mail for Quiz Authors'),
    '#collapsible' => FALSE,
  );

  $form['quiz_email_settings']['author']['quiz_results_to_quiz_author'] = array(
    '#type' => 'checkbox',
    '#title' => t('E-mail all results to quiz author.'),
    '#default_value' => variable_get('quiz_results_to_quiz_author', 0),
    '#description' => t('Check this to send quiz results for all users to the quiz author.'),
  );

  $form['quiz_email_settings']['author']['quiz_email_results_subject'] = array(
    '#type' => 'textfield',
    '#title' => t('Configure E-mail Subject'),
    '#description' => t('This format will be used when sending quiz results at the end of a quiz. Authors and quiz takers gets the same format.'),
    '#default_value' => variable_get('quiz_email_results_subject', quiz_email_results_format('subject', 'author')),
  );

  $form['quiz_email_settings']['author']['quiz_email_results_body'] = array(
    '#type' => 'textarea',
    '#title' => t('Configure E-mail Format'),
    '#description' => t('This format will be used when sending quiz results at the end of a quiz. !title(quiz title), !sitename, !taker(quiz takers username), !date(time when quiz was finished), !minutes(How many minutes the quiz taker spent taking the quiz), !desc(description of the quiz), !correct(points attained), !total(max score for the quiz), !percentage(percentage score), !url(url to the result page) and !author are placeholders.'),
    '#default_value' => variable_get('quiz_email_results_body', quiz_email_results_format('body', 'author')),
  );

  $form['def_settings_link'] = array(
    '#markup' => '<p>' . t('Default values for the quiz creation form can be edited <a href="!url">here</a>', array('!url' => url('admin/quiz/settings/quiz_form'))) . '</p>',
  );

  $form['#validate'][] = 'quiz_settings_form_validate';
  $form['#submit'][] = 'quiz_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Validation of the Form Settings form.
 *
 * Checks the values for the form administration form for quiz settings.
 */
function quiz_settings_form_validate($form, &$form_state) {
  if (!_quiz_is_int($form_state['values']['quiz_default_close'])) {
    form_set_error('quiz_default_close', t('The default number of days before a quiz is closed must be a number greater than 0.'));
  }

  if (!_quiz_is_int($form_state['values']['quiz_autotitle_length'], 0, 128)) {
    form_set_error('quiz_autotitle_length', t('The autotitle length value must be an integer between 0 and 128.'));
  }

  if (!_quiz_is_int($form_state['values']['quiz_max_result_options'], 0, 100)) {
    form_set_error('quiz_max_result_options', t('The number of resultoptions must be an integer between 0 and 100.'));
  }

  if (!_quiz_is_plain($form_state['values']['quiz_name'])) {
    form_set_error('quiz_name', t('The quiz name must be plain text.'));
  }

  /*if (!_quiz_is_plain($form_state['values']['quiz_action_type']))
   form_set_error('quiz_action_type', t('The action type must be plain text.'));*/
}

/**
 * Submit the admin settings form
 */
function quiz_settings_form_submit($form, &$form_state) {
  if (QUIZ_NAME != $form_state['values']['quiz_name']) {
    variable_set('quiz_name', $form_state['values']['quiz_name']);
    define(QUIZ_NAME, $form_state['values']['quiz_name']);
    menu_rebuild();
  }
}

/**
 * Renders the quiz node form for the admin pages
 *
 * This form is used to configure default values for the quiz node form
 */
function quiz_admin_node_form($form, &$form_state) {
  // Create a dummy node to use as input for quiz_form
  $dummy_node = new stdClass();
  // def_uid is the uid of the default user holding the default values for the node form(no real user with this uid exists)
  $dummy_node->def_uid = variable_get('quiz_def_uid', 1);
  $settings = _quiz_load_user_settings(variable_get('quiz_def_uid', 1));
  $settings += _quiz_get_node_defaults();
  foreach ($settings as $key => $value) {
    if (!isset($dummy_node->$key)) {
      $dummy_node->{$key} = $value;
    }
  }
  $form = quiz_form($dummy_node, $form_state);
  $form['direction'] = array(
    '#markup' => t('Here you can change the default quiz settings for new users.'),
    '#weight' => -10,
  );
  // unset values we can't or won't let the user edit default values for
  unset(
    $form['#quiz_check_revision_access'],
    $form['title'],
    $form['body_field'],
    $form['taking']['aid'],
    $form['taking']['addons'],
    $form['quiz_availability']['quiz_open'],
    $form['quiz_availability']['quiz_close'],
    $form['resultoptions'],
    $form['number_of_random_questions']
  );

  $form['remember_settings']['#type'] = 'value';
  $form['remember_settings']['#default_value'] = TRUE;

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#submit' => array('quiz_admin_node_form_submit'),
  );
  return $form;
}

/**
 * Validation function for the quiz_admin_node_form form
 */
function quiz_admin_node_form_validate($form, &$form_state) {
  // Create dummy node for quiz_validate
  $dummy_node = new stdClass();
  foreach ($form_state['values'] as $key => $value) {
    $dummy_node->{$key} = $value;
  }
  $dummy_node->resultoptions = array();

  // We use quiz_validate to validate the default values
  quiz_validate($dummy_node);
}

/**
 * Submit function for quiz_admin_node_form
 *
 * The default values are saved as the user settings for the "default user"
 * The default user is created when quiz is installed. He has a unique uid, but doesn't exist
 * as a real user.
 *
 * Why?
 * Default user settings can be loaded and saved using the same code and
 * database tables as any other user settings, making the code a lot easier to maintain.
 * Ref: http://en.wikipedia.org/wiki/Don%27t_repeat_yourself
 */
function quiz_admin_node_form_submit($form, &$form_state) {
  // We add the uid for the "default user"
  $form_state['values']['save_def_uid'] = variable_get('quiz_def_uid', NULL);
  $form_state['values']['nid'] = 0;
  $form_state['values']['vid'] = 0;
  $form_state['values']['aid'] = '';
  _quiz_save_user_settings($form_state['values']);
}

// QUIZ RESULTS ADMIN

/**
 * Displays the quizzes by title with a link to the appropriate results
 * for that specific quiz.
 *
 * @return
 *  Formatted data.
 */
function quiz_admin_quizzes() {
  global $user;
  $uid = $user->uid;
  if (user_access('view any quiz results')) {
    $uid = NULL;
  }
  $results = _quiz_get_quizzes($uid);
  return theme('quiz_admin_quizzes', array('results' => $results));
}

/**
 * Quiz result report page for the quiz admin section
 *
 * @param $quiz
 *   The quiz node
 * @param $rid
 *   The result id
 */
function quiz_admin_results($quiz, $rid) {
  $breadcrumb = drupal_get_breadcrumb();
  $breadcrumb[] = l(t('Quiz Results'), 'admin/quiz/reports/results');

  // Make sure we have the right version of the quiz
  $vid = db_query('SELECT vid FROM {quiz_node_results} WHERE result_id = :result_id', array(':result_id' => $rid))->fetchField();
  if ($quiz->vid != $vid) {
    $quiz = node_load($quiz->nid, $vid);
  }

  // Get all the data we need.
  $questions = _quiz_get_answers($quiz, $rid);
  $score = quiz_calculate_score($quiz, $rid);
  $summary = _quiz_get_summary_text($quiz, $score);

  // Lets add the quiz title to the breadcrumb array.
  $breadcrumb[] = l($quiz->title, 'admin/quiz/reports/results/' . $quiz->nid);
  //drupal_set_breadcrumb($breadcrumb);
  $data = array(
    'quiz' => $quiz,
    'questions' => $questions,
    'score' => $score,
    'summary' => $summary,
    'rid' => $rid
  );
  return theme('quiz_admin_summary', $data);
}

/**
 * Store values for each browser filters in $_SESSION
 *
 * @param $filters
 *   array holding the values for each filter
 */
function _quiz_results_mr_store_filters($form_state) {
  $pre = 'quiz_results_mr_';
  $filters = $form_state['values']['table']['header']['filters'];
  $_SESSION[$pre . 'name'] = trim($filters['name']);
  $_SESSION[$pre . 'started'] = $filters['started'];
  $_SESSION[$pre . 'finished'] = $filters['finished'];
  $_SESSION[$pre . 'score'] = $filters['score'];
  $_SESSION[$pre . 'evaluated'] = $filters['evaluated'];
  $_SESSION[$pre . 'best_results'] = $filters['best_results'];
  $_SESSION[$pre . 'not_in_progress'] = $filters['not_in_progress'];
}

function quiz_browser_body_callback($form, $form_state) {
  return $form['table']['body'];
}

function quiz_questions_browser_body_callback($form, $form_state) {
  return $form['question_list']['browser']['table']['body'];
}

// MANAGE QUESTIONS

/**
 * Creates a form for quiz questions.
 *
 * Handles the manage questions tab.
 *
 * @param $node
 *   The quiz node we are managing questions for.
 * @return
 *   String containing the form.
 */
function quiz_questions($node) {
  // Set page title.
  drupal_set_title($node->title);
  if ($node->randomization < 3) {
    $form = drupal_get_form('quiz_questions_form', $node);
  }
  else {
    $form = drupal_get_form('quiz_categorized_form', $node);
  }
  return drupal_render($form);
}

/**
 * Form for managing what questions should be added to a quiz with categorized random questions.
 *
 * @param array $form_state
 *  The form state array
 * @param object $quiz
 *  The quiz node
 */
function quiz_categorized_form($form, $form_state, $quiz) {
  $form = array();
  _quiz_categorized_existing_terms_form($form, $form_state, $quiz);
  _quiz_categorized_new_term_form($form, $form_state, $quiz);
  $form['nid'] = array(
    '#type' => 'value',
    '#value' => $quiz->nid,
  );
  $form['vid'] = array(
    '#type' => 'value',
    '#value' => $quiz->vid,
  );
  $form['tid'] = array(
    '#type' => 'value',
    '#value' => NULL,
  );
  // Give the user the option to create a new revision of the quiz
  _quiz_add_revision_checkbox($form, $quiz);
  // Timestamp is needed to avoid multiple users editing the same quiz at the same time.
  $form['timestamp'] = array('#type' => 'hidden', '#default_value' => REQUEST_TIME);
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#tree'] = TRUE;
  return $form;
}

function _quiz_categorized_existing_terms_form(&$form, $form_state, $quiz) {
  $terms = _quiz_get_terms($quiz->vid);
  foreach ($terms as $term) {
    $form[$term->tid]['name'] = array(
      '#markup' => check_plain($term->name),
    );
    $form[$term->tid]['number'] = array(
      '#type' => 'textfield',
      '#size' => 3,
      '#default_value' => $term->number,
    );
    $form[$term->tid]['max_score'] = array(
      '#type' => 'textfield',
      '#size' => 3,
      '#default_value' => $term->max_score,
    );
    $form[$term->tid]['remove'] = array(
      '#type' => 'checkbox',
      '#default_value' => 0,
    );
    $form[$term->tid]['weight'] = array(
      '#type' => 'textfield',
      '#size' => 3,
      '#default_value' => $term->weight,
      '#attributes' => array(
        'class' => array('term-weight')
      ),
    );
  }
}

/**
 * Form for adding new terms to a quiz
 *
 * @see quiz_categorized_form
 */
function _quiz_categorized_new_term_form(&$form, $form_state, $quiz) {
  $form['new'] = array(
    '#type' => 'fieldset',
    '#title' => t('Add category'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => FALSE,
  );
  $form['new']['term'] = array(
    '#type' => 'textfield',
    '#title' => t('Category'),
    '#description' => t('Type in the name of the term you would like to add questions from.'),
    '#autocomplete_path' => "node/$quiz->nid/questions/term_ahah",
    '#field_suffix' => '<a id="browse-for-term" href="javascript:void(0)">' . t('browse') . '</a>',
  );
  $form['new']['number'] = array(
    '#type' => 'textfield',
    '#title' => t('Number of questions'),
    '#description' => t('How many questions would you like to draw from this term?'),
  );
  $form['new']['max_score'] = array(
    '#type' => 'textfield',
    '#title' => t('Max score for each question'),
    '#description' => t('The number of points a user will be awarded for each question he gets correct.'),
    '#default_value' => 1,
  );
}

/**
 * Validate the categorized form
 */
function quiz_categorized_form_validate($form, &$form_state) {
  if (_quiz_is_int(arg(1))) {
    if (node_last_changed(arg(1)) > $form_state['values']['timestamp']) {
      form_set_error('changed', t('This content has been modified by another user, changes cannot be saved.'));
    }
  }
  else {
    form_set_error('changed', t('A critical error has occured. Please report error code 28 on the quiz project page.'));
    return;
  }
  if (!empty($form_state['values']['term'])) {
    $tid = _quiz_get_id_from_string($form_state['values']['term']);
    if ($tid === FALSE) {
      $terms = _quiz_search_terms($form_state['values']['term']);
      $num_terms = count($terms);
      if ($num_terms == 1) {
        $tid = key($terms);
      }
      elseif ($num_terms > 1) {
        form_set_error('term', t('You need to be more specific, or use the autocomplete feature. The term name you entered matches several terms: %terms', array('%terms' => implode(', ', $terms))));
      }
      elseif ($num_terms == 0) {
        form_set_error('term', t("The term name you entered doesn't match any registered question terms."));
      }
    }
    if (in_array($tid, array_keys($form))) {
      form_set_error('term', t('The category you are trying to add has already been added to this quiz.'));
    }
    else {
      form_set_value($form['tid'], $tid, $form_state);
    }

    if (!_quiz_is_int($form_state['values']['number'])) {
      form_set_error('number', t('The number of questions needs to be a positive integer'));
    }
    if (!_quiz_is_int($form_state['values']['max_score'], 0)) {
      form_set_error('max_score', t('The max score needs to be a positive integer or 0'));
    }
  }
}

/**
 * Submit the categorized form
 */
function quiz_categorized_form_submit($form, $form_state) {
  $quiz = node_load($form_state['values']['nid'], $form_state['values']['vid']);
  $quiz->number_of_random_questions = 0;
  // Update the refresh latest quizzes table so that we know what the users latest quizzes are
  if (variable_get('quiz_auto_revisioning', 1)) {
    $is_new_revision = quiz_has_been_answered($quiz);
  }
  else {
    $is_new_revision = (bool) $form_state['values']['new_revision'];
  }
  if (!empty($form_state['values']['tid'])) {
    $quiz->number_of_random_questions += _quiz_categorized_add_term($form, $form_state);
  }
  $quiz->number_of_random_questions += _quiz_categorized_update_terms($form, $form_state);
  if ($is_new_revision) {
    $quiz->revision = 1;
  }
  // We save the node to update its timestamp and let other modules react to the update.
  // We also do this in case a new revision is required...
  node_save($quiz);
}

/**
 * Update the categoriez belonging to a quiz with categorized random questions.
 *
 * Helper function for quiz_categorized_form_submit
 */
function _quiz_categorized_update_terms(&$form, &$form_state) {
  $ids = array('weight', 'max_score', 'number');
  $changed = array();
  $removed = array();
  $num_questions = 0;
  foreach ($form_state['values'] as $key => $existing) {
    if (!is_numeric($key)) {
      continue;
    }
    if (!$existing['remove']) {
      $num_questions += $existing['number'];
    }
    foreach ($ids as $id) {
      if ($existing[$id] != $form[$key][$id]['#default_value'] && !$existing['remove']) {
        $existing['nid'] = $form_state['values']['nid'];
        $existing['vid'] = $form_state['values']['vid'];
        $existing['tid'] = $key;
        $existing['weight'] = 1;
        $changed[] = $form[$key]['name']['#markup'];
        drupal_write_record('quiz_terms', $existing, array('vid', 'tid'));
        break;
      }
      elseif ($existing['remove']) {
        db_delete('quiz_terms')
          ->condition('tid', $key)
          ->condition('vid', $form_state['values']['vid'])
        ->execute();
        $removed[] = $form[$key]['name']['#markup'];
        break;
      }
    }
  }
  if (!empty($changed)) {
    drupal_set_message(t('Updates were made for the following terms: %terms', array('%terms' => implode(', ', $changed))));
  }
  if (!empty($removed)) {
    drupal_set_message(t('The following terms were removed: %terms', array('%terms' => implode(', ', $removed))));
  }
  return $num_questions;
}

/**
 * Adds a term to a categorized quiz
 *
 * This is a helper function for the submit function.
 */
function _quiz_categorized_add_term($form, $form_state) {
  drupal_set_message(t('The term was added'));
  // Needs to be set to avoid error-message from db:
  $form_state['values']['weight'] = 0;
  drupal_write_record('quiz_terms', $form_state['values']);
  return $form_state['values']['number'];
}

/**
 * Searches for an id in the end of a string.
 *
 * Id should be written like "(id:23)"
 *
 * @param string $string
 *  The string where we will search for an id
 * @return int
 *  The matched integer
 */
function _quiz_get_id_from_string($string) {
  $matches = array();
  preg_match('/\(id:(\d+)\)$/', $string, $matches);
  return isset($matches[1]) ? (int) $matches[1] : FALSE;
}

/**
 * Ahah function for finding terms...
 *
 * @param string $start
 *  The start of the string we are looking for
 */
function quiz_categorized_term_ahah($start) {
  $terms = _quiz_search_terms($start, $start == '*');
  $to_json = array();
  foreach ($terms as $key => $value) {
    $to_json["$value (id:$key)"] = $value;
  }
  drupal_json_output($to_json);
}

/**
 * Helper function for finding terms...
 *
 * @param string $start
 *  The start of the string we are looking for
 */
function _quiz_search_terms($start, $all = FALSE) {
  $terms = array();
  $sql_args = array_keys(_quiz_get_vocabularies());
  if (empty($sql_args)) {
    return $terms;
  }
  $query = db_select('taxonomy_term_data', 't')
    ->fields('t', array('name', 'tid'))
    ->condition('t.vid', $sql_args , 'IN');
  if (!$all) {
    $query->condition('t.name', '%' . $start . '%', 'LIKE');
  }
  $res = $query->execute();
  // TODO Don't user db_fetch_object
  while ($res_o = $res->fetch()) {
    $terms[$res_o->tid] = $res_o->name;
  }
  return $terms;
}

/**
 * Handles "manage questions" tab.
 *
 * Displays form which allows questions to be assigned to the given quiz.
 *
 * This function is not used if the question assignment type "categorized random questions" is chosen
 *
 * @param $form_state
 *  The form state variable
 * @param $quiz
 *  The quiz node.
 * @return
 *  HTML output to create page.
 */
function quiz_questions_form($form, $form_state, $quiz) {
  if ($form_state['rebuild']) {
    // Save the active filters in $_SESSION
    $filters = $form_state['values']['browser']['table']['header']['filters'];
    _quiz_questions_store_filters($filters);
  }

  $types = _quiz_get_question_types();

  _quiz_add_fields_for_creating_questions($form, $types, $quiz);

  // Display questions in this quiz.
  $form['question_list'] = array(
    '#type' => 'fieldset',
    '#title' => t('Questions in this quiz'),
    '#theme' => 'question_selection_table',
    '#collapsible' => TRUE,
    '#attributes' => array('id' => 'mq-fieldset'),
    'question_status' => array('#tree' => TRUE),
  );

  $form['#attached']['js'] = array(drupal_get_path('module', 'quiz') .'/theme/quiz_question_browser.js');

  // Add randomization settings if this quiz allows randomized questions
  _quiz_add_fields_for_random_quiz($form, $quiz);

  // Build up a list of questions
  $questions_to_add = array();

  // We use $form_state[post] to avoid validation failures when questions are added using AJAX
  if (isset($form_state['post']['weights'])) {
    $questions = _quiz_get_questions_from_form_state($form_state, $questions_to_add);
  }
  else {
    // We are coming in fresh and fetches the questions currently on the quiz from the database...
    $include_random = $quiz->randomization == 2;
    $questions = quiz_get_questions($quiz->nid, $quiz->vid, TRUE, FALSE, FALSE, $include_random);
  }

  if (empty($questions)) {
    $form['question_list']['no_questions'] = array(
      '#markup' => '<div id = "no-questions">' . t('There are currently no questions in this quiz. Assign existing questions by using the question browser below. You can also use the links above to create new questions.') . '</div>',
    );
  }

  // We add the browser and allows the browser to give us information on what questions are displayed in the browser...
  $hidden_questions = array();
  $form['question_list']['browser'] = _quiz_question_browser_form($hidden_questions, $questions_to_add, $form_state, $quiz, $types);
  // We add the questions from the browser as hidden question rows in the question list. Doing this we can have
  // the question show up in the question list instantly when a question is chosen in the browser(using js).
  _quiz_add_hidden_questions($questions, $hidden_questions, $form_state, $quiz);

  // We add the questions to the form array
  _quiz_add_questions_to_form($form, $questions, $quiz, $types);

  // Show the number of questions in the table header.
  $always_count = 0;
  foreach ($form['question_list']['stayers'] as $stayer) {
    if ($stayer['#default_value'] === 1) {
      $always_count++;
    }
  }
  $form['question_list']['#title'] .= ' (' . $always_count . ')';

  // Give the user the option to create a new revision of the quiz
  _quiz_add_revision_checkbox($form, $quiz);

  // Timestamp is needed to avoid multiple users editing the same quiz at the same time.
  $form['timestamp'] = array('#type' => 'hidden', '#default_value' => REQUEST_TIME);

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#submit' => array('quiz_questions_form_submit'),
  );
  return $form;
}

/**
 * Fields for creating new questions are added to the quiz_questions_form
 *
 * @param $form
 *   FAPI form(array)
 * @param $types
 *   All the question types(array)
 * @param $quiz
 *   The quiz node
 */
function _quiz_add_fields_for_creating_questions(&$form, &$types, &$quiz) {
  // Display links to create other questions.
  $form['additional_questions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Create new question'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $url_query = drupal_get_destination();
  $url_query['quiz_nid'] = $quiz->nid;
  $url_query['quiz_vid'] = $quiz->vid;
  foreach ($types as $type => $info) {
    $url_type = str_replace('_', '-', $type);
    $options = array(
      'attributes' => array('title' => t('Create @name', array('@name' => $info['name']))),
      'query' => $url_query,
    );
    $form['additional_questions'][$type] = array(
      '#markup' => '<div class="add-questions">' . l($info['name'], "node/add/$url_type", $options) . '</div>',
    );
  }
}

/**
 * Add fields for random quiz to the quiz_questions_form
 *
 * @param $form
 *   FAPI form array
 * @param $quiz
 *   The quiz node(object)
 */
function _quiz_add_fields_for_random_quiz(&$form, $quiz) {
  if ($quiz->randomization != 2) {
    return;
  }
  $form['question_list']['random_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Settings for random questions'),
    '#collapsible' => TRUE,
  );
  $form['question_list']['random_settings']['num_random_questions'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#weight' => -5,
    '#title' => t('Number of random questions'),
    '#description' => t('The number of questions to be randomly selected each time someone takes this quiz'),
    '#default_value' => isset($quiz->number_of_random_questions) ? $quiz->number_of_random_questions : 10,
  );
  $form['question_list']['random_settings']['max_score_for_random'] = array(
    '#type' => 'textfield',
    '#size' => 3,
    '#maxlength' => 3,
    '#weight' => -5,
    '#title' => t('Max score for each random question'),
    '#default_value' => isset($quiz->max_score_for_random) ? $quiz->max_score_for_random : 1,
  );
  if ($quiz->randomization == 3) {
    $terms =  _quiz_taxonomy_select($quiz->tid);
    if (!empty($terms) && function_exists('taxonomy_get_vocabularies')) {
      $form['question_list']['random_settings']['random_term_id'] = array(
        '#type' => 'select',
        '#title' => t('Terms'),
        '#size' => 1,
        '#options' => _quiz_taxonomy_select($quiz->tid),
        '#default_value' => $quiz->tid,
        '#description' => t('Randomly select from questions with this term, or choose from the question pool below'),
        '#weight' => -4,
      );
    }
  }
}


/**
 * Returns the questions that was in the question list when the form was submitted using ajax.
 *
 * @param $form_state
 *   FAPI form_state(array)
 * @return $questions
 *   Array of questions as objects
 */
function _quiz_get_questions_from_form_state(&$form_state, &$questions_to_add) {
  $questions = array();
  // We first store all data from the post in a temporary array.
  // Then we fetch more data for each question from the database.
  $cur_questions = array();
  $vids = array();
  foreach ($form_state['post']['weights'] as $id => $value) {
    $cur_question = new stdClass();

    // Find nid and vid
    $matches = array();
    preg_match('/([0-9]+)-([0-9]+)/', $id, $matches);
    $cur_question->nid = $matches[1];
    if (!is_numeric($matches[2])) {
      continue;
    }
    $vids[] = $cur_question->vid = $matches[2];
    $cur_question->max_score = intval($form_state['post']['max_scores'][$id]);
    $cur_question->auto_update_max_score = intval($form_state['post']['auto_update_max_scores'][$id]);
    $cur_question->weight = intval($value);
    $cur_question->staying = $form_state['post']['stayers'][$id] === '1';
    $cur_question->question_status = QUESTION_ALWAYS;
    if ($cur_question->staying == TRUE) {
      $questions_to_add[] = $id;
    }
    $cur_questions[$cur_question->nid] = $cur_question;
  }

  $query = db_select('node_revision', 'r');
  $table_alias = $query->join('node', 'n', 'n.nid = r.nid');
  $res = $query->addField('n', 'nid')
    ->addTag('node_access')
    ->addField('n', 'type')
    ->addField('n', 'vid', 'latest_vid')
    ->addField('r', 'title')
    ->condition('r.vid', $vids, 'IN')
  ->execute();
  // TODO: Don't use db_fetch_object
  while ($res_o = $res->fetch()) {
    $cur_questions[$res_o->nid]->type = $res_o->type;
    $cur_questions[$res_o->nid]->title = $res_o->title;
    $cur_questions[$res_o->nid]->latest_vid = $res_o->latest_vid;
    $questions[] = $cur_questions[$res_o->nid];
  }
  return $questions;
}

/**
 * Adds all information about the hidden questions to the questions array.
 *
 * Hidden questions are used to avoid unnecessary ajax calls.
 *
 * @see quiz_questions_form
 *
 * @param $questions
 *   The questions already added to the question list(array)
 * @param $hidden_questions
 *   The questions added to the browser(array)
 * @param $form_state
 *   FAPI form_state(array)
 * @param $quiz
 *   The quiz node
 */
function _quiz_add_hidden_questions(&$questions, &$hidden_questions, &$form_state, &$quiz) {
  $cur_questions = array();
  $vids = array();
  foreach ($hidden_questions as $key => $id) {
    $cur_question = new stdClass();
    $matches = array();

    // Find nid and vid
    preg_match('/([0-9]+)-([0-9]+)/', $id, $matches);
    $nid = $matches[1];
    $vid = $matches[2];

    // If a question already exists in the $questions array we won't add a new one...
    $continue = FALSE;
    foreach ($questions as $question) {
      if ($question->vid == $vid) {
        $continue = TRUE;
        break;
      }
    }
    if (!is_numeric($nid) || !is_numeric($vid) || $continue) {
      continue;
    }

    $cur_question->nid = $nid;
    $vids[] = $cur_question->vid = $vid;
    $cur_question->weight = 0;
    $cur_question->question_status = ($quiz->randomization == 2) ? QUESTION_RANDOM : QUESTION_ALWAYS;
    $cur_question->staying = isset($form_state['values']['stayers'][$id]) ? $form_state['values']['stayers'][$id] === '1' : FALSE;
    $cur_questions[$cur_question->nid] = $cur_question;
  }
  if (count($vids) > 0) {
    // We fetch the rest of the information for each question and adds node access security
    $res = db_select('node', 'n');
    $res->fields('n', array('nid', 'type'));
    $res->fields('r', array('title'));
    $res->fields('p', array('max_score'));
    $res->addField('n', 'vid', 'latest_vid');
    $res->join('node_revision', 'r', 'n.nid = r.nid');
    $res->join('quiz_question_properties', 'p', 'r.vid = p.vid');
    $res->condition('r.vid', $vids, 'in');

    // TODO: Don't user db_fetch_object
    foreach ($res->execute() as $res_o) {
      $cur_questions[$res_o->nid]->type = $res_o->type;
      $cur_questions[$res_o->nid]->title = $res_o->title;
      $cur_questions[$res_o->nid]->max_score = $res_o->type == 'scale' ? 0 : $res_o->max_score;
      $cur_questions[$res_o->nid]->latest_vid = $res_o->latest_vid;
      $questions[] = $cur_questions[$res_o->nid];
    }
  }
}

/**
 * Adds the questions in the $questions array to the form
 *
 * @param $form
 *   FAPI form(array)
 * @param $questions
 *   The questions to be added to the question list(array)
 * @param $quiz
 *   The quiz node(object)
 * @param $question_types
 *   array of all available question types
 */
function _quiz_add_questions_to_form(&$form, &$questions, &$quiz, &$question_types) {
  $form['question_list']['weights'] = array('#tree' => TRUE);
  $form['question_list']['max_scores'] = array('#tree' => TRUE);
  $form['question_list']['auto_update_max_scores'] = array('#tree' => TRUE);
  $form['question_list']['stayers'] = array('#tree' => TRUE);
  $form['question_list']['revision'] = array('#tree' => TRUE);
  if ($quiz->randomization == 2) {
    $form['question_list']['compulsories'] = array('#tree' => TRUE);
  }

  $my_dest = $_GET['q'];
  foreach ($questions as $question) {
    $fieldset = 'question_list';
    $id = $question->nid . '-' . $question->vid;

    $form[$fieldset]['weights'][$id] = array(
      '#type' => 'textfield',
      '#size' => 3,
      '#maxlength' => 4,
      '#default_value' => isset($question->weight) ? $question->weight : 0,
    );
    // Quiz directions don't have scoring...
    if ($question->type != 'quiz_directions') {
      $form[$fieldset]['max_scores'][$id] = array(
        '#type' => 'textfield',
        '#size' => 2,
        '#maxlength' => 2,
        '#disabled' => $question->auto_update_max_score,
        '#default_value' => isset($question->max_score) ? $question->max_score : 0,
      );
    }
    else {
      $form[$fieldset]['max_scores'][$id] = array(
        '#type' => 'value',
        '#value' => isset($question->max_score) ? $question->max_score : 0,
      );
    }
    
    $form[$fieldset]['auto_update_max_scores'][$id] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($question->auto_update_max_score) ? $question->auto_update_max_score : 0,
    );

    // Add checkboxes to remove questions in js disabled browsers...
    $form[$fieldset]['stayers'][$id] = array(
      '#type' => 'checkbox',
      '#default_value' => (isset($question->staying) && $question->staying === FALSE) ? 0 : 1,
      '#attributes' => array('class' => array('q-staying')),
    );

    //Add checkboxes to mark compulsory questions for randomized quizzes.
    if ($quiz->randomization == 2) {
      $form[$fieldset]['compulsories'][$id] = array(
        '#type' => 'checkbox',
        '#default_value' => isset($question->question_status) ? ($question->question_status == QUESTION_ALWAYS) ? 1 : 0 : 0,
        '#attributes' => array('class' => array('q-compulsory')),
      );
    }

    $link_options = array(
      'attributes' => array('class' => array('handle-changes')),
    );

    $form[$fieldset]['titles'][$id] = array('#markup' => l($question->title, 'node/' . $question->nid, $link_options));


    $form[$fieldset]['types'][$id] = array(
      '#markup' => $question_types[$question->type]['name'],
    );

    $form[$fieldset]['view_links'][$id] = array(
      '#markup' => l(
        t('Edit'),
        'node/' . $question->nid . '/edit',
        array(
          'query' => array('destination' => $my_dest),
          'attributes' => array('class' => array('handle-changes')),
        )
      ),
    );
    // For js enabled browsers questions are removed by pressing a remove link
    $form[$fieldset]['remove_links'][$id] = array(
      '#markup' => '<a href="#" class="rem-link">' . t('Remove') . '</a>',
    );
    // Add a checkbox to update to the latest revision of the question
    if ($question->vid == $question->latest_vid) {
      $update_cell = array(
        '#markup' => t('<em>Up to date</em>'),
      );
    }
    else {
      $update_cell = array(
      '#type' => 'checkbox',
      '#title' => (l(t('Latest'), 'node/' . $question->nid . '/revisions/' .$question->latest_vid . '/view')
                  . ' of ' .
                  l(t('revisions'), 'node/' . $question->nid . '/revisions')
                  ),
      );
    }
    $form[$fieldset]['revision'][$id] = $update_cell;
  }
}

/**
 * Adds checkbox for creating new revision. Checks it by default if answers exists.
 *
 * @param $form
 *   FAPI form(array)
 * @param $quiz
 *   Quiz node(object)
 */
function _quiz_add_revision_checkbox(&$form, &$quiz) {
  // Recomend and preselect to create the quiz as a new revision if it already has been answered
  if (quiz_has_been_answered($quiz)) {
    $rev_default = TRUE;
    $rev_description = t('This quiz has been answered. To maintain correctnes of existing answer reports changes should be saved as a new revision.');
  }
  else {
    $rev_default = in_array('revision', variable_get('node_options_quiz', array()));
    $rev_description = t('Allow question status changes to create a new revision of the quiz?');
  }
  if (user_access('manual quiz revisioning') && !variable_get('quiz_auto_revisioning', 1)) {
    $form['new_revision'] = array(
      '#type' => 'checkbox',
      '#default_value' => $rev_default,
      '#title' => t('New revision'),
      '#description' => $rev_description,
    );
  }
  else {
    $form['new_revision'] = array(
      '#type' => 'value',
      '#value' => $rev_default,
    );
  }
}

/**
 * Creates the browser part of the quiz_questions_form
 *
 * @param $hidden_questions
 *   Array where we add the questions in the browser
 * @param $questions
 *   Questions already added to the question list(array)
 * @param $form_state
 *   FAPI form_state(array)
 * @param $quiz
 *   Quiz node(object)
 * @return form
 *   FAPI form(array)
 */
function _quiz_question_browser_form(&$hidden_questions, $questions, $form_state, $quiz, $question_types) {
  if (!is_array($question_types) || count($question_types) == 0) {
    return $form['no_questions'] = array(
      '#markup' => t('No question types are enabled'),
    );
  }
  $form = array(
    '#type' => 'fieldset',
    '#title' => t('Browse for questions to add'),
    '#description' => t('Mark all the questions you want to add.') . ' '
    . t('You can filter questions by using the textfields and select boxes.') . ' '
    . t('You can sort by pressing the table headers.'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#tree' => TRUE,
    '#prefix' => '<div id="quiz-browser-target">',
    '#suffix' => '</div>',
  );
  $form['table'] = array('#theme' => 'quiz_browser');
  $browser = &$form['table'];

  // Ajax use this field to send extra query strings to drupal
  $browser['add_to_get'] = array(
    '#type' => 'hidden',
    '#default_value' => '',
  );

  $browser['header'] = array('#theme' => 'quiz_questions_browser_header');
  $browser['body'] = array('#theme' => 'quiz_questions_browser_body');

  //Build filter part of form:
  _quiz_question_browser_add_filter_fields($browser['header'], $question_types, $quiz);

  // Add querystring recieved via ajax to the $_GET array...
  if (isset($form_state['values'])) {
    _quiz_add_to_get($form_state['values']['browser']['table']['add_to_get']);
  }

  // Browsers table header
  $browser['header']['#header'] = array(
    NULL,
    array('data' => t('Title'), 'field' => 'n.title'),
    array('data' => t('Type'), 'field' => 'n.type'),
    array('data' => t('Changed'), 'field' => 'n.changed', 'sort' => 'desc'),
    array('data' => t('Username'), 'field' => 'u.name'),
  );

  $child_nid = db_query('SELECT child_nid FROM {quiz_node_relationship}
      WHERE parent_vid = :parent_vid',
      array(':parent_vid' => $quiz->vid)
    )
    ->fetchCol();

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
  $query->fields('n', array('nid', 'type', 'vid', 'title', 'changed'));
  $query->fields('u', array('name'));
  $query->leftJoin('users', 'u', 'n.uid = u.uid');
  $query->condition('type', array_keys($question_types), 'IN');
  if (count($child_nid)) {
    $query->condition('nid', $child_nid, 'NOT IN');
  }

  // Apply filter conditions
  // _quiz_question_browser_prepare_filter_sql($query);
  $pre = 'quiz_question_browser_';
  $changed_timestamps = _quiz_get_interval_timestamps('changed');
  $filter_sql = '';
  if (isset($_SESSION[$pre . 'title']) && !empty($_SESSION[$pre . 'title'])) {
    $query->condition('n.title', '%' . db_like($_SESSION[$pre . 'title']) . '%', 'LIKE');
  }

  if (isset($_SESSION[$pre . 'name']) && !empty($_SESSION[$pre . 'name'])) {
    $query->condition('u.name', '%' . db_like($_SESSION[$pre . 'name']) . '%', 'LIKE');
  }

  if (isset($_SESSION[$pre . 'type']) && ($_SESSION[$pre . 'type'] !== '0')) {
    $query->condition('type', array($_SESSION[$pre . 'type']), 'IN');
  }

  if (isset($_SESSION[$pre . 'changed'])) {
    $changed_timestamps = _quiz_get_interval_timestamps('changed');
    if ($changed_timestamps[$_SESSION[$pre . 'changed']][0]) {
      $query->condition('changed', $changed_timestamps[$_SESSION[$pre . 'changed']][0], '>');
    }
    if ($changed_timestamps[$_SESSION[$pre . 'changed']][1]) {
      $query->condition('changed', $changed_timestamps[$_SESSION[$pre . 'changed']][1], '<');
    }
  }
  $query->limit(10);
  $query->orderByHeader($browser['header']['#header']);
  $options = array();

  foreach ($query->execute() as $res_o) {
    $id = $res_o->nid . '-' . $res_o->vid;
    // Add $id to hidden_questions, this way quiz_questions_form knows that it has to add a invisible row for this question.
    $hidden_questions[] = $id;

    $options[$id] = check_plain($res_o->title);
    $browser['body']['changed'][$id]['#value'] = format_date($res_o->changed, 'short');
    $browser['body']['types'][$id]['#value'] = $question_types[$res_o->type]['name'];
    $browser['body']['names'][$id]['#value'] = check_plain($res_o->name);
  }

  $browser['body']['titles'] = array(
    '#title' => t('Titles'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#attributes' => array('class' => array('quiz-browser-checkbox')),
    '#default_value' => $questions,
  );

  $browser['pager'] = array(
    '#markup' => '<div id="browser-pager">' . theme('pager', array('tags' => NULL)) . '</div>',
  );
  return $form;
}


/**
 * adds filter fields to the question browser form
 *
 * @param $browser
 *   FAPI form(array)
 * @param $question_types
 *   Array of question types
 */
function _quiz_question_browser_add_filter_fields(&$browser, &$question_types, $quiz) {
  // Create options array for the type filter(select field)
  $type_options = array(t('No filter'));
  foreach (array_keys($question_types) as $type) {
    $type_options[$type] = $question_types[$type]['name'];
  }

  // Create options array for the changed filter
  $changed_options = _quiz_get_time_interval_options();

  // Create the filter form items
  $browser['filters'] = array();
  $filters = &$browser['filters'];

  $filters['all'] = array(
    '#type' => 'checkbox',
  );

  $pre = 'quiz_question_browser_';

  $filters['title'] = array(
    '#type' => 'textfield',
    '#size' => 20,
    '#default_value' => isset($_SESSION[$pre . 'title']) ? $_SESSION[$pre . 'title'] : '',
    '#ajax' => array(
      'callback' => 'quiz_questions_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
      'event' => 'doneTyping', // custom event
    ),
  );
  $filters['type'] = array(
    '#type' => 'select',
    '#options' => $type_options,
    '#default_value' => isset($_SESSION[$pre . 'type']) ? $_SESSION[$pre . 'type'] : '',
    '#ajax' => array(
      'callback' => 'quiz_questions_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
  $filters['changed'] = array(
    '#type' => 'select',
    '#options' => $changed_options,
    '#default_value' => isset($_SESSION[$pre . 'changed']) ? $_SESSION[$pre . 'changed'] : '',
    '#ajax' => array(
      'callback' => 'quiz_questions_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
  $filters['name'] = array(
    '#type' => 'textfield',
    '#size' => 10,
    '#default_value' => isset($_SESSION[$pre . 'name']) ? $_SESSION[$pre . 'name'] : '',
    '#ajax' => array(
      'callback' => 'quiz_questions_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
      'event' => 'doneTyping', // custom event
    ),
  );
}

/**
 * Returns sql to be added in where clause in the browsers select statement
 *
 * @see _quiz_questions_browser_form()
 *
 * @param $filter_params
 *   params to be sent as parameter to db_query. (array)
 * @return $filter_sql
 *   sql to be added to where statement in browser(string)
 */
function _quiz_question_browser_prepare_filter_sql(&$filter_params) {
  $pre = 'quiz_question_browser_';
  $changed_timestamps = _quiz_get_interval_timestamps('changed');
  $filter_sql = '';
  if (isset($_SESSION[$pre .'title']) && drupal_strlen($_SESSION[$pre .'title']) > 0) {
    $filter_sql .= ' AND n.title LIKE \'%s%%\'';
    $filter_params[] = $_SESSION[$pre . 'title'];
  }
  if (isset($_SESSION[$pre .'name']) && drupal_strlen($_SESSION[$pre .'name']) > 0) {
    $filter_sql .= ' AND u.name LIKE \'%s%%\'';
    $filter_params[] = $_SESSION[$pre . 'name'];
  }
  if (isset($_SESSION[$pre . 'type']) && ($_SESSION[$pre . 'type'] !== '0')) {
    $filter_sql .= ' AND n.type = \'%s\'';
    $filter_params[] = $_SESSION[$pre . 'type'];
  }
  if (isset($_SESSION[$pre . 'changed'])) {
    $filter_sql .= $changed_timestamps[$_SESSION[$pre . 'changed']]['sql'];
  }
  return $filter_sql;
}

/**
 * Validate that the supplied questions are real.
 */
function quiz_questions_form_validate($form, $form_state) {
  if (_quiz_is_int(arg(1))) {
    if (node_last_changed(intval(arg(1))) > $form_state['values']['timestamp']) {
      form_set_error('changed', t('This content has been modified by another user, changes cannot be saved.'));
    }
  }
  else {
    form_set_error('changed', t('A critical error has occured. Please report error code 28 on the quiz project page.'));
    return;
  }

  $already_checked = array();
  $weight_map = $form_state['values']['weights'];

  // Make sure the number of random questions is a positive number
  if (isset($form_state['values']['num_random_questions']) && !_quiz_is_int($form_state['values']['num_random_questions'], 0)) {
    form_set_error('num_random_questions', 'The number of random questions needs to be a positive number');
  }

  // Make sure the max score for random questions is a positive number
  if (isset($form_state['values']['max_score_for_random']) && !_quiz_is_int($form_state['values']['max_score_for_random'], 0)) {
    form_set_error('max_score_for_random', 'The max score for random questions needs to be a positive number');
  }

  if (empty($weight_map)) {
    form_set_error('none', 'No questions were included.');
    return;
  }

  $question_types = array_keys(_quiz_get_question_types());

  foreach ($weight_map as $id => $weight) {
    if ($form_state['values']['stayers'][$id] == 0) {
      continue;
    } // The question isn't to be added...

    list($nid, $vid) = explode('-', $id, 2);

    // If a node isn't one of the questionstypes we remove it from the question list
    $has_questions = (Boolean) db_select('node', 'n')
      ->fields('n', array('nid'))
      ->condition('type', $question_types, 'IN')
      ->addTag('node_access')
      ->condition('n.nid', $nid)
      ->execute()
      ->fetchField();
    if (!$has_questions) {
      form_set_error('none', 'One of the supplied questions was invalid. It has been removed from the quiz.');
      unset($form_state['values']['weights'][$id]);
    }

    // We also make sure that we don't have duplicate questions in the quiz.
    elseif (in_array($nid, $already_checked)) {
      form_set_error('none', 'A duplicate question has been removed. You can only ask a question once per quiz.');
      unset($form_state['values']['weights'][$id]);
    }
    else {
      $already_checked[] = $nid;
    }
  }

  // We make sure max score is a positive number
  $max_scores = $form_state['values']['max_scores'];
  foreach ($max_scores as $id => $max_score) {
    if ($form_state['values']['stayers'][$id] == 0) {
      continue;
    }
    if (!_quiz_is_int($max_score, 0)) {
      form_set_error("max_scores][$id", t('Max score needs to be a positive number'));
    }
  }
}

/**
 * Update a quiz set of items with new weights and membership
 * @param $quiz
 *   The quiz node
 * @param $weight_map
 *   Weights for each question(determines the order in which the question will be taken by the quiz taker)
 * @param $max_scores
 *   Array of max scores for each question
 * @param $is_new_revision
 *   Array of boolean values determining if the question is to be updated to the newest revision
 * @param $refreshes
 *   True if we are creating a new revision of the quiz
 * @param $stayers
 *   Questions added to the quiz
 * @param $compulsories
 *   Array of boolean values determining if the question is compulsory or not.
 * @return array set of questions after updating
 */
function _quiz_update_items($quiz, $weight_map, $max_scores, $auto_update_max_scores, $is_new_revision, $refreshes, $stayers, $compulsories = NULL) {
  $questions = array();
  foreach ($weight_map as $id => $weight) {
    // Do not add hidden questions to $questions
    if ($stayers[$id] == 0) {
      continue;
    }
    list($nid, $vid) = explode('-', $id, 2);
    $nid = (int) $nid;
    $vid = (int) $vid;
    $question = new stdClass();
    $question->nid = $nid;
    $question->vid = $vid;
    if (isset($compulsories)) {
      if ($compulsories[$id] == 1) {
        $question->state = QUESTION_ALWAYS;
      }
      else {
        $question->state = QUESTION_RANDOM;
        $max_scores[$id] = $quiz->max_score_for_random;
      }
    }
    else {
      $question->state = QUESTION_ALWAYS;
    }     
    $question->weight = $weight;
    $question->max_score = $max_scores[$id];
    $question->auto_update_max_score = $auto_update_max_scores[$id];
    $question->refresh = (isset($refreshes[$id]) && $refreshes[$id] == 1);

    // Add item as an object in the questions array.
    $questions[] = $question;
  }

  // Save questions.
  quiz_set_questions($quiz, $questions, $is_new_revision);

  return $questions;
}

/**
 * Submit function for quiz_questions.
 *
 * Updates from the "manage questions" tab.
 */
function quiz_questions_form_submit($form, &$form_state) {
  if (isset($form_state['#from_ahah'])) {
    return;
  }

  // Load the quiz node
  $quiz = node_load(intval(arg(1)));
  // Update the refresh latest quizzes table so that we know what the users latest quizzes are
  if (variable_get('quiz_auto_revisioning', 1)) {
    $is_new_revision = quiz_has_been_answered($quiz);
  }
  else {
    $is_new_revision = (bool) $form_state['values']['new_revision'];
  }

  _quiz_question_browser_submit($form, $form_state);

  $weight_map = $form_state['values']['weights'];
  $max_scores = $form_state['values']['max_scores'];
  $auto_update_max_scores = $form_state['values']['auto_update_max_scores'];
  $refreshes = isset($form_state['values']['revision']) ? $form_state['values']['revision'] : NULL;
  $stayers = $form_state['values']['stayers'];
  $compulsories = isset($form_state['values']['compulsories']) ? $form_state['values']['compulsories'] : NULL;

  $num_random = isset($form_state['values']['num_random_questions']) ? $form_state['values']['num_random_questions'] : 0;


  $quiz->max_score_for_random = isset($form_state['values']['max_score_for_random']) ? $form_state['values']['max_score_for_random'] : 1;
  $term_id = isset($form_state['values']['random_term_id']) ? (int) $form_state['values']['random_term_id'] : 0;


  // Store what questions belong to the quiz
  $questions = _quiz_update_items($quiz, $weight_map, $max_scores, $auto_update_max_scores, $is_new_revision, $refreshes, $stayers, $compulsories);

  // If using random questions and no term ID is specified, make sure we have enough.
  if (empty($term_id)) {
    $assigned_random = 0;

    foreach ($questions as $question) {
      if ($question->state == QUESTION_RANDOM) {
        ++$assigned_random;
      }
    }

    // Adjust number of random questions downward to match number of selected questions..
    if ($num_random > $assigned_random) {
      $num_random = $assigned_random;
      drupal_set_message(t('The number of random questions for this @quiz have been lowered to %anum to match the number of questions you assigned.', array('@quiz' => QUIZ_NAME, '%anum' => $assigned_random), array('langcode' => 'warning')));
    }
  }
  else {
    // Warn user if not enough questions available with this term_id.
    $available_random = count(_quiz_get_random_taxonomy_question_ids($term_id, $num_random));
    if ($num_random > $available_random) {
      $num_random = $available_random;
      drupal_set_message(t('There are currently not enough questions assigned to this term (@random). Please lower the number of random quetions or assign more questions to this taxonomy term before taking this @quiz.', array('@random' => $available_random, '@quiz' => QUIZ_NAME)), 'error');
    }
  }

  if ($quiz->type == 'quiz') {
    // Update the quiz node properties.
    $success = db_update('quiz_node_properties')
      ->fields(array(
        'number_of_random_questions' => $num_random ? $num_random : 0,
        'max_score_for_random' => $quiz->max_score_for_random,
        'tid' => $term_id,
      ))
      ->condition('vid', $quiz->vid)
      ->condition('nid', $quiz->nid)
      ->execute();

    // Get sum of max_score
    $query = db_select('quiz_node_relationship', 'qnr');
    $query->addExpression('SUM(max_score)', 'sum');
    $query->condition('parent_vid', $quiz->vid);
    $query->condition('question_status', QUESTION_ALWAYS);
    $score = $query->execute()->fetchAssoc();

    $success2 = db_update('quiz_node_properties')
      ->expression('max_score', 'max_score_for_random * number_of_random_questions + :sum', array(':sum' => (int) $score['sum']))
      ->condition('vid', $quiz->vid)
      ->execute();
  }

  if (isset($success) && isset($success2)) {
    drupal_set_message(t('Questions updated successfully.'));
  }
  else {
    drupal_set_message(t('There was an error updating the @quiz.', array('@quiz' => QUIZ_NAME)), 'error');
  }
}

/**
 * Takes care of the browser part of the submitted form values.
 *
 * This function changes the form_state to reflect questions added via the browser.
 * (Especially if js is disabled)
 *
 *
 * @param $form
 *   FAPI form(array)
 * @param $form_state
 *   FAPI form_state(array)
 */
function _quiz_question_browser_submit($form, &$form_state) {
  // Find the biggest weight:
  $next_weight = max($form_state['values']['weights']);

  // If a question is chosen in the browser, add it to the question list if it isn't already there
  if (isset($form_state['values']['browser']['table']['titles'])) {
    foreach ($form_state['values']['browser']['table']['titles'] as $id) {
      if ($id !== 0) {
        if ($form_state['values']['stayers'][$id] == 1) {
          continue;
        }
        $matches = array();
        preg_match('/([0-9]+)-([0-9]+)/', $id, $matches);
        $nid = $matches[1];
        $vid = $matches[2];
        $form_state['values']['weights'][$id] = ++$next_weight;
        $form_state['values']['max_scores'][$id] = quiz_question_get_max_score($nid, $vid);
        $form_state['values']['stayers'][$id] = 1;
      }
    }
  }
}

/**
 * Store values for each browser filter in $_SESSION
 *
 * @param $filters
 *   array holding the values for each filter
 */
function _quiz_questions_store_filters($filters) {
  $pre = 'quiz_question_browser_';
  $_SESSION[$pre . 'title'] = trim($filters['title']);
  $_SESSION[$pre . 'type'] = $filters['type'];
  $_SESSION[$pre . 'changed'] = $filters['changed'];
  $_SESSION[$pre . 'name'] = trim($filters['name']);
}

// THEME FUNCTIONS

/**
 * Theme the admin quizzes table.
 *
 * @param $results
 *  As returned by _quiz_get_quizzes().
 *
 * @ingroup themeable
 */
function theme_quiz_admin_quizzes($variables) {
  $results = $variables['results'];
  $output = '';

  // The export images
  $path_to_module_quiz = drupal_get_path('module', 'quiz');
  $png = array(
    'html' => theme('image', array('path' => $path_to_module_quiz . '/images/html.png', 'width' => t('Export as HTML'), 'height' => t('Export as HTML'))),
    'xml' => theme('image', array('path' => $path_to_module_quiz . '/images/xml.png', 'width' => t('Export as XML'), 'height' => t('Export as XML'))),
    'csv' => theme('image', array('path' => $path_to_module_quiz . '/images/csv.png', 'width' => t('Export as CSV'), 'height' => t('Export as CSV'))),
    'csv_full' => theme('image', array('path' => $path_to_module_quiz . '/images/csv_complete.png', 'width' => t('Export full data as CSV'), 'height' => t('Export full data as CSV'))),
  );
  $rows = array();

  $exp = module_exists('results_export');

  while (list($key, $result) = each($results)) {
    $cols = array(
      l($result['title'], 'node/' . $result['nid'] . '/results'),
      check_plain($result['name']),
      format_date($result['created'], 'short'),
    );
    // Add export links if the results export module is enabled
    if ($exp) {
      $cols[] = l($png['html'], 'admin/quiz/results_export_teaser_view/' . $result['nid'] . '/html', array('html' => TRUE))
              . l($png['xml'], 'admin/quiz/results_export_teaser_view/' . $result['nid'] . '/xml', array('html' => TRUE))
              . l($png['csv'], 'admin/quiz/results_export_teaser_view/' . $result['nid'] . '/csv', array('html' => TRUE))
              . l($png['csv_full'], 'admin/quiz/results_export_full_view/' . $result['nid'] . '/csv', array('html' => TRUE));
    }
    $rows[] = $cols;
  }

  $header = array(
    t('@quiz title', array('@quiz' => QUIZ_NAME)),
    t('Created by'),
    t('Created on')
  );
  if ($exp) {
    $header[] = t('Export');
  }
  // Message if there are no quizzes available
  if (!user_access('view any quiz results')) {
    $no_quizzes = '<p>' . t('No @quiz that you have created was found. You do not have permission to see any other results.', array('@quiz' => QUIZ_NAME)) . '</p>';
  }
  else {
    $no_quizzes = '<p>' . t('No @quiz found.', array('@quiz' => QUIZ_NAME)) . '</p>';
  }
  $output = (!empty($rows)) ? theme('table', array('header' => $header, 'rows' => $rows)) : $no_quizzes;
  return $output;
}

/**
 * Theme the quiz node form
 *
 * Adds js to enhance the ux.
 *
 * @param $form
 *   FAPI form array
 */
function theme_quiz_node_form($variables) {
  $form = $variables['form'];
  $path = drupal_get_path('module', 'quiz') . '/theme/quiz_node_form.js';
  drupal_add_js($path);
  return theme('node_form', array('form' => $form));
}

/**
 * Theme the summary page for admins.
 *
 * @param $quiz
 *  The quiz node object.
 * @param $questions
 *  The questions array as defined by _quiz_get_answers.
 * @param $score
 *  Array of score information as returned by quiz_calculate_score().
 * @param $summary
 *  Filtered text of the summary.
 * @return
 *  Themed html.
 *
 * @ingroup themeable
 */
function theme_quiz_admin_summary($variables) {
  $quiz = $variables['quiz'];
  $questions = $variables['questions'];
  $score = $variables['score'];
  $summary = $variables['summary'];
  $rid = $variables['rid'];
  // To adjust the title uncomment and edit the line below:
  // drupal_set_title(check_plain($quiz->title));
  if (!$score['is_evaluated']) {
    drupal_set_message(t('This quiz has not been scored yet.'), 'warning');
  }
  // Display overall result.
  $output = '';
  $params = array('%num_correct' => $score['numeric_score'], '%question_count' => $score['possible_score']);
  $output .= '<div id="quiz_score_possible">' . t('This person got %num_correct of %question_count possible points.', $params) . '</div>' . "\n";
  $output .= '<div id="quiz_score_percent">' . t('Total score: @score %', array('@score' => $score['percentage_score'])) . '</div>' . "\n";
  if (isset($summary['passfail'])) {
    $output .= '<div id="quiz_summary">' . check_markup($summary['passfail'], $quiz->body['und'][0]['format']) . '</div>' . "\n";
  }
  if (isset($summary['result'])) {
    $output .= '<div id="quiz_summary">' . check_markup($summary['result'], $quiz->body['und'][0]['format']) . '</div>' . "\n";
  }

  // Get the feedback for all questions.
  require_once DRUPAL_ROOT . '/' . drupal_get_path('module', 'quiz') . '/quiz.pages.inc';
  $report_form = drupal_get_form('quiz_report_form', $questions, TRUE, TRUE, TRUE);
  $output .= drupal_render($report_form);
  return $output;
}

/**
 * Theme a question selection table, adding drag and drop support.
 */
function theme_question_selection_table($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('question-list', 'order', 'sibling', 'question-list-weight', NULL, NULL, TRUE);

  // Building headers
  $headers = array(t('Question'), t('Type'), t('Actions'), t('Update'), t('Max score'), t('Auto update max score'));
  if (isset($form['compulsories'])) {
    $headers[] = t('Compulsory');
  }
  $headers[] = t('Weight');

  // Building table body
  $rows = array();
  if (!empty($form['titles'])) {
    foreach (element_children($form['titles']) as $id) {
      $form['weights'][$id]['#attributes']['class'] = array('question-list-weight');

      $rows[] = _quiz_get_question_row($form, $id);
    }
    // Make sure the same fields aren't rendered twice
    unset($form['types'], $form['view_links'], $form['remove_links'], $form['stayers']);
    unset($form['max_scores'], $form['auto_update_max_scores'], $form['revision'], $form['weights'], $form['titles'], $form['compulsories']);
  }
  $html_attr = array('id' => 'question-list');

  // We hide the table if no questions have been added so that jQuery can show it the moment the first question is beeing added.
  if (isset($form['no_questions'])) {
    $html_attr['style'] = "display:none;";
  }

  $table = theme('table', array('header' => $headers, 'rows' => $rows, 'attributes' => $html_attr));

  return drupal_render($form['random_settings'])
       . $table
       . drupal_render_children($form);
}

// RESULT MANAGEMENT

/**
 * Form for searching after and manipulating results for a quiz
 *
 * @param $form_state
 *   FAPI form_state
 * @param $quiz
 *   The quiz node
 * @return
 *   FAPI-array
 */
function quiz_results_manage_results_form($form, &$form_state, $quiz) {
  if ($form_state['rebuild']) {
    // We remember the filters for the next time the same user visits the result browser
    _quiz_results_mr_store_filters($form_state);
  }
  $form = array();
  $pre = 'quiz_results_mr_';

  $form['#attached']['js'] = array(drupal_get_path('module', 'quiz') .'/theme/quiz_results_browser.js');
  /* not_in_progress is a filter to filter away questions that are in progress...
   By default we don't want to show questions in progress... */
  if (!isset($_SESSION[$pre . 'not_in_progress'])) {
    $_SESSION[$pre . 'not_in_progress'] = 1;
  }

  // We hide the update fieldset if we are to delete results
  $display = isset($_GET['del']) || isset($form_state['storage']['del']) ? 'none' : 'block';
  $form['update'] = array(
    '#type' => 'fieldset',
    '#title' => t('Options'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array(
      'class' => array('container-inline'),
      'id' => 'quiz-results-update',
      'style' => "display:$display;"
    ),
  );

  $form['update']['bulk_action'] = array(
    '#type' => 'select',
    '#options' => array(
      'def' => '',
      'del' => t('delete'),
      // In later versions we will be adding score as a third option here
    ),
  );
  $form['update']['update'] = array(
    '#type' => 'submit',
    '#value' => t('Update'),
  );

  // We show the delete confirmation fieldset if we are to delete results
  $display = isset($_GET['del']) || isset($form_state['storage']['del']) ? 'block' : 'none';
  $form['confirm_delete'] = array(
    '#type' => 'fieldset',
    '#title' => t('Confirm deletion'),
    '#collapsible' => FALSE,
    '#collapsed' => FALSE,
    '#attributes' => array(
      'style' => "display:$display;",
      'id' => 'quiz-results-confirm-delete'
    ),
  );
  $form['confirm_delete']['help'] = array(
    '#type' => 'item',
    '#value' => t('Are you sure you want to delete all of these results?'),
    '#description' => t('This action cannot be undone'),
  );
  $form['confirm_delete']['confirm_delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete all marked results'),
  );
  $form['confirm_delete']['cancel'] = array(
    '#markup' => l(t('cancel'), $_GET['q'], array('attributes' => array('id' => 'quiz-results-cancel-delete'))),
  );

  $form['special_filters'] = array(
    '#type' => 'fieldset',
    '#title' => t('Special filters'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  if (!isset($_SESSION[$pre . 'best_results'])) {
    $_SESSION[$pre . 'best_results'] = 1;
  }
  $form['special_filters']['best_results'] = array(
    '#type' => 'checkbox',
    '#title' => t('Only show each users best result'),
    '#parents' => array('table', 'header', 'filters', 'best_results'),
    '#default_value' => $_SESSION[$pre . 'best_results'],
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );

  if (!isset($_SESSION[$pre . 'not_in_progress'])) {
    $_SESSION[$pre . 'not_in_progress'] = 1;
  }
  $form['special_filters']['not_in_progress'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not show quizzes in progress'),
    '#parents' => array('table', 'header', 'filters', 'not_in_progress'),
    '#default_value' => $_SESSION[$pre . 'not_in_progress'],
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );

  $form['table'] = array('#theme' => 'quiz_browser', '#tree' => TRUE);
  $browser = &$form['table'];

  // js use this field to send extra query strings to drupal(sorting, paging etc)
  $browser['add_to_get'] = array(
    '#type' => 'hidden',
    '#default_value' => '',
  );

  // Build filter part of form:
  $browser['header'] = array('#theme' => 'quiz_results_browser_header');

  // Browsers table header
  $browser['header']['#header'] = array(
    array('data' => t('Username'), 'field' => 'u.uid'),
    array('data' => t('Started'), 'field' => 'started'),
    array('data' => t('Finished'), 'field' => 'finished'),
    array('data' => t('Score'), 'field' => 'score'),
    array('data' => t('Evaluated'), 'field' => 'evaluated'),
  );

  _quiz_results_mr_add_filter_fields($browser['header'], $quiz);

  // Add querystring recieved via ajax to the $_GET array...
  if (isset($form_state['values'])) {
    _quiz_add_to_get($form_state['values']['table']['add_to_get']);
  }

  $browser['body'] = array('#theme' => 'quiz_results_browser_body');

  $res = _quiz_results_mr_data_provider($browser['header']['#header'], $quiz);

  // build data part of form
  $options = array();
  //while ($res_o = db_fetch_object($res)) {
  foreach ($res as $res_o) {
    $id = $quiz->nid . '-' . $res_o->result_id;

    // build options array for checkboxes for item
    if (empty($res_o->name)) {
      if ($res_o->uid == '0') {
        $options[$id] = variable_get('anonymous', t('Anonymous'));
      }
      else {
        $options[$id] = t('ORPHAN %uid', array('%uid' => '#' . $res_o->uid));
      }
    }
    else {
      $options[$id] = check_plain($res_o->name);
    }

    // Build hover menu for users who want to act on a single result
    $browser['body']['hover_menu'][$id]['#value'] = _quiz_results_mr_get_hover($quiz, $res_o->result_id);

    // Add data for the table columns
    $browser['body']['started'][$id]['#value'] = format_date($res_o->started, 'short');
    $browser['body']['finished'][$id]['#value'] = $res_o->finished == 0 ? t('In progress') : format_date($res_o->finished, 'short');
    $browser['body']['duration'][$id]['#value'] = $res_o->finished == 0 ? t('In progress') : _quiz_format_duration($res_o->duration);
    $browser['body']['score'][$id]['#value'] = $res_o->finished == 0 ? t('In progress') : check_plain($res_o->score);
    $browser['body']['evaluated'][$id]['#value'] = $res_o->evaluated == 0 ? t('No') : t('Yes');
    $browser['body']['pass_rate'][$id]['#value'] = $res_o->pass_rate;
  }

  // We copy the checkboxes that have been chosen in the previous stage, and unset them to avoid having them loaded again.
  $default_value = isset($form_state['storage']['del']) ? $form_state['storage']['del'] : array($quiz->nid . '-' . (isset($_GET['del']) ? $_GET['del'] : ''));
  unset($form_state['storage']['del']);

  $browser['body']['name'] = array(
    '#title' => t('Name'),
    '#type' => 'checkboxes',
    '#options' => $options,
    '#attributes' => array('class' => array('quiz-browser-checkbox')),
    '#default_value' => $default_value,
  );

  $form['pager'] = array(
    '#markup' => '<DIV ID ="browser-pager">' . theme('pager', array('tags' => NULL)) . '</DIV>',
  );
  $form['#submit'][] = 'quiz_results_mr_form_submit';

  return $form;
}

/**
 *
 * @param $header
 *   header array for theme_table
 * @param $quiz
 *   The quiz node
 * @return
 *   Query result set
 */
function _quiz_results_mr_data_provider($header, $quiz) {
  $filter = _quiz_results_mr_prepare_filter($quiz);
  $sql = "SELECT u.name, qnrs.uid, qnrs.result_id, qnrs.score, qnrs.is_evaluated AS evaluated, qnrs.time_start as started, qnrs.time_end as finished, qnp.pass_rate, qnrs.time_end - qnrs.time_start as duration
          FROM {quiz_node_results} qnrs
          LEFT JOIN {users} u ON u.uid = qnrs.uid
          LEFT JOIN {quiz_node_properties} qnp ON qnrs.vid = qnp.vid
          " . $filter['join'] . "
          WHERE qnrs.nid = :quiz_nid " . $filter['where'] . $filter['group'];// . tablesort_sql($header) . ', qnrs.result_id DESC';
  //echo $sql;exit;
  return db_query($sql, $filter['params']);
  /*
  // We remove the links to the last page and use a custom query to fetch the number of pages
  // Doing this we wastly improve performance
  $page = isset($_GET['page']) ? intval($_GET['page']) : 0;
  $num = 50;
  $pager_sql = "SELECT COUNT(*) FROM (
                SELECT qnrs.result_id
                FROM {quiz_node_results} qnrs
                LEFT JOIN {users} u ON u.uid = qnrs.uid
                LEFT JOIN {quiz_node_properties} qnp ON qnrs.vid = qnp.vid
                " . $filter['join'] . "
                WHERE  qnrs.nid = %d " . $filter['where'] . $filter['group'] . ' LIMIT 0, ' . max($page * $num + $num * 7, $num * 10) . ") tbl";

  return pager_query($sql, $num, 0, $pager_sql, $filter['params']);
  */
}

/**
 * Returns sql and parameters to be added in join, where and group clauses in the
 * _quiz_results_mr_data_provider select statement
 *
 * TODO: Rewrite to use db_select
 *
 * @see _quiz_results_mr_data_provider()
 *
 * @param $filter_params
 *   params to be sent as parameter to db_query. (array)
 * @return $filter_sql
 *   sql to be added to where statement in browser(string)
 */
function _quiz_results_mr_prepare_filter($quiz) {
  $pre = 'quiz_results_mr_';

  // Get all the intervals we need
  $started_intervals = _quiz_get_interval_timestamps('time_start');
  $finished_intervals = _quiz_get_interval_timestamps('time_end');
  $duration_intervals = _quiz_get_duration_intervals();
  $score_intervals = _quiz_get_score_intervals($quiz);

  // Prepare the filter array
  $filter = array(
    'params' => array(':quiz_nid' => $quiz->nid),
    'join' => '',
    'where' => '',
    'group' => '',
  );
  if (isset($_SESSION[$pre . 'name']) && drupal_strlen($_SESSION[$pre . 'name']) > 0) {
    $filter['where'] .= ' AND u.name LIKE :name';
    $filter['params'][':name'] = '%' . $_SESSION[$pre . 'name'] . '%';
  }
  if (isset($_SESSION[$pre . 'started']) && isset($started_intervals[$_SESSION[$pre . 'started']]['sql'])) {
    $filter['where'] .= $started_intervals[$_SESSION[$pre . 'started']]['sql'];
  }
  if (isset($_SESSION[$pre . 'finished']) && isset($finished_intervals[$_SESSION[$pre . 'finished']]['sql'])) {
    $filter['where'] .= $finished_intervals[$_SESSION[$pre . 'finished']]['sql'];
  }
  if (isset($_SESSION[$pre . 'score']) && isset($score_intervals[$_SESSION[$pre . 'score']])) {
    $filter['where'] .= $score_intervals[$_SESSION[$pre . 'score']];
  }
  if (isset($_SESSION[$pre . 'evaluated'])) {
    switch ($_SESSION[$pre . 'evaluated']) {
      case '0':
        $filter['where'] .= ' AND is_evaluated = 0';
        break;
      case '1':
        $filter['where'] .= ' AND is_evaluated = 1';
        break;
    }
  }
  if ($_SESSION[$pre . 'not_in_progress'] == 1) {
    $filter['where'] .= " AND time_end <> 0";
  }
  if ($_SESSION[$pre . 'best_results'] == 1) {
    $filter['join'] .= " INNER JOIN (
                           SELECT qnrs.uid, MAX(qnrs.score) AS top_score
                           FROM {quiz_node_results} qnrs
                           LEFT JOIN {users} u ON u.uid = qnrs.uid
                           LEFT JOIN {quiz_node_properties} qnp ON qnrs.vid = qnp.vid
                           WHERE qnrs.nid = :quiz_nid " . $filter['where'] . "
                           GROUP BY qnrs.uid
                         ) AS qnrc ON qnrs.uid = qnrc.uid AND qnrs.score = qnrc.top_score";
    $filter['group'] .= " GROUP BY qnrs.uid";
    if (db_driver() == 'pgsql') {
      $filter['group'] .= " GROUP BY qnrs.uid, u.uid, u.name, qnrs.result_id, qnrs.score, qnrs.is_evaluated, qnrs.time_start, qnrs.time_end, qnp.pass_rate";
    }
  }
  return $filter;
}

/**
 * Adds form items for the filters to the browser form.
 *
 * @param $browser
 *   FAPI form array
 */
function _quiz_results_mr_add_filter_fields(&$browser, $quiz) {
  // Create options array for the changed filter
  $browser['filters'] = array();
  $filters = &$browser['filters'];
  $filters['all'] = array(
    '#type' => 'checkbox',
  );

  $pre = 'quiz_results_mr_';
  $filters['name'] = array(
    '#type' => 'textfield',
    '#size' => 12,
    '#default_value' => isset($_SESSION[$pre . 'name']) ? $_SESSION[$pre . 'name'] : '',
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
      'event' => 'doneTyping', // custom event
    ),
  );
  $filters['started'] = array(
    '#type' => 'select',
    '#options' => _quiz_get_time_interval_options(),
    '#default_value' => isset($_SESSION[$pre . 'started']) ? $_SESSION[$pre . 'started'] : '',
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
  $filters['finished'] = array(
    '#type' => 'select',
    '#options' => _quiz_get_time_interval_options(),
    '#default_value' => isset($_SESSION[$pre . 'finished']) ? $_SESSION[$pre . 'finished'] : '',
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
  $filters['score'] = array(
    '#type' => 'select',
    '#options' => _quiz_get_score_options(),
    '#default_value' => isset($_SESSION[$pre . 'score']) ? $_SESSION[$pre . 'score'] : '',
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
  $filters['evaluated'] = array(
    '#type' => 'select',
    '#options' => array('def' => t('No filter'), '1' => t('Yes'), '0' => t('No')),
    '#default_value' => isset($_SESSION[$pre . 'evaluated']) ? $_SESSION[$pre . 'evaluated'] : '',
    '#ajax' => array(
      'callback' => 'quiz_browser_body_callback',
      'effect' => 'slide',
      'wrapper' => 'quiz-browser-body',
      'method' => 'replace',
    ),
  );
}

/**
 * Submit function for the result browser form
 */
function quiz_results_mr_form_submit($form, &$form_state) {
  // If we are confirming the deltion of results.
  if ($form_state['values']['op'] == t('Delete all marked results')) {
    foreach ($form_state['values']['table']['body']['name'] as $value) {
      if ($value !== 0) {
        // Find nid and rid
        $matches = array();
        preg_match('/([0-9]+)-([0-9]+)/', $value, $matches);
        $res_nid = $matches[1];
        $res_rid = $matches[2];
        // If we only showing the best results we still want to delete all results for this user
        if ($form_state['values']['table']['header']['filters']['best_results'] == 1) {
          _quiz_delete_results($res_rid, $res_nid);
        }
        else {
          _quiz_delete_results($res_rid);
        }
      }
    }
    if (isset($res_rid)) {
      drupal_set_message(t('Results have been deleted.'));
    }
  }
  else {
    // If we are deleting quizzes
    if ($form_state['values']['bulk_action'] == 'del') {
      $form_state['storage']['del'] = $form_state['values']['table']['body']['name'];
    }
  }
}

/**
 * Returns links to be placed on the quiz results browser.
 *
 * The links will be made visible when the user hovers over them.
 *
 * @param $quiz
 *   The quiz node
 * @param $rid
 *   Result id
 * @return Html string with links.
 */
function _quiz_results_mr_get_hover($quiz, $rid) {
  $to_return = array(l(t('view'), 'node/' . $quiz->nid . '/results/' . $rid));
  if (user_access('delete any quiz results') || user_access('delete results for own quiz')) {
    $to_return[] = l(t('delete'), 'admin/quiz/reports/results/' . $quiz->nid, array(
      'query' => array('del' => $rid),
      'attributes' => array('class' => 'hover-del', 'id' => $quiz->nid . '-' . $rid . '-del'),
    ));
  }
  return implode(' | ', $to_return);
}

/**
 * Delete a single result, or all results for a given user and a given quiz.
 *
 * @param $rid
 *   result if for the result to be deleted
 * @param $nid
 *   Node id for the quiz the result belongs to. If set all the users results for this quiz will be deleted.
 */
function _quiz_delete_results($rid, $nid = NULL) {
  $rids = array();

  // We are to delete all results for a certain user on a certain quiz.
  if (isset($nid)) {
    // TODO: We should be able to rewrite this one to use the DBTNG.
    $res = db_query('SELECT result_id
            FROM {quiz_node_results}
            WHERE nid = :nid AND uid = (
              SELECT uid
              FROM {quiz_node_results}
              WHERE result_id = :result_id
            )', array(':nid' => $nid, ':result_id' => $rid));

    while ($result = $res->fetchField()) {
      $rids[] = $result;
    }
  }
  // We are only to delete one specific result
  else {
    $rids[] = $rid;
  }
  quiz_delete_results($rids);
}

// HELPER FUNCTIONS

/**
 * Recursive helper function to set the validated property. (Taken from the skip validation module.)
 *
 * TODO: DELETE
 *
 * @param &$elements
 *   The elements that are currently being processed.
 */
function _quiz_skip_validation(&$elements) {
  $elements['#validated'] = TRUE;
  foreach (element_children($elements) as $key) {
    _quiz_skip_validation($elements[$key]);
  }
}

/**
 * Helper function for theme_question_selection_table
 *
 * TODO: DELETE
 *
 * @see quiz_questions_form()
 * @see theme_question_selection_table()
 *
 * @param $sub_form
 *   Form definition array for a filtered questions list
 * @param $id
 *   Identifier used in $sub_form
 * @return table row
 *   Array defining a table row
 */
function _quiz_get_question_row($sub_form, $id) {
  $question_types = _quiz_get_question_types();
  $type = $sub_form['types'][$id]['#markup'];

  // We add the class "hidden-class" to hide questions that haven't been added to the quiz yet.
  $hidden_class = ($sub_form['stayers'][$id]['#default_value'] === 0) ? ' hidden-question' : '';

  $data_array = array(
    // The checkbox and the title
    drupal_render($sub_form['stayers'][$id]) . drupal_render($sub_form['titles'][$id]),

    $type,
    $sub_form['view_links'][$id]['#markup'] . '<SPAN CLASS="q-remove" STYLE="display:none"> | ' . $sub_form['remove_links'][$id]['#markup'] . '</SPAN>',
    isset($sub_form['revision'][$id]) ? drupal_render($sub_form['revision'][$id]) : t("Up to date"),
    drupal_render($sub_form['max_scores'][$id]),
    drupal_render($sub_form['auto_update_max_scores'][$id]),
  );
  if (isset($sub_form['compulsories'])) {
    $data_array[] = drupal_render($sub_form['compulsories'][$id]);
  }
  $data_array[] = drupal_render($sub_form['weights'][$id]);
  return array(
    'class' => array('q-row draggable' . $hidden_class),
    'id' => 'q-' . $id,
    'data' => $data_array
  );
}

/**
 * Finds and returns the last table rows(HTML) in a table(HTML)
 *
 * TODO: DELETE
 *
 * @param $table
 *   HTML string with a table
 * @param $num_rows
 *   The number of rows to return(int)
 * @return
 *   last table row in the table(html string)
 */
function _quiz_get_last_table_rows($table, $num_rows = 1) {
  $matches = array();
  $num_matches = preg_match_all('/<tr.*?<\/tr>/is', $table, $matches);
  $to_return = '';
  $num_rows_to_return = ($num_matches > $num_rows) ? $num_rows : $num_matches;
  for ($i = $num_matches - 1; $i > $num_matches - 1 - $num_rows_to_return; $i--) {
    $to_return .= $matches[0][$i];
  }
  return $to_return;
}

/**
 * Finds and returns all table rows with a certain class(HTML) in a table(HTML)
 *
 * TODO: DELETE
 *
 * @param $table
 *   HTML string with a table
 * @return
 *   all table rows with a certain class in a table(html string)
 */
function _quiz_get_browser_content($table, $class) {
  $matches = array();
  $n_matches = preg_match('/<tr class="' . $class . '.*<\/tr>/is', $table, $matches);
  return $matches[0];
}

/**
 * Adds variables from a querystring to $_GET
 *
 * This is to help the pager system work with ajax
 *
 * @see quiz_browser_ahah()
 *
 * @param $to_add
 *   query string
 */
function _quiz_add_to_get($to_add) {
  $pre = 'quiz_question_browser_';
  parse_str($to_add, $output);
  $vars = array('sort', 'order', 'page');
  if (empty($to_add)) {
    unset($_SESSION[$pre . 'page']);
  }
  foreach ($vars as $value) {
    if (isset($output[$value])) {
      $_GET[$value] = $_SESSION[$pre . $value] = $output[$value];
    }
    elseif (isset($_GET[$value])) {
      continue;
    }
    elseif (isset($_SESSION[$pre . $value])) {
      $_GET[$value] = $_SESSION[$pre . $value];
    }
  }
}

/**
 * Helper function returning number of days as values and corresponding
 * number of milliseconds as array keys.
 *
 * @return
 *   array of options for when we want to delete partial quiz record values.
 */
function quiz_remove_partial_quiz_record_value() {
  return array(
    '0' => t('Never'),
    '86400' => t('1 Day'),
    '172800' => t('2 Days'),
    '259200' => t('3 Days'),
    '345600' => t('4 Days'),
    '432000' => t('5 Days'),
    '518400' => t('6 Days'),
    '604800' => t('7 Days'),
    '691200' => t('8 Days'),
    '777600' => t('9 Days'),
    '864000' => t('10 Days'),
    '950400' => t('11 Days'),
    '1036800' => t('12 Days'),
    '1123200' => t('13 Days'),
    '1209600' => t('14 Days'),
    '1296000' => t('15 Days'),
    '1382400' => t('16 Days'),
    '1468800' => t('17 Days'),
    '1555200' => t('18 Days'),
    '1641600' => t('19 Days'),
    '1728000' => t('20 Days'),
    '1814400' => t('21 Days'),
    '1900800' => t('22 Days'),
    '1987200' => t('23 Days'),
    '2073600' => t('24 Days'),
    '2160000' => t('25 Days'),
    '2246400' => t('26 Days'),
    '2332800' => t('27 Days'),
    '2419200' => t('28 Days'),
    '2505600' => t('29 Days'),
    '2592000' => t('30 Days'),
    '3024000' => t('35 Days'),
    '3456000' => t('40 Days'),
    '3888000' => t('45 Days'),
    '4320000' => t('50 Days'),
    '4752000' => t('55 Days'),
    '5184000' => t('60 Days'),
    '5616000' => t('65 Days'),
    '6048000' => t('70 Days'),
    '6480000' => t('75 Days'),
    '6912000' => t('80 Days'),
    '7344000' => t('85 Days'),
    '7776000' => t('90 Days'),
    '8208000' => t('95 Days'),
    '8640000' => t('100 Days'),
    '9072000' => t('105 Days'),
    '9504000' => t('110 Days'),
    '9936000' => t('115 Days'),
    '10368000' => t('120 Days'),
  );
}

/**
 * Adds inline js to automatically set the question's node title.
 */
function quiz_set_auto_title() {
  $max_length = variable_get('quiz_autotitle_length', 50);
  drupal_add_js('
  (function ($) {
  $(document).ready(function () {
    function quizStripTags(str) {
      return str.replace(/<\/?[^>]+>/gi, \'\');
    }

    function quizUpdateTitle() {
      var body = $("#edit-body textarea:eq(1)").val();
      if (quizStripTags(body).length > ' . $max_length . ') {
        $("#edit-title").val(quizStripTags(body).substring(0, ' . $max_length . ' - 3) + "...");
      }
      else {
        $("#edit-title").val(quizStripTags(body).substring(0, ' . $max_length . '));
      }
    }
    $("#edit-body textarea").keyup(quizUpdateTitle);
    // Do not use auto title if a title already has been set
    if($("#edit-title").val().length > 0){
      $("#edit-body textarea:eq(1)").unbind("keyup", quizUpdateTitle);
    }
    $("#edit-title").keyup(function() {
      $("#edit-body textarea:eq(1)").unbind("keyup", quizUpdateTitle);
    });
  });
  })(jQuery);
  ', array('type' => 'inline', 'scope' => JS_DEFAULT));
}

/**
 * Returns list of options for the changed select box
 *
 * @see _quiz_questions_browser_form()
 *
 * @return $changed_options
 *   Options for the changed select box.
 */
function _quiz_get_time_interval_options() {
  return array(
    t('No filter'),
    t('Today'),
    t('Yesterday'),
    t('Two days ago'),
    t('This week'),
    t('Last week'),
    t('This month'),
    t('Last month'),
    t('This year'),
    t('Last year'),
    t('Long ago'),
  );
}

/**
 * Returns an array with sql where clauses correscponding to the options in the time filters.
 *
 * @see _quiz_questions_browser_form()
 *
 * @return $changed_timestamps
 *   array of timestamps and sql filters
 */
function _quiz_get_interval_timestamps($fieldname) {
  // Create datastructure to help create where clause in the sql for the changed filter...
  $now = REQUEST_TIME;
  $one_day = 86400;
  $one_week = 604800;
  $timestamp_today = mktime(0, 0, 0, date('n'), date('j'), date('Y'));
  $weekday = date('N', $now);
  $timestamp_week = $timestamp_today - ((int) $weekday -1) * $one_day;
  $timestamp_month = mktime(0, 0, 0, date('n'), 1, date('Y'));
  $timestamp_last_month = mktime(0, 0, 0, date('n', $timestamp_month - 1), 1, date('Y', $timestamp_month - 1));
  $timestamp_year = mktime(0, 0, 0, 1, 1, date('Y'));
  $timestamp_last_year = mktime(0, 0, 0, 1, 1, date('Y', $timestamp_year - 1));
  $changed_timestamps = array(
    NULL,
    array($timestamp_today, $now),
    array($timestamp_today - $one_day * 1, $timestamp_today),
    array($timestamp_today - $one_day * 2, $timestamp_today - $one_day * 1),
    array($timestamp_week, $now),
    array($timestamp_week - $one_week, $timestamp_week),
    array($timestamp_month, $now),
    array($timestamp_last_month, $timestamp_month),
    array($timestamp_year, $now),
    array($timestamp_last_year, $timestamp_year),
    array(0, $timestamp_last_year),
  );

  foreach ($changed_timestamps as $key => &$val) {
    if ($val == NULL) {
      continue;
    }
    $val['sql'] = " AND $fieldname > " . $val[0] . " AND $fieldname < " . $val[1];
  }
  return $changed_timestamps;
}

/**
 * Returns an array with sql where clauses correscponding to the options in the duration filters.
 *
 * @see _quiz_questions_browser_form()
 *
 * @return $changed_timestamps
 *   array of timestamps and sql filters
 */
function _quiz_get_duration_intervals() {
  // Create datastructure to help create where clause in the sql for the changed filter...
  $durations = array(
    NULL,
    '> 60',
    '> 300',
    '> 600',
    '> 3600',
    '> 28800',
    '> 86400',
    '< 60',
    '< 300',
    '< 600',
    '< 3600',
    '< 28800',
    '< 86400',
  );

  foreach ($durations as $key => &$val) {
    if ($val == NULL) {
      continue;
    }
    $durations[$key] = ' AND (time_end - time_start) ' . $val;
  }
  return $durations;
}

/**
 * Returns an array with options for the time filters.
 *
 * @see _quiz_get_duration_intervals()
 *
 * @return $options
 *   array of options for the duration filter
 */
function _quiz_get_duration_options() {
  return array(
    t('No filter'),
    t('> 1 m'),
    t('> 5 m'),
    t('> 10 m'),
    t('> 1 h'),
    t('> 8 h'),
    t('> 24 h'),
    t('< 1 m'),
    t('< 5 m'),
    t('< 10 m'),
    t('< 1 h'),
    t('< 8 h'),
    t('< 24 h'),
  );
}

/**
 * Returns an array with options for the score filters.
 *
 * @see _quiz_get_score_intervals()
 *
 * @return $options
 *   array of options for the score filter
 */
function _quiz_get_score_options() {
  return array(
    t('No filter'),
    t('Passed'),
    t('Failed'),
    t('= 100 %'),
    t('> 90 %'),
    t('> 75 %'),
    t('> 50 %'),
    t('> 25 %'),
    t('< 90 %'),
    t('< 75 %'),
    t('< 50 %'),
    t('< 25 %'),
  );
}

/**
 * Returns an array with sql where clauses correscponding to the options in the score filters.
 *
 * @see _quiz_questions_browser_form()
 *
 * @return $changed_timestamps
 *   array of timestamps and sql filters
 */
function _quiz_get_score_intervals($quiz) {
  // Create datastructure to help create where clause in the sql for the changed filter...
  $scores = array(
    NULL,
    '>= qnp.pass_rate',
    '< qnp.pass_rate',
    '= 100',
    '> 90',
    '> 75',
    '> 50',
    '> 25',
    '< 90',
    '< 75',
    '< 50',
    '< 25',
  );

  foreach ($scores as $key => &$val) {
    if ($val == NULL) {
      continue;
    }
    $scores[$key] = ' AND score ' . $val;
  }
  return $scores;
}

/**
 * Themes a categorized quiz form
 */
function theme_quiz_categorized_form($variables) {
  $form = $variables['form'];
  $output = '';
  $rows = array();
  foreach ($form as $key => &$existing) {
    if (!is_numeric($key)) {
      continue;
    }
    $cols = array();
    $cols[] = drupal_render($existing['name']);
    $cols[] = drupal_render($existing['number']);
    $cols[] = drupal_render($existing['max_score']);
    $cols[] = drupal_render($existing['remove']);
    $cols[] = drupal_render($existing['weight']);
    $rows[] = array(
      'data' => $cols,
      'class' => array('draggable'),
    );
  }
  if (!empty($rows)) {
    $header = array(
      t('Category'),
      t('Number of questions'),
      t('Max score per question'),
      t('Remove'),
      t('Weight'),
    );
    drupal_add_tabledrag('existing-terms', 'order', 'sibling', 'term-weight', NULL, NULL, TRUE);
    $output .= theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'existing-terms')));
  }
  $output .= drupal_render_children($form);
  drupal_add_js(
    "(function ($) {
     Drupal.behaviors.quiz_categorized = {
     attach: function(context) {
      $('#browse-for-term:not(.quiz-processed)').click(function(event) {
        event.preventDefault();
        $('#edit-term').focus().val('*').trigger('keyup');
      }).addClass('quiz-processed');
      $('#edit-term').click(function(){
        if ($(this).val() == '*') {
          $(this).val('');
        }
      });
    }};}(jQuery));"
    , array('type' => 'inline', 'group' => JS_DEFAULT));
  return $output;
}

function theme_quiz_browser($variables) {
  return '<table>' . drupal_render($variables['form']['header']) . drupal_render($variables['form']['body']) . '</table>';
}
