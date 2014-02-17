<?php
/**
 * @file
 * cle_assignment.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cle_assignment_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cle_assignment_bulk';
  $view->description = 'Edit assignment information in bulk';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Assignment bulk edit';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Manage assignments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'og_context';
  $handler->display->display_options['access']['perm'] = 'update group';
  $handler->display->display_options['access']['group_id_arg'] = '1';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title_editable' => 'title_editable',
    'field_number_editable' => 'field_number_editable',
    'field_sub_number_editable' => 'field_sub_number_editable',
    'field_color_editable' => 'field_color_editable',
    'field_due_date_editable' => 'field_due_date_editable',
    'edit_node' => 'edit_node',
    'clone_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title_editable' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_number_editable' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sub_number_editable' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_color_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_due_date_editable' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'clone_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['summary'] = 'Bulk modify the assignments for this section';
  $handler->display->display_options['style_options']['save_messages'] = 'summary';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable']['id'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['label'] = 'Title';
  $handler->display->display_options['fields']['title_editable']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_editable']['link_to_node'] = FALSE;
  $handler->display->display_options['fields']['title_editable']['textfield_size'] = '30';
  /* Field: Content: Number (editable) */
  $handler->display->display_options['fields']['field_number_editable']['id'] = 'field_number_editable';
  $handler->display->display_options['fields']['field_number_editable']['table'] = 'field_data_field_number';
  $handler->display->display_options['fields']['field_number_editable']['field'] = 'field_number_editable';
  $handler->display->display_options['fields']['field_number_editable']['label'] = 'Number';
  $handler->display->display_options['fields']['field_number_editable']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_number_editable']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['field_number_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_number_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_number_editable']['suppress_description'] = 1;
  /* Field: Content: Sub-number (editable) */
  $handler->display->display_options['fields']['field_sub_number_editable']['id'] = 'field_sub_number_editable';
  $handler->display->display_options['fields']['field_sub_number_editable']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['fields']['field_sub_number_editable']['field'] = 'field_sub_number_editable';
  $handler->display->display_options['fields']['field_sub_number_editable']['label'] = 'Sub-number';
  $handler->display->display_options['fields']['field_sub_number_editable']['element_type'] = 'span';
  $handler->display->display_options['fields']['field_sub_number_editable']['element_wrapper_type'] = 'span';
  $handler->display->display_options['fields']['field_sub_number_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_sub_number_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_sub_number_editable']['suppress_description'] = 1;
  /* Field: Content: Color (editable) */
  $handler->display->display_options['fields']['field_color_editable']['id'] = 'field_color_editable';
  $handler->display->display_options['fields']['field_color_editable']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color_editable']['field'] = 'field_color_editable';
  $handler->display->display_options['fields']['field_color_editable']['label'] = 'Color';
  $handler->display->display_options['fields']['field_color_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_color_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_color_editable']['suppress_description'] = 1;
  /* Field: Content: Due Date (editable) */
  $handler->display->display_options['fields']['field_due_date_editable']['id'] = 'field_due_date_editable';
  $handler->display->display_options['fields']['field_due_date_editable']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date_editable']['field'] = 'field_due_date_editable';
  $handler->display->display_options['fields']['field_due_date_editable']['label'] = 'Due Date';
  $handler->display->display_options['fields']['field_due_date_editable']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_due_date_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_due_date_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_due_date_editable']['suppress_description'] = 1;
  /* Field: Content: Media Requirements (editable) */
  $handler->display->display_options['fields']['field_media_requirements_editable']['id'] = 'field_media_requirements_editable';
  $handler->display->display_options['fields']['field_media_requirements_editable']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements_editable']['field'] = 'field_media_requirements_editable';
  $handler->display->display_options['fields']['field_media_requirements_editable']['label'] = 'Media Requirements';
  $handler->display->display_options['fields']['field_media_requirements_editable']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_media_requirements_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_media_requirements_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_media_requirements_editable']['suppress_description'] = 1;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = 'Operations';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit';
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['clone_node']['text'] = 'clone';
  /* Sort criterion: Content: Number (field_number) */
  $handler->display->display_options['sorts']['field_number_value']['id'] = 'field_number_value';
  $handler->display->display_options['sorts']['field_number_value']['table'] = 'field_data_field_number';
  $handler->display->display_options['sorts']['field_number_value']['field'] = 'field_number_value';
  /* Sort criterion: Content: Sub-number (field_sub_number) */
  $handler->display->display_options['sorts']['field_sub_number_value']['id'] = 'field_sub_number_value';
  $handler->display->display_options['sorts']['field_sub_number_value']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['sorts']['field_sub_number_value']['field'] = 'field_sub_number_value';
  /* Contextual filter: Content: Section (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate']['type'] = 'og';
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/assignment_bulk';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Manage Assignments';
  $handler->display->display_options['menu']['description'] = 'Manage Assignments in Bulk';
  $handler->display->display_options['menu']['weight'] = '20';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cle_assignment_bulk'] = $view;

  $view = new view();
  $view->name = 'cle_assignments';
  $view->description = 'Assignment Listing views';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Assignments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Assignments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
    6 => '6',
    8 => '8',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'nid' => 'nid',
    'field_color' => 'field_color',
    'field_number' => 'field_number',
    'field_sub_number' => 'field_number',
    'title' => 'title',
    'field_due_date' => 'field_due_date',
    'nid_1' => 'nid_1',
    'nothing' => 'nothing',
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
    'field_color' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_number' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '-',
      'empty_column' => 0,
    ),
    'field_sub_number' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_due_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nid_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['summary'] = 'Assignments for this Section';
  $handler->display->display_options['style_options']['empty_table'] = TRUE;
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_assignment_node']['id'] = 'reverse_field_assignment_node';
  $handler->display->display_options['relationships']['reverse_field_assignment_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_assignment_node']['field'] = 'reverse_field_assignment_node';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_number']['id'] = 'field_number';
  $handler->display->display_options['fields']['field_number']['table'] = 'field_data_field_number';
  $handler->display->display_options['fields']['field_number']['field'] = 'field_number';
  /* Field: Content: Sub-number */
  $handler->display->display_options['fields']['field_sub_number']['id'] = 'field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['field'] = 'field_sub_number';
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
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: COUNT(DISTINCT Content: Nid) */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'reverse_field_assignment_node';
  $handler->display->display_options['fields']['nid_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['nid_1']['label'] = 'Submissions';
  $handler->display->display_options['fields']['nid_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['nid_1']['empty'] = '0';
  $handler->display->display_options['fields']['nid_1']['empty_zero'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Create new Submission';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/add/cle-submission?field_assignment=[nid]&og_group_ref=!1';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Number (field_number) */
  $handler->display->display_options['sorts']['field_number_value']['id'] = 'field_number_value';
  $handler->display->display_options['sorts']['field_number_value']['table'] = 'field_data_field_number';
  $handler->display->display_options['sorts']['field_number_value']['field'] = 'field_number_value';
  /* Sort criterion: Content: Sub-number (field_sub_number) */
  $handler->display->display_options['sorts']['field_sub_number_value']['id'] = 'field_sub_number_value';
  $handler->display->display_options['sorts']['field_sub_number_value']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['sorts']['field_sub_number_value']['field'] = 'field_sub_number_value';
  /* Contextual filter: Content: Section (og_group_ref) */
  $handler->display->display_options['arguments']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['default_argument_type'] = 'og_context';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['og_group_ref_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['og_group_ref_target_id']['validate']['type'] = 'og';
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

  /* Display: For Students */
  $handler = $view->new_display('page', 'For Students', 'assignments');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_number']['id'] = 'field_number';
  $handler->display->display_options['fields']['field_number']['table'] = 'field_data_field_number';
  $handler->display->display_options['fields']['field_number']['field'] = 'field_number';
  /* Field: Content: Sub-number */
  $handler->display->display_options['fields']['field_sub_number']['id'] = 'field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['field'] = 'field_sub_number';
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
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Create new Submission';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/add/cle-submission?field_assignment=[nid]&og_group_ref=!1';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/assignments';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Assignments';
  $handler->display->display_options['menu']['description'] = 'Listing of assignments for this section';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Staff / Instructor */
  $handler = $view->new_display('page', 'Staff / Instructor', 'assignments_bypass');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    5 => '5',
    7 => '7',
    9 => '9',
  );
  $handler->display->display_options['path'] = 'node/%/assignments-list';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Assignments';
  $handler->display->display_options['menu']['description'] = 'Listing of assignments for this section';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Listing all */
  $handler = $view->new_display('page', 'Listing all', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['label'] = '';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nid']['element_label_colon'] = FALSE;
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  /* Field: Content: Number */
  $handler->display->display_options['fields']['field_number']['id'] = 'field_number';
  $handler->display->display_options['fields']['field_number']['table'] = 'field_data_field_number';
  $handler->display->display_options['fields']['field_number']['field'] = 'field_number';
  /* Field: Content: Sub-number */
  $handler->display->display_options['fields']['field_sub_number']['id'] = 'field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['table'] = 'field_data_field_sub_number';
  $handler->display->display_options['fields']['field_sub_number']['field'] = 'field_sub_number';
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
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Create new Submission';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/add/cle-submission?field_assignment=[nid]&og_group_ref=!1';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    'cle_assignment' => 'cle_assignment',
  );
  /* Filter criterion: Content: Section (og_group_ref) */
  $handler->display->display_options['filters']['og_group_ref_target_id']['id'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['table'] = 'og_membership';
  $handler->display->display_options['filters']['og_group_ref_target_id']['field'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['og_group_ref_target_id']['expose']['operator_id'] = 'og_group_ref_target_id_op';
  $handler->display->display_options['filters']['og_group_ref_target_id']['expose']['label'] = 'Section';
  $handler->display->display_options['filters']['og_group_ref_target_id']['expose']['operator'] = 'og_group_ref_target_id_op';
  $handler->display->display_options['filters']['og_group_ref_target_id']['expose']['identifier'] = 'og_group_ref_target_id';
  $handler->display->display_options['filters']['og_group_ref_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    4 => 0,
    8 => 0,
    9 => 0,
    5 => 0,
    7 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'cle/my_assignments';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Assignments';
  $handler->display->display_options['menu']['description'] = 'Listing of assignments for this section';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'user-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cle_assignments'] = $view;

  return $export;
}
