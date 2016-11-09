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
  $handler->display->display_options['use_ajax'] = TRUE;
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    75987638 => '75987638',
    166149871 => '166149871',
    67296478 => '67296478',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['exposed_form']['type'] = 'better_exposed_filters';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['autosubmit'] = TRUE;
  $handler->display->display_options['exposed_form']['options']['bef'] = array(
    'general' => array(
      'allow_secondary' => 0,
      'secondary_label' => 'Advanced options',
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'title' => array(
      'more_options' => array(
        'is_secondary' => 0,
        'bef_filter_description' => '',
        'tokens' => array(
          'available' => array(
            0 => 'global_types',
            'secondary_label' => NULL,
            'collapsible_label' => NULL,
            'combine_rewrite' => NULL,
            'reset_label' => NULL,
            'bef_filter_description' => NULL,
            'any_label' => NULL,
            'filter_rewrite_values' => NULL,
          ),
          'secondary_label' => NULL,
          'collapsible_label' => NULL,
          'combine_rewrite' => NULL,
          'reset_label' => NULL,
          'bef_filter_description' => NULL,
          'any_label' => NULL,
          'filter_rewrite_values' => NULL,
        ),
        'secondary_label' => NULL,
        'collapsible_label' => NULL,
        'combine_rewrite' => NULL,
        'reset_label' => NULL,
        'any_label' => NULL,
        'filter_rewrite_values' => NULL,
      ),
      'secondary_label' => NULL,
      'collapsible_label' => NULL,
      'combine_rewrite' => NULL,
      'reset_label' => NULL,
      'bef_filter_description' => NULL,
      'any_label' => NULL,
      'filter_rewrite_values' => NULL,
    ),
    'secondary_label' => NULL,
    'collapsible_label' => NULL,
    'combine_rewrite' => NULL,
    'reset_label' => NULL,
    'bef_filter_description' => NULL,
    'any_label' => NULL,
    'filter_rewrite_values' => NULL,
  );
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '50';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['pager']['options']['quantity'] = '9';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'type' => 'type',
    'title' => 'title',
    'field_course' => 'title',
    'edit_node' => 'delete_node',
    'entity_iframe_link' => 'delete_node',
    'delete_node' => 'delete_node',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'type' => array(
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
    'field_course' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'edit_node' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'entity_iframe_link' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'delete_node' => array(
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
  );
  /* Relationship: H5P: H5P library properties */
  $handler->display->display_options['relationships']['h5p_libraries']['id'] = 'h5p_libraries';
  $handler->display->display_options['relationships']['h5p_libraries']['table'] = 'h5p_nodes';
  $handler->display->display_options['relationships']['h5p_libraries']['field'] = 'h5p_libraries';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_tagging']['id'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['table'] = 'field_data_field_tagging';
  $handler->display->display_options['fields']['field_tagging']['field'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['label'] = 'Tag';
  $handler->display->display_options['fields']['field_tagging']['element_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_tagging']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_tagging']['field_api_classes'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Field: Content: iframe link */
  $handler->display->display_options['fields']['entity_iframe_link']['id'] = 'entity_iframe_link';
  $handler->display->display_options['fields']['entity_iframe_link']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['entity_iframe_link']['field'] = 'entity_iframe_link';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_cis_course_ref']['id'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['field'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['label'] = '';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_cis_course_ref']['field_api_classes'] = TRUE;
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['order'] = 'DESC';
  $handler->display->display_options['sorts']['title']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['title']['expose']['label'] = 'Title';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['exposed'] = TRUE;
  $handler->display->display_options['sorts']['created']['expose']['label'] = 'Date';
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
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cis_course' => 'cis_course',
    'section' => 'section',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'image_gallery' => 'image_gallery',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'static_content' => 'static_content',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['type_1']['expose']['reduce'] = TRUE;
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

  /* Display: Table */
  $handler = $view->new_display('page', 'Table', 'page');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['defaults']['cache'] = FALSE;
  $handler->display->display_options['cache']['type'] = 'views_content_cache';
  $handler->display->display_options['cache']['results_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['results_max_lifespan'] = '21600';
  $handler->display->display_options['cache']['output_min_lifespan'] = '-1';
  $handler->display->display_options['cache']['output_max_lifespan'] = '21600';
  $handler->display->display_options['cache']['keys'] = array(
    'node' => array(
      'audio' => 0,
      'cis_course' => 0,
      'section' => 0,
      'document' => 0,
      'external_video' => 0,
      'figurelabel' => 0,
      'elmsmedia_image' => 0,
      'image_gallery' => 0,
      'h5p_content' => 0,
      'svg' => 0,
      'static_content' => 0,
      'video' => 0,
    ),
    'node_only' => array(
      'node_changed' => 'node_changed',
    ),
    'og' => array(
      'current' => 0,
      'user' => 0,
    ),
  );
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Bulk operations: Content */
  $handler->display->display_options['fields']['views_bulk_operations']['id'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['table'] = 'node';
  $handler->display->display_options['fields']['views_bulk_operations']['field'] = 'views_bulk_operations';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['display_type'] = '1';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['enable_select_all_pages'] = 1;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['force_single'] = 0;
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_settings']['entity_load_capacity'] = '10';
  $handler->display->display_options['fields']['views_bulk_operations']['vbo_operations'] = array(
    'action::views_bulk_operations_delete_item' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Delete selected',
    ),
    'action::views_bulk_operations_modify_action' => array(
      'selected' => 1,
      'postpone_processing' => 0,
      'skip_confirmation' => 0,
      'override_label' => 1,
      'label' => 'Modify tags',
      'settings' => array(
        'show_all_tokens' => 1,
        'display_values' => array(
          'audio::field_tagging' => 'audio::field_tagging',
          'audio::field_cis_course_ref' => 'audio::field_cis_course_ref',
          'document::field_tagging' => 'document::field_tagging',
          'document::field_cis_course_ref' => 'document::field_cis_course_ref',
          'external_video::field_tagging' => 'external_video::field_tagging',
          'external_video::field_cis_course_ref' => 'external_video::field_cis_course_ref',
          'elmsmedia_image::field_tagging' => 'elmsmedia_image::field_tagging',
          'elmsmedia_image::field_cis_course_ref' => 'elmsmedia_image::field_cis_course_ref',
          'video::field_tagging' => 'video::field_tagging',
          'video::field_cis_course_ref' => 'video::field_cis_course_ref',
        ),
      ),
    ),
  );
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_tagging']['id'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['table'] = 'field_data_field_tagging';
  $handler->display->display_options['fields']['field_tagging']['field'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['label'] = 'Tag';
  $handler->display->display_options['fields']['field_tagging']['element_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_tagging']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_tagging']['field_api_classes'] = TRUE;
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  /* Field: Content: iframe link */
  $handler->display->display_options['fields']['entity_iframe_link']['id'] = 'entity_iframe_link';
  $handler->display->display_options['fields']['entity_iframe_link']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['entity_iframe_link']['field'] = 'entity_iframe_link';
  /* Field: Content: Delete link */
  $handler->display->display_options['fields']['delete_node']['id'] = 'delete_node';
  $handler->display->display_options['fields']['delete_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['delete_node']['field'] = 'delete_node';
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_cis_course_ref']['id'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['field'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['label'] = '';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['settings'] = array(
    'link' => 1,
  );
  $handler->display->display_options['fields']['field_cis_course_ref']['field_api_classes'] = TRUE;
  $handler->display->display_options['path'] = 'elmsmedia/table';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Table view';
  $handler->display->display_options['menu']['description'] = 'Use this for bulk operations';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: EVA Field */
  $handler = $view->new_display('entity_view', 'EVA Field', 'entity_view_1');
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Course (field_cis_course_ref) */
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['id'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['field'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['default_action'] = 'default';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_cis_course_ref_target_id']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['entity_type'] = 'node';
  $handler->display->display_options['bundles'] = array(
    0 => 'cis_course',
  );

  /* Display: Visual */
  $handler = $view->new_display('page', 'Visual', 'page_1');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_tagging']['id'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['table'] = 'field_data_field_tagging';
  $handler->display->display_options['fields']['field_tagging']['field'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['label'] = 'Tag';
  $handler->display->display_options['fields']['field_tagging']['element_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_tagging']['delta_limit'] = '5';
  $handler->display->display_options['fields']['field_tagging']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_tagging']['separator'] = ' ';
  $handler->display->display_options['fields']['field_tagging']['field_api_classes'] = TRUE;
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_cis_course_ref']['id'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['field'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['label'] = '';
  $handler->display->display_options['fields']['field_cis_course_ref']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_cis_course_ref']['field_api_classes'] = TRUE;
  /* Field: Content: External media */
  $handler->display->display_options['fields']['field_external_media']['id'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['table'] = 'field_data_field_external_media';
  $handler->display->display_options['fields']['field_external_media']['field'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['label'] = '';
  $handler->display->display_options['fields']['field_external_media']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_external_media']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_external_media']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_external_media']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_external_media']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_external_media']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: File */
  $handler->display->display_options['fields']['field_document_file']['id'] = 'field_document_file';
  $handler->display->display_options['fields']['field_document_file']['table'] = 'field_data_field_document_file';
  $handler->display->display_options['fields']['field_document_file']['field'] = 'field_document_file';
  $handler->display->display_options['fields']['field_document_file']['label'] = '';
  $handler->display->display_options['fields']['field_document_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_file']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_document_file']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_document_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_document_file']['settings'] = array(
    'file_view_mode' => 'default',
  );
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_images']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_images']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'view_mode' => 'image__circle',
    'links' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_limit'] = '4';
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_images']['separator'] = '';
  /* Field: Content: Poster */
  $handler->display->display_options['fields']['field_poster']['id'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['table'] = 'field_data_field_poster';
  $handler->display->display_options['fields']['field_poster']['field'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['label'] = '';
  $handler->display->display_options['fields']['field_poster']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_poster']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_poster']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_poster']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_poster']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: SVG */
  $handler->display->display_options['fields']['field_svg']['id'] = 'field_svg';
  $handler->display->display_options['fields']['field_svg']['table'] = 'field_data_field_svg';
  $handler->display->display_options['fields']['field_svg']['field'] = 'field_svg';
  $handler->display->display_options['fields']['field_svg']['label'] = '';
  $handler->display->display_options['fields']['field_svg']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_svg']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_svg']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_svg']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_svg']['type'] = 'svg_sanitizer';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = '';
  $handler->display->display_options['fields']['changed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'm/d/y g:ia';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type_1']['id'] = 'type_1';
  $handler->display->display_options['fields']['type_1']['table'] = 'node';
  $handler->display->display_options['fields']['type_1']['field'] = 'type';
  $handler->display->display_options['fields']['type_1']['label'] = '';
  $handler->display->display_options['fields']['type_1']['alter']['trim_whitespace'] = TRUE;
  $handler->display->display_options['fields']['type_1']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['type_1']['element_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_label_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['type_1']['machine_name'] = TRUE;
  /* Field: H5P: H5P: Content type */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'h5p_libraries';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'h5p_libraries';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = TRUE;
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
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cis_course' => 'cis_course',
    'section' => 'section',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'image_gallery' => 'image_gallery',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'static_content' => 'static_content',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['type_1']['expose']['reduce'] = TRUE;
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
  /* Filter criterion: Content: Course (field_cis_course_ref) */
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['id'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['field'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['operator_id'] = 'field_cis_course_ref_target_id_op';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['label'] = 'Course';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['operator'] = 'field_cis_course_ref_target_id_op';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['identifier'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['path'] = 'elmsmedia';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Assets';
  $handler->display->display_options['menu']['description'] = 'Visual listing of media';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;

  /* Display: Visual Tab */
  $handler = $view->new_display('page', 'Visual Tab', 'page_3');
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['style_options']['default_row_class'] = FALSE;
  $handler->display->display_options['style_options']['row_class_special'] = FALSE;
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type']['id'] = 'type';
  $handler->display->display_options['fields']['type']['table'] = 'node';
  $handler->display->display_options['fields']['type']['field'] = 'type';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Content: Tags */
  $handler->display->display_options['fields']['field_tagging']['id'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['table'] = 'field_data_field_tagging';
  $handler->display->display_options['fields']['field_tagging']['field'] = 'field_tagging';
  $handler->display->display_options['fields']['field_tagging']['label'] = 'Tag';
  $handler->display->display_options['fields']['field_tagging']['element_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_tagging']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_tagging']['type'] = 'taxonomy_term_reference_plain';
  $handler->display->display_options['fields']['field_tagging']['delta_limit'] = '5';
  $handler->display->display_options['fields']['field_tagging']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_tagging']['separator'] = ' ';
  $handler->display->display_options['fields']['field_tagging']['field_api_classes'] = TRUE;
  /* Field: Content: Course */
  $handler->display->display_options['fields']['field_cis_course_ref']['id'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['field'] = 'field_cis_course_ref';
  $handler->display->display_options['fields']['field_cis_course_ref']['label'] = '';
  $handler->display->display_options['fields']['field_cis_course_ref']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['field_cis_course_ref']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['field_cis_course_ref']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_cis_course_ref']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_cis_course_ref']['field_api_classes'] = TRUE;
  /* Field: Content: External media */
  $handler->display->display_options['fields']['field_external_media']['id'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['table'] = 'field_data_field_external_media';
  $handler->display->display_options['fields']['field_external_media']['field'] = 'field_external_media';
  $handler->display->display_options['fields']['field_external_media']['label'] = '';
  $handler->display->display_options['fields']['field_external_media']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_external_media']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_external_media']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_external_media']['click_sort_column'] = 'video_url';
  $handler->display->display_options['fields']['field_external_media']['type'] = 'video_embed_field_thumbnail';
  $handler->display->display_options['fields']['field_external_media']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: File */
  $handler->display->display_options['fields']['field_document_file']['id'] = 'field_document_file';
  $handler->display->display_options['fields']['field_document_file']['table'] = 'field_data_field_document_file';
  $handler->display->display_options['fields']['field_document_file']['field'] = 'field_document_file';
  $handler->display->display_options['fields']['field_document_file']['label'] = '';
  $handler->display->display_options['fields']['field_document_file']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_document_file']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_document_file']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_document_file']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_document_file']['settings'] = array(
    'file_view_mode' => 'default',
  );
  /* Field: Content: Image */
  $handler->display->display_options['fields']['field_image']['id'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['table'] = 'field_data_field_image';
  $handler->display->display_options['fields']['field_image']['field'] = 'field_image';
  $handler->display->display_options['fields']['field_image']['label'] = '';
  $handler->display->display_options['fields']['field_image']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_image']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_image']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_image']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_image']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: Images */
  $handler->display->display_options['fields']['field_images']['id'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['table'] = 'field_data_field_images';
  $handler->display->display_options['fields']['field_images']['field'] = 'field_images';
  $handler->display->display_options['fields']['field_images']['label'] = '';
  $handler->display->display_options['fields']['field_images']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_images']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_images']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_images']['type'] = 'entityreference_entity_view';
  $handler->display->display_options['fields']['field_images']['settings'] = array(
    'view_mode' => 'image__circle',
    'links' => 0,
  );
  $handler->display->display_options['fields']['field_images']['delta_limit'] = '4';
  $handler->display->display_options['fields']['field_images']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_images']['separator'] = '';
  /* Field: Content: Poster */
  $handler->display->display_options['fields']['field_poster']['id'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['table'] = 'field_data_field_poster';
  $handler->display->display_options['fields']['field_poster']['field'] = 'field_poster';
  $handler->display->display_options['fields']['field_poster']['label'] = '';
  $handler->display->display_options['fields']['field_poster']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_poster']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_poster']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_poster']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_poster']['settings'] = array(
    'image_style' => 'image_card_medium',
    'image_link' => '',
  );
  /* Field: Content: SVG */
  $handler->display->display_options['fields']['field_svg']['id'] = 'field_svg';
  $handler->display->display_options['fields']['field_svg']['table'] = 'field_data_field_svg';
  $handler->display->display_options['fields']['field_svg']['field'] = 'field_svg';
  $handler->display->display_options['fields']['field_svg']['label'] = '';
  $handler->display->display_options['fields']['field_svg']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_svg']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['field_svg']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['field_svg']['click_sort_column'] = 'fid';
  $handler->display->display_options['fields']['field_svg']['type'] = 'svg_sanitizer';
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = '';
  $handler->display->display_options['fields']['changed']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['changed']['date_format'] = 'custom';
  $handler->display->display_options['fields']['changed']['custom_date_format'] = 'm/d/y g:ia';
  $handler->display->display_options['fields']['changed']['second_date_format'] = 'long';
  /* Field: Content: Type */
  $handler->display->display_options['fields']['type_1']['id'] = 'type_1';
  $handler->display->display_options['fields']['type_1']['table'] = 'node';
  $handler->display->display_options['fields']['type_1']['field'] = 'type';
  $handler->display->display_options['fields']['type_1']['label'] = '';
  $handler->display->display_options['fields']['type_1']['element_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_label_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['type_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['type_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['type_1']['empty_zero'] = TRUE;
  $handler->display->display_options['fields']['type_1']['machine_name'] = TRUE;
  /* Field: H5P: H5P: Content type */
  $handler->display->display_options['fields']['title_1']['id'] = 'title_1';
  $handler->display->display_options['fields']['title_1']['table'] = 'h5p_libraries';
  $handler->display->display_options['fields']['title_1']['field'] = 'title';
  $handler->display->display_options['fields']['title_1']['relationship'] = 'h5p_libraries';
  $handler->display->display_options['fields']['title_1']['label'] = '';
  $handler->display->display_options['fields']['title_1']['element_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title_1']['element_wrapper_type'] = '0';
  $handler->display->display_options['fields']['title_1']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['title_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['title_1']['empty_zero'] = TRUE;
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
  $handler->display->display_options['filters']['type']['operator'] = 'not in';
  $handler->display->display_options['filters']['type']['value'] = array(
    'cis_course' => 'cis_course',
    'section' => 'section',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type_1']['id'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['table'] = 'node';
  $handler->display->display_options['filters']['type_1']['field'] = 'type';
  $handler->display->display_options['filters']['type_1']['value'] = array(
    'audio' => 'audio',
    'document' => 'document',
    'external_video' => 'external_video',
    'figurelabel' => 'figurelabel',
    'elmsmedia_image' => 'elmsmedia_image',
    'image_gallery' => 'image_gallery',
    'h5p_content' => 'h5p_content',
    'svg' => 'svg',
    'static_content' => 'static_content',
    'video' => 'video',
  );
  $handler->display->display_options['filters']['type_1']['group'] = 1;
  $handler->display->display_options['filters']['type_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['type_1']['expose']['operator_id'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['label'] = 'Type';
  $handler->display->display_options['filters']['type_1']['expose']['operator'] = 'type_1_op';
  $handler->display->display_options['filters']['type_1']['expose']['identifier'] = 'type_1';
  $handler->display->display_options['filters']['type_1']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['filters']['type_1']['expose']['reduce'] = TRUE;
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
  /* Filter criterion: Content: Course (field_cis_course_ref) */
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['id'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['table'] = 'field_data_field_cis_course_ref';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['field'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['operator_id'] = 'field_cis_course_ref_target_id_op';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['label'] = 'Course';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['operator'] = 'field_cis_course_ref_target_id_op';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['identifier'] = 'field_cis_course_ref_target_id';
  $handler->display->display_options['filters']['field_cis_course_ref_target_id']['expose']['remember_roles'] = array(
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
  $handler->display->display_options['path'] = 'elmsmedia/visual';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Visual view';
  $handler->display->display_options['menu']['description'] = 'Visual listing of media';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'menu-elmsln-navigation';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['elms_media_overview'] = $view;

  return $export;
}
