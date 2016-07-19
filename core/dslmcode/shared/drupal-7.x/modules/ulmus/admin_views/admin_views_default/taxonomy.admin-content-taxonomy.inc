<?php

/**
 * @file
 * Default view for taxonomy term administration.
 */

$view = new view();
$view->name = 'admin_views_taxonomy_term';
$view->description = 'Manage tagging, categorization, and classification of your content.';
$view->tag = 'admin';
$view->base_table = 'taxonomy_term_data';
$view->human_name = 'Administration: Taxonomy terms';
$view->core = 0;
$view->api_version = '3.0';
$view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

/* Display: Defaults */
$handler = $view->new_display('default', 'Defaults', 'default');
$handler->display->display_options['title'] = 'Terms';
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'menu';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
$handler->display->display_options['pager']['type'] = 'none';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'name_1' => 'name_1',
  'name' => 'name',
  'tid' => 'tid',
);
$handler->display->display_options['style_options']['default'] = 'name';
$handler->display->display_options['style_options']['info'] = array(
  'name_1' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
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
  'tid' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
    'empty_column' => 0,
  ),
);
$handler->display->display_options['style_options']['sticky'] = TRUE;
/* Field: Taxonomy vocabulary: Name */
$handler->display->display_options['fields']['name_1']['id'] = 'name_1';
$handler->display->display_options['fields']['name_1']['table'] = 'taxonomy_vocabulary';
$handler->display->display_options['fields']['name_1']['field'] = 'name';
$handler->display->display_options['fields']['name_1']['label'] = '';
$handler->display->display_options['fields']['name_1']['exclude'] = TRUE;
/* Field: Taxonomy term: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = 'Term';
$handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
/* Field: Taxonomy term: Term ID */
$handler->display->display_options['fields']['tid']['id'] = 'tid';
$handler->display->display_options['fields']['tid']['table'] = 'taxonomy_term_data';
$handler->display->display_options['fields']['tid']['field'] = 'tid';
$handler->display->display_options['fields']['tid']['label'] = 'Operations';
$handler->display->display_options['fields']['tid']['alter']['alter_text'] = TRUE;
$handler->display->display_options['fields']['tid']['alter']['text'] = 'edit';
$handler->display->display_options['fields']['tid']['alter']['make_link'] = TRUE;
$handler->display->display_options['fields']['tid']['alter']['path'] = 'taxonomy/term/[tid]/edit';
$handler->display->display_options['fields']['tid']['separator'] = '';
/* Sort criterion: Taxonomy term: Weight */
$handler->display->display_options['sorts']['weight']['id'] = 'weight';
$handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
$handler->display->display_options['sorts']['weight']['field'] = 'weight';
/* Sort criterion: Taxonomy term: Name */
$handler->display->display_options['sorts']['name']['id'] = 'name';
$handler->display->display_options['sorts']['name']['table'] = 'taxonomy_term_data';
$handler->display->display_options['sorts']['name']['field'] = 'name';
/* Contextual filter: Taxonomy vocabulary: Machine name */
$handler->display->display_options['arguments']['machine_name']['id'] = 'machine_name';
$handler->display->display_options['arguments']['machine_name']['table'] = 'taxonomy_vocabulary';
$handler->display->display_options['arguments']['machine_name']['field'] = 'machine_name';
$handler->display->display_options['arguments']['machine_name']['title_enable'] = TRUE;
$handler->display->display_options['arguments']['machine_name']['title'] = 'Terms in %1';
$handler->display->display_options['arguments']['machine_name']['breadcrumb_enable'] = TRUE;
$handler->display->display_options['arguments']['machine_name']['breadcrumb'] = '%1';
$handler->display->display_options['arguments']['machine_name']['default_argument_type'] = 'fixed';
$handler->display->display_options['arguments']['machine_name']['summary']['number_of_records'] = '0';
$handler->display->display_options['arguments']['machine_name']['summary']['format'] = 'default_summary';
$handler->display->display_options['arguments']['machine_name']['summary_options']['items_per_page'] = '25';
$handler->display->display_options['arguments']['machine_name']['specify_validation'] = TRUE;
$handler->display->display_options['arguments']['machine_name']['validate']['fail'] = 'ignore';
$handler->display->display_options['arguments']['machine_name']['limit'] = '0';
/* Filter criterion: Taxonomy term: Vocabulary */
$handler->display->display_options['filters']['vid']['id'] = 'vid';
$handler->display->display_options['filters']['vid']['table'] = 'taxonomy_term_data';
$handler->display->display_options['filters']['vid']['field'] = 'vid';
$handler->display->display_options['filters']['vid']['group'] = '0';
$handler->display->display_options['filters']['vid']['exposed'] = TRUE;
$handler->display->display_options['filters']['vid']['expose']['operator_id'] = 'vid_op';
$handler->display->display_options['filters']['vid']['expose']['label'] = 'Vocabulary';
$handler->display->display_options['filters']['vid']['expose']['operator'] = 'vid_op';
$handler->display->display_options['filters']['vid']['expose']['identifier'] = 'vid';
$handler->display->display_options['filters']['vid']['expose']['remember'] = TRUE;
/* Filter criterion: Taxonomy term: Name */
$handler->display->display_options['filters']['name']['id'] = 'name';
$handler->display->display_options['filters']['name']['table'] = 'taxonomy_term_data';
$handler->display->display_options['filters']['name']['field'] = 'name';
$handler->display->display_options['filters']['name']['operator'] = 'word';
$handler->display->display_options['filters']['name']['exposed'] = TRUE;
$handler->display->display_options['filters']['name']['expose']['operator_id'] = 'name_op';
$handler->display->display_options['filters']['name']['expose']['label'] = 'Name';
$handler->display->display_options['filters']['name']['expose']['operator'] = 'name_op';
$handler->display->display_options['filters']['name']['expose']['identifier'] = 'name';
$handler->display->display_options['filters']['name']['expose']['remember'] = TRUE;

/* Display: System */
$handler = $view->new_display('system', 'System', 'system_1');
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['path'] = 'admin/structure/taxonomy/%';
$translatables['admin_views_taxonomy_term'] = array(
  t('Defaults'),
  t('Terms'),
  t('more'),
  t('Apply'),
  t('Reset'),
  t('Sort by'),
  t('Asc'),
  t('Desc'),
  t('Term'),
  t('Operations'),
  t('edit'),
  t('.'),
  t('All'),
  t('Terms in %1'),
  t('%1'),
  t('Vocabulary'),
  t('Name'),
  t('System'),
);
