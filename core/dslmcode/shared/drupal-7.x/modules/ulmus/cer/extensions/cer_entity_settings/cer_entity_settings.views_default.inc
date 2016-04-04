<?php

/**
 * Implements hook_views_default_views().
 */
function cer_entity_settings_views_default_views() {
  $views = array();

  $view = new view();
  $view->name = 'cer_endpoint_in_use';
  $view->description = '';
  $view->tag = 'CER Entity Settings';
  $view->base_table = 'cer_preset';
  $view->human_name = 'CER Endpoints in Use';
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
  $handler->display->display_options['row_plugin'] = 'entity';
  $handler->display->display_options['row_options']['view_mode'] = 'default';
  $handler->display->display_options['filter_groups']['groups'] = array(
    1 => 'OR',
  );
  /* Filter criterion: CER Preset: Left Field (cer_left) */
  $handler->display->display_options['filters']['cer_left_path']['id'] = 'cer_left_path';
  $handler->display->display_options['filters']['cer_left_path']['table'] = 'field_data_cer_left';
  $handler->display->display_options['filters']['cer_left_path']['field'] = 'cer_left_path';
  $handler->display->display_options['filters']['cer_left_path']['operator'] = 'starts';
  $handler->display->display_options['filters']['cer_left_path']['group'] = 1;
  $handler->display->display_options['filters']['cer_left_path']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cer_left_path']['expose']['operator_id'] = 'cer_left_path_op';
  $handler->display->display_options['filters']['cer_left_path']['expose']['label'] = 'Left Field';
  $handler->display->display_options['filters']['cer_left_path']['expose']['operator'] = 'cer_left_path_op';
  $handler->display->display_options['filters']['cer_left_path']['expose']['identifier'] = 'left';
  $handler->display->display_options['filters']['cer_left_path']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  /* Filter criterion: CER Preset: Right Field (cer_right) */
  $handler->display->display_options['filters']['cer_right_path']['id'] = 'cer_right_path';
  $handler->display->display_options['filters']['cer_right_path']['table'] = 'field_data_cer_right';
  $handler->display->display_options['filters']['cer_right_path']['field'] = 'cer_right_path';
  $handler->display->display_options['filters']['cer_right_path']['operator'] = 'starts';
  $handler->display->display_options['filters']['cer_right_path']['group'] = 1;
  $handler->display->display_options['filters']['cer_right_path']['exposed'] = TRUE;
  $handler->display->display_options['filters']['cer_right_path']['expose']['operator_id'] = 'cer_right_path_op';
  $handler->display->display_options['filters']['cer_right_path']['expose']['label'] = 'Right Field';
  $handler->display->display_options['filters']['cer_right_path']['expose']['operator'] = 'cer_right_path_op';
  $handler->display->display_options['filters']['cer_right_path']['expose']['identifier'] = 'right';
  $handler->display->display_options['filters']['cer_right_path']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
  );
  $views[$view->name] = $view;

  return $views;
}
