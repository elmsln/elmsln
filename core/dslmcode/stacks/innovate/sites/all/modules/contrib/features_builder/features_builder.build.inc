<?php

/**
 * @file
 * Features Builder building code.
 */

/**
 * Gets the list of builders and components.
 *
 * @return array
 *   Components included by the builders, keyed by builder.
 */
function features_builder_get_manifest() {

  // module_load_include('inc', 'features_builder', 'features_builder.build');

  $manifest = array();
  $features = features_builder_get_features();

  foreach ($features as $feature => $builder) {
    $class = features_builder_get_class($builder, $feature);
    $component_types = $class->components();
    foreach ($component_types as $type => $components) {
      if (!empty($components)) {
        $manifest[$feature][$type] = $components;
      }
    }
  }

  return $manifest;
}

/**
 * Generate an "info" declaration as used by Features.
 *
 * @param string $feature
 *   The name of the Features Builder feature.
 * @param array $component_types
 *   Component type array.
 *
 * @return array
 *   Features info array.
 */
function features_builder_get_build_info($feature, $component_types) {
  $info = array();

  $features = features_builder_get_features();
  $builder = features_builder_get_class($features[$feature], $feature);

  $info['name'] = $builder->label();
  $info['package'] = $builder->package();

  foreach ($component_types as $type => $components) {
    // Handle dependencies and features_exclude differently.
    switch ($type) {
      case 'dependencies':
        $info['dependencies'] = array_keys($components);
        break;
      case 'features_exclude':
        $info['features_exclude'] = $components;
        break;
      default:
        $info['features'][$type] = array_keys($components);
    }
  }

  return $info;
}

/**
 * Produce a Features "export" array.
 *
 * @param $feature
 *   The name of the Features Builder feature.
 * @param $component_types
 *   The component type array.
 *
 * @return array
 *   A Features export array.
 */
function features_builder_get_build_export($feature, $component_types) {
  module_load_include('inc', 'features', 'features.export');
  $info = features_builder_get_build_info($feature, $component_types);
  $module_name =  variable_get('features_builder_prefix_name') . '_' . $feature;
  $export = features_populate($info, $module_name);
  return $export;
}

/**
 * Finds components added to the export by Features.
 *
 * @param array $export
 *   The Features export array.
 * @param array $component_types
 *   Component types array provided by the builder.
 *
 * @return array
 *   An array of components, keyed by component type.
 */
function features_builder_build_diff($export, $component_types) {
  $diff = array();

  foreach ($export['features'] as $type => $exp) {
    if (!array_key_exists($type, $component_types)) {
      $diff[$type] = $exp;
    } else {
      if ($type_diff = array_diff_key($exp, $component_types[$type])) {
        $diff[$type] = $type_diff;
      }
    }
  }

  return $diff;
}

/**
 * Identify dependencies between components included by the builders.
 *
 * @param array $manifest
 *   A manifest array.
 *
 * @return array
 *   An array of dependencies, keyed by feature. Values are arrays of the
 *   component's owner, keyed by "component_type|component".
 */
function features_builder_build_get_dependencies($manifest) {
  $dependencies = array();

  foreach ($manifest as $feature => $component_types) {
    $export = features_builder_get_build_export($feature, $component_types);
    $diff = features_builder_build_diff($export, $component_types);

    foreach ($diff as $type => $components) {
      foreach ($components as $component => $val) {
        if ($owner = features_builder_find_feature($type, $component, $manifest)) {
          $dependencies[$feature]["$type|$component"] = $owner;
        }
      }
    }
  }

  return $dependencies;
}

/**
 * Set dependencies into the manifest.
 *
 * @param $manifest
 *   A manifest array.
 * @param $dependencies
 *   A dependency array.
 *
 * @return array
 *   An updated manifest with dependencies set.
 */
function features_builder_build_set_dependencies($manifest, $dependencies) {
  $prefix = variable_get('features_builder_prefix_name') . '_';

  foreach ($dependencies as $feature => $feature_dependencies) {
    foreach ($feature_dependencies as $component => $dependency) {
      $dependency = $prefix . $dependency;
      $manifest[$feature]['dependencies'][$dependency] = $dependency;
      list($component_type, $name) = explode('|', $component);
      $manifest[$feature]['features_exclude'][$component_type][] = $name;
    }
  }

  return $manifest;
}

/**
 * Determine the order in which the Features should be built.
 *
 * @param $manifest
 *   A manifest array.
 * @param $dependencies
 *   A dependency array.
 *
 * @return array
 *   An updated manifest ordered as needed to meet dependencies.
 */
function features_builder_build_order_manifest($manifest, $dependencies) {
  $order = array();
  $features = array_keys($manifest);

  $continue = TRUE;

  while (!empty($features) && $continue) {
    $count = count($order);
    foreach ($features as $key => $feature) {
      $diff = !empty($dependencies[$feature]) ? array_diff($dependencies[$feature], $order) : array();

      if (empty($diff)) {
        $order[] = $feature;
        unset($features[$key]);
      }
    }

    // Insure we've added at least one feature to the list before running
    // through the list again.
    $continue = count($order) != $count;
  }

  // Build a new array in the order we just computed.
  $new_manifest = array();
  foreach ($order as $feature) {
    $new_manifest[$feature] = $manifest[$feature];
  }

  return $new_manifest;
}

/**
 * Find the Feature which includes a specific component.
 *
 * @param string $component_type
 *   Name of the component type.
 * @param string $component
 *   Name of the component.
 * @param array $manifest
 *   The component type manifest array.
 *
 * @return string
 *   The name of the Features Builder feature module which contains a component.
 */
function features_builder_find_feature($component_type, $component, $manifest) {
  $data = &drupal_static(__FUNCTION__, array());

  if (isset($data[$component_type][$component])) {
    return $data[$component_type][$component];
  }

  foreach ($manifest as $feature => $component_types) {
    if (isset($component_types[$component_type][$component])) {
      $data[$component_type][$component] = $feature;
      return $feature;
    }
  }

  $data[$component_type][$component] = NULL;
}

/**
 * Write the Feature.
 *
 * @param string $feature
 *   The machine name of the Features Builder feature being built.
 * @param array $component_types
 *   Array keyed by component types, containing an array of component names.
 */
function features_builder_build($feature, $component_types) {

  $module_name =  variable_get('features_builder_prefix_name') . '_' . $feature;

  features_get_modules(NULL, TRUE);

  $export = features_builder_get_build_export($feature, $component_types);

  // Force stuff in explicitly declared by the builder.
  foreach ($component_types as $type => $components) {
    foreach ($components as $component => $label) {
      $export['features'][$type][$component] = $component;
    }
    ksort($export['features'][$type]);
  }

  if (isset($export['features']['dependencies'])) {
    $export['dependencies'] += $export['features']['dependencies'];
    unset($export['features']['dependencies']);
  }

  if (isset($export['features']['features_exclude'])) {
    unset($export['features']['features_exclude']);
  }

  $files = features_export_render($export, $module_name, TRUE);

  // Write to module code.
  if (!$directory = drupal_get_path('module', $module_name)) {
    $directory = variable_get('features_builder_base_dir') . '/' . $module_name;
  }
  file_prepare_directory($directory, FILE_CREATE_DIRECTORY || FILE_MODIFY_PERMISSIONS);
  foreach ($files as $extension => $file_contents) {
    if (!in_array($extension, array('module', 'info'))) {
      $extension .= '.inc';
    }
    $filepath = "{$directory}/{$module_name}.{$extension}";
    file_put_contents($filepath, $file_contents);
    if (function_exists('drupal_clear_opcode_cache')) {
      drupal_clear_opcode_cache($filepath);
    }
  }

}
