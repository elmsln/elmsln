<?php
/**
 * @file
 * views_timelinejs_feature.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function views_timelinejs_feature_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'timeline';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Timeline';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Timeline';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'timelinejs';
  $handler->display->display_options['style_options']['timeline_fields'] = array(
    'headline' => 'title',
    'bodytext' => 'body',
    'date' => 'field_timeline_dates',
    'tag' => '0',
    'media' => 'field_timeline_media_image',
    'credit' => 'field_timeline_credit_text',
    'caption' => 'field_timeline_caption_text',
  );
  $handler->display->display_options['style_options']['timeline_config'] = array(
    'link_to_entity' => 0,
    'link_text_enabled' => 0,
    'link_text' => 'Read more',
    'hash_bookmark' => '0',
    'start_at_end' => '0',
  );
  /* Field: Content: Body */
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

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'timeline';
  $export['timeline'] = $view;

  return $export;
}
