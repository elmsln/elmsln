<?php
/**
 * @file
 * editableviews_test_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function editableviews_test_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'test_editable_views_node_fields';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Test editable views node fields';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Test editable views node title';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  /* Field: Content: Test editable text (editable) */
  $handler->display->display_options['fields']['field_test_editable_text_editable']['id'] = 'field_test_editable_text_editable';
  $handler->display->display_options['fields']['field_test_editable_text_editable']['table'] = 'field_data_field_test_editable_text';
  $handler->display->display_options['fields']['field_test_editable_text_editable']['field'] = 'field_test_editable_text_editable';
  $handler->display->display_options['fields']['field_test_editable_text_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_test_editable_text_editable']['suppress_label'] = 0;
  $handler->display->display_options['fields']['field_test_editable_text_editable']['suppress_description'] = 0;
  /* Field: Content: Test editable options (editable) */
  $handler->display->display_options['fields']['field_test_editable_options_editable']['id'] = 'field_test_editable_options_editable';
  $handler->display->display_options['fields']['field_test_editable_options_editable']['table'] = 'field_data_field_test_editable_options';
  $handler->display->display_options['fields']['field_test_editable_options_editable']['field'] = 'field_test_editable_options_editable';
  $handler->display->display_options['fields']['field_test_editable_options_editable']['widget_type'] = '0';
  $handler->display->display_options['fields']['field_test_editable_options_editable']['suppress_label'] = 0;
  $handler->display->display_options['fields']['field_test_editable_options_editable']['suppress_description'] = 0;
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
    'editable_views_test_node' => 'editable_views_test_node',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test-editable-views-node-fields';
  $export['test_editable_views_node_fields'] = $view;

  $view = new view();
  $view->name = 'test_editable_views_node_properties';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'test_editable_views_node_properties';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Test editable views node properties';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Entity metadata property (editable) */
  $handler->display->display_options['fields']['metadata_property_editable']['id'] = 'metadata_property_editable';
  $handler->display->display_options['fields']['metadata_property_editable']['table'] = 'node';
  $handler->display->display_options['fields']['metadata_property_editable']['field'] = 'metadata_property_editable';
  $handler->display->display_options['fields']['metadata_property_editable']['label'] = 'Status';
  $handler->display->display_options['fields']['metadata_property_editable']['property'] = 'status';
  /* Field: Content: Entity metadata property (editable) */
  $handler->display->display_options['fields']['metadata_property_editable_1']['id'] = 'metadata_property_editable_1';
  $handler->display->display_options['fields']['metadata_property_editable_1']['table'] = 'node';
  $handler->display->display_options['fields']['metadata_property_editable_1']['field'] = 'metadata_property_editable';
  $handler->display->display_options['fields']['metadata_property_editable_1']['label'] = 'Promote';
  $handler->display->display_options['fields']['metadata_property_editable_1']['property'] = 'promote';
  /* Field: Content: Entity metadata property (editable) */
  $handler->display->display_options['fields']['metadata_property_editable_2']['id'] = 'metadata_property_editable_2';
  $handler->display->display_options['fields']['metadata_property_editable_2']['table'] = 'node';
  $handler->display->display_options['fields']['metadata_property_editable_2']['field'] = 'metadata_property_editable';
  $handler->display->display_options['fields']['metadata_property_editable_2']['label'] = 'Sticky';
  $handler->display->display_options['fields']['metadata_property_editable_2']['property'] = 'sticky';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'editable_views_test_node' => 'editable_views_test_node',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test-editable-views-node-properties';
  $export['test_editable_views_node_properties'] = $view;

  $view = new view();
  $view->name = 'test_editable_views_node_referenced_backwards_title';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Test editable views node referenced backwards title';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Test editable views node title';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title_editable' => 'title_editable',
    'title_editable_1' => 'title_editable_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_editable_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['relationship_creation_bundle'] = array(
    'reverse_field_test_node_reference_node' => 'editable_views_test_referencing',
  );
  /* Relationship: Entity Reference: Referencing entity */
  $handler->display->display_options['relationships']['reverse_field_test_node_reference_node']['id'] = 'reverse_field_test_node_reference_node';
  $handler->display->display_options['relationships']['reverse_field_test_node_reference_node']['table'] = 'node';
  $handler->display->display_options['relationships']['reverse_field_test_node_reference_node']['field'] = 'reverse_field_test_node_reference_node';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable']['id'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['textfield_size'] = '';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable_1']['id'] = 'title_editable_1';
  $handler->display->display_options['fields']['title_editable_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable_1']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable_1']['relationship'] = 'reverse_field_test_node_reference_node';
  $handler->display->display_options['fields']['title_editable_1']['textfield_size'] = '';
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
    'editable_views_test_node' => 'editable_views_test_node',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test_editable_views_node_referenced_backwards_title';
  $export['test_editable_views_node_referenced_backwards_title'] = $view;

  $view = new view();
  $view->name = 'test_editable_views_node_referenced_forwards_title';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Test editable views node referenced forwards title';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Test editable views node title';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title_editable' => 'title_editable',
    'title_editable_1' => 'title_editable_1',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title_editable' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title_editable_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['relationship_creation_bundle'] = array(
    'field_test_node_reference_target_id' => 'editable_views_test_node',
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_test_node_reference_target_id']['id'] = 'field_test_node_reference_target_id';
  $handler->display->display_options['relationships']['field_test_node_reference_target_id']['table'] = 'field_data_field_test_node_reference';
  $handler->display->display_options['relationships']['field_test_node_reference_target_id']['field'] = 'field_test_node_reference_target_id';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable']['id'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['textfield_size'] = '';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable_1']['id'] = 'title_editable_1';
  $handler->display->display_options['fields']['title_editable_1']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable_1']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable_1']['relationship'] = 'field_test_node_reference_target_id';
  $handler->display->display_options['fields']['title_editable_1']['textfield_size'] = '';
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
    'editable_views_test_referencing' => 'editable_views_test_referencing',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test_editable_views_node_referenced_forwards_title';
  $export['test_editable_views_node_referenced_forwards_title'] = $view;

  $view = new view();
  $view->name = 'test_editable_views_node_title';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Test editable views node title';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Test editable views node title';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'editableviews_table';
  /* Field: Content: Title (editable) */
  $handler->display->display_options['fields']['title_editable']['id'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['table'] = 'node';
  $handler->display->display_options['fields']['title_editable']['field'] = 'title_editable';
  $handler->display->display_options['fields']['title_editable']['textfield_size'] = '';
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
    'editable_views_test_node' => 'editable_views_test_node',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'test-editable-views-node-title';
  $export['test_editable_views_node_title'] = $view;

  return $export;
}
