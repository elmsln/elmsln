<?php
/**
 * @file
 * harmony_core.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function harmony_core_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'harmony_administration_posts';
  $view->description = '';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Administration: Posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Posts';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer harmony forum content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'field_harmony_thread' => 'field_harmony_thread',
    'name' => 'name',
    'status' => 'status',
    'created' => 'created',
    'updated' => 'updated',
    'edit_link' => 'delete_link',
    'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'updated';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_harmony_thread' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => 'views-align-center',
      'separator' => ' ',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No posts have been created.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Post: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Bulk operations: Post */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete post',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_locked_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Re-assign post(s) to a different thread',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'harmony_post::field_harmony_thread' => 'harmony_post::field_harmony_thread',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::harmony_core_post_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_reassign_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_split_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_unlock_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Post: Thread */
  $handler->display->display_options['fields']['field_harmony_thread']['id'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['field'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['settings'] = array(
    'link' => 1,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Post: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Post: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Post: Date updated */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Updated';
  $handler->display->display_options['fields']['updated']['date_format'] = 'short';
  /* Field: Post: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = '';
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_link']['text'] = 'edit';
  /* Field: Post: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = 'Operations';
  $handler->display->display_options['fields']['delete_link']['text'] = 'delete';
  /* Filter criterion: Post: Text (field_harmony_text) */
  $handler->display->display_options['filters']['field_harmony_text_value']['id'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['table'] = 'field_data_field_harmony_text';
  $handler->display->display_options['filters']['field_harmony_text_value']['field'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_harmony_text_value']['group'] = 1;
  $handler->display->display_options['filters']['field_harmony_text_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['operator_id'] = 'field_harmony_text_value_op';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['label'] = 'Text contains';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['operator'] = 'field_harmony_text_value_op';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['identifier'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Post: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Date: Date (harmony_post) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>';
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Posted after';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'harmony_post.created' => 'harmony_post.created',
  );
  $handler->display->display_options['filters']['date_filter']['date_method'] = 'AND';
  /* Filter criterion: Date: Date (harmony_post) */
  $handler->display->display_options['filters']['date_filter_1']['id'] = 'date_filter_1';
  $handler->display->display_options['filters']['date_filter_1']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['date_filter_1']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter_1']['operator'] = '<';
  $handler->display->display_options['filters']['date_filter_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter_1']['expose']['operator_id'] = 'date_filter_1_op';
  $handler->display->display_options['filters']['date_filter_1']['expose']['label'] = 'Posted before';
  $handler->display->display_options['filters']['date_filter_1']['expose']['operator'] = 'date_filter_1_op';
  $handler->display->display_options['filters']['date_filter_1']['expose']['identifier'] = 'date_filter_1';
  $handler->display->display_options['filters']['date_filter_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['date_filter_1']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter_1']['date_fields'] = array(
    'harmony_post.created' => 'harmony_post.created',
  );
  $handler->display->display_options['filters']['date_filter_1']['date_method'] = 'AND';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/harmony/content/posts';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Posts';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['harmony_administration_posts'] = $view;

  $view = new view();
  $view->name = 'harmony_administration_threads';
  $view->description = 'List and manage threads.';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_thread';
  $view->human_name = 'Administration: Threads';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Threads';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer harmony forum content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'title' => 'title',
    'field_harmony_category' => 'field_harmony_category',
    'field_harmony_post_count' => 'field_harmony_post_count',
    'status' => 'status',
    'created' => 'created',
    'updated' => 'updated',
    'locked' => 'locked',
    'pinned' => 'pinned',
    'edit_link' => 'delete_link',
    'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'updated';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_harmony_category' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_harmony_post_count' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'locked' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'pinned' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_link' => array(
      'align' => 'views-align-center',
      'separator' => ' ',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No threads have been posted.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Thread: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'harmony_thread';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Bulk operations: Thread */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete thread',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_hide_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_locked_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_merge_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 1,
      'label' => 'Mass change a field/property',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
        ),
      ),
    ),
    'action::harmony_core_thread_move_category_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::harmony_core_thread_make_pinned_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_save_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_unhide_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_unlock_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_make_unpinned_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_thread_update_alias_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Thread: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_thread'] = TRUE;
  /* Field: Thread: Category */
  $handler->display->display_options['fields']['field_harmony_category']['id'] = 'field_harmony_category';
  $handler->display->display_options['fields']['field_harmony_category']['table'] = 'field_data_field_harmony_category';
  $handler->display->display_options['fields']['field_harmony_category']['field'] = 'field_harmony_category';
  /* Field: Field: Post count */
  $handler->display->display_options['fields']['field_harmony_post_count']['id'] = 'field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['table'] = 'field_data_field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['field'] = 'field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['label'] = 'Posts';
  $handler->display->display_options['fields']['field_harmony_post_count']['settings'] = array(
    'thousand_separator' => ' ',
    'prefix_suffix' => 1,
  );
  /* Field: Thread: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Thread: Date updated */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Updated';
  $handler->display->display_options['fields']['updated']['date_format'] = 'short';
  /* Field: Thread: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Thread: Locked */
  $handler->display->display_options['fields']['locked']['id'] = 'locked';
  $handler->display->display_options['fields']['locked']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['locked']['field'] = 'locked';
  $handler->display->display_options['fields']['locked']['not'] = 0;
  /* Field: Thread: Pinned */
  $handler->display->display_options['fields']['pinned']['id'] = 'pinned';
  $handler->display->display_options['fields']['pinned']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['pinned']['field'] = 'pinned';
  $handler->display->display_options['fields']['pinned']['not'] = 0;
  /* Field: Thread: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = '';
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_link']['text'] = 'edit';
  /* Field: Thread: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = 'Operations';
  $handler->display->display_options['fields']['delete_link']['text'] = 'delete';
  /* Filter criterion: Thread: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Title';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Thread: Category (field_harmony_category) */
  $handler->display->display_options['filters']['field_harmony_category_tid']['id'] = 'field_harmony_category_tid';
  $handler->display->display_options['filters']['field_harmony_category_tid']['table'] = 'field_data_field_harmony_category';
  $handler->display->display_options['filters']['field_harmony_category_tid']['field'] = 'field_harmony_category_tid';
  $handler->display->display_options['filters']['field_harmony_category_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_harmony_category_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['operator_id'] = 'field_harmony_category_tid_op';
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['operator'] = 'field_harmony_category_tid_op';
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['identifier'] = 'field_harmony_category_tid';
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['field_harmony_category_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  $handler->display->display_options['filters']['field_harmony_category_tid']['type'] = 'select';
  $handler->display->display_options['filters']['field_harmony_category_tid']['vocabulary'] = 'harmony_category';
  $handler->display->display_options['filters']['field_harmony_category_tid']['hierarchy'] = 1;
  /* Filter criterion: Thread: Locked */
  $handler->display->display_options['filters']['locked']['id'] = 'locked';
  $handler->display->display_options['filters']['locked']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['locked']['field'] = 'locked';
  $handler->display->display_options['filters']['locked']['value'] = 'All';
  $handler->display->display_options['filters']['locked']['group'] = 1;
  $handler->display->display_options['filters']['locked']['exposed'] = TRUE;
  $handler->display->display_options['filters']['locked']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['locked']['expose']['label'] = 'Locked?';
  $handler->display->display_options['filters']['locked']['expose']['operator'] = 'locked_op';
  $handler->display->display_options['filters']['locked']['expose']['identifier'] = 'locked';
  $handler->display->display_options['filters']['locked']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Thread: Pinned */
  $handler->display->display_options['filters']['pinned']['id'] = 'pinned';
  $handler->display->display_options['filters']['pinned']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['pinned']['field'] = 'pinned';
  $handler->display->display_options['filters']['pinned']['value'] = 'All';
  $handler->display->display_options['filters']['pinned']['group'] = 1;
  $handler->display->display_options['filters']['pinned']['exposed'] = TRUE;
  $handler->display->display_options['filters']['pinned']['expose']['operator_id'] = '';
  $handler->display->display_options['filters']['pinned']['expose']['label'] = 'Pinned?';
  $handler->display->display_options['filters']['pinned']['expose']['operator'] = 'pinned_op';
  $handler->display->display_options['filters']['pinned']['expose']['identifier'] = 'pinned';
  $handler->display->display_options['filters']['pinned']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: Thread: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author(s)';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Date: Date (harmony_thread) */
  $handler->display->display_options['filters']['date_filter_1']['id'] = 'date_filter_1';
  $handler->display->display_options['filters']['date_filter_1']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['date_filter_1']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter_1']['operator'] = '>';
  $handler->display->display_options['filters']['date_filter_1']['group'] = 1;
  $handler->display->display_options['filters']['date_filter_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter_1']['expose']['operator_id'] = 'date_filter_1_op';
  $handler->display->display_options['filters']['date_filter_1']['expose']['label'] = 'Posted after';
  $handler->display->display_options['filters']['date_filter_1']['expose']['operator'] = 'date_filter_1_op';
  $handler->display->display_options['filters']['date_filter_1']['expose']['identifier'] = 'date_filter_1';
  $handler->display->display_options['filters']['date_filter_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['date_filter_1']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter_1']['date_fields'] = array(
    'harmony_thread.created' => 'harmony_thread.created',
  );
  $handler->display->display_options['filters']['date_filter_1']['date_method'] = 'AND';
  /* Filter criterion: Date: Date (harmony_thread) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '<';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['exposed'] = TRUE;
  $handler->display->display_options['filters']['date_filter']['expose']['operator_id'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['label'] = 'Posted before';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = 'date_filter_op';
  $handler->display->display_options['filters']['date_filter']['expose']['identifier'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['date_filter']['form_type'] = 'date_popup';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'harmony_thread.created' => 'harmony_thread.created',
  );
  $handler->display->display_options['filters']['date_filter']['date_method'] = 'AND';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/harmony/content/threads';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Threads';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Threads';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['harmony_administration_threads'] = $view;

  $view = new view();
  $view->name = 'harmony_category_sub_category_listing';
  $view->description = 'Lists the sub-categories of the current category.';
  $view->tag = 'harmony_core';
  $view->base_table = 'taxonomy_term_data';
  $view->human_name = 'Category sub-category listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Sub-categories';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  /* Field: Taxonomy term: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['name']['link_to_taxonomy'] = TRUE;
  /* Field: Field: Thread count */
  $handler->display->display_options['fields']['field_harmony_thread_count']['id'] = 'field_harmony_thread_count';
  $handler->display->display_options['fields']['field_harmony_thread_count']['table'] = 'field_data_field_harmony_thread_count';
  $handler->display->display_options['fields']['field_harmony_thread_count']['field'] = 'field_harmony_thread_count';
  $handler->display->display_options['fields']['field_harmony_thread_count']['label'] = 'Threads';
  $handler->display->display_options['fields']['field_harmony_thread_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Sort criterion: Taxonomy term: Weight */
  $handler->display->display_options['sorts']['weight']['id'] = 'weight';
  $handler->display->display_options['sorts']['weight']['table'] = 'taxonomy_term_data';
  $handler->display->display_options['sorts']['weight']['field'] = 'weight';
  /* Contextual filter: Taxonomy term: Parent term */
  $handler->display->display_options['arguments']['parent']['id'] = 'parent';
  $handler->display->display_options['arguments']['parent']['table'] = 'taxonomy_term_hierarchy';
  $handler->display->display_options['arguments']['parent']['field'] = 'parent';
  $handler->display->display_options['arguments']['parent']['default_action'] = 'default';
  $handler->display->display_options['arguments']['parent']['default_argument_type'] = 'taxonomy_tid';
  $handler->display->display_options['arguments']['parent']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['parent']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['parent']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['parent']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['parent']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['parent']['validate_options']['vocabularies'] = array(
    'harmony_category' => 'harmony_category',
  );
  /* Filter criterion: Taxonomy vocabulary: Machine name */
  $handler->display->display_options['filters']['machine_name']['id'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['table'] = 'taxonomy_vocabulary';
  $handler->display->display_options['filters']['machine_name']['field'] = 'machine_name';
  $handler->display->display_options['filters']['machine_name']['value'] = array(
    'harmony_category' => 'harmony_category',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $export['harmony_category_sub_category_listing'] = $view;

  $view = new view();
  $view->name = 'harmony_post_replies_to_post';
  $view->description = '';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Post: Replies to post';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'harmony_post';
  $handler->display->display_options['row_options']['view_mode'] = 'inline_reply';
  /* Field: Post: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Sort criterion: Post: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'harmony_post';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Post: Post is reply to (field_harmony_post_is_reply_to) */
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['id'] = 'field_harmony_post_is_reply_to_target_id';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['table'] = 'field_data_field_harmony_post_is_reply_to';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['field'] = 'field_harmony_post_is_reply_to_target_id';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_harmony_post_is_reply_to_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Post: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  $export['harmony_post_replies_to_post'] = $view;

  $view = new view();
  $view->name = 'harmony_post_revisions';
  $view->description = '';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_post_revision';
  $view->human_name = 'Post revisions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Revisions';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'reverse_counter' => 'reverse_counter',
    'name' => 'name',
    'timestamp' => 'timestamp',
    'log' => 'log',
    'hostname' => 'hostname',
    'is_current' => 'delete_revision',
    'delete_revision' => 'delete_revision',
    'make_current' => 'delete_revision',
    'view_diff' => 'view_diff',
    'field_harmony_thread-revision_id' => 'field_harmony_thread-revision_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'reverse_counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'log' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'hostname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'is_current' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_revision' => array(
      'align' => 'views-align-center',
      'separator' => ' | ',
      'empty_column' => 0,
    ),
    'make_current' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'view_diff' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_harmony_thread-revision_id' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Footer: Global: Text area */
  $handler->display->display_options['footer']['area']['id'] = 'area';
  $handler->display->display_options['footer']['area']['table'] = 'views';
  $handler->display->display_options['footer']['area']['field'] = 'area';
  $handler->display->display_options['footer']['area']['empty'] = TRUE;
  $handler->display->display_options['footer']['area']['content'] = '[field_harmony_thread-revision_id]';
  $handler->display->display_options['footer']['area']['format'] = 'filtered_html';
  $handler->display->display_options['footer']['area']['tokenize'] = TRUE;
  /* Relationship: Post (historical data): Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'harmony_post_revision';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Harmony: View result reverse counter */
  $handler->display->display_options['fields']['reverse_counter']['id'] = 'reverse_counter';
  $handler->display->display_options['fields']['reverse_counter']['table'] = 'views';
  $handler->display->display_options['fields']['reverse_counter']['field'] = 'reverse_counter';
  $handler->display->display_options['fields']['reverse_counter']['label'] = '';
  $handler->display->display_options['fields']['reverse_counter']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['reverse_counter']['prepend'] = 'v';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Post (historical data): Created date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Edited';
  $handler->display->display_options['fields']['timestamp']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['timestamp']['alter']['text'] = '[timestamp] by [name]';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'long';
  /* Field: Post (historical data): Log message */
  $handler->display->display_options['fields']['log']['id'] = 'log';
  $handler->display->display_options['fields']['log']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['log']['field'] = 'log';
  /* Field: Post (historical data): Hostname */
  $handler->display->display_options['fields']['hostname']['id'] = 'hostname';
  $handler->display->display_options['fields']['hostname']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['hostname']['field'] = 'hostname';
  /* Field: Post (historical data): Is current */
  $handler->display->display_options['fields']['is_current']['id'] = 'is_current';
  $handler->display->display_options['fields']['is_current']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['is_current']['field'] = 'is_current';
  $handler->display->display_options['fields']['is_current']['label'] = '';
  $handler->display->display_options['fields']['is_current']['element_label_colon'] = FALSE;
  /* Field: Post (historical data): Administrative delete link */
  $handler->display->display_options['fields']['delete_revision']['id'] = 'delete_revision';
  $handler->display->display_options['fields']['delete_revision']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['delete_revision']['field'] = 'delete_revision';
  $handler->display->display_options['fields']['delete_revision']['label'] = '';
  $handler->display->display_options['fields']['delete_revision']['element_label_colon'] = FALSE;
  /* Field: Post (historical data): Administrative set current revision link */
  $handler->display->display_options['fields']['make_current']['id'] = 'make_current';
  $handler->display->display_options['fields']['make_current']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['make_current']['field'] = 'make_current';
  $handler->display->display_options['fields']['make_current']['label'] = '';
  $handler->display->display_options['fields']['make_current']['element_label_colon'] = FALSE;
  /* Field: Post (historical data): Link to view or AJAX load the post differences */
  $handler->display->display_options['fields']['view_diff']['id'] = 'view_diff';
  $handler->display->display_options['fields']['view_diff']['table'] = 'harmony_post_revision';
  $handler->display->display_options['fields']['view_diff']['field'] = 'view_diff';
  $handler->display->display_options['fields']['view_diff']['label'] = '';
  $handler->display->display_options['fields']['view_diff']['element_label_colon'] = FALSE;
  /* Field: Post (historical data): Thread */
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['id'] = 'field_harmony_thread-revision_id';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['table'] = 'field_revision_field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['field'] = 'field_harmony_thread-revision_id';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['label'] = '';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['alter']['text'] = 'Return to the thread';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['alter']['path'] = 'thread/[field_harmony_thread-revision_id-target_id]';
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_harmony_thread-revision_id']['settings'] = array(
    'link' => 0,
  );
  /* Sort criterion: Post (historical data): Created date */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'harmony_post_revision';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['order'] = 'DESC';
  /* Contextual filter: Post (historical data): Post ID */
  $handler->display->display_options['arguments']['post_id']['id'] = 'post_id';
  $handler->display->display_options['arguments']['post_id']['table'] = 'harmony_post_revision';
  $handler->display->display_options['arguments']['post_id']['field'] = 'post_id';
  $handler->display->display_options['arguments']['post_id']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['post_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['post_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['post_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['post_id']['summary_options']['items_per_page'] = '25';
  $export['harmony_post_revisions'] = $view;

  $view = new view();
  $view->name = 'harmony_thread_administer_posts';
  $view->description = '';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Thread: Administer posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Administer posts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'administer harmony forum content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'harmony_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'counter' => 'counter',
    'name' => 'name',
    'status' => 'status',
    'created' => 'created',
    'updated' => 'updated',
    'hostname' => 'hostname',
    'post_view_text' => 'delete_link',
    'edit_link' => 'delete_link',
    'delete_link' => 'delete_link',
  );
  $handler->display->display_options['style_options']['default'] = 'created';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'counter' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'name' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'status' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'hostname' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'post_view_text' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'edit_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'delete_link' => array(
      'align' => 'text-center',
      'separator' => ' ',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
  );
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No posts have been created.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Post: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Bulk operations: Post */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
  $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '0';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete post',
    ),
    'action::views_bulk_operations_delete_revision' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_script_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_locked_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 0,
      'postpone_processing' => 1,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'harmony_post::field_harmony_thread' => 'harmony_post::field_harmony_thread',
        ),
      ),
    ),
    'action::views_bulk_operations_argument_selector_action' => array(
      'selected' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'url' => '',
      ),
    ),
    'action::harmony_core_post_publish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_reassign_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::system_send_email_action' => array(
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_split_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_unlock_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
    'action::harmony_core_post_unpublish_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 1,
      'override_label' => 0,
      'label' => '',
    ),
  );
  /* Field: Post: Position in thread */
  $handler->display->display_options['fields']['position']['id'] = 'position';
  $handler->display->display_options['fields']['position']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['position']['field'] = 'position';
  $handler->display->display_options['fields']['position']['label'] = '';
  $handler->display->display_options['fields']['position']['element_label_colon'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Author';
  /* Field: Post: Status */
  $handler->display->display_options['fields']['status']['id'] = 'status';
  $handler->display->display_options['fields']['status']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['status']['field'] = 'status';
  /* Field: Post: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Post: Date updated */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Updated';
  $handler->display->display_options['fields']['updated']['date_format'] = 'short';
  /* Field: Post: Hostname */
  $handler->display->display_options['fields']['hostname']['id'] = 'hostname';
  $handler->display->display_options['fields']['hostname']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['hostname']['field'] = 'hostname';
  /* Field: Post: Link to view or AJAX load the posts text */
  $handler->display->display_options['fields']['post_view_text']['id'] = 'post_view_text';
  $handler->display->display_options['fields']['post_view_text']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['post_view_text']['field'] = 'post_view_text';
  $handler->display->display_options['fields']['post_view_text']['label'] = '';
  $handler->display->display_options['fields']['post_view_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['post_view_text']['text'] = 'view post text';
  $handler->display->display_options['fields']['post_view_text']['newline_prepend'] = FALSE;
  /* Field: Post: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = '';
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_link']['text'] = 'edit';
  /* Field: Post: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = 'Operations';
  $handler->display->display_options['fields']['delete_link']['text'] = 'delete';
  /* Contextual filter: Post: Thread (field_harmony_thread) */
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['id'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['field'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['default_argument_type'] = 'harmony_thread_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Post: Text (field_harmony_text) */
  $handler->display->display_options['filters']['field_harmony_text_value']['id'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['table'] = 'field_data_field_harmony_text';
  $handler->display->display_options['filters']['field_harmony_text_value']['field'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_harmony_text_value']['group'] = 1;
  $handler->display->display_options['filters']['field_harmony_text_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['operator_id'] = 'field_harmony_text_value_op';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['label'] = 'Text contains';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['operator'] = 'field_harmony_text_value_op';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['identifier'] = 'field_harmony_text_value';
  $handler->display->display_options['filters']['field_harmony_text_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['group'] = 1;
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Author';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  /* Filter criterion: Post: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['exposed'] = TRUE;
  $handler->display->display_options['filters']['status']['expose']['operator_id'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['status']['expose']['operator'] = 'status_op';
  $handler->display->display_options['filters']['status']['expose']['identifier'] = 'status';
  $handler->display->display_options['filters']['status']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'thread/%/administer-posts';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Administer posts';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['harmony_thread_administer_posts'] = $view;

  $view = new view();
  $view->name = 'harmony_thread_listing';
  $view->description = 'Listing of threads belonging to a category,';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_thread';
  $view->human_name = 'Thread listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view harmony_threads';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_tags'] = array(
    0 => 'harmony_access',
  );
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'load_more';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'harmony_table';
  $handler->display->display_options['style_options']['columns'] = array(
    'pinned' => 'title',
    'title' => 'title',
    'field_harmony_category' => 'field_harmony_category',
    'field_harmony_post_count' => 'field_harmony_post_count',
    'picture' => 'picture',
    'views' => 'views',
    'likes' => 'likes',
    'updated' => 'updated',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'pinned' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => '',
      'meta_field' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
      'cell_class' => 'tl-title',
      'meta_field' => 0,
    ),
    'field_harmony_category' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-category',
      'meta_field' => 1,
    ),
    'field_harmony_post_count' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-posts',
      'meta_field' => 1,
    ),
    'picture' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-users',
      'meta_field' => 1,
    ),
    'views' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-views',
      'meta_field' => 1,
    ),
    'likes' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-likes',
      'meta_field' => 1,
    ),
    'updated' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'text-center',
      'separator' => '',
      'empty_column' => 0,
      'cell_class' => 'tl-activity',
      'meta_field' => 1,
    ),
  );
  /* Header: Global: Harmony listing header */
  $handler->display->display_options['header']['harmony_listing_header']['id'] = 'harmony_listing_header';
  $handler->display->display_options['header']['harmony_listing_header']['table'] = 'views';
  $handler->display->display_options['header']['harmony_listing_header']['field'] = 'harmony_listing_header';
  $handler->display->display_options['header']['harmony_listing_header']['empty'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'No threads have been posted.';
  $handler->display->display_options['empty']['area']['format'] = 'plain_text';
  /* Relationship: Thread: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'harmony_thread';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  /* Field: Thread: Pinned */
  $handler->display->display_options['fields']['pinned']['id'] = 'pinned';
  $handler->display->display_options['fields']['pinned']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['pinned']['field'] = 'pinned';
  $handler->display->display_options['fields']['pinned']['label'] = '';
  $handler->display->display_options['fields']['pinned']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['pinned']['alter']['text'] = '<span class="harmony-pinned">[pinned]</span>';
  $handler->display->display_options['fields']['pinned']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['pinned']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['pinned']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['pinned']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['pinned']['type'] = 'custom';
  $handler->display->display_options['fields']['pinned']['type_custom_true'] = 'Pinned';
  $handler->display->display_options['fields']['pinned']['not'] = 0;
  /* Field: Thread: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_thread'] = TRUE;
  /* Field: Thread: Category */
  $handler->display->display_options['fields']['field_harmony_category']['id'] = 'field_harmony_category';
  $handler->display->display_options['fields']['field_harmony_category']['table'] = 'field_data_field_harmony_category';
  $handler->display->display_options['fields']['field_harmony_category']['field'] = 'field_harmony_category';
  /* Field: Field: Post count */
  $handler->display->display_options['fields']['field_harmony_post_count']['id'] = 'field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['table'] = 'field_data_field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['field'] = 'field_harmony_post_count';
  $handler->display->display_options['fields']['field_harmony_post_count']['label'] = 'Posts';
  $handler->display->display_options['fields']['field_harmony_post_count']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_post_count']['alter']['text'] = '[field_harmony_post_count]<span class="inline-visible-xs"> posts</span>';
  $handler->display->display_options['fields']['field_harmony_post_count']['settings'] = array(
    'thousand_separator' => ',',
    'prefix_suffix' => 1,
  );
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['relationship'] = 'uid';
  $handler->display->display_options['fields']['picture']['label'] = 'Author';
  $handler->display->display_options['fields']['picture']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['picture']['alter']['text'] = '<span class="inline-visible-xs">By </span>[picture]';
  $handler->display->display_options['fields']['picture']['element_type'] = 'span';
  $handler->display->display_options['fields']['picture']['element_class'] = 'avatar';
  $handler->display->display_options['fields']['picture']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'harmony-32-32';
  /* Field: Thread: Views */
  $handler->display->display_options['fields']['views']['id'] = 'views';
  $handler->display->display_options['fields']['views']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['views']['field'] = 'views';
  $handler->display->display_options['fields']['views']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['views']['alter']['text'] = '[views]<span class="inline-visible-xs"> Views</span>';
  /* Field: Thread: Likes */
  $handler->display->display_options['fields']['likes']['id'] = 'likes';
  $handler->display->display_options['fields']['likes']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['likes']['field'] = 'likes';
  $handler->display->display_options['fields']['likes']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['likes']['alter']['text'] = '<i class="fa fa-heart"></i> [likes] ';
  /* Field: Thread: Date updated */
  $handler->display->display_options['fields']['updated']['id'] = 'updated';
  $handler->display->display_options['fields']['updated']['table'] = 'harmony_thread';
  $handler->display->display_options['fields']['updated']['field'] = 'updated';
  $handler->display->display_options['fields']['updated']['label'] = 'Updated';
  $handler->display->display_options['fields']['updated']['date_format'] = 'short';
  /* Sort criterion: Thread: Pinned */
  $handler->display->display_options['sorts']['pinned']['id'] = 'pinned';
  $handler->display->display_options['sorts']['pinned']['table'] = 'harmony_thread';
  $handler->display->display_options['sorts']['pinned']['field'] = 'pinned';
  $handler->display->display_options['sorts']['pinned']['order'] = 'DESC';
  /* Sort criterion: Thread: Date updated */
  $handler->display->display_options['sorts']['updated']['id'] = 'updated';
  $handler->display->display_options['sorts']['updated']['table'] = 'harmony_thread';
  $handler->display->display_options['sorts']['updated']['field'] = 'updated';
  $handler->display->display_options['sorts']['updated']['order'] = 'DESC';
  /* Contextual filter: Thread: Category (field_harmony_category) */
  $handler->display->display_options['arguments']['field_harmony_category_tid']['id'] = 'field_harmony_category_tid';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['table'] = 'field_data_field_harmony_category';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['field'] = 'field_harmony_category_tid';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_harmony_category_tid']['validate']['type'] = 'taxonomy_term';
  $handler->display->display_options['arguments']['field_harmony_category_tid']['validate_options']['vocabularies'] = array(
    'harmony_category' => 'harmony_category',
  );
  /* Filter criterion: Thread: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  /* Filter criterion: Thread: Hidden */
  $handler->display->display_options['filters']['hidden']['id'] = 'hidden';
  $handler->display->display_options['filters']['hidden']['table'] = 'harmony_thread';
  $handler->display->display_options['filters']['hidden']['field'] = 'hidden';
  $handler->display->display_options['filters']['hidden']['value'] = '0';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Forum';
  $handler->display->display_options['path'] = 'forum';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Forum';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['harmony_thread_listing'] = $view;

  $view = new view();
  $view->name = 'harmony_thread_posts_listing';
  $view->description = '';
  $view->tag = 'harmony_core';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Thread: Posts listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'harmony_post';
  /* Field: Post: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Sort criterion: Post: Date created */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'harmony_post';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  /* Contextual filter: Post: Thread (field_harmony_thread) */
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['id'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['field'] = 'field_harmony_thread_target_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['default_argument_type'] = 'harmony_thread_id';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_harmony_thread_target_id']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Post: Status */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'harmony_post';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = array(
    1 => '1',
  );
  $export['harmony_thread_posts_listing'] = $view;

  return $export;
}
