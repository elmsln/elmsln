<?php

/**
 * @file
 * Theme functions for cloze.
 */
function theme_cloze_user_answer($variables) {
  $header = array(t('Correct Answer'), t('User Answer'));
  $row = array(array($variables['correct'], $variables['answer']));
  $output = theme('table', array('header' => $header, 'rows' => $row));
  return $output;
}

/**
 * Theme the cloze response form
 */
function theme_cloze_response_form(&$variables) {
  $form = &$variables['form'];
  return drupal_render_children($form);
}

/**
 * Theme the cloze answering form
 */
function theme_cloze_answering_form(&$variables) {
  $form = &$variables['form'];
  unset($form['question']);
  drupal_add_css(drupal_get_path('module', 'cloze') . '/theme/cloze.css');
  return drupal_render_children($form);
}

