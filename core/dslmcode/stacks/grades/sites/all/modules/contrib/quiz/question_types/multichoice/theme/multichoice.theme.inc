<?php

/**
 * The theme file for multichoice.
 *
 * Sponsored by: Norwegian Centre for Telemedicine
 * Code: falcon
 *
 * @file
 * Theming functions for the multichoice question type.
 */

/**
 * Theme the creation form.
 */
function theme_multichoice_creation_form($variables) {
  $form = $variables['form'];
  $path = drupal_get_path('module', 'multichoice') . '/multichoice.js';
  drupal_add_js($path);

  // We open the settings fieldset if there is errors involving the choice_multi setting
  $errors = form_get_errors();
  if (isset($errors['choice_multi'])) {
    $form['settings']['#collapsed'] = FALSE;
  }

  // We open the alternative fieldsets if errors have been reported
  if ($errors) {
    for ($i = 0; isset($form[$i]) && is_array($form[$i]); $i++) {
      if (drupal_strlen(strip_tags($_POST['alternatives'][$i]['answer']['value'])) > 0) {
        $form[$i]['#collapsed'] = FALSE;
      }
    }
  }
  return drupal_render_children($form);
}

/**
 * Theme the answer part of the node view
 *
 * @param $alternatives
 *  Array of alternatives. Each alternative is also an array with all the
 *  data for each alternative.
 * @param $show_correct
 *  True if the user is allowed to view the solution
 */
function theme_multichoice_answer_node_view($variables) {
  $alternatives = $variables['alternatives'];
  $show_correct = $variables['show_correct'];
  $header = array('', '');

  foreach ($alternatives as $i => $short) {
    $answer_markup = check_markup($short['answer']['value'], $short['answer']['format']);
    // Find the is_correct status
    $is_correct = ($short['score_if_chosen'] > $short['score_if_not_chosen']);
    $image = $is_correct ? 'correct' : 'wrong';
    if (!$show_correct) {
      $image = 'unknown';
    }

    $rows[] = array(
      array(
        'data' => array(
          '#theme' => 'html_tag',
          '#tag' => 'span',
          '#attributes' => array(
            'class' => array(
              'multichoice-icon',
              $image,
            ),
            'title' => $show_correct ?
              t('Score if chosen: @sc Score if not chosen: @nc', array(
                '@sc' => $short['score_if_chosen'],
                '@nc' => $short['score_if_not_chosen'])
              ) :
              t('You are not allowed to view the solution for this question'),
          ),
        ),
        'class' => array('multichoice-icon-cell'),
      ),
      $answer_markup
    );
  }
  return theme('table', array('header' => $header, 'rows' => $rows));
}
