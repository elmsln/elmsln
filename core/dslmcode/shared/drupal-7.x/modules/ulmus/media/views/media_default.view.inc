<?php

/**
 * @file
 * The default view for the media browser library tab.
 */

$view = new view();
$view->name = 'media_default';
$view->description = 'Default view for the media browser library tab.';
$view->tag = 'media, default';
$view->base_table = 'file_managed';
$view->human_name = 'Media browser';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['use_ajax'] = TRUE;
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['group_by'] = TRUE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view files';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['query']['options']['query_tags'] = array(
  0 => 'media_browser',
);
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['exposed_form']['options']['reset_button'] = FALSE;
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '25';
$handler->display->display_options['pager']['options']['offset'] = '0';
$handler->display->display_options['pager']['options']['id'] = '0';
$handler->display->display_options['style_plugin'] = 'media_browser';
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['content'] = 'No files available.';
$handler->display->display_options['empty']['area']['format'] = filter_fallback_format();
/* Field: File: Name */
$handler->display->display_options['fields']['filename']['id'] = 'filename';
$handler->display->display_options['fields']['filename']['table'] = 'file_managed';
$handler->display->display_options['fields']['filename']['field'] = 'filename';
$handler->display->display_options['fields']['filename']['label'] = '';
$handler->display->display_options['fields']['filename']['alter']['word_boundary'] = FALSE;
$handler->display->display_options['fields']['filename']['alter']['ellipsis'] = FALSE;
$handler->display->display_options['fields']['filename']['link_to_file'] = TRUE;
/* Sort criterion: File: Upload date */
$handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
$handler->display->display_options['sorts']['timestamp']['table'] = 'file_managed';
$handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
$handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
$handler->display->display_options['sorts']['timestamp']['exposed'] = TRUE;
$handler->display->display_options['sorts']['timestamp']['expose']['label'] = 'Upload date';
/* Sort criterion: SUM(File Usage: Use count) */
$handler->display->display_options['sorts']['count']['id'] = 'count';
$handler->display->display_options['sorts']['count']['table'] = 'file_usage';
$handler->display->display_options['sorts']['count']['field'] = 'count';
$handler->display->display_options['sorts']['count']['group_type'] = 'sum';
$handler->display->display_options['sorts']['count']['exposed'] = TRUE;
$handler->display->display_options['sorts']['count']['expose']['label'] = 'Use count';
/* Filter criterion: File: Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'file_managed';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = array(
  1 => '1',
);
/* Filter criterion: File: Name */
$handler->display->display_options['filters']['filename']['id'] = 'filename';
$handler->display->display_options['filters']['filename']['table'] = 'file_managed';
$handler->display->display_options['filters']['filename']['field'] = 'filename';
$handler->display->display_options['filters']['filename']['operator'] = 'contains';
$handler->display->display_options['filters']['filename']['exposed'] = TRUE;
$handler->display->display_options['filters']['filename']['expose']['operator_id'] = 'filename_op';
$handler->display->display_options['filters']['filename']['expose']['label'] = 'File name';
$handler->display->display_options['filters']['filename']['expose']['operator'] = 'filename_op';
$handler->display->display_options['filters']['filename']['expose']['identifier'] = 'filename';
/* Filter criterion: File: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'file_managed';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';

/* Display: Media browser */
$handler = $view->new_display('media_browser', 'Media browser', 'media_browser_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Library';
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;

/* Display: My files */
$handler = $view->new_display('media_browser', 'My files', 'media_browser_my_files');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'My files';
$handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'view own files';
$handler->display->display_options['defaults']['relationships'] = FALSE;
/* Relationship: File: User who uploaded */
$handler->display->display_options['relationships']['uid']['id'] = 'uid';
$handler->display->display_options['relationships']['uid']['table'] = 'file_managed';
$handler->display->display_options['relationships']['uid']['field'] = 'uid';
$handler->display->display_options['relationships']['uid']['required'] = TRUE;
$handler->display->display_options['defaults']['arguments'] = FALSE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: File: Status */
$handler->display->display_options['filters']['status']['id'] = 'status';
$handler->display->display_options['filters']['status']['table'] = 'file_managed';
$handler->display->display_options['filters']['status']['field'] = 'status';
$handler->display->display_options['filters']['status']['value'] = array(
  1 => '1',
);
/* Filter criterion: File: Name */
$handler->display->display_options['filters']['filename']['id'] = 'filename';
$handler->display->display_options['filters']['filename']['table'] = 'file_managed';
$handler->display->display_options['filters']['filename']['field'] = 'filename';
$handler->display->display_options['filters']['filename']['operator'] = 'contains';
$handler->display->display_options['filters']['filename']['exposed'] = TRUE;
$handler->display->display_options['filters']['filename']['expose']['operator_id'] = 'filename_op';
$handler->display->display_options['filters']['filename']['expose']['label'] = 'File name';
$handler->display->display_options['filters']['filename']['expose']['operator'] = 'filename_op';
$handler->display->display_options['filters']['filename']['expose']['identifier'] = 'filename';
/* Filter criterion: File: Type */
$handler->display->display_options['filters']['type']['id'] = 'type';
$handler->display->display_options['filters']['type']['table'] = 'file_managed';
$handler->display->display_options['filters']['type']['field'] = 'type';
$handler->display->display_options['filters']['type']['exposed'] = TRUE;
$handler->display->display_options['filters']['type']['expose']['operator_id'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['label'] = 'Type';
$handler->display->display_options['filters']['type']['expose']['operator'] = 'type_op';
$handler->display->display_options['filters']['type']['expose']['identifier'] = 'type';
/* Filter criterion: User: Current */
$handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['table'] = 'users';
$handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
$handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
$handler->display->display_options['filters']['uid_current']['value'] = '1';
$translatables['media_default'] = array(
  t('Master'),
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
  t('No files available.'),
  t('Upload date'),
  t('Use count'),
  t('File name'),
  t('Type'),
  t('Media browser'),
  t('Library'),
  t('My files'),
  t('User who uploaded'),
);
