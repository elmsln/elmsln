<?php

/**
 * @file
 * This file provides metadata to the Views 2 API for views integration.
 *
 */

/**
 * Implements hook_views_handlers().
 *
 * @todo use hook_views_data_alter to assign these field/filter handlers to the
 * automatically generated Entity API views definitions.
 */
function quiz_views_handlers() {
  return array(
    'info' => array(
      'path' => QUIZ_VIEWS_DIR . '/handlers',
    ),
    'handlers' => array(
      // Fields
      'quiz_views_handler_field_takes' => array(
        'parent' => 'views_handler_field',
      ),
      'quiz_views_handler_field_node_link_take' => array(
        'parent' => 'views_handler_field_node_link',
      ),
      'quiz_views_handler_field_time' => array(
        'parent' => 'views_handler_field',
      ),
      'quiz_views_handler_field_question_status' => array(
        'parent' => 'views_handler_field',
      ),
      'quiz_views_handler_field_user_quiz_state' => array(
        'parent' => 'views_handler_field',
      ),
      'quiz_views_handler_field_score_aggregate' => array(
        'parent' => 'views_handler_field_numeric',
      ),
      'quiz_views_handler_field_number_questions' => array(
        'parent' => 'views_handler_field',
      ),
      // Filters
      'quiz_views_handler_filter_question_status' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
      'quiz_views_handler_filter_quiz_nid' => array(
        'parent' => 'views_handler_filter',
      ),
      'quiz_views_handler_filter_user_quiz_state' => array(
        'parent' => 'views_handler_filter',
      ),
      'quiz_views_handler_filter_user_nullable' => array(
        'parent' => 'views_handler_filter',
      ),
      // Relationships
      'quiz_views_handler_relationship_vid_from_nid' => array(
        'parent' => 'views_handler_relationship',
      ),
      // Arguments
      'quiz_views_handler_argument_quiz_nid' => array(
        'parent' => 'views_handler_argument_numeric',
      ),
      'quiz_views_handler_argument_user_uid_nullable' => array(
        'parent' => 'views_handler_argument_user_uid',
      ),
      // Filters
      'quiz_views_handler_filter_quiz_question_type' => array(
        'parent' => 'views_handler_filter_node_type',
      ),
      'quiz_views_handler_filter_quiz_question' => array(
        'parent' => 'views_handler_filter_boolean_operator',
      ),
    ),
  );
}

/**
 * Implements hook_views_data_alter().
 */
function quiz_views_data_alter(&$data) {
  // Join the quiz properties table to Quiz nodes.
  $data['quiz_node_properties']['table']['join'] = array(
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
      'type' => 'INNER',
    ),
    'node_revision' => array(
      'left_field' => 'vid',
      'field' => 'vid',
      'type' => 'INNER',
    ),
  );

  $data['quiz_node_results']['table']['join'] = array(
    // This is vid because vid is always more specific.
    'node' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
    'quiz_node_properties' => array(
      'left_field' => 'vid',
      'field' => 'vid',
    ),
  );

  $data['quiz_node_relationship']['table']['join'] = array(
    // This is vid because vid is always more specific.
    'node' => array(
      'left_field' => 'vid',
      'field' => 'parent_vid',
    ),
    'node_revisions' => array(
      'left_field' => 'vid',
      'field' => 'parent_vid',
    ),
    'quiz_node_properties' => array(
      'left_field' => 'vid',
      'field' => 'parent_vid',
      'type' => 'INNER',
    ),
  );

  $data['quiz_node_results_answers']['table']['join'] = array(
    'quiz_node_properties' => array(
      'left_table' => 'quiz_node_relationship',
      'left_field' => 'child_nid',
      'field' => 'question_nid',
      'extra' => 'quiz_node_results_answers.result_id = quiz_node_results.result_id',
    ),
  );

  // Filter for the node being a quiz question.
  $data['node']['quiz_question_type'] = array(
    'title' => t('Question type'),
    'help' => t('Filter by quiz question type.'),
    'real field' => 'type',
    'filter' => array(
      'label' => 'Quiz question type',
      'handler' => 'quiz_views_handler_filter_quiz_question_type',
    ),
  );

  // Filter for the node being a quiz question.
  $data['node']['quiz_question'] = array(
    'title' => t('Quiz question'),
    'help' => t('Filter by quiz question.'),
    'real field' => 'type',
    'filter' => array(
      'label' => 'Quiz question',
      'handler' => 'quiz_views_handler_filter_quiz_question',
    ),
  );
}
