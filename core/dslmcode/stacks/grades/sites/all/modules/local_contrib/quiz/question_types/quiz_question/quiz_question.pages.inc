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
function quiz_question_revision_actions_form($form, $form_state, $question_node) {
  $efq = new EntityFieldQuery;

  // Find relationships that contain not the current version of this question.
  $result = $efq->entityCondition('entity_type', 'quiz_question_relationship')
    ->propertyCondition('child_nid', $question_node->nid)
    ->execute();

  $relationships = entity_load('quiz_question_relationship', array_keys($result['quiz_question_relationship']));
  $affected = array();
  foreach ($relationships as $relationship) {
    $affected[$relationship->parent_nid] = $relationship->parent_nid;
  }

  $text = t('You have created a new revision of a question that belongs to %num quizzes. Choose what you want to do with the different quizzes.', array('%num' => count($affected)));
  $form['intro'] = array(
    '#markup' => $text,
  );
  $form['question_node'] = array(
    '#type' => 'value',
    '#value' => $question_node,
  );
  $form['quizzes'] = array();
  // Create a form element for each quiz.
  foreach ($relationships as $relationship) {
    $quiz = node_load($relationship->parent_nid);
    if (node_access('update', $quiz)) {
      $answered = quiz_has_been_answered($quiz);

      $options = array();
      if (user_access('manual quiz revisioning')) {
        $options['update'] = t('Update (no revision)');
      }
      $options['revise'] = t('Create new revision');
      $options['nothing'] = t('Do nothing');

      $form['quizzes']['#tree'] = TRUE;
      $form['quizzes'][$quiz->nid]['revise'] = array(
        '#type' => 'radios',
        '#title' => check_plain($quiz->title) . ' - ' . ($answered ? t('answered') : t('unanswered')) . ', ' . ($quiz->status ? t('published') : t('unpublished')),
        '#options' => $options,
        '#default_value' => ($answered ? 'nothing' : 'update'),
      );
      $form['quizzes'][$quiz->nid]['status'] = array(
        '#type' => 'checkbox',
        '#title' => $quiz->status ? t('Leave published') : t('Publish'),
        '#default_value' => $quiz->status,
      );
    }
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  // Help texts.
  $form['update_expl'] = array(
    '#type' => 'item',
    '#title' => t('Update'),
    '#description' => t('Replace the old revision of the question with the new revision. This may affect reporting. It is the default when the most recent Quiz revision has not been answered.'),
  );
  $form['revise_expl'] = array(
    '#type' => 'item',
    '#title' => t('Create new revision'),
    '#description' => t('If the current revision of a Quiz has been answered, you should make a new revision to ensure that existing answer statistics and reports remain correct.')
    . '<br/>' . t('If the new revision of the question only corrects spelling errors, you do not need to create a new revision of the Quiz.'),
  );
  $form['nothing_expl'] = array(
    '#type' => 'item',
    '#title' => t('Do nothing'),
    '#description' => t('The quiz will not be revised, and will still use the old revision of the question.'),
  );
  return $form;
}

/**
 * Submit callback for the revision actions page
 */
function quiz_question_revision_actions_form_submit($form, &$form_state) {
  $form_state['redirect'] = 'node/' . $form_state['values']['question_node']->nid;
  foreach ($form_state['values']['quizzes'] as $nid => $actions) {
    // Get the current version of the questions.
    $quiz_node = node_load($nid);
    $question_node = node_load($form_state['values']['question_node']->nid);
    $efq = new EntityFieldQuery();
    $results = $efq->entityCondition('entity_type', 'quiz_question_relationship')
      ->propertyCondition('parent_nid', $quiz_node->nid)
      ->propertyCondition('parent_vid', $quiz_node->vid)
      ->execute();
    $questions = entity_load('quiz_question_relationship', array_keys($results['quiz_question_relationship']));
    foreach ($questions as $question) {
      if ($question->child_nid == $question_node->nid) {
        // We found the existing question.
        $question->child_vid = $question_node->vid;
      }
    }

    if ($actions['revise'] == 'revise') {
      $result = quiz_set_questions($quiz_node, $questions, TRUE);
      if ($result) {
        drupal_set_message(t('Quiz %title succesfully revised.', array('%title' => $quiz_node->title)), 'status');
      }
    }
    elseif ($actions['revise'] == 'update') {
      $result = quiz_set_questions($quiz_node, $questions, FALSE);
      if ($result) {
        drupal_set_message(t('Quiz %title succesfully updated.', array('%title' => $quiz_node->title)), 'status');
      }
    }
    else {
      drupal_set_message(t('Quiz not updated, please use the Quiz question listing to if you decide to update the quiz manually.', array('%title' => $quiz_node->title)), 'status');
    }
  }
}
