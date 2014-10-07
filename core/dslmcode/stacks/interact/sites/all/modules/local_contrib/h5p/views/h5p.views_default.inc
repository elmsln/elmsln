<?php
/**
 * @file
 * Provide default views for H5P module
 *
 * @ingroup views_default
 */

function h5p_views_default_views() {
  // Begin copy and paste of node_points export
  $view = new view();
  $view->name = 'node_results';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Node results';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'h5p-node';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: H5P: H5P Points for node */
  $handler->display->display_options['relationships']['h5p_points']['id'] = 'h5p_points';
  $handler->display->display_options['relationships']['h5p_points']['table'] = 'h5p_nodes';
  $handler->display->display_options['relationships']['h5p_points']['field'] = 'h5p_points';
  /* Relationship: H5P: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'h5p_points';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'h5p_points';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: H5P: Start time */
  $handler->display->display_options['fields']['started']['id'] = 'started';
  $handler->display->display_options['fields']['started']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['started']['field'] = 'started';
  $handler->display->display_options['fields']['started']['relationship'] = 'h5p_points';
  /* Field: H5P: Finish time */
  $handler->display->display_options['fields']['finished']['id'] = 'finished';
  $handler->display->display_options['fields']['finished']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['finished']['field'] = 'finished';
  $handler->display->display_options['fields']['finished']['relationship'] = 'h5p_points';
  /* Field: H5P: Points awarded */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  $handler->display->display_options['fields']['points']['relationship'] = 'h5p_points';
  /* Field: H5P: Max points awarded */
  $handler->display->display_options['fields']['max_points']['id'] = 'max_points';
  $handler->display->display_options['fields']['max_points']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['max_points']['field'] = 'max_points';
  $handler->display->display_options['fields']['max_points']['relationship'] = 'h5p_points';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'h5p_content' => 'h5p_content',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/h5p-results';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Results';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // (Export ends here.)

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  // Begin copy and paste of node_points export
  $view = new view();
  $view->name = 'user_results';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User results';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'User results';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'h5p-user';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: User: H5P Points for user */
  $handler->display->display_options['relationships']['h5p_uid_points']['id'] = 'h5p_uid_points';
  $handler->display->display_options['relationships']['h5p_uid_points']['table'] = 'users';
  $handler->display->display_options['relationships']['h5p_uid_points']['field'] = 'h5p_uid_points';
  $handler->display->display_options['relationships']['h5p_uid_points']['required'] = TRUE;
  /* Relationship: H5P: Content ID */
  $handler->display->display_options['relationships']['content_id']['id'] = 'content_id';
  $handler->display->display_options['relationships']['content_id']['table'] = 'h5p_points';
  $handler->display->display_options['relationships']['content_id']['field'] = 'content_id';
  $handler->display->display_options['relationships']['content_id']['relationship'] = 'h5p_uid_points';
  /* Relationship: H5P: Content */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'h5p_nodes';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'content_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  /* Field: H5P: Start time */
  $handler->display->display_options['fields']['started']['id'] = 'started';
  $handler->display->display_options['fields']['started']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['started']['field'] = 'started';
  /* Field: H5P: Finish time */
  $handler->display->display_options['fields']['finished']['id'] = 'finished';
  $handler->display->display_options['fields']['finished']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['finished']['field'] = 'finished';
  $handler->display->display_options['fields']['finished']['relationship'] = 'h5p_uid_points';
  /* Field: H5P: Points awarded */
  $handler->display->display_options['fields']['points']['id'] = 'points';
  $handler->display->display_options['fields']['points']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['points']['field'] = 'points';
  /* Field: H5P: Max points awarded */
  $handler->display->display_options['fields']['max_points']['id'] = 'max_points';
  $handler->display->display_options['fields']['max_points']['table'] = 'h5p_points';
  $handler->display->display_options['fields']['max_points']['field'] = 'max_points';
  $handler->display->display_options['fields']['max_points']['relationship'] = 'h5p_uid_points';
  /* Sort criterion: User: Created date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'users';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: User: Uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'users';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'user';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['user'] = FALSE;
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'user/%/h5p-results';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Results';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  // Add view to list of views to provide.
  $views[$view->name] = $view;

  return $views;
}