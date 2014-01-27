<?php
/**
 * @file
 * Features integration for default config.
 */

/**
 * Implements hook_features_export_options().
 */
function defaultconfig_features_export_options() {
  $options = array();
  $components = defaultconfig_get_components();
  foreach ($components as $component_name => $component) {
    if (isset($component['features component'])) {
      module_load_include('inc', 'features', 'features.export');
      $components = features_invoke($component['features component'], 'features_export_options');
      // Find all default components that are not provided by this feature and
      // strip them out of the possible options.
      $map = features_get_default_map($component['features component']);
      if (isset($map) && is_array($map)) {
        foreach ($map as $k => $v) {
          if (isset($components[$k])) {
            unset($components[$k]);
          }
        }
      }
      foreach (array_keys($components) as $default_name) {
        $options[$component_name . ':' . $default_name] = $component['label'] . ': ' . $default_name;
      }
    }
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function defaultconfig_features_export($data, &$export, $module_name = '') {
  foreach ($data as $component) {
    $export['features']['defaultconfig'][$component] = $component;
  }
  $export['dependencies'][] = 'defaultconfig';
  return $export;
}

/**
 * Implements hook_features_export_render().
 */
function defaultconfig_features_export_render($module, $data, $export = NULL) {
  module_load_include('export.inc', 'features');
  $items = array();
  $components = defaultconfig_get_components();
  $functions = array();
  $types[$module] = array();
  foreach ($data as $name) {
    list($type, $configurable) = explode(':', $name);
    if (!isset($data[$type])) {
      $items[$type][$configurable] = $configurable;
      $types[$module][$type] = $type;
    }
  }
  $types_code = features_var_export($types, '  ');
  $functions['defaultconfig_features'] = "  return {$types_code};";
  foreach ($items as $type => $configurables) {
    $type_functions = features_invoke($components[$type]['features component'], 'features_export_render', $module, $configurables, $export);
    foreach ($type_functions as $code) {
      $functions[$components[$type]['hook']] = $code;
    }
  }
  return $functions;
}

/**
 * Implements hook_features_revert().
 */
function defaultconfig_features_revert($module) {
}

/**
 * Implements hook_features_rebuild().
 */
function defaultconfig_features_rebuild($module) {
}

