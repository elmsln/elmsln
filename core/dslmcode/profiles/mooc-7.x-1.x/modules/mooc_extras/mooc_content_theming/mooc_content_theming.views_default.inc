<?php
/**
 * @file
 * mooc_content_theming.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function mooc_content_theming_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'foundation_access_header';
  $view->description = 'Block to supply header image contextually for branded theming';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'Foundation Access Header';
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
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['default_field_elements'] = FALSE;
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_mooc_image']['id'] = 'field_mooc_image';
  $handler->display->display_options['fields']['field_mooc_image']['table'] = 'field_data_field_mooc_image';
  $handler->display->display_options['fields']['field_mooc_image']['field'] = 'field_mooc_image';
  $handler->display->display_options['fields']['field_mooc_image']['label'] = '';
  $handler->display->display_options['fields']['field_mooc_image']['element_type'] = '0';
  $handler->display->display_options['fields']['field_mooc_image']['element_label_type'] = '0';
  $handler->display->display_options['fields']['field_mooc_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_mooc_image']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_mooc_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_mooc_image']['settings'] = array(
    'image_style' => '',
    'image_link' => '',
  );
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block');
  $handler->display->display_options['authcache'] = array(
    'lifespan' => '21600',
    'perpage' => '1',
    'clients' => array(
      'authcache_ajax' => array(
        'status' => '1',
        'weight' => '0',
      ),
    ),
    'fallback' => 'cancel',
    'status' => 0,
    'peruser' => 0,
  );
  $handler->display->display_options['block_description'] = 'Foundation Access Header';
  $handler->display->display_options['block_caching'] = '-1';
  $export['foundation_access_header'] = $view;

  return $export;
}
