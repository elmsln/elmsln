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
  global $user;
  $result = db_query('SELECT qnp.nid, qnp.vid, qnrs.uid
    FROM {quiz_node_properties} qnp
    INNER JOIN {quiz_node_results} qnrs ON qnrs.vid = qnp.vid
    WHERE qnrs.result_id = :rid', array(':rid' => $result_id))->fetch();

  if ($result->nid) {
    // User can view own results (quiz_menu sets access to 'own results').
    // User with role 'user results' can view other user's results.
    if ($result->uid != $user->uid && !user_access('view any quiz results')) {
      drupal_access_denied();
      return;
    }

    $quiz = node_load($result->nid, $result->vid);
    $questions = _quiz_get_answers($quiz, $result_id);
    $score = quiz_calculate_score($quiz, $result_id);
    $summary = _quiz_get_summary_text($quiz, $score);
    $data = array(
      'quiz' => $quiz,
      'questions' => $questions,
      'score' => $score,
      'summary' => $summary,
      'rid' => $result_id,
    );
    return theme('quiz_user_summary', $data);
  }
  else {
    drupal_not_found();
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
      $result = db_query('SELECT nid, uid, vid FROM {quiz_node_results} WHERE result_id = :result_id', array(':result_id' => $q_values['rid']))->fetchObject();
      $quiz = node_load($result->nid, $result->vid);
      $rid = $q_values['rid'];
    }

    $q_values['quiz'] = $quiz;

    // We call the submit function provided by the question
    call_user_func($q_values['submit'], $q_values);
  }
  // Scores may have been changed. We take the necessary actions
  quiz_update_total_score_fast($rid, $quiz->vid);
  $changed = db_update('quiz_node_results')
  ->fields(array(
    'is_evaluated' =>  1,
  ))
  ->condition('result_id', $rid)
  ->execute();
  $results_got_deleted = _quiz_maintain_results($quiz, $rid);

  // A message saying the quiz is unscored has already been set. We unset it here...
  if($changed > 0) {
    _quiz_remove_unscored_message();
  }

  // Notify the user if results got deleted as a result of him scoring an answer.
  $add = $quiz->keep_results == QUIZ_KEEP_BEST && $results_got_deleted ? ' ' . t('Note that this quiz is set to only keep each users best answer.') : '';

  $score_data = quiz_get_score_array($rid, $quiz->vid, TRUE);

  module_invoke_all('quiz_scored', $quiz, $score_data, $rid);

  drupal_set_message(t('The scoring data you provided has been saved.') . $add);
  if (user_access('score taken quiz answer') && !user_access('view any quiz results')) {
    if ($result && $result->uid == $user->uid) {
      $form_state['redirect'] = 'node/' . $quiz->nid . '/results/' . $rid;
    }
  }
}

/**
 * Helper function to remove the message saying the quiz haven't been scored
 */
function _quiz_remove_unscored_message() {
  if (is_array($_SESSION['messages']['warning'])) {
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
 * @param $rid
 *  Result id
 * @param $quiz_vid
 *  Quiz node version id
 */
function quiz_update_total_score_fast($rid, $quiz_vid) {
	$subq1 = db_select('quiz_node_results_answers', 'a');
	$subq1
		->condition('a.result_id', $rid)
		->addExpression('SUM(a.points_awarded)');
	$res1 = $subq1->execute()->fetchField();

	$subq2 = db_select('quiz_node_properties', 'qnp');
	$subq2
		->condition('qnp.vid', $quiz_vid)
		->addField('qnp', 'max_score');
	$res2 = $subq2->execute()->fetchField();

	db_update('quiz_node_results')
		->expression('score', 'ROUND(100*(:res1/:res2))', array(':res1' => $res1, ':res2' => $res2))
		->condition('result_id', $rid)
		->execute();
}

/**
 * Returns an array of score information for a quiz
 *
 * @param unknown_type $rid
 * @param unknown_type $quiz_vid
 * @param unknown_type $is_evaluated
 */
function quiz_get_score_array($rid, $quiz_vid, $is_evaluated) {
  $properties = db_query('SELECT max_score, number_of_random_questions
          FROM {quiz_node_properties}
          WHERE vid = :vid', array(':vid' => $quiz_vid))->fetchObject();
  $total_score = db_query('SELECT SUM(points_awarded)
          FROM (quiz_node_results_answers)
          WHERE result_id = :result_id', array(':result_id' => $rid))->fetchField();

  return array(
    'question_count' => $properties->number_of_random_questions + _quiz_get_num_always_questions($quiz_vid),
    'possible_score' => $properties->max_score,
    'numeric_score' => $total_score,
    'percentage_score' => ($properties->max_score == 0) ? 0 : round(($total_score * 100) / $properties->max_score),
    'is_evaluated' => $is_evaluated,
  );
}

/**
 * Displays all the quizzes the user has taken part in.
 *
 * @param $user_id
 *  User id
 * @return
 *  HTML output for page.
 */
function quiz_get_user_results($uid) {
  $results = array();
  $dbresult = db_query('SELECT DISTINCT(n.nid), n.title, qnp.pass_rate, qnrs.result_id, qnrs.time_start, qnrs.time_end, qnrs.score, qnrs.is_evaluated
    FROM {node} n
    INNER JOIN {quiz_node_properties} qnp ON n.nid = qnp.nid
    INNER JOIN {quiz_node_results} qnrs ON qnrs.vid = qnp.vid
    INNER JOIN {users} u ON u.uid = qnrs.uid
    WHERE n.type = :type
      AND u.uid = :uid
    ORDER BY qnrs.result_id ASC', array(':type' => 'quiz', ':uid' => $uid));

  // Create an array out of the results.
  foreach ($dbresult as $result) {
    $result = (array) $result;
    $results[$result['result_id']] = $result;
  }
  return theme('quiz_get_user_results', array('results' => $results));
}

/**
 * Show results for the current quiz
 */
function quiz_my_results($node) {
  global $user;
  $results = array();
  $res = db_query('
    SELECT qnp.nid, qnp.pass_rate, qnrs.result_id, qnrs.time_start, qnrs.time_end, qnrs.score
    FROM {quiz_node_properties} qnp
    INNER JOIN {quiz_node_results} qnrs ON qnrs.vid = qnp.vid
    WHERE qnrs.uid = :uid AND qnrs.nid = :nid AND qnrs.is_evaluated = 1
    ORDER BY qnrs.result_id DESC',
    array(':uid' => $user->uid, ':nid' => $node->nid)
  );
  // Create an array out of the results.
  while ($line = $res->fetchAssoc()) {
    $results[$line['result_id']] = $line;
  }
  return theme('quiz_my_results_for_quiz', array('rows' => $results));
}

// THEME FUNCTIONS

/**
 * Theme the user results page.
 *
 * @param $results
 *  An array of quiz information.
 * @return
 *  Themed html.
 *
 * @ingroup themeable
 */
function theme_quiz_get_user_results($variables) {
  $results = $variables['results'];
  $rows = array();

  while (list($key, $result) = each($results)) {
    $interval = _quiz_format_duration($result['time_end'] - $result['time_start']);
    $passed = $result['score'] >= $result['pass_rate'];
    $grade = $passed ? t('Passed') : t('Failed');
    $passed_class = $passed ? 'quiz-passed' : 'quiz-failed';
    if (!is_numeric($result['score'])) {
      $score = t('In progress');
    }
    elseif (!$result['is_evaluated']) {
      $score = t('Not evaluated');
    }
    else {
      if (!empty($result['pass_rate']) && is_numeric($result['score'])) {
        $pre_score = '<span class = "' . $passed_class . '">';
        $post_score = ' %<br><em>' . $grade . '</em></span>';
      }
      else {
        $post_score = ' %';
      }
      $score = $pre_score . $result['score'] . $post_score;
    }
    $rows[] = array(
      'title'       => l($result['title'], 'node/' . $result['nid']),
      'time_start'  => format_date($result['time_start'], 'short'),
      'time_end'    => ($result['time_end'] > 0) ? format_date($result['time_end'], 'short') . '<br />' . t('Duration :  @value', array('@value' => $interval)) : t('In Progress'),

      'score'       => $score,
      'evaluated'   => $result['is_evaluated'] ? t('Yes') : t('No'),
      'op'          => l(t('View answers'), 'user/quiz/' . $result['result_id'] . '/userresults'),
    );

  }

  if (empty($rows)) {
    return t('No @quiz results found.', array('@quiz' => QUIZ_NAME));
  }

  $header = array(
    t('@quiz Title', array('@quiz' => QUIZ_NAME)),
    t('Started'),
    t('Finished'),
    t('Score'),
    t('Evaluated'),
    t('Operation'),
  );

  $output = theme('table', array('header' => $header, 'rows' => $rows));
  $output .= '<p><em>' . t('@quizzes that are not evaluated may have a different score and grade once evaluated.', array('@quizzes' => QUIZ_NAME)) . '</em></p>';
  return $output;
}

/**
 * Theme the user results page.
 *
 * @param $results
 *  An array of quiz information.
 * @return
 *  Themed html.
 *
 * @ingroup themeable
 */
function theme_quiz_my_results_for_quiz($variables) {
  $results = $variables['rows'];
  $rows = array();
  $with_passing = FALSE;
  while (list($key, $result) = each($results)) {
    $interval = _quiz_format_duration($result['time_end'] - $result['time_start']);
    $score = $result['score'] . ' %';

    $row = array(
      'time_start'  => format_date($result['time_start'], 'short'),
      'duration' => $interval,
      'score'       => $score,
    );
    if (!empty($result['pass_rate'])) {
      $with_passing = TRUE;
      $passed = $result['score'] >= $result['pass_rate'];
      $grade = $passed ? t('Passed') : t('Failed');
      $passed_class = $passed ? 'quiz-passed' : 'quiz-failed';
      $pre = '<span class = "' . $passed_class . '">';
      $row['passed'] = $pre . $grade . '</span>';
    }
    $row['more'] = l(t('More') . '...', 'node/' . $result['nid'] . '/myresults/' . $result['result_id']);
    $rows[] = $row;
  }

  if (empty($rows)) {
    return t('No @quiz results found.', array('@quiz' => QUIZ_NAME));
  }

  $header = array(
    t('Started'),
    t('Duration'),
    t('Score'),
  );
  if ($with_passing) {
    $header[] = t('Passed');
  }
  $header[] = '';
  $output = theme('table', array('header' => $header, 'rows' => $rows));
  return $output;
}

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
  $question_number = $variables['question_number'];
  $num_of_question = $variables['num_questions'];
  // TODO Number of parameters in this theme funcion does not match number of parameters found in hook_theme.
  // Determine the percentage finished (not used, but left here for other implementations).
  //$progress = ($question_number*100)/$num_of_question;

  // Get the current question # by adding one.
  $current_question = $question_number + 1;

  if ($variables['allow_jumping']) {
    $current_question = theme('quiz_jumper', array('current' => $current_question, 'num_questions' => $num_of_question));
  }

  $output  = '';
  $output .= '<div id="quiz_progress">';
  $output .= t('Question <span id="quiz-question-number">!x</span> of <span id="quiz-num-questions">@y</span>', array('!x' => $current_question, '@y' => $num_of_question));
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
  $current = $variables['current'];
  $num_questions = $variables['num_questions'];
  $output = '<select name="quiz-jumper" class="form-select" id="quiz-jumper">';
  for ($i = 1; $i <= $num_questions; $i++) {
    $extra = $i == $current ? ' selected="selected"' : '';
    $output .= '<option value="' . $i . '"' . $extra . '>' . $i . '</option>';
  }
  $output .= '</select><span id="quiz-jumper-no-js">' . $current . '</span>';
  drupal_add_js('
    (function ($) {
      Drupal.behaviors.quizJumper = {
        attach: function(context, settings) {
          $("#quiz-jumper:not(.quizJumper-processed)", context).show().addClass("quizJumper-processed").change(function(){
            $("[name=jump_to_question]").val($(this).val());
            $("#edit-submit").trigger("click");
          });
          $("#quiz-jumper-no-js:not(.quizJumper-processed)").hide().addClass("quizJumper-processed");
        }
      };
    })(jQuery);
  ', array('type' => 'inline', 'scope' => JS_DEFAULT));
  return $output;
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
  $rid =  $variables['rid'];
  // Set the title here so themers can adjust.
  drupal_set_title($quiz->title);

  // Display overall result.
  $output = '';
  if (!empty($score['possible_score'])) {
    if (!$score['is_evaluated']) {
      if (user_access('score taken quiz answer')) {
        $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final. <a class="self-score" href="!result_url">Click here</a> to give scores on your own.', array('@quiz' => QUIZ_NAME, '!result_url' => url('node/' . $quiz->nid . '/results/' . $rid)));
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
  if ($quiz->display_feedback) {
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
  $quiz = $variables['quiz'];
  $questions = $variables['questions'];
  $score = $variables['score'];
  $summary = $variables['summary'];
  $rid = $variables['rid'];
  // Set the title here so themers can adjust.
  drupal_set_title($quiz->title);

  if (!$score['is_evaluated']) {
    if (user_access('score taken quiz answer')) {
      $msg = t('Parts of this @quiz have not been evaluated yet. The score below is not final. <a class="self-score" href="!result_url">Click here</a> to give scores on your own.', array('@quiz' => QUIZ_NAME, '!result_url' => url('node/' . $quiz->nid . '/results/' . $rid)));
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
    t('Your score was: @score %', array('@score' => $score['percentage_score'])) .
    '</div>';

  if (isset($summary['passfail'])) {
    $output .= '<div id="quiz_summary">' . $summary['passfail'] . '</div>' . "\n";
  }
  if (isset($summary['result'])) {
    $output .= '<div id="quiz_summary">' . $summary['result'] . '</div>' . "\n";
  }
  // Get the feedback for all questions.
  $form = drupal_get_form('quiz_report_form', $questions, FALSE, TRUE);
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
  return drupal_render($node->content['body']);
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
