<?php

/**
 * @file
 * Features integration for Flag module.
 */

/**
 * Implements hook_features_export().
 */
function flag_features_export($data, &$export, $module_name = '') {
  $pipe = array();

  // Add flag module as a dependency.
  $export['dependencies']['flag'] = 'flag';

  // Ensure the modules that provide the flag are included as dependencies.
  $modules = flag_features_providing_module();
  foreach ($data as $key => $flag) {
    $module = '';
    if ($flag = flag_load($flag, TRUE)) {
      // Try to get the module that provides the entity this flag is on.
      // First pass: check whether there's a module that implements
      // hook_flag_type_info() for this entity.
      if (array_key_exists($flag->entity_type, $modules)) {
        $module = $modules[$flag->entity_type];
      }
      else {
        // Second pass: check whether this entity is defined using Entity API
        // and therefore has an extra 'module' property in its information.
        if ($entity_info = entity_get_info($flag->entity_type)) {
          if (isset($entity_info['module'])) {
            $module = $entity_info['module'];
          }
        }
      }

      if (!empty($module)) {
        $export['dependencies'][$module] = $module;
      }

      $export['features']['flag'][$flag->name] = $flag->name;
    }
  }

  return $pipe;
}

/**
 * Implements hook_features_export_options().
 */
function flag_features_export_options() {
  $options = array();
  // Get all flags, including disabled defaults.
  $flags = flag_get_flags() + flag_get_default_flags(TRUE);
  foreach ($flags as $name => $flag) {
    $options[$name] = drupal_ucfirst(check_plain($flag->entity_type)) . ': ' . check_plain($flag->title);
  }
  return $options;
}

/**
 * Implements hook_features_export_render().
 */
function flag_features_export_render($module, $data) {
  module_load_include('inc', 'flag', '/includes/flag.export');
  $code = flag_export_flags($data, $module, '  ');
  return array('flag_default_flags' => $code);
}

/**
 * Implements hook_features_revert().
 *
 * @param string $module
 *   The name of module for which to revert content.
 */
function flag_features_revert($module = NULL) {
  // Get default flags from features.
  if (module_hook($module, 'flag_default_flags')) {
    module_load_include('inc', 'flag', '/includes/flag.admin');
    $default_flags = module_invoke($module, 'flag_default_flags');

    // Build up values for the cache clear.
    $entity_types = array();

    // Revert flags that are defined in code.
    foreach ($default_flags as $flag_name => $flag_info) {
      if (is_numeric($flag_name)) {
        // Backward compatibility.
        $flag_name = $flag_info['name'];
      }
      $flag = flag_load($flag_name, TRUE);
      if ($flag && $flag->revert() === FALSE) {
        drupal_set_message(t('Could not revert flag %flag-name to the state described in your code: Your flag was created by a different version of the Flag module than is now being used.', array('%flag-name' => $flag->name)), 'error');
      }

      $entity_types[] = $flag->entity_type;
    }
    _flag_clear_cache($entity_types);
  }
}

/**
 * Helper function; Retrieve the providing modules defining the flags.
 */
function flag_features_providing_module() {
  $modules = array();
  $hook = 'flag_type_info';
  foreach (module_implements($hook) as $module) {
    foreach (module_invoke($module, $hook) as $key => $value) {
      $modules[$key] = isset($value['module']) ? $value['module'] : $module;
    }
  }

  // Any entity type without a flag providing module will be provided by the
  // flag module.
  foreach (entity_get_info() as $entity_type => $entity) {
    if (!isset($modules[$entity_type]) && empty($entity['configuration']) && $entity_type !== 'taxonomy_vocabulary') {
      $modules[$entity_type] = 'flag';
    }
  }

  return $modules;
}
