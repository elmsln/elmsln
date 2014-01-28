<?php
/**
 * @file
 * Additional hooks for features support.
 */

/**
 * Implements hook_features_export_options().
 */
function user_progress_features_export_options() {
  $options = array();
  foreach (user_progress_registry_load_all() as $template) {
    $options[$record['name']] = $record['title'];
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function user_progress_features_export($data, &$export, $module_name) {
  $export['dependencies']['features'] = 'features';
  $export['dependencies']['user_progress'] = 'user_progress';
  foreach ($data as $component) {
    $export['features']['user_progress'][$component] = $component;
  }
  return array();
}

/**
 * Implements hook_features_export_render().
 */
function user_progress_features_export_render($module_name, $data, $export = NULL) {
  $code = array();
  $code[] = '  $record = array();';
  foreach ($data as $upregid) {
    $code[] = "  \$record['{$name}'] = " . features_var_export(user_progress_registry_load($upregid), '  ') . ";";
  }
  $code[] = "  return \$record;";
  $code = implode("\n", $code);
  return array('user_progress_default_records' => $code);
}

/**
 * Implements hook_features_revert().
 */
function user_progress_features_revert($module) {
  return user_progress_features_rebuild($module);
}

/**
 * Implements hook_features_rebuild().
 */
function user_progress_features_rebuild($module) {
  if ($defaults = features_get_default('user_progress', $module)) {
    foreach ($defaults as $record) {
      user_progress_registry_save($record);
    }
  }
}