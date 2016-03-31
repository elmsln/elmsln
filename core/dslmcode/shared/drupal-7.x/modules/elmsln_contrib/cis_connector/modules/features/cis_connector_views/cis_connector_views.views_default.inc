<?php
/**
 * @file
 * cis_connector_views.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cis_connector_views_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cis_connector_node';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'xml';
  $view->human_name = 'CIS connector node';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Online site nodes';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['row_xpath'] = '/list/node';
  $handler->display->display_options['query']['options']['show_errors'] = 1;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'text' => 'text',
    'text_1' => 'text_1',
    'date' => 'date',
    'markup' => 'markup',
    'text_2' => 'text_2',
  );
  $handler->display->display_options['style_options']['default'] = 'text_1';
  $handler->display->display_options['style_options']['info'] = array(
    'text' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text_1' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'markup' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: nid: Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['label'] = 'Nid';
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'nid';
  $handler->display->display_options['fields']['text']['multiple'] = 0;
  /* Field: title: Text */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['label'] = 'Title';
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'title';
  $handler->display->display_options['fields']['text_1']['multiple'] = 0;
  /* Field: changed: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'xml';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['label'] = 'Updated';
  $handler->display->display_options['fields']['date']['xpath_selector'] = 'changed';
  $handler->display->display_options['fields']['date']['multiple'] = 0;
  $handler->display->display_options['fields']['date']['date_format'] = 'long';
  /* Field: body/value: Markup */
  $handler->display->display_options['fields']['markup']['id'] = 'markup';
  $handler->display->display_options['fields']['markup']['table'] = 'xml';
  $handler->display->display_options['fields']['markup']['field'] = 'markup';
  $handler->display->display_options['fields']['markup']['label'] = 'Content';
  $handler->display->display_options['fields']['markup']['xpath_selector'] = 'body/value';
  $handler->display->display_options['fields']['markup']['multiple'] = 0;
  $handler->display->display_options['fields']['markup']['format'] = 'textbook_editor';
  /* Field: edit_url: Text */
  $handler->display->display_options['fields']['text_2']['id'] = 'text_2';
  $handler->display->display_options['fields']['text_2']['table'] = 'xml';
  $handler->display->display_options['fields']['text_2']['field'] = 'text';
  $handler->display->display_options['fields']['text_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['text_2']['alter']['text'] = 'edit';
  $handler->display->display_options['fields']['text_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['text_2']['alter']['path'] = '[text_2]';
  $handler->display->display_options['fields']['text_2']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['text_2']['xpath_selector'] = 'edit_url';
  $handler->display->display_options['fields']['text_2']['multiple'] = 0;
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text']['id'] = 'text';
  $handler->display->display_options['filters']['text']['table'] = 'xml';
  $handler->display->display_options['filters']['text']['field'] = 'text';
  $handler->display->display_options['filters']['text']['exposed'] = TRUE;
  $handler->display->display_options['filters']['text']['expose']['operator_id'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['label'] = 'Text';
  $handler->display->display_options['filters']['text']['expose']['operator'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['text']['group_info']['label'] = 'Text';
  $handler->display->display_options['filters']['text']['group_info']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Academic units',
      'operator' => '=',
      'value' => 'academic_unit',
    ),
    2 => array(
      'title' => 'Courses',
      'operator' => '=',
      'value' => 'course',
    ),
    3 => array(
      'title' => 'Material',
      'operator' => '=',
      'value' => 'isbn2node_book',
    ),
    4 => array(
      'title' => 'Program',
      'operator' => '=',
      'value' => 'program',
    ),
    5 => array(
      'title' => 'Service',
      'operator' => '=',
      'value' => 'service',
    ),
  );
  $handler->display->display_options['filters']['text']['xpath_selector'] = 'type';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'online-connector';
  $export['cis_connector_node'] = $view;

  return $export;
}
