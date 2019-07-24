<?php

/**
 * @file quiz.theme.inc
 * Quiz theme functions.
 */

/**
 * Pass the correct mark to the theme so that theme authors can use an image.
 *
 * @ingroup themeable
 */
function theme_quiz_answer_result($variables) {
  $options = array();
  $type = $variables['type'];

  switch ($type) {
    case 'correct':
      $options['path'] = 'check_008000_64.png';
      $options['alt'] = t('Correct');
      break;

    case 'incorrect':
      $options['path'] = 'times_ff0000_64.png';
      $options['alt'] = t('Incorrect');
      break;

    case 'unknown':
      $options['path'] = 'question_808080_64.png';
      $options['alt'] = t('Unknown');
      break;

    case 'should':
      $options['path'] = 'check_808080_64.png';
      $options['alt'] = t('Should have chosen');
      break;

    case 'should-not':
      $options['path'] = 'times_808080_64.png';
      $options['alt'] = t('Should not have chosen');
      break;

    case 'almost':
      $options['path'] = 'check_ffff00_64.png';
      $options['alt'] = t('Almost');
      break;

    case 'selected':
      $options['path'] = 'arrow-right_808080_64.png';
      $options['alt'] = t('Selected');
      break;

    case 'unselected':
      $options['path'] = 'circle-o_808080_64.png';
      $options['alt'] = t('Unselected');
      break;

    default:
      $options['path'] = '';
      $options['alt'] = '';
  }

  if (!empty($options['path'])) {
    $options['path'] = drupal_get_path('module', 'quiz') . '/images/' . $options['path'];
  }
  if (!empty($options['alt'])) {
    $options['title'] = $options['alt'];
  }

  $image = theme('image', $options);
  return '<div class="quiz-score-icon ' . $type . '">' . $image . '</div>';
}

/**
 * Theme a progress indicator for use during a quiz.
 *
 * @param $question_number
 *   The position of the current question in the sessions' array.
 * @param $num_of_question
 *   The number of questions for this quiz as returned by
 *   quiz_get_number_of_questions().
 *
 * @return
 *   Themed html.
 *
 * @ingroup themeable
 */
function theme_quiz_progress($variables) {
  drupal_add_js(drupal_get_path('module', 'quiz') . '/js/quiz.jumper.js');
  $output = '';
  $output .= '<div id="quiz-progress">';
  $text = 'Page <span id="quiz-question-number">!x</span> of <span id="quiz-num-questions">@y</span>';

  if ($variables['allow_jumping']) {
    // Show jump form.
    if ($variables['pager']) {
      $output .= theme('quiz_pager', array(
        'siblings' => variable_get('quiz_pager_siblings', 5),
        'current' => $variables['current'],
        'total' => count($variables['questions']),
      ));
    }
    else {
      $selectbox = drupal_get_form('quiz_jumper_form', $variables['questions'], $variables['current']);
      $output .= t($text, array('!x' => drupal_render($selectbox), '@y' => count($variables['questions'])));
    }
  }
  else {
    // Just text.
    $output .= t($text, array('!x' => $variables['current'], '@y' => count($variables['questions'])));
  }

  $output .= '</div>' . "\n";
  return $output;
}

/**
 * Theme the stats on the views page.
 *
 * @param $node
 *   The quiz node.
 */
function theme_quiz_view_stats($variables) {
  $node = $variables['node'];
  // Fetch data.
  $stats = array(
    array(
      array('header' => TRUE, 'width' => '25%', 'data' => t('Questions')),
      $node->number_of_questions,
    ),
  );
  if ($node->show_attempt_stats) {
    $takes = $node->takes == 0 ? t('Unlimited') : $node->takes;
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Attempts allowed')),
      $takes,
    );
  }
  if ($node->quiz_always) {
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Available')),
      t('Always'),
    );
  }
  else {
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Opens')),
      format_date($node->quiz_open, 'short'),
    );
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Closes')),
      format_date($node->quiz_close, 'short'),
    );
  }
  if (!empty($node->pass_rate)) {
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Pass rate')),
      $node->pass_rate . ' %',
    );
  }
  if (!empty($node->time_limit)) {
    $stats[] = array(
      array('header' => TRUE, 'data' => t('Time limit')),
      _quiz_format_duration($node->time_limit),
    );
  }
  $stats[] = array(
    array('header' => TRUE, 'data' => t('Backwards navigation')),
    $node->backwards_navigation ? t('Allowed') : t('Forbidden'),
  );

  return theme('table', array('attributes' => array('id' => 'quiz-view-table'), 'rows' => $stats));
}

/**
 * Help us with special pagination.
 *
 * Why not the Drupal theme_pager()?
 *
 * It uses query strings. We have access on each menu argument (quiz question
 * number) so we unfortunately cannot use it.
 */
function _quiz_pagination_helper($total, $perpage = NULL, $current = NULL, $siblings = NULL) {
  $result = array();

  if (isset($total, $perpage) === TRUE) {
    $result = range(1, ceil($total / $perpage));

    if (isset($current, $siblings) === TRUE) {
      if (($siblings = floor($siblings / 2) * 2 + 1) >= 1) {
        $result = array_slice($result, max(0, min(count($result) - $siblings, intval($current) - ceil($siblings / 2))), $siblings);
      }
    }
  }

  return $result;
}

/**
 * Theme the quiz pager.
 */
function theme_quiz_pager($variables) {
  $total = $variables['total'];
  $current = $variables['current'];
  $siblings = $variables['siblings'];
  $items = array();
  $nid = arg(1);
  $items[] = array(
    'class' => array('pager-first'),
    'data' => l(t('first'), "node/$nid/take/1"),
  );
  foreach (_quiz_pagination_helper($total, 1, $current, $siblings) as $i) {
    if ($i == $current) {
      $items[] = array(
        'class' => array('pager-current'),
        'data' => $i,
      );
    }
    else {
      $items[] = array(
        'class' => array('pager-item'),
        'data' => l($i, "node/$nid/take/$i"),
      );
    }
  }
  $items[] = array(
    'class' => array('pager-last'),
    'data' => l(t('last'), "node/$nid/take/$total"),
  );
  return theme('item_list', array('items' => $items, 'attributes' => array('class' => array('pager'))));
}

/**
 * Themes a categorized quiz form.
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
    $output .= theme('table', array(
      'header' => $header,
      'rows' => $rows,
      'attributes' => array('id' => 'existing-terms'),
    ));
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
    }};}(jQuery));",
    array('type' => 'inline', 'group' => JS_DEFAULT));
  return $output;
}

/**
 * Theme a question selection table, adding drag and drop support.
 */
function theme_question_selection_table($variables) {
  $form = $variables['form'];
  drupal_add_tabledrag('question-list', 'match', 'parent', 'qnr-pid', 'qnr-pid', 'qnr-id', TRUE, 1);
  drupal_add_tabledrag('question-list', 'order', 'sibling', 'question-list-weight');

  // Building headers.
  $headers = array(
    t('Question'),
    t('Type'),
    t('Actions'),
    t('Update'),
    t('Max score'),
    t('Auto update max score'),
    t('Delete'),
  );
  if (isset($form['compulsories'])) {
    $headers[] = t('Compulsory');
  }
  $headers[] = t('Weight');
  $headers[] = t('Parent ID');
  $headers[] = array(
    'data' => t('ID'),
    'class' => array('tabledrag-hide'),
  );

  // Building table body.
  $rows = array();
  if (!empty($form['titles'])) {
    foreach (element_children($form['titles']) as $id) {
      $form['weights'][$id]['#attributes']['class'] = array('question-list-weight');
      $form['qnr_ids'][$id]['#attributes']['class'] = array('qnr-id');
      $form['qnr_pids'][$id]['#attributes']['class'] = array('qnr-pid');
      $rows[] = _quiz_get_question_row($form, $id);
    }
    // Make sure the same fields aren't rendered twice.
    unset($form['types'], $form['view_links'], $form['remove_links'], $form['stayers']);
    unset($form['max_scores'], $form['auto_update_max_scores'], $form['revision'], $form['weights'], $form['titles'], $form['compulsories'], $form['qnr_ids'], $form['qnr_pids']);
  }
  $html_attr = array('id' => 'question-list');

  // We hide the table if no questions have been added so that jQuery can show
  // it the moment the first question is beeing added.
  if (isset($form['no_questions'])) {
    $html_attr['style'] = "display:none;";
  }

  $table = theme('table', array(
    'header' => $headers,
    'rows' => $rows,
    'attributes' => $html_attr
  ));

  return drupal_render($form['random_settings'])
    . $table
    . drupal_render_children($form);
}

/**
 * Theme the quiz questions admin page.
 */
function theme_quiz_questions_page($variables) {
  // Set page title.
  drupal_set_title($variables['node']->title);
  return $variables['form'];
}
