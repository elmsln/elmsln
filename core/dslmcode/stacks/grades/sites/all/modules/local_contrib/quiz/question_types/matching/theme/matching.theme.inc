<?php

/**
 * @file
 * Theme functions for the matching question type.
 */

/**
 * Theme the matching question form.
 *
 * @param $variables
 *
 * @return string
 *   An HTML string.
 */
function theme_matching_question_form($variables) {
  $form = $variables['form'];
  $rows = array();
  $header = array(
    'question' => t('Question'),
    'answer' => t('Correct answer'),
    'feedback' => t('Feedback'),
  );
  foreach (element_children($form) as $key) {
    $rows[] = array(
      'question' => drupal_render($form[$key]['question']),
      'answer' => drupal_render($form[$key]['answer']),
      'feedback' => drupal_render($form[$key]['feedback']),
    );
  }
  // Theme output and display to screen.
  return theme('table', array('header' => $header, 'rows' => $rows));
}

/**
 * Theme the answering form.
 *
 * @param $variables
 *
 * @return string
 *   An HTML string.
 */
function theme_matching_subquestion_form($variables) {
  $form = $variables['form'];
  $out = '<table class = "matching-tbl">';
  foreach ($form as $key => $value) {
    if (is_int($key)) {
      $out .= '<tr><td class = "matching-question">' . $value['#question'];
      $out .= '</td><td class = "matching-select">' . drupal_render_children($value) . '</td></tr>';
    }
  }
  $out .= '</table>';
  return $out;
}

/**
 * Theme the answer part of the node view.
 *
 * @param $variables
 *
 * @return string
 *   An HTML string.
 */
function theme_matching_match_node_view($variables) {
  $subquestions = $variables['subquestions'];
  // We know the correct answer for each subquestion.
  if (isset($subquestions[0]['correct'])) {
    $header = array(t('Subquestion'), t('Correct match'), t('Feedback'));
  }
  // We do not know the correct answer for each subquestion.
  else {
    $header = array(t('Subquestion'), t('Possible match'));
  }
  return theme('table', array('header' => $header, 'rows' => $subquestions));
}

/**
 * Theme the contents of the matching response form.
 *
 * @param $variables
 *
 * @return string
 *   An HTML string.
 */
function theme_matching_response($variables) {
  $metadata = $variables['metadata'];
  $data = $variables['data'];
  if (isset($data[0]['is_correct'])) {
    foreach ($data as $id => $match_data) {
      if ($match_data['is_correct'] == 0) {
        $theme = 'quiz_score_incorrect';
      }
      if ($match_data['is_correct'] == 1) {
        $theme = 'quiz_score_correct';
      }
      if ($match_data['is_correct'] == 2) {
        $theme = 'quiz_score_unknown';
      }
      // TODO Please change this theme call to use an associative array for the $variables parameter.
      $data[$id]['is_correct'] = array(
        'data' => theme($theme),
        'class' => 'quiz-summary-qcell',
      );
    }
  }
  return theme('table', array('header' => $metadata, 'rows' => $data));
}
