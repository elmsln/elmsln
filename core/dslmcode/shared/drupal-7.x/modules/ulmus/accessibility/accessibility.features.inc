<?php


/**
 * Implements hook[component]_features_export().
 */
function accessibility_test_features_export($data, &$export, $module_name) {
  if(!function_exists($module_name . 'accessibility_test_default')) {
    module_load_include('inc', $module_name, $module_name .'.accessibility_test');
  }
  foreach ($data as $component) {
    $export['features']['accessibility_test'][$component] = $component;
  }
  return array();
}

/**
 * Implements hook[component]_features_export_options().
 */
function accessibility_test_features_export_options() {
  $options = array();
  $tests = accessibility_get_active_tests();
  $return = array();
  foreach($tests as $test) {
  	$return[$test->quail_name] = $test->name;
  }
  return $return;
}

/**
 * Implements hook[component]_features_export_render().
 */
function accessibility_test_features_export_render($module_name, $data, $export = NULL) {
  if(!function_exists($module_name . 'accessibility_test_default')) {
    module_load_include('inc', $module_name, $module_name .'.accessibility_test');
  }
  $code = array();
  $code[] = '$accessibility_tests = array();';
  foreach ($data as $name) {
  	$id = accessibility_get_test_by_machine_name($name);
  	$test = accessibility_test_load($id);
  	unset($test->test_id);
  	unset($test->created);
  	unset($test->changed);
  	unset($test->rdf_mapping);
    $code[] = "\$accessibility_tests['{$name}'] = (object)" . features_var_export($test) .";";
  }
  $code[] = "return \$accessibility_tests;";
  $code = implode("\n", $code);
  return array('accessibility_test_default' => $code);
}

/**
 * Implements hook[component]_features_revert().
 */
function accessibility_test_features_revert($module_name) {
  accessibility_test_features_rebuild($module_name);
}

/**
 * Implements hook[component]_features_rebuild().
 */
function accessibility_test_features_rebuild($module_name) {
  if(!function_exists($module_name . 'accessibility_test_default')) {
    module_load_include('inc', $module_name, $module_name .'.accessibility_test');
  }
  $accessibility_tests = module_invoke($module_name, 'accessibility_test_default');
  if (!empty($accessibility_tests)) {
    foreach ($accessibility_tests as $machine_name => $accessibility_test) {
      $id = accessibility_get_test_by_machine_name($machine_name);
      if($id) {
	      $accessibility_test->test_id = $id;
      }
      $accessibility_test->changed = time();
      $accessibility_test->created = time();
      accessibility_test_save($accessibility_test);
    }
  }
}