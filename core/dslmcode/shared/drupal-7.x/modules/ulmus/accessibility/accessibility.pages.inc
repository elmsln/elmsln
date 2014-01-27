<?php

/**
 * Outputs settings and test information in JSON.
 */
function accessibility_tests_json($return = FALSE) {
  if(!$result = cache_get('accessibility_tests_json')) {
    $existing_tests = accessibility_get_active_tests();
    $accessibility_tests = module_invoke_all('accessibility_tests', FALSE);
    $result = array();
    foreach ($existing_tests as $test_id => $test) {
      $result[$test->quail_name] = $accessibility_tests[$test->quail_name];
      $result[$test->quail_name]['readableName'] = $test->name;
      $result[$test->quail_name]['testId'] = $test_id;
      $result[$test->quail_name]['tags'] = $accessibility_tests[$test->quail_name]['tags'];
    }
    cache_set('accessibility_tests_json', $result);
  }
  else {
    $result = $result->data;
  }
  if ($return) {
    return $result;
  }
  drupal_json_output(array('guideline' => array_keys($result), 'tests' => $result));
}