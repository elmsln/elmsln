<?php
/**
 * @file
 * cle_critique.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cle_critique_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cle_critique';
  $view->description = 'Displays related to critiques received';
  $view->tag = 'critique';
  $view->base_table = 'node';
  $view->human_name = 'Critique - critiques received';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Feedback received';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'view_node' => 'view_node',
    'title' => 'title',
    'last_updated' => 'last_updated',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'A listing of feedback you\'ve been given by other classmates';
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_cle_crit_sub_ref_node']['id'] = 'reverse_field_cle_crit_sub_ref_node';
  $handler->display->display_options['relationships']['reverse_field_cle_crit_sub_ref_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_cle_crit_sub_ref_node']['field'] = 'reverse_field_cle_crit_sub_ref_node';
  $handler->display->display_options['relationships']['reverse_field_cle_crit_sub_ref_node']['label'] = 'Critique';
  $handler->display->display_options['relationships']['reverse_field_cle_crit_sub_ref_node']['required'] = TRUE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['relationship'] = 'reverse_field_cle_crit_sub_ref_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Critique';
  $handler->display->display_options['fields']['view_node']['text'] = 'View critique';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Submission';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Updated/commented date */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Submitted';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'long';
  $handler->display->display_options['fields']['last_updated']['second_date_format'] = 'long';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
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

  /* Display: default */
  $handler = $view->new_display('page', 'default', 'page');
  $handler->display->display_options['path'] = 'cle/critique';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Critique';
  $handler->display->display_options['menu']['weight'] = '-8';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: feedback recieved */
  $handler = $view->new_display('page', 'feedback recieved', 'page_1');
  $handler->display->display_options['path'] = 'cle/critique/feedback-received';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Feedback received';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Feedback received';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'menu-elmsln-navigation';
  $export['cle_critique'] = $view;

  $view = new view();
  $view->name = 'cle_critique_feedback_given';
  $view->description = 'Listing of feedback that the user has given to others';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Critique feedback given';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Feedback given';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'view_node' => 'view_node',
    'field_cle_crit_sub_ref' => 'field_cle_crit_sub_ref',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'nid' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cle_crit_sub_ref' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'A listing of feedback you gave to your classmates';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Critique';
  $handler->display->display_options['fields']['view_node']['text'] = 'Feedback you gave';
  /* Field: Content: Submission */
  $handler->display->display_options['fields']['field_cle_crit_sub_ref']['id'] = 'field_cle_crit_sub_ref';
  $handler->display->display_options['fields']['field_cle_crit_sub_ref']['table'] = 'field_data_field_cle_crit_sub_ref';
  $handler->display->display_options['fields']['field_cle_crit_sub_ref']['field'] = 'field_cle_crit_sub_ref';
  $handler->display->display_options['fields']['field_cle_crit_sub_ref']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Submitted';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
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
    'cle_critique' => 'cle_critique',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'cle/critique/feedback-given';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Feedback given';
  $handler->display->display_options['menu']['weight'] = '-9';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cle_critique_feedback_given'] = $view;

  $view = new view();
  $view->name = 'critique_evas';
  $view->description = 'Entity views attachemnts';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Critique EVAs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Critiques';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_cle_crit_sub_ref_target_id']['id'] = 'field_cle_crit_sub_ref_target_id';
  $handler->display->display_options['relationships']['field_cle_crit_sub_ref_target_id']['table'] = 'field_data_field_cle_crit_sub_ref';
  $handler->display->display_options['relationships']['field_cle_crit_sub_ref_target_id']['field'] = 'field_cle_crit_sub_ref_target_id';
  $handler->display->display_options['relationships']['field_cle_crit_sub_ref_target_id']['label'] = 'Submission';
  $handler->display->display_options['relationships']['field_cle_crit_sub_ref_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['relationship'] = 'field_cle_crit_sub_ref_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Critiques';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Submission (field_cle_crit_sub_ref) */
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['id'] = 'field_cle_crit_sub_ref_target_id';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['table'] = 'field_data_field_cle_crit_sub_ref';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['field'] = 'field_cle_crit_sub_ref_target_id';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_cle_crit_sub_ref_target_id']['summary_options']['items_per_page'] = '25';
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
    'cle_critique' => 'cle_critique',
  );
  /* Filter criterion: Content: Type (field_cle_crit_type) */
  $handler->display->display_options['filters']['field_cle_crit_type_value']['id'] = 'field_cle_crit_type_value';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['table'] = 'field_data_field_cle_crit_type';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['field'] = 'field_cle_crit_type_value';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['value'] = array(
    'doubleblind' => 'doubleblind',
  );

  /* Display: EVA Double-blind */
  $handler = $view->new_display('entity_view', 'EVA Double-blind', 'entity_view_1');
  $handler->display->display_options['display_description'] = 'Double-blind listing of critiques';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Critiques';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = 'Critique by classmate';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'cle_submission',
  );
  $handler->display->display_options['show_title'] = 0;

  /* Display: EVA Open */
  $handler = $view->new_display('entity_view', 'EVA Open', 'entity_view_2');
  $handler->display->display_options['display_description'] = 'Open / single blind critique';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
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
    'cle_critique' => 'cle_critique',
  );
  /* Filter criterion: Content: Type (field_cle_crit_type) */
  $handler->display->display_options['filters']['field_cle_crit_type_value']['id'] = 'field_cle_crit_type_value';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['table'] = 'field_data_field_cle_crit_type';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['field'] = 'field_cle_crit_type_value';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_cle_crit_type_value']['value'] = array(
    'blind' => 'blind',
    'open' => 'open',
  );
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'cle_submission',
  );
  $handler->display->display_options['show_title'] = 0;
  $export['critique_evas'] = $view;

  return $export;
}
