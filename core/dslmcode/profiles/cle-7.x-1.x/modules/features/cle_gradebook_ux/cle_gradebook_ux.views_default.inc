<?php
/**
 * @file
 * cle_gradebook_ux.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cle_gradebook_ux_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cle_gradebook';
  $view->description = 'View showing the grades as a traditional grid that can be updated';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gradebook';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bulk Gradebook update';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access gradebook';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_cle_point_value_editable' => 'field_cle_point_value_editable',
    'title' => 'title',
    'name' => 'name',
  );
  $handler->display->display_options['style_options']['default'] = 'name';
  $handler->display->display_options['style_options']['info'] = array(
    'field_cle_point_value_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
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
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['relationship_creation_bundle'] = array(
    'reverse_field_cle_associated_submission_assessment_entity' => 'submission_evaluation',
  );
  /* Relationship: Broken/missing handler */
  $handler->display->display_options['relationships']['reverse_field_cle_associated_submission_assessment_entity']['id'] = 'reverse_field_cle_associated_submission_assessment_entity';
  $handler->display->display_options['relationships']['reverse_field_cle_associated_submission_assessment_entity']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_cle_associated_submission_assessment_entity']['field'] = 'reverse_field_cle_associated_submission_assessment_entity';
  $handler->display->display_options['relationships']['reverse_field_cle_associated_submission_assessment_entity']['label'] = 'Assessment entity';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_cle_point_value_editable']['id'] = 'field_cle_point_value_editable';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['table'] = 'field_data_field_cle_point_value';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['field'] = 'field_cle_point_value_editable';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['relationship'] = 'reverse_field_cle_associated_submission_assessment_entity';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['label'] = 'Points';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cle_point_value_editable']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cle_point_value_editable']['element_default_classes'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_cle_status_editable']['id'] = 'field_cle_status_editable';
  $handler->display->display_options['fields']['field_cle_status_editable']['table'] = 'field_data_field_cle_status';
  $handler->display->display_options['fields']['field_cle_status_editable']['field'] = 'field_cle_status_editable';
  $handler->display->display_options['fields']['field_cle_status_editable']['relationship'] = 'reverse_field_cle_associated_submission_assessment_entity';
  $handler->display->display_options['fields']['field_cle_status_editable']['label'] = 'Status';
  $handler->display->display_options['fields']['field_cle_status_editable']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cle_status_editable']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cle_status_editable']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cle_status_editable']['element_default_classes'] = FALSE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_cle_associated_submission_editable']['id'] = 'field_cle_associated_submission_editable';
  $handler->display->display_options['fields']['field_cle_associated_submission_editable']['table'] = 'field_data_field_cle_associated_submission';
  $handler->display->display_options['fields']['field_cle_associated_submission_editable']['field'] = 'field_cle_associated_submission_editable';
  $handler->display->display_options['fields']['field_cle_associated_submission_editable']['relationship'] = 'reverse_field_cle_associated_submission_assessment_entity';
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
  /* Filter criterion: Content: Assignment (field_assignment) */
  $handler->display->display_options['filters']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator_id'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['label'] = 'Assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['identifier'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    7 => 0,
    8 => 0,
    4 => 0,
    9 => 0,
    6 => 0,
    10 => 0,
  );
  /* Filter criterion: Broken/missing handler */
  $handler->display->display_options['filters']['field_cle_status_value']['id'] = 'field_cle_status_value';
  $handler->display->display_options['filters']['field_cle_status_value']['table'] = 'field_data_field_cle_status';
  $handler->display->display_options['filters']['field_cle_status_value']['field'] = 'field_cle_status_value';
  $handler->display->display_options['filters']['field_cle_status_value']['relationship'] = 'reverse_field_cle_associated_submission_assessment_entity';
  $handler->display->display_options['filters']['field_cle_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cle_status_value']['expose']['operator_id'] = 'field_cle_status_value_op';
  $handler->display->display_options['filters']['field_cle_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_cle_status_value']['expose']['operator'] = 'field_cle_status_value_op';
  $handler->display->display_options['filters']['field_cle_status_value']['expose']['identifier'] = 'field_cle_status_value';
  $handler->display->display_options['filters']['field_cle_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    7 => 0,
    8 => 0,
    4 => 0,
    9 => 0,
    6 => 0,
    10 => 0,
  );

  /* Display: Gradebook default page */
  $handler = $view->new_display('page', 'Gradebook default page', 'page');
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['path'] = 'cle/gradebook';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Gradebook';
  $handler->display->display_options['menu']['description'] = 'gradebook';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-cis-toolkit';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Menu Tab */
  $handler = $view->new_display('page', 'Menu Tab', 'page_1');
  $handler->display->display_options['path'] = 'cle/gradebook/bulk';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Bulk update';
  $handler->display->display_options['menu']['description'] = 'Bulk gradebook display and assessment';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-cis-toolkit';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cle_gradebook'] = $view;

  $view = new view();
  $view->name = 'gradebook_assignment_block';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gradebook assignment block';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Associated Assignment';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access gradebook';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'node';
  $handler->display->display_options['row_options']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['row_options']['view_mode'] = 'gradebook_viewer';
  $handler->display->display_options['row_options']['links'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['nid']['default_argument_options']['index'] = '4';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['gradebook_assignment_block'] = $view;

  $view = new view();
  $view->name = 'gradebook_other_work';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Gradebook Other work';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Gradebook Other work';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access gradebook';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['view_node']['alter']['target'] = '_blank';
  $handler->display->display_options['fields']['view_node']['text'] = 'view';
  /* Field: Content: Assignment */
  $handler->display->display_options['fields']['field_assignment']['id'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['fields']['field_assignment']['field'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['element_type'] = '0';
  $handler->display->display_options['fields']['field_assignment']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_assignment']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_assignment']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_assignment']['field_api_classes'] = TRUE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'html5_tools_iso8601';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
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
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'raw';
  $handler->display->display_options['arguments']['uid']['default_argument_options']['index'] = '5';
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['gradebook_other_work'] = $view;

  return $export;
}
