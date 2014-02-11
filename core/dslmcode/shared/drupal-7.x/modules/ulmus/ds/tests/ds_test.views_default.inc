<?php

/**
 * @file
 * Default views used for testing.
 */

/**
 * Implements hook_views_default_views().
 */
function ds_test_views_default_views() {
  $views = array();

  $view = new view;
  $view->name = 'ds_testing';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ds-testing';
  $view->core = 7;
  $view->api_version = '3.0-alpha1';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'ds-testing';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'ds';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['title']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['title']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = 0;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = 0;
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['title']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['title']['alter']['html'] = 0;
  $handler->display->display_options['fields']['title']['hide_empty'] = 0;
  $handler->display->display_options['fields']['title']['empty_zero'] = 0;
  $handler->display->display_options['fields']['title']['link_to_node'] = 1;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Sort criterion: Content: Tags (field_tags) */
  $handler->display->display_options['sorts']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['sorts']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['sorts']['field_tags_tid']['field'] = 'field_tags_tid';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 0,
    'group_field' => 'node_created',
    'group_field_function' => '',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 0,
    'allpages' => 0,
    'item_0' => 'teaser',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 0,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'ds-testing';

  /* Display: Page 1 */
  $handler = $view->new_display('page', 'Page 1', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 1;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 0,
    'group_field' => 'node_created',
    'group_field_function' => '',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 1,
    'allpages' => 0,
    'item_0' => 'full',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 0,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'ds-testing-2';

  /* Display: Page 2 */
  $handler = $view->new_display('page', 'Page 2', 'page_2');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 1;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 1,
    'group_field' => 'field_data_field_tags_field_tags_tid',
    'group_field_function' => '',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 0,
    'allpages' => 0,
    'item_0' => 'teaser',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 0,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Tags (field_tags) */
  $handler->display->display_options['sorts']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['sorts']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['sorts']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['path'] = 'ds-testing-3';

  /* Display: Page 3 */
  $handler = $view->new_display('page', 'Page 3', 'page_3');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 1;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 1,
    'group_field' => 'field_data_field_tags_field_tags_tid',
    'group_field_function' => 'ds_test_get_tag_name',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 0,
    'allpages' => 0,
    'item_0' => 'teaser',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 0,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Tags (field_tags) */
  $handler->display->display_options['sorts']['field_tags_tid']['id'] = 'field_tags_tid';
  $handler->display->display_options['sorts']['field_tags_tid']['table'] = 'field_data_field_tags';
  $handler->display->display_options['sorts']['field_tags_tid']['field'] = 'field_tags_tid';
  $handler->display->display_options['path'] = 'ds-testing-4';

  /* Display: Page 4 */
  $handler = $view->new_display('page', 'Page 4', 'page_4');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 1;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 0,
    'group_field' => 'field_data_field_tags_field_tags_tid',
    'group_field_function' => '',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 0,
    'allpages' => 0,
    'item_0' => 'teaser',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 1,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'ds-testing-5';

  /* Display: Page 5 */
  $handler = $view->new_display('page', 'Page 5', 'page_5');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'ds';
  $handler->display->display_options['row_options']['alternating'] = 0;
  $handler->display->display_options['row_options']['grouping'] = 0;
  $handler->display->display_options['row_options']['advanced'] = 0;
  $handler->display->display_options['row_options']['grouping_fieldset'] = array(
    'grouping' => 0,
    'group_field' => 'field_data_field_tags_field_tags_tid',
    'group_field_function' => '',
  );
  $handler->display->display_options['row_options']['default_fieldset'] = array(
    'view_mode' => 'teaser',
    'load_comments' => 0,
  );
  $handler->display->display_options['row_options']['alternating_fieldset'] = array(
    'alternating' => 0,
    'allpages' => 0,
    'item_0' => 'teaser',
    'item_1' => 'teaser',
    'item_2' => 'teaser',
    'item_3' => 'teaser',
    'item_4' => 'teaser',
    'item_5' => 'teaser',
    'item_6' => 'teaser',
    'item_7' => 'teaser',
    'item_8' => 'teaser',
    'item_9' => 'teaser',
  );
  $handler->display->display_options['row_options']['advanced_fieldset'] = array(
    'advanced' => 0,
  );
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = 'Header text';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['footer'] = FALSE;
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['empty'] = FALSE;
  $handler->display->display_options['footer']['area']['content'] = 'Footer text';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $handler->display->display_options['footer']['area']['tokenize'] = 0;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 0;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'article' => 'article',
    'page' => 'page',
  );
  $handler->display->display_options['filters']['type']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
  $handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
  $handler->display->display_options['filters']['type']['expose']['reduce'] = 0;
  $handler->display->display_options['path'] = 'ds-testing-6';
  $views['ds_testing'] = $view;

  return $views;
}
