<?php

$view = new view();
$view->name = 'quiz_by_author';
$view->description = 'View of all the quizzes owned by a particular user (\'author\').';
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
$handler->display->display_options['access']['perm'] = 'create quiz content';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['grouping'] = 'nid';
$handler->display->display_options['style_options']['columns'] = array(
  'nid' => 'nid',
  'vid' => 'vid',
  'quiz_close' => 'quiz_close',
  'quiz_open' => 'quiz_open',
  'time_limit' => 'time_limit',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'nid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'vid' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'quiz_close' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'quiz_open' => array(
    'sortable' => 0,
    'separator' => '',
  ),
  'time_limit' => array(
    'sortable' => 0,
    'separator' => '',
  ),
);
/* Relationship: Quiz: Quiz Node NID */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'quiz_node_properties';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
$handler->display->display_options['relationships']['nid']['required'] = TRUE;
/* Field: Quiz: Quiz Node NID */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
/* Field: Quiz: Quiz Node VID */
$handler->display->display_options['fields']['vid']['id'] = 'vid';
$handler->display->display_options['fields']['vid']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['vid']['field'] = 'vid';
/* Field: Quiz: Close time */
$handler->display->display_options['fields']['quiz_close']['id'] = 'quiz_close';
$handler->display->display_options['fields']['quiz_close']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['quiz_close']['field'] = 'quiz_close';
$handler->display->display_options['fields']['quiz_close']['label'] = 'Quiz close time';
/* Field: Quiz: Open time */
$handler->display->display_options['fields']['quiz_open']['id'] = 'quiz_open';
$handler->display->display_options['fields']['quiz_open']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['quiz_open']['field'] = 'quiz_open';
$handler->display->display_options['fields']['quiz_open']['label'] = 'Quiz open time';
/* Field: Quiz: Time limit */
$handler->display->display_options['fields']['time_limit']['id'] = 'time_limit';
$handler->display->display_options['fields']['time_limit']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['time_limit']['field'] = 'time_limit';
/* Field: Quiz: Allowed takes */
$handler->display->display_options['fields']['takes']['id'] = 'takes';
$handler->display->display_options['fields']['takes']['table'] = 'quiz_node_properties';
$handler->display->display_options['fields']['takes']['field'] = 'takes';
/* Contextual filter: Quiz Results: User */
$handler->display->display_options['arguments']['uid']['id'] = 'uid';
$handler->display->display_options['arguments']['uid']['table'] = 'quiz_node_results';
$handler->display->display_options['arguments']['uid']['field'] = 'uid';
$handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
$handler->display->display_options['arguments']['uid']['exception']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['uid']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['uid']['title'] = 'Quizzes created by %1';
$handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['uid']['specify_validation'] = TRUE;

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'page_1');
$handler->display->display_options['path'] = 'quiztest/byauthor/%';
