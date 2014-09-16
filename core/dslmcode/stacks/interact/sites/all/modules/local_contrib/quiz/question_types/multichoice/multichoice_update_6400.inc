<?php
/*
 * @file
 * Update for choice Questions type module.
 *
 */

/**
 * Helper function for multichoice_update_6400
 *
 * Converts the database from the old to the new multichoice module
 *
 * @param $sandbox
 *  Array to store progress in
 * @return
 *  Array with progress data
 */
function _multichoice_update_6400(&$sandbox = NULL) {
  $to_return = array();
  $sandbox['current_step'] = isset($sandbox['current_step']) ? $sandbox['current_step'] : 0;

  // Create datastructure for organizing the update process
  $steps = array();
  $steps[] = array('alter_user_answers1', 'next_step');
  $steps[] = array('move_old_answers');
  $steps[] = array('alter_user_answers2', 'create_properties', 'alter_answers', 'next_step');
  $steps[] = array('check_answers');
  $steps[] = array('create_user_settings', 'next_step');

  // Do all the updates in the cureent step
  foreach ($steps[$sandbox['current_step']] as $value) {
    $function = '_multichoice_' . $value;
    $function($to_return, $sandbox);
  }

  // Update progress so that the batch_api can update the status bar, and knows when the update is finished
  $to_return['#finished'] = $sandbox['current_step'] / count($steps);

  return $to_return;
}

/**
 * Alter and create tables to store user answers
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_alter_user_answers1(&$to_return, &$sandbox = NULL) {
  db_drop_primary_key('quiz_multichoice_user_answers');
  db_add_field('quiz_multichoice_user_answers', 'id', array(
    'type' => 'serial',
    'unsignet' => TRUE,
    'not_null' => TRUE,
  ), array('primary key' => array('id')));
  db_add_field('quiz_multichoice_user_answers', 'choice_order', array('type' => 'text'));
  db_create_table('quiz_multichoice_user_answer_multi', array(
    'fields' => array(
      'user_answer_id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'answer_id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    ),
    'primary key' => array(
      'user_answer_id', 'answer_id'
    ),
  ));
}

/**
 * Move/convert user answer data from the old data model to the new
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_move_old_answers(&$to_return, &$sandbox = NULL) {
  // Store persistent data in the sandbox variable
  if (!isset($sandbox['step_progress'])) {
    $sandbox['step_progress'] = 0;
    $sandbox['last_rid'] = -1;
    $sandbox['last_nid'] = -1;
    $sandbox['last_vid'] = -1;
    $sandbox['last_id'] = -1;
    $sandbox['step_max'] = db_query('SELECT COUNT(DISTINCT id) FROM {quiz_multichoice_user_answers}')->fetchField();
  }
  // Fetch old user ans
  $sql = 'SELECT id, answer_id, question_nid, question_vid, result_id
          FROM {quiz_multichoice_user_answers}
          WHERE result_id >= %d
          ORDER BY result_id, question_nid, question_vid, answer_id';
  $res = db_query_range('SELECT id, answer_id, question_nid, question_vid, result_id
          FROM {quiz_multichoice_user_answers}
          WHERE result_id >= :result_id
          ORDER BY result_id, question_nid, question_vid, answer_id', array(':result_id' => $sandbox['last_rid']));
  $progress_to_add = 0;
  while ($res_o = db_fetch_object($res)) {
    if ($res_o->question_nid == $sandbox['last_nid']
     && $res_o->question_vid == $sandbox['last_vid']
     && $res_o->result_id    == $sandbox['last_rid']) {
      // We only keep one row for each question result in quiz_multichoice_user_answers
      if ($res_o->id > $sandbox['last_id']) {
        $sql2 = 'DELETE FROM {quiz_multichoice_user_answers}
                 WHERE id = %d';
        // TODO Please review the conversion of this statement to the D7 database API syntax.
        /* db_query($sql2, $res_o->id) */
        db_delete('quiz_multichoice_user_answers')
  ->condition('id', $res_o->id)
  ->execute();
        if ($progress_to_add + $sandbox['step_progress'] + 1 >= $sandbox['step_max']) {
          $sandbox['step_progress'] = $sandbox['step_max'];
        }
      }
    }
    else {
      // This is the first row for this question result
      $sandbox['last_nid'] = $res_o->question_nid;
      $sandbox['last_vid'] = $res_o->question_vid;
      $sandbox['last_rid'] = $res_o->result_id;
      $sandbox['last_id'] = $res_o->id;
      $sandbox['step_progress'] += $progress_to_add;
      $progress_to_add = 0;
    }
    // We insert ther answers in quiz_multichoice_user_answer_multi
    $sql = 'INSERT IGNORE INTO {quiz_multichoice_user_answer_multi}
            (user_answer_id, answer_id)
            VALUES(%d, %d)';
    // TODO Please convert this statement to the D7 database API syntax.
    /* db_query($sql, $sandbox['last_id'], $res_o->answer_id) */
    NULL;
    $progress_to_add++;
  }
  // We move on if all user answers have been moved
  if ($sandbox['step_progress'] >= $sandbox['step_max']) {
    _multichoice_next_step($to_return, $sandbox);
  }
}

/**
 * We delete fields not needed after the user_answer data was moved from the old data model
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_alter_user_answers2(&$to_return, &$sandbox = NULL) {
  db_drop_field('quiz_multichoice_user_answers', 'answer_id');
}

/**
 * We create a new table to store multichoice properties in
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_create_properties(&$to_return, &$sandbox = NULL) {
  db_create_table('quiz_multichoice_properties', array(
    'fields' => array(
      'nid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'vid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'choice_multi' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
      ),
      'choice_random' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
      ),
      'choice_boolean' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'default' => 0,
      ),
    ),
    'primary key' => array(
      'nid', 'vid'
    ),
  ));
}

/**
 * We alter the quiz_multichoice_answers table to fit the new data model
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_alter_answers(&$to_return, &$sandbox = NULL) {
  //db_drop_primary_key($to_return, 'quiz_multichoice_answers');
  db_change_field('quiz_multichoice_answers', 'answer_id', 'id', array(
    'type' => 'serial',
    'unsigned' => TRUE,
    'not null' => TRUE,
  ));
  db_change_field('quiz_multichoice_answers', 'nid', 'question_nid', array(
    'type' => 'int',
    'unsigned' => TRUE,
    'not null' => TRUE,
  ));
  db_change_field('quiz_multichoice_answers', 'vid', 'question_vid', array(
    'type' => 'int',
    'unsigned' => TRUE,
    'not null' => TRUE,
  ));
  db_change_field('quiz_multichoice_answers', 'feedback', 'feedback_if_chosen', array(
    'type' => 'text',
  ));
  db_add_field('quiz_multichoice_answers', 'feedback_if_chosen_format', array(
    'type' => 'int',
  ));
  db_add_field('quiz_multichoice_answers', 'feedback_if_not_chosen', array(
    'type' => 'text',
  ));
  db_add_field('quiz_multichoice_answers', 'feedback_if_not_chosen_format', array(
    'type' => 'int',
  ));
  db_add_field('quiz_multichoice_answers', 'answer_format', array(
    'type' => 'int',
  ));
  db_change_field('quiz_multichoice_answers', 'is_correct', 'score_if_chosen', array(
    'type' => 'int',
    'unsigned' => TRUE,
    'not_null' => TRUE,
    'default' => 0,
  ));
  db_add_field('quiz_multichoice_answers', 'score_if_not_chosen', array(
    'type' => 'int',
    'unsigned' => TRUE,
    'not_null' => TRUE,
    'default' => 0,
  ));
  db_drop_field('quiz_multichoice_answers', 'result_option');
}

/**
 * We go through the alternatives and update question properties and field formats
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_check_answers(&$to_return, &$sandbox) {
  // Init persistent variables
  if (!isset($sandbox['multichoice_check_answers'])) {
    $sandbox['step_progress'] = 0;
    $sandbox['multichoice_check_answers'] = TRUE;
    $sandbox['last_nid'] = 0;
    $sandbox['last_vid'] = 0;
    $sandbox['step_max'] = db_query('SELECT COUNT(DISTINCT id) FROM {quiz_multichoice_answers}')->fetchField();
  }
  $sandbox['num_corrects'] = 0;
  $sql = 'SELECT id, question_nid, question_vid, score_if_chosen, score_if_not_chosen
          FROM {quiz_multichoice_answers}
          WHERE question_nid >= %d AND question_vid >= %d
          ORDER BY question_nid, question_vid';
  $res = db_query_range('SELECT id, question_nid, question_vid, score_if_chosen, score_if_not_chosen
          FROM {quiz_multichoice_answers}
          WHERE question_nid >= :question_nid AND question_vid >= :question_vid
          ORDER BY question_nid, question_vid', array(':question_nid' => $sandbox['last_nid'], ':question_vid' => $sandbox['last_vid']));
  $progress_to_add = 0;
  while ($res_o = db_fetch_object($res)) {
    if ($res_o->question_nid == $sandbox['last_nid']
     && $res_o->question_vid == $sandbox['last_vid']) {
      // This is the same node as we processed in the last loop
      if ($progress_to_add + $sandbox['step_progress'] + 1 >= $sandbox['step_max']) {
        $sandbox['step_progress'] = $sandbox['step_max'];
      }
    }
    else {
      // New node
      $sandbox['step_progress'] += $progress_to_add;
      $progress_to_add = 0;
      $sandbox['last_nid'] = $res_o->question_nid;
      $sandbox['last_vid'] = $res_o->question_vid;
      $sandbox['num_corrects'] = 0;

      // Store the format for this node
      $sql = 'SELECT format
              FROM {node_revision}
              WHERE vid = %d';
      $res2 = db_query('SELECT format
              FROM {node_revision}
              WHERE vid = :vid', array(':vid' => $res_o->question_vid));
      $sandbox['last_format'] = $res2->fetchField();
      $sql = 'INSERT INTO {quiz_multichoice_properties}
              (nid, vid, choice_boolean)
              VALUES(%d, %d, 1)';
      // TODO Please convert this statement to the D7 database API syntax.
      /* db_query($sql, $res_o->question_nid, $res_o->question_vid) */
      NULL;
    }

    if ($res_o->score_if_chosen == 1) {
      $sandbox['num_corrects']++;
      if ($sandbox['num_corrects'] == 2) {
        // If more than one answer is correct we set the choice_multi property to one.
        $sql = 'UPDATE {quiz_multichoice_properties}
                SET choice_multi = 1
                WHERE nid = %d AND vid = %d';
        // TODO Please review the conversion of this statement to the D7 database API syntax.
        /* db_query($sql, $res_o->question_nid, $res_o->question_vid) */
        db_update('quiz_multichoice_properties')
  ->fields(array(
    'choice_multi' =>  1,
  ))
  ->condition('nid', $res_o->question_nid)
  ->condition('vid', $res_o->question_vid)
  ->execute();
      }
    }
    // Update all the formats
    $sql = 'UPDATE {quiz_multichoice_answers}
            SET answer_format = %d, feedback_if_chosen_format = %d, feedback_if_not_chosen_format = %d
            WHERE question_vid = %d'; // This table haven't been indexed yet, making this query very slow... :/
    $lf = $sandbox['last_format'];
    // TODO Please review the conversion of this statement to the D7 database API syntax.
    /* db_query($sql, $lf, $lf, $lf, $res_o->question_vid) */
    db_update('quiz_multichoice_answers')
  ->fields(array(
    'answer_format' => $lf,
    'feedback_if_chosen_format' => $lf,
    'feedback_if_not_chosen_format' => $lf,
  ))
  ->condition('question_vid', $res_o->question_vid)
  ->execute();
    $progress_to_add++;
  }
  $sandbox['step_progress'] += $progress_to_add;
  // Check if we are finished, and jump to the next step if we are
  if ($sandbox['step_progress'] >= $sandbox['step_max']) {
    _multichoice_next_step($to_return, $sandbox);
  }
}

/**
 * We create the user settings table
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_create_user_settings(&$to_return, &$sandbox = NULL) {
  db_create_table('quiz_multichoice_user_settings', array(
    'fields' => array(
      'uid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'last_nid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
      'last_vid' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
      ),
    ),
    'primary key' => array(
      'uid'
    ),
  ));
}

/**
 * Helper function to switch steps in the update process
 *
 * @param $to_return
 *  Array where progress can be reported
 * @param $sandbox
 *  Array where persistent data can be stored, and progress can be found
 */
function _multichoice_next_step(&$to_return, &$sandbox) {
  $sandbox['current_step']++;
}
