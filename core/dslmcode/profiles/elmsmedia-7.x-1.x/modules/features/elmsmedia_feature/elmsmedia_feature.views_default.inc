<?php
/**
 * @file
 * elmsmedia_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function elmsmedia_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'elms_media_overview';
  $view->description = 'This is the searchable homepage of media';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'ELMS Media overview';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Media';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'create elmsmedia_image content';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
    ),
    'title' => array(
      'more_options' => array(
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
          ),
        ),
      ),
    ),
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'fluid_grid';
  $handler->display->display_options['style_options']['items_width'] = '250';
  $handler->display->display_options['style_options']['items_height'] = '250';
  $handler->display->display_options['style_options']['advanced_layout'] = array(
    'align' => TRUE,
    'margins' => TRUE,
    'css3' => TRUE,
  );
  $handler->display->display_options['style_options']['items_alignment'] = 'center';
  $handler->display->display_options['style_options']['items_h_margin'] = '0.2em';
  $handler->display->display_options['style_options']['items_v_margin'] = '0.2em';
  $handler->display->display_options['style_options']['box_shadow'] = '1';
  $handler->display->display_options['style_options']['border_radius'] = '1';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Poster */
  $handler->display->display_options['fields']['field_poster']['id'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['table'] = 'field_data_field_poster';
  $handler->display->display_options['fields']['field_poster']['field'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['label'] = '';
  $handler->display->display_options['fields']['field_poster']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_poster']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_poster']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_poster']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'content',
  );
  /* Field: Content: External media */
  $handler->display->display_options['fields']['field_external_media']['id'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['table'] = 'field_data_field_external_media';
  $handler->display->display_options['fields']['field_external_media']['field'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['label'] = '';
  $handler->display->display_options['fields']['field_external_media']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_external_media']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_external_media']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_external_media']['settings'] = array(
    'image_style' => 'medium',
    'image_link' => 'node',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_course']['id'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['table'] = 'field_data_field_course';
  $handler->display->display_options['fields']['field_course']['field'] = 'field_course';
  $handler->display->display_options['fields']['field_course']['label'] = '';
  $handler->display->display_options['fields']['field_course']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_course']['type'] = 'taxonomy_term_reference_plain';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content type groups: Content type group */
  $handler->display->display_options['filters']['group_type']['id'] = 'group_type';
  $handler->display->display_options['filters']['group_type']['table'] = 'content_type_groups_types';
  $handler->display->display_options['filters']['group_type']['field'] = 'group_type';
  $handler->display->display_options['filters']['group_type']['value'] = array(
    'elmsmedia_types' => 'elmsmedia_types',
  );
  $handler->display->display_options['filters']['group_type']['group'] = 1;
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
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
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['title']['expose']['autocomplete_filter'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_items'] = '10';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_field'] = 'title';
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_suggestion'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_raw_dropdown'] = 1;
  $handler->display->display_options['filters']['title']['expose']['autocomplete_dependent'] = 0;
  /* Filter criterion: Content: Course (field_course) */
  $handler->display->display_options['filters']['field_course_tid']['id'] = 'field_course_tid';
  $handler->display->display_options['filters']['field_course_tid']['table'] = 'field_data_field_course';
  $handler->display->display_options['filters']['field_course_tid']['field'] = 'field_course_tid';
  $handler->display->display_options['filters']['field_course_tid']['value'] = '';
  $handler->display->display_options['filters']['field_course_tid']['group'] = 1;
  $handler->display->display_options['filters']['field_course_tid']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_course_tid']['expose']['operator_id'] = 'field_course_tid_op';
  $handler->display->display_options['filters']['field_course_tid']['expose']['label'] = 'Course';
  $handler->display->display_options['filters']['field_course_tid']['expose']['operator'] = 'field_course_tid_op';
  $handler->display->display_options['filters']['field_course_tid']['expose']['identifier'] = 'field_course_tid';
  $handler->display->display_options['filters']['field_course_tid']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );
  $handler->display->display_options['filters']['field_course_tid']['vocabulary'] = 'elmsmedia_course';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
    4 => 0,
    5 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'media-overview';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Overview';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['elms_media_overview'] = $view;

  return $export;
}
