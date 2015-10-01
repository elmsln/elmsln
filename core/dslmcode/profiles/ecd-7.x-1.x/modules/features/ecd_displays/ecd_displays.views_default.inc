<?php
/**
 * @file
 * ecd_displays.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function ecd_displays_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'ecd_asset_audit';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Asset Audit';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Asset Compliance';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['expose_sort_order'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_course' => 'field_course',
    'title' => 'title',
    'field_accessibility_verified_editable' => 'field_accessibility_verified_editable',
    'field_copyright_verified_editable' => 'field_copyright_verified_editable',
    'field_quality_verified_editable' => 'field_quality_verified_editable',
    'field_source' => 'field_source',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_course' => array(
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
    'field_accessibility_verified_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_copyright_verified_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_quality_verified_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_source' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['caption'] = 'Current status of the compliance audit for this course';
  $handler->display->display_options['style_options']['save_messages'] = 'summary';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course']['id'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['settings'] = array(
    'link' => 0,
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Accessibility verified (editable) */
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['id'] = 'field_accessibility_verified_editable';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['table'] = 'field_data_field_accessibility_verified';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['field'] = 'field_accessibility_verified_editable';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['label'] = 'Accessibility verified';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_accessibility_verified_editable']['suppress_description'] = 1;
  /* Field: Content: Copyright verified (editable) */
  $handler->display->display_options['fields']['field_copyright_verified_editable']['id'] = 'field_copyright_verified_editable';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['table'] = 'field_data_field_copyright_verified';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['field'] = 'field_copyright_verified_editable';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['label'] = 'Copyright verified';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_copyright_verified_editable']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_copyright_verified_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_copyright_verified_editable']['suppress_description'] = 1;
  /* Field: Content: Quality verified (editable) */
  $handler->display->display_options['fields']['field_quality_verified_editable']['id'] = 'field_quality_verified_editable';
  $handler->display->display_options['fields']['field_quality_verified_editable']['table'] = 'field_data_field_quality_verified';
  $handler->display->display_options['fields']['field_quality_verified_editable']['field'] = 'field_quality_verified_editable';
  $handler->display->display_options['fields']['field_quality_verified_editable']['label'] = 'Quality verified';
  $handler->display->display_options['fields']['field_quality_verified_editable']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_quality_verified_editable']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['field_quality_verified_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_quality_verified_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_quality_verified_editable']['suppress_description'] = 1;
  /* Field: Content: Source */
  $handler->display->display_options['fields']['field_source']['id'] = 'field_source';
  $handler->display->display_options['fields']['field_source']['table'] = 'field_data_field_source';
  $handler->display->display_options['fields']['field_source']['field'] = 'field_source';
  $handler->display->display_options['fields']['field_source']['click_sort_column'] = 'url';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Course (field_course) */
  $handler->display->display_options['arguments']['field_course_target_id']['id'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['field_course_target_id']['table'] = 'field_data_field_course';
  $handler->display->display_options['arguments']['field_course_target_id']['field'] = 'field_course_target_id';
  $handler->display->display_options['arguments']['field_course_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_course_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_course_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_course_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_course_target_id']['summary_options']['items_per_page'] = '25';
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
    'ecd_asset' => 'ecd_asset',
  );
  /* Filter criterion: Content: Accessibility verified (field_accessibility_verified) */
  $handler->display->display_options['filters']['field_accessibility_verified_value']['id'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['table'] = 'field_data_field_accessibility_verified';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['field'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_accessibility_verified_value']['expose']['operator_id'] = 'field_accessibility_verified_value_op';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['expose']['label'] = 'Accessibility verified (field_accessibility_verified)';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['expose']['operator'] = 'field_accessibility_verified_value_op';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['expose']['identifier'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_accessibility_verified_value']['group_info']['label'] = 'Accessibility';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['group_info']['identifier'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Not Verified',
      'operator' => 'or',
      'value' => array(
        0 => '0',
      ),
    ),
    2 => array(
      'title' => 'Verified',
      'operator' => 'or',
      'value' => array(
        1 => '1',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => 'or',
      'value' => array(),
    ),
  );
  /* Filter criterion: Content: Copyright verified (field_copyright_verified) */
  $handler->display->display_options['filters']['field_copyright_verified_value']['id'] = 'field_copyright_verified_value';
  $handler->display->display_options['filters']['field_copyright_verified_value']['table'] = 'field_data_field_copyright_verified';
  $handler->display->display_options['filters']['field_copyright_verified_value']['field'] = 'field_copyright_verified_value';
  $handler->display->display_options['filters']['field_copyright_verified_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_copyright_verified_value']['expose']['operator_id'] = 'field_copyright_verified_value_op';
  $handler->display->display_options['filters']['field_copyright_verified_value']['expose']['label'] = 'Copyright verified (field_copyright_verified)';
  $handler->display->display_options['filters']['field_copyright_verified_value']['expose']['operator'] = 'field_copyright_verified_value_op';
  $handler->display->display_options['filters']['field_copyright_verified_value']['expose']['identifier'] = 'field_copyright_verified_value';
  $handler->display->display_options['filters']['field_copyright_verified_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_copyright_verified_value']['group_info']['label'] = 'Copyright';
  $handler->display->display_options['filters']['field_copyright_verified_value']['group_info']['identifier'] = 'field_copyright_verified_value';
  $handler->display->display_options['filters']['field_copyright_verified_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Not Verified',
      'operator' => 'or',
      'value' => array(
        0 => '0',
      ),
    ),
    2 => array(
      'title' => 'Verified',
      'operator' => 'or',
      'value' => array(
        1 => '1',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => 'or',
      'value' => array(),
    ),
  );
  /* Filter criterion: Content: Quality verified (field_quality_verified) */
  $handler->display->display_options['filters']['field_quality_verified_value']['id'] = 'field_quality_verified_value';
  $handler->display->display_options['filters']['field_quality_verified_value']['table'] = 'field_data_field_quality_verified';
  $handler->display->display_options['filters']['field_quality_verified_value']['field'] = 'field_quality_verified_value';
  $handler->display->display_options['filters']['field_quality_verified_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_quality_verified_value']['expose']['operator_id'] = 'field_quality_verified_value_op';
  $handler->display->display_options['filters']['field_quality_verified_value']['expose']['label'] = 'Quality verified (field_quality_verified)';
  $handler->display->display_options['filters']['field_quality_verified_value']['expose']['operator'] = 'field_quality_verified_value_op';
  $handler->display->display_options['filters']['field_quality_verified_value']['expose']['identifier'] = 'field_quality_verified_value';
  $handler->display->display_options['filters']['field_quality_verified_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_quality_verified_value']['group_info']['label'] = 'Quality';
  $handler->display->display_options['filters']['field_quality_verified_value']['group_info']['identifier'] = 'field_quality_verified_value';
  $handler->display->display_options['filters']['field_quality_verified_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Not Verified',
      'operator' => 'or',
      'value' => array(
        0 => '0',
      ),
    ),
    2 => array(
      'title' => 'Verified',
      'operator' => 'or',
      'value' => array(
        1 => '1',
      ),
    ),
    3 => array(
      'title' => '',
      'operator' => 'or',
      'value' => array(),
    ),
  );

  /* Display: Overview */
  $handler = $view->new_display('page', 'Overview', 'page_1');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  $handler->display->display_options['path'] = 'asset-compliance';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Assets';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Course specific */
  $handler = $view->new_display('page', 'Course specific', 'page');
  $handler->display->display_options['path'] = 'asset-compliance/%';

  /* Display: Course EVA */
  $handler = $view->new_display('entity_view', 'Course EVA', 'entity_view_1');
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'cis_course',
  );
  $export['ecd_asset_audit'] = $view;

  $view = new view();
  $view->name = 'ecd_bulk_update';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ECD bulk update';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Bulk Course Update';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['row_clickable'] = 1;
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
        'show_all_tokens' => 1,
        'display_values' => array(
          'cis_course::field_accessibility_audit' => 'cis_course::field_accessibility_audit',
          'cis_course::field_copyright_audit' => 'cis_course::field_copyright_audit',
          'cis_course::field_quality_audit' => 'cis_course::field_quality_audit',
        ),
      ),
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Accessibility audit */
  $handler->display->display_options['fields']['field_accessibility_audit']['id'] = 'field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['table'] = 'field_data_field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['field'] = 'field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['label'] = 'Accessibility';
  /* Field: Content: Copyright audit */
  $handler->display->display_options['fields']['field_copyright_audit']['id'] = 'field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['table'] = 'field_data_field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['field'] = 'field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['label'] = 'Copyright';
  /* Field: Content: Quality Audit */
  $handler->display->display_options['fields']['field_quality_audit']['id'] = 'field_quality_audit';
  $handler->display->display_options['fields']['field_quality_audit']['table'] = 'field_data_field_quality_audit';
  $handler->display->display_options['fields']['field_quality_audit']['field'] = 'field_quality_audit';
  /* Field: Content: Last formal quality audit */
  $handler->display->display_options['fields']['field_last_quality_date']['id'] = 'field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['table'] = 'field_data_field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['field'] = 'field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
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
    'cis_course' => 'cis_course',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'courses/bulk-update';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Bulk Update Courses';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-comply-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['ecd_bulk_update'] = $view;

  $view = new view();
  $view->name = 'ecd_quality_overview';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Compliance Overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Course Compliance';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_accessibility_audit' => 'field_accessibility_audit',
    'field_copyright_audit' => 'field_copyright_audit',
    'field_last_quality_date' => 'field_last_quality_date',
    'field_quality_audit' => 'field_quality_audit',
  );
  $handler->display->display_options['style_options']['default'] = 'title';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_accessibility_audit' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_copyright_audit' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_last_quality_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_quality_audit' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_course_node']['id'] = 'reverse_field_course_node';
  $handler->display->display_options['relationships']['reverse_field_course_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_course_node']['field'] = 'reverse_field_course_node';
  $handler->display->display_options['relationships']['reverse_field_course_node']['label'] = 'Asset';
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Accessibility audit */
  $handler->display->display_options['fields']['field_accessibility_audit']['id'] = 'field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['table'] = 'field_data_field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['field'] = 'field_accessibility_audit';
  $handler->display->display_options['fields']['field_accessibility_audit']['label'] = 'Accessibility';
  /* Field: Content: Copyright audit */
  $handler->display->display_options['fields']['field_copyright_audit']['id'] = 'field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['table'] = 'field_data_field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['field'] = 'field_copyright_audit';
  $handler->display->display_options['fields']['field_copyright_audit']['label'] = 'Copyright';
  /* Field: Content: Last formal quality audit */
  $handler->display->display_options['fields']['field_last_quality_date']['id'] = 'field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['table'] = 'field_data_field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['field'] = 'field_last_quality_date';
  $handler->display->display_options['fields']['field_last_quality_date']['label'] = 'Last QA';
  $handler->display->display_options['fields']['field_last_quality_date']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Quality Audit */
  $handler->display->display_options['fields']['field_quality_audit']['id'] = 'field_quality_audit';
  $handler->display->display_options['fields']['field_quality_audit']['table'] = 'field_data_field_quality_audit';
  $handler->display->display_options['fields']['field_quality_audit']['field'] = 'field_quality_audit';
  $handler->display->display_options['fields']['field_quality_audit']['label'] = 'Quality';
  /* Field: COUNT(Content: Nid) */
  $handler->display->display_options['fields']['nid_1']['id'] = 'nid_1';
  $handler->display->display_options['fields']['nid_1']['table'] = 'node';
  $handler->display->display_options['fields']['nid_1']['field'] = 'nid';
  $handler->display->display_options['fields']['nid_1']['relationship'] = 'reverse_field_course_node';
  $handler->display->display_options['fields']['nid_1']['group_type'] = 'count';
  $handler->display->display_options['fields']['nid_1']['label'] = 'Assets';
  $handler->display->display_options['fields']['nid_1']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['nid_1']['alter']['path'] = 'asset-compliance/[nid]';
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
    'cis_course' => 'cis_course',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'courses/compliance';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Course Compliance';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-comply-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['ecd_quality_overview'] = $view;

  return $export;
}
