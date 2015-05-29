<?php
/**
 * @file
 * cis_data.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function cis_data_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'historical_college_data';
  $view->description = 'Default view for data table Historical course data';
  $view->tag = 'data table';
  $view->base_table = 'historical_course_data';
  $view->human_name = 'historical_college_data';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Default */
  $handler = $view->new_display('default', 'Default', 'default');
  $handler->display->display_options['title'] = 'Historical course data';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'role';
  $handler->display->display_options['access']['role'] = array(
    30037204 => '30037204',
    166149871 => '166149871',
  );
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'schedule_id' => 'schedule_id',
    'course' => 'course',
    'semester' => 'semester',
    'year' => 'year',
    'location' => 'location',
    'section' => 'section',
    'enrolled' => 'enrolled',
    'limit' => 'limit',
  );
  $handler->display->display_options['style_options']['default'] = -1;
  $handler->display->display_options['style_options']['info'] = array(
    'schedule_id' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'course' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'semester' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'year' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'location' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'section' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'enrolled' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'limit' => array(
      'sortable' => 1,
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'There is no data in this table.';
  $handler->display->display_options['empty']['text']['format'] = '1';
  /* Relationship: Historical course data: Course */
  $handler->display->display_options['relationships']['course']['id'] = 'course';
  $handler->display->display_options['relationships']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['relationships']['course']['field'] = 'course';
  $handler->display->display_options['relationships']['course']['required'] = TRUE;
  /* Relationship: nid */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'historical_name_to_data';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'course';
  $handler->display->display_options['relationships']['nid']['ui_name'] = 'nid';
  $handler->display->display_options['relationships']['nid']['label'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Field: Historical course data: Schedule id */
  $handler->display->display_options['fields']['schedule_id']['id'] = 'schedule_id';
  $handler->display->display_options['fields']['schedule_id']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['schedule_id']['field'] = 'schedule_id';
  $handler->display->display_options['fields']['schedule_id']['label'] = 'schedule_id';
  $handler->display->display_options['fields']['schedule_id']['separator'] = '';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  /* Field: Historical course data: Semester */
  $handler->display->display_options['fields']['semester']['id'] = 'semester';
  $handler->display->display_options['fields']['semester']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['semester']['field'] = 'semester';
  $handler->display->display_options['fields']['semester']['label'] = 'semester';
  /* Field: Historical course data: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  $handler->display->display_options['fields']['year']['label'] = 'year';
  /* Field: Historical course data: Location */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  $handler->display->display_options['fields']['location']['label'] = 'location';
  /* Field: Historical course data: Section */
  $handler->display->display_options['fields']['section']['id'] = 'section';
  $handler->display->display_options['fields']['section']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['section']['field'] = 'section';
  $handler->display->display_options['fields']['section']['label'] = 'section';
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  /* Sort criterion: Content: Title */
  $handler->display->display_options['sorts']['title']['id'] = 'title';
  $handler->display->display_options['sorts']['title']['table'] = 'node';
  $handler->display->display_options['sorts']['title']['field'] = 'title';
  $handler->display->display_options['sorts']['title']['relationship'] = 'nid';
  /* Filter criterion: Historical course data: Location */
  $handler->display->display_options['filters']['location']['id'] = 'location';
  $handler->display->display_options['filters']['location']['table'] = 'historical_course_data';
  $handler->display->display_options['filters']['location']['field'] = 'location';
  $handler->display->display_options['filters']['location']['group'] = 1;
  $handler->display->display_options['filters']['location']['exposed'] = TRUE;
  $handler->display->display_options['filters']['location']['expose']['operator_id'] = 'location_op';
  $handler->display->display_options['filters']['location']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['location']['expose']['operator'] = 'location_op';
  $handler->display->display_options['filters']['location']['expose']['identifier'] = 'location';
  $handler->display->display_options['filters']['location']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );
  /* Filter criterion: Historical course data: Semester */
  $handler->display->display_options['filters']['semester']['id'] = 'semester';
  $handler->display->display_options['filters']['semester']['table'] = 'historical_course_data';
  $handler->display->display_options['filters']['semester']['field'] = 'semester';
  $handler->display->display_options['filters']['semester']['group'] = 1;
  $handler->display->display_options['filters']['semester']['exposed'] = TRUE;
  $handler->display->display_options['filters']['semester']['expose']['operator_id'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['label'] = 'Semester';
  $handler->display->display_options['filters']['semester']['expose']['operator'] = 'semester_op';
  $handler->display->display_options['filters']['semester']['expose']['identifier'] = 'semester';
  $handler->display->display_options['filters']['semester']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );
  /* Filter criterion: Historical course data: Year */
  $handler->display->display_options['filters']['year']['id'] = 'year';
  $handler->display->display_options['filters']['year']['table'] = 'historical_course_data';
  $handler->display->display_options['filters']['year']['field'] = 'year';
  $handler->display->display_options['filters']['year']['group'] = 1;
  $handler->display->display_options['filters']['year']['exposed'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['operator_id'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['label'] = 'Year';
  $handler->display->display_options['filters']['year']['expose']['operator'] = 'year_op';
  $handler->display->display_options['filters']['year']['expose']['identifier'] = 'year';
  $handler->display->display_options['filters']['year']['expose']['multiple'] = TRUE;
  $handler->display->display_options['filters']['year']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );
  $handler->display->display_options['filters']['year']['group_info']['label'] = 'Year';
  $handler->display->display_options['filters']['year']['group_info']['identifier'] = 'year';
  $handler->display->display_options['filters']['year']['group_info']['multiple'] = TRUE;
  $handler->display->display_options['filters']['year']['group_info']['group_items'] = array(
    1 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
    2 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
    3 => array(
      'title' => '',
      'operator' => '=',
      'value' => '',
    ),
  );
  /* Filter criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['filters']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['filters']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['relationship'] = 'nid';
  $handler->display->display_options['filters']['field_academic_home_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator_id'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['label'] = 'Unit';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['operator'] = 'field_academic_home_target_id_op';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['identifier'] = 'field_academic_home_target_id';
  $handler->display->display_options['filters']['field_academic_home_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );
  /* Filter criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['filters']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['filters']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['relationship'] = 'nid';
  $handler->display->display_options['filters']['field_program_classification_target_id']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator_id'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['label'] = 'Program';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['operator'] = 'field_program_classification_target_id_op';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['identifier'] = 'field_program_classification_target_id';
  $handler->display->display_options['filters']['field_program_classification_target_id']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );
  /* Filter criterion: Historical course data: Course */
  $handler->display->display_options['filters']['course']['id'] = 'course';
  $handler->display->display_options['filters']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['filters']['course']['field'] = 'course';
  $handler->display->display_options['filters']['course']['exposed'] = TRUE;
  $handler->display->display_options['filters']['course']['expose']['operator_id'] = 'course_op';
  $handler->display->display_options['filters']['course']['expose']['label'] = 'Course';
  $handler->display->display_options['filters']['course']['expose']['operator'] = 'course_op';
  $handler->display->display_options['filters']['course']['expose']['identifier'] = 'course';
  $handler->display->display_options['filters']['course']['expose']['remember_roles'] = array(
    2 => '2',
    1 => 0,
    9 => 0,
    11 => 0,
    5 => 0,
    10 => 0,
    6 => 0,
    4 => 0,
    7 => 0,
    8 => 0,
    3 => 0,
  );

  /* Display: Course */
  $handler = $view->new_display('page', 'Course', 'page_1');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'title',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'ColumnChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  $handler->display->display_options['path'] = 'cis/historical_college_data';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'College data';
  $handler->display->display_options['menu']['weight'] = '10';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Year */
  $handler = $view->new_display('page', 'Year', 'page_2');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'year',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'ColumnChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Historical course data: Year */
  $handler->display->display_options['fields']['year']['id'] = 'year';
  $handler->display->display_options['fields']['year']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['year']['field'] = 'year';
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['group_type'] = 'sum';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['separator'] = '';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['group_type'] = 'sum';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  $handler->display->display_options['fields']['limit']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Historical course data: Year */
  $handler->display->display_options['sorts']['year']['id'] = 'year';
  $handler->display->display_options['sorts']['year']['table'] = 'historical_course_data';
  $handler->display->display_options['sorts']['year']['field'] = 'year';
  $handler->display->display_options['path'] = 'cis/historical_college_data/year';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Year';
  $handler->display->display_options['menu']['weight'] = '-1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Campus */
  $handler = $view->new_display('page', 'Campus', 'page_3');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'location',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'ColumnChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Historical course data: Location */
  $handler->display->display_options['fields']['location']['id'] = 'location';
  $handler->display->display_options['fields']['location']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['location']['field'] = 'location';
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['group_type'] = 'sum';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['separator'] = '';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['group_type'] = 'sum';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  $handler->display->display_options['fields']['limit']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Historical course data: Location */
  $handler->display->display_options['sorts']['location']['id'] = 'location';
  $handler->display->display_options['sorts']['location']['table'] = 'historical_course_data';
  $handler->display->display_options['sorts']['location']['field'] = 'location';
  $handler->display->display_options['path'] = 'cis/historical_college_data/campus';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Campus';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Unit */
  $handler = $view->new_display('page', 'Unit', 'page_6');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_abbreviation',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'PieChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Historical course data: Course */
  $handler->display->display_options['relationships']['course']['id'] = 'course';
  $handler->display->display_options['relationships']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['relationships']['course']['field'] = 'course';
  $handler->display->display_options['relationships']['course']['required'] = TRUE;
  /* Relationship: nid */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'historical_name_to_data';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'course';
  $handler->display->display_options['relationships']['nid']['ui_name'] = 'nid';
  $handler->display->display_options['relationships']['nid']['label'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['relationship'] = 'nid';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_abbreviation']['type'] = 'text_plain';
  /* Field: Historical course data: Course */
  $handler->display->display_options['fields']['course']['id'] = 'course';
  $handler->display->display_options['fields']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['course']['field'] = 'course';
  $handler->display->display_options['fields']['course']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['course']['label'] = '';
  $handler->display->display_options['fields']['course']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['course']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['sorts']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['relationship'] = 'nid';
  $handler->display->display_options['path'] = 'cis/historical_college_data/unit';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Unit';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Unit enrollments */
  $handler = $view->new_display('page', 'Unit enrollments', 'page_4');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_abbreviation',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'PieChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Historical course data: Course */
  $handler->display->display_options['relationships']['course']['id'] = 'course';
  $handler->display->display_options['relationships']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['relationships']['course']['field'] = 'course';
  $handler->display->display_options['relationships']['course']['required'] = TRUE;
  /* Relationship: nid */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'historical_name_to_data';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'course';
  $handler->display->display_options['relationships']['nid']['ui_name'] = 'nid';
  $handler->display->display_options['relationships']['nid']['label'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  /* Relationship: Entity Reference: Referenced Entity */
  $handler->display->display_options['relationships']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['relationship'] = 'nid';
  $handler->display->display_options['relationships']['field_academic_home_target_id']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Abbreviation */
  $handler->display->display_options['fields']['field_abbreviation']['id'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['table'] = 'field_data_field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['field'] = 'field_abbreviation';
  $handler->display->display_options['fields']['field_abbreviation']['relationship'] = 'field_academic_home_target_id';
  $handler->display->display_options['fields']['field_abbreviation']['type'] = 'text_plain';
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['group_type'] = 'sum';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['separator'] = '';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['group_type'] = 'sum';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  $handler->display->display_options['fields']['limit']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Academic home (field_academic_home) */
  $handler->display->display_options['sorts']['field_academic_home_target_id']['id'] = 'field_academic_home_target_id';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['table'] = 'field_data_field_academic_home';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['field'] = 'field_academic_home_target_id';
  $handler->display->display_options['sorts']['field_academic_home_target_id']['relationship'] = 'nid';
  $handler->display->display_options['path'] = 'cis/historical_college_data/unit/enrollments';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Enrollments';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Program */
  $handler = $view->new_display('page', 'Program', 'page_7');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_program_classification',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'PieChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['relationships'] = FALSE;
  /* Relationship: Historical course data: Course */
  $handler->display->display_options['relationships']['course']['id'] = 'course';
  $handler->display->display_options['relationships']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['relationships']['course']['field'] = 'course';
  $handler->display->display_options['relationships']['course']['required'] = TRUE;
  /* Relationship: nid */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'historical_name_to_data';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  $handler->display->display_options['relationships']['nid']['relationship'] = 'course';
  $handler->display->display_options['relationships']['nid']['ui_name'] = 'nid';
  $handler->display->display_options['relationships']['nid']['label'] = 'nid';
  $handler->display->display_options['relationships']['nid']['required'] = TRUE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Program classification */
  $handler->display->display_options['fields']['field_program_classification']['id'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['field'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_program_classification']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_program_classification']['empty'] = 'No Program';
  $handler->display->display_options['fields']['field_program_classification']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_program_classification']['delta_offset'] = '0';
  /* Field: Historical course data: Course */
  $handler->display->display_options['fields']['course']['id'] = 'course';
  $handler->display->display_options['fields']['course']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['course']['field'] = 'course';
  $handler->display->display_options['fields']['course']['group_type'] = 'count_distinct';
  $handler->display->display_options['fields']['course']['label'] = '';
  $handler->display->display_options['fields']['course']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['course']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['sorts']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['relationship'] = 'nid';
  $handler->display->display_options['path'] = 'cis/historical_college_data/program';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Program';
  $handler->display->display_options['menu']['weight'] = '1';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Program enrollments */
  $handler = $view->new_display('page', 'Program enrollments', 'page_5');
  $handler->display->display_options['defaults']['group_by'] = FALSE;
  $handler->display->display_options['group_by'] = TRUE;
  $handler->display->display_options['defaults']['pager'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'google_chart_tools_views';
  $handler->display->display_options['style_options']['grouping'] = array(
    0 => array(
      'field' => 'field_program_classification',
      'rendered' => 1,
      'rendered_strip' => 0,
    ),
  );
  $handler->display->display_options['style_options']['type'] = 'PieChart';
  $handler->display->display_options['style_options']['width'] = '900';
  $handler->display->display_options['style_options']['height'] = '600';
  $handler->display->display_options['style_options']['responsive'] = 1;
  $handler->display->display_options['style_options']['isstacked'] = 0;
  $handler->display->display_options['style_options']['pointsize'] = '0';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Program classification */
  $handler->display->display_options['fields']['field_program_classification']['id'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['field'] = 'field_program_classification';
  $handler->display->display_options['fields']['field_program_classification']['relationship'] = 'nid';
  $handler->display->display_options['fields']['field_program_classification']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['field_program_classification']['empty'] = 'No program';
  $handler->display->display_options['fields']['field_program_classification']['settings'] = array(
    'link' => 0,
  );
  $handler->display->display_options['fields']['field_program_classification']['delta_offset'] = '0';
  /* Field: Historical course data: Enrolled */
  $handler->display->display_options['fields']['enrolled']['id'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['enrolled']['field'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['group_type'] = 'sum';
  $handler->display->display_options['fields']['enrolled']['label'] = 'enrolled';
  $handler->display->display_options['fields']['enrolled']['separator'] = '';
  /* Field: Historical course data: Limit */
  $handler->display->display_options['fields']['limit']['id'] = 'limit';
  $handler->display->display_options['fields']['limit']['table'] = 'historical_course_data';
  $handler->display->display_options['fields']['limit']['field'] = 'limit';
  $handler->display->display_options['fields']['limit']['group_type'] = 'sum';
  $handler->display->display_options['fields']['limit']['label'] = 'limit';
  $handler->display->display_options['fields']['limit']['separator'] = '';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Program classification (field_program_classification) */
  $handler->display->display_options['sorts']['field_program_classification_target_id']['id'] = 'field_program_classification_target_id';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['table'] = 'field_data_field_program_classification';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['field'] = 'field_program_classification_target_id';
  $handler->display->display_options['sorts']['field_program_classification_target_id']['relationship'] = 'nid';
  $handler->display->display_options['path'] = 'cis/historical_college_data/program/enrollments';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Enrollments';
  $handler->display->display_options['menu']['weight'] = '2';
  $handler->display->display_options['menu']['name'] = 'management';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Export */
  $handler = $view->new_display('views_data_export', 'Export', 'views_data_export_1');
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'views_data_export_csv';
  $handler->display->display_options['path'] = 'historical_college_data/export';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'page_2' => 'page_2',
    'page_3' => 'page_3',
    'page_6' => 'page_6',
    'page_4' => 'page_4',
    'page_7' => 'page_7',
    'page_5' => 'page_5',
    'default' => 0,
  );
  $export['historical_college_data'] = $view;

  return $export;
}
