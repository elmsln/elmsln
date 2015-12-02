<?php
/**
 * @file
 * cle_submission.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cle_submission_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cle_my_submissions';
  $view->description = 'Listing of a user\'s submissions';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CLE my submissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'My Gallery';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_assignment' => 'field_assignment',
    'og_group_ref' => 'og_group_ref',
    'created' => 'created',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_assignment' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'og_group_ref' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
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
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['summary'] = 'All of my assignments';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Assignment */
  $handler->display->display_options['fields']['field_assignment']['id'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['fields']['field_assignment']['field'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  /* Field: Content: Section */
  $handler->display->display_options['fields']['og_group_ref']['id'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['table'] = 'og_membership';
  $handler->display->display_options['fields']['og_group_ref']['field'] = 'og_group_ref';
  $handler->display->display_options['fields']['og_group_ref']['settings'] = array(
    'link' => 1,
  );
  /* Sort criterion: Content: Order (field_cle_order) */
  $handler->display->display_options['sorts']['field_cle_order_value']['id'] = 'field_cle_order_value';
  $handler->display->display_options['sorts']['field_cle_order_value']['table'] = 'field_data_field_cle_order';
  $handler->display->display_options['sorts']['field_cle_order_value']['field'] = 'field_cle_order_value';
  $handler->display->display_options['sorts']['field_cle_order_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['sorts']['field_cle_order_value']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['field_cle_order_value']['expose']['label'] = 'Order of Assignments';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Date Created';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Assignment (field_assignment) */
  $handler->display->display_options['filters']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator_id'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['label'] = 'Assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['identifier'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    7 => 0,
    8 => 0,
    4 => 0,
    9 => 0,
    6 => 0,
    10 => 0,
  );
  /* Filter criterion: Content: Submission type (field_submission_type) */
  $handler->display->display_options['filters']['field_submission_type_value']['id'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['table'] = 'field_data_field_submission_type';
  $handler->display->display_options['filters']['field_submission_type_value']['field'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['operator_id'] = 'field_submission_type_value_op';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['operator'] = 'field_submission_type_value_op';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['identifier'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );

  /* Display: My Gallery (non-social) */
  $handler = $view->new_display('page', 'My Gallery (non-social)', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Gallery';
  $handler->display->display_options['display_description'] = 'Your gallery in the course';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: cle_exemplary */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cle_exemplary';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['label'] = 'Likes';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'vote',
    'function' => '',
  );
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache_1']['id'] = 'votingapi_cache_1';
  $handler->display->display_options['relationships']['votingapi_cache_1']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache_1']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache_1']['label'] = 'Emotion';
  $handler->display->display_options['relationships']['votingapi_cache_1']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'emotion',
    'function' => '',
  );
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Submitted';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Assignment */
  $handler->display->display_options['fields']['field_assignment']['id'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['fields']['field_assignment']['field'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Images (field_images:delta) */
  $handler->display->display_options['fields']['delta_1']['id'] = 'delta_1';
  $handler->display->display_options['fields']['delta_1']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['delta_1']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_1']['label'] = 'Images';
  /* Field: Content: Video (field_video:delta) */
  $handler->display->display_options['fields']['delta_3']['id'] = 'delta_3';
  $handler->display->display_options['fields']['delta_3']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['delta_3']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_3']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_3']['label'] = 'Videos';
  /* Field: Content: Files (field_files:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta']['label'] = 'Files';
  /* Field: Content: Links (field_links:delta) */
  $handler->display->display_options['fields']['delta_2']['id'] = 'delta_2';
  $handler->display->display_options['fields']['delta_2']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['delta_2']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_2']['label'] = 'Links';
  $handler->display->display_options['path'] = 'cle/my-gallery';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Gallery';
  $handler->display->display_options['menu']['description'] = 'All of my submissions for this course';
  $handler->display->display_options['menu']['weight'] = '9';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: My Overview */
  $handler = $view->new_display('page', 'My Overview', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Gallery';
  $handler->display->display_options['display_description'] = 'Submission listing overview data';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Submitted';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Assignment */
  $handler->display->display_options['fields']['field_assignment']['id'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['fields']['field_assignment']['field'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Files (field_files:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta']['label'] = 'Files';
  /* Field: Content: Images (field_images:delta) */
  $handler->display->display_options['fields']['delta_1']['id'] = 'delta_1';
  $handler->display->display_options['fields']['delta_1']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['delta_1']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_1']['label'] = 'Images';
  /* Field: Content: Links (field_links:delta) */
  $handler->display->display_options['fields']['delta_2']['id'] = 'delta_2';
  $handler->display->display_options['fields']['delta_2']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['delta_2']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_2']['label'] = 'Links';
  /* Field: Content: Video (field_video:delta) */
  $handler->display->display_options['fields']['delta_3']['id'] = 'delta_3';
  $handler->display->display_options['fields']['delta_3']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['delta_3']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_3']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_3']['label'] = 'Videos';
  $handler->display->display_options['path'] = 'cle/my-gallery/overview';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Overview';
  $handler->display->display_options['menu']['description'] = 'Overview of your submissions';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: My Images */
  $handler = $view->new_display('page', 'My Images', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Gallery';
  $handler->display->display_options['display_description'] = 'Visual gallery of all images';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'masonry_views_grid';
  $handler->display->display_options['style_options']['masonry_width'] = '300';
  $handler->display->display_options['style_options']['masonry_animated'] = TRUE;
  $handler->display->display_options['style_options']['masonry_resizable'] = TRUE;
  $handler->display->display_options['style_options']['masonry_center'] = FALSE;
  $handler->display->display_options['style_options']['masonry_rtl'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'colorbox_node_style' => '',
    'colorbox_node_style_first' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'page',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_images']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'cle/my-gallery/images';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Images';
  $handler->display->display_options['menu']['description'] = 'All my submissions as a gallery';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: My Video */
  $handler = $view->new_display('page', 'My Video', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Video';
  $handler->display->display_options['display_description'] = 'Visual gallery of all video';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'masonry_views_grid';
  $handler->display->display_options['style_options']['masonry_width'] = '350';
  $handler->display->display_options['style_options']['masonry_animated'] = TRUE;
  $handler->display->display_options['style_options']['masonry_resizable'] = TRUE;
  $handler->display->display_options['style_options']['masonry_center'] = TRUE;
  $handler->display->display_options['style_options']['masonry_gutter'] = '4';
  $handler->display->display_options['style_options']['masonry_rtl'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video']['id'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['field_video']['field'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['label'] = '';
  $handler->display->display_options['fields']['field_video']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_video']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_video']['settings'] = array(
    'video_style' => 'cle_masonry',
  );
  $handler->display->display_options['fields']['field_video']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_video']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'cle/my-gallery/video';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Video';
  $handler->display->display_options['menu']['description'] = 'All my videos as a gallery';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: My Files */
  $handler = $view->new_display('page', 'My Files', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Files';
  $handler->display->display_options['display_description'] = 'Visual gallery of all files';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'masonry_views_grid';
  $handler->display->display_options['style_options']['masonry_width'] = '350';
  $handler->display->display_options['style_options']['masonry_animated'] = TRUE;
  $handler->display->display_options['style_options']['masonry_resizable'] = TRUE;
  $handler->display->display_options['style_options']['masonry_center'] = TRUE;
  $handler->display->display_options['style_options']['masonry_gutter'] = '4';
  $handler->display->display_options['style_options']['masonry_rtl'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Files */
  $handler->display->display_options['fields']['field_files']['id'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['field_files']['field'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['label'] = '';
  $handler->display->display_options['fields']['field_files']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_files']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_files']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'cle/my-gallery/files';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Files';
  $handler->display->display_options['menu']['description'] = 'All my files as a gallery';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: My Links */
  $handler = $view->new_display('page', 'My Links', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Links';
  $handler->display->display_options['display_description'] = 'Visual gallery of all links';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'infinite_scroll';
  $handler->display->display_options['pager']['options']['items_per_page'] = '6';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'masonry_views_grid';
  $handler->display->display_options['style_options']['masonry_width'] = '350';
  $handler->display->display_options['style_options']['masonry_animated'] = TRUE;
  $handler->display->display_options['style_options']['masonry_resizable'] = TRUE;
  $handler->display->display_options['style_options']['masonry_center'] = TRUE;
  $handler->display->display_options['style_options']['masonry_gutter'] = '4';
  $handler->display->display_options['style_options']['masonry_rtl'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['label'] = '';
  $handler->display->display_options['fields']['field_links']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['group_rows'] = FALSE;
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'cle/my-gallery/links';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Links';
  $handler->display->display_options['menu']['description'] = 'All my links as a gallery';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: My Gallery (social) */
  $handler = $view->new_display('page', 'My Gallery (social)', 'page_6');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Gallery';
  $handler->display->display_options['enabled'] = FALSE;
  $handler->display->display_options['display_description'] = 'Your gallery in the course';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Flags: cle_exemplary */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cle_exemplary';
  $handler->display->display_options['relationships']['flag_content_rel']['user_scope'] = 'any';
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['label'] = 'Likes';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'vote',
    'function' => '',
  );
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache_1']['id'] = 'votingapi_cache_1';
  $handler->display->display_options['relationships']['votingapi_cache_1']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache_1']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache_1']['label'] = 'Emotion';
  $handler->display->display_options['relationships']['votingapi_cache_1']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'emotion',
    'function' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Submitted';
  $handler->display->display_options['fields']['created']['date_format'] = 'long';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Assignment */
  $handler->display->display_options['fields']['field_assignment']['id'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['fields']['field_assignment']['field'] = 'field_assignment';
  $handler->display->display_options['fields']['field_assignment']['settings'] = array(
    'link' => 1,
  );
  /* Field: Content: Images (field_images:delta) */
  $handler->display->display_options['fields']['delta_1']['id'] = 'delta_1';
  $handler->display->display_options['fields']['delta_1']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['delta_1']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_1']['label'] = 'Images';
  /* Field: Content: Video (field_video:delta) */
  $handler->display->display_options['fields']['delta_3']['id'] = 'delta_3';
  $handler->display->display_options['fields']['delta_3']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['delta_3']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_3']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_3']['label'] = 'Videos';
  /* Field: Content: Files (field_files:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta']['label'] = 'Files';
  /* Field: Content: Links (field_links:delta) */
  $handler->display->display_options['fields']['delta_2']['id'] = 'delta_2';
  $handler->display->display_options['fields']['delta_2']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['delta_2']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_2']['label'] = 'Links';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Comments';
  /* Field: Vote results: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['appearance'] = 'rate_views_widget_disabled';
  /* Field: Vote results: Value */
  $handler->display->display_options['fields']['value_1']['id'] = 'value_1';
  $handler->display->display_options['fields']['value_1']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value_1']['field'] = 'value';
  $handler->display->display_options['fields']['value_1']['relationship'] = 'votingapi_cache_1';
  $handler->display->display_options['fields']['value_1']['label'] = 'Emotion';
  $handler->display->display_options['fields']['value_1']['precision'] = '0';
  $handler->display->display_options['fields']['value_1']['appearance'] = 'rate_views_widget_compact';
  $handler->display->display_options['path'] = 'cle/my-gallery';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Gallery';
  $handler->display->display_options['menu']['description'] = 'All of my submissions for this course';
  $handler->display->display_options['menu']['weight'] = '9';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['cle_my_submissions'] = $view;

  $view = new view();
  $view->name = 'cle_submission';
  $view->description = 'Blocks for media positioning';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CLE submission';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'colorbox_node_style' => 'cle_submission',
    'colorbox_image_style' => 'large',
    'colorbox_gallery' => 'field_post',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['nid']['validate_options']['types'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $export['cle_submission'] = $view;

  $view = new view();
  $view->name = 'cle_submissions';
  $view->description = 'Student submissions';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Submissions';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Open Studio';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '';
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '250';
  $handler->display->display_options['style_options']['items_height'] = '250';
  $handler->display->display_options['style_options']['advanced_layout'] = array(
    'align' => TRUE,
    'margins' => TRUE,
    'css3' => TRUE,
  );
  $handler->display->display_options['style_options']['list_alignment'] = 'center';
  $handler->display->display_options['style_options']['items_alignment'] = 'center';
  $handler->display->display_options['style_options']['items_h_margin'] = '0.2em';
  $handler->display->display_options['style_options']['items_v_margin'] = '0.2em';
  $handler->display->display_options['style_options']['box_shadow'] = '1';
  $handler->display->display_options['style_options']['border_radius'] = '1';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'Artist';
  $handler->display->display_options['fields']['name']['exclude'] = TRUE;
  /* Field: Content: Link */
  $handler->display->display_options['fields']['view_node']['id'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['view_node']['field'] = 'view_node';
  $handler->display->display_options['fields']['view_node']['label'] = 'Action';
  $handler->display->display_options['fields']['view_node']['text'] = 'Comment / Critique';
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['alter']['path'] = 'node/[nid]';
  $handler->display->display_options['fields']['field_images']['element_class'] = 'cle-image';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'colorbox_node_style' => 'cle_square',
    'colorbox_node_style_first' => '',
    'colorbox_image_style' => 'cle_submission',
    'colorbox_gallery' => 'page',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'node_title',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_images']['delta_limit'] = '1';
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Assignment (field_assignment) */
  $handler->display->display_options['filters']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator_id'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['label'] = 'Assignment';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['operator'] = 'field_assignment_target_id_op';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['identifier'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_assignment_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );
  /* Filter criterion: Content: Submission type (field_submission_type) */
  $handler->display->display_options['filters']['field_submission_type_value']['id'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['table'] = 'field_data_field_submission_type';
  $handler->display->display_options['filters']['field_submission_type_value']['field'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_submission_type_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['operator_id'] = 'field_submission_type_value_op';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['operator'] = 'field_submission_type_value_op';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['identifier'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Artist';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    6065076 => 0,
    135574917 => 0,
    66784200 => 0,
    67296478 => 0,
    75987638 => 0,
    166149871 => 0,
    30037204 => 0,
    76550217 => 0,
  );

  /* Display: Open Studio */
  $handler = $view->new_display('page', 'Open Studio', 'page');
  $handler->display->display_options['display_description'] = 'Section specific submissions';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'cle';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Open Studio';
  $handler->display->display_options['menu']['description'] = 'Listing of all Open Submissions';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cle_submissions'] = $view;

  $view = new view();
  $view->name = 'cle_submissions_listing';
  $view->description = 'Submissions listing for an assignment';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Submissions listing';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Media';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    75987638 => 75987638,
    166149871 => 166149871,
    67296478 => 67296478,
    30037204 => 30037204,
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'created' => 'created',
    'name' => 'name',
    'title' => 'title',
    'comment_count' => 'comment_count',
    'delta' => 'delta',
    'delta_1' => 'delta_1',
    'delta_2' => 'delta_2',
    'delta_3' => 'delta_3',
    'field_due_date' => 'field_due_date',
    'field_media_requirements' => 'field_media_requirements',
    'value' => 'value',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'created' => array(
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
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'comment_count' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta_1' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta_2' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delta_3' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_due_date' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_media_requirements' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'value' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  $handler->display->display_options['style_options']['summary'] = 'A list of all submissions for this assignment';
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['label'] = 'Assignment';
  $handler->display->display_options['header']['area']['empty'] = TRUE;
  $handler->display->display_options['header']['area']['content'] = '<h3>%1 Submissions</h3>';
  $handler->display->display_options['header']['area']['format'] = 'textbook_editor';
  $handler->display->display_options['header']['area']['tokenize'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['area']['id'] = 'area';
  $handler->display->display_options['empty']['area']['table'] = 'views';
  $handler->display->display_options['empty']['area']['field'] = 'area';
  $handler->display->display_options['empty']['area']['empty'] = TRUE;
  $handler->display->display_options['empty']['area']['content'] = 'There are no submissions for this assignment yet.';
  $handler->display->display_options['empty']['area']['format'] = 'textbook_editor';
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Relationship: Flags: cle_exemplary */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cle_exemplary';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Comments';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video']['id'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['field_video']['field'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['group_type'] = 'count';
  $handler->display->display_options['fields']['field_video']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_video']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_video']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_video']['group_column'] = 'video_url';
  $handler->display->display_options['fields']['field_video']['delta_offset'] = '0';
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['group_type'] = 'count';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_images']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_images']['group_columns'] = array(
    'fid' => 'fid',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Field: Content: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['group_type'] = 'count';
  $handler->display->display_options['fields']['field_links']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_links']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['group_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'text';
  $handler->display->display_options['fields']['body']['type'] = 'text_trimmed';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '50',
  );
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = 'Mark exemplary';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Assignment (field_assignment) */
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['id'] = 'field_assignment_target_id_1';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['validate_options']['types'] = array(
    'cle_assignment' => 'cle_assignment',
  );
  $handler->display->display_options['arguments']['field_assignment_target_id_1']['validate_options']['access'] = TRUE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: User: Name */
  $handler->display->display_options['filters']['uid']['id'] = 'uid';
  $handler->display->display_options['filters']['uid']['table'] = 'users';
  $handler->display->display_options['filters']['uid']['field'] = 'uid';
  $handler->display->display_options['filters']['uid']['relationship'] = 'uid';
  $handler->display->display_options['filters']['uid']['value'] = '';
  $handler->display->display_options['filters']['uid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['uid']['expose']['operator_id'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['expose']['operator'] = 'uid_op';
  $handler->display->display_options['filters']['uid']['expose']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    7 => 0,
    8 => 0,
    4 => 0,
    9 => 0,
    6 => 0,
    10 => 0,
  );
  $handler->display->display_options['filters']['uid']['group_info']['label'] = 'Name';
  $handler->display->display_options['filters']['uid']['group_info']['identifier'] = 'uid';
  $handler->display->display_options['filters']['uid']['group_info']['remember'] = FALSE;
  $handler->display->display_options['filters']['uid']['group_info']['group_items'] = array(
    1 => array(),
    2 => array(),
    3 => array(),
  );
  /* Filter criterion: Content: Comment count */
  $handler->display->display_options['filters']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['filters']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['filters']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['filters']['comment_count']['exposed'] = TRUE;
  $handler->display->display_options['filters']['comment_count']['expose']['operator_id'] = 'comment_count_op';
  $handler->display->display_options['filters']['comment_count']['expose']['label'] = 'Comments';
  $handler->display->display_options['filters']['comment_count']['expose']['use_operator'] = TRUE;
  $handler->display->display_options['filters']['comment_count']['expose']['operator_label'] = 'Modifier';
  $handler->display->display_options['filters']['comment_count']['expose']['operator'] = 'comment_count_op';
  $handler->display->display_options['filters']['comment_count']['expose']['identifier'] = 'comment_count';
  $handler->display->display_options['filters']['comment_count']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    5 => 0,
    3 => 0,
    7 => 0,
    8 => 0,
    4 => 0,
    9 => 0,
    6 => 0,
    10 => 0,
  );

  /* Display: Submission Overview */
  $handler = $view->new_display('page', 'Submission Overview', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Overview';
  $handler->display->display_options['display_description'] = 'High level';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Files (field_files:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta']['label'] = 'Files';
  /* Field: Content: Images (field_images:delta) */
  $handler->display->display_options['fields']['delta_1']['id'] = 'delta_1';
  $handler->display->display_options['fields']['delta_1']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['delta_1']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_1']['label'] = 'Images';
  /* Field: Content: Links (field_links:delta) */
  $handler->display->display_options['fields']['delta_2']['id'] = 'delta_2';
  $handler->display->display_options['fields']['delta_2']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['delta_2']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_2']['label'] = 'Links';
  /* Field: Content: Video (field_video:delta) */
  $handler->display->display_options['fields']['delta_3']['id'] = 'delta_3';
  $handler->display->display_options['fields']['delta_3']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['delta_3']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_3']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_3']['label'] = 'Videos';
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_due_date']['group_column'] = 'entity_id';
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'node/%/submissions';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Submissions';
  $handler->display->display_options['menu']['description'] = 'Listing of Submissions for this assignment';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Submissions';
  $handler->display->display_options['tab_options']['description'] = 'Listing of submissions for this assignemnt';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Submission Overview */
  $handler = $view->new_display('page', 'Submission Overview', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Overview';
  $handler->display->display_options['display_description'] = 'High level';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Relationship: Flags: cle_exemplary */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cle_exemplary';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Comments';
  /* Field: Content: Files (field_files:delta) */
  $handler->display->display_options['fields']['delta']['id'] = 'delta';
  $handler->display->display_options['fields']['delta']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['delta']['field'] = 'delta';
  $handler->display->display_options['fields']['delta']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta']['label'] = 'Files';
  /* Field: Content: Images (field_images:delta) */
  $handler->display->display_options['fields']['delta_1']['id'] = 'delta_1';
  $handler->display->display_options['fields']['delta_1']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['delta_1']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_1']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_1']['label'] = 'Images';
  /* Field: Content: Links (field_links:delta) */
  $handler->display->display_options['fields']['delta_2']['id'] = 'delta_2';
  $handler->display->display_options['fields']['delta_2']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['delta_2']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_2']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_2']['label'] = 'Links';
  /* Field: Content: Video (field_video:delta) */
  $handler->display->display_options['fields']['delta_3']['id'] = 'delta_3';
  $handler->display->display_options['fields']['delta_3']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['delta_3']['field'] = 'delta';
  $handler->display->display_options['fields']['delta_3']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['delta_3']['label'] = 'Videos';
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_due_date']['group_column'] = 'entity_id';
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'node/%/submissions/overview';
  $handler->display->display_options['menu']['type'] = 'default tab';
  $handler->display->display_options['menu']['title'] = 'Overview';
  $handler->display->display_options['menu']['description'] = 'Listing of Submissions for this assignment';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Submissions';
  $handler->display->display_options['tab_options']['description'] = 'Listing of submissions for this assignemnt';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Submission Media */
  $handler = $view->new_display('page', 'Submission Media', 'page_1');
  $handler->display->display_options['display_description'] = 'Media displayed';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Video */
  $handler->display->display_options['fields']['field_video']['id'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['table'] = 'field_data_field_video';
  $handler->display->display_options['fields']['field_video']['field'] = 'field_video';
  $handler->display->display_options['fields']['field_video']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_video']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_video']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_video']['delta_offset'] = '0';
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'image_style' => 'thumbnail',
    'image_link' => '',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Field: Content: Files */
  $handler->display->display_options['fields']['field_files']['id'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['table'] = 'field_data_field_files';
  $handler->display->display_options['fields']['field_files']['field'] = 'field_files';
  $handler->display->display_options['fields']['field_files']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_files']['delta_offset'] = '0';
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  $handler->display->display_options['fields']['created']['second_date_format'] = 'long';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Last updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  $handler->display->display_options['path'] = 'node/%/submissions/media';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Media';
  $handler->display->display_options['menu']['description'] = 'Submission list by media';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Writing */
  $handler = $view->new_display('page', 'Writing', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Writing';
  $handler->display->display_options['display_description'] = 'Textual submission parts';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Links */
  $handler->display->display_options['fields']['field_links']['id'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['table'] = 'field_data_field_links';
  $handler->display->display_options['fields']['field_links']['field'] = 'field_links';
  $handler->display->display_options['fields']['field_links']['group_type'] = 'count';
  $handler->display->display_options['fields']['field_links']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_links']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_links']['click_sort_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['group_column'] = 'url';
  $handler->display->display_options['fields']['field_links']['delta_offset'] = '0';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = 'text';
  $handler->display->display_options['fields']['body']['settings'] = array(
    'trim_length' => '50',
  );
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'node/%/submissions/writing';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Writing';
  $handler->display->display_options['menu']['description'] = 'List of submission writing';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Social */
  $handler = $view->new_display('page', 'Social', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Social';
  $handler->display->display_options['display_description'] = 'High level';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['query'] = FALSE;
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Relationship: Flags: cle_exemplary */
  $handler->display->display_options['relationships']['flag_content_rel']['id'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['table'] = 'node';
  $handler->display->display_options['relationships']['flag_content_rel']['field'] = 'flag_content_rel';
  $handler->display->display_options['relationships']['flag_content_rel']['required'] = 0;
  $handler->display->display_options['relationships']['flag_content_rel']['flag'] = 'cle_exemplary';
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache']['id'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache']['label'] = 'Like';
  $handler->display->display_options['relationships']['votingapi_cache']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'vote',
    'function' => '',
  );
  /* Relationship: Content: Vote results */
  $handler->display->display_options['relationships']['votingapi_cache_1']['id'] = 'votingapi_cache_1';
  $handler->display->display_options['relationships']['votingapi_cache_1']['table'] = 'node';
  $handler->display->display_options['relationships']['votingapi_cache_1']['field'] = 'votingapi_cache';
  $handler->display->display_options['relationships']['votingapi_cache_1']['label'] = 'Emotion';
  $handler->display->display_options['relationships']['votingapi_cache_1']['votingapi'] = array(
    'value_type' => '',
    'tag' => 'emotion',
    'function' => '',
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['date_format'] = 'medium';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['relationship'] = 'uid';
  $handler->display->display_options['fields']['name']['label'] = 'User';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: Comment count */
  $handler->display->display_options['fields']['comment_count']['id'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['table'] = 'node_comment_statistics';
  $handler->display->display_options['fields']['comment_count']['field'] = 'comment_count';
  $handler->display->display_options['fields']['comment_count']['label'] = 'Comments';
  /* Field: Content: Due Date */
  $handler->display->display_options['fields']['field_due_date']['id'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['table'] = 'field_data_field_due_date';
  $handler->display->display_options['fields']['field_due_date']['field'] = 'field_due_date';
  $handler->display->display_options['fields']['field_due_date']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_due_date']['label'] = '';
  $handler->display->display_options['fields']['field_due_date']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_due_date']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_due_date']['settings'] = array(
    'format_type' => 'medium',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['fields']['field_due_date']['group_column'] = 'entity_id';
  /* Field: Content: Media Requirements */
  $handler->display->display_options['fields']['field_media_requirements']['id'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['table'] = 'field_data_field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['field'] = 'field_media_requirements';
  $handler->display->display_options['fields']['field_media_requirements']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['fields']['field_media_requirements']['label'] = '';
  $handler->display->display_options['fields']['field_media_requirements']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_media_requirements']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_media_requirements']['group_column'] = 'entity_id';
  $handler->display->display_options['fields']['field_media_requirements']['delta_offset'] = '0';
  /* Field: Vote results: Value */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['relationship'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value']['label'] = 'Likes';
  $handler->display->display_options['fields']['value']['precision'] = '0';
  $handler->display->display_options['fields']['value']['appearance'] = 'rate_views_widget';
  /* Field: Vote results: Value */
  $handler->display->display_options['fields']['value_1']['id'] = 'value_1';
  $handler->display->display_options['fields']['value_1']['table'] = 'votingapi_cache';
  $handler->display->display_options['fields']['value_1']['field'] = 'value';
  $handler->display->display_options['fields']['value_1']['relationship'] = 'votingapi_cache_1';
  $handler->display->display_options['fields']['value_1']['label'] = 'Emotions';
  $handler->display->display_options['fields']['value_1']['precision'] = '0';
  $handler->display->display_options['fields']['value_1']['appearance'] = 'rate_views_widget';
  /* Field: Flags: Flag link */
  $handler->display->display_options['fields']['ops']['id'] = 'ops';
  $handler->display->display_options['fields']['ops']['table'] = 'flag_content';
  $handler->display->display_options['fields']['ops']['field'] = 'ops';
  $handler->display->display_options['fields']['ops']['relationship'] = 'flag_content_rel';
  $handler->display->display_options['fields']['ops']['label'] = 'Mark exemplary';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  $handler->display->display_options['path'] = 'node/%/submissions/social';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Social';
  $handler->display->display_options['menu']['description'] = 'What everyone thinks about this';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Submissions';
  $handler->display->display_options['tab_options']['description'] = 'Listing of submissions for this assignemnt';
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Viewer */
  $handler = $view->new_display('page', 'Viewer', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Viewer';
  $handler->display->display_options['display_description'] = 'A Viewer that lets you see one submission at at time and page through';
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'lite';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/submissions/viewer';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Viewer';
  $handler->display->display_options['menu']['description'] = 'Viewer mode for submissions';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cle_submissions_listing'] = $view;

  $view = new view();
  $view->name = 'sketch_book';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Sketch book';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Open Studio';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'masonry_views_grid';
  $handler->display->display_options['style_options']['masonry_animated'] = TRUE;
  $handler->display->display_options['style_options']['masonry_resizable'] = TRUE;
  $handler->display->display_options['style_options']['masonry_center'] = FALSE;
  $handler->display->display_options['style_options']['masonry_rtl'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_assignment_target_id']['id'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['table'] = 'field_data_field_assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['field'] = 'field_assignment_target_id';
  $handler->display->display_options['relationships']['field_assignment_target_id']['label'] = 'Assignment';
  $handler->display->display_options['relationships']['field_assignment_target_id']['required'] = TRUE;
  /* Relationship: Content: Author */
  $handler->display->display_options['relationships']['uid']['id'] = 'uid';
  $handler->display->display_options['relationships']['uid']['table'] = 'node';
  $handler->display->display_options['relationships']['uid']['field'] = 'uid';
  $handler->display->display_options['relationships']['uid']['required'] = TRUE;
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_images']['type'] = 'colorbox';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'colorbox_node_style' => 'cle_submission',
    'colorbox_node_style_first' => '',
    'colorbox_image_style' => '',
    'colorbox_gallery' => 'page',
    'colorbox_gallery_custom' => '',
    'colorbox_caption' => 'auto',
    'colorbox_caption_custom' => '',
  );
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Contextual filter: Content: Author uid */
  $handler->display->display_options['arguments']['uid']['id'] = 'uid';
  $handler->display->display_options['arguments']['uid']['table'] = 'node';
  $handler->display->display_options['arguments']['uid']['field'] = 'uid';
  $handler->display->display_options['arguments']['uid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['uid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Submission type (field_submission_type) */
  $handler->display->display_options['filters']['field_submission_type_value']['id'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['table'] = 'field_data_field_submission_type';
  $handler->display->display_options['filters']['field_submission_type_value']['field'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_submission_type_value']['value'] = array(
    'exercise' => 'exercise',
  );

  /* Display: Sketch Book */
  $handler = $view->new_display('page', 'Sketch Book', 'page');
  $handler->display->display_options['path'] = 'cle/sketch-book';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Sketch Book';
  $handler->display->display_options['menu']['weight'] = '8';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Draft pages */
  $handler = $view->new_display('page', 'Draft pages', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Draft Pages';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Submission type (field_submission_type) */
  $handler->display->display_options['filters']['field_submission_type_value']['id'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['table'] = 'field_data_field_submission_type';
  $handler->display->display_options['filters']['field_submission_type_value']['field'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_submission_type_value']['value'] = array(
    'draft' => 'draft',
  );
  $handler->display->display_options['path'] = 'cle/draft-pages';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Draft Pages';
  $handler->display->display_options['menu']['description'] = 'A visual showcase of all your submitted draft pages';
  $handler->display->display_options['menu']['weight'] = '9';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Final Pages */
  $handler = $view->new_display('page', 'Final Pages', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'My Final pages';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cle_submission' => 'cle_submission',
  );
  /* Filter criterion: Content: Submission type (field_submission_type) */
  $handler->display->display_options['filters']['field_submission_type_value']['id'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['table'] = 'field_data_field_submission_type';
  $handler->display->display_options['filters']['field_submission_type_value']['field'] = 'field_submission_type_value';
  $handler->display->display_options['filters']['field_submission_type_value']['relationship'] = 'field_assignment_target_id';
  $handler->display->display_options['filters']['field_submission_type_value']['value'] = array(
    'final' => 'final',
  );
  $handler->display->display_options['path'] = 'cle/final-pages';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'My Final Pages';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'menu-cle-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['sketch_book'] = $view;

  return $export;
}
