<?php

/**
 * Callback for apps/game-show-scoreboard/options.
 */
function _game_show_scoreboard_options($machine_name, $app_route, $params, $args) {
  // load a list of sections for the active user
  $field_conditions = array();
  $property_conditions = array('status' => array(NODE_PUBLISHED, '='));
  $orderby = array('field_cis_active' => array('value', 'DESC'));
  $sections = array_merge(array("" => t("All")), _cis_connector_assemble_entity_list('node', 'section', 'field_section_id', 'title', $field_conditions, $property_conditions, $orderby));
  $jeopardys = array(
    "" => t("All"),
  );
  $query = db_select('game_show_quiz', 'gsq')
    ->fields('gsq', array('game'));
  $result = $query->execute()->fetchAllAssoc('game');
  foreach($result as $values) {
    $jeopardys[$values->game] = $values->game;
  }
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
  $query = db_select('game_show_quiz', 'gsq')
      ->fields('gsq');
    if (isset($params['section']) && $params['section'] != '') {
      $query->condition('section', $params['section'], '=');
    }
    if (isset($params['game']) && $params['game'] != '') {
      $query->condition('game', $params['game'], '=');
    }
    $result = $query->execute()->fetchAllAssoc('uuid');
    foreach($result as $values) {
    $usr = user_load($values->uid);
    $scores = json_decode($values->scores);
    $dates = json_decode($values->dates);
    $row = array(
      "high" => max($scores),
      "dates" => $dates,
      "scores" => $scores,
      "game" => $values->game,
      "section" => $values->section,
      "display_name" => _elmsln_core_get_user_name('full', $values->uid),
      "avatar" => _elmsln_core_get_user_picture('avatar', $values->uid),
      "visual" => _elmsln_core_get_user_extras($values->uid),
      "sis" => _elmsln_core_get_sis_user_data($values->uid),
    );
    $rows[] = $row;
  }
  return array(
    'status' => 200,
    'data' => $rows,
  );
}