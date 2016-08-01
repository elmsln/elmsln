<?php
/**
 * @file
 * cle_dashboard.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cle_dashboard_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cle_dashboard';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CLE Dashboard';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Assignments Dashboard';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'cle_dashboard',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = 'Section';
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['field_cle_crit_type']['id'] = 'field_cle_crit_type';
  $handler->display->display_options['fields']['field_cle_crit_type']['table'] = 'field_data_field_cle_crit_type';
  $handler->display->display_options['fields']['field_cle_crit_type']['field'] = 'field_cle_crit_type';
  /* Field: start_date */
  $handler->display->display_options['fields']['field_submission_state']['id'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['table'] = 'field_data_field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['field'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['ui_name'] = 'start_date';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'og_group_ref_target_id';
  $handler->display->display_options['fields']['nid']['label'] = 'og_ref_id';
  /* Field: Content: Critique Date */
  $handler->display->display_options['fields']['field_critique_date']['id'] = 'field_critique_date';
  $handler->display->display_options['fields']['field_critique_date']['table'] = 'field_data_field_critique_date';
  $handler->display->display_options['fields']['field_critique_date']['field'] = 'field_critique_date';
  $handler->display->display_options['fields']['field_critique_date']['settings'] = array(
    'format_type' => 'cle_dashboard',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Sort criterion: Content: Due Date (field_due_date) */
  $handler->display->display_options['sorts']['field_due_date_value']['id'] = 'field_due_date_value';
  $handler->display->display_options['sorts']['field_due_date_value']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['sorts']['field_due_date_value']['field'] = 'field_due_date_value';
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
    'cle_assignment' => 'cle_assignment',
  );
  $export['cle_dashboard'] = $view;

  $view = new view();
  $view->name = 'cle_dashboard_my_submissions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CLE Dashboard My Submissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_assignment_target_id';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'cle_dashboard';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'D d/m/y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_submission_state']['id'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['table'] = 'field_data_field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['field'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_submission_state']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
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
    'cle_submission' => 'cle_submission',
  );
  $export['cle_dashboard_my_submissions'] = $view;

  $view = new view();
  $view->name = 'cle_dashboard_student_submissions';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CLE Dashboard Student Submissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer cle content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_assignment_target_id';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'cle_dashboard';
  $handler->display->display_options['fields']['created']['custom_date_format'] = 'D d/m/y';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_submission_state']['id'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['table'] = 'field_data_field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['field'] = 'field_submission_state';
  $handler->display->display_options['fields']['field_submission_state']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_submission_state']['element_default_classes'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
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
    'cle_submission' => 'cle_submission',
  );
  $export['cle_dashboard_student_submissions'] = $view;

  return $export;
}
