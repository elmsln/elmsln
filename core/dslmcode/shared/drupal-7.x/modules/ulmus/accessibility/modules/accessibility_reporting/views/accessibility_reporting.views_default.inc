<?php

/**
 * Implements hook_views_default_views().
 */

function accessibility_reporting_views_default_views() {
	$views = array();

	$view = new view();
	$view->name = 'accessibility_report';
	$view->description = '';
	$view->tag = 'default';
	$view->base_table = 'node';
	$view->human_name = 'Accessibility report';
	$view->core = 7;
	$view->api_version = '3.0';
	$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

	/* Display: Master */
	$handler = $view->new_display('default', 'Master', 'default');
	$handler->display->display_options['title'] = 'Accessibility report';
	$handler->display->display_options['use_more_always'] = FALSE;
	$handler->display->display_options['access']['type'] = 'perm';
	$handler->display->display_options['access']['perm'] = 'view acessibility reports';
	$handler->display->display_options['cache']['type'] = 'none';
	$handler->display->display_options['query']['type'] = 'views_query';
	$handler->display->display_options['exposed_form']['type'] = 'basic';
	$handler->display->display_options['pager']['type'] = 'full';
	$handler->display->display_options['pager']['options']['items_per_page'] = '10';
	$handler->display->display_options['style_plugin'] = 'table';
	$handler->display->display_options['style_options']['columns'] = array(
	  'title' => 'title',
	  'field' => 'field',
	  'name' => 'name',
	  'severity' => 'severity',
	  'total' => 'total',
	);
	$handler->display->display_options['style_options']['default'] = 'total';
	$handler->display->display_options['style_options']['info'] = array(
	  'title' => array(
	    'sortable' => 0,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'field' => array(
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'name' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'severity' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'asc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	  'total' => array(
	    'sortable' => 1,
	    'default_sort_order' => 'desc',
	    'align' => '',
	    'separator' => '',
	    'empty_column' => 0,
	  ),
	);
	/* Relationship: Content: Accessibility report results */
	$handler->display->display_options['relationships']['accessibility_reporting_base_left_node']['id'] = 'accessibility_reporting_base_left_node';
	$handler->display->display_options['relationships']['accessibility_reporting_base_left_node']['table'] = 'node';
	$handler->display->display_options['relationships']['accessibility_reporting_base_left_node']['field'] = 'accessibility_reporting_base_left_node';
	/* Relationship: Accessibility reporting: Accessibility test */
	$handler->display->display_options['relationships']['accessibility_test']['id'] = 'accessibility_test';
	$handler->display->display_options['relationships']['accessibility_test']['table'] = 'accessibility_reporting';
	$handler->display->display_options['relationships']['accessibility_test']['field'] = 'accessibility_test';
	$handler->display->display_options['relationships']['accessibility_test']['relationship'] = 'accessibility_reporting_base_left_node';
	/* Field: Content: Title */
	$handler->display->display_options['fields']['title']['id'] = 'title';
	$handler->display->display_options['fields']['title']['table'] = 'node';
	$handler->display->display_options['fields']['title']['field'] = 'title';
	$handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
	$handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
	/* Field: Accessibility reporting: Responsible field */
	$handler->display->display_options['fields']['field']['id'] = 'field';
	$handler->display->display_options['fields']['field']['table'] = 'accessibility_reporting';
	$handler->display->display_options['fields']['field']['field'] = 'field';
	$handler->display->display_options['fields']['field']['relationship'] = 'accessibility_reporting_base_left_node';
	/* Field: Accessibility test: Name */
	$handler->display->display_options['fields']['name']['id'] = 'name';
	$handler->display->display_options['fields']['name']['table'] = 'accessibility_test';
	$handler->display->display_options['fields']['name']['field'] = 'name';
	$handler->display->display_options['fields']['name']['relationship'] = 'accessibility_test';
	$handler->display->display_options['fields']['name']['label'] = 'Accessibility test';
	/* Field: Accessibility test: Severity */
	$handler->display->display_options['fields']['severity']['id'] = 'severity';
	$handler->display->display_options['fields']['severity']['table'] = 'accessibility_test';
	$handler->display->display_options['fields']['severity']['field'] = 'severity';
	$handler->display->display_options['fields']['severity']['relationship'] = 'accessibility_test';
	/* Field: Accessibility reporting: Total errors */
	$handler->display->display_options['fields']['total']['id'] = 'total';
	$handler->display->display_options['fields']['total']['table'] = 'accessibility_reporting';
	$handler->display->display_options['fields']['total']['field'] = 'total';
	$handler->display->display_options['fields']['total']['relationship'] = 'accessibility_reporting_base_left_node';
	/* Sort criterion: Content: Post date */
	$handler->display->display_options['sorts']['created']['id'] = 'created';
	$handler->display->display_options['sorts']['created']['table'] = 'node';
	$handler->display->display_options['sorts']['created']['field'] = 'created';
	$handler->display->display_options['sorts']['created']['order'] = 'DESC';
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

	/* Display: Page */
	$handler = $view->new_display('page', 'Page', 'page');
	$handler->display->display_options['path'] = 'accessibility/report';
	$translatables['accessibility_report'] = array(
	  t('Master'),
	  t('Accessibility report'),
	  t('more'),
	  t('Apply'),
	  t('Reset'),
	  t('Sort by'),
	  t('Asc'),
	  t('Desc'),
	  t('Items per page'),
	  t('- All -'),
	  t('Offset'),
	  t('« first'),
	  t('‹ previous'),
	  t('next ›'),
	  t('last »'),
	  t('Reporting'),
	  t('Accessibility test'),
	  t('Title'),
	  t('Responsible field'),
	  t('Severity'),
	  t('Total errors'),
	  t('.'),
	  t(','),
	  t('Page'),
	);
	$views[] = $view;

	return $views;
}