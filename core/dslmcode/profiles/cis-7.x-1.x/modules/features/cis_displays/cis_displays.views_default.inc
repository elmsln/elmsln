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
  $view->name = 'author_block';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Author block';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'About the Author';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_course_author_target_id']['id'] = 'field_course_author_target_id';
  $handler->display->display_options['relationships']['field_course_author_target_id']['table'] = 'field_data_field_course_author';
  $handler->display->display_options['relationships']['field_course_author_target_id']['field'] = 'field_course_author_target_id';
  $handler->display->display_options['relationships']['field_course_author_target_id']['label'] = 'course author';
  $handler->display->display_options['relationships']['field_course_author_target_id']['required'] = TRUE;
  /* Field: Content: Headshot */
  $handler->display->display_options['fields']['field_headshot']['id'] = 'field_headshot';
  $handler->display->display_options['fields']['field_headshot']['table'] = 'field_data_field_headshot';
  $handler->display->display_options['fields']['field_headshot']['field'] = 'field_headshot';
  $handler->display->display_options['fields']['field_headshot']['relationship'] = 'field_course_author_target_id';
  $handler->display->display_options['fields']['field_headshot']['label'] = '';
  $handler->display->display_options['fields']['field_headshot']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_headshot']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_headshot']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  /* Field: Content: Display Name */
  $handler->display->display_options['fields']['field_display_name']['id'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['fields']['field_display_name']['field'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['relationship'] = 'field_course_author_target_id';
  $handler->display->display_options['fields']['field_display_name']['label'] = '';
  $handler->display->display_options['fields']['field_display_name']['element_label_colon'] = FALSE;
  /* Field: Content: Professional Title */
  $handler->display->display_options['fields']['field_professional_title']['id'] = 'field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['table'] = 'field_data_field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['field'] = 'field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['relationship'] = 'field_course_author_target_id';
  $handler->display->display_options['fields']['field_professional_title']['label'] = '';
  $handler->display->display_options['fields']['field_professional_title']['element_label_colon'] = FALSE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['relationship'] = 'field_course_author_target_id';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_class'] = 'unit-color';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['text'] = 'View profile';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'field_course_author_target_id';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '400',
  );
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
    'course' => 'course',
  );
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

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['author_block'] = $view;

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
    3 => '3',
    8 => '8',
    10 => '10',
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
    'action::node_assign_owner_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_sticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_make_unsticky_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
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
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::node_promote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_publish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpromote_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::replicate_ui_replicate_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::node_unpublish_by_keyword_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::pathauto_node_update_action' => array(
      'selected' => 0,
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
  $handler->display->display_options['menu']['title'] = 'Bulk Ops';
  $handler->display->display_options['menu']['description'] = 'Course Bulk Operations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_bulk_operations'] = $view;

  $view = new view();
  $view->name = 'cis_departments';
  $view->description = 'Views that help visualize department information';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Departments';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Departments';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
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
    'academic_unit' => 'academic_unit',
  );

  /* Display: Unit / Department List */
  $handler = $view->new_display('page', 'Unit / Department List', 'page');
  $handler->display->display_options['path'] = 'cis/units';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Units';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Visual */
  $handler = $view->new_display('page', 'Visual', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 0;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'border-color:green;font-size:11px;';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'border-color:green;';
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
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Academic home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
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
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['path'] = 'cis/units/map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Unit Map';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_departments'] = $view;

  $view = new view();
  $view->name = 'cis_faculty';
  $view->description = 'Searchable index of faculty members that produce online courses';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Faculty';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Faculty profiles';
  $handler->display->display_options['css_class'] = 'faculty-display';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'field_display_name_value' => array(
      'more_options' => array(
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'field_academic_home_target_id' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => FALSE,
        'bef_collapsible' => 1,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_academic_home',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['row_class'] = 'faculty-display-row';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_professional_title' => 'field_professional_title',
    'view_node' => 'view_node',
  );
  $handler->display->display_options['row_options']['separator'] = ' ';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_academic_home']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_academic_home']['alter']['text'] = '[field_color][field_academic_home]';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Headshot */
  $handler->display->display_options['fields']['field_headshot']['id'] = 'field_headshot';
  $handler->display->display_options['fields']['field_headshot']['table'] = 'field_data_field_headshot';
  $handler->display->display_options['fields']['field_headshot']['field'] = 'field_headshot';
  $handler->display->display_options['fields']['field_headshot']['label'] = '';
  $handler->display->display_options['fields']['field_headshot']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_headshot']['element_wrapper_class'] = 'faculty-headshot';
  $handler->display->display_options['fields']['field_headshot']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_headshot']['settings'] = array(
    'image_style' => 'people_headshot',
    'image_link' => 'content',
  );
  /* Field: Content: Display Name */
  $handler->display->display_options['fields']['field_display_name']['id'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['fields']['field_display_name']['field'] = 'field_display_name';
  $handler->display->display_options['fields']['field_display_name']['label'] = '';
  $handler->display->display_options['fields']['field_display_name']['element_type'] = 'h3';
  $handler->display->display_options['fields']['field_display_name']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_display_name']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_display_name']['element_wrapper_class'] = 'faculty-display-name';
  /* Field: Content: Professional Title */
  $handler->display->display_options['fields']['field_professional_title']['id'] = 'field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['table'] = 'field_data_field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['field'] = 'field_professional_title';
  $handler->display->display_options['fields']['field_professional_title']['label'] = '';
  $handler->display->display_options['fields']['field_professional_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_professional_title']['element_wrapper_class'] = 'faculty-pro-title';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_type'] = '0';
  $handler->display->display_options['fields']['view_node']['element_label_type'] = '0';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'faculty-view-profile';
  $handler->display->display_options['fields']['view_node']['text'] = 'View profile';
  /* Sort criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['sorts']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  /* Sort criterion: Content: Display Name (field_display_name) */
  $handler->display->display_options['sorts']['field_display_name_value']['id'] = 'field_display_name_value';
  $handler->display->display_options['sorts']['field_display_name_value']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['sorts']['field_display_name_value']['field'] = 'field_display_name_value';
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
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Internal Classification (field_internal_classification) */
  $handler->display->display_options['filters']['field_internal_classification_value']['id'] = 'field_internal_classification_value';
  $handler->display->display_options['filters']['field_internal_classification_value']['table'] = 'field_data_field_internal_classification';
  $handler->display->display_options['filters']['field_internal_classification_value']['field'] = 'field_internal_classification_value';
  $handler->display->display_options['filters']['field_internal_classification_value']['value'] = array(
    'faculty' => 'faculty',
  );
  $handler->display->display_options['filters']['field_internal_classification_value']['group'] = 1;
  /* Filter criterion: Content: Display Name (field_display_name) */
  $handler->display->display_options['filters']['field_display_name_value']['id'] = 'field_display_name_value';
  $handler->display->display_options['filters']['field_display_name_value']['table'] = 'field_data_field_display_name';
  $handler->display->display_options['filters']['field_display_name_value']['field'] = 'field_display_name_value';
  $handler->display->display_options['filters']['field_display_name_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_display_name_value']['group'] = 1;
  $handler->display->display_options['filters']['field_display_name_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_display_name_value']['expose']['operator_id'] = 'field_display_name_value_op';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['label'] = 'Search faculty';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['operator'] = 'field_display_name_value_op';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['identifier'] = 'field_display_name_value';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_display_name_value']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['autocomplete_field'] = 'field_display_name';
  $handler->display->display_options['filters']['field_display_name_value']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['field_display_name_value']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['field_display_name_value']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['value'] = array(
    1 => '1',
    2 => '2',
    3 => '3',
    5 => '5',
    6 => '6',
  );
  $handler->display->display_options['filters']['field_academic_home_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Department';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['reduce'] = TRUE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'faculty';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Faculty';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['cis_faculty'] = $view;

  $view = new view();
  $view->name = 'cis_faculty_courses';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Faculty Courses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Courses Authored';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '200';
  $handler->display->display_options['style_options']['items_height'] = '200';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Course Author (field_course_author) */
  $handler->display->display_options['arguments']['field_course_author_target_id']['id'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['table'] = 'field_data_field_course_author';
  $handler->display->display_options['arguments']['field_course_author_target_id']['field'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_action'] = 'access denied';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_author_target_id']['validate']['type'] = 'node';
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

  /* Display: Courses Authored */
  $handler = $view->new_display('block', 'Courses Authored', 'block');
  $export['cis_faculty_courses'] = $view;

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
    3 => '3',
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
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::replicate_ui_replicate_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
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
  $handler->display->display_options['menu']['title'] = 'Field Collection admin';
  $handler->display->display_options['menu']['weight'] = '30';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
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
    3 => '3',
    8 => '8',
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
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['tab_options']['name'] = 'management';

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
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['path'] = 'cis/offerings/verification';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Verification';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['menu']['title'] = 'Welcome Letter';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['menu']['title'] = 'Syllabus';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['menu']['title'] = 'Welcome Page';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['name'] = 'management';
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
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_manage_semester'] = $view;

  $view = new view();
  $view->name = 'cis_marketing_programs';
  $view->description = 'Listings of Programs';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Marketing programs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Programs of study';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '518400';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title_1',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'Go further and complete a course of study online.';
  $handler->display->display_options['header']['area']['format'] = 'textbook_editor';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['label'] = 'academic home';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color']['element_wrapper_class'] = 'program_color_block';
  /* Field: Content: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['label'] = '';
  $handler->display->display_options['fields']['field_abbreviation']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_abbreviation']['element_wrapper_class'] = 'program_abbrev';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] ([field_abbreviation])';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = 'h4';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'program_name';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['element_wrapper_class'] = 'program_body';
  $handler->display->display_options['fields']['body']['type'] = 'text_summary_or_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'program_details';
  $handler->display->display_options['fields']['view_node']['text'] = 'More details';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title_1']['id'] = 'title_1';
  $handler->display->display_options['sorts']['title_1']['table'] = 'node';
  $handler->display->display_options['sorts']['title_1']['field'] = 'title';
  $handler->display->display_options['sorts']['title_1']['relationship'] = 'field_academic_home_target_id';
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
    'program' => 'program',
  );
  /* Filter criterion: Content: Abbreviation (field_abbreviation) */
  $handler->display->display_options['filters']['field_abbreviation_value']['id'] = 'field_abbreviation_value';
  $handler->display->display_options['filters']['field_abbreviation_value']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['filters']['field_abbreviation_value']['field'] = 'field_abbreviation_value';
  $handler->display->display_options['filters']['field_abbreviation_value']['operator'] = '!=';
  $handler->display->display_options['filters']['field_abbreviation_value']['value'] = 'GA';

  /* Display: Programs */
  $handler = $view->new_display('page', 'Programs', 'page');
  $handler->display->display_options['path'] = 'programs';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Programs';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_marketing_programs'] = $view;

  $view = new view();
  $view->name = 'cis_marketing_services';
  $view->description = 'Marketing about servies offered and that exist. This is a front-facing component to the backend system services.';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Marketing services';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Marketing services';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '200',
  );
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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
    'college_services' => 'college_services',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'cis-marketing-services';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Services';
  $handler->display->display_options['menu']['description'] = 'Services offered to the college';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_marketing_services'] = $view;

  $view = new view();
  $view->name = 'cis_my_courses';
  $view->description = 'Course listing in the administrative CIS side';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Courses';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS My Courses';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
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

  /* Display: Instructional Designer of record */
  $handler = $view->new_display('block', 'Instructional Designer of record', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses I\'m responsible for';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Instructional Designer (field_instructional_designer) */
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['id'] = 'field_instructional_designer_target_id';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['table'] = 'field_data_field_instructional_designer';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['field'] = 'field_instructional_designer_target_id';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_instructional_designer_target_id']['summary_options']['items_per_page'] = '25';

  /* Display: Instructor */
  $handler = $view->new_display('block', 'Instructor', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses I Teach';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Offering */
  $handler->display->display_options['relationships']['field_offerings_value']['id'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['table'] = 'field_data_field_offerings';
  $handler->display->display_options['relationships']['field_offerings_value']['field'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_offerings_value']['ui_name'] = 'Offering';
  $handler->display->display_options['relationships']['field_offerings_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_offerings_value']['delta'] = '-1';
  /* Relationship: Section */
  $handler->display->display_options['relationships']['field_sections_value']['id'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['table'] = 'field_data_field_sections';
  $handler->display->display_options['relationships']['field_sections_value']['field'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['relationship'] = 'field_offerings_value';
  $handler->display->display_options['relationships']['field_sections_value']['ui_name'] = 'Section';
  $handler->display->display_options['relationships']['field_sections_value']['required'] = TRUE;
  $handler->display->display_options['relationships']['field_sections_value']['delta'] = '-1';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Field collection item: Instructor of record (field_instructor_of_record) */
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['id'] = 'field_instructor_of_record_target_id';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['table'] = 'field_data_field_instructor_of_record';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['field'] = 'field_instructor_of_record_target_id';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['relationship'] = 'field_sections_value';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_instructor_of_record_target_id']['summary_options']['items_per_page'] = '25';

  /* Display: CIS Container */
  $handler = $view->new_display('page', 'CIS Container', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses';
  $handler->display->display_options['path'] = 'cis';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'CIS';
  $handler->display->display_options['menu']['description'] = 'CIS list of courses';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Course list */
  $handler = $view->new_display('page', 'Course list', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses';
  $handler->display->display_options['path'] = 'cis/courses';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Courses';
  $handler->display->display_options['menu']['description'] = 'List of Courses';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_my_courses'] = $view;

  $view = new view();
  $view->name = 'cis_offerings';
  $view->description = 'Displays useful in visualizing what is being offered';
  $view->tag = 'default';
  $view->base_table = 'field_collection_item';
  $view->human_name = 'CIS Offerings';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Offerings';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Relationship: Field collection item: Entity with the Offerings (field_offerings) */
  $handler->display->display_options['relationships']['field_offerings_node']['id'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_offerings_node']['field'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['required'] = TRUE;
  /* Relationship: Field collection item: Sections (field_sections) */
  $handler->display->display_options['relationships']['field_sections_value']['id'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['table'] = 'field_data_field_sections';
  $handler->display->display_options['relationships']['field_sections_value']['field'] = 'field_sections_value';
  $handler->display->display_options['relationships']['field_sections_value']['label'] = 'sections';
  $handler->display->display_options['relationships']['field_sections_value']['delta'] = '-1';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['exclude'] = TRUE;
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'title';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[item_id]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_year] [field_semester]';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]/offerings';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'format';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'border-color:green;';
  /* Sort criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['sorts']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['sorts']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['sorts']['field_year_value']['field'] = 'field_year_value';
  /* Sort criterion: Field collection item: Semester (field_semester) */
  $handler->display->display_options['sorts']['field_semester_value']['id'] = 'field_semester_value';
  $handler->display->display_options['sorts']['field_semester_value']['table'] = 'field_data_field_semester';
  $handler->display->display_options['sorts']['field_semester_value']['field'] = 'field_semester_value';
  /* Filter criterion: Field collection item: Archived */
  $handler->display->display_options['filters']['archived']['id'] = 'archived';
  $handler->display->display_options['filters']['archived']['table'] = 'field_collection_item';
  $handler->display->display_options['filters']['archived']['field'] = 'archived';
  $handler->display->display_options['filters']['archived']['value']['value'] = '0';
  $handler->display->display_options['filters']['archived']['group'] = 1;
  /* Filter criterion: Field collection item: Year (field_year) */
  $handler->display->display_options['filters']['field_year_value']['id'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['table'] = 'field_data_field_year';
  $handler->display->display_options['filters']['field_year_value']['field'] = 'field_year_value';
  $handler->display->display_options['filters']['field_year_value']['relationship'] = 'field_sections_field_collection_item';
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
  /* Filter criterion: Field collection item: Semester (field_semester) */
  $handler->display->display_options['filters']['field_semester_value']['id'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['table'] = 'field_data_field_semester';
  $handler->display->display_options['filters']['field_semester_value']['field'] = 'field_semester_value';
  $handler->display->display_options['filters']['field_semester_value']['relationship'] = 'field_sections_field_collection_item';
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

  /* Display: C - O Map */
  $handler = $view->new_display('page', 'C - O Map', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses - Offerings';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['exclude'] = TRUE;
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'title';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[item_id]';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_year] [field_semester]';
  $handler->display->display_options['fields']['nothing']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nothing']['alter']['path'] = 'node/[nid]/offerings';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'format';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'border-color:green;';
  $handler->display->display_options['path'] = 'cis/offerings/course-map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Course Map';
  $handler->display->display_options['menu']['description'] = 'Course Map';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Attachment */
  $handler = $view->new_display('attachment', 'Attachment', 'attachment_1');
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['exclude'] = TRUE;
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'title';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[field_year] - [field_semester]';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_year] - [field_semester]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'format';
  $handler->display->display_options['fields']['nothing_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'border-color:green;';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'page_2' => 'page_2',
    'page_3' => 'page_3',
    'default' => 0,
    'page' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $handler->display->display_options['inherit_exposed_filters'] = TRUE;

  /* Display: O - C Map */
  $handler = $view->new_display('page', 'O - C Map', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses - Offerings';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['exclude'] = TRUE;
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'field_offerings_node';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  $handler->display->display_options['fields']['title']['label'] = 'Course';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'title';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_year] [field_semester]';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'format';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'border-color:green;';
  $handler->display->display_options['path'] = 'cis/offerings/semester-map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Semester Map';
  $handler->display->display_options['menu']['description'] = 'Semester Map';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: O - S Map */
  $handler = $view->new_display('page', 'O - S Map', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Sections';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Field collection item: Entity with the Sections (field_sections) */
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['id'] = 'field_sections_field_collection_item';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['field'] = 'field_sections_field_collection_item';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['label'] = 'Offering';
  $handler->display->display_options['relationships']['field_sections_field_collection_item']['required'] = TRUE;
  /* Relationship: Field collection item: Entity with the Offerings (field_offerings) */
  $handler->display->display_options['relationships']['field_offerings_node']['id'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['table'] = 'field_collection_item';
  $handler->display->display_options['relationships']['field_offerings_node']['field'] = 'field_offerings_node';
  $handler->display->display_options['relationships']['field_offerings_node']['relationship'] = 'field_sections_field_collection_item';
  $handler->display->display_options['relationships']['field_offerings_node']['label'] = 'Course';
  $handler->display->display_options['relationships']['field_offerings_node']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field collection item: Year */
  $handler->display->display_options['fields']['field_year']['id'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['table'] = 'field_data_field_year';
  $handler->display->display_options['fields']['field_year']['field'] = 'field_year';
  $handler->display->display_options['fields']['field_year']['relationship'] = 'field_sections_field_collection_item';
  $handler->display->display_options['fields']['field_year']['exclude'] = TRUE;
  /* Field: Field collection item: Semester */
  $handler->display->display_options['fields']['field_semester']['id'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['table'] = 'field_data_field_semester';
  $handler->display->display_options['fields']['field_semester']['field'] = 'field_semester';
  $handler->display->display_options['fields']['field_semester']['relationship'] = 'field_sections_field_collection_item';
  $handler->display->display_options['fields']['field_semester']['exclude'] = TRUE;
  /* Field: Field collection item: Campus */
  $handler->display->display_options['fields']['field_campus']['id'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['table'] = 'field_data_field_campus';
  $handler->display->display_options['fields']['field_campus']['field'] = 'field_campus';
  $handler->display->display_options['fields']['field_campus']['exclude'] = TRUE;
  /* Field: Field collection item: Section number */
  $handler->display->display_options['fields']['field_section_number']['id'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['table'] = 'field_data_field_section_number';
  $handler->display->display_options['fields']['field_section_number']['field'] = 'field_section_number';
  $handler->display->display_options['fields']['field_section_number']['exclude'] = TRUE;
  /* Field: Field collection item: Field collection item ID */
  $handler->display->display_options['fields']['item_id']['id'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['table'] = 'field_collection_item';
  $handler->display->display_options['fields']['item_id']['field'] = 'item_id';
  $handler->display->display_options['fields']['item_id']['separator'] = '';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = 'Display title';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '[field_semester] [field_year] [field_campus] [field_section_number]';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_offerings_node';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = 'format';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = 'border-color:green;';
  $handler->display->display_options['path'] = 'cis/offerings/section-map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Section Map';
  $handler->display->display_options['menu']['description'] = 'Section Map';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_offerings'] = $view;

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
    3 => '3',
    8 => '8',
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
  /* Field: Content: Internal Classification */
  $handler->display->display_options['fields']['field_internal_classification']['id'] = 'field_internal_classification';
  $handler->display->display_options['fields']['field_internal_classification']['table'] = 'field_data_field_internal_classification';
  $handler->display->display_options['fields']['field_internal_classification']['field'] = 'field_internal_classification';
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
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_people'] = $view;

  $view = new view();
  $view->name = 'cis_programs';
  $view->description = 'Listings of Programs';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Programs';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Programs';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
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
    'program' => 'program',
  );

  /* Display: Program table */
  $handler = $view->new_display('page', 'Program table', 'page');
  $handler->display->display_options['path'] = 'cis/programs';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Programs';
  $handler->display->display_options['menu']['name'] = 'management';

  /* Display: Map */
  $handler = $view->new_display('page', 'Map', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  /* Field: Content: Program classification */
  $handler->display->display_options['fields']['field_program_classification']['id'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['field'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_program_classification']['delta_offset'] = '0';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'border-color:green;';
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
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['path'] = 'cis/programs/map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Program map';
  $handler->display->display_options['menu']['description'] = 'Program mapping';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_programs'] = $view;

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
  /* Field: Content: Clone link */
  $handler->display->display_options['fields']['clone_node']['id'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['table'] = 'node';
  $handler->display->display_options['fields']['clone_node']['field'] = 'clone_node';
  $handler->display->display_options['fields']['clone_node']['label'] = '';
  $handler->display->display_options['fields']['clone_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['clone_node']['text'] = 'duplicate';
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
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_resources'] = $view;

  $view = new view();
  $view->name = 'cis_service_map';
  $view->description = 'Visualizing the service instances and courses that exist';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS service map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS service map';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['type'] = 'OrgChart';
  $handler->display->display_options['style_options']['width'] = '600';
  $handler->display->display_options['style_options']['height'] = '400';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['relationships']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['relationships']['field_course_target_id']['field'] = 'field_course_target_id';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course']['id'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_course']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_course']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['text'] = '[field_course]';
  /* Field: Field: Services in use */
  $handler->display->display_options['fields']['field_services']['id'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['table'] = 'field_data_field_services';
  $handler->display->display_options['fields']['field_services']['field'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_2']['id'] = 'title_2';
  $handler->display->display_options['fields']['title_2']['table'] = 'node';
  $handler->display->display_options['fields']['title_2']['field'] = 'title';
  $handler->display->display_options['fields']['title_2']['link_to_node'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'border-color:green;border-size:3px;';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'border-color:red';
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
    'service_instance' => 'service_instance',
  );
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['relationship'] = 'field_course_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Academic home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
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

  /* Display: Services */
  $handler = $view->new_display('page', 'Services', 'page');
  $handler->display->display_options['path'] = 'cis/services/map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Service Map';
  $handler->display->display_options['menu']['description'] = 'Service map';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Courses */
  $handler = $view->new_display('page', 'Courses', 'page_1');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Field: Services in use */
  $handler->display->display_options['fields']['field_services']['id'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['table'] = 'field_data_field_services';
  $handler->display->display_options['fields']['field_services']['field'] = 'field_services';
  $handler->display->display_options['fields']['field_services']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_services']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['text'] = '[field_services]';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course']['id'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_course']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_2']['id'] = 'title_2';
  $handler->display->display_options['fields']['title_2']['table'] = 'node';
  $handler->display->display_options['fields']['title_2']['field'] = 'title';
  $handler->display->display_options['fields']['title_2']['link_to_node'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = 'border-color:green;border-size:3px;';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = 'border-color:red';
  $handler->display->display_options['path'] = 'cis/courses/map';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Course Map';
  $handler->display->display_options['menu']['description'] = 'Visual list of courses';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cis_service_map'] = $view;

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
  $handler->display->display_options['menu']['title'] = 'Services';
  $handler->display->display_options['menu']['description'] = 'List of all services in the CIS';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

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
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
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
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'edit any course content';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
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
  /* Field: Content: Machine name */
  $handler->display->display_options['fields']['field_machine_name_1']['id'] = 'field_machine_name_1';
  $handler->display->display_options['fields']['field_machine_name_1']['table'] = 'field_data_field_machine_name';
  $handler->display->display_options['fields']['field_machine_name_1']['field'] = 'field_machine_name';
  $handler->display->display_options['fields']['field_machine_name_1']['relationship'] = 'field_services_target_id';
  $handler->display->display_options['fields']['field_machine_name_1']['label'] = '';
  $handler->display->display_options['fields']['field_machine_name_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_machine_name_1']['element_label_colon'] = FALSE;
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'field_services_target_id';
  $handler->display->display_options['fields']['title_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['text'] = '[title_1] ([field_machine_name_1])';
  $handler->display->display_options['fields']['title_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title_1']['alter']['path'] = '[field_location]/[field_machine_name]';
  $handler->display->display_options['fields']['title_1']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['title_1']['link_to_node'] = FALSE;
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
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = ' service instance';
  $handler->display->display_options['fields']['edit_node']['text'] = 'edit (admin)';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'field_services_target_id';
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
  $handler->display->display_options['menu']['title'] = 'Services';
  $handler->display->display_options['menu']['description'] = 'Short cuts to service instances used by this course';
  $handler->display->display_options['menu']['weight'] = '5';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['course_service_instances'] = $view;

  $view = new view();
  $view->name = 'course_slider';
  $view->description = 'Breaks the course rendering up into blocks that can be easily positioned';
  $view->tag = 'course';
  $view->base_table = 'node';
  $view->human_name = 'Course displays';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Course slider';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Field: Content: Promotional screenshots for course */
  $handler->display->display_options['fields']['field_screenshot']['id'] = 'field_screenshot';
  $handler->display->display_options['fields']['field_screenshot']['table'] = 'field_data_field_screenshot';
  $handler->display->display_options['fields']['field_screenshot']['field'] = 'field_screenshot';
  $handler->display->display_options['fields']['field_screenshot']['label'] = '';
  $handler->display->display_options['fields']['field_screenshot']['alter']['link_class'] = 'colorbox-inline';
  $handler->display->display_options['fields']['field_screenshot']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_screenshot']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_screenshot']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_screenshot']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_screenshot']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_screenshot']['type'] = 'flexslider';
  $handler->display->display_options['fields']['field_screenshot']['settings'] = array(
    'flexslider_optionset' => 'course',
  );
  $handler->display->display_options['fields']['field_screenshot']['delta_offset'] = '0';
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
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'course' => 'course',
  );
  $handler->display->display_options['arguments']['nid']['validate_options']['access'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Slider */
  $handler = $view->new_display('block', 'Slider', 'block');
  $handler->display->display_options['display_description'] = 'Flex slider block display';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Promotional screenshots for course (field_screenshot:delta) */
  $handler->display->display_options['filters']['delta']['id'] = 'delta';
  $handler->display->display_options['filters']['delta']['table'] = 'field_data_field_screenshot';
  $handler->display->display_options['filters']['delta']['field'] = 'delta';
  $handler->display->display_options['filters']['delta']['operator'] = 'not empty';

  /* Display: Samples */
  $handler = $view->new_display('block', 'Samples', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Samples';
  $handler->display->display_options['display_description'] = 'Links to sample materials';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Sample Syllabus */
  $handler->display->display_options['fields']['field_sample_syllabus']['id'] = 'field_sample_syllabus';
  $handler->display->display_options['fields']['field_sample_syllabus']['table'] = 'field_data_field_sample_syllabus';
  $handler->display->display_options['fields']['field_sample_syllabus']['field'] = 'field_sample_syllabus';
  $handler->display->display_options['fields']['field_sample_syllabus']['label'] = '';
  $handler->display->display_options['fields']['field_sample_syllabus']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_sample_syllabus']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sample_syllabus']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_sample_syllabus']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_sample_syllabus']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sample_syllabus']['type'] = 'file_custom_link';
  $handler->display->display_options['fields']['field_sample_syllabus']['settings'] = array(
    'format_custom_link_text' => 'Sample Syllabus',
  );
  /* Field: Content: Sample Lesson */
  $handler->display->display_options['fields']['field_sample_lesson']['id'] = 'field_sample_lesson';
  $handler->display->display_options['fields']['field_sample_lesson']['table'] = 'field_data_field_sample_lesson';
  $handler->display->display_options['fields']['field_sample_lesson']['field'] = 'field_sample_lesson';
  $handler->display->display_options['fields']['field_sample_lesson']['label'] = '';
  $handler->display->display_options['fields']['field_sample_lesson']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_sample_lesson']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_sample_lesson']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_sample_lesson']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_sample_lesson']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_sample_lesson']['type'] = 'file_custom_link';
  $handler->display->display_options['fields']['field_sample_lesson']['settings'] = array(
    'format_custom_link_text' => 'Sample Lesson',
  );
  /* Field: Content: University Bulletin */
  $handler->display->display_options['fields']['field_university_bulletin']['id'] = 'field_university_bulletin';
  $handler->display->display_options['fields']['field_university_bulletin']['table'] = 'field_data_field_university_bulletin';
  $handler->display->display_options['fields']['field_university_bulletin']['field'] = 'field_university_bulletin';
  $handler->display->display_options['fields']['field_university_bulletin']['label'] = '';
  $handler->display->display_options['fields']['field_university_bulletin']['element_type'] = 'div';
  $handler->display->display_options['fields']['field_university_bulletin']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_university_bulletin']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_university_bulletin']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_university_bulletin']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_university_bulletin']['type'] = 'link_label';

  /* Display: TA Tab */
  $handler = $view->new_display('page', 'TA Tab', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Teaching Assistant Resources';
  $handler->display->display_options['display_description'] = 'Teaching assistant area for documents and resources';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    7 => '7',
    8 => '8',
    10 => '10',
    6 => '6',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Instructions */
  $handler->display->display_options['fields']['field_ta_instructions']['id'] = 'field_ta_instructions';
  $handler->display->display_options['fields']['field_ta_instructions']['table'] = 'field_data_field_ta_instructions';
  $handler->display->display_options['fields']['field_ta_instructions']['field'] = 'field_ta_instructions';
  $handler->display->display_options['fields']['field_ta_instructions']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_ta_instructions']['element_label_colon'] = FALSE;
  /* Field: Content: Documents */
  $handler->display->display_options['fields']['field_ta_documents']['id'] = 'field_ta_documents';
  $handler->display->display_options['fields']['field_ta_documents']['table'] = 'field_data_field_ta_documents';
  $handler->display->display_options['fields']['field_ta_documents']['field'] = 'field_ta_documents';
  $handler->display->display_options['fields']['field_ta_documents']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_ta_documents']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ta_documents']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_ta_documents']['type'] = 'file_table';
  $handler->display->display_options['fields']['field_ta_documents']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'node/%/resources/ta';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Teaching Assistants';
  $handler->display->display_options['menu']['description'] = 'Teaching Assistant Resources';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Offerings';
  $handler->display->display_options['tab_options']['description'] = 'Listing of offerings';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Inst Tab */
  $handler = $view->new_display('page', 'Inst Tab', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Instructor Resources';
  $handler->display->display_options['display_description'] = 'Instructor tab';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    7 => '7',
    8 => '8',
    10 => '10',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Design doc */
  $handler->display->display_options['fields']['field_inst_design_doc']['id'] = 'field_inst_design_doc';
  $handler->display->display_options['fields']['field_inst_design_doc']['table'] = 'field_data_field_inst_design_doc';
  $handler->display->display_options['fields']['field_inst_design_doc']['field'] = 'field_inst_design_doc';
  $handler->display->display_options['fields']['field_inst_design_doc']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_inst_design_doc']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_inst_design_doc']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_inst_design_doc']['settings'] = array(
    'format_custom_link_text' => 'Design document',
  );
  /* Field: Content: Setup guide */
  $handler->display->display_options['fields']['field_inst_setup_guide']['id'] = 'field_inst_setup_guide';
  $handler->display->display_options['fields']['field_inst_setup_guide']['table'] = 'field_data_field_inst_setup_guide';
  $handler->display->display_options['fields']['field_inst_setup_guide']['field'] = 'field_inst_setup_guide';
  $handler->display->display_options['fields']['field_inst_setup_guide']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_inst_setup_guide']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_inst_setup_guide']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_inst_setup_guide']['settings'] = array(
    'format_custom_link_text' => 'Setup Guide',
  );
  /* Field: Content: Delivery Guide */
  $handler->display->display_options['fields']['field_inst_delivery_guide']['id'] = 'field_inst_delivery_guide';
  $handler->display->display_options['fields']['field_inst_delivery_guide']['table'] = 'field_data_field_inst_delivery_guide';
  $handler->display->display_options['fields']['field_inst_delivery_guide']['field'] = 'field_inst_delivery_guide';
  $handler->display->display_options['fields']['field_inst_delivery_guide']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_inst_delivery_guide']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_inst_delivery_guide']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_inst_delivery_guide']['settings'] = array(
    'format_custom_link_text' => 'Delivery Guide',
  );
  /* Field: Content: Other documents */
  $handler->display->display_options['fields']['field_inst_other_documents']['id'] = 'field_inst_other_documents';
  $handler->display->display_options['fields']['field_inst_other_documents']['table'] = 'field_data_field_inst_other_documents';
  $handler->display->display_options['fields']['field_inst_other_documents']['field'] = 'field_inst_other_documents';
  $handler->display->display_options['fields']['field_inst_other_documents']['element_label_type'] = 'h2';
  $handler->display->display_options['fields']['field_inst_other_documents']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_inst_other_documents']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_inst_other_documents']['type'] = 'file_table';
  $handler->display->display_options['fields']['field_inst_other_documents']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'node/%/resources/instructor';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Instructors';
  $handler->display->display_options['menu']['description'] = 'Instructor Resources';
  $handler->display->display_options['menu']['weight'] = '9';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Offerings';
  $handler->display->display_options['tab_options']['description'] = 'Listing of offerings';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Resources Tab */
  $handler = $view->new_display('page', 'Resources Tab', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Resources';
  $handler->display->display_options['display_description'] = 'Resources Tab';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['access'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    3 => '3',
    4 => '4',
    11 => '11',
    7 => '7',
    8 => '8',
    10 => '10',
    6 => '6',
    5 => '5',
    9 => '9',
  );
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '[title] Resources';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/resources';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Resources';
  $handler->display->display_options['menu']['description'] = 'Course Resources';
  $handler->display->display_options['menu']['weight'] = '9';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Offerings';
  $handler->display->display_options['tab_options']['description'] = 'Listing of offerings';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['course_slider'] = $view;

  $view = new view();
  $view->name = 'courses_overview';
  $view->description = 'Pages and Blocks to visualize courses';
  $view->tag = 'CIS';
  $view->base_table = 'node';
  $view->human_name = 'Course pages and blocks';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List';
  $handler->display->display_options['css_class'] = 'course-blocks-display';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '518400';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['reset_button_label'] = 'Show all';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'title' => array(
      'more_options' => array(
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'field_academic_home_target_id' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 1,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'field_program_classification_target_id' => array(
      'bef_format' => 'bef',
      'more_options' => array(
        'bef_select_all_none' => 0,
        'bef_collapsible' => 1,
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
    'title_1' => array(
      'more_options' => array(
        'is_secondary' => 1,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_course_title' => 'field_course_title',
    'field_academic_home' => 'field_academic_home',
    'field_program_classification' => 'field_program_classification',
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
    'field_course_title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_academic_home' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
    'field_program_classification' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'responsive' => '',
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['label'] = 'academic home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['element_wrapper_class'] = 'course-block-banner';
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_block_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['label'] = '';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Program classification */
  $handler->display->display_options['fields']['field_program_classification']['id'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['field'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['label'] = '';
  $handler->display->display_options['fields']['field_program_classification']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_program_classification']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_program_classification']['delta_offset'] = '0';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'field_academic_home_target_id';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title_1']['id'] = 'title_1';
  $handler->display->display_options['sorts']['title_1']['table'] = 'node';
  $handler->display->display_options['sorts']['title_1']['field'] = 'title';
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
  /* Filter criterion: Content: Display in course list (field_display_in_course_list) */
  $handler->display->display_options['filters']['field_display_in_course_list_value']['id'] = 'field_display_in_course_list_value';
  $handler->display->display_options['filters']['field_display_in_course_list_value']['table'] = 'field_data_field_display_in_course_list';
  $handler->display->display_options['filters']['field_display_in_course_list_value']['field'] = 'field_display_in_course_list_value';
  $handler->display->display_options['filters']['field_display_in_course_list_value']['value'] = array(
    1 => '1',
  );
  $handler->display->display_options['filters']['field_display_in_course_list_value']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'starts';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Find a course';
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
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  $handler->display->display_options['filters']['title']['group_info']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['group_info']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['title']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Academic unit';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['field_academic_home_target_id']['group_info']['label'] = 'Academic home (field_academic_home)';
  $handler->display->display_options['filters']['field_academic_home_target_id']['group_info']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['group'] = 1;
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['title_1']['id'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['table'] = 'node';
  $handler->display->display_options['filters']['title_1']['field'] = 'title';
  $handler->display->display_options['filters']['title_1']['operator'] = 'ends';
  $handler->display->display_options['filters']['title_1']['group'] = 1;
  $handler->display->display_options['filters']['title_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title_1']['expose']['operator_id'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['label'] = 'Course number';
  $handler->display->display_options['filters']['title_1']['expose']['operator'] = 'title_1_op';
  $handler->display->display_options['filters']['title_1']['expose']['identifier'] = 'title_1';
  $handler->display->display_options['filters']['title_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['title_1']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title_1']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title_1']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title_1']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title_1']['expose']['autocomplete_dependent'] = 0;

  /* Display: Visual */
  $handler = $view->new_display('page', 'Visual', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Browse the catalog';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_academic_home',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['items_width'] = '';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['label'] = 'academic unit';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['element_wrapper_class'] = 'course-block-banner';
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_block_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color']['element_wrapper_class'] = 'course-block-color';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'course-block-title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['label'] = '';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course_title']['element_wrapper_class'] = 'course-block-name';
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['element_wrapper_class'] = 'course-block-unit';
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'course-block-details';
  $handler->display->display_options['fields']['view_node']['text'] = 'Details';
  $handler->display->display_options['path'] = 'courses';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Courses';
  $handler->display->display_options['menu']['description'] = 'Listing of courses';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Courses';
  $handler->display->display_options['tab_options']['description'] = 'All available online courses';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'main-menu';

  /* Display: List */
  $handler = $view->new_display('page', 'List', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Name';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['label'] = 'Title';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = 'Academic Unit';
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
  $handler->display->display_options['path'] = 'courses/list';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = 'Listing of courses';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Author block */
  $handler = $view->new_display('block', 'Author block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses Authored';
  $handler->display->display_options['display_description'] = 'Block of courses authored by the contextual user';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['element_wrapper_class'] = 'course-block-banner';
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_block_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color']['element_wrapper_class'] = 'course-block-color';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'course-block-title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['label'] = '';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course_title']['element_wrapper_class'] = 'course-block-name';
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['element_wrapper_class'] = 'course-block-unit';
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'course-block-details';
  $handler->display->display_options['fields']['view_node']['text'] = 'Details';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Course Author (field_course_author) */
  $handler->display->display_options['arguments']['field_course_author_target_id']['id'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['table'] = 'field_data_field_course_author';
  $handler->display->display_options['arguments']['field_course_author_target_id']['field'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_author_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_course_author_target_id']['validate_options']['types'] = array(
    'person' => 'person',
  );
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
  $handler->display->display_options['block_description'] = 'Course Author';

  /* Display: Instructor Highlights */
  $handler = $view->new_display('block', 'Instructor Highlights', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Highlight Reel';
  $handler->display->display_options['defaults']['css_class'] = FALSE;
  $handler->display->display_options['display_description'] = 'Media for this instructor';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '350';
  $handler->display->display_options['style_options']['items_height'] = '200';
  $handler->display->display_options['style_options']['advanced_layout'] = array(
    'align' => TRUE,
    'margins' => TRUE,
  );
  $handler->display->display_options['style_options']['list_alignment'] = 'center';
  $handler->display->display_options['style_options']['items_alignment'] = 'center';
  $handler->display->display_options['style_options']['items_h_margin'] = '0.2em';
  $handler->display->display_options['style_options']['items_v_margin'] = '0.2em';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Author video */
  $handler->display->display_options['fields']['field_author_video']['id'] = 'field_author_video';
  $handler->display->display_options['fields']['field_author_video']['table'] = 'field_data_field_author_video';
  $handler->display->display_options['fields']['field_author_video']['field'] = 'field_author_video';
  $handler->display->display_options['fields']['field_author_video']['label'] = '';
  $handler->display->display_options['fields']['field_author_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_author_video']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_author_video']['settings'] = array(
    'video_style' => 'normal',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['sorts']['changed']['order'] = 'DESC';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Course Author (field_course_author) */
  $handler->display->display_options['arguments']['field_course_author_target_id']['id'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['table'] = 'field_data_field_course_author';
  $handler->display->display_options['arguments']['field_course_author_target_id']['field'] = 'field_course_author_target_id';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_course_author_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_author_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_course_author_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_course_author_target_id']['validate_options']['types'] = array(
    'person' => 'person',
  );
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
  /* Filter criterion: Content: Author video (field_author_video:video_url) */
  $handler->display->display_options['filters']['field_author_video_video_url']['id'] = 'field_author_video_video_url';
  $handler->display->display_options['filters']['field_author_video_video_url']['table'] = 'field_data_field_author_video';
  $handler->display->display_options['filters']['field_author_video_video_url']['field'] = 'field_author_video_video_url';
  $handler->display->display_options['filters']['field_author_video_video_url']['operator'] = 'not empty';
  $handler->display->display_options['block_description'] = 'Instructor Highlites';

  /* Display: Related Course */
  $handler = $view->new_display('block', 'Related Course', 'block_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Related Courses';
  $handler->display->display_options['display_description'] = 'Courses related to this one';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'mini';
  $handler->display->display_options['pager']['options']['items_per_page'] = '4';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['label'] = 'academic home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_related_courses_target_id']['id'] = 'field_related_courses_target_id';
  $handler->display->display_options['relationships']['field_related_courses_target_id']['table'] = 'field_data_field_related_courses';
  $handler->display->display_options['relationships']['field_related_courses_target_id']['field'] = 'field_related_courses_target_id';
  $handler->display->display_options['relationships']['field_related_courses_target_id']['label'] = 'related courses';
  $handler->display->display_options['relationships']['field_related_courses_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['relationship'] = 'field_related_courses_target_id';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['element_wrapper_class'] = 'course-block-banner';
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_block_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color']['element_wrapper_class'] = 'course-block-color';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_related_courses_target_id';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'course-block-title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['relationship'] = 'field_related_courses_target_id';
  $handler->display->display_options['fields']['field_course_title']['label'] = '';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course_title']['element_wrapper_class'] = 'course-block-name';
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['relationship'] = 'field_related_courses_target_id';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['element_wrapper_class'] = 'course-block-unit';
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['relationship'] = 'field_related_courses_target_id';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'course-block-details';
  $handler->display->display_options['fields']['view_node']['text'] = 'Details';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Updated date */
  $handler->display->display_options['sorts']['changed']['id'] = 'changed';
  $handler->display->display_options['sorts']['changed']['table'] = 'node';
  $handler->display->display_options['sorts']['changed']['field'] = 'changed';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    'course' => 'course',
  );
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
  $handler->display->display_options['block_description'] = 'Related Courses';

  /* Display: Program courses */
  $handler = $view->new_display('block', 'Program courses', 'block_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Courses';
  $handler->display->display_options['display_description'] = 'Courses in this program of study';
  $handler->display->display_options['defaults']['exposed_form'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '';
  $handler->display->display_options['style_options']['box_shadow'] = '0';
  $handler->display->display_options['style_options']['border_radius'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['label'] = 'academic home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  /* Relationship: Course */
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['id'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['field'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['ui_name'] = 'Course';
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['label'] = 'Course';
  $handler->display->display_options['relationships']['reverse_field_program_classification_node']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Banner */
  $handler->display->display_options['fields']['field_banner']['id'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['table'] = 'field_data_field_banner';
  $handler->display->display_options['fields']['field_banner']['field'] = 'field_banner';
  $handler->display->display_options['fields']['field_banner']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['fields']['field_banner']['label'] = '';
  $handler->display->display_options['fields']['field_banner']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_banner']['element_wrapper_class'] = 'course-block-banner';
  $handler->display->display_options['fields']['field_banner']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_banner']['settings'] = array(
    'image_style' => 'course_block_thumb',
    'image_link' => 'content',
  );
  /* Field: Content: Color */
  $handler->display->display_options['fields']['field_color']['id'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['table'] = 'field_data_field_color';
  $handler->display->display_options['fields']['field_color']['field'] = 'field_color';
  $handler->display->display_options['fields']['field_color']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_color']['label'] = '';
  $handler->display->display_options['fields']['field_color']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_color']['element_wrapper_class'] = 'course-block-color';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_type'] = '0';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['element_wrapper_class'] = 'course-block-title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Course title */
  $handler->display->display_options['fields']['field_course_title']['id'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['table'] = 'field_data_field_course_title';
  $handler->display->display_options['fields']['field_course_title']['field'] = 'field_course_title';
  $handler->display->display_options['fields']['field_course_title']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['fields']['field_course_title']['label'] = '';
  $handler->display->display_options['fields']['field_course_title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course_title']['element_wrapper_class'] = 'course-block-name';
  /* Field: Content: Academic home */
  $handler->display->display_options['fields']['field_academic_home']['id'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['field'] = 'field_academic_home';
  $handler->display->display_options['fields']['field_academic_home']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['fields']['field_academic_home']['label'] = '';
  $handler->display->display_options['fields']['field_academic_home']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_academic_home']['element_wrapper_class'] = 'course-block-unit';
  $handler->display->display_options['fields']['field_academic_home']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_academic_home']['delta_offset'] = '0';
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['fields']['view_node']['label'] = '';
  $handler->display->display_options['fields']['view_node']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['view_node']['element_wrapper_class'] = 'course-block-details';
  $handler->display->display_options['fields']['view_node']['text'] = 'Details';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['defaults']['arguments'] = FALSE;
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
    'program' => 'program',
  );
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
  $handler->display->display_options['filters']['type']['relationship'] = 'reverse_field_program_classification_node';
  $handler->display->display_options['filters']['type']['value'] = array(
    'course' => 'course',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['block_description'] = 'Program courses';
  $export['courses_overview'] = $view;

  $view = new view();
  $view->name = 'per_academic_unit_charts';
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
    3 => '3',
    8 => '8',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 1,
    ),
  );
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['style_options']['title'] = 'Seats over time';
  $handler->display->display_options['style_options']['type'] = 'ColumnChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '500';
  $handler->display->display_options['style_options']['3d'] = 1;
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
  $export['per_academic_unit_charts'] = $view;

  $view = new view();
  $view->name = 'person_in_the_news';
  $view->description = 'News associated with an entity that shows up on that entity\'s page';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Recent news';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Recent news';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_news_image' => 'field_news_image',
    'title' => 'title',
  );
  /* Field: Content: News Image */
  $handler->display->display_options['fields']['field_news_image']['id'] = 'field_news_image';
  $handler->display->display_options['fields']['field_news_image']['table'] = 'field_data_field_news_image';
  $handler->display->display_options['fields']['field_news_image']['field'] = 'field_news_image';
  $handler->display->display_options['fields']['field_news_image']['label'] = '';
  $handler->display->display_options['fields']['field_news_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_news_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_news_image']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => 'content',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Related (field_related_entity) */
  $handler->display->display_options['arguments']['field_related_entity_target_id']['id'] = 'field_related_entity_target_id';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['table'] = 'field_data_field_related_entity';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['field'] = 'field_related_entity_target_id';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_related_entity_target_id']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_related_entity_target_id']['validate_options']['types'] = array(
    'academic_unit' => 'academic_unit',
    'program' => 'program',
    'service' => 'service',
    'college_services' => 'college_services',
    'person' => 'person',
  );
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
    'news' => 'news',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['person_in_the_news'] = $view;

  $view = new view();
  $view->name = 'person_references';
  $view->description = 'Use this for doing entity references to person nodes';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Person references';
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
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Internal Classification */
  $handler->display->display_options['fields']['field_internal_classification']['id'] = 'field_internal_classification';
  $handler->display->display_options['fields']['field_internal_classification']['table'] = 'field_data_field_internal_classification';
  $handler->display->display_options['fields']['field_internal_classification']['field'] = 'field_internal_classification';
  $handler->display->display_options['fields']['field_internal_classification']['label'] = '';
  $handler->display->display_options['fields']['field_internal_classification']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_internal_classification']['alter']['text'] = '([field_internal_classification-value])';
  $handler->display->display_options['fields']['field_internal_classification']['element_label_colon'] = FALSE;
  /* Sort criterion: Content: Internal Classification (field_internal_classification) */
  $handler->display->display_options['sorts']['field_internal_classification_value']['id'] = 'field_internal_classification_value';
  $handler->display->display_options['sorts']['field_internal_classification_value']['table'] = 'field_data_field_internal_classification';
  $handler->display->display_options['sorts']['field_internal_classification_value']['field'] = 'field_internal_classification_value';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
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

  /* Display: Entity Reference */
  $handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'title' => 'title',
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entityreference_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;

  /* Display: Faculty */
  $handler = $view->new_display('entityreference', 'Faculty', 'entityreference_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
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
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
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
    'person' => 'person',
  );
  /* Filter criterion: Content: Internal Classification (field_internal_classification) */
  $handler->display->display_options['filters']['field_internal_classification_value']['id'] = 'field_internal_classification_value';
  $handler->display->display_options['filters']['field_internal_classification_value']['table'] = 'field_data_field_internal_classification';
  $handler->display->display_options['filters']['field_internal_classification_value']['field'] = 'field_internal_classification_value';
  $handler->display->display_options['filters']['field_internal_classification_value']['value'] = array(
    'faculty' => 'faculty',
  );
  $export['person_references'] = $view;

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
    9 => '9',
    11 => '11',
    5 => '5',
    10 => '10',
    6 => '6',
    4 => '4',
    7 => '7',
    8 => '8',
    3 => '3',
  );

  /* Display: Unit Heads */
  $handler = $view->new_display('entityreference', 'Unit Heads', 'entityreference_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
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
    5 => '5',
    10 => '10',
  );

  /* Display: Coordinators */
  $handler = $view->new_display('entityreference', 'Coordinators', 'entityreference_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
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
    11 => '11',
    10 => '10',
    4 => '4',
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
    6 => '6',
  );

  /* Display: World Campus */
  $handler = $view->new_display('entityreference', 'World Campus', 'entityreference_4');
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
    11 => '11',
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
    9 => '9',
  );

  /* Display: Learning Designer */
  $handler = $view->new_display('entityreference', 'Learning Designer', 'entityreference_6');
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
    7 => '7',
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
    8 => '8',
    3 => '3',
  );

  /* Display: Deans */
  $handler = $view->new_display('entityreference', 'Deans', 'entityreference_8');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'entityreference_style';
  $handler->display->display_options['style_options']['search_fields'] = array(
    'field_first_name' => 'field_first_name',
    'field_last_name' => 'field_last_name',
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
    5 => '5',
  );

  /* Display: University employees */
  $handler = $view->new_display('entityreference', 'University employees', 'entityreference_10');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '0';
  $handler->display->display_options['pager']['options']['offset'] = '0';
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
    9 => '9',
    11 => '11',
    5 => '5',
    10 => '10',
    6 => '6',
    4 => '4',
    7 => '7',
    8 => '8',
    3 => '3',
  );
  $handler->display->display_options['filters']['rid']['reduce_duplicates'] = TRUE;
  $export['user_type_lists'] = $view;

  return $export;
}
