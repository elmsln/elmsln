<?php

/**
 * Callback for apps/game-show-scoreboard/options.
 */
function _game_show_scoreboard_options($machine_name, $app_route, $params, $args) {
  // load a list of sections for the active user
  $sections = array();
  $field_conditions = array();
  $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
  if (isset($filter['section'])) {
    $property_conditions['nid'] = array($filter['section'], '=');
  }
  $orderby = array('field_cis_active' => array('value', 'DESC'));
  $sections = _cis_connector_assemble_entity_list('node', 'section', 'nid', '_entity', $field_conditions, $property_conditions, $orderby);
  

  return array(
    'status' => 200,
    'data' => array(
      'sections' => $sections,
      'games' => $jeopardys,
    ),
  );
}

/**
 * Callback for apps/game-show-scoreboard/data.
 */
function _game_show_scoreboard_data($machine_name, $app_route, $params, $args) {
  // connect to the database table
  // return data like this per row
  $rows = array();
  $result = db_select('game_show_quiz', 'gsq')
    ->fields('gsq');
    if (isset($args['game'])) {
      $result->condition('game', $args['game'], '=');
    }
    if (isset($args['section'])) {
      $result->condition('section', $args['section'], '=');
    }
    $result->execute()
    ->fetchAssoc();
  foreach ($result as $values) {
    $usr = user_load($values['uid']);
    $scores = json_decode($values['scores']);
    $row = array(
      "high" => max($scores),
      "dates" => $values['dates'],
      "scores" => implode(', ', $scores),
      "display_name" => _elmsln_core_get_user_name('full', $values['uid']),
      "avatar" => _elmsln_core_get_user_picture('avatar', $values['uid']),
      "visual" => _elmsln_core_get_user_extras($values['uid']),
      "sis" => _elmsln_core_get_sis_user_data($values['uid']),
    );
    $rows[] = $row;
  }
  return array(
    'status' => 200,
    'data' => $data,
  );
}