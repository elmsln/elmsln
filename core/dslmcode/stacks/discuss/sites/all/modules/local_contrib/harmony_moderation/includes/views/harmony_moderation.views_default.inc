<?php

/**
 * Implements hook_views_default_views().
 */
function harmony_moderation_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'harmony_moderation_reported_posts';
  $view->description = 'A listing of all the reported Harmony posts.';
  $view->tag = 'harmony, harmony_moderation';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Reported posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Reported posts';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'moderate harmony_posts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'views_bulk_operations' => 'views_bulk_operations',
    'field_harmony_thread' => 'field_harmony_thread',
    'name_1' => 'name_1',
    'created' => 'created',
    'count' => 'count',
    'last_updated' => 'last_updated',
    'post_view_text' => 'post_view_text',
    'harmony_moderation_view_reports' => 'post_view_text',
    'edit_link' => 'edit_link',
    'delete_link' => 'delete_link',
    'ops' => 'ops',
  );
  $handler->display->display_options['style_options']['default'] = 'last_updated';
  $handler->display->display_options['style_options']['info'] = array(
    'views_bulk_operations' => array(
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
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'created' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'count' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'last_updated' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'post_view_text' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'harmony_moderation_view_reports' => array(
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
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['label'] = 'Guidance text';
  $handler->display->display_options['header']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['header']['area_text_custom']['content'] = '<p>If a post has been reported enough times it is automatically unpublished, if that post   happens to be   the first post in a thread, the whole thread is unpublished. Removing the report will not re-publish but Whitelisting will.</p>
      <p>You can sort results by when the post was reported by click the "Report" table heading.</p>
      <p>Links in the &quot;Operations&quot; column will not take you away from this page, links in the &quot;Actions&quot; column will.</p>
      <p><strong>Whitelisting</strong> will remove all reports against that post, publish the post (if unpublished) and prevent future reports being added for the post.</p>';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<p class="text-center">No posts have been reported.</p>';
  /* Relationship: Post: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'post_user';
  /* Relationship: Flags: harmony_post_report counter */
  $handler->display->display_options['relationships']['flag_count_rel']['id'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['flag_count_rel']['field'] = 'flag_count_rel';
  $handler->display->display_options['relationships']['flag_count_rel']['flag'] = 'harmony_post_report';
  /* Relationship: Flags: harmony_post_report_whitelist */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['label'] = 'whitelist';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'harmony_post_report_whitelist';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
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
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
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
      'selected' => 0,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 0,
      'label' => '',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          '_all_' => '_all_',
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
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Publish post(s)',
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
      'override_label' => 1,
      'label' => 'Unpublish post(s)',
    ),
  );
  /* Field: Post: Thread */
  $handler->display->display_options['fields']['field_harmony_thread']['id'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['field'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['label'] = 'Post';
  $handler->display->display_options['fields']['field_harmony_thread']['settings'] = array(
    'link' => 1,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['name_1']['label'] = 'Author';
  /* Field: Post: Date created */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Flags: Flag counter */
  $handler->display->display_options['fields']['count']['id'] = 'count';
  $handler->display->display_options['fields']['count']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['count']['field'] = 'count';
  $handler->display->display_options['fields']['count']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['count']['label'] = '# of reports';
  /* Field: Flags: Time last flagged */
  $handler->display->display_options['fields']['last_updated']['id'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['table'] = 'flag_counts';
  $handler->display->display_options['fields']['last_updated']['field'] = 'last_updated';
  $handler->display->display_options['fields']['last_updated']['relationship'] = 'flag_count_rel';
  $handler->display->display_options['fields']['last_updated']['label'] = 'Last reported';
  $handler->display->display_options['fields']['last_updated']['date_format'] = 'short';
  $handler->display->display_options['fields']['last_updated']['second_date_format'] = 'long';
  /* Field: Post: Link to view or AJAX load the posts text */
  $handler->display->display_options['fields']['post_view_text']['id'] = 'post_view_text';
  $handler->display->display_options['fields']['post_view_text']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['post_view_text']['field'] = 'post_view_text';
  $handler->display->display_options['fields']['post_view_text']['label'] = 'Operations';
  $handler->display->display_options['fields']['post_view_text']['text'] = 'View posts\' text';
  /* Field: Post: Link to view or AJAX load the reports */
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['id'] = 'harmony_moderation_view_reports';
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['field'] = 'harmony_moderation_view_reports';
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['label'] = '';
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['harmony_moderation_view_reports']['newline_prepend'] = FALSE;
  /* Field: Post: Edit link */
  $handler->display->display_options['fields']['edit_link']['id'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['edit_link']['field'] = 'edit_link';
  $handler->display->display_options['fields']['edit_link']['label'] = '';
  $handler->display->display_options['fields']['edit_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['edit_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['edit_link']['text'] = 'Edit post';
  /* Field: Post: Delete link */
  $handler->display->display_options['fields']['delete_link']['id'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['table'] = 'harmony_post';
  $handler->display->display_options['fields']['delete_link']['field'] = 'delete_link';
  $handler->display->display_options['fields']['delete_link']['label'] = '';
  $handler->display->display_options['fields']['delete_link']['exclude'] = TRUE;
  $handler->display->display_options['fields']['delete_link']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['delete_link']['text'] = 'Delete post';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = 'Actions';
  $handler->display->display_options['fields']['ops']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['ops']['alter']['text'] = '[edit_link]<br>
  [delete_link]<br>
  [ops]';
  $handler->display->display_options['fields']['ops']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['ops']['link_type'] = 'confirm';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/harmony/content/moderation';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Reported posts';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'tab';
  $handler->display->display_options['tab_options']['title'] = 'Reported posts';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $views[] = $view;

  $view = new view();
  $view->name = 'harmony_moderation_reported_posts_post';
  $view->description = '';
  $view->tag = 'harmony, harmony_moderation';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Reported posts - post';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Reports';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'name' => 'name',
    'field_harmony_moderation_reason' => 'field_harmony_moderation_reason',
    'field_harmony_moderation_text' => 'field_harmony_moderation_text',
    'nothing' => 'nothing',
    'timestamp' => 'timestamp',
    'harmony_moderation_remove_report' => 'harmony_moderation_remove_report',
    'field_harmony_moderation_source' => 'field_harmony_moderation_source',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'field_harmony_moderation_source' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
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
    'field_harmony_moderation_reason' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_harmony_moderation_text' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'nothing' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'harmony_moderation_remove_report' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<p>This post doesn\'t have any reports against it.</p>';
  /* Relationship: Flags: harmony_post_report */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'harmony_post_report';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Flags: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'flagging';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'flag_content_rel';
  /* Field: Flagging: Source */
  $handler->display->display_options['fields']['field_harmony_moderation_source']['id'] = 'field_harmony_moderation_source';
  $handler->display->display_options['fields']['field_harmony_moderation_source']['table'] = 'field_data_field_harmony_moderation_source';
  $handler->display->display_options['fields']['field_harmony_moderation_source']['field'] = 'field_harmony_moderation_source';
  $handler->display->display_options['fields']['field_harmony_moderation_source']['relationship'] = 'flag_content_rel';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Reporter / Author';
  /* Field: Flagging: Reason for reporting */
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['id'] = 'field_harmony_moderation_reason';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['table'] = 'field_data_field_harmony_moderation_reason';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['field'] = 'field_harmony_moderation_reason';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['label'] = '';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['alter']['text'] = '[field_harmony_moderation_reason]<br>[field_harmony_moderation_text]';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_harmony_moderation_reason']['multi_type'] = 'ul';
  /* Field: Flagging: Additional information */
  $handler->display->display_options['fields']['field_harmony_moderation_text']['id'] = 'field_harmony_moderation_text';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['table'] = 'field_data_field_harmony_moderation_text';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['field'] = 'field_harmony_moderation_text';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['label'] = '';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_moderation_text']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_harmony_moderation_text']['alter']['text'] = '<br><strong>Additional information:</strong><br>[field_harmony_moderation_text]';
  $handler->display->display_options['fields']['field_harmony_moderation_text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_harmony_moderation_text']['hide_empty'] = TRUE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = 'Reason for reporting';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '[field_harmony_moderation_reason]
    [field_harmony_moderation_text]';
  $handler->display->display_options['fields']['nothing']['alter']['trim_whitespace'] = TRUE;
  /* Field: Flags: Flagged time */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'flagging';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Reported';
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  $handler->display->display_options['fields']['timestamp']['second_date_format'] = 'long';
  /* Field: Flags: Link to remove or AJAX remove a report. */
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['id'] = 'harmony_moderation_remove_report';
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['table'] = 'flagging';
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['field'] = 'harmony_moderation_remove_report';
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['label'] = 'Operations';
  $handler->display->display_options['fields']['harmony_moderation_remove_report']['element_label_colon'] = FALSE;
  /* Sort criterion: Flags: Flagged time */
  $handler->display->display_options['sorts']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['table'] = 'flagging';
  $handler->display->display_options['sorts']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['sorts']['timestamp']['relationship'] = 'flag_content_rel';
  /* Contextual filter: Post: Post ID */
  $handler->display->display_options['arguments']['post_id']['id'] = 'post_id';
  $handler->display->display_options['arguments']['post_id']['table'] = 'harmony_post';
  $handler->display->display_options['arguments']['post_id']['field'] = 'post_id';
  $handler->display->display_options['arguments']['post_id']['default_action'] = 'empty';
  $handler->display->display_options['arguments']['post_id']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['post_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['post_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['post_id']['summary_options']['items_per_page'] = '25';
  $views[] = $view;

  $view = new view();
  $view->name = 'harmony_moderation_whitelisted_posts';
  $view->description = '';
  $view->tag = 'harmony, harmony_moderation';
  $view->base_table = 'harmony_post';
  $view->human_name = 'Whitelisted posts';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Whitelisted posts';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'moderate harmony_posts';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_harmony_thread' => 'field_harmony_thread',
    'name_1' => 'name_1',
    'name' => 'name',
    'timestamp' => 'timestamp',
    'ops' => 'ops',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'field_harmony_thread' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'name_1' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => 'views-align-center',
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
    'timestamp' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
    'ops' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: Unfiltered text */
  $handler->display->display_options['header']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['header']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['header']['area_text_custom']['content'] = '<p>Posts which are in the whitelist cannot be reported as abusive.</p>';
  /* No results behavior: Global: Unfiltered text */
  $handler->display->display_options['empty']['area_text_custom']['id'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['table'] = 'views';
  $handler->display->display_options['empty']['area_text_custom']['field'] = 'area_text_custom';
  $handler->display->display_options['empty']['area_text_custom']['empty'] = TRUE;
  $handler->display->display_options['empty']['area_text_custom']['content'] = '<p class="text-center">No posts have been whitelisted.</p>';
  /* Relationship: Flags: harmony_post_report_whitelist */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'harmony_post_report_whitelist';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Flags: User */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'flagging';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Post: Author */
  $handler->display->display_options['relationships']['uid_1']['id'] = 'uid_1';
  $handler->display->display_options['relationships']['uid_1']['table'] = 'harmony_post';
  $handler->display->display_options['relationships']['uid_1']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid_1']['label'] = 'post_user';
  /* Field: Post: Thread */
  $handler->display->display_options['fields']['field_harmony_thread']['id'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['table'] = 'field_data_field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['field'] = 'field_harmony_thread';
  $handler->display->display_options['fields']['field_harmony_thread']['settings'] = array(
    'link' => 1,
  );
  /* Field: User: Name */
  $handler->display->display_options['fields']['name_1']['id'] = 'name_1';
  $handler->display->display_options['fields']['name_1']['table'] = 'users';
  $handler->display->display_options['fields']['name_1']['field'] = 'name';
  $handler->display->display_options['fields']['name_1']['relationship'] = 'uid_1';
  $handler->display->display_options['fields']['name_1']['label'] = 'Post author';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Whitelisted by';
  /* Field: Flags: Flagged time */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'flagging';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Whitelisted on';
  $handler->display->display_options['fields']['timestamp']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['timestamp']['date_format'] = 'short';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flagging';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = 'Actions';
  $handler->display->display_options['fields']['ops']['link_type'] = 'confirm';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/harmony/content/moderation/whitelisted-posts';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Whitelisted posts';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $views[] = $view;

  return $views;
}
