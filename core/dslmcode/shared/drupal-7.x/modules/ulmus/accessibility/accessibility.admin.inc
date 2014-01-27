<?php

/**
 * Helper function to get enabled tests.
 */
function _accessibility_admin_get_enabled_tests() {
  static $tests;
  if ($tests) {
    return $tests;
  }
  $tests = db_select('accessibility_test', 'a')
              ->fields('a', array('quail_name', 'name'))
              ->execute()
              ->fetchAllKeyed();
  return $tests;
}

/**
 * Form for importing tests. 
 */
function accessibility_tests_list($form, $form_state) {
  $library_path = libraries_get_path('quail');
  $options = array();
  $form = array();
  $tests = module_invoke_all('accessibility_tests', TRUE);

  $guidelines = module_invoke_all('accessibility_guidelines', TRUE);

  $session = isset($_SESSION['accessibility_tests_filter']) ? $_SESSION['accessibility_tests_filter'] : array();
  $form['filter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Filter tests'),
    '#collapsible' => TRUE,
  );

  $guideline_options = array();
  foreach($guidelines as $k => $guideline) {
    $guideline_options[$k] = $guideline['title'];
  }

  $form['filter']['guideline'] = array(
    '#type' => 'select',
    '#title' => t('Guideline'),
    '#options' => $guideline_options,
    '#default_value' => isset($session['guideline']) ? $session['guideline'] : '',
    '#empty_option' => t('-- Any --'),
  );

  $categories = array();
  foreach($tests as $test) {
    foreach($test['tags'] as $tag) {
      $categories[$tag] = $tag;
    }
  }
  ksort($categories);
  $form['filter']['category'] = array(
    '#type' => 'select',
    '#title' => t('Category'),
    '#options' => $categories,
    '#default_value' => isset($session['category']) ? $session['category'] : '',
    '#empty_option' => t('-- Any --'),
  );

  $form['filter']['severity'] = array(
    '#type' => 'select',
    '#title' => t('Severity'),
    '#options' => array(
        ACCESSIBILITY_TEST_SEVERE => t('Severe'),
        ACCESSIBILITY_TEST_MODERATE => t('Moderate'),
        ACCESSIBILITY_TEST_SUGGESTION => t('Suggestion'),
      ),
    '#default_value' => isset($session['severity']) ? $session['severity'] : '',
    '#empty_option' => t('-- Any --'),
  );

  $form['filter']['filter'] = array(
    '#type' => 'submit',
    '#value' => t('Filter'),
  );

  $form['filter']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
  );

  $enabled_tests = _accessibility_admin_get_enabled_tests();
  foreach ($tests as $testname => $test) {
    if (!isset($enabled_tests[$testname]) && 
       (!isset($session['category']) || !$session['category'] || in_array($session['category'], $test['tags'])) &&
       (!isset($session['guideline']) || !$session['guideline'] || in_array($testname, $guidelines[$session['guideline']]['tests'])) &&
       (!isset($session['severity']) || !$session['severity'] || $test['severity'] == $session['severity'])) {
      $options[$testname] = array('test' => $test['title'],
                                  'severity' => t(ucfirst($test['severity'])),
                                  'categories' => implode(', ', $test['tags']),
                                  );
    }
  }
  
  $header = array('test' => t('Test'),
                  'categories' => t('Categories'),
                  'severity' => t('Severity'),
                  );

  $form['tests'] = array(
    '#type' => 'tableselect',
    '#title' => t('Available accessibility tests'),
    '#options' => $options,
    '#header' => $header,
    '#default_value' => $enabled_tests,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import tests'),
  );
    
  return $form;
}

/**
 * Form submit callback for importing tests.
 */
function accessibility_tests_list_submit($form, &$form_state) {
  if($form_state['clicked_button']['#value'] == t('Filter')) {
    $_SESSION['accessibility_tests_filter'] = array(
      'guideline' => $form_state['values']['guideline'],
      'category' => $form_state['values']['category'],
      'severity' => $form_state['values']['severity'],
    );
    return;
  }
  if($form_state['clicked_button']['#value'] == t('Reset')) {
    $_SESSION['accessibility_tests_filter'] = array();
    return;
  }
  $tests = module_invoke_all('accessibility_tests', TRUE);
  $enabled_tests = _accessibility_admin_get_enabled_tests();
  $batch = array(
    'operations' => array(),
    'finished' => 'accessibility_tests_list_done',
    'title' => t('Importing tests'),
    'init_message' => t('Starting to import tests.'),
    'progress_message' => t('Imported @current out of @total.'),
    'error_message' => t('An error occurred while importing tests.'),
    'file' => drupal_get_path('module', 'accessibility') . '/accessibility.admin.inc',
  );
  foreach ($form_state['values']['tests'] as $test => $enabled) {
    if ($enabled && !isset($enabled_tests[$test])) {
      $batch['operations'][] = array('_accessibility_create_test_from_quail', array($test, $tests[$test]));
    }
  }

  batch_set($batch);
}

/**
 * Batch import finished callback.
 */
function accessibility_tests_list_done($success, $results, $operations) {
  if ($success) {
    // Here we do something meaningful with the results.
    $message = count($results) . ' imported.';
    $message .= theme('item_list', $results);
  }
  else {
    // An error occurred.
    // $operations contains the operations that remained unprocessed.
    $error_operation = reset($operations);
    $message = t('An error occurred while processing %error_operation with arguments: @arguments', array('%error_operation' => $error_operation[0], '@arguments' => print_r($error_operation[1], TRUE)));
  }
  drupal_set_message($message);
}

/**
 * Creates a test entity from a quail test.
 */
function _accessibility_create_test_from_quail($quail_name, $test, &$context) {
  $language = language_default();
  $new_test = new stdClass();
  $new_test->language = $language->language;
  $new_test->quail_name = $quail_name;
  $new_test->name = $test['title'];
  $new_test->severity = (isset($test['severity'])) ? $test['severity'] : 'suggestion';

  $wrapper = entity_metadata_wrapper('accessibility_test', $new_test);
  $wrapper->error_description->set(array('value'  => $test['description'],
                                         'format' => filter_default_format()
      ));
  $wrapper->save(TRUE);
  accessibility_test_save($new_test);
  $context['message'] = t('Done importing @name', array('@name' => $new_test->name));
  $context['results'][] = $new_test->name;
}

/**
 * List existing accessibility tests.
 * @todo - add a filter form
 */
function accessibility_admin_existing_tests() {
  $build = array('filter_form' => drupal_get_form('accessibility_admin_filter_form'));

  $header = array(t('Name'), t('Severity'), t('Status'), t('Edit'), t('Delete'));

  $rows = array();

  $query = db_select('accessibility_test', 't')
           ->fields('t', array('test_id', 'name', 'quail_name', 'severity', 'status'))
           ->orderBy('t.name');

  $filter = (isset($_SESSION['accessibility_admin_filter'])) ? $_SESSION['accessibility_admin_filter'] : array();
  if (isset($filter['severity'])) {
    $in = array();
    foreach ($filter['severity'] as $severity) {
      if ($severity) {
        $in[] = $severity;
      }
    }
    if (count($in)) {
      $query->condition('t.severity', $in, 'IN');
    }
  }
  if (isset($filter['name']) && strlen($filter['name'])) {
    $query->condition('t.name', '%' . $filter['name'] . '%', 'LIKE');
  }

  $tests = $query->execute()
                 ->fetchAll();
  foreach ($tests as $test) {
    $rows[] = array(l($test->name, 'accessibility-test/' . $test->test_id),
      t(ucfirst($test->severity)),
      (($test->status) ? t('Active') : t('Inactive')),
      l(t('edit'), 'accessibility-test/' . $test->test_id . '/edit', array('query' => array('destination' => 'admin/config/accessibility/tests'))),
      l(t('delete'), 'accessibility-test/' . $test->test_id . '/delete', array('query' => array('destination' => 'admin/config/accessibility/tests')))
    );
  }

  $build['result_table'] = array('#theme' => 'table',
                                 '#header' => $header,
                                 '#rows' => $rows,
                                 );
  if (!count($rows)) {
    $build['result_table'] = array('#markup' => t('No tests, found. !link.', array('!link' => l(t('Import tests'), 'admin/config/accessibility/tests/import'))));
  }
  return $build;
}

/**
 * Form to filter accessibility tests.
 */
function accessibility_admin_filter_form($form, $form_state) {
  $form = array();

  $filter = (isset($_SESSION['accessibility_admin_filter'])) ? $_SESSION['accessibility_admin_filter'] : array();

  $form['filters'] = array(
    '#type' => 'fieldset'
    );

  $form['filters']['name'] = array(
    '#title' => t('Test name contains'),
    '#type' => 'textfield',
    '#default_value' => (isset($filter['name']) ? $filter['name'] : array())
  );

  $form['filters']['severity'] = array(
    '#title' => t('Severity level'),
    '#type' => 'checkboxes',
    '#options' => array(
      ACCESSIBILITY_TEST_SEVERE => t('Severe'),
      ACCESSIBILITY_TEST_MODERATE => t('Moderate'),
      ACCESSIBILITY_TEST_SUGGESTION => t('Suggestion'),
    ),
    '#default_value' => (isset($filter['severity']) ? $filter['severity'] : array())
  );

  $form['filters']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Search'),
    );

  $form['filters']['reset'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    );

  return $form;
}

/**
 * Form submit callback for filter form.
 */
function accessibility_admin_filter_form_submit($form, $form_state) {
  $_SESSION['accessibility_admin_filter'] = $form_state['values'];
  if ($form_state['clicked_button']['#value'] == t('Reset')) {
    $_SESSION['accessibility_admin_filter'] = array();
  }
}