<?php
/**
 * @file
 * discuss_displays.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function discuss_displays_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'discuss_my_posts';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Discuss My Posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Posts';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view harmony_posts';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '1800';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '1800';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'harmony_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'post_id' => 'post_id',
    'thread_id' => 'thread_id',
    'title' => 'title',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'post_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'thread_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_harmony_thread_target_id']['id'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['relationships']['field_harmony_thread_target_id']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['relationships']['field_harmony_thread_target_id']['field'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['relationships']['field_harmony_thread_target_id']['label'] = 'Thread';
  $handler->display->display_options['relationships']['field_harmony_thread_target_id']['required'] = TRUE;
  /* Field: Post: Post ID */
  $handler->display->display_options['fields']['post_id']['id'] = 'post_id';
  $handler->display->display_options['fields']['post_id']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['post_id']['field'] = 'post_id';
  $handler->display->display_options['fields']['post_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['post_id']['separator'] = '';
  /* Field: Thread: Thread ID */
  $handler->display->display_options['fields']['thread_id']['id'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['thread_id']['field'] = 'thread_id';
  $handler->display->display_options['fields']['thread_id']['relationship'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['fields']['thread_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['thread_id']['separator'] = '';
  /* Field: Post: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['path'] = 'thread/[thread_id]#post-[post_id]';
  /* Field: Post: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Posted';
  $handler->display->display_options['fields']['created']['date_format'] = 'time ago';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'html5_tools_iso8601';
  /* Contextual filter: Post: Author */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'harmony_post';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Post: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'discuss/my/posts';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Posts';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $export['discuss_my_posts'] = $view;

  return $export;
}
