<?php

/**
 * Implementation of hook_views_data().
 */
function multichoice_views_data() {
  $data = array();

  $data['quiz_multichoice_answers'] = array(
    // Table Definition
    'table' => array(
      'group' => 'Quiz Multichoice Answers',
      'join' => array(
        'quiz_node_properties' => array(
          'left_table' => 'quiz_node_relationship',
          'left_field' => 'child_nid',
          'field' => 'question_nid',
        ),
      ),
    ),
    // Field descriptions:
    'id' => array(
      'title' => t('Answer ID'),
      'help' => t('The ID identifying an individual answer.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'result_id',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'question_nid' => array(
      'title' => t('Answers Question Node NID'),
      'help' => t('The ID of the Question Node.'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        //'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'nid',
      ),
      'filter' => array(
        'handler' => 'quiz_views_handler_filter_numeric',
        'help' => t('Filter results to a particular subset of question versions.'),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'node',
        'field' => 'nid',
        'label' => t('node'),
      ),
    ),
    'question_vid' => array(
      'title' => t('Answers Question Node VID'),
      'help' => t('The Version ID of the Question Node.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        //'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'vid',
      ),
      // Related to NODE
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'node_revision',
        'field' => 'vid',
        'label' => t('node revision'),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'answer' => array(
      'title' => t('Answer'),
      'help' => t('Answer text'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
  ); // End quiz_multichoice_answers


  $data['quiz_multichoice_user_answers'] = array(
    // Table Definition
    'table' => array(
      'group' => 'Quiz Multichoice Answers',
      'join' => array(
        'quiz_node_properties' => array(
          'left_table' => 'quiz_node_relationship',
          'left_field' => 'child_nid',
          'field' => 'question_nid',
        ),
      ),
    ),
    // Field descriptions:
    'id' => array(
      'title' => t('User answer set ID'),
      'help' => t('The ID identifying an answer set for a user.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'result_id',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'result_id' => array(
      'title' => t('Result ID'),
      'help' => t('The ID identifying a particular set of quiz results. This ID is unique with respect to the quiz nid and vid of the quiz, uid of the quizee, and the take of the quiz.'),
      'field' => array(
        'handler' => 'views_handler_field_numeric',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'result_id',
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'help' => t('Filter results to a particular result set'),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'quiz_node_results',
        'field' => 'result_id',
        'base field' => 'result_id',
        'label' => t('Result'),
      ),
    ),
    'question_nid' => array(
      'title' => t('Result Question Node NID'),
      'help' => t('The ID of the Question Node.'),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        //'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'nid',
      ),
      'filter' => array(
        'handler' => 'quiz_views_handler_filter_numeric',
        'help' => t('Filter results to a particular subset of question versions.'),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'node',
        'field' => 'nid',
        'label' => t('node'),
      ),
    ),
    'question_vid' => array(
      'title' => t('Result Question Node VID'),
      'help' => t('The Version ID of the Question Node.'),
      'field' => array(
        'handler' => 'views_handler_field',
        'click sortable' => TRUE,
      ),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        //'name_field' => 'title',
        'numeric' => TRUE,
        'validate type' => 'vid',
      ),
      // Related to NODE
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'node_revision',
        'field' => 'vid',
        'label' => t('node revision'),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
  ); // End quiz_multichoice_user_answers

  $data['quiz_multichoice_user_answer_multi'] = array(
    'table' => array(
      'group' => t('Quiz Multichoice Answers'),
      'join' => array(
        'quiz_node_properties' => array(
          'left_table' => 'quiz_multichoice_user_answers',
          'left_field' => 'id',
          'field' => 'user_answer_id',
        ),
      ),
    ),
    // Field descriptions:
    'user_answer_id' => array(
      'title' => t('User answer set id'),
      'help' => t("The ID of a user's answer set."),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
        'help' => t("Filter results to a particular subset of a user's answer set."),
      ),
      'sort' => array('handler' => 'views_handler_sort'),
    ),
    'answer_id' => array(
      'title' => t('Answer id'),
      'help' => t("The ID of a user's answer."),
      'argument' => array(
        'handler' => 'views_handler_argument_numeric',
        'numeric' => TRUE,
      ),
      'filter' => array(
        'handler' => 'views_handler_filter_numeric',
      ),
      'sort' => array('handler' => 'views_handler_sort'),
      'relationship' => array(
        'handler' => 'views_handler_relationship',
        'base' => 'quiz_multichoice_answers',
        'field' => 'answer_id',
        'base field' => 'id',
        'label' => t('answer'),
      ),
    ),
  ); // End quiz_multichoice_user_answer_multi

  return $data;
}
