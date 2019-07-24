<?php

$view = new view();
$view->name = 'quiz_unevaluated_results';
$view->description = '';
$view->tag = 'quiz';
$view->base_table = 'quiz_node_results';
$view->human_name = 'quiz_unevaluated_results';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Attempts awaiting score';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'score own quiz';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
/* No results behavior: Global: Unfiltered text */
$handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
$handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
$handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
$handler->display->display_options['empty']['area_text_custom']['content'] = 'There are no quiz attempts that require scoring.';
/* Relationship: Quiz result: Nid */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
/* Relationship: Quiz result: Uid */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
/* Relationship: Content: Author */
$handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
$handler->display->display_options['relationships']['uid_1']['table'] = 'node';
$handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
$handler->display->display_options['relationships']['uid_1']['relationship'] = 'nid';
$handler->display->display_options['relationships']['uid_1']['label'] = 'Author';
/* Field: Quiz result: Quiz result ID */
$handler->display->display_options['fields']['result_id']['id'] = 'result_id';
$handler->display->display_options['fields']['result_id']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['result_id']['field'] = 'result_id';
$handler->display->display_options['fields']['result_id']['exclude'] = TRUE;
$handler->display->display_options['fields']['result_id']['separator'] = '';
/* Field: Quiz result: Nid */
$handler->display->display_options['fields']['nid']['id'] = 'nid';
$handler->display->display_options['fields']['nid']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['nid']['field'] = 'nid';
$handler->display->display_options['fields']['nid']['exclude'] = TRUE;
$handler->display->display_options['fields']['nid']['separator'] = '';
/* Field: Content: Title */
$handler->display->display_options['fields']['title']['id'] = 'title';
$handler->display->display_options['fields']['title']['table'] = 'node';
$handler->display->display_options['fields']['title']['field'] = 'title';
$handler->display->display_options['fields']['title']['relationship'] = 'nid';
/* Field: User: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'users';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['relationship'] = 'uid';
/* Field: Quiz result: Date finished */
$handler->display->display_options['fields']['time_end']['id'] = 'time_end';
$handler->display->display_options['fields']['time_end']['table'] = 'quiz_node_results';
$handler->display->display_options['fields']['time_end']['field'] = 'time_end';
$handler->display->display_options['fields']['time_end']['date_format'] = 'short';
$handler->display->display_options['fields']['time_end']['second_date_format'] = 'long';
/* Field: Global: Custom text */
$handler->display->display_options['fields']['nothing']['id'] = 'nothing';
$handler->display->display_options['fields']['nothing']['table'] = 'views';
$handler->display->display_options['fields']['nothing']['field'] = 'nothing';
$handler->display->display_options['fields']['nothing']['label'] = 'Operations';
$handler->display->display_options['fields']['nothing']['alter']['text'] = 'score';
$handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]/quiz/results/[result_id]/view?destination=admin/quiz/quiz-unevaluated-results';
/* Filter criterion: Quiz result: Evaluated */
$handler->display->display_options['filters']['is_evaluated']['id'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_evaluated']['field'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['value'] = '0';
$handler->display->display_options['filters']['is_evaluated']['group'] = 1;
/* Filter criterion: Quiz result: Invalid */
$handler->display->display_options['filters']['is_invalid']['id'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_invalid']['field'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['value'] = '0';

/* Display: Score any quiz */
$handler = $view->new_display('page', 'Score any quiz', 'page');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'score any quiz';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: Quiz result: Nid */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
/* Relationship: Quiz result: Uid */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['path'] = 'admin/quiz/quiz-unevaluated-results';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Score quizzes';
$handler->display->display_options['menu']['description'] = 'List all quizzes that require scoring.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Score own quiz */
$handler = $view->new_display('page', 'Score own quiz', 'page_1');
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Quiz result: Evaluated */
$handler->display->display_options['filters']['is_evaluated']['id'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_evaluated']['field'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['value'] = '0';
$handler->display->display_options['filters']['is_evaluated']['group'] = 1;
/* Filter criterion: Quiz result: Invalid */
$handler->display->display_options['filters']['is_invalid']['id'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_invalid']['field'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['value'] = '0';
$handler->display->display_options['filters']['is_invalid']['group'] = 1;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid_1';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['filters']['uid_current']['group'] = 1;
$handler->display->display_options['path'] = 'admin/quiz/quiz-unevaluated-results';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Score quizzes';
$handler->display->display_options['menu']['description'] = 'List all quizzes that require scoring.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;

/* Display: Score taken quiz answer */
$handler = $view->new_display('page', 'Score taken quiz answer', 'page_2');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'score taken quiz answer';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: Quiz result: Nid */
$handler->display->display_options['relationships']['nid']['id'] = 'nid';
$handler->display->display_options['relationships']['nid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['nid']['field'] = 'nid';
/* Relationship: Quiz result: Uid */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'quiz_node_results';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Quiz result: Evaluated */
$handler->display->display_options['filters']['is_evaluated']['id'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_evaluated']['field'] = 'is_evaluated';
$handler->display->display_options['filters']['is_evaluated']['value'] = '0';
$handler->display->display_options['filters']['is_evaluated']['group'] = 1;
/* Filter criterion: Quiz result: Invalid */
$handler->display->display_options['filters']['is_invalid']['id'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['table'] = 'quiz_node_results';
$handler->display->display_options['filters']['is_invalid']['field'] = 'is_invalid';
$handler->display->display_options['filters']['is_invalid']['value'] = '0';
$handler->display->display_options['filters']['is_invalid']['group'] = 1;
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$handler->display->display_options['filters']['uid_current']['group'] = 1;
$handler->display->display_options['path'] = 'admin/quiz/quiz-unevaluated-results';
$handler->display->display_options['menu']['type'] = 'normal';
$handler->display->display_options['menu']['title'] = 'Score quizzes';
$handler->display->display_options['menu']['description'] = 'List all quizzes that require scoring.';
$handler->display->display_options['menu']['weight'] = '0';
$handler->display->display_options['menu']['name'] = 'management';
$handler->display->display_options['menu']['context'] = 0;
$handler->display->display_options['menu']['context_only_inline'] = 0;
