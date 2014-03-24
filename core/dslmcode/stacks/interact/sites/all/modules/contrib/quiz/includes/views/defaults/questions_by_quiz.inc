<?php
$view = new view();
$view->name = 'questions_by_quiz';
$view->description = 'View of all the questions associated with a quiz';
$view->tag = 'quiz';
$view->base_table = 'quiz_node_properties';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer quiz configuration';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['grouping'] = 'parent_vid';
$handler->display->display_options['style_options']['columns'] = array(
  'timestamp' => 'parent_nid',
  'title' => 'title',
  'type' => 'type',
  'child_nid' => 'child_nid',
  'child_vid' => 'child_vid',
  'question_status' => 'question_status',
  'parent_nid' => 'timestamp',
  'parent_vid' => 'parent_vid',
);
$handler->display->display_options['style_options']['default'] = 'title';
$handler->display->display_options['style_options']['info'] = array(
  'timestamp' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'title' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'type' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'child_nid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'child_vid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'question_status' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'parent_nid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'parent_vid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
);
/* Relationship: Quiz Questions: Quiz Node VID */
$handler->display->display_options['relationships']['parent_vid']['id'] = 'parent_vid';
$handler->display->display_options['relationships']['parent_vid']['table'] = 'quiz_node_relationship';
$handler->display->display_options['relationships']['parent_vid']['field'] = 'parent_vid';
$handler->display->display_options['relationships']['parent_vid']['label'] = 'node';
$handler->display->display_options['relationships']['parent_vid']['required'] = TRUE;
/* Relationship: Quiz Questions: Question Node VID */
$handler->display->display_options['relationships']['child_vid']['id'] = 'child_vid';
$handler->display->display_options['relationships']['child_vid']['table'] = 'quiz_node_relationship';
$handler->display->display_options['relationships']['child_vid']['field'] = 'child_vid';
$handler->display->display_options['relationships']['child_vid']['label'] = 'question node revision';
/* Field: Quiz Questions: Question Node ID */
$handler->display->display_options['fields']['child_nid']['id'] = 'child_nid';
$handler->display->display_options['fields']['child_nid']['table'] = 'quiz_node_relationship';
$handler->display->display_options['fields']['child_nid']['field'] = 'child_nid';
$handler->display->display_options['fields']['child_nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['child_nid']['separator'] = '';
/* Field: Content revision: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node_revision';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'child_vid';
$handler->display->display_options['fields']['title']['label'] = 'Question Title';
$handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['title']['alter']['path'] = 'node/[child_nid]';
$handler->display->display_options['fields']['title']['link_to_node'] = TRUE;
/* Field: Quiz Questions: Question Status */
$handler->display->display_options['fields']['question_status']['id'] = 'question_status';
$handler->display->display_options['fields']['question_status']['table'] = 'quiz_node_relationship';
$handler->display->display_options['fields']['question_status']['field'] = 'question_status';
/* Contextual filter: Quiz: Quiz Node NID */
$handler->display->display_options['arguments']['nid']['id'] = 'nid';
$handler->display->display_options['arguments']['nid']['table'] = 'quiz_node_properties';
$handler->display->display_options['arguments']['nid']['field'] = 'nid';
$handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['nid']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['nid']['title'] = 'Questions';
$handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';

/* Display: Questions by Specific Quiz */
$handler = $view->new_display('page', 'Questions by Specific Quiz', 'page_1');
$handler->display->display_options['path'] = 'admin/quiz/questions_by_quiz/%';
$handler->display->display_options['menu']['title'] = 'Questions by Quiz';
$handler->display->display_options['menu']['weight'] = '0';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_2');
$handler->display->display_options['path'] = 'admin/quiz/%/questions';
