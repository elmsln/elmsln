<?php

/**
 * @file
 * Theming the charts page
 *
 * Variables available:
 * $charts (array)
 *
 * The following charts are available:
 * $charts['top_scorers'] (array or FALSE if chart doesn't exist)
 * $charts['takeup'] (array or FALSE if chart doesn't exist)
 * $charts['status'] (array or FALSE if chart doesn't exist)
 * $charts['grade_range'] (array or FALSE if chart doesn't exist)
 *
 * Each chart has a title, an image and an explanation like this:
 * $charts['top_scorers']['title'] (string)
 * $charts['top_scorers']['chart'] (string - img tag - google chart)
 * $charts['top_scorers']['explanation'] (string)
 */
$chart_found = FALSE;
if (!function_exists('_quiz_stats_print_chart')) {
  function _quiz_stats_print_chart(&$chart) {
    if (is_array($chart)) {
      echo '<h2 class="quiz-charts-title">' . $chart['title'] . '</h2>' . "\n"
         . $chart['chart']. "\n"
         . $chart['explanation'] . "\n";
      $chart_found = TRUE;
    }
  }
}
_quiz_stats_print_chart($charts['takeup']);
_quiz_stats_print_chart($charts['top_scorers']);
_quiz_stats_print_chart($charts['status']);
_quiz_stats_print_chart($charts['grade_range']);
if (!$chart_found) {
  echo t('There are no statistics for this quiz (or quiz revision). This is probably because nobody has yet run this quiz (or quiz revision). If the quiz has multiple revisions, it is possible that the other revisions do have statistics. If this is the last revision, taking the quiz should generate some statistics.');
}
?>
