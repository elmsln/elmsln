<?php

/**
 * @file
 * Administration file for Quiz stats Module
 *
 */

/**
 * Page for selecting between several quiz revisions
 *
 * @param $nid
 *  Quiz node id
 * @return
 *  Themed html
 */
function quiz_stats_revision_selector_page($quiz) {
  $res = db_query('SELECT vid FROM {node_revision} WHERE nid = :nid ORDER BY vid', array(':nid' => $quiz->nid));
  $count = 0; //uses this variable to slightly increase performance
  $vids = array();
  while ($res_o = $res->fetch()) {
    $vids[] = $res_o->vid;
    $count++;
  }
  if ($count < 1) {
    return t('Something went wrong. Please try again');
  }
  elseif ($count == 1) {
    // If there is only one revision we jump directly to that revision
    drupal_goto("node/{$quiz->nid}/quiz/statistics/{$vids[0]}");
  }
  else {
    $content = array();
    $content['explanation'] = t('There are !num revisions of this quiz that have been taken.
    Different revisions may have different scoring, difficulity and other differences affecting its statistics.
    Because of this you have to choose the revision you want to see statistics from.', array('!num' => $count));
    $content['links'] = array();
    foreach ($vids as $key => $value) {
      $content['links'][] = 'node/' . $quiz->nid . '/quiz/statistics/' . $value;
    }
    return theme('quiz_stats_revision_selector', array('content' => $content));
  }
}

/**
 * Returns statistics for all available quizzes
 *
 * @param $uid
 *   User id
 * @return
 *   HTML table
 */
function quiz_stats_get_basic_stats($uid = 0) {
  $results = _quiz_get_quizzes($uid);
  return empty($results) ? t('No Statistics found.') : theme('quiz_stats_get_basic_stats', array('results' => $results));
}

/**
 * Get stats for a single quiz. Maybe also for a single user.
 *
 * @param $vid
 *   quiz revision id
 *
 * @param $uid
 *   User id
 *
 * @return
 *   HTML page with charts/graphs
 */
function quiz_stats_get_adv_stats($vid, $uid = 0) {
  $charts = array();
  drupal_add_css(drupal_get_path('module', 'quiz_stats') . '/quiz_stats.css', array('type' => 'file', 'weight' => CSS_THEME));
  $charts['takeup'] = _get_date_vs_takeup_count_chart($vid, $uid);
  // line chart/graph showing quiz takeup date along x-axis and count along y-axis
  $charts['status'] = _get_quiz_status_chart($vid, $uid);
  // 3D pie chart showing percentage of pass, fail, incomplete quiz status
  $charts['top_scorers'] = _get_quiz_top_scorers_chart($vid, $uid);
  // Bar chart displaying top scorers
  $charts['grade_range'] = _get_quiz_grade_range_chart($vid, $uid);
  return theme('quiz_stats_charts', array('charts' => $charts));
}

/**
 * Generates grade range chart
 *
 * @param $uid
 *   User id
 * @param $vid
 *   revision id of quiz node
 * @return
 *   array with chart and metadata
 */
function _get_quiz_grade_range_chart($vid, $uid = 0) {
  // @todo: make the ranges configurable
  $sql = 'SELECT SUM(score >= 0 && score < 20) AS zero_to_twenty,
    SUM(score >= 20 && score < 40) AS twenty_to_fourty,
    SUM(score >= 40 && score < 60) AS fourty_to_sixty,
    SUM(score >= 60 && score < 80) AS sixty_to_eighty,
    SUM(score >= 80 && score <= 100) AS eighty_to_hundred
    FROM {quiz_node_results}
    WHERE vid = :vid';
  $arg[':vid'] = $vid;
  if ($uid != 0) {
    $sql .= ' AND uid = :uid';
    $arg[':uid'] = $uid;
  }
  $range = db_query($sql, $arg)->fetch();
  $count = $range->zero_to_twenty + $range->twenty_to_fourty + $range->fourty_to_sixty + $range->sixty_to_eighty + $range->eighty_to_hundred;
  if ($count < 2) {
    return FALSE;
  }
  // Get the charts
  $chart = '<div id="quiz_top_scorers" class="quiz-stats-chart-space">';
  $chart .= theme('quiz_grade_range', array('range' => $range));
  $chart .= '</div>';
  // Return the chart with some meta data
  return array(
    'chart' => $chart,
    'title' => t('Distribution'),
    'explanation' => t('This chart shows the distribution of the scores on this quiz.'),
  );
}

/**
 * Generates the top scorers chart
 *
 * @param $vid
 *   revision id of quiz node
 *
 * @param $uid
 *   User id
 *
 * @return
 *   array with chart and metadata
 */
function _get_quiz_top_scorers_chart($vid, $uid = 0) {
  $top_scorers = array();
  $sql = 'SELECT name, score FROM {quiz_node_results} qnr
    LEFT JOIN {users} u ON (u.uid = qnr.uid)
    WHERE vid = :vid';
  $arg[':vid'] = $vid;
  if ($uid != 0) {
    $sql .= ' AND qnr.uid = :uid';
    $arg[':uid'] = $uid;
  }
  $sql .= ' ORDER by score DESC LIMIT 10';
  $results = db_query($sql, $arg);
  while ($result = $results->fetchAssoc()) {
    $key = $result['name'] . '-' . $result['score'];
    $top_scorers[$key] = $result;
  }
  if (count($top_scorers) == 0) {
    return FALSE;
  }
  $chart = '<div id="quiz_top_scorers" class="quiz-stats-chart-space">';
  $chart .= theme('quiz_top_scorers', array('scorer' => $top_scorers));
  $chart .= '</div>';
  return array(
    'chart' => $chart,
    'title' => t('Top scorers'),
    'explanation' => t('This chart shows which quiz takers have the highest scores.'),
  );
}

/**
 * Generates a chart showing the status for all registered responses to a quiz
 *
 * @param $vid
 *   revision id of quiz node
 *
 * @param $uid
 *   User id
 *
 * @return
 *   HTML to render to chart/graph
 */
function _get_quiz_status_chart($vid, $uid = 0) {
  // get the pass rate of the given quiz by vid
  $pass_rate = db_query("SELECT pass_rate FROM {quiz_node_properties} WHERE vid = :vid", array(':vid' => $vid))->fetchField();
  if (!$pass_rate) {
    return;
  }
  // get the count value of results row above and below pass rate
  $quiz = db_query("SELECT SUM(score >= $pass_rate) AS no_pass, SUM(score < $pass_rate) AS no_fail, SUM(is_evaluated = 0) AS no_incomplete FROM {quiz_node_results} WHERE vid = :vid", array(':vid' => $vid))
    ->fetchAssoc();
  if (($quiz['no_pass'] + $quiz['no_fail'] + $quiz['no_incomplete']) < 1) {
    return FALSE; // no sufficient data
  }
  // generates quiz status chart 3D pie chart
  $chart = '<div id="get_quiz_status_chart" class="quiz-stats-chart-space">';
  $chart .= theme('get_quiz_status_chart', array('quiz' => $quiz));
  $chart .= '</div>';
  return array(
    'chart' => $chart,
    'title' => t('Status'),
    'explanation' => t('This chart shows the status for all attempts made to answer this revision of the quiz.'),
  );
}

/**
 * Generates chart showing how often the quiz has been taken the last days
 *
 * @param $uid
 *   user id
 * @param $vid
 *   revision id of quiz
 * @return
 *   HTML to display chart
 */
function _get_date_vs_takeup_count_chart($vid, $uid = 0) {
  $start = 0;
  $end = 30;
  $takeup = array();
  $sql = "SELECT COUNT(result_id) AS count,
            DATE_FORMAT(FROM_UNIXTIME(time_start), '%Y-%m-%e') AS date
            FROM {quiz_node_results}
            WHERE vid = :vid AND time_start > (UNIX_TIMESTAMP(NOW()) - (86400*$end))";
  $sql_args[':vid'] = $vid;
  if ($uid != 0) {
    $sql .= " AND uid = :uid";
    $sql_args[':uid'] = $uid;
  }
  $sql .= " GROUP BY date ORDER BY time_start ASC";
  $results = db_query($sql, $sql_args);
  $res_o = $results->fetchAll();
  if ($res_o) {
    $chart = '<div id="date_vs_takeup_count" class="quiz-stats-chart-space">';
    // wrapping the chart output with div for custom theming.
    $chart .= theme('date_vs_takeup_count', array('takeup' => $res_o));
    // generate date vs takeup count line chart
    $chart .= '</div>';
    return array(
      'chart' => $chart,
      'title' => t('Activity'),
      'explanation' => t('This chart shows how many times the quiz has been taken each day over the last !days days.', array('!days' => $end)),
    );
  }
}

/**
 * Computes quiz attempt count
 *
 * @param $vid
 *   quiz node id
 * @param $uid
 *   user id for filtering
 * @return
 *   Integer containing number of times that a quiz has
 *   been attended, can be filtered by uid.
 */
function _quiz_get_attempt_count($nid, $uid = 0) {
  $sql = 'SELECT COUNT(result_id) FROM {quiz_node_results} WHERE nid = :nid';
  $arg[':nid'] = $nid;
  if ($uid != 0) {
    $sql .= ' AND uid = :uid';
    $arg[':uid'] = $uid;
  }
  return db_query($sql, $arg)->fetchField();
}

// Theme functions

/**
 * Theme function for quiz grade range chart generates Chart using CHART API function
 *
 * @param $range
 *   array containg quiz results data structure
 *
 * @return
 *   HTML to render/display chart
 */
function theme_quiz_grade_range($variables) {
  $range = $variables['range'];

  $max = max((array) $range);
  $count = array_sum((array) $range);

  $chart = array(
    '#type' => 'chart',
    '#chart_type' => 'column',
    '#title' => t('Score distribution'),
  );
  $chart['range'] = array(
    '#type' => 'chart_data',
    '#title' => t('% of quiz takers'),
    '#data' => array(
      round(($range->zero_to_twenty / $count) * 100),
      round(($range->twenty_to_fourty / $count) * 100),
      round(($range->fourty_to_sixty / $count) * 100),
      round(($range->sixty_to_eighty / $count) * 100),
      round(($range->eighty_to_hundred / $count) * 100),
    ),
  );
  $chart['xaxis'] = array(
    '#title' => t('Score'),
    '#type' => 'chart_xaxis',
    '#labels' => array(
      '0-20%',
      '20-40%',
      '40-60%',
      '60-80%',
      '80-100%',
    ),
  );
  $chart['yaxis'] = array(
    '#title' => t('Grade istribution'),
    '#type' => 'chart_yaxis',
    '#max' => 100,
  );
  return drupal_render($chart);
}

/**
 * generates a chart of quiz top scorers
 *
 * @param $attendees
 *   array containing quiz data structure
 *
 * @return
 *   HTML to render quiz top scorers chart
 */
function theme_quiz_top_scorers($variables) {
  $attendees = array_reverse($variables['scorer']);
  $chart = array(
    '#type' => 'chart',
    '#title' => t('Quiz Top Scorers'),
    '#chart_type' => 'column',
  );
  $chart['bar_data'] = array(
    '#type' => 'chart_data',
    '#title' => 'Result',
  );
  foreach ($attendees as $attendee) {
    $chart['bar_data']['#data'][] = (float) $attendee['score'];
    $labels[] = $attendee['name'] . ' ' . $attendee['score'] . '%';

  }
  $chart['yaxis'] = array(
    '#title' => t('Score') . ' (%)',
    '#type' => 'chart_yaxis',
    '#max' => 100,
  );
  $chart['xaxis'] = array(
    '#title' => 'Quiz Attendees',
    '#type' => 'chart_xaxis',
    '#labels' => $labels,

  );
  return drupal_render($chart);
}

/**
 * generates quiz status chart number of pass, fail, incomplete
 *
 * @param $quiz
 *   array of quiz data structure
 *
 * @return
 *   HTML to render quiz status chart
 */
function theme_get_quiz_status_chart($variables) {
  $quiz = $variables['quiz'];
  $quiz['total'] = $quiz['no_pass'] + $quiz['no_fail'] + $quiz['no_incomplete'];

  $chart = array(
    '#type' => 'chart',
    '#title' => t('Quiz results'),
    '#chart_type' => 'pie',
  );

  $chart['pie_data'] = array(
    '#type' => 'chart_data',
    '#title' => t('Result'),
    '#labels' => array('Pass', 'Incomplete', 'Fail'),
    '#data' => array(
      (int) $quiz['no_pass'],
      (int) $quiz['no_incomplete'],
      (int) $quiz['no_fail']
    ),
  );
  return drupal_render($chart);
}

/**
 * Generates date vs takeup count chart
 *
 * @param $takeup
 *   Array quiz data structure
 * @return
 *   HTML to render/display chart
 */
function theme_date_vs_takeup_count($variables) {
  $chart = array(
    '#type' => 'chart',
    '#title' => t('Activity by date'),
    '#chart_type' => 'line',
  );

  $chart['line_data'] = array(
    '#type' => 'chart_data',
    '#title' => t('Result'),
    '#labels' => array('Something'),
  );

  $chart['line_data']['#data'] = array();
  $labels = array();
  foreach ($variables['takeup'] as $point) {
    $chart['line_data']['#data'][] = (int) $point->count;
    $labels[] = $point->date;
  }

  $chart['xaxis'] = array(
    '#type' => 'chart_xaxis',
    '#labels' => $labels,
  );
  $chart['yaxis'] = array(
    '#title' => 'Participants',
    '#type' => 'chart_yaxis',
  );
  return drupal_render($chart);
}

/**
 * Generates table of results from quiz data structure.
 *
 * @param @results
 *   Array containing quiz results data structure
 * @return
 *   HTML table containing quiz title, author, questions count, attempt count
 */
function theme_quiz_stats_get_basic_stats($variables) {
  $results = $variables['results'];
  if (empty($results)) {
    return '<p>' . t('No questions were found.') . '</p>';
  }
  $header = $rows = array();
  $header = array(
    'title' => t('Quiz'),
    'creator' => t('Author'),
    'created' => t('Created'),
  );
  if (user_access('access author stats')) {
    $header['questions_count'] = t('Questions');
    $header['attempt_count'] = t('Attempts');
  }
  $p = drupal_get_path('module', 'quiz_stats');
  $chart_icon = theme('image', array('path' => "$p/chart.png", 'width' => t('Charts'), 'height' => t('See charts')));
  foreach ($results as $result) {
    $title_link = user_access('access author stats') ? 'node/' . $result['nid'] . '/quiz/statistics' : 'user/' . arg(1) . '/stats/';
    $row = array(
      'title' => l($chart_icon . ' ' . $result['title'], $title_link, array('html' => TRUE)),
      'creator' => l($result['name'], 'user/' . $result['uid']),
      'created' => format_date($result['created'], 'short'),
    );
    if (user_access('access author stats')) {
      $row['questions_count'] = quiz_get_number_of_questions($result['vid'], $result['nid']);
      $row['attempt_count'] = _quiz_get_attempt_count($result['nid']);
    }
    $rows[] = $row;
  }
  module_load_include('inc', 'quiz', 'quiz.pages');
  $cc = '<em>' . t('Chart icon from !url', array('!url' => 'pinvoke.com')) . '</em>';
  return theme('table', array('header' => $header, 'rows' => $rows, 'attributes' => array('id' => 'tablesorter'))) . $cc;
}
