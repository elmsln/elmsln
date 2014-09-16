<?php
/**
 * @file
 * Provides the charts definitions.
 */

function analytics_dashboard_charts() {
  $period = _get_time_from_url();
  $from = isset($period[0]) ? $period[0] : strtotime('-1 month');
  $to   = isset($period[1]) ? $period[1] : time();
  $header = $nodes = $comments = $votes = $users = array();
  //==================================
  // Chart for Nodes created per day.
  //==================================
  if (module_exists('node')) {
    $i = 0;
    $f = $from;
    while ($f <= $to) {
      // Building the header - list of date from today backward.
      $header[$i] = date('d.m.y', $f);
      // The number of nodes created each day.
      $nodes[$i] = db_query("SELECT COUNT(*) FROM {node} WHERE FROM_UNIXTIME(created,'%d.%m.%y') = :dete", array(':dete' => $header[$i]))->fetchField();
      $i++;
      $f = strtotime("+1 day", $f);
    }
    // Building the rows, array of the data point arrays.
    $rows = array($nodes);
    // The labels for the rows.
    $columns = array('No. Of Contents');

    // Put all the data into the settings array,
    // which will be send to draw.

    // Must empty the array first.
    $settings = array();
    $settings['chart']['chartNodes'] = array(  
      'header' => $header,
      'rows' => $rows,
      'columns' => $columns,
      'chartType' => GOOGLE_CHART_TOOLS_DEFAULT_CHART,
      'options' => array( // Optionals.
        'curveType' => "function",
        'forceIFrame' => FALSE,
        'title' => 'Content created per day',
        'width' => 500,
        'height' => 300
      )
    );

    // Draw it.
    $ret[] = draw_chart($settings);
  }
  //=====================================
  // Chart for comments created per day.
  //=====================================
  if (module_exists('comment')) {
    $i = 0;
    $f = $from;
    while ($f <= $to) {
      // Building the header - list of date from today backward.
      $header[$i] = date('d.m.y', $f);
      // The number of comments created each day.
      $comments[$i] = db_query("SELECT COUNT(*) FROM {comment} WHERE FROM_UNIXTIME(created,'%d.%m.%y') = :dete", array(':dete' => $header[$i]))->fetchField();
      // The number of voted placed each day.
      $i++;
      $f = strtotime("+1 day", $f);
    }
    // Building the rows, array of the data point arrays.
    $rows = array($comments);
    // The labels for the rows.
    $columns = array('No. Of Comments');

    // Put all the data into the settings array,
    // which will be send to draw.

    // Must empty the array first.
    $settings = array();
    $settings['chart']['chartComments'] = array(
      'header' => $header,
      'rows' => $rows,
      'columns' => $columns,
      'chartType' => GOOGLE_CHART_TOOLS_DEFAULT_CHART,
      'options' => array( // Optionals.
        'curveType' => "function",
        'colors' => array('green'),
        'forceIFrame' => FALSE,
        'title' => 'Comments created per day',
        'width' => 500,
        'height' => 300
      )
    );

    // Draw it.
    $ret[] = draw_chart($settings);
  }
  //=====================================
  // Chart for votes placed per day.
  //=====================================
  if (module_exists('votingapi')) {
    $i = 0;
    $f = $from;
    while ($f <= $to) {
      // Building the header - list of date from today backward.
      $header[$i] = date('d.m.y', $f);
      // The number of voted placed each day.
      $votes[$i] = db_query("SELECT COUNT(*) FROM {votingapi_vote} WHERE  FROM_UNIXTIME(timestamp,'%d.%m.%y') = :dete", array(':dete' => $header[$i]))->fetchField();
      $i++;
      $f = strtotime("+1 day", $f);
    }
    // Building the rows, array of the data point arrays.
    $rows = array($votes);
    // The labels for the rows.
    $columns = array('No. Of Votes');

    // Put all the data into the settings array,
    // which will be send to draw.

    // Must empty the array first.
    $settings = array();
    $settings['chart']['chartVotes'] = array(
      'header' => $header,
      'rows' => $rows,
      'columns' => $columns,
      'chartType' => GOOGLE_CHART_TOOLS_DEFAULT_CHART,
      'options' => array( // Optionals.
        'curveType' => "function",
        'colors' => array('purple'),
        'forceIFrame' => FALSE,
        'title' => 'Votes placed per day',
        'width' => 500,
        'height' => 300
      )
    );

    // Draw it.
    $ret[] = draw_chart($settings);
  }
  //=====================================
  // Chart for user joind per day.
  //=====================================
  if (module_exists('user')) {
    $i = 0;
    $f = $from;
    while ($f <= $to) {
      // Building the header - list of date from today backward.
      $header[$i] = date('d.m.y', $f);
      // The number of users join each day.
      $users[$i] = db_query("SELECT COUNT(*) FROM {users} WHERE  FROM_UNIXTIME(created,'%d.%m.%y') = :dete", array(':dete' => $header[$i]))->fetchField();
      $i++;
      $f = strtotime("+1 day", $f);
    }
    // Building the rows, array of the data point arrays.
    $rows = array($users);
    // The labels for the rows.
    $columns = array('No. Of Users');

    // Put all the data into the settings array,
    // which will be send to draw.

    // Must empty the array first.
    $settings = array();
    $settings['chart']['chartUsers'] = array(  
      'header' => $header,
      'rows' => $rows,
      'columns' => $columns,
      'chartType' => GOOGLE_CHART_TOOLS_DEFAULT_CHART,
      'options' => array( // Optionals.
        'curveType' => "function",
        'colors' => array('orange'),
        'forceIFrame' => FALSE,
        'title' => 'Users joined per day',
        'width' => 500,
        'height' => 300
      )
    );

    // Draw it.
    $ret[] = draw_chart($settings);
  }
  //=====================================
  // Chart for content by tags.
  //=====================================
  if (module_exists('taxonomy') && array_key_exists('tags', taxonomy_vocabulary_get_names())) {
    $voc = taxonomy_vocabulary_machine_name_load('tags');
    $tree = taxonomy_get_tree($voc->vid);
    $header = array();
    foreach ($tree as $term) {
      $header[] = $term->name;
      $query = db_select('taxonomy_index', 'ti');
      $query->condition('ti.tid', $term->tid, '=')
            ->fields('ti', array('nid'));
      $terms[] = $query->countQuery()->execute()->fetchField();
    }
    $columns = array('Content by Tags');
    $rows = isset($terms) ? array($terms) : array();

    $settings = array();
    $settings['chart']['chartTag'] = array(
      'header' => $header,
      'rows' => $rows,
      'columns' => $columns,
      'chartType' => 'PieChart',
      'options' => array( // Optionals.
        'curveType' => "function",
        'is3D' => TRUE,
        'forceIFrame' => FALSE,
        'title' => 'Content by Tags',
        'width' => 500,
        'height' => 300
      )
    );

    // Draw it.
    $ret[] = draw_chart($settings);
  }
  return $ret;
}