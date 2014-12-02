<?php

/**
 * @file
 * Contains default views on behalf of the feedback module.
 */

/**
 * Implements hook_views_default_views().
 */
function feedback_views_default_views() {
  $view = new view();
  $view->name = 'feedback_messages';
  $view->description = 'Override the default feedback messages report.';
  $view->tag = 'feedback';
  $view->base_table = 'feedback';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Feedback Messages';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view feedback messages';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = 50;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'location' => 'location',
    'timestamp' => 'timestamp',
    'name' => 'name',
    'message' => 'message',
    'useragent' => 'message',
    'view_entry' => 'message',
    'view_entry_delete' => 'message',
    'view_entry_edit' => 'message',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
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
    'message' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'useragent' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_entry' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_entry_delete' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_entry_edit' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'text';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['content'] = 'Open Feedback Messages';
  $handler->display->display_options['header']['text']['format'] = 'full_html';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no open feedback entries.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  /* Relationship: Feedback: User Id */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'feedback';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Feedback: Location */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'feedback';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  /* Field: Feedback: Timestamp */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'feedback';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Feedback: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'feedback';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['element_type'] = 'div';
  /* Field: Feedback: User agent */
  $handler->display->display_options['fields']['useragent']['id'] = 'useragent';
  $handler->display->display_options['fields']['useragent']['table'] = 'feedback';
  $handler->display->display_options['fields']['useragent']['field'] = 'useragent';
  $handler->display->display_options['fields']['useragent']['label'] = '';
  $handler->display->display_options['fields']['useragent']['element_type'] = 'div';
  /* Field: Feedback: Link */
  $handler->display->display_options['fields']['view_entry']['id'] = 'view_entry';
  $handler->display->display_options['fields']['view_entry']['table'] = 'feedback';
  $handler->display->display_options['fields']['view_entry']['field'] = 'view_entry';
  $handler->display->display_options['fields']['view_entry']['label'] = '';
  $handler->display->display_options['fields']['view_entry']['element_label_colon'] = FALSE;
  /* Field: Feedback: Edit entry */
  $handler->display->display_options['fields']['view_entry_edit']['id'] = 'view_entry_edit';
  $handler->display->display_options['fields']['view_entry_edit']['table'] = 'feedback';
  $handler->display->display_options['fields']['view_entry_edit']['field'] = 'view_entry_edit';
  $handler->display->display_options['fields']['view_entry_edit']['label'] = '';
  $handler->display->display_options['fields']['view_entry_edit']['element_label_colon'] = FALSE;
  /* Field: Feedback: Delete entry */
  $handler->display->display_options['fields']['view_entry_delete']['id'] = 'view_entry_delete';
  $handler->display->display_options['fields']['view_entry_delete']['table'] = 'feedback';
  $handler->display->display_options['fields']['view_entry_delete']['field'] = 'view_entry_delete';
  $handler->display->display_options['fields']['view_entry_delete']['label'] = '';
  $handler->display->display_options['fields']['view_entry_delete']['element_label_colon'] = FALSE;
  /* Sort criterion: Feedback: Timestamp */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'feedback';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  /* Filter criterion: Feedback: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'feedback';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;

  /* Display: Open Entries */
  $handler = $view->new_display('page', 'Open Entries', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'text';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['empty'] = TRUE;
  $handler->display->display_options['header']['text']['content'] = '<h3>Open Feedback Messages</h3>';
  $handler->display->display_options['header']['text']['format'] = 'full_html';
  $handler->display->display_options['path'] = 'admin/reports/feedback';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Feedback messages';
  $handler->display->display_options['menu']['description'] = 'View feedback messages.';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';

  /* Display: Processed Entries */
  $handler = $view->new_display('attachment', 'Processed Entries', 'attachment_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'text';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['empty'] = TRUE;
  $handler->display->display_options['header']['text']['content'] = '<h3>Processed Feedback Messages</h3>';
  $handler->display->display_options['header']['text']['format'] = 'full_html';
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no processed feedback entries.';
  $handler->display->display_options['empty']['area']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Feedback: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'feedback';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'default' => 0,
  );
  $handler->display->display_options['attachment_position'] = 'after';
  $handler->display->display_options['render_pager'] = TRUE;
  $translatables['feedback_messages'] = array(
    t('Defaults'),
    t('Feedback Messages'),
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
    t('Open Feedback Messages'),
    t('There are no processed feedback entries.'),
    t('There are no open feedback entries.'),
    t('User'),
    t('Location'),
    t('Date'),
    t('Message'),
    t('Page'),
    t('Attachment'),
    t('Processed Feedback Messages'),
  );
  $views[$view->name] = $view;
  return $views;
}
