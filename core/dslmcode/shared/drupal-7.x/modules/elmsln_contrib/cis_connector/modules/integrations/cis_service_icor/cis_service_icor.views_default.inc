<?php
/**
 * @file
 * cis_service_icor.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cis_service_icor_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cis_icor_objects';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'xml';
  $view->human_name = 'CIS ICOR objects';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS ICOR objects';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['xml_file'] = 'node.xml';
  $handler->display->display_options['query']['options']['row_xpath'] = '/list/node';
  $handler->display->display_options['query']['options']['show_errors'] = 1;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'text_1' => 'text_1',
    'text' => 'text',
    'date' => 'date',
    'text_2' => 'text_2',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'text_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text' => array(
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
    'text_2' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: nid: Text */
  $handler->display->display_options['fields']['text_4']['id'] = 'text_4';
  $handler->display->display_options['fields']['text_4']['table'] = 'xml';
  $handler->display->display_options['fields']['text_4']['field'] = 'text';
  $handler->display->display_options['fields']['text_4']['label'] = '';
  $handler->display->display_options['fields']['text_4']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_4']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_4']['xpath_selector'] = 'nid';
  $handler->display->display_options['fields']['text_4']['multiple'] = 0;
  /* Field: url: Text */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['label'] = '';
  $handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'url';
  $handler->display->display_options['fields']['text_1']['multiple'] = 0;
  /* Field: title: Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['text']['alter']['path'] = '[text_1]';
  $handler->display->display_options['fields']['text']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'title';
  $handler->display->display_options['fields']['text']['multiple'] = 0;
  /* Field: type: Text */
  $handler->display->display_options['fields']['text_3']['id'] = 'text_3';
  $handler->display->display_options['fields']['text_3']['table'] = 'xml';
  $handler->display->display_options['fields']['text_3']['field'] = 'text';
  $handler->display->display_options['fields']['text_3']['label'] = 'Type';
  $handler->display->display_options['fields']['text_3']['xpath_selector'] = 'type';
  $handler->display->display_options['fields']['text_3']['multiple'] = 0;
  /* Field: edit_url: Text */
  $handler->display->display_options['fields']['text_2']['id'] = 'text_2';
  $handler->display->display_options['fields']['text_2']['table'] = 'xml';
  $handler->display->display_options['fields']['text_2']['field'] = 'text';
  $handler->display->display_options['fields']['text_2']['label'] = '';
  $handler->display->display_options['fields']['text_2']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['text_2']['alter']['text'] = 'edit';
  $handler->display->display_options['fields']['text_2']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['text_2']['alter']['path'] = '[text_2]';
  $handler->display->display_options['fields']['text_2']['alter']['external'] = TRUE;
  $handler->display->display_options['fields']['text_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_2']['xpath_selector'] = 'edit_url';
  $handler->display->display_options['fields']['text_2']['multiple'] = 0;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a href="#" id="icor-insert-[text_4]" class="icor-asset-insert">Insert</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
    2 => 'AND',
  );
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text_1']['id'] = 'text_1';
  $handler->display->display_options['filters']['text_1']['table'] = 'xml';
  $handler->display->display_options['filters']['text_1']['field'] = 'text';
  $handler->display->display_options['filters']['text_1']['value'] = 'quiz';
  $handler->display->display_options['filters']['text_1']['group'] = 1;
  $handler->display->display_options['filters']['text_1']['xpath_selector'] = 'type';
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text_2']['id'] = 'text_2';
  $handler->display->display_options['filters']['text_2']['table'] = 'xml';
  $handler->display->display_options['filters']['text_2']['field'] = 'text';
  $handler->display->display_options['filters']['text_2']['value'] = 'poll';
  $handler->display->display_options['filters']['text_2']['group'] = 1;
  $handler->display->display_options['filters']['text_2']['xpath_selector'] = 'type';
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text_4']['id'] = 'text_4';
  $handler->display->display_options['filters']['text_4']['table'] = 'xml';
  $handler->display->display_options['filters']['text_4']['field'] = 'text';
  $handler->display->display_options['filters']['text_4']['value'] = 'timeline';
  $handler->display->display_options['filters']['text_4']['group'] = 1;
  $handler->display->display_options['filters']['text_4']['xpath_selector'] = 'type';
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text_3']['id'] = 'text_3';
  $handler->display->display_options['filters']['text_3']['table'] = 'xml';
  $handler->display->display_options['filters']['text_3']['field'] = 'text';
  $handler->display->display_options['filters']['text_3']['value'] = 'icor_interactive_player';
  $handler->display->display_options['filters']['text_3']['group'] = 1;
  $handler->display->display_options['filters']['text_3']['xpath_selector'] = 'type';
  /* Filter criterion: type: Text */
  $handler->display->display_options['filters']['text']['id'] = 'text';
  $handler->display->display_options['filters']['text']['table'] = 'xml';
  $handler->display->display_options['filters']['text']['field'] = 'text';
  $handler->display->display_options['filters']['text']['group'] = 2;
  $handler->display->display_options['filters']['text']['exposed'] = TRUE;
  $handler->display->display_options['filters']['text']['expose']['operator_id'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['label'] = 'Text';
  $handler->display->display_options['filters']['text']['expose']['operator'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['text']['group_info']['label'] = 'Type';
  $handler->display->display_options['filters']['text']['group_info']['description'] = 'Type of object you want to use';
  $handler->display->display_options['filters']['text']['group_info']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Quiz',
      'operator' => '=',
      'value' => 'quiz',
    ),
    2 => array(
      'title' => 'Poll',
      'operator' => '=',
      'value' => 'poll',
    ),
    3 => array(
      'title' => 'Interactive player',
      'operator' => '=',
      'value' => 'icor_interactive_player',
    ),
    4 => array(
      'title' => 'Timeline',
      'operator' => '=',
      'value' => 'timeline',
    ),
  );
  $handler->display->display_options['filters']['text']['xpath_selector'] = 'type';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['cis_bucket'] = 'icor';
  $handler->display->display_options['cis_instance'] = 1;
  $handler->display->display_options['path'] = 'ciscon/interactive-objects';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Interactive Objects';
  $handler->display->display_options['menu']['description'] = 'Objects list from interactive';
  $handler->display->display_options['menu']['weight'] = '100';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-settings';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_icor_objects'] = $view;

  return $export;
}
