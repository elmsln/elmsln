<?php
/**
 * @file
 * cis_displays.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cis_displays_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cis_bulk_operations';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Course Bulk operations';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Course Bulk Operations';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    166149871 => '166149871',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'field_academic_home' => 'field_academic_home',
    'field_program_classification' => 'field_program_classification',
    'field_course_author' => 'field_course_author',
    'field_instructional_designer' => 'field_instructional_designer',
    'field_lead_instructor' => 'field_lead_instructor',
    'edit_node' => 'edit_node',
    'field_machine_name' => 'field_machine_name',
    'field_method_of_access' => 'field_method_of_access',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
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
    'field_academic_home' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_program_classification' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_course_author' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_instructional_designer' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_lead_instructor' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_method_of_access' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['summary'] = 'List of courses to perform bulk operations on';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 0,
        'display_values' => array(
          'course::field_academic_home' => 'course::field_academic_home',
          'course::field_instructional_designer' => 'course::field_instructional_designer',
          'course::field_program_classification' => 'course::field_program_classification',
          'course::field_method_of_access' => 'course::field_method_of_access',
          'course::field_display_in_course_list' => 'course::field_display_in_course_list',
          'course::field_course_author' => 'course::field_course_author',
          'course::field_lead_instructor' => 'course::field_lead_instructor',
        ),
      ),
    ),
    'action::replicate_ui_replicate_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = 'Unit';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Program classification */
  $handler->display->display_options['fields']['field_program_classification']['id'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['field'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['label'] = 'Program';
  $handler->display->display_options['fields']['field_program_classification']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_program_classification']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_program_classification']['delta_offset'] = '0';
  /* Field: Content: Course Author */
  $handler->display->display_options['fields']['field_course_author']['id'] = 'field_course_author';
  $handler->display->display_options['fields']['field_course_author']['table'] = 'field_data_field_course_author';
  $handler->display->display_options['fields']['field_course_author']['field'] = 'field_course_author';
  $handler->display->display_options['fields']['field_course_author']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Instructional Designer */
  $handler->display->display_options['fields']['field_instructional_designer']['id'] = 'field_instructional_designer';
  $handler->display->display_options['fields']['field_instructional_designer']['table'] = 'field_data_field_instructional_designer';
  $handler->display->display_options['fields']['field_instructional_designer']['field'] = 'field_instructional_designer';
  $handler->display->display_options['fields']['field_instructional_designer']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Lead Instructor */
  $handler->display->display_options['fields']['field_lead_instructor']['id'] = 'field_lead_instructor';
  $handler->display->display_options['fields']['field_lead_instructor']['table'] = 'field_data_field_lead_instructor';
  $handler->display->display_options['fields']['field_lead_instructor']['field'] = 'field_lead_instructor';
  $handler->display->display_options['fields']['field_lead_instructor']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
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
    'course' => 'course',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Unit';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );

  /* Display: Bulk Ops */
  $handler = $view->new_display('page', 'Bulk Ops', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'cis/courses/bulk_ops';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Bulk Operations';
  $handler->display->display_options['menu']['description'] = 'Course Bulk Operations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_bulk_operations'] = $view;

  $view = new view();
  $view->name = 'cis_course_offerings';
  $view->description = 'Offerings listed as node page';
  $view->tag = 'offerings';
  $view->base_table = 'node';
  $view->human_name = 'Offerings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = '%1 Enrollments per Course';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => 30037204,
    166149871 => 166149871,
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  /* Relationship: Course */
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['id'] = 'reverse_field_academic_home_node';
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['field'] = 'reverse_field_academic_home_node';
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['ui_name'] = 'Course';
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['label'] = 'Course';
  $handler->display->display_options['relationships']['reverse_field_academic_home_node']['required'] = TRUE;
  /* Relationship: Offering */
  $handler->display->display_options['relationships']['field_offerings_value']['id'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['table'] = 'field_data_field_offerings';
  $handler->display->display_options['relationships']['field_offerings_value']['field'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['relationship'] = 'reverse_field_academic_home_node';
  $handler->display->display_options['relationships']['field_offerings_value']['ui_name'] = 'Offering';
  $handler->display->display_options['relationships']['field_offerings_value']['label'] = 'Offering';
  $handler->display->display_options['relationships']['field_offerings_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_offerings_value']['delta'] = '-1';
  /* Relationship: Section */
  $handler->display->display_options['relationships']['field_sections_value']['id'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['table'] = 'field_data_field_sections';
  $handler->display->display_options['relationships']['field_sections_value']['field'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_sections_value']['ui_name'] = 'Section';
  $handler->display->display_options['relationships']['field_sections_value']['label'] = 'Section';
  $handler->display->display_options['relationships']['field_sections_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_sections_value']['delta'] = '-1';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['field_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['relationship'] = 'field_offerings_value';
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['field_campus']['element_label_colon'] = FALSE;
  /* Sort criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['sorts']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['sorts']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['sorts']['field_year_value']['field'] = 'field_year_value';
  $handler->display->display_options['sorts']['field_year_value']['relationship'] = 'field_offerings_value';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'academic_unit' => 'academic_unit',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate_options']['access_op'] = 'update';
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
    'academic_unit' => 'academic_unit',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['relationship'] = 'reverse_field_academic_home_node';
  $handler->display->display_options['filters']['field_program_classification_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'reverse_field_academic_home_node';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );

  /* Display: Offerings */
  $handler = $view->new_display('page', 'Offerings', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Offerings';
  $handler->display->display_options['display_description'] = 'Offering tab';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'item_id' => 'item_id',
    'title' => 'title',
    'field_year' => 'field_year',
    'field_semester' => 'field_semester',
    'field_sections' => 'field_sections',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'item_id' => array(
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
    'field_year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'field_semester' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_sections' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Result summary */
  $handler->display->display_options['footer']['result']['id'] = 'result';
  $handler->display->display_options['footer']['result']['table'] = 'views';
  $handler->display->display_options['footer']['result']['field'] = 'result';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Offering */
  $handler->display->display_options['relationships']['field_offerings_value']['id'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['table'] = 'field_data_field_offerings';
  $handler->display->display_options['relationships']['field_offerings_value']['field'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['ui_name'] = 'Offering';
  $handler->display->display_options['relationships']['field_offerings_value']['label'] = 'Offering';
  $handler->display->display_options['relationships']['field_offerings_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_offerings_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['field_year']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_year']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['field_semester']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Sections */
  $handler->display->display_options['fields']['field_sections']['id'] = 'field_sections';
  $handler->display->display_options['fields']['field_sections']['table'] = 'field_data_field_sections';
  $handler->display->display_options['fields']['field_sections']['field'] = 'field_sections';
  $handler->display->display_options['fields']['field_sections']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['field_sections']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_sections']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sections']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_sections']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_sections']['type'] = 'field_collection_table_view';
  $handler->display->display_options['fields']['field_sections']['settings'] = array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'add' => 'Add',
    'description' => 0,
    'view_mode' => 'full',
    'empty' => 1,
  );
  $handler->display->display_options['fields']['field_sections']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_sections']['multi_type'] = 'ol';
  /* Field: Add Section */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['ui_name'] = 'Add Section';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Add Section';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'field-collection/field-sections/add/field_collection_item/[item_id]?destination=node/!1/offerings';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Field collection item: replicate link */
  $handler->display->display_options['fields']['replicate_ui_link']['id'] = 'replicate_ui_link';
  $handler->display->display_options['fields']['replicate_ui_link']['table'] = 'views_entity_field_collection_item';
  $handler->display->display_options['fields']['replicate_ui_link']['field'] = 'replicate_ui_link';
  $handler->display->display_options['fields']['replicate_ui_link']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['fields']['replicate_ui_link']['label'] = '';
  $handler->display->display_options['fields']['replicate_ui_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['replicate_ui_link']['text'] = 'replicate';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'course' => 'course',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate_options']['access_op'] = 'update';
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
    'course' => 'course',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['filters']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['filters']['field_year_value']['field'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['filters']['field_year_value']['group'] = 1;
  $handler->display->display_options['filters']['field_year_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_year_value']['expose']['operator_id'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['field_year_value']['expose']['operator'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['identifier'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );
  /* Filter criterion: Field collection item: Semester (field_semester) */
  $handler->display->display_options['filters']['field_semester_value']['id'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['field_semester_value']['field'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['filters']['field_semester_value']['group'] = 1;
  $handler->display->display_options['filters']['field_semester_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator_id'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['label'] = 'Semester';
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['identifier'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    7 => 0,
    4 => 0,
    8 => 0,
    10 => 0,
    3 => 0,
  );
  $handler->display->display_options['path'] = 'node/%/offerings';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Offerings';
  $handler->display->display_options['menu']['description'] = 'Offerings of this course';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_course_offerings'] = $view;

  $view = new view();
  $view->name = 'cis_courses';
  $view->description = 'courses path';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Courses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Course list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'node/[nid]/service-instances';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
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
    'course' => 'course',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'courses';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Courses';
  $handler->display->display_options['menu']['weight'] = '-50';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_courses'] = $view;

  $view = new view();
  $view->name = 'cis_field_collection_admin';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'CIS Field Collection admin';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Field Collection admin';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'item_id' => 'item_id',
    'field_name' => 'field_name',
    'field_access_string' => 'field_access_string',
    'archived' => 'archived',
    'field_machine_name' => 'field_machine_name',
    'field_semester' => 'field_semester',
    'field_year' => 'field_year',
    'field_sections' => 'field_sections',
    'field_semester_1' => 'field_semester_1',
    'field_year_1' => 'field_year_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'item_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_access_string' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'archived' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_semester' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_year' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_sections' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_semester_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_year_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  /* Relationship: Field collection item: Entity with the Sections (field_sections) */
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['id'] = 'field_sections_field_collection_item';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['field'] = 'field_sections_field_collection_item';
  /* Relationship: Field collection item: Entity with the Offerings (field_offerings) */
  $handler->display->display_options['relationships']['field_offerings_node_1']['id'] = 'field_offerings_node_1';
  $handler->display->display_options['relationships']['field_offerings_node_1']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_offerings_node_1']['field'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node_1']['relationship'] = 'field_sections_field_collection_item';
  /* Field: Bulk operations: Field collection item */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::replicate_ui_replicate_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  /* Field: Field collection item: Field name */
  $handler->display->display_options['fields']['field_name']['id'] = 'field_name';
  $handler->display->display_options['fields']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['field_name']['field'] = 'field_name';
  /* Field: Field collection item: Access string */
  $handler->display->display_options['fields']['field_access_string']['id'] = 'field_access_string';
  $handler->display->display_options['fields']['field_access_string']['table'] = 'field_data_field_access_string';
  $handler->display->display_options['fields']['field_access_string']['field'] = 'field_access_string';
  $handler->display->display_options['fields']['field_access_string']['delta_offset'] = '0';
  /* Field: Field collection item: Archived */
  $handler->display->display_options['fields']['archived']['id'] = 'archived';
  $handler->display->display_options['fields']['archived']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['archived']['field'] = 'archived';
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['relationship'] = 'field_offerings_node_1';
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['relationship'] = 'field_sections_field_collection_item';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['relationship'] = 'field_sections_field_collection_item';
  /* Field: Field collection item: Sections */
  $handler->display->display_options['fields']['field_sections']['id'] = 'field_sections';
  $handler->display->display_options['fields']['field_sections']['table'] = 'field_data_field_sections';
  $handler->display->display_options['fields']['field_sections']['field'] = 'field_sections';
  $handler->display->display_options['fields']['field_sections']['settings'] = array(
    'edit' => 'Edit',
    'delete' => 'Delete',
    'add' => 'Add',
    'description' => 1,
    'view_mode' => 'full',
  );
  $handler->display->display_options['fields']['field_sections']['delta_offset'] = '0';
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester_1']['id'] = 'field_semester_1';
  $handler->display->display_options['fields']['field_semester_1']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester_1']['field'] = 'field_semester';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year_1']['id'] = 'field_year_1';
  $handler->display->display_options['fields']['field_year_1']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year_1']['field'] = 'field_year';
  /* Filter criterion: Field collection item: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_name']['expose']['operator_id'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['label'] = 'Field name';
  $handler->display->display_options['filters']['field_name']['expose']['operator'] = 'field_name_op';
  $handler->display->display_options['filters']['field_name']['expose']['identifier'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Access string (field_access_string) */
  $handler->display->display_options['filters']['field_access_string_value']['id'] = 'field_access_string_value';
  $handler->display->display_options['filters']['field_access_string_value']['table'] = 'field_data_field_access_string';
  $handler->display->display_options['filters']['field_access_string_value']['field'] = 'field_access_string_value';
  $handler->display->display_options['filters']['field_access_string_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_access_string_value']['expose']['operator_id'] = 'field_access_string_value_op';
  $handler->display->display_options['filters']['field_access_string_value']['expose']['label'] = 'Access string (field_access_string)';
  $handler->display->display_options['filters']['field_access_string_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_access_string_value']['expose']['operator'] = 'field_access_string_value_op';
  $handler->display->display_options['filters']['field_access_string_value']['expose']['identifier'] = 'field_access_string_value';
  $handler->display->display_options['filters']['field_access_string_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  $handler->display->display_options['filters']['field_access_string_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_access_string_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_access_string_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_access_string_value']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Field collection item: Archived */
  $handler->display->display_options['filters']['archived']['id'] = 'archived';
  $handler->display->display_options['filters']['archived']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['archived']['field'] = 'archived';
  $handler->display->display_options['filters']['archived']['exposed'] = TRUE;
  $handler->display->display_options['filters']['archived']['expose']['operator_id'] = 'archived_op';
  $handler->display->display_options['filters']['archived']['expose']['label'] = 'Archived';
  $handler->display->display_options['filters']['archived']['expose']['operator'] = 'archived_op';
  $handler->display->display_options['filters']['archived']['expose']['identifier'] = 'archived';
  $handler->display->display_options['filters']['archived']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Content: Machine name (field_machine_name) */
  $handler->display->display_options['filters']['field_machine_name_value']['id'] = 'field_machine_name_value';
  $handler->display->display_options['filters']['field_machine_name_value']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['filters']['field_machine_name_value']['field'] = 'field_machine_name_value';
  $handler->display->display_options['filters']['field_machine_name_value']['relationship'] = 'field_offerings_node_1';
  $handler->display->display_options['filters']['field_machine_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['operator_id'] = 'field_machine_name_value_op';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['label'] = 'Machine name (field_machine_name)';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['operator'] = 'field_machine_name_value_op';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['identifier'] = 'field_machine_name_value';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_field'] = 'field_machine_name';
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_machine_name_value']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Field collection item: Semester (field_semester) */
  $handler->display->display_options['filters']['field_semester_value']['id'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['field_semester_value']['field'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['relationship'] = 'field_sections_field_collection_item';
  $handler->display->display_options['filters']['field_semester_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator_id'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['label'] = 'Semester (field_semester)';
  $handler->display->display_options['filters']['field_semester_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['identifier'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['filters']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['filters']['field_year_value']['field'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['relationship'] = 'field_sections_field_collection_item';
  $handler->display->display_options['filters']['field_year_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_year_value']['expose']['operator_id'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['label'] = 'Year (field_year)';
  $handler->display->display_options['filters']['field_year_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_year_value']['expose']['operator'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['identifier'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Sections (field_sections) */
  $handler->display->display_options['filters']['field_sections_value']['id'] = 'field_sections_value';
  $handler->display->display_options['filters']['field_sections_value']['table'] = 'field_data_field_sections';
  $handler->display->display_options['filters']['field_sections_value']['field'] = 'field_sections_value';
  $handler->display->display_options['filters']['field_sections_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_sections_value']['expose']['operator_id'] = 'field_sections_value_op';
  $handler->display->display_options['filters']['field_sections_value']['expose']['label'] = 'Sections (field_sections)';
  $handler->display->display_options['filters']['field_sections_value']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['field_sections_value']['expose']['operator'] = 'field_sections_value_op';
  $handler->display->display_options['filters']['field_sections_value']['expose']['identifier'] = 'field_sections_value';
  $handler->display->display_options['filters']['field_sections_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Field collection item ID */
  $handler->display->display_options['filters']['item_id']['id'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['item_id']['field'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['item_id']['expose']['operator_id'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['label'] = 'Field collection item ID';
  $handler->display->display_options['filters']['item_id']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['item_id']['expose']['operator'] = 'item_id_op';
  $handler->display->display_options['filters']['item_id']['expose']['identifier'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  $handler->display->display_options['filters']['item_id']['group_info']['label'] = 'Field collection item ID';
  $handler->display->display_options['filters']['item_id']['group_info']['identifier'] = 'item_id';
  $handler->display->display_options['filters']['item_id']['group_info']['group_items'] = array(
    1 => array(
      'title' => '',
      'operator' => '=',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
    2 => array(
      'title' => '',
      'operator' => '=',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => array(
        'value' => '',
        'min' => '',
        'max' => '',
      ),
    ),
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'cis/admin/field-collections';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Administer Field Collection';
  $handler->display->display_options['menu']['weight'] = '30';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_field_collection_admin'] = $view;

  $view = new view();
  $view->name = 'cis_manage_semester';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'CIS Manage semester';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Syllabus';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    166149871 => '166149871',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_campus_editable' => 'field_campus_editable',
    'field_instructor_of_record_editable' => 'field_instructor_of_record_editable',
    'field_teaching_assistants_editable' => 'field_teaching_assistants_editable',
    'field_section_number_editable' => 'field_section_number_editable',
    'field_services_editable' => 'field_services_editable',
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
    'field_campus_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_instructor_of_record_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_teaching_assistants_editable' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_section_number_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_services_editable' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'Offering data';
  $handler->display->display_options['style_options']['summary'] = 'Lists all offerings for upcoming semesters';
  $handler->display->display_options['style_options']['save_messages'] = 'summary';
  /* Header: Global: Result summary */
  $handler->display->display_options['header']['result']['id'] = 'result';
  $handler->display->display_options['header']['result']['table'] = 'views';
  $handler->display->display_options['header']['result']['field'] = 'result';
  $handler->display->display_options['header']['result']['empty'] = TRUE;
  /* Relationship: Field collection item: Entity with the Offerings (field_offerings) */
  $handler->display->display_options['relationships']['field_offerings_node']['id'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_offerings_node']['field'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['label'] = 'Course';
  $handler->display->display_options['relationships']['field_offerings_node']['required'] = TRUE;
  /* Relationship: Field collection item: Sections (field_sections) */
  $handler->display->display_options['relationships']['field_sections_value']['id'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['table'] = 'field_data_field_sections';
  $handler->display->display_options['relationships']['field_sections_value']['field'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['label'] = 'Section';
  $handler->display->display_options['relationships']['field_sections_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_sections_value']['delta'] = '-1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus (editable) */
  $handler->display->display_options['fields']['field_campus_editable']['id'] = 'field_campus_editable';
  $handler->display->display_options['fields']['field_campus_editable']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus_editable']['field'] = 'field_campus_editable';
  $handler->display->display_options['fields']['field_campus_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_campus_editable']['label'] = 'Campus';
  $handler->display->display_options['fields']['field_campus_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_campus_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_campus_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Instructor of record (editable) */
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['id'] = 'field_instructor_of_record_editable';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['table'] = 'field_data_field_instructor_of_record';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['field'] = 'field_instructor_of_record_editable';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['label'] = 'Instructor of record';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Teaching assistants (editable) */
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['id'] = 'field_teaching_assistants_editable';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['table'] = 'field_data_field_teaching_assistants';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['field'] = 'field_teaching_assistants_editable';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['label'] = 'Teaching assistants';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_teaching_assistants_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Section number (editable) */
  $handler->display->display_options['fields']['field_section_number_editable']['id'] = 'field_section_number_editable';
  $handler->display->display_options['fields']['field_section_number_editable']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number_editable']['field'] = 'field_section_number_editable';
  $handler->display->display_options['fields']['field_section_number_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_section_number_editable']['label'] = 'Section number';
  $handler->display->display_options['fields']['field_section_number_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_section_number_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_section_number_editable']['suppress_description'] = 1;
  /* Field: Field: Services in use (editable) */
  $handler->display->display_options['fields']['field_services_editable']['id'] = 'field_services_editable';
  $handler->display->display_options['fields']['field_services_editable']['table'] = 'field_data_field_services';
  $handler->display->display_options['fields']['field_services_editable']['field'] = 'field_services_editable';
  $handler->display->display_options['fields']['field_services_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_services_editable']['label'] = 'Services in use';
  $handler->display->display_options['fields']['field_services_editable']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_services_editable']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_services_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_services_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_services_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Schedule number (editable) */
  $handler->display->display_options['fields']['field_schedule_number_editable']['id'] = 'field_schedule_number_editable';
  $handler->display->display_options['fields']['field_schedule_number_editable']['table'] = 'field_data_field_schedule_number';
  $handler->display->display_options['fields']['field_schedule_number_editable']['field'] = 'field_schedule_number_editable';
  /* Filter criterion: Field collection item: Field name */
  $handler->display->display_options['filters']['field_name']['id'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['field_name']['field'] = 'field_name';
  $handler->display->display_options['filters']['field_name']['value'] = array(
    'field_offerings' => 'field_offerings',
  );
  $handler->display->display_options['filters']['field_name']['group'] = 1;
  /* Filter criterion: Field collection item: Semester (field_semester) */
  $handler->display->display_options['filters']['field_semester_value']['id'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['field_semester_value']['field'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['group'] = 1;
  $handler->display->display_options['filters']['field_semester_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator_id'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['label'] = 'Semester';
  $handler->display->display_options['filters']['field_semester_value']['expose']['operator'] = 'field_semester_value_op';
  $handler->display->display_options['filters']['field_semester_value']['expose']['identifier'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['filters']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['filters']['field_year_value']['field'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['group'] = 1;
  $handler->display->display_options['filters']['field_year_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_year_value']['expose']['operator_id'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['field_year_value']['expose']['operator'] = 'field_year_value_op';
  $handler->display->display_options['filters']['field_year_value']['expose']['identifier'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field collection item: Campus (field_campus) */
  $handler->display->display_options['filters']['field_campus_value']['id'] = 'field_campus_value';
  $handler->display->display_options['filters']['field_campus_value']['table'] = 'field_data_field_campus';
  $handler->display->display_options['filters']['field_campus_value']['field'] = 'field_campus_value';
  $handler->display->display_options['filters']['field_campus_value']['relationship'] = 'field_sections_value';
  $handler->display->display_options['filters']['field_campus_value']['group'] = 1;
  $handler->display->display_options['filters']['field_campus_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_campus_value']['expose']['operator_id'] = 'field_campus_value_op';
  $handler->display->display_options['filters']['field_campus_value']['expose']['label'] = 'Campus';
  $handler->display->display_options['filters']['field_campus_value']['expose']['operator'] = 'field_campus_value_op';
  $handler->display->display_options['filters']['field_campus_value']['expose']['identifier'] = 'field_campus_value';
  $handler->display->display_options['filters']['field_campus_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['filters']['title']['operator'] = 'starts';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 1;
  /* Filter criterion: Field collection item: Archived */
  $handler->display->display_options['filters']['archived']['id'] = 'archived';
  $handler->display->display_options['filters']['archived']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['archived']['field'] = 'archived';
  $handler->display->display_options['filters']['archived']['relationship'] = 'field_sections_value';
  $handler->display->display_options['filters']['archived']['value']['value'] = '0';

  /* Display: Logistics - default */
  $handler = $view->new_display('page', 'Logistics - default', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Offerings';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_year',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
    1 => array(
      'field' => 'field_semester',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'item_id' => 'item_id',
    'field_year' => 'field_year',
    'field_semester' => 'field_semester',
    'title' => 'title',
    'field_campus' => 'field_campus',
    'nothing' => 'nothing',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'item_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_year' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_semester' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_campus' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  $handler->display->display_options['style_options']['summary'] = 'This is a listing of all offerings upcoming';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'edit';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = 'field-collection/field-sections/[item_id]/edit';
  $handler->display->display_options['fields']['nothing_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'cis/offerings';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Offerings';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Manage Semester';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';

  /* Display: List - default */
  $handler = $view->new_display('page', 'List - default', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Offerings';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_year',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
    1 => array(
      'field' => 'field_semester',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['columns'] = array(
    'field_year' => 'field_year',
    'field_semester' => 'field_semester',
    'title' => 'title',
    'field_campus' => 'field_campus',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_year' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_semester' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_campus' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  $handler->display->display_options['style_options']['caption'] = 'Offering List';
  $handler->display->display_options['style_options']['summary'] = 'This is a listing of all offerings upcoming';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['item_id']['label'] = '';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'edit';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'field-collection/field-sections/[item_id]/edit?destination=cis/offerings';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'cis/offerings/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Offerings';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Offerings';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'menu-elmsln-settings';

  /* Display: Logistics */
  $handler = $view->new_display('page', 'Logistics', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Logistics';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus (editable) */
  $handler->display->display_options['fields']['field_campus_editable']['id'] = 'field_campus_editable';
  $handler->display->display_options['fields']['field_campus_editable']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus_editable']['field'] = 'field_campus_editable';
  $handler->display->display_options['fields']['field_campus_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_campus_editable']['label'] = 'Campus';
  $handler->display->display_options['fields']['field_campus_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_campus_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_campus_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Section number (editable) */
  $handler->display->display_options['fields']['field_section_number_editable']['id'] = 'field_section_number_editable';
  $handler->display->display_options['fields']['field_section_number_editable']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number_editable']['field'] = 'field_section_number_editable';
  $handler->display->display_options['fields']['field_section_number_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_section_number_editable']['label'] = 'Section number';
  $handler->display->display_options['fields']['field_section_number_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_section_number_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_section_number_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Schedule number (editable) */
  $handler->display->display_options['fields']['field_schedule_number_editable']['id'] = 'field_schedule_number_editable';
  $handler->display->display_options['fields']['field_schedule_number_editable']['table'] = 'field_data_field_schedule_number';
  $handler->display->display_options['fields']['field_schedule_number_editable']['field'] = 'field_schedule_number_editable';
  $handler->display->display_options['fields']['field_schedule_number_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_schedule_number_editable']['label'] = 'Schedule number';
  $handler->display->display_options['fields']['field_schedule_number_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_schedule_number_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_schedule_number_editable']['suppress_description'] = 1;
  $handler->display->display_options['path'] = 'cis/offerings/logistics';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Logistics';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Verification */
  $handler = $view->new_display('page', 'Verification', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Instructor Verification';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Instructor of record (editable) */
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['id'] = 'field_instructor_of_record_editable';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['table'] = 'field_data_field_instructor_of_record';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['field'] = 'field_instructor_of_record_editable';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['label'] = 'Instructor of record';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_instructor_of_record_editable']['suppress_description'] = 1;
  /* Field: Field collection item: Access string (editable) */
  $handler->display->display_options['fields']['field_access_string_editable']['id'] = 'field_access_string_editable';
  $handler->display->display_options['fields']['field_access_string_editable']['table'] = 'field_data_field_access_string';
  $handler->display->display_options['fields']['field_access_string_editable']['field'] = 'field_access_string_editable';
  $handler->display->display_options['fields']['field_access_string_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_access_string_editable']['label'] = 'Access strings';
  $handler->display->display_options['fields']['field_access_string_editable']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_access_string_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_access_string_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_access_string_editable']['suppress_description'] = 1;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Field collection item: Course Start */
  $handler->display->display_options['fields']['field_course_start']['id'] = 'field_course_start';
  $handler->display->display_options['fields']['field_course_start']['table'] = 'field_data_field_course_start';
  $handler->display->display_options['fields']['field_course_start']['field'] = 'field_course_start';
  $handler->display->display_options['fields']['field_course_start']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_course_start']['label'] = 'Course dates';
  $handler->display->display_options['fields']['field_course_start']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Field collection item: Access duration */
  $handler->display->display_options['fields']['field_access_dates']['id'] = 'field_access_dates';
  $handler->display->display_options['fields']['field_access_dates']['table'] = 'field_data_field_access_dates';
  $handler->display->display_options['fields']['field_access_dates']['field'] = 'field_access_dates';
  $handler->display->display_options['fields']['field_access_dates']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_access_dates']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['path'] = 'cis/offerings/verification';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Verification';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Welcome letter */
  $handler = $view->new_display('page', 'Welcome letter', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Welcome letter';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Section number */
  $handler->display->display_options['fields']['field_section_number']['id'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number']['field'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Welcome Letter (editable) */
  $handler->display->display_options['fields']['field_welcome_letter_editable']['id'] = 'field_welcome_letter_editable';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['table'] = 'field_data_field_welcome_letter';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['field'] = 'field_welcome_letter_editable';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['label'] = 'Welcome Letter';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_welcome_letter_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_welcome_letter_editable']['suppress_description'] = 1;
  $handler->display->display_options['path'] = 'cis/offerings/welcome-letters';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Welcome Letters';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Syllabus */
  $handler = $view->new_display('page', 'Syllabus', 'page_1');
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Section number */
  $handler->display->display_options['fields']['field_section_number']['id'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number']['field'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Syllabus (editable) */
  $handler->display->display_options['fields']['field_syllabus_editable']['id'] = 'field_syllabus_editable';
  $handler->display->display_options['fields']['field_syllabus_editable']['table'] = 'field_data_field_syllabus';
  $handler->display->display_options['fields']['field_syllabus_editable']['field'] = 'field_syllabus_editable';
  $handler->display->display_options['fields']['field_syllabus_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_syllabus_editable']['label'] = 'Syllabus';
  $handler->display->display_options['fields']['field_syllabus_editable']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_syllabus_editable']['settings'] = array(
    'format_custom_link_text' => 'Download syllabus',
  );
  $handler->display->display_options['fields']['field_syllabus_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_syllabus_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_syllabus_editable']['suppress_description'] = 1;
  $handler->display->display_options['path'] = 'cis/offerings/syllabi';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Syllabi';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Welcome Page */
  $handler = $view->new_display('page', 'Welcome Page', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Welcome Page';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Section number */
  $handler->display->display_options['fields']['field_section_number']['id'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number']['field'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Schedule number */
  $handler->display->display_options['fields']['field_schedule_number']['id'] = 'field_schedule_number';
  $handler->display->display_options['fields']['field_schedule_number']['table'] = 'field_data_field_schedule_number';
  $handler->display->display_options['fields']['field_schedule_number']['field'] = 'field_schedule_number';
  $handler->display->display_options['fields']['field_schedule_number']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Welcome Page (editable) */
  $handler->display->display_options['fields']['field_welcome_page_editable']['id'] = 'field_welcome_page_editable';
  $handler->display->display_options['fields']['field_welcome_page_editable']['table'] = 'field_data_field_welcome_page';
  $handler->display->display_options['fields']['field_welcome_page_editable']['field'] = 'field_welcome_page_editable';
  $handler->display->display_options['fields']['field_welcome_page_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_welcome_page_editable']['label'] = 'Welcome Page';
  $handler->display->display_options['fields']['field_welcome_page_editable']['settings'] = array(
    'trim_length' => '1',
  );
  $handler->display->display_options['fields']['field_welcome_page_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_welcome_page_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_welcome_page_editable']['suppress_description'] = 1;
  $handler->display->display_options['path'] = 'cis/offerings/welcome-page';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Welcome Pages';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Resources */
  $handler = $view->new_display('page', 'Resources', 'page_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Resources';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Section number */
  $handler->display->display_options['fields']['field_section_number']['id'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number']['field'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['relationship'] = 'field_sections_value';
  /* Field: Field collection item: Resources (editable) */
  $handler->display->display_options['fields']['field_resources_editable']['id'] = 'field_resources_editable';
  $handler->display->display_options['fields']['field_resources_editable']['table'] = 'field_data_field_resources';
  $handler->display->display_options['fields']['field_resources_editable']['field'] = 'field_resources_editable';
  $handler->display->display_options['fields']['field_resources_editable']['relationship'] = 'field_sections_value';
  $handler->display->display_options['fields']['field_resources_editable']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_resources_editable']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_resources_editable']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_resources_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_resources_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_resources_editable']['suppress_description'] = 1;
  $handler->display->display_options['path'] = 'cis/offerings/resources';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Resources';
  $handler->display->display_options['menu']['weight'] = '6';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_manage_semester'] = $view;

  $view = new view();
  $view->name = 'cis_people';
  $view->description = 'Backend list of people for administration';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS people';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS people';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    166149871 => '166149871',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
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
      'responsive' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'person' => 'person',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'cis/admin/people';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'People';
  $handler->display->display_options['menu']['description'] = 'view all people in the system';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_people'] = $view;

  $view = new view();
  $view->name = 'cis_resources';
  $view->description = 'List of global resources for use by course sections in the system.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Resources';
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
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'resource' => 'resource',
  );
  /* Filter criterion: Content: Resource type (field_type) */
  $handler->display->display_options['filters']['field_type_value']['id'] = 'field_type_value';
  $handler->display->display_options['filters']['field_type_value']['table'] = 'field_data_field_type';
  $handler->display->display_options['filters']['field_type_value']['field'] = 'field_type_value';
  $handler->display->display_options['filters']['field_type_value']['value'] = array(
    'global' => 'global',
  );

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['label'] = '';
  $handler->display->display_options['fields']['field_machine_name']['element_label_colon'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'CIS Resources';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_machine_name' => 'field_machine_name',
    'field_type' => 'field_type',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_type' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['element_label_colon'] = FALSE;
  /* Field: Content: Resource type */
  $handler->display->display_options['fields']['field_type']['id'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['table'] = 'field_data_field_type';
  $handler->display->display_options['fields']['field_type']['field'] = 'field_type';
  $handler->display->display_options['fields']['field_type']['element_label_colon'] = FALSE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
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
    'resource' => 'resource',
  );
  $handler->display->display_options['path'] = 'cis/resources';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Resources';
  $handler->display->display_options['menu']['description'] = 'List of all resources in the system';
  $handler->display->display_options['menu']['weight'] = '-49';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_resources'] = $view;

  $view = new view();
  $view->name = 'cis_services';
  $view->description = 'List of global resources for use by course sections in the system.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Services';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create service_instance content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'entity';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
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
    'service' => 'service',
  );

  /* Display: Service Entity Reference */
  $handler = $view->new_display('entityreference', 'Service Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Service list */
  $handler = $view->new_display('page', 'Service list', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'CIS Resources';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_location' => 'field_location',
    'field_distribution' => 'field_distribution',
    'field_machine_name' => 'field_machine_name',
    'body' => 'body',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_distribution' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'body' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'url';
  /* Field: Content: Distribution */
  $handler->display->display_options['fields']['field_distribution']['id'] = 'field_distribution';
  $handler->display->display_options['fields']['field_distribution']['table'] = 'field_data_field_distribution';
  $handler->display->display_options['fields']['field_distribution']['field'] = 'field_distribution';
  $handler->display->display_options['fields']['field_distribution']['element_label_colon'] = FALSE;
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['element_label_colon'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'Description';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['path'] = 'cis/services';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Network Services';
  $handler->display->display_options['menu']['description'] = 'List of all services in the CIS';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Service Instance list */
  $handler = $view->new_display('page', 'Service Instance list', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Service Instances';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_location' => 'field_location',
    'field_machine_name' => 'field_machine_name',
    'field_course' => 'field_course',
    'nothing' => 'nothing',
    'field_course_1' => 'field_course_1',
    'field_services' => 'field_services',
    'edit_node' => 'edit_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_machine_name' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_course' => array(
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
    'field_course_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_services' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Service ref */
  $handler->display->display_options['relationships']['field_services_target_id']['id'] = 'field_services_target_id';
  $handler->display->display_options['relationships']['field_services_target_id']['table'] = 'field_data_field_services';
  $handler->display->display_options['relationships']['field_services_target_id']['field'] = 'field_services_target_id';
  $handler->display->display_options['relationships']['field_services_target_id']['ui_name'] = 'Service ref';
  $handler->display->display_options['relationships']['field_services_target_id']['label'] = 'Service ref';
  $handler->display->display_options['relationships']['field_services_target_id']['required'] = TRUE;
  /* Relationship: course ref */
  $handler->display->display_options['relationships']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['ui_name'] = 'course ref';
  $handler->display->display_options['relationships']['field_course_target_id']['label'] = 'course ref';
  $handler->display->display_options['relationships']['field_course_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Service URL */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['relationship'] = 'field_services_target_id';
  $handler->display->display_options['fields']['field_location']['ui_name'] = 'Service URL';
  $handler->display->display_options['fields']['field_location']['label'] = '';
  $handler->display->display_options['fields']['field_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_location']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_location']['type'] = 'link_plain';
  /* Field: Content: Cron key */
  $handler->display->display_options['fields']['field_cron_key']['id'] = 'field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['table'] = 'field_data_field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['field'] = 'field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['label'] = '';
  $handler->display->display_options['fields']['field_cron_key']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_cron_key']['element_label_colon'] = FALSE;
  /* Field: Course machine */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['fields']['field_machine_name']['ui_name'] = 'Course machine';
  $handler->display->display_options['fields']['field_machine_name']['label'] = '';
  $handler->display->display_options['fields']['field_machine_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_machine_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_machine_name']['type'] = 'text_plain';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course']['id'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_course']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course']['settings'] = array(
    'link' => 0,
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Link';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Access [field_course]';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[field_location]/[field_machine_name]';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course_1']['id'] = 'field_course_1';
  $handler->display->display_options['fields']['field_course_1']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course_1']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course_1']['settings'] = array(
    'link' => 1,
  );
  /* Field: Field: Services in use */
  $handler->display->display_options['fields']['field_services']['id'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['table'] = 'field_data_field_services';
  $handler->display->display_options['fields']['field_services']['field'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_services']['settings'] = array(
    'link' => 1,
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Cron';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Run Cron';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = '[field_location]/[field_machine_name]/cron.php?cron_key=[field_cron_key]';
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'Sync Roster';
  $handler->display->display_options['fields']['nothing_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['alter']['path'] = '[field_location]/[field_machine_name]/cron.php?cron_key=[field_cron_key]&force_roster_sync';
  $handler->display->display_options['fields']['nothing_2']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit instance';
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
    'service_instance' => 'service_instance',
  );
  /* Filter criterion: Content: Course (field_course) */
  $handler->display->display_options['filters']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['filters']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['filters']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['filters']['field_course_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_course_target_id']['expose']['operator_id'] = 'field_course_target_id_op';
  $handler->display->display_options['filters']['field_course_target_id']['expose']['label'] = 'Course';
  $handler->display->display_options['filters']['field_course_target_id']['expose']['operator'] = 'field_course_target_id_op';
  $handler->display->display_options['filters']['field_course_target_id']['expose']['identifier'] = 'field_course_target_id';
  $handler->display->display_options['filters']['field_course_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  /* Filter criterion: Field: Services in use (field_services) */
  $handler->display->display_options['filters']['field_services_target_id']['id'] = 'field_services_target_id';
  $handler->display->display_options['filters']['field_services_target_id']['table'] = 'field_data_field_services';
  $handler->display->display_options['filters']['field_services_target_id']['field'] = 'field_services_target_id';
  $handler->display->display_options['filters']['field_services_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_services_target_id']['expose']['operator_id'] = 'field_services_target_id_op';
  $handler->display->display_options['filters']['field_services_target_id']['expose']['label'] = 'Service';
  $handler->display->display_options['filters']['field_services_target_id']['expose']['operator'] = 'field_services_target_id_op';
  $handler->display->display_options['filters']['field_services_target_id']['expose']['identifier'] = 'field_services_target_id';
  $handler->display->display_options['filters']['field_services_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
    13 => 0,
  );
  $handler->display->display_options['path'] = 'cis/services/instances';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Service Instances';
  $handler->display->display_options['menu']['description'] = 'List of all services in the CIS';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_services'] = $view;

  $view = new view();
  $view->name = 'course_service_instances';
  $view->description = 'Quick links to service instances used in a course';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Course Service Instances';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Service Instances';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any course content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Header: Global: Autorefresh */
  $handler->display->display_options['header']['autorefresh']['id'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['table'] = 'views';
  $handler->display->display_options['header']['autorefresh']['field'] = 'autorefresh';
  $handler->display->display_options['header']['autorefresh']['interval'] = '10000';
  $handler->display->display_options['header']['autorefresh']['display'] = 'page';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_services_target_id']['id'] = 'field_services_target_id';
  $handler->display->display_options['relationships']['field_services_target_id']['table'] = 'field_data_field_services';
  $handler->display->display_options['relationships']['field_services_target_id']['field'] = 'field_services_target_id';
  $handler->display->display_options['relationships']['field_services_target_id']['label'] = 'service';
  $handler->display->display_options['relationships']['field_services_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['label'] = 'course';
  $handler->display->display_options['relationships']['field_course_target_id']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Location */
  $handler->display->display_options['fields']['field_location']['id'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['table'] = 'field_data_field_location';
  $handler->display->display_options['fields']['field_location']['field'] = 'field_location';
  $handler->display->display_options['fields']['field_location']['relationship'] = 'field_services_target_id';
  $handler->display->display_options['fields']['field_location']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_location']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_location']['type'] = 'link_plain';
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name']['id'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['fields']['field_machine_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_machine_name']['type'] = 'text_plain';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Link';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'Access service';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = '[field_location]/[field_machine_name]';
  $handler->display->display_options['fields']['nothing']['alter']['external'] = TRUE;
  /* Field: Content: Cron key */
  $handler->display->display_options['fields']['field_cron_key']['id'] = 'field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['table'] = 'field_data_field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['field'] = 'field_cron_key';
  $handler->display->display_options['fields']['field_cron_key']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Sync Service';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'Run Cron';
  $handler->display->display_options['fields']['nothing_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing_1']['alter']['path'] = '[field_location]/[field_machine_name]/cron.php?cron_key=[field_cron_key]&force_roster_sync';
  $handler->display->display_options['fields']['nothing_1']['alter']['external'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'Status';
  $handler->display->display_options['fields']['nothing_2']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Contextual filter: Content: Course (field_course) */
  $handler->display->display_options['arguments']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['arguments']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['field_course_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_course_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_course_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_course_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_course_target_id']['validate_options']['types'] = array(
    'course' => 'course',
  );
  $handler->display->display_options['arguments']['field_course_target_id']['validate_options']['access'] = TRUE;
  $handler->display->display_options['arguments']['field_course_target_id']['validate_options']['access_op'] = 'update';
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
    'service_instance' => 'service_instance',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'node/%/service-instances';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Course Network';
  $handler->display->display_options['menu']['description'] = 'Short cuts to service instances used by this course';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-add';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['course_service_instances'] = $view;

  $view = new view();
  $view->name = 'user_type_lists';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'User type lists';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: First name */
  $handler->display->display_options['fields']['field_first_name']['id'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['table'] = 'field_data_field_first_name';
  $handler->display->display_options['fields']['field_first_name']['field'] = 'field_first_name';
  $handler->display->display_options['fields']['field_first_name']['label'] = '';
  $handler->display->display_options['fields']['field_first_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_first_name']['element_label_colon'] = FALSE;
  /* Field: User: Last name */
  $handler->display->display_options['fields']['field_last_name']['id'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['fields']['field_last_name']['field'] = 'field_last_name';
  $handler->display->display_options['fields']['field_last_name']['label'] = '';
  $handler->display->display_options['fields']['field_last_name']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_last_name']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['name']['alter']['text'] = '[field_last_name], [field_first_name] ([name])';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_user'] = FALSE;
  /* Sort criterion: User: Last name (field_last_name) */
  $handler->display->display_options['sorts']['field_last_name_value']['id'] = 'field_last_name_value';
  $handler->display->display_options['sorts']['field_last_name_value']['table'] = 'field_data_field_last_name';
  $handler->display->display_options['sorts']['field_last_name_value']['field'] = 'field_last_name_value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    6065076 => '6065076',
    135574917 => '135574917',
    66784200 => '66784200',
    67296478 => '67296478',
    75987638 => '75987638',
    166149871 => '166149871',
    30037204 => '30037204',
  );

  /* Display: Inst of record */
  $handler = $view->new_display('entityreference', 'Inst of record', 'entityreference_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    75987638 => '75987638',
  );

  /* Display: TAs */
  $handler = $view->new_display('entityreference', 'TAs', 'entityreference_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    67296478 => '67296478',
  );

  /* Display: Internal Staff */
  $handler = $view->new_display('entityreference', 'Internal Staff', 'entityreference_7');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'name' => 'name',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: User: Roles */
  $handler->display->display_options['filters']['rid']['id'] = 'rid';
  $handler->display->display_options['filters']['rid']['table'] = 'users_roles';
  $handler->display->display_options['filters']['rid']['field'] = 'rid';
  $handler->display->display_options['filters']['rid']['value'] = array(
    166149871 => '166149871',
    30037204 => '30037204',
  );
  $export['user_type_lists'] = $view;

  return $export;
}
