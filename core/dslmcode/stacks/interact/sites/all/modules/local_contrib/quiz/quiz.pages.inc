<?php

/**
 * User pages.
 * @file
 */

/**
 * Show result page for a given result id
 *
 * @param $result_id
 *  Result id
 */
function quiz_user_results($result_id) {
  $result = quiz_result_load($result_id);

  if ($result->nid) {
    $quiz = node_load($result->nid, $result->vid);
    $current_quiz = node_load($result->nid);
    $questions = _quiz_get_answers($quiz, $result_id);
    $score = quiz_calculate_score($quiz, $result_id);
    $summary = _quiz_get_summary_text($quiz, $score);
    $data = array(
      'quiz' => $quiz,
      'questions' => $questions,
      'score' => $score,
      'summary' => $summary,
      'result_id' => $result_id,
    );
    if (user_access('view own quiz results') || $current_quiz->feedback_time == QUIZ_FEEDBACK_END) {
      // User can view own quiz results OR the current quiz has "display solution".
      return theme('quiz_user_summary', $data);
    }
    else {
      // User cannot view own results or show solution. Show summary.
      return theme('quiz_take_summary', $data);
    }
  }
}

/**
 * Form for showing feedback, and for editing the feedback if necessary...
 *
 * @param $form_state
 *   FAPI form state(array)
 * @param $questions
 *   array of questions to inclide in the report
 * @param $showpoints
 *   Should points be included in the report? (Boolean)
 * @param $showfeedback
 *   Should feedback be included in the report? (Boolean)
 * @param $allow_scoring
 *   Should we allow the user to score results that needs manual scoring? (Boolean)
 * @return $form
 *   FAPI form array
 */
function quiz_report_form($form, $form_state, $questions, $showpoints = TRUE, $showfeedback = TRUE, $allow_scoring = FALSE) {
  $form = array();
  // The submit button is only shown if one or more of the questions has input elements
  $show_submit = FALSE;
  foreach ($questions as $question) {
    $module = quiz_question_module_for_type($question->type);
    if (!$module) {
      return array();
    }
    $function = $module . '_report_form';
    $form_to_add = $function($question, $showpoints, $showfeedback, $allow_scoring);
    if (isset($form_to_add['submit'])) {
      $show_submit = TRUE;
    }
    $form[] = $form_to_add;
  }
  $form['#theme'] = 'quiz_report_form';
  $form['#showpoints'] = $showpoints;
  $form['#showfeedback'] = $showfeedback;
  $form['#tree'] = TRUE;
  if ($show_submit) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#submit' => array('quiz_report_form_submit'),
      '#validate' => array('quiz_report_form_validate'),
      '#value' => t('Save Score'),
    );
  }

  if (arg(4) == 'feedback') {
    // @todo figure something better than args.
    $quiz = node_load(arg(1));
    if (empty($_SESSION['quiz'][$quiz->nid])) {
      // Quiz is done.
      $form['finish'] = array(
        '#type' => 'submit',
        '#submit' => array('quiz_take_question_feedback_end_submit'),
        '#value' => t('Finish'),
      );
    }
    else {
      $form['next'] = array(
        '#type' => 'submit',
        '#submit' => array('quiz_take_question_feedback_submit'),
        '#value' => t('Next question'),
      );
    }
  }

  return $form;
}

/**
 * Validate the report form
 */
function quiz_report_form_validate($form, &$form_state) {
  /* We go through the form state values and validates all
   * questiontypes with validation functions declared.
   */
  foreach ($form_state['values'] as $key => $q_values) {
    // Questions has numeric keys in the report form
    if (!is_numeric($key)) {
      continue;
    }
    // Questions store the name of the validation function with the key 'validate'
    if (!isset($q_values['validate'])) {
      continue;
    }
    // The validation function must exist
    if (!function_exists($q_values['validate'])) {
      continue;
    }
    // We call the validation function provided by the question
    call_user_func($q_values['validate'], $q_values, $key);
  }
}

/**
 * Submit the report form
 */
function quiz_report_form_submit($form, &$form_state) {
  /* We go through the form state values and submit all
   * questiontypes with validation functions declared.
   */
  global $user;
  foreach ($form_state['values'] as $key => $q_values) {
    // Questions has numeric keys in the report form
    if (!is_numeric($key)) {
      continue;
    }
    // Questions store the name of the validation function with the key 'submit'
    if (!isset($q_values['submit'])) {
      continue;
    }
    // The submit function must exist
    if (!function_exists($q_values['submit'])) {
      continue;
    }

    // Load the quiz
    if (!isset($quiz)) {
      $result = db_query('SELECT nid, uid, vid FROM {quiz_node_results} WHERE result_id = :result_id', array(':result_id' => $q_values['result_id']))->fetchObject();
      $quiz = node_load($result->nid, $result->vid);
      $result_id = $q_values['result_id'];
    }

    $q_values['quiz'] = $quiz;

    // We call the submit function provided by the question
    call_user_func($q_values['submit'], $q_values);
  }
  // Scores may have been changed. We take the necessary actions
  quiz_update_total_score_fast($result_id, $quiz->vid);
  $changed = db_update('quiz_node_results')
    ->fields(array(
      'is_evaluated' => 1,
    ))
    ->condition('result_id', $result_id)
    ->execute();
  $results_got_deleted = _quiz_maintain_results($quiz, $result_id);

  // A message saying the quiz is unscored has already been set. We unset it here...
  if ($changed > 0) {
    _quiz_remove_unscored_message();
  }

  // Notify the user if results got deleted as a result of him scoring an answer.
  $add = $quiz->keep_results == QUIZ_KEEP_BEST && $results_got_deleted ? ' ' . t('Note that this quiz is set to only keep each users best answer.') : '';

  $score_data = quiz_get_score_array($result_id, $quiz->vid, TRUE);

  module_invoke_all('quiz_scored', $quiz, $score_data, $result_id);

  drupal_set_message(t('The scoring data you provided has been saved.') . $add);
  if (user_access('score taken quiz answer') && !user_access('view any quiz results')) {
    if ($result && $result->uid == $user->uid) {
      $form_state['redirect'] = 'node/' . $quiz->nid . '/quiz/results/' . $result_id;
    }
  }
}

/**
 * Helper function to remove the message saying the quiz haven't been scored
 */
function _quiz_remove_unscored_message() {
  if (!empty($_SESSION['messages']['warning'])) {
    // Search for the message, and remove it if we find it.
    foreach ($_SESSION['messages']['warning'] as $key => $val) {
      if ($val == t('This quiz has not been scored yet.')) {
        unset($_SESSION['messages']['warning'][$key]);
      }
    }
    // Clean up if the message array was left empty
    if (empty($_SESSION['messages']['warning'])) {
      unset($_SESSION['messages']['warning']);
      if (empty($_SESSION['messages'])) {
        unset($_SESSION['messages']);
      }
    }
  }
}

/**
 * Updates the total score using only one mySql query.
 *
 * @param $result_id
 *  Result id
 * @param $quiz_vid
 *  Quiz node version id
 */
function quiz_update_total_score_fast($result_id, $quiz_vid) {
  $subq1 = db_select('quiz_node_results_answers', 'a');
  $subq1
    ->condition('a.result_id', $result_id)
    ->addExpression('SUM(a.points_awarded)');
  $res1 = $subq1->execute()->fetchField();

  $subq2 = db_select('quiz_node_properties', 'qnp');
  $subq2
    ->condition('qnp.vid', $quiz_vid)
    ->addField('qnp', 'max_score');
  $res2 = $subq2->execute()->fetchField();

  db_update('quiz_node_results')
    ->expression('score', 'ROUND(100*(:res1/:res2))', array(':res1' => $res1, ':res2' => $res2))
    ->condition('result_id', $result_id)
    ->execute();
}

/**
 * Returns an array of score information for a quiz
 *
 * @param unknown_type $result_id
 * @param unknown_type $quiz_vid
 * @param unknown_type $is_evaluated
 */
function quiz_get_score_array($result_id, $quiz_vid, $is_evaluated) {
  $properties = db_query('SELECT max_score, number_of_random_questions
          FROM {quiz_node_properties}
          WHERE vid = :vid', array(':vid' => $quiz_vid))->fetchObject();
  $total_score = db_query('SELECT SUM(points_awarded)
          FROM {quiz_node_results_answers}
          WHERE result_id = :result_id', array(':result_id' => $result_id))->fetchField();

  return array(
    'question_count' => $properties->number_of_random_questions + _quiz_get_num_always_questions($quiz_vid),
    'possible_score' => $properties->max_score,
    'numeric_score' => $total_score,
    'percentage_score' => ($properties->max_score == 0) ? 0 : round(($total_score * 100) / $properties->max_score),
    'is_evaluated' => $is_evaluated,
  );
}

// THEME FUNCTIONS

/**
 * Pass the correct mark to the theme so that theme authors can use an image.
 *
 * @ingroup themeable
 */
function theme_quiz_score_correct() {
  $variables = array(
    'path' => drupal_get_path('module', 'quiz') . '/images/correct.gif',
    'alt' => t('correct'),
    'title' => t('correct'),
  );
  return theme('image', $variables);
}

/**
 * Pass the incorrect mark to the theme so that theme authors can use an image.
 *
 * @ingroup themeable
 */
function theme_quiz_score_incorrect() {
  $variables = array(
    'path' => drupal_get_path('module', 'quiz') . '/images/incorrect.gif',
    'alt' => t('incorrect'),
    'title' => t('incorrect'),
  );
  return theme('image', $variables);
}

/**
 * Pass the unknown mark to the theme so that theme authors can use an image.
 *
 * @ingroup themeable
 */
function theme_quiz_score_unknown() {
  $variables = array(
    'path' => drupal_get_path('module', 'quiz') . '/images/unselected.gif',
    'alt' => t('unknown'),
    'title' => t('unknown'),
  );
  return theme('image', $variables);
}

/**
 * Theme a progress indicator for use during a quiz.
 *
 * @param $question_number
 *  The position of the current question in the sessions' array.
 * @param $num_of_question
 *  The number of questions for this quiz as returned by quiz_get_number_of_questions().
 * @return
 *  Themed html.
 *
 * @ingroup themeable
 */
function theme_quiz_progress($variables) {
  $output = '';
  $output .= '<div id="quiz_progress">';

  if ($variables['allow_jumping']) {
    // Show jump form.
    $current_question = drupal_get_form('quiz_jumper', $variables['questions'], $variables['current']);
    $output .= drupal_render($current_question);
  }
  else {
    // Just text.
    $output .= t('Question <span id="quiz-question-number">!x</span> of <span id="quiz-num-questions">@y</span>', array('!x' => $variables['current'], '@y' => count($variables['questions'])));
  }

  $output .= '</div>' . "\n";
  // Add div to be used by jQuery countdown
  if ($variables['time_limit']) {
    $output .= '<div class="countdown"></div>';
  }
  return $output;
}

/**
 * @todo Please document this function.
 * @see http://drupal.org/node/1354
 */
function theme_quiz_jumper($variables) {
  drupal_add_js('
    (function ($) {
      Drupal.behaviors.quizJumper = {
        attach: function(context, settings) {
          $("#quiz-jumper:not(.quizJumper-processed)", context).show().addClass("quizJumper-processed").change(function(){
            $("#quiz-jumper #edit-submit").trigger("click");
          });
          $("#quiz-jumper-no-js:not(.quizJumper-processed)").hide().addClass("quizJumper-processed");
        }
      };
    })(jQuery);
  ', array('type' => 'inline', 'scope' => JS_DEFAULT));
  return '';
}

/**
 * Theme the summary page after the quiz has been completed.
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
function theme_quiz_take_summary($variables) {
  $quiz = $variables['quiz'];
  $questions = $variables['questions'];
  $score = $variables['score'];
  $summary = $variables['summary'];
  $result_id = $variables['result_id'];
  // Set the title here so themers can adjust.
  drupal_set_title($quiz->title);

  // Display overall result.
  $output = '';
  if (!empty($score['possible_score'])) {
    if (!$score['is_evaluated']) {
      if (user_access('score taken quiz answer')) {
        $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final. <a class="self-score" href="!result_url">Click here</a> to give scores on your own.', array('@quiz' => QUIZ_NAME, '!result_url' => url('node/' . $quiz->nid . '/results/' . $result_id)));
      }
      else {
        $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final.', array('@quiz' => QUIZ_NAME));
      }
      drupal_set_message($msg, 'warning');
    }
    $output .= '<div id="quiz_score_possible">' . t('You got %num_correct of %question_count possible points.', array('%num_correct' => $score['numeric_score'], '%question_count' => $score['possible_score'])) . '</div>' . "\n";
    $output .= '<div id="quiz_score_percent">' . t('Your score: %score %', array('%score' => $score['percentage_score'])) . '</div>' . "\n";
  }
  if (isset($summary['passfail'])) {
    $output .= '<div id="quiz_summary">' . $summary['passfail'] . '</div>' . "\n";
  }
  if (isset($summary['result'])) {
    $output .= '<div id="quiz_summary">' . $summary['result'] . '</div>' . "\n";
  }
  // Get the feedback for all questions. These are included here to provide maximum flexibility for themers
  if ($quiz->feedback_time == QUIZ_FEEDBACK_END) {
    $form = drupal_get_form('quiz_report_form', $questions);
    $output .= drupal_render($form);
  }
  return $output;
}

/**
 * Theme the summary page for user results.
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
function theme_quiz_user_summary($variables) {
  global $user;
  $quiz = $variables['quiz'];
  $questions = $variables['questions'];
  $score = $variables['score'];
  $summary = $variables['summary'];
  $result_id = $variables['result_id'];
  // Set the title here so themers can adjust.
  drupal_set_title($quiz->title);

  if (!$score['is_evaluated']) {
    if (user_access('score taken quiz answer')) {
      $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final. <a class="self-score" href="!result_url">Click here</a> to give scores on your own.', array('@quiz' => QUIZ_NAME, '!result_url' => url('node/' . $quiz->nid . '/results/' . $result_id)));
    }
    else {
      $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final.', array('@quiz' => QUIZ_NAME));
    }
  }

  // Display overall result.
  $output = '';
  $output .= '<div id="quiz_score_possible">' .
    t('You got %num_correct of %question_count possible points.', array('%num_correct' => $score['numeric_score'], '%question_count' => $score['possible_score'])) .
    '</div>';
  $output .= '<div id="quiz_score_percent">' .
    t('Your score: @score%', array('@score' => $score['percentage_score'])) .
    '</div>';

  if (isset($summary['passfail'])) {
    $output .= '<div id="quiz_summary">' . $summary['passfail'] . '</div>' . "\n";
  }
  if (isset($summary['result'])) {
    $output .= '<div id="quiz_summary">' . $summary['result'] . '</div>' . "\n";
  }
  // Get the feedback for all questions.
  $allow_scoring = quiz_allow_score_access($quiz);
  $form = drupal_get_form('quiz_report_form', $questions, FALSE, TRUE, $allow_scoring);
  $output .= drupal_render($form);
  return $output;
}

/**
 * Theme the "no feedback" option.
 *
 * @return
 *  Themed html feedback.
 *
 * @ingroup themeable
 */
function theme_quiz_no_feedback() {
  return t('Thanks for taking the quiz!');
}

/**
 * Theme the single question node
 *
 * @param $node
 *  The question node
 * @return
 *  Themed html feedback
 */
function theme_quiz_single_question_node($variables) {
  $node = $variables['question_node'];
  // This might seem meaningless, but it is designed this way to allow themes to add more
  // meaningful stuff here...
  return drupal_render($node->content);
}

/**
 * Theme the stats on the views page
 *
 * @param $node
 *   The quiz node
 */
function theme_quiz_view_stats($variables) {
  $node = $variables['node'];
  // Fetch data
  $stats = array(
    array(
      'title' => t('Questions'),
      'data' => $node->number_of_questions,
    ),
  );
  if ($node->show_attempt_stats) {
    $takes = $node->takes == 0 ? t('Unlimited') : $node->takes;
    $stats[] = array(
      'title' => t('Attempts allowed'),
      'data' => $takes,
    );
  }
  if ($node->quiz_always) {
    $stats[] = array(
      'title' => t('Available'),
      'data' => t('Always'),
    );
  }
  else {
    $stats[] = array(
      'title' => t('Opens'),
      'data' => format_date($node->quiz_open, 'short'),
    );
    $stats[] = array(
      'title' => t('Closes'),
      'data' => format_date($node->quiz_close, 'short'),
    );
  }
  if (!empty($node->pass_rate)) {
    $stats[] = array(
      'title' => t('Pass rate'),
      'data' => $node->pass_rate . ' %',
    );
  }
  if (!empty($node->time_limit)) {
    $stats[] = array(
      'title' => t('Time limit'),
      'data' => _quiz_format_duration($node->time_limit),
    );
  }
  $stats[] = array(
    'title' => t('Backwards navigation'),
    'data' => $node->backwards_navigation ? t('Allowed') : t('Forbidden'),
  );
  // Format and output the data
  $out = '<table id="quiz-view-table">' . "\n";
  foreach ($stats as $stat) {
    $out .= '<tr><td class="quiz-view-table-title"><strong>' . $stat['title'] . ':</strong></td><td class="quiz-view-table-data"><em>' . $stat['data'] . '</em></td></tr>' . "\n";
  }
  $out .= '</table>' . "\n";
  return $out;
}
