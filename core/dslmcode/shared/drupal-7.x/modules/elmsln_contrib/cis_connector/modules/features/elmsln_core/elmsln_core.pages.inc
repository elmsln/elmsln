<?php

/**
 * Callback to return all data about the current entity from
 * our xAPI / LRS data we can drum up that's meaningful.
 */
function elmsln_core_data_form() {
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
  $chart_style = (isset($_GET['chart_style']) ? filter_xss(check_plain($_GET['chart_style'])) : 'pie');
  $display = arg(3);
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
  if (isset($entity)) {
    $uri = entity_uri($etype, $entity);
    $url = url($uri['path'], array('absolute' => TRUE));
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
  else {
    // just filter to this course
    $query['pipeline'][0]['$match']['$or'][]['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course'] = _cis_connector_course_context();
    $query['pipeline'][0]['$match']['$or'][]['statement.object.definition.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-course'] = _cis_connector_course_context();
    $uri = array(
      'path' => current_path(),
    );
  }
  // statement filtering by verb
  if (!empty($filtered_verb)) {
        $filtertitle .= '<span class="chip">' . t('verb: @verb', array('@verb' => $filtered_verb)) . '</span>';

    $query['pipeline'][0]['$match']['statement.verb.display.en-US'] = $filtered_verb;
  }
  // only show role results requested if filtered
  if ($etype != 'user' && isset($_GET['role'])) {
    if (isset($roles[$_GET['role']]) && $_GET['role'] != 'all') {
      $role = $_GET['role'];
      $filtertitle .= '<span class="chip">' . t('role: @role', array('@role' => $role)) . '</span>';
      $query['pipeline'][0]['$match']['statement.context.extensions.https://www%2646;elmsln%2646;org/x-api/elmsln-role'] = $role;
    }
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
      // count verbs
      if (!isset($aggregates['counts'][$verb])) {
        $aggregates['counts'][$verb] = 0;
      }
      $aggregates['counts'][$verb]++;
      if (!isset($aggregates['users'][$verb][$record['statement']['actor']['name']])) {
        $aggregates['users'][$verb][$record['statement']['actor']['name']] = 0;
      }
      $aggregates['users'][$verb][$record['statement']['actor']['name']]++;
      $aggregates['user_list'][$record['statement']['actor']['name']] = NULL;
    }
  }
  // order from biggest to smallest xAPI counts
  uasort($aggregates['counts'], '_elmsln_uasortcmp');
  // load in the icon associations
  $icons = _elmsln_core_icon_map();
  foreach ($aggregates['verbs'] as $verb) {
    if (isset($icons[$verb])) {
      $aggregates['colors'][$verb] = $icons[$verb]['color'];
      $aggregates['icons'][$verb] = $icons[$verb]['icon'];
    }
    else {
      $aggregates['colors'][$verb] = ELMSLN_XAPI_DEFAULT_COLOR;
      $aggregates['icons'][$verb] = ELMSLN_XAPI_DEFAULT_ICON;
    }
    $aggregates['verb_data_links'][$verb] = $uri['path'] . '/data';
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
    $filtertitle = t('Filters applied:') . ' ' . $filtertitle;
  }
  // send off for theming
  $vars = array(
    'datatitle' => $datatitle,
    'filtertitle' => $filtertitle,
    'data' => $data,
    'aggregates' => $aggregates,
  );
  // kick out as table
  // @todo support other methods of visualizing data
  if ($display == 'table' || empty($display)) {
    $output .= theme('elmsln_core_lrs_data', $vars);
    drupal_add_js(drupal_get_path('module', 'elmsln_core') . '/js/elmsln-core-lrs-data-display.js');
  }
  // load up read time if it exists
  if ($etype == 'node' && module_exists('read_time') && user_access('view read time')) {
    $filters['read_time'] = array(
      '#type' => 'fieldset',
      '#title' => t('Read time stats'),
      '#collapsed' => TRUE,
      '#collapsible' => TRUE,
      '#weight' => -15,
      '#attributes' => array(
        'class' => array(
          'collapsible',
          'form-wrapper',
          'collapsed',
        ),
      ),
      '#materialize' => array(
        'type' => 'collapsible',
        'icon' => 'access_time',
      ),
      '#markup' => theme('read_time', array('node' => $entity)),
    );
  }

  $filters['visualizations'] = array(
    '#type' => 'fieldset',
    '#title' => t('Visualizations'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#weight' => -10,
    '#attributes' => array(
      'class' => array(
        'collapsible',
        'form-wrapper',
        'collapsed',
      ),
    ),
    '#materialize' => array(
      'type' => 'collapsible',
      'icon' => 'show_chart',
    ),
    'datacontainer' => array(
      '#type' => 'markup',
      '#markup' => '<div class="elmsln-data-container"><canvas id="lrs-data-chart" width="400" height="400"></canvas></div>',
    ),
  );
  // build simple visuals
  $values = $labels = $colors = array();
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
  shuffle($colorlist);
  foreach ($aggregates['counts'] as $label => $count) {
    $values[] = $count;
    $labels[] = $label;
    $colors[] = array_pop($colorlist);
  }
  $datajs = array(
    'elmslnCore' => array(
      'chart' => array(
        'data' => array(
          'values' => $values,
          'labels' => $labels,
        ),
        'style' => array(
          'type' => $chart_style,
          'borderWidth' => 1,
          'label' => t('xAPI statements'),
          'colors' => $colors,
        ),
      ),
    ),
  );
  drupal_add_js($datajs, array('type' => 'setting'));

  $filters['filter_data'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filters'),
    '#collapsed' => TRUE,
    '#collapsible' => TRUE,
    '#weight' => -9,
    '#attributes' => array(
      'class' => array(
        'collapsible',
        'form-wrapper',
        'collapsed',
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
      '#type' => 'select',
      '#title' => t('Role'),
      '#default_value' => $role,
      '#options' => $roles,
    );
  }
  $filters['filter_data']['chart_style'] = array(
    '#type' => 'select',
    '#title' => t('Chart style'),
    '#default_value' => $chart_style,
    '#options' => array(
      'pie' => t('Pie'),
      'bar' => t('Bar'),
    ),
  );
  $filters['filter_data']['verb'] = array(
    '#type' => 'select',
    '#title' => t('Verb'),
    '#default_value' => $filtered_verb,
    '#options' => array('' => t('All')) + $aggregates['verbs'],
  );
  $filters['filter_data']['actions']['#type'] = 'actions';
  $filters['filter_data']['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Apply filter'),
    '#id' => 'submit_filters',
  );
  $filters['filter_data']['actions']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset filters'),
    '#id' => 'reset_filters',
  );
  $form = array(
    'filter_fieldset' => array(
      '#type' => 'fieldset',
      '#materialize' => array(
        'type' => 'collapsible_wrapper'
      ),
      '#attributes' => array(
        'class' => array('collapsible', 'lrs-data-filters'),
        'data-collapsible' => 'accordion',
      ),
      'filters' => $filters,
    ),
    'markup' => array(
      '#type' => 'markup',
      '#markup' => $output,
    )
  );
  return $form;
}

/**
 * Implements submit callback for elmsln_core_data_form().
 */
function elmsln_core_data_form_submit($form, &$form_state) {
  // reset the form vs submit w/ the new filters applied
  if ($form_state['triggering_element']['#id'] == 'reset_filters') {
    drupal_goto(current_path());
  }
  else {
    $filters = array(
      'verb' => $form_state['values']['verb']
    );
    if (isset($form_state['values']['role'])) {
      $filters['role'] = $form_state['values']['role'];
    }
    if (isset($form_state['values']['chart_style'])) {
      $filters['chart_style'] = $form_state['values']['chart_style'];
    }
    drupal_goto(current_path(), array('query' => $filters));
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