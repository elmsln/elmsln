<?php
/**
 * @file
 * Default views.
 */

/**
 * Implements hook_views_default_views().
 */
function entityform_views_default_views() {
  $view = new view;
  $view->name = 'entityforms';
  $view->description = 'A list of all entityforms submissions to be as an admin report';
  $view->tag = 'entityforms';
  $view->base_table = 'entityform';
  $view->human_name = 'Entityforms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view any entityform';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
      'name' => 'name',
      'entityform_id' => 'entityform_id',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
      'name' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
      ),
      'entityform_id' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
      ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No form submissions available.';
  /* Relationship: Entityform: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'entityform';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  if (module_exists('views_bulk_operations')) {
    /* Field: Bulk operations: Entityform */
    $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'entityform';
    $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['external'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['more_link'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['html'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['views_bulk_operations']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['hide_empty'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['empty_zero'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['entity_load_capacity'] = '10';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['operations'] = array(
        'action::views_bulk_operations_delete_item' => array(
            'selected' => 1,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 1,
            'label' => 'Delete Submissions',
        ),
        'action::system_message_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::views_bulk_operations_script_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::views_bulk_operations_modify_action' => array(
            'selected' => 0,
            'use_queue' => 0,
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
        'action::system_goto_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::system_send_email_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
    );
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['enable_select_all_pages'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_type'] = '1';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_result'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['merge_single_action'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['force_single'] = 0;
  }
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Submitter';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Entityform: Link */
  $handler->display->display_options['fields']['link_entityform']['id'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['link_entityform']['field'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['label'] = 'View';
  $handler->display->display_options['fields']['link_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_entityform']['empty_zero'] = 0;
  /* Field: Entityform: Edit Link */
  $handler->display->display_options['fields']['edit_entityform']['id'] = 'edit_entityform';
  $handler->display->display_options['fields']['edit_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['edit_entityform']['field'] = 'edit_entityform';
  $handler->display->display_options['fields']['edit_entityform']['label'] = 'Edit';
  $handler->display->display_options['fields']['edit_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['hide_alter_empty'] = 1;
  /* Field: Entityform: Delete Link */
  $handler->display->display_options['fields']['delete_entityform']['id'] = 'delete_entityform';
  $handler->display->display_options['fields']['delete_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['delete_entityform']['field'] = 'delete_entityform';
  $handler->display->display_options['fields']['delete_entityform']['label'] = 'Delete';
  $handler->display->display_options['fields']['delete_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['hide_alter_empty'] = 0;
  /* Field: Entityform Type: Label */
  $handler->display->display_options['fields']['label_1']['id'] = 'label_1';
  $handler->display->display_options['fields']['label_1']['table'] = 'entityform_type';
  $handler->display->display_options['fields']['label_1']['field'] = 'label';
  $handler->display->display_options['fields']['label_1']['label'] = 'Form Type';
  $handler->display->display_options['fields']['label_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['label_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['label_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['label_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['label_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['label_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['label_1']['empty_zero'] = 0;
  /* Field: Entityform: Date submitted */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'entityform';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: Entityform: Date changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'entityform';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 0;
  /* Sort criterion: Entityform: Date submitted */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'entityform';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Entityform: Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'entityform';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['type']['title_enable'] = 1;
  $handler->display->display_options['arguments']['type']['title'] = 'Submissions for %1';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['glossary'] = 0;
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['type']['break_phrase'] = 0;
  /* Filter criterion: Entityform: Date submitted */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'entityform';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = '>';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date submitted';
  $handler->display->display_options['filters']['created']['expose']['use_operator'] = 1;
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
  /* Filter criterion: Entityform: Draft */
  $handler->display->display_options['filters']['draft']['id'] = 'draft';
  $handler->display->display_options['filters']['draft']['table'] = 'entityform';
  $handler->display->display_options['filters']['draft']['field'] = 'draft';
  $handler->display->display_options['filters']['draft']['operator'] = '!=';
  $handler->display->display_options['filters']['draft']['value']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'entityforms_admin_page');
  $handler->display->display_options['path'] = 'entityform-submissions/submissions/%/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = 'View Submissions for all Entityforms';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Submissions';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  if (module_exists('views_data_export')) {
    /* Display: XML Data export */
    $handler = $view->new_display('views_data_export', 'XML Data export', 'autofields_xml');
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'views_data_export_xml';
    $handler->display->display_options['style_options']['provide_file'] = 1;
    $handler->display->display_options['style_options']['filename'] = '%1-title_submissions_%timestamp-full.xml';
    $handler->display->display_options['style_options']['parent_sort'] = 1;
    $handler->display->display_options['style_options']['transform'] = 1;
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['relationship'] = 'uid';
    $handler->display->display_options['fields']['name']['label'] = 'Submitter';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['link_to_user'] = 1;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    /* Field: Entityform Type: Label */
    $handler->display->display_options['fields']['label_1']['id'] = 'label_1';
    $handler->display->display_options['fields']['label_1']['table'] = 'entityform_type';
    $handler->display->display_options['fields']['label_1']['field'] = 'label';
    $handler->display->display_options['fields']['label_1']['label'] = 'Form Type';
    $handler->display->display_options['fields']['label_1']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['external'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['label_1']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['label_1']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['html'] = 0;
    $handler->display->display_options['fields']['label_1']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['label_1']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['label_1']['hide_empty'] = 0;
    $handler->display->display_options['fields']['label_1']['empty_zero'] = 0;
    /* Field: Entityform: Date submitted */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'entityform';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['created']['alter']['external'] = 0;
    $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['created']['alter']['html'] = 0;
    $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['created']['hide_empty'] = 0;
    $handler->display->display_options['fields']['created']['empty_zero'] = 0;
    $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['created']['date_format'] = 'medium';
    /* Field: Entityform: Date changed */
    $handler->display->display_options['fields']['changed']['id'] = 'changed';
    $handler->display->display_options['fields']['changed']['table'] = 'entityform';
    $handler->display->display_options['fields']['changed']['field'] = 'changed';
    $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
    $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
    $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
    $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 0;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: Entityform: Type */
    $handler->display->display_options['arguments']['type']['id'] = 'type';
    $handler->display->display_options['arguments']['type']['table'] = 'entityform';
    $handler->display->display_options['arguments']['type']['field'] = 'type';
    $handler->display->display_options['arguments']['type']['title_enable'] = 1;
    $handler->display->display_options['arguments']['type']['title'] = 'entityform_submissions_%1';
    $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
    $handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['type']['glossary'] = 0;
    $handler->display->display_options['arguments']['type']['limit'] = '0';
    $handler->display->display_options['arguments']['type']['transform_dash'] = 0;
    $handler->display->display_options['arguments']['type']['break_phrase'] = 0;
    $handler->display->display_options['path'] = 'entityform-submissions/downloads/%/xml';
    $handler->display->display_options['displays'] = array(
        'entityforms_admin_page' => 'entityforms_admin_page',
        'autofields_table' => 'autofields_table',
        'block_1' => 'block_1',
        'default' => 0,
    );

    /* Display: CSV Data export */
    $handler = $view->new_display('views_data_export', 'CSV Data export', 'autofields_csv');
    $handler->display->display_options['pager']['type'] = 'none';
    $handler->display->display_options['pager']['options']['offset'] = '0';
    $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
    $handler->display->display_options['style_options']['provide_file'] = 1;
    $handler->display->display_options['style_options']['filename'] = '%1-title_submissions_%timestamp-full.csv';
    $handler->display->display_options['style_options']['parent_sort'] = 1;
    $handler->display->display_options['style_options']['quote'] = 1;
    $handler->display->display_options['style_options']['trim'] = 0;
    $handler->display->display_options['style_options']['replace_newlines'] = 0;
    $handler->display->display_options['style_options']['header'] = 1;
    $handler->display->display_options['style_options']['encoding'] = 'ASCII';
    $handler->display->display_options['defaults']['fields'] = FALSE;
    /* Field: User: Name */
    $handler->display->display_options['fields']['name']['id'] = 'name';
    $handler->display->display_options['fields']['name']['table'] = 'users';
    $handler->display->display_options['fields']['name']['field'] = 'name';
    $handler->display->display_options['fields']['name']['relationship'] = 'uid';
    $handler->display->display_options['fields']['name']['label'] = 'Submitter';
    $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['name']['alter']['external'] = 0;
    $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['name']['alter']['html'] = 0;
    $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['name']['hide_empty'] = 0;
    $handler->display->display_options['fields']['name']['empty_zero'] = 0;
    $handler->display->display_options['fields']['name']['link_to_user'] = 1;
    $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
    /* Field: Entityform Type: Label */
    $handler->display->display_options['fields']['label_1']['id'] = 'label_1';
    $handler->display->display_options['fields']['label_1']['table'] = 'entityform_type';
    $handler->display->display_options['fields']['label_1']['field'] = 'label';
    $handler->display->display_options['fields']['label_1']['label'] = 'Form Type';
    $handler->display->display_options['fields']['label_1']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['external'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['label_1']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['label_1']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['label_1']['alter']['html'] = 0;
    $handler->display->display_options['fields']['label_1']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['label_1']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['label_1']['hide_empty'] = 0;
    $handler->display->display_options['fields']['label_1']['empty_zero'] = 0;
    /* Field: Entityform: Date submitted */
    $handler->display->display_options['fields']['created']['id'] = 'created';
    $handler->display->display_options['fields']['created']['table'] = 'entityform';
    $handler->display->display_options['fields']['created']['field'] = 'created';
    $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['created']['alter']['external'] = 0;
    $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['created']['alter']['html'] = 0;
    $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['created']['hide_empty'] = 0;
    $handler->display->display_options['fields']['created']['empty_zero'] = 0;
    $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['created']['date_format'] = 'medium';
    /* Field: Entityform: Date changed */
    $handler->display->display_options['fields']['changed']['id'] = 'changed';
    $handler->display->display_options['fields']['changed']['table'] = 'entityform';
    $handler->display->display_options['fields']['changed']['field'] = 'changed';
    $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
    $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
    $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
    $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
    $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 0;
    $handler->display->display_options['defaults']['arguments'] = FALSE;
    /* Contextual filter: Entityform: Type */
    $handler->display->display_options['arguments']['type']['id'] = 'type';
    $handler->display->display_options['arguments']['type']['table'] = 'entityform';
    $handler->display->display_options['arguments']['type']['field'] = 'type';
    $handler->display->display_options['arguments']['type']['title_enable'] = 1;
    $handler->display->display_options['arguments']['type']['title'] = 'entityform_submissions_%1';
    $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
    $handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
    $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
    $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
    $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
    $handler->display->display_options['arguments']['type']['glossary'] = 0;
    $handler->display->display_options['arguments']['type']['limit'] = '0';
    $handler->display->display_options['arguments']['type']['transform_dash'] = 0;
    $handler->display->display_options['arguments']['type']['break_phrase'] = 0;
    $handler->display->display_options['path'] = 'entityform-submissions/downloads/%/csv';
    $handler->display->display_options['displays'] = array(
        'entityforms_admin_page' => 'entityforms_admin_page',
        'autofields_table' => 'autofields_table',
        'default' => 0,
    );
  }
  /* Display: Table */
  $handler = $view->new_display('page', 'Table', 'autofields_table');
  $handler->display->display_options['defaults']['fields'] = FALSE;
  if (module_exists('views_bulk_operations')) {
    /* Field: Bulk operations: Entityform */
    $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'entityform';
    $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
    $handler->display->display_options['fields']['views_bulk_operations']['label'] = '';
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['alter_text'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['make_link'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['absolute'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['external'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['replace_spaces'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim_whitespace'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['nl2br'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['word_boundary'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['ellipsis'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['more_link'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['strip_tags'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['trim'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['alter']['html'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['element_label_colon'] = FALSE;
    $handler->display->display_options['fields']['views_bulk_operations']['element_default_classes'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['hide_empty'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['empty_zero'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['hide_alter_empty'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['entity_load_capacity'] = '10';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['operations'] = array(
        'action::views_bulk_operations_delete_item' => array(
            'selected' => 1,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 1,
            'label' => 'Delete Submissions',
        ),
        'action::system_message_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::views_bulk_operations_script_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::views_bulk_operations_modify_action' => array(
            'selected' => 0,
            'use_queue' => 0,
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
        'action::system_goto_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
        'action::system_send_email_action' => array(
            'selected' => 0,
            'use_queue' => 0,
            'skip_confirmation' => 0,
            'override_label' => 0,
            'label' => '',
        ),
    );
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['enable_select_all_pages'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_type'] = '1';
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['display_result'] = 1;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['merge_single_action'] = 0;
    $handler->display->display_options['fields']['views_bulk_operations']['vbo']['force_single'] = 0;
  }
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Submitter';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Entityform: Link */
  $handler->display->display_options['fields']['link_entityform']['id'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['link_entityform']['field'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['label'] = 'View';
  $handler->display->display_options['fields']['link_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_entityform']['empty_zero'] = 0;
  /* Field: Entityform Type: Label */
  $handler->display->display_options['fields']['label_1']['id'] = 'label_1';
  $handler->display->display_options['fields']['label_1']['table'] = 'entityform_type';
  $handler->display->display_options['fields']['label_1']['field'] = 'label';
  $handler->display->display_options['fields']['label_1']['label'] = 'Form Type';
  $handler->display->display_options['fields']['label_1']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['external'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['label_1']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['label_1']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['label_1']['alter']['html'] = 0;
  $handler->display->display_options['fields']['label_1']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['label_1']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['label_1']['hide_empty'] = 0;
  $handler->display->display_options['fields']['label_1']['empty_zero'] = 0;
  /* Field: Entityform: Date submitted */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'entityform';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: Entityform: Date changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'entityform';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 0;
  $handler->display->display_options['path'] = 'entityform-submissions/submissions/%/table';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Table';
  $handler->display->display_options['menu']['description'] = 'View Submissions for all Entityforms';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';


  $views[$view->name] = $view;
  /*
   * Views to Display Entityform types that will links to submissions
   */
  $view = new view;
  $view->name = 'entityform_type_list';
  $view->description = 'Provide an index of entityform types that link to submission View';
  $view->tag = 'default';
  $view->base_table = 'entityform_type';
  $view->human_name = 'Entityform Type List';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Entityform Submissions';
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'view any entityform';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '30';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
      'type' => 'type',
      'label' => 'label',
  );
  $handler->display->display_options['style_options']['default'] = 'type';
  $handler->display->display_options['style_options']['info'] = array(
      'type' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
      'label' => array(
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
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['empty'] = FALSE;
  $handler->display->display_options['header']['area']['content'] = 'Click a form label below to view the forms submissions';
  $handler->display->display_options['header']['area']['format'] = 'filtered_html';
  $handler->display->display_options['header']['area']['tokenize'] = 0;
  /* Field: Entityform Type: Machine-readable name */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'entityform_type';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  $handler->display->display_options['fields']['type']['label'] = '';
  $handler->display->display_options['fields']['type']['exclude'] = TRUE;
  $handler->display->display_options['fields']['type']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['type']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['type']['alter']['external'] = 0;
  $handler->display->display_options['fields']['type']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['type']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['type']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['type']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['type']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['type']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['type']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['type']['alter']['html'] = 0;
  $handler->display->display_options['fields']['type']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['type']['hide_empty'] = 0;
  $handler->display->display_options['fields']['type']['empty_zero'] = 0;
  $handler->display->display_options['fields']['type']['hide_alter_empty'] = 1;
  /* Field: Entityform Type: Label */
  $handler->display->display_options['fields']['label']['id'] = 'label';
  $handler->display->display_options['fields']['label']['table'] = 'entityform_type';
  $handler->display->display_options['fields']['label']['field'] = 'label';
  $handler->display->display_options['fields']['label']['label'] = 'Entityform Type';
  $handler->display->display_options['fields']['label']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['label']['alter']['make_link'] = 1;
  $handler->display->display_options['fields']['label']['alter']['path'] = 'admin/reports/entityforms/submissions/[type]';
  $handler->display->display_options['fields']['label']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['label']['alter']['external'] = 0;
  $handler->display->display_options['fields']['label']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['label']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['label']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['label']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['label']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['label']['alter']['more_link'] = 0;
  $handler->display->display_options['fields']['label']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['label']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['label']['alter']['html'] = 0;
  $handler->display->display_options['fields']['label']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['label']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['label']['hide_empty'] = 0;
  $handler->display->display_options['fields']['label']['empty_zero'] = 0;
  $handler->display->display_options['fields']['label']['hide_alter_empty'] = 1;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'admin/reports/entityforms';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Entityform Submissions';
  $handler->display->display_options['menu']['description'] = 'View Submissions for all Entityforms';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $views[$view->name] = $view;

  $view = new view;
  $view->name = 'user_entityforms';
  $view->description = 'A list of all entityforms submissions to be displayed to the submitter.';
  $view->tag = 'entityforms';
  $view->base_table = 'entityform';
  $view->human_name = 'User Entityforms';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'List';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = 0;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = 1;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['expose']['items_per_page_options_all'] = 0;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
      'name' => 'name',
      'link_entityform' => 'link_entityform',
      'label_1' => 'label_1',
      'created' => 'created',
      'changed' => 'changed',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
      'name' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
      'link_entityform' => array(
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
      'label_1' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
      'created' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
      'changed' => array(
          'sortable' => 0,
          'default_sort_order' => 'asc',
          'align' => '',
          'separator' => '',
          'empty_column' => 0,
      ),
  );
  $handler->display->display_options['style_options']['override'] = 1;
  $handler->display->display_options['style_options']['sticky'] = 0;
  $handler->display->display_options['style_options']['empty_table'] = 0;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['label'] = 'Empty ';
  $handler->display->display_options['empty']['area']['empty'] = FALSE;
  $handler->display->display_options['empty']['area']['content'] = 'No form submissions available.';
  /* Relationship: Entityform: Uid */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'entityform';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = 0;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Submitter';
  $handler->display->display_options['fields']['name']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['name']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['name']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['name']['alter']['external'] = 0;
  $handler->display->display_options['fields']['name']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['name']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['name']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['name']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['name']['alter']['html'] = 0;
  $handler->display->display_options['fields']['name']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['name']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['name']['hide_empty'] = 0;
  $handler->display->display_options['fields']['name']['empty_zero'] = 0;
  $handler->display->display_options['fields']['name']['link_to_user'] = 1;
  $handler->display->display_options['fields']['name']['overwrite_anonymous'] = 0;
  /* Field: Entityform: Link */
  $handler->display->display_options['fields']['link_entityform']['id'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['link_entityform']['field'] = 'link_entityform';
  $handler->display->display_options['fields']['link_entityform']['label'] = 'View';
  $handler->display->display_options['fields']['link_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['link_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['link_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['link_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['link_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['link_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['link_entityform']['empty_zero'] = 0;
  /* Field: Entityform: Edit Link */
  $handler->display->display_options['fields']['edit_entityform']['id'] = 'edit_entityform';
  $handler->display->display_options['fields']['edit_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['edit_entityform']['field'] = 'edit_entityform';
  $handler->display->display_options['fields']['edit_entityform']['label'] = 'Edit';
  $handler->display->display_options['fields']['edit_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['edit_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['empty_zero'] = 0;
  $handler->display->display_options['fields']['edit_entityform']['hide_alter_empty'] = 1;
  /* Field: Entityform: Delete Link */
  $handler->display->display_options['fields']['delete_entityform']['id'] = 'delete_entityform';
  $handler->display->display_options['fields']['delete_entityform']['table'] = 'entityform';
  $handler->display->display_options['fields']['delete_entityform']['field'] = 'delete_entityform';
  $handler->display->display_options['fields']['delete_entityform']['label'] = 'Delete';
  $handler->display->display_options['fields']['delete_entityform']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['external'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['alter']['html'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['delete_entityform']['hide_empty'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['empty_zero'] = 0;
  $handler->display->display_options['fields']['delete_entityform']['hide_alter_empty'] = 0;
  /* Field: Entityform: Date submitted */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'entityform';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['created']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['created']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['created']['alter']['external'] = 0;
  $handler->display->display_options['fields']['created']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['created']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['created']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['created']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['created']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['created']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['created']['alter']['html'] = 0;
  $handler->display->display_options['fields']['created']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['created']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['created']['hide_empty'] = 0;
  $handler->display->display_options['fields']['created']['empty_zero'] = 0;
  $handler->display->display_options['fields']['created']['hide_alter_empty'] = 1;
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: Entityform: Date changed */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'entityform';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['alter']['alter_text'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['make_link'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['absolute'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['external'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['replace_spaces'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim_whitespace'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['nl2br'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['word_boundary'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['ellipsis'] = 1;
  $handler->display->display_options['fields']['changed']['alter']['strip_tags'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['trim'] = 0;
  $handler->display->display_options['fields']['changed']['alter']['html'] = 0;
  $handler->display->display_options['fields']['changed']['element_label_colon'] = 1;
  $handler->display->display_options['fields']['changed']['element_default_classes'] = 1;
  $handler->display->display_options['fields']['changed']['hide_empty'] = 0;
  $handler->display->display_options['fields']['changed']['empty_zero'] = 0;
  $handler->display->display_options['fields']['changed']['hide_alter_empty'] = 0;
  /* Sort criterion: Entityform: Date submitted */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'entityform';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Entityform: Entityform Type */
  $handler->display->display_options['arguments']['type']['id'] = 'type';
  $handler->display->display_options['arguments']['type']['table'] = 'entityform';
  $handler->display->display_options['arguments']['type']['field'] = 'type';
  $handler->display->display_options['arguments']['type']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['type']['title_enable'] = 1;
  $handler->display->display_options['arguments']['type']['title'] = 'Submissions for %1';
  $handler->display->display_options['arguments']['type']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['type']['default_argument_skip_url'] = 0;
  $handler->display->display_options['arguments']['type']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['type']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['type']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['type']['glossary'] = 0;
  $handler->display->display_options['arguments']['type']['limit'] = '0';
  $handler->display->display_options['arguments']['type']['transform_dash'] = 0;
  $handler->display->display_options['arguments']['type']['break_phrase'] = 0;
  /* Filter criterion: Entityform: Date submitted */
  $handler->display->display_options['filters']['created']['id'] = 'created';
  $handler->display->display_options['filters']['created']['table'] = 'entityform';
  $handler->display->display_options['filters']['created']['field'] = 'created';
  $handler->display->display_options['filters']['created']['operator'] = '>';
  $handler->display->display_options['filters']['created']['exposed'] = TRUE;
  $handler->display->display_options['filters']['created']['expose']['operator_id'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['label'] = 'Date submitted';
  $handler->display->display_options['filters']['created']['expose']['use_operator'] = 1;
  $handler->display->display_options['filters']['created']['expose']['operator'] = 'created_op';
  $handler->display->display_options['filters']['created']['expose']['identifier'] = 'created';
  $handler->display->display_options['filters']['created']['expose']['multiple'] = FALSE;
  /* Filter criterion: User: Current */
  $handler->display->display_options['filters']['uid_current']['id'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['table'] = 'users';
  $handler->display->display_options['filters']['uid_current']['field'] = 'uid_current';
  $handler->display->display_options['filters']['uid_current']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid_current']['value'] = '1';
  /* Filter criterion: Entityform: Draft */
  $handler->display->display_options['filters']['draft']['id'] = 'draft';
  $handler->display->display_options['filters']['draft']['table'] = 'entityform';
  $handler->display->display_options['filters']['draft']['field'] = 'draft';
  $handler->display->display_options['filters']['draft']['operator'] = '!=';
  $handler->display->display_options['filters']['draft']['value']['value'] = '1';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'entityforms_admin_page');
  $handler->display->display_options['display_description'] = 'Show the current user\'s submissions for a entityform type';
  $handler->display->display_options['path'] = 'entityform-user-submissions/submissions/%/list';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'List';
  $handler->display->display_options['menu']['description'] = 'View Submissions for all Entityforms';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Submissions';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'management';
  $views[$view->name] = $view;

  return $views;
}