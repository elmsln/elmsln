<?php
/**
 * @file
 * cis_section.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cis_section_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cis_section_list';
  $view->description = 'Administration fo all sections';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'CIS Section list';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'CIS Section list';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    4 => '4',
    6 => '6',
    8 => '8',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_section_id' => 'field_section_id',
    'etid' => 'etid',
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
    'field_section_id' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'etid' => array(
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
  $handler->display->display_options['style_options']['summary'] = 'A list of all sections in this course.';
  /* Header: OG membership: Group membership overview */
  $handler->display->display_options['header']['og_membership_overview']['id'] = 'og_membership_overview';
  $handler->display->display_options['header']['og_membership_overview']['table'] = 'og_membership';
  $handler->display->display_options['header']['og_membership_overview']['field'] = 'og_membership_overview';
  $handler->display->display_options['header']['og_membership_overview']['manager'] = 1;
  $handler->display->display_options['header']['og_membership_overview']['total_members_1'] = 0;
  $handler->display->display_options['header']['og_membership_overview']['total_members_2'] = 0;
  $handler->display->display_options['header']['og_membership_overview']['total_members_3'] = 0;
  $handler->display->display_options['header']['og_membership_overview']['total_members'] = 1;
  $handler->display->display_options['header']['og_membership_overview']['total_content'] = 1;
  /* Relationship: OG membership: OG membership from Node group */
  $handler->display->display_options['relationships']['og_membership_rel_group']['id'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['table'] = 'node';
  $handler->display->display_options['relationships']['og_membership_rel_group']['field'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_rel_group']['required'] = TRUE;
  /* Relationship: OG membership: User from OG membership */
  $handler->display->display_options['relationships']['og_membership_related_user']['id'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['table'] = 'og_membership';
  $handler->display->display_options['relationships']['og_membership_related_user']['field'] = 'og_membership_related_user';
  $handler->display->display_options['relationships']['og_membership_related_user']['relationship'] = 'og_membership_rel_group';
  $handler->display->display_options['relationships']['og_membership_related_user']['required'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Section id */
  $handler->display->display_options['fields']['field_section_id']['id'] = 'field_section_id';
  $handler->display->display_options['fields']['field_section_id']['table'] = 'field_data_field_section_id';
  $handler->display->display_options['fields']['field_section_id']['field'] = 'field_section_id';
  /* Field: Content: Instructional outlines */
  $handler->display->display_options['fields']['field_instructional_outlines']['id'] = 'field_instructional_outlines';
  $handler->display->display_options['fields']['field_instructional_outlines']['table'] = 'field_data_field_instructional_outlines';
  $handler->display->display_options['fields']['field_instructional_outlines']['field'] = 'field_instructional_outlines';
  $handler->display->display_options['fields']['field_instructional_outlines']['label'] = 'Instructional Outline';
  $handler->display->display_options['fields']['field_instructional_outlines']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_instructional_outlines']['delta_offset'] = '0';
  /* Field: COUNT(DISTINCT OG membership: Entity id) */
  $handler->display->display_options['fields']['etid']['id'] = 'etid';
  $handler->display->display_options['fields']['etid']['table'] = 'og_membership';
  $handler->display->display_options['fields']['etid']['field'] = 'etid';
  $handler->display->display_options['fields']['etid']['relationship'] = 'og_membership_related_user';
  $handler->display->display_options['fields']['etid']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['etid']['label'] = 'Members';
  /* Field: Content: Active */
  $handler->display->display_options['fields']['field_cis_active']['id'] = 'field_cis_active';
  $handler->display->display_options['fields']['field_cis_active']['table'] = 'field_data_field_cis_active';
  $handler->display->display_options['fields']['field_cis_active']['field'] = 'field_cis_active';
  $handler->display->display_options['fields']['field_cis_active']['label'] = 'Status';
  /* Field: Content: Post date */
  $handler->display->display_options['fields']['created']['id'] = 'created';
  $handler->display->display_options['fields']['created']['table'] = 'node';
  $handler->display->display_options['fields']['created']['field'] = 'created';
  $handler->display->display_options['fields']['created']['label'] = 'Created';
  $handler->display->display_options['fields']['created']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['created']['date_format'] = 'short';
  /* Field: Content: Edit link */
  $handler->display->display_options['fields']['edit_node']['id'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['table'] = 'views_entity_node';
  $handler->display->display_options['fields']['edit_node']['field'] = 'edit_node';
  $handler->display->display_options['fields']['edit_node']['label'] = '';
  $handler->display->display_options['fields']['edit_node']['element_label_colon'] = FALSE;
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
    'section' => 'section',
  );
  /* Filter criterion: Content: Active (field_cis_active) */
  $handler->display->display_options['filters']['field_cis_active_value']['id'] = 'field_cis_active_value';
  $handler->display->display_options['filters']['field_cis_active_value']['table'] = 'field_data_field_cis_active';
  $handler->display->display_options['filters']['field_cis_active_value']['field'] = 'field_cis_active_value';
  $handler->display->display_options['filters']['field_cis_active_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cis_active_value']['expose']['operator_id'] = 'field_cis_active_value_op';
  $handler->display->display_options['filters']['field_cis_active_value']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['field_cis_active_value']['expose']['operator'] = 'field_cis_active_value_op';
  $handler->display->display_options['filters']['field_cis_active_value']['expose']['identifier'] = 'field_cis_active_value';
  $handler->display->display_options['filters']['field_cis_active_value']['expose']['remember_roles'] = array(
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
    11 => 0,
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'cis/section-list';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Sections list';
  $handler->display->display_options['menu']['description'] = 'Listing of all sections in this area';
  $handler->display->display_options['menu']['weight'] = '100';
  $handler->display->display_options['menu']['name'] = 'menu-cis-toolkit';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['menu']['context_only_inline'] = 0;
  $export['cis_section_list'] = $view;

  return $export;
}
