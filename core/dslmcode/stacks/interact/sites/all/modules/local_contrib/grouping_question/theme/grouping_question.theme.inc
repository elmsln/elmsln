<?php

/**
 * @file
 */

/**
 * Theme the response part of the response report
 *
 * @param array $vars
 *   'data' array Each element is a group array containing the following keys:
 *     - user_answers (optional) string A comma separated list of user answers.
 *     - correct_answers string a comma separated list of the correct answers
 *       for that group.
 *     - name string The name of the group.
 *     - feedback string Feedback on that group (Must be clean by this point).
 *   'general_feedback' string General feedback (Must be clean by this point).
 *   'showpoints' boolean TRUE to display the answer and score.
 *   'showfeedback' boolean TRUE to display the feedback.
 */
function theme_grouping_question_response($vars) {
  $display_user_answers = $vars['display_user_answers'];
  $general_feedback = $vars['general_feedback'];
  $showpoints = $vars['showpoints'];
  $showfeedback = $vars['showfeedback'];

  $rows = array();

  foreach ($vars['data'] as $id => $group) {
    $correct_answers_str = '';
    if ($showpoints) {
      $user_answers_str = '';
      $correct_answers = explode(',', $group['correct_answers']);

      if ($display_user_answers) {
        $user_answers = explode(',', $group['user_answers']);
        foreach ($user_answers as $answer) {
          $user_answers_str .= (in_array($answer, $correct_answers) ? $answer : '<strong class="error">' . $answer . '</strong>');
          $user_answers_str .= '<br />';
        }
      }

      foreach ($correct_answers as $correct_answer) {
        $correct_answers_str .= (!$display_user_answers || in_array($correct_answer, $user_answers) ? $correct_answer : '<strong class="error">' . $correct_answer . '</strong>');
        $correct_answers_str .= '<br />';
      }

    }

    $cols = array();

    $cols[] = array(
      'data' => "<span>{$id}. </span>",
      'width' => 35,
    );

    $cols[] = array(
      'data' => $group['name'],
    );

    if ($display_user_answers) {
      $cols[] = array(
        'data' => $user_answers_str,
      );
    }

    if ($showpoints) {
      $cols[] = array(
        'data' => $correct_answers_str,
      );
    }

    if ($showfeedback) {
      $cols[] = array(
        'data' => $group['feedback'],
      );
    }

    $rows[] = $cols;
  }

  $header = array();
  $header[] = array(
    'data' => '',
  );

  $header[] = array(
    'data' => t('Group'),
  );

  if ($display_user_answers) {
    $header[] = array(
      'data' => t('Your answers'),
    );
  }

  if ($showpoints) {
    $header[] = array(
      'data' => t('Correct Answer'),
    );
  }

  if ($showfeedback) {
    $header[] = array(
      'data' => t('Feedback'),
    );
  }

  $output = theme('table', array('header' => $header, 'rows' => $rows));

  if ($showfeedback) {
    $output .= "<p>{$general_feedback}</p>";
  }

  return $output;
}

/**
 * Template preprocessor for the grouping question answer form
 */
function template_preprocess_grouping_question_answer_form_groups(&$vars) {
  $path = drupal_get_path('module', 'grouping_question');
  drupal_add_library('system', 'ui.draggable');
  drupal_add_library('system', 'ui.droppable');
  drupal_add_js($path . '/js/grouping_question.js');
  drupal_add_css($path . '/theme/grouping_question.css', 'module', 'all');

  $vars['members'] = $vars['form']['members']['#value'];
  $vars['answers'] = '';
  $vars['answer_titles'] = array();

  foreach ($vars['form'] as $id => $group) {
    if (is_numeric($id) && intval($id) > 0) {
      $vars['answer_titles'][$id] = $group['user_answers']['#title'];
      $vars['answers'] .= drupal_render($group['user_answers']);
    }
  }
}

/**
 * Template preprocess function to render the creation form for
 * grouping questions
 */
function template_preprocess_grouping_question_creation(&$vars) {
  $rows = array();
  foreach ($vars['form'] as $id => $group) {
    if (is_numeric($id) && intval($id) > 0) {
      $row = array();
      $row[] = array('data' => drupal_render($group['name']));
      $row[] = array('data' => drupal_render($group['members']));
      $row[] = array('data' => '<div class="contain-ckeditor">' . drupal_render($group['feedback']) . '</div>');
      $rows[] = $row;
    }
  }

  $vars['output'] = '';

  if (!empty($rows)) {
    $header[] = array('data' => t('Group name'));
    $header[] = array('data' => t('Items'));
    $header[] = array('data' => t('Feedback'));
    $vars['output'] = theme('table', array('header' => $header, 'rows' => $rows));
  }
}
