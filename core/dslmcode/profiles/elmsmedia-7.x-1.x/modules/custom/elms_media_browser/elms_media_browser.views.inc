<?php

/**
 * Implements hook_views_data().
 */
function elms_media_browser_views_data() {
  $data['file_managed']['image'] = array(
    'title' => 'File as image',
    'help' => 'Render this file as an image. Make sure it actually is.',
    'real field' => 'uri',
    'field' => array(
      'real field' => 'uri',
      'handler' => 'elms_media_browser_views_handler_field_image',
    ),
  );

  return $data;
}
/**
 * Implements hook_views_default_views().
 */
function elms_media_browser_views_default_views() {

  $view = new view();
  $view->name = 'image_library';
  $view->description = '';
  $view->tag = 'elms_media_browser';
  $view->base_table = 'xml';
  $view->human_name = 'Image Library';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  
  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Image Library';
  $handler->display->display_options['css_class'] = 'elms-media-browser';
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['xml_file'] = 'sites/all/modules/custom/elms_media_browser/example.xml';
  $handler->display->display_options['query']['options']['row_xpath'] = 'node';
  $handler->display->display_options['query']['options']['show_errors'] = 1;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit_hide'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '20';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: url */
  $handler->display->display_options['fields']['text_1']['id'] = 'text_1';
  $handler->display->display_options['fields']['text_1']['table'] = 'xml';
  $handler->display->display_options['fields']['text_1']['field'] = 'text';
  $handler->display->display_options['fields']['text_1']['ui_name'] = 'url';
  $handler->display->display_options['fields']['text_1']['label'] = '';
  $handler->display->display_options['fields']['text_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['text_1']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['text_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_1']['xpath_selector'] = 'image-orig/img/@src';
  $handler->display->display_options['fields']['text_1']['multiple'] = 0;
  /* Field: thumb */
  $handler->display->display_options['fields']['text']['id'] = 'text';
  $handler->display->display_options['fields']['text']['table'] = 'xml';
  $handler->display->display_options['fields']['text']['field'] = 'text';
  $handler->display->display_options['fields']['text']['ui_name'] = 'thumb';
  $handler->display->display_options['fields']['text']['label'] = '';
  $handler->display->display_options['fields']['text']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['text']['alter']['text'] = '<img src="[text]"/>';
  $handler->display->display_options['fields']['text']['alter']['path'] = '[text_1]';
  $handler->display->display_options['fields']['text']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text']['xpath_selector'] = 'image/img/@src';
  $handler->display->display_options['fields']['text']['multiple'] = 0;
  /* Field: tags */
  $handler->display->display_options['fields']['text_2']['id'] = 'text_2';
  $handler->display->display_options['fields']['text_2']['table'] = 'xml';
  $handler->display->display_options['fields']['text_2']['field'] = 'text';
  $handler->display->display_options['fields']['text_2']['ui_name'] = 'tags';
  $handler->display->display_options['fields']['text_2']['label'] = '';
  $handler->display->display_options['fields']['text_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['text_2']['xpath_selector'] = 'tags';
  $handler->display->display_options['fields']['text_2']['multiple'] = 0;
  /* Filter criterion: tags: Text */
  $handler->display->display_options['filters']['text']['id'] = 'text';
  $handler->display->display_options['filters']['text']['table'] = 'xml';
  $handler->display->display_options['filters']['text']['field'] = 'text';
  $handler->display->display_options['filters']['text']['exposed'] = TRUE;
  $handler->display->display_options['filters']['text']['expose']['operator_id'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['label'] = 'Tags';
  $handler->display->display_options['filters']['text']['expose']['operator'] = 'text_op';
  $handler->display->display_options['filters']['text']['expose']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['text']['is_grouped'] = TRUE;
  $handler->display->display_options['filters']['text']['group_info']['label'] = 'Tags';
  $handler->display->display_options['filters']['text']['group_info']['identifier'] = 'text';
  $handler->display->display_options['filters']['text']['group_info']['group_items'] = array(
    1 => array(
      'title' => 'Elms',
      'operator' => '=',
      'value' => 'elms',
    ),
    2 => array(
      'title' => 'Not Elms',
      'operator' => '=',
      'value' => 'not_elms',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );
  $handler->display->display_options['filters']['text']['xpath_selector'] = 'tags';
  
  /* Display: ELMS Media Browser */
  $handler = $view->new_display('page', 'ELMS Media Browser', 'elms_media_browser');
  $handler->display->display_options['display_description'] = 'The view that will open in the pop-up dialog.';
  $handler->display->display_options['path'] = 'elms_media_image_library';

  
  $views[$view->name] = $view;

  return $views;
  
}