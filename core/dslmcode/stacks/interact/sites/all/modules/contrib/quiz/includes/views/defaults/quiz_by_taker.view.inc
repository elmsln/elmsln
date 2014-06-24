<?php
$view = new view();
$view->name = 'quiz_by_taker';
$view->description = 'View of all the quizzes a user has taken';
$view->tag = 'quiz';
$view->base_table = 'quiz_node_properties';
$view->human_name = '';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer quiz configuration';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['grouping'] = 'vid';
$handler->display->display_options['style_options']['columns'] = array(
  'time_end' => 'time_end',
  'nid' => 'nid',
  'vid' => 'vid',
  'time_start' => 'time_start',
  'score' => 'score',
  'uid' => 'uid',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'time_end' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'nid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'vid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'time_start' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'score' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'uid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
);
/* Relationship: Quiz Results: Quiz Node VID */
$handler->display->display_options['relationships']['vid']['id'] = 'vid';
$handler->display->display_options['relationships']['vid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['vid']['field'] = 'vid';
$handler->display->display_options['relationships']['vid']['label'] = 'quiz revision';
$handler->display->display_options['relationships']['vid']['required'] = TRUE;
/* Field: Content revision: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node_revision';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'vid';
/* Field: Quiz Results: Score */
$handler->display->display_options['fields']['score']['id'] = 'score';
$handler->display->display_options['fields']['score']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['score']['field'] = 'score';
/* Field: Quiz Results: Quiz Start Time */
$handler->display->display_options['fields']['time_start']['id'] = 'time_start';
$handler->display->display_options['fields']['time_start']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['time_start']['field'] = 'time_start';
$handler->display->display_options['fields']['time_start']['label'] = 'Quiz Start Time.';
/* Field: Quiz Results: Quiz End Time */
$handler->display->display_options['fields']['time_end']['id'] = 'time_end';
$handler->display->display_options['fields']['time_end']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['time_end']['field'] = 'time_end';
/* Field: Quiz Results: Quiz State */
$handler->display->display_options['fields']['quiz_state']['id'] = 'quiz_state';
$handler->display->display_options['fields']['quiz_state']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['quiz_state']['field'] = 'quiz_state';
/* Contextual filter: Quiz Results: User */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'quiz_node_results';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['uid']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['uid']['title'] = 'Quizzes taken by %1';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['uid']['allow_null'] = 1;
/* Filter criterion: Quiz: Quiz Version */
$handler->display->display_options['filters']['nid']['id'] = 'nid';
$handler->display->display_options['filters']['nid']['table'] = 'quiz_node_properties';
$handler->display->display_options['filters']['nid']['field'] = 'nid';
$handler->display->display_options['filters']['nid']['group'] = '0';
$handler->display->display_options['filters']['nid']['expose']['operator'] = FALSE;
$handler->display->display_options['filters']['nid']['secondary'] = 'results';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['path'] = 'quiztest/bytaker/%';
