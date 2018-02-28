<?php

/**
 * Callback to return all data about the current entity from
 * our xAPI / LRS data we can drum up that's meaningful.
 */
function elmsln_core_data_form($form, $form_state) {
  if ($_GET['op'] == t('Reset filters')) {
    drupal_goto(current_path());
  }
  // form reposts to itself so ensure there's stuff to visualize here
  if (empty($form_state['input']) || isset($form_state['values']) || $form_state['input']['op'] == t('Reset filters') || $form_state['input']['op'] == t('Apply filters')) {
    // add in chartjs
    $libraries = libraries_get_libraries();
    if (isset($libraries['chartjs'])) {
      drupal_add_js(base_path() . $libraries['chartjs'] . '/Chart.min.js');
    }
    $etype = arg(0);
    $etid = arg(1);
    if (is_numeric($etid)) {
      $entity = entity_load_single($etype, $etid);
    }
    $filtered_verb = (isset($_GET['verb']) ? filter_xss(check_plain($_GET['verb'])) : '');
    $date_start = (isset($_GET['date_start']) ? filter_xss(check_plain($_GET['date_start'])) : '');
    $date_end = (isset($_GET['date_end']) ? filter_xss(check_plain($_GET['date_end'])) : '');
    $visualization = (isset($_GET['visualization']) ? filter_xss(check_plain($_GET['visualization'])) : 'pie');
    $limit = (isset($_GET['limit']) ? filter_xss(check_plain($_GET['limit'])) : 10);
    $sort = (isset($_GET['sort']) ? filter_xss(check_plain($_GET['sort'])) : -1);
    $pivot = (isset($_GET['pivot']) ? filter_xss(check_plain($_GET['pivot'])) : 'verb');
    $course = (isset($_GET['course']) ? filter_xss(check_plain($_GET['course'])) : _cis_connector_course_context());
    $program = (isset($_GET['program']) ? filter_xss(check_plain($_GET['program'])) : '-all-');
    $unit = (isset($_GET['unit']) ? filter_xss(check_plain($_GET['unit'])) : '-all-');
    $programs = _cis_connector_assemble_entity_list('node', 'program', 'nid', 'title');
    $units = _cis_connector_assemble_entity_list('node', 'academic_unit', 'nid', 'title');
    $course_filter = array();
    if (empty($course)) {
      $course = '-all-';
    }
    // allow for debugging mode
    $debug = (isset($_GET['debug']) ? true : false);
    $roles = array(
      'all' => t('All roles'),
      'student' => t('Student'),
      'staff' => t('Staff'),
      'teacher' => t('Teacher'),
      'other' => t('Other'),
    );
    $role = 'all';
    $aggregates = array(
      'verbs' => array(),
      'users' => array(),
      'counts' => array(),
      'icons' => array(),
      'colors' => array(),
      'user_list' => array(),
      'percent_used' => array(),
    );
    // make initial query scaffold we need for all calls for data
    $query = array(
      'pipeline' => array(
        array(
          '$match' => array(),
        ),
      )
    );
    $output = '';
    $filtertitle = '';
    $uri = array(
      'path' => current_path(),
    );
    if (isset($entity)) {
      $uri = entity_uri($etype, $entity);
      $url = url($uri['path'], array('absolute' => TRUE, 'alias' => TRUE));
      // show query data specific to the entity type in question
      switch ($etype) {
        case 'user':
          $query['pipeline'][0]['$match']['statement.actor.name'] = $entity->name;
          $filtertitle .= '<span class="chip">' . t('user: @user', array('@user' => $entity->name)) . '</span>';
        break;
        case 'node':
          $query['pipeline'][0]['$match']['$or'][]['statement.context.contextActivities.parent.id'] = $url;
          $query['pipeline'][0]['$match']['$or'][]['statement.object.id'] = $url;
          $query['pipeline'][0]['$match']['$or'][]['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-url'] = $url;
          $query['pipeline'][0]['$match']['$or'][]['statement.object.definition.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-url'] = $url;
          $filtertitle .= '<span class="chip">' . t('content: @content', array('@content' => drupal_get_title())) . '</span>';
        break;
      }
    }
    elseif (!empty($program) && $program != '-all-' && $course == '-all-') {
      $course_filter = array('field_program_classification' => array('target_id', $program));
      // oh programs, you are fun, this is the same as multiple courses at the same time
      $courses = _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title', $course_filter);
      // just filter to these courses which = program
      if (!empty($courses)) {
        $query['pipeline'][0]['$match']['$or'][]['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course']['$in'] = array_keys($courses);
        $query['pipeline'][0]['$match']['$or'][]['statement.object.definition.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course']['$in'] = array_keys($courses);
        $filtertitle .= '<span class="chip">' . t('program: @program', array('@program' => $programs[$program])) . '</span>';

      }
    }
    elseif (!empty($unit) && $unit != '-all-' && $course == '-all-') {
      $course_filter = array('field_academic_home' => array('target_id', $unit));
      // oh programs, you are fun, this is the same as multiple courses at the same time
      $courses = _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title', $course_filter);
      // just filter to these courses which = unit
      if (!empty($courses)) {
        $query['pipeline'][0]['$match']['$or'][]['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course']['$in'] = array_keys($courses);
        $query['pipeline'][0]['$match']['$or'][]['statement.object.definition.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course']['$in'] = array_keys($courses);
        $filtertitle .= '<span class="chip">' . t('unit: @unit', array('@unit' => $units[$unit])) . '</span>';
      }
    }
    elseif (!empty($course) && $course != '-all-') {
      // just filter to this course
      $query['pipeline'][0]['$match']['$or'][]['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course'] = $course;
      $query['pipeline'][0]['$match']['$or'][]['statement.object.definition.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course'] = $course;
      $filtertitle .= '<span class="chip">' . t('course: @course', array('@course' => $course)) . '</span>';
    }
    // statement filtering by verb
    if (!empty($filtered_verb)) {
          $filtertitle .= '<span class="chip">' . t('verb: @verb', array('@verb' => $filtered_verb)) . '</span>';

      $query['pipeline'][0]['$match']['statement.verb.display.en-US'] = $filtered_verb;
    }
    else {
      // ignore pause, it's worthless by itself
      $query['pipeline'][0]['$match']['statement.verb.display.en-US'] = array('$nin' => array('paused', 'progressed'));
    }
    // filter based on date if it's set to do so
    if (!empty($date_start)) {
       $query['pipeline'][0]['$match']['statement.timestamp']['$gt'] = $date_start . 'T00:00:00.000000+00:00';
        $filtertitle .= '<span class="chip">' . t('date start: @date_start', array('@date_start' => $date_start)) . '</span>';
    }
    if (!empty($date_end)) {
       $query['pipeline'][0]['$match']['statement.timestamp']['$lt'] = $date_end . 'T00:00:00.000000+00:00';
        $filtertitle .= '<span class="chip">' . t('date end: @date_end', array('@date_end' => $date_end)) . '</span>';

    }
    // only show role results requested if filtered
    if ($etype != 'user' && isset($_GET['role'])) {
      if (isset($roles[$_GET['role']]) && $_GET['role'] != 'all') {
        $role = filter_xss($_GET['role']);
        $filtertitle .= '<span class="chip">' . t('role: @role', array('@role' => $role)) . '</span>';
        $query['pipeline'][0]['$match']['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-role'] = $role;
      }
      if (isset($_GET['user_filter']) && $_GET['user_filter'] != '') {
        $user_filter = filter_xss($_GET['user_filter']);
        $users = explode(',', $user_filter);
        $filtertitle .= '<span class="chip">' . t('user: @userfilter', array('@userfilter' => $user_filter)) . '</span>';
        $query['pipeline'][0]['$match']['statement.actor.name']['$in'] = $users;
      }
    }
    // apply active section context if one exists
    if (module_exists('cis_section')) {
      $section = (isset($_GET['section']) ? filter_xss(check_plain($_GET['section'])) : _cis_connector_section_context());
    }
    else {
      $section = (isset($_GET['section']) ? filter_xss(check_plain($_GET['section'])) : '-all-');
    }
    // only show active section data if selected
    if ($section != '-all-') {
      $query['pipeline'][0]['$match']['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-section'] = $section;
      $filtertitle .= '<span class="chip">' . t('section: @section', array('@section' => $section)) . '</span>';
    }
    // sort based on time stamp in whatever order
    $query['pipeline'][] = array('$sort' => array('statement.timestamp' => (int)$sort));
    $filtertitle .= '<span class="chip">' . t('sort results: @sort', array('@sort' => ($sort == -1 ? t('newest to oldest') : t('oldest to newest')))) . '</span>';
    // allow for response limiting to avoid flooding
    if ($limit != 0) {
      $query['pipeline'][] = array('$limit' => (int)$limit);
      $query['pipeline'][]['$limit'] = (int)$limit;
      $filtertitle .= '<span class="chip">' . t('limit results: @limit', array('@limit' => $limit)) . '</span>';
    }
    // if in debug mode, print it to the screen
    if ($debug) {
      dpm($query);
    }
    $query['pipeline'] = json_encode($query['pipeline']);
    $result = _elmsln_core_lrs_query($query, FALSE);
    // start cleaning up the data to make it more useful downstream
    $data = $result['result'];
    if (!empty($data)) {
      foreach ($data as $key => $record) {
        // engineer verb agnostic of language
        $verb = t($record['statement']['verb']['display']['en-US']);
        $aggregates['verbs'][$verb] = $verb;
        if (!url_is_external(str_replace($GLOBALS['base_url'], '', $record['statement']['object']['id']))) {
          $item_link = $record['statement']['object']['id'];
        }
        elseif (isset($record['statement']['context']['contextActivities']['parent'][0]['id'])) {
          $item_link = $record['statement']['context']['contextActivities']['parent'][0]['id'];
        }
        elseif (isset($record['statement']['context']['extensions']['https://www.elmsln.org/x-api/elmsln-url'])) {
          $item_link = $record['statement']['context']['extensions']['https://www.elmsln.org/x-api/elmsln-url'];
        }
        elseif (isset($record['statement']['object']['definition']['extensions']['https://www.elmsln.org/x-api/elmsln-url'])) {
          $item_link = $record['statement']['object']['definition']['extensions']['https://www.elmsln.org/x-api/elmsln-url'];
        }
        else {
          $item_link = NULL;
        }
        $record['_item_link'] = $item_link;
        $aggregates['statements'][$verb][] = $record;
          // count based on pivot
        switch ($pivot) {
          case 'verb':
            if (!isset($aggregates['counts'][0][$verb])) {
              $aggregates['counts'][0][$verb] = array(
                'title' => $verb,
                'value' => 0,
                'verb' => $verb,
              );
            }
            $aggregates['counts'][0][$verb]['value']++;
          break;
          case 'h5p':
            // look for an answered H5P statement
            if ($verb == 'answered' && isset($record['statement']['context']['contextActivities']['category'][0]['id'])) {
              $itemtype = $record['statement']['context']['contextActivities']['category'][0]['id'];
              $item = $record['statement']['object']['definition']['description']['en-US'];
              // support for multiple choice / known quantity items
              if (isset($record['statement']['object']['definition']['choices'])) {
                // make sure we started recording these answers
                if (!isset($aggregates['counts'][$item])) {
                  // loop through possible choices
                  foreach ($record['statement']['object']['definition']['choices'] as $choice) {
                    // extract each possible option
                    $option = check_plain(trim($choice['description']['en-US']));
                    // see if the current option is part of the 'correct' response
                    if (in_array($choice['id'], $record['statement']['object']['definition']['correctResponsesPattern'])) {
                      $option = $option . ' ' . t('[correct]');
                    }
                    // set option as empty so we at least have a bucket for it existing
                    $aggregates['counts'][$item][$choice['id']] = array(
                      'title' => $option,
                      'value' => 0,
                      'verb' => $verb,
                    );
                  }
                }
                if (isset($record['statement']['result']['response']) && is_numeric($record['statement']['result']['response'])) {
                  $aggregates['counts'][$item][$record['statement']['result']['response']]['value']++;
                }
              }
              // support for H5P Fill in the blank
              elseif (strpos($itemtype, 'H5P.Blanks')) {
                if (isset($record['statement']['result']['response'])) {
                  if (!isset($aggregates['counts'][$item][$record['statement']['result']['response']])) {
                    $response = check_plain(trim($record['statement']['result']['response']));
                    if ($record['statement']['result']['score']['scaled'] == 1) {
                      $response .= t('[correct]');
                    }
                    $aggregates['counts'][$item][$record['statement']['result']['response']] = array(
                      'title' => $response,
                      'value' => 0,
                      'verb' => $verb,
                    );
                  }
                  $aggregates['counts'][$item][$record['statement']['result']['response']]['value']++;
                }
              }
              // support for H5P TrueFalse in the blank
              elseif (strpos($itemtype, 'H5P.TrueFalse')) {
                if (isset($record['statement']['result']['response'])) {
                  if (!isset($aggregates['counts'][$item][$record['statement']['result']['response']])) {
                    $response = check_plain(trim($record['statement']['result']['response']));
                    if ($record['statement']['result']['score']['scaled'] == 1) {
                      $response .= t('[correct]');
                    }
                    $aggregates['counts'][$item][$record['statement']['result']['response']] = array(
                      'title' => $response,
                      'value' => 0,
                      'verb' => $verb,
                    );
                  }
                  $aggregates['counts'][$item][$record['statement']['result']['response']]['value']++;
                }
              }
            }
          break;
        }
        if (!isset($aggregates['users'][$verb][$record['statement']['actor']['name']])) {
          $aggregates['users'][$verb][$record['statement']['actor']['name']] = 0;
        }
        $aggregates['users'][$verb][$record['statement']['actor']['name']]++;
        $aggregates['user_list'][$record['statement']['actor']['name']] = NULL;
      }
    }
    // order from biggest to smallest xAPI counts
    //uasort($aggregates['counts'], '_elmsln_uasortcmp');
    // load in the icon associations
    $icons = _elmsln_core_icon_map();
    $descriptions = array();
    if (module_exists('elmsln_lrs')) {
      $descriptions = _elmsln_lrs_verb_descriptions();
    }
    foreach ($aggregates['verbs'] as $verb) {
      if (isset($icons[$verb])) {
        $aggregates['colors'][$verb] = $icons[$verb]['color'];
        $aggregates['icons'][$verb] = $icons[$verb]['icon'];
      }
      else {
        $aggregates['colors'][$verb] = ELMSLN_XAPI_DEFAULT_COLOR;
        $aggregates['icons'][$verb] = ELMSLN_XAPI_DEFAULT_ICON;
      }
      if (isset($descriptions[$verb])) {
        $aggregates['descriptions'][$verb] = $descriptions[$verb];
      }
      else {
        $aggregates['descriptions'][$verb] = array(
          'title' => ucfirst($verb),
          'description' => '',
        );
      }
      if (isset($entity)) {
        $aggregates['verb_data_links'][$verb] = $uri['path'] . '/data';
      }
      else {
        $aggregates['verb_data_links'][$verb] = $uri['path'];
      }
      $aggregates['percent_used'][$verb] = 100 * round(count($aggregates['users'][$verb]) / count($aggregates['user_list']), 2);
    }
    foreach ($aggregates['user_list'] as $tmpname => $val) {
      // try loading a user by name
      if ($tmpuser = user_load_by_name($tmpname)) {
        $aggregates['user_list'][$tmpname] = $tmpuser->uid;
      }
    }
    $datatitle = t('@statements statements generated by @users users.', array('@statements' => count($data), '@users' => count($aggregates['user_list'])));
    if (empty($filtertitle)) {
      $filtertitle = '';
    }
    else {
      $filtertitle = t('Filters:') . ' ' . $filtertitle;
    }
    // send off for theming
    $vars = array(
      'data' => $data,
      'aggregates' => $aggregates,
    );
    drupal_add_js(drupal_get_path('module', 'elmsln_core') . '/js/elmsln-core-lrs-data-display.js');
    // kick out as table
    if ($visualization == 'table') {
      $output .= theme('elmsln_core_lrs_data', $vars);
    }
    else {
      // colorlist of just a bunch of options that will look ok
    $colorlist = array(
      '#f44336',
      '#e91e63',
      '#9c27b0',
      '#673ab7',
      '#3f51b5',
      '#2196f3',
      '#03a9f4',
      '#00bcd4',
      '#009688',
      '#4caf50',
      '#8bc34a',
      '#cddc39',
      '#ffeb3b',
      '#ffc107',
      '#ff9800',
      '#ff5722',
      '#795548',
      '#607d8b',
    );
    $visualizations = array(
      '#type' => 'fieldset',
      '#title' => t('Visualizations'),
      '#collapsed' => FALSE,
      '#collapsible' => TRUE,
      '#weight' => -14,
      '#attributes' => array(
        'class' => array(
          'collapsible',
          'form-wrapper',
        ),
      ),
      '#materialize' => array(
        'type' => 'collapsible',
        'icon' => 'show_chart',
      ),
      'datacontainer' => array(
        '#type' => 'markup',
        '#markup' => '<div class="row elmsln-data-container">',
      ),
    );
    // container for the chart data
    $datajs = array(
      'elmslnCore' => array(
        'charts' => array()
      ),
    );
      // build simple visuals
      $values = $labels = $colors = array();
      foreach ($aggregates['counts'] as $charttitle => $item) {
        $colorlisttmp = $colorlist;
        shuffle($colorlisttmp);
        $visualizations['datacontainer']['#markup'] .= '<div class="col s12 m6 l4"><canvas class="lrs-data-chart" width="100" height="100"></canvas></div>';
        foreach ($item as $data) {
          $values[$charttitle][] = $data['value'];
          $labels[$charttitle][] = $data['title'];
          $colors[$charttitle][] = array_pop($colorlisttmp);
        }
        $datajs['elmslnCore']['charts'][] = array(
          'title' => strip_tags(trim($charttitle)),
          'data' => array(
            'values' => $values[$charttitle],
            'labels' => $labels[$charttitle],
          ),
          'style' => array(
            'type' => $visualization,
            'borderWidth' => 1,
            'label' => $charttitle,
            'colors' => $colors[$charttitle],
          ),
        );
      }
      // end cap
      $visualizations['datacontainer']['#markup'] .= '</div>';
      // apply the chart settings to the document
      drupal_add_js($datajs, array('type' => 'setting'));
    }

    $filters['filter_data'] = array(
      '#type' => 'fieldset',
      '#title' => t('Filters'),
      '#collapsed' => FALSE,
      '#collapsible' => TRUE,
      '#weight' => -9,
      '#attributes' => array(
        'class' => array(
          'collapsible',
          'form-wrapper',
          'collapsed'
        ),
      ),
      '#materialize' => array(
        'type' => 'collapsible',
        'icon' => 'filter_list',
      ),
    );
    // ensure users have advanced permissions before displaying
    if ($etype != 'user' && user_access('view elmsln lrs data')) {
      $filters['filter_data']['role'] = array(
        '#prefix' => '<div class="row"><div class="col s12 m6 l6">',
        '#suffix' => '</div>',
        '#type' => 'select',
        '#title' => t('Role'),
        '#default_value' => $role,
        '#options' => $roles,
      );
      $filters['filter_data']['user_filter'] = array(
        '#prefix' => '<div class="col s12 m6 l6">',
        '#suffix' => '</div></div>',
        '#type' => 'textfield',
        '#title' => t('User(s)'),
        '#placeholder' => t('Use , for multiple users'),
        '#default_value' => $user_filter,
      );
    }
    $sections = array('-all-' => t('All data'));
    // check that this is a section based system
    if (_cis_connector_system_type() == 'service') {
      // assemble all active sections of the current user
      $sections += cis_section_all_sections(FALSE, TRUE);
    }
    // CIS specialized part of data model
    elseif (elmsln_core_get_profile_key() == 'cis') {
      // CIS has programs which are complicated but can filter course options as groups
      $filters['filter_data']['unit'] = array(
        '#prefix' => '<div class="row"><div class="col s12 m6 l6">',
        '#suffix' => '</div>',
        '#type' => 'select',
        '#title' => t('Unit'),
        '#default_value' => $unit,
        '#options' => array('-all-' => t('All units')) + $units,
      );
      // CIS has programs which are complicated but can filter course options as groups
      $filters['filter_data']['program'] = array(
        '#prefix' => '<div class="col s12 m6 l6">',
        '#suffix' => '</div></div>',
        '#type' => 'select',
        '#title' => t('Program'),
        '#default_value' => $program,
        '#options' => array('-all-' => t('All programs')) + $programs,
      );
      // we need a course first
      $filters['filter_data']['course'] = array(
        '#type' => 'select',
        '#title' => t('Course'),
        '#default_value' => $course,
        '#options' => array('-all-' => t('All courses')) + _cis_connector_assemble_entity_list('node', 'course', 'field_machine_name', 'title', $course_filter),
      );
      // if we have a specific course then we can add in the sections from it
      if ($course != '-all-') {
        $results = _cis_helper_course_access_strings($course);
        if (!empty($results)) {
          $sections += $results;
        }
      }
    }
    elseif (_cis_connector_system_type() == 'authority') {
      // we need a course first
      $filters['filter_data']['course'] = array(
        '#type' => 'select',
        '#title' => t('Course'),
        '#default_value' => $course,
        '#options' =>  array('-all-' => t('All courses')) + _cis_connector_assemble_entity_list('node', 'cis_course', 'field_course_machine_name', 'title'),
      );
      // many authorities use this but don't have to
      if (module_exists('cis_section')) {
        // get section listing from CIS if anything comes across
        $results = _cis_connector_assemble_entity_list('node', 'section', 'field_section_id', 'title');
        if (!empty($results)) {
          $sections += $results;
        }
      }
    }
    // make sure we actually have sections to both bringing in this filter
    if (count($sections) > 1) {
      $filters['filter_data']['section'] = array(
        '#type' => 'select',
        '#title' => t('Section'),
        '#default_value' => $section,
        '#options' => $sections,
      );
    }
    $filters['filter_data']['date_start'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="row"><div class="col s12 m6 l6"><label for="date_start" class="">' . t('Start date') . '</label><input type="date" class="datepicker" name="date_start" id="date_start" value="' . $date_start . '"/></div>',
      '#title' => t('Date start'),
    );
    $filters['filter_data']['date_end'] = array(
      '#type' => 'markup',
      '#markup' => '<div class="col s12 m6 l6"><label for="date_end" class="">' . t('End date') . '</label><input type="date" class="datepicker" name="date_end" id="date_end" value="' . $date_end . '"/></div></div>',
      '#title' => t('Date end'),
    );
    $filters['filter_data']['pivot'] = array(
      '#prefix' => '<div class="row"><div class="col s12 m6 l6">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#title' => t('Pivot'),
      '#default_value' => $pivot,
      '#options' => array(
        'verb' => t('Verb centric'),
        'h5p' => t('H5P response data'),
        //'session' => t('Session centric'),
        //'video' => t('Video based data'),
      ),
    );
    $filters['filter_data']['visualization'] = array(
      '#prefix' => '<div class="col s12 m6 l6">',
      '#suffix' => '</div></div>',
      '#type' => 'select',
      '#title' => t('Visualization'),
      '#default_value' => $visualization,
      '#options' => array(
        'pie' => t('Pie chart'),
        'bar' => t('Bar chart'),
        'table' => t('Table by verb'),
      ),
    );
    $filters['filter_data']['verb'] = array(
      '#prefix' => '<div class="row"><div class="col s12 m4 l4">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#title' => t('Verb'),
      '#default_value' => $filtered_verb,
      '#options' => array('' => t('All')) + $aggregates['verbs'],
    );
    $filters['filter_data']['limit'] = array(
      '#prefix' => '<div class="col s12 m4 l4">',
      '#suffix' => '</div>',
      '#type' => 'select',
      '#title' => t('Limit'),
      '#default_value' => $limit,
      '#options' => array(
        0 => t('All results'),
        10 => t('1 result'),
        10 => t('10 results'),
        100 => t('100 results'),
        1000 => t('1,000 results'),
        2000 => t('2,000 results'),
      ),
    );
    $filters['filter_data']['sort'] = array(
      '#prefix' => '<div class="col s12 m4 l4">',
      '#suffix' => '</div></div>',
      '#type' => 'select',
      '#title' => t('Sort'),
      '#default_value' => $sort,
      '#options' => array(
        -1 => t('Newest to oldest'),
        1 => t('Oldest to newest'),
      ),
    );

    $filters['filter_data']['actions']['#type'] = 'actions';
    $filters['filter_data']['actions']['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Apply filters'),
      '#id' => 'submit_filters',
    );
    $filters['filter_data']['actions']['reset'] = array(
      '#type' => 'submit',
      '#value' => t('Reset filters'),
      '#id' => 'reset_filters',
    );
    $form = array(
      'header' => array(
        '#type' => 'markup',
        '#markup' => '<h2>' . $datatitle . '</h2>
        <div>' . $filtertitle .'</div>',
      ),
    );
    $form['filter_fieldset'] = array(
      '#type' => 'fieldset',
      '#materialize' => array(
        'type' => 'collapsible_wrapper'
      ),
      '#attributes' => array(
        'class' => array('collapsible', 'lrs-data-filters', 'col', 's12'),
        'data-collapsible' => 'accordion',
      ),
      'filters' => $filters,
    );
    $form['visualization_fieldset'] = array(
      '#type' => 'fieldset',
      '#materialize' => array(
        'type' => 'collapsible_wrapper'
      ),
      '#attributes' => array(
        'class' => array('collapsible', 'lrs-data-visualizations', 'col', 's12'),
        'data-collapsible' => 'accordion',
      ),
      'visualizations' => $visualizations,
    );
    $form['markup'] = array(
      '#type' => 'markup',
      '#markup' => $output,
    );
    $form['#method'] = 'GET';
    return $form;
  }
}

/**
 * callback for uasort comparison of array values
 */
function _elmsln_uasortcmp($a, $b) {
    if ($a == $b) {
        return 0;
    }
    return ($a > $b) ? -1 : 1;
}