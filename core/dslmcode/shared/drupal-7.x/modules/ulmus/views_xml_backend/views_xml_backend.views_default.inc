<?php
/**
 * @file
 * Default example view.
 */

/**
 * Implements hook_views_default_views().
 */
function views_xml_backend_views_default_views() {
  $views = array();
  // Export code begin.

  $view = new view;
  $view->name = 'views_project_releases';
  $view->description = 'Releases for a project by API compatability version';
  $view->tag = 'default';
  $view->base_table = 'xml';
  $view->human_name = 'Views project releases';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Views project releases';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['xml_file'] = 'http://updates.drupal.org/release-history/views/6.x';
  $handler->display->display_options['query']['options']['row_xpath'] = '/project/releases/release';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '5';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'text_1' => 'text_1',
    'text' => 'text',
    'text_2' => 'text_2',
    'text_4' => 'text_4',
    'text_3' => 'text_3',
    'date' => 'date',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'text_1' => array(
      'sortable' => 1,
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
    'text_2' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text_4' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'text_3' => array(
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
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* Field: download_link: Text */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['label'] = 'Download URL';
  $handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'download_link';
  /* Field: name: Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['text']['alter']['path'] = '[text_1] ';
  $handler->display->display_options['fields']['text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text']['alter']['external'] = 1;
  $handler->display->display_options['fields']['text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'name';
  /* Field: mdhash: Text */
  $handler->display->display_options['fields']['text_2']['id'] = 'text_2';
  $handler->display->display_options['fields']['text_2']['table'] = 'xml';
  $handler->display->display_options['fields']['text_2']['field'] = 'text';
  $handler->display->display_options['fields']['text_2']['label'] = 'MD5 Hash';
  $handler->display->display_options['fields']['text_2']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_2']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_2']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_2']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_2']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_2']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_2']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_2']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_2']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_2']['xpath_selector'] = 'mdhash';
  /* Field: version_major: Text */
  $handler->display->display_options['fields']['text_4']['id'] = 'text_4';
  $handler->display->display_options['fields']['text_4']['table'] = 'xml';
  $handler->display->display_options['fields']['text_4']['field'] = 'text';
  $handler->display->display_options['fields']['text_4']['label'] = 'Version major';
  $handler->display->display_options['fields']['text_4']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_4']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_4']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_4']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_4']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_4']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_4']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_4']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_4']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_4']['xpath_selector'] = 'version_major';
  $handler->display->display_options['fields']['text_4']['multiple'] = 0;
  /* Field: terms/term/value: Text */
  $handler->display->display_options['fields']['text_3']['id'] = 'text_3';
  $handler->display->display_options['fields']['text_3']['table'] = 'xml';
  $handler->display->display_options['fields']['text_3']['field'] = 'text';
  $handler->display->display_options['fields']['text_3']['label'] = 'Release type';
  $handler->display->display_options['fields']['text_3']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_3']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_3']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_3']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_3']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['text_3']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_3']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_3']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_3']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_3']['xpath_selector'] = 'terms/term/value';
  $handler->display->display_options['fields']['text_3']['multiple'] = 1;
  /* Field: date: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'xml';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['date']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['date']['xpath_selector'] = 'date';
  $handler->display->display_options['fields']['date']['multiple'] = 0;
  $handler->display->display_options['fields']['date']['date_format'] = 'time ago';
  /* Filter criterion: version_major: Numeric */
  $handler->display->display_options['filters']['numeric']['id'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['table'] = 'xml';
  $handler->display->display_options['filters']['numeric']['field'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['exposed'] = TRUE;
  $handler->display->display_options['filters']['numeric']['expose']['operator_id'] = 'numeric_op';
  $handler->display->display_options['filters']['numeric']['expose']['label'] = 'Major Version';
  $handler->display->display_options['filters']['numeric']['expose']['operator'] = 'numeric_op';
  $handler->display->display_options['filters']['numeric']['expose']['identifier'] = 'numeric';
  $handler->display->display_options['filters']['numeric']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['numeric']['xpath_selector'] = 'version_major';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'views-project-releases';

  // Export code end.
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'rss';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'xml';
  $view->human_name = 'Drupal Planet';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = TRUE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Drupal Planet';
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['xml_file'] = 'http://drupal.org/planet/rss.xml';
  $handler->display->display_options['query']['options']['row_xpath'] = '/rss/channel/item';
  $handler->display->display_options['query']['options']['show_errors'] = 1;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'list';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'text_1' => 'text_1',
    'text' => 'text',
  );
  $handler->display->display_options['row_options']['hide_empty'] = 0;
  $handler->display->display_options['row_options']['default_field_elements'] = 1;
  /* Field: link: Text */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['label'] = '';
  $handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text_1']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text_1']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'link';
  /* Field: title: Text */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['label'] = '';
  $handler->display->display_options['fields']['text']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['text']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['text']['alter']['path'] = '[text_1]';
  $handler->display->display_options['fields']['text']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['text']['alter']['external'] = 0;
  $handler->display->display_options['fields']['text']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['text']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['text']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['text']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['text']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['text']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['text']['alter']['html'] = 0;
  $handler->display->display_options['fields']['text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['text']['hide_empty'] = 0;
  $handler->display->display_options['fields']['text']['empty_zero'] = 0;
  $handler->display->display_options['fields']['text']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'title';
  /* Field: pubDate: Date */
  $handler->display->display_options['fields']['date']['id'] = 'date';
  $handler->display->display_options['fields']['date']['table'] = 'xml';
  $handler->display->display_options['fields']['date']['field'] = 'date';
  $handler->display->display_options['fields']['date']['label'] = '';
  $handler->display->display_options['fields']['date']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['date']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['date']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['date']['alter']['external'] = 0;
  $handler->display->display_options['fields']['date']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['date']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['date']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['date']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['date']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['date']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['date']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['date']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['date']['alter']['html'] = 0;
  $handler->display->display_options['fields']['date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['date']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['date']['hide_empty'] = 0;
  $handler->display->display_options['fields']['date']['empty_zero'] = 0;
  $handler->display->display_options['fields']['date']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['date']['xpath_selector'] = 'pubDate';
  $handler->display->display_options['fields']['date']['multiple'] = 0;
  $handler->display->display_options['fields']['date']['date_format'] = 'long';
  /* Field: description: Markup */
  $handler->display->display_options['fields']['markup']['id'] = 'markup';
  $handler->display->display_options['fields']['markup']['table'] = 'xml';
  $handler->display->display_options['fields']['markup']['field'] = 'markup';
  $handler->display->display_options['fields']['markup']['label'] = '';
  $handler->display->display_options['fields']['markup']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['external'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['markup']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['markup']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['markup']['alter']['html'] = 0;
  $handler->display->display_options['fields']['markup']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['markup']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['markup']['hide_empty'] = 0;
  $handler->display->display_options['fields']['markup']['empty_zero'] = 0;
  $handler->display->display_options['fields']['markup']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['markup']['xpath_selector'] = 'description';
  $handler->display->display_options['fields']['markup']['multiple'] = 0;
  $handler->display->display_options['fields']['markup']['format'] = 'filtered_html';
  /* Sort criterion: pubDate: Date */
  $handler->display->display_options['sorts']['date']['id'] = 'date';
  $handler->display->display_options['sorts']['date']['table'] = 'xml';
  $handler->display->display_options['sorts']['date']['field'] = 'date';
  $handler->display->display_options['sorts']['date']['order'] = 'DESC';
  $handler->display->display_options['sorts']['date']['xpath_selector'] = 'pubDate';
  /* Filter criterion: description: Text */
  $handler->display->display_options['filters']['text']['id'] = 'text';
  $handler->display->display_options['filters']['text']['table'] = 'xml';
  $handler->display->display_options['filters']['text']['field'] = 'text';
  $handler->display->display_options['filters']['text']['operator'] = 'contains';
  $handler->display->display_options['filters']['text']['exposed'] = TRUE;
  $handler->display->display_options['filters']['text']['expose']['operator_id'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['label'] = 'Search';
  $handler->display->display_options['filters']['text']['expose']['operator'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['expose']['required'] = 0;
  $handler->display->display_options['filters']['text']['expose']['multiple'] = FALSE;
  $handler->display->display_options['filters']['text']['xpath_selector'] = 'description';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'drupal-planet';

  $views[$view->name] = $view;

  return $views;
}
