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
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_course']['delta_offset'] = '0';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Asset';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
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
  /* Field: Content: Needs review (editable) */
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['id'] = 'field_ecd_needs_review_editable';
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['table'] = 'field_data_field_ecd_needs_review';
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['field'] = 'field_ecd_needs_review_editable';
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['label'] = 'Needs review';
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['suppress_label'] = 1;
  $handler->display->display_options['fields']['field_ecd_needs_review_editable']['suppress_description'] = 1;
  /* Field: Content: Source */
  $handler->display->display_options['fields']['field_source']['id'] = 'field_source';
  $handler->display->display_options['fields']['field_source']['table'] = 'field_data_field_source';
  $handler->display->display_options['fields']['field_source']['field'] = 'field_source';
  $handler->display->display_options['fields']['field_source']['click_sort_column'] = 'url';
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
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
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Accessibility verified (field_accessibility_verified) */
  $handler->display->display_options['filters']['field_accessibility_verified_value']['id'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['table'] = 'field_data_field_accessibility_verified';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['field'] = 'field_accessibility_verified_value';
  $handler->display->display_options['filters']['field_accessibility_verified_value']['group'] = 1;
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
  $handler->display->display_options['filters']['field_copyright_verified_value']['group'] = 1;
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
  $handler->display->display_options['filters']['field_quality_verified_value']['group'] = 1;
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
  /* Filter criterion: Content: Needs review (field_ecd_needs_review) */
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['id'] = 'field_ecd_needs_review_value';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['table'] = 'field_data_field_ecd_needs_review';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['field'] = 'field_ecd_needs_review_value';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['group'] = 1;
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['expose']['operator_id'] = 'field_ecd_needs_review_value_op';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['expose']['label'] = 'Needs review';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['expose']['operator'] = 'field_ecd_needs_review_value_op';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['expose']['identifier'] = 'field_ecd_needs_review_value';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['group_info']['label'] = 'Needs review';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['group_info']['identifier'] = 'field_ecd_needs_review_value';
  $handler->display->display_options['filters']['field_ecd_needs_review_value']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Yes',
      'operator' => 'or',
      'value' => array(
        1 => '1',
      ),
    ),
    2 => array(
      'title' => '',
      'operator' => 'or',
      'value' => array(),
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
  $handler->display->display_options['path'] = 'assets';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Assets';
  $handler->display->display_options['menu']['description'] = 'All system assets on record';
  $handler->display->display_options['menu']['weight'] = '-10';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
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
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['ecd_bulk_update'] = $view;

  $view = new view();
  $view->name = 'ecd_documentation';
  $view->description = 'Documentation for copyright to be on file';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ECD Documentation';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Asset Documentation';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Copyright justification */
  $handler->display->display_options['fields']['field_copyright_justification']['id'] = 'field_copyright_justification';
  $handler->display->display_options['fields']['field_copyright_justification']['table'] = 'field_data_field_copyright_justification';
  $handler->display->display_options['fields']['field_copyright_justification']['field'] = 'field_copyright_justification';
  $handler->display->display_options['fields']['field_copyright_justification']['label'] = 'Justification';
  /* Field: Content: Related asset */
  $handler->display->display_options['fields']['field_ecd_related_asset']['id'] = 'field_ecd_related_asset';
  $handler->display->display_options['fields']['field_ecd_related_asset']['table'] = 'field_data_field_ecd_related_asset';
  $handler->display->display_options['fields']['field_ecd_related_asset']['field'] = 'field_ecd_related_asset';
  $handler->display->display_options['fields']['field_ecd_related_asset']['label'] = 'Asset';
  $handler->display->display_options['fields']['field_ecd_related_asset']['settings'] = array(
    'link' => 1,
  );
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
    'ecd_documentation' => 'ecd_documentation',
  );
  /* Filter criterion: Content: Copyright justification (field_copyright_justification) */
  $handler->display->display_options['filters']['field_copyright_justification_value']['id'] = 'field_copyright_justification_value';
  $handler->display->display_options['filters']['field_copyright_justification_value']['table'] = 'field_data_field_copyright_justification';
  $handler->display->display_options['filters']['field_copyright_justification_value']['field'] = 'field_copyright_justification_value';
  $handler->display->display_options['filters']['field_copyright_justification_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_copyright_justification_value']['expose']['operator_id'] = 'field_copyright_justification_value_op';
  $handler->display->display_options['filters']['field_copyright_justification_value']['expose']['label'] = 'Copyright justification';
  $handler->display->display_options['filters']['field_copyright_justification_value']['expose']['operator'] = 'field_copyright_justification_value_op';
  $handler->display->display_options['filters']['field_copyright_justification_value']['expose']['identifier'] = 'field_copyright_justification_value';
  $handler->display->display_options['filters']['field_copyright_justification_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'asset/documentation';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Documentation';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $export['ecd_documentation'] = $view;

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
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['ecd_quality_overview'] = $view;

  $view = new view();
  $view->name = 'ecd_systems';
  $view->description = 'Systems that requests can be associated to';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ECD Systems';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Systems';
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
    'cis_system' => 'cis_system',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'ecd-systems';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Systems';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $export['ecd_systems'] = $view;

  $view = new view();
  $view->name = 'eva_systems';
  $view->description = 'EVA for systems to show access requests';
  $view->tag = 'default';
  $view->base_table = 'entityform';
  $view->human_name = 'EVA Systems';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Access requests';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'link_entityform' => 'link_entityform',
    'field_account_request' => 'field_account_request',
    'field_role' => 'field_role',
    'field_duration' => 'field_duration',
    'field_access_status' => 'field_access_status',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'link_entityform' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_account_request' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_role' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_duration' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_access_status' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Entityform Submission: Link */
  $handler->display->display_options['fields']['link_entityform']['id'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['link_entityform']['field'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['label'] = '';
  $handler->display->display_options['fields']['link_entityform']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['link_entityform']['text'] = 'View';
  /* Field: Entityform Submission: Account Request */
  $handler->display->display_options['fields']['field_account_request']['id'] = 'field_account_request';
  $handler->display->display_options['fields']['field_account_request']['table'] = 'field_data_field_account_request';
  $handler->display->display_options['fields']['field_account_request']['field'] = 'field_account_request';
  /* Field: Entityform Submission: Role */
  $handler->display->display_options['fields']['field_role']['id'] = 'field_role';
  $handler->display->display_options['fields']['field_role']['table'] = 'field_data_field_role';
  $handler->display->display_options['fields']['field_role']['field'] = 'field_role';
  /* Field: Entityform Submission: Duration */
  $handler->display->display_options['fields']['field_duration']['id'] = 'field_duration';
  $handler->display->display_options['fields']['field_duration']['table'] = 'field_data_field_duration';
  $handler->display->display_options['fields']['field_duration']['field'] = 'field_duration';
  $handler->display->display_options['fields']['field_duration']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Entityform Submission: Status */
  $handler->display->display_options['fields']['field_access_status']['id'] = 'field_access_status';
  $handler->display->display_options['fields']['field_access_status']['table'] = 'field_data_field_access_status';
  $handler->display->display_options['fields']['field_access_status']['field'] = 'field_access_status';
  /* Contextual filter: Entityform Submission: System(s) (field_ecd_systems) */
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['id'] = 'field_ecd_systems_target_id';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['table'] = 'field_data_field_ecd_systems';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['field'] = 'field_ecd_systems_target_id';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_ecd_systems_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Entityform Submission: Entityform Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'entityform';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'system_access_request' => 'system_access_request',
  );
  /* Filter criterion: Entityform Submission: Status (field_access_status) */
  $handler->display->display_options['filters']['field_access_status_value']['id'] = 'field_access_status_value';
  $handler->display->display_options['filters']['field_access_status_value']['table'] = 'field_data_field_access_status';
  $handler->display->display_options['filters']['field_access_status_value']['field'] = 'field_access_status_value';
  $handler->display->display_options['filters']['field_access_status_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_access_status_value']['expose']['operator_id'] = 'field_access_status_value_op';
  $handler->display->display_options['filters']['field_access_status_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_access_status_value']['expose']['operator'] = 'field_access_status_value_op';
  $handler->display->display_options['filters']['field_access_status_value']['expose']['identifier'] = 'field_access_status_value';
  $handler->display->display_options['filters']['field_access_status_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );

  /* Display: EVA Field */
  $handler = $view->new_display('entity_view', 'EVA Field', 'entity_view_1');
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'cis_system',
  );
  $export['eva_systems'] = $view;

  return $export;
}
