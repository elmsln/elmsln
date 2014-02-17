<?php

/**
 * @file
 * User page callbacks for the quiz_question module.
 */

/**
 * Create the form for the revision actions page
 *
 * Form for deciding what to do with the quizzes a question is member of when the question is
 * revised
 *
 * @param $form_state
 * @param $nid
 *  Question node id
 * @param $vid
 *  Question node version id
 * @return
 *  FAPI form array
 */
function quiz_question_revision_actions($form, $form_state, $nid, $vid) {
  // If no questions were kept we shouldn't get here...
  if (!isset($_SESSION['quiz_question_kept'])) {
    drupal_goto('node/' . $nid);
  }

  $form = array();
  $form['q_nid'] = array('#type' => 'value', '#value' => intval($nid));
  $form['q_vid'] = array('#type' => 'value', '#value' => intval($vid));

  // Fetch data for all the quizzes that was kept
  $quiz_nids = array();
  $quiz_vids = array();
  foreach ($_SESSION['quiz_question_kept'] as $nid_vid) {
    $temp = explode('-', $nid_vid);
    if (_quiz_is_int($temp[0], 0) && _quiz_is_int($temp[1], 0)) {
      $quiz_nids[] = $temp[0];
      $quiz_vids[] = $temp[1];
    }
  }
  $quizzes = array();
  $sql = 'SELECT nr.nid, nr.vid, nr.title, n.status FROM {node_revision} nr
          JOIN {node} n ON n.nid = nr.nid
          WHERE nr.vid IN (:vids)';
  $res = db_query($sql, array(':vids' => $quiz_vids));
  //while ($res_o = db_fetch_object($res)) {
  foreach ($res as $res_o) {
    $res_o->answered = quiz_has_been_answered($res_o);
    $quizzes[] = $res_o;
  }

  $text = t('You have created a new revision of a question that belongs to %num quizzes. Choose what you want to do with the different quizzes.', array('%num' => count($quizzes)));
  $form['intro'] = array(
    '#markup' => $text,
  );
  $form['quizzes'] = array();
  // Create a form element for each quiz
  foreach ($quizzes as $quiz) {
    $published = $quiz->status == 1 ? t('published') : t('unpublished');
    $answered = $quiz->answered ? t('answered') : t('unanswered');

    // We fetch the revision options from a helper function
    $options = _quiz_question_revision_options($quiz->status == 1, $quiz->answered);

    $form['quizzes'][$quiz->nid . '-' . $quiz->vid . '-' . $quiz->status . '-' . ($quiz->answered ? '1' : '0')] = array(
      '#type' => 'radios',
      '#title' => check_plain($quiz->title) . ' (' . $published . ' ' . t('and') . ' ' . $answered . ')',
      '#default_value' => $options['default'],
      '#options' => $options['options'],
    );
    $form['quizzes'][$quiz->vid]['#quiz_title'] = $quiz->title;
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  $form['#submit'] = array('quiz_question_revision_actions_submit');

  // Help texts
  $form['update_expl'] = array(
    '#type' => 'item',
    '#title' => t('Update'),
    '#value' => t('Replace the old revision of the question with the new revision.'),
  );
  $form['revise_expl'] = array(
    '#type' => 'item',
    '#title' => t('Revise'),
    '#value' => t('If a quiz has been answered you should make a new revision to ensure that existing answer statistics and reports remain correct.'),
    '#description' => t('If the new revision of the question only correct spelling errors etc. you don\'t need to revise.'),
  );
  return $form;
}

/**
 * Get revision options for the revision actions page
 *
 * Returns revision options and default option depending on the published and answered status
 * for a quiz
 *
 * @param $published
 *  Publish status for a quiz
 * @param $answered
 *  Has the quiz been answered?
 * @return
 *  Array with values for the #options and #default_value part of a form item
 */
function _quiz_question_revision_options($published, $answered) {
  // We create a data structure holding the different options for the different quiz states
  $struct = array(
    'published' => array(
      'answered' => array(
        'options' => array(
          // The key is in the form [update][revise][publish]
          '110' => t('Update, revise and unpublish'),
          '111' => t('Update and revise'),
          '101' => t('Update'),
          '001' => t('Do nothing'),
        ),
        'default' => '111',
      ),
      'unanswered' => array(
        'options' => array(
          '100' => t('Update and Unpublish'),
          '101' => t('Update'),
          '001' => t('Do nothing'),
        ),
        'default' => '101',
      ),

    ),
    'unpublished' => array(
      'answered' => array(
        'options' => array(
          '111' => t('Update, revise and publish'),
          '110' => t('Update and revise'),
          '101' => t('Update and publish'),
          '100' => t('Update'),
          '000' => t('Do nothing'),
        ),
        'default' => '110',
      ),
      'unanswered' => array(
        'options' => array(
          '101' => t('Update and publish'),
          '100' => t('Update'),
          '000' => t('Do nothing'),
        ),
        'default' => '100',
      ),
    ),
  );
  $published = $published ? 'published' : 'unpublished';
  $answered = $answered ? 'answered' : 'unanswered';
  return $struct[$published][$answered];
}

/**
 * Submit callback for the revision actions page
 */
function quiz_question_revision_actions_submit($form, &$form_state) {
  // TODO: Add date check here?
  // We should't be able to revisit the revision actions page after this.
  unset($_SESSION['quiz_question_kept']);

  foreach ($form_state['values'] as $key => $value) {
    if (!preg_match('/^[0-9]+-[0-9]+-[0,1]-[0,1]$/', $key)) {
      continue;
    }
    list($update, $revise, $publish) = str_split($value); //FORMAT: Update[0,1], revise[0,1] and publish[0,1]
    list($nid, $vid, $published, $answered) = explode('-', $key); //FORMAT: nid(int), vid(int), published[0,1] and answered[0,1]

    //If we are to revise the quiz we need to do that first...
    if ($revise == '1') {
      $quiz_node = node_load((int) $nid, (int) $vid);
      $quiz_node->revision = 1;
    }
    if (!isset($quiz_node) && $publish != $published) {
      $quiz_node = node_load((int) $nid, (int) $vid);
    }

    // If the quiz node is to be revised and/or (un)published we save it now
    if (isset($quiz_node)) {
      $quiz_node->auto_created = TRUE;
      $quiz_node->status = $publish;
      node_save($quiz_node);
      $quiz_nid = $quiz_node->nid;
      $quiz_vid = $quiz_node->vid;
    }
    else {
      $quiz_nid = (int) $nid;
      $quiz_vid = (int) $vid;
    }

    if ($update == '1') {
      $res_relationship = db_query('SELECT max_score, auto_update_max_score FROM {quiz_node_relationship}
              WHERE parent_vid = :parent_vid AND child_nid = :child_nid',
              array(':parent_vid' => $quiz_vid, ':child_nid' => $form_state['values']['q_nid']))->fetch();
      
      $auto_update_max_score = isset($res_relationship->auto_update_max_score) ? $res_relationship->auto_update_max_score : 0; 
      
      if($res_relationship) {
        $max_score = $res_relationship->max_score;
      }
      
      if (!$res_relationship || $auto_update_max_score) {
        $res = db_query('SELECT max_score FROM {quiz_question_properties}
                WHERE vid = :vid', array(':vid' => $form_state['values']['q_vid']));
        $max_score = $res->fetchField();
      }

      $res = db_query('SELECT weight, question_status FROM {quiz_node_relationship}
              WHERE parent_nid = :parent_nid AND parent_vid = :parent_vid AND child_nid = :child_nid',
              array(':parent_nid' => $quiz_nid, ':parent_vid' => $quiz_vid, ':child_nid' => $form_state['values']['q_nid']));
      if ($res_o = $res->fetch()) {
        // Remove old revsions of the question from the quiz
        db_delete('quiz_node_relationship')
          ->condition('parent_nid', $quiz_nid)
          ->condition('parent_vid', $quiz_vid)
          ->condition('child_nid', $form_state['values']['q_nid'])
          ->execute();
        $weight = $res_o->weight;
        $question_status = $res_o->question_status;
      }
      else {
        $weight = 1 + db_query(
          "SELECT MAX(weight)
          FROM {quiz_node_relationship}
          WHERE parent_vid = :parent_vid",
          array(':parent_vid' => $quiz_vid))->fetchField();
        $quiz_randomization = db_query(
          "SELECT randomization
          FROM {quiz_node_properties}
          WHERE nid = :nid AND vid = :vid",
          array(':nid' => $quiz_nid, ':vid' => $quiz_vid))->fetchField();
        $question_status = $quiz_randomization == 2 ? QUESTION_RANDOM : QUESTION_ALWAYS;
      }
      // Insert the newest revision of the question into the quiz
      $insert_qnr = db_insert('quiz_node_relationship')
        ->fields(array('parent_nid', 'parent_vid', 'child_nid', 'child_vid', 'max_score', 'weight', 'question_status', 'auto_update_max_score'))
        ->values(array(
          'parent_nid' => $quiz_nid,
          'parent_vid' => $quiz_vid,
          'child_nid' => $form_state['values']['q_nid'],
          'child_vid' => $form_state['values']['q_vid'],
          'max_score' => $max_score,
          'weight' => $weight,
          'question_status' => $question_status,
          'auto_update_max_score' => $auto_update_max_score,
        ))
        ->execute();
    }
  }
}
