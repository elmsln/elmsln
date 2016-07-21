<?php
/**
 * @file
 * views_timelinejs_extras.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function views_timelinejs_extras_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'timeline_content_type';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Timeline Content type';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Timeline';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'time';
  $handler->display->display_options['cache']['results_lifespan'] = '1800';
  $handler->display->display_options['cache']['results_lifespan_custom'] = '0';
  $handler->display->display_options['cache']['output_lifespan'] = '1800';
  $handler->display->display_options['cache']['output_lifespan_custom'] = '0';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_theme'] = array(
    'width' => '100%',
    'width_unit' => '1',
    'height' => '400',
    'height_unit' => '0',
  );
  $handler->display->display_options['style_options']['timeline_fields'] = array(
    'headline' => 'title',
    'bodytext' => 'body',
    'date' => 'field_timeline_dates',
    'media' => 'field_timeline_media_image',
    'credit' => 'field_timeline_credit_text',
    'caption' => 'field_timeline_caption_text',
    'tag' => '0',
  );
  $handler->display->display_options['style_options']['timeline_config'] = array(
    'link_to_entity' => 0,
    'link_text_enabled' => 0,
    'link_text' => 'Read more',
    'hash_bookmark' => '1',
    'start_at_end' => '0',
    'start_zoom_adjust' => '0',
  );
  /* Field: Content: Text */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  /* Field: Content: Caption Text */
  $handler->display->display_options['fields']['field_timeline_caption_text']['id'] = 'field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['table'] = 'field_data_field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['field'] = 'field_timeline_caption_text';
  /* Field: Content: Credit Text */
  $handler->display->display_options['fields']['field_timeline_credit_text']['id'] = 'field_timeline_credit_text';
  $handler->display->display_options['fields']['field_timeline_credit_text']['table'] = 'field_data_field_timeline_credit_text';
  $handler->display->display_options['fields']['field_timeline_credit_text']['field'] = 'field_timeline_credit_text';
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_timeline_dates']['id'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['table'] = 'field_data_field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['field'] = 'field_timeline_dates';
  /* Field: Content: Media Image */
  $handler->display->display_options['fields']['field_timeline_media_image']['id'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['table'] = 'field_data_field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['field'] = 'field_timeline_media_image';
  /* Field: Content: Media Link */
  $handler->display->display_options['fields']['field_timeline_media_link']['id'] = 'field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['table'] = 'field_data_field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['field'] = 'field_timeline_media_link';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
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
    'timeline_date' => 'timeline_date',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';

  /* Display: Dynamic Select */
  $handler = $view->new_display('dynamic_select', 'Dynamic Select', 'dynamic_select_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'dynamic_select_style';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'dynamic_select_fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_timeline_dates']['id'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['table'] = 'field_data_field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['field'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['label'] = '';
  $handler->display->display_options['fields']['field_timeline_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_timeline_dates']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  $handler->display->display_options['defaults']['arguments'] = FALSE;

  /* Display: EVA Field */
  $handler = $view->new_display('entity_view', 'EVA Field', 'entity_view_1');
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_time_points_target_id']['id'] = 'field_time_points_target_id';
  $handler->display->display_options['relationships']['field_time_points_target_id']['table'] = 'field_data_field_time_points';
  $handler->display->display_options['relationships']['field_time_points_target_id']['field'] = 'field_time_points_target_id';
  $handler->display->display_options['relationships']['field_time_points_target_id']['label'] = 'Timeline Date';
  $handler->display->display_options['relationships']['field_time_points_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Dates */
  $handler->display->display_options['fields']['field_timeline_dates']['id'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['table'] = 'field_data_field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['field'] = 'field_timeline_dates';
  $handler->display->display_options['fields']['field_timeline_dates']['relationship'] = 'field_time_points_target_id';
  $handler->display->display_options['fields']['field_timeline_dates']['label'] = '';
  $handler->display->display_options['fields']['field_timeline_dates']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_timeline_dates']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_timeline_dates']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Text */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['relationship'] = 'field_time_points_target_id';
  /* Field: Content: Caption Text */
  $handler->display->display_options['fields']['field_timeline_caption_text']['id'] = 'field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['table'] = 'field_data_field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['field'] = 'field_timeline_caption_text';
  $handler->display->display_options['fields']['field_timeline_caption_text']['relationship'] = 'field_time_points_target_id';
  /* Field: Content: Credit Text */
  $handler->display->display_options['fields']['field_timeline_credit_text']['id'] = 'field_timeline_credit_text';
  $handler->display->display_options['fields']['field_timeline_credit_text']['table'] = 'field_data_field_timeline_credit_text';
  $handler->display->display_options['fields']['field_timeline_credit_text']['field'] = 'field_timeline_credit_text';
  $handler->display->display_options['fields']['field_timeline_credit_text']['relationship'] = 'field_time_points_target_id';
  /* Field: Content: Media Image */
  $handler->display->display_options['fields']['field_timeline_media_image']['id'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['table'] = 'field_data_field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['field'] = 'field_timeline_media_image';
  $handler->display->display_options['fields']['field_timeline_media_image']['relationship'] = 'field_time_points_target_id';
  $handler->display->display_options['fields']['field_timeline_media_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_timeline_media_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Field: Content: Media Link */
  $handler->display->display_options['fields']['field_timeline_media_link']['id'] = 'field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['table'] = 'field_data_field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['field'] = 'field_timeline_media_link';
  $handler->display->display_options['fields']['field_timeline_media_link']['relationship'] = 'field_time_points_target_id';
  $handler->display->display_options['fields']['field_timeline_media_link']['click_sort_column'] = 'url';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'field_time_points_target_id';
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
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
    'timeline' => 'timeline',
  );
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'timeline',
  );
  $export['timeline_content_type'] = $view;

  return $export;
}
