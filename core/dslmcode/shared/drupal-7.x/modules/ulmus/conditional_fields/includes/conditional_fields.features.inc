<?php
/**
 * @file
 * Features integration hooks.
 */

/**
 * Implements hook_features_export_options().
 */
function conditional_fields_features_export_options() {
  $dependencies = conditional_fields_load_dependencies();
  $entity_info = entity_get_info();
  $options = array();
  foreach ($dependencies as $type => $data) {
    foreach ($data as $dependency => $info) {
      $option = $type . ':' . $dependency;
      if (!isset($options[$dependency])) {
        $options[$option] = $entity_info[$type]['bundles'][$dependency]['label'] . ' (' . $type . ')';
      }
    }
  }
  return $options;
}

/**
 * Implements hook_features_export().
 */
function conditional_fields_features_export($data, &$export, $module_name = '') {
  $export['dependencies']['conditional_fields'] = 'conditional_fields';

  foreach ($data as $entity) {
    $export['features']['conditional_fields'][$entity] = $entity;
  }
}

/**
 * Implements hook_features_export_render().
 */
function conditional_fields_features_export_render($module_name, $data, $export = NULL) {
  $dependencies = conditional_fields_load_dependencies();
  if (empty($dependencies)) {
    return array();
  }

  $code = array();
  foreach ($data as $option) {
    $tokens = explode(':', $option);
    $entity = $tokens[0];
    $bundle = $tokens[1];

    if (isset($dependencies[$entity]) && isset($dependencies[$entity][$bundle])) {
      $info = $dependencies[$entity][$bundle];
      $delta[$option] = 0;

      // Ensure that dependencies are always exported in the same order to
      // avoid fake overrides.
      ksort($info['dependents']);

      foreach ($info['dependents'] as $dependent_field_name => $dependees) {
        foreach ($dependees as $dependee) {
          $code[] = '';
          $code[] = '  $items["' . $option . ':' . $delta[$option] . '"] = array(';
          $code[] = "    'entity' => '" . $entity . "',";
          $code[] = "    'bundle' => '" . $bundle . "',";
          $code[] = "    'dependent' => '" . $dependent_field_name . "',";
          $code[] = "    'dependee' => '" . $dependee['dependee'] . "',";
          $code[] = "    'options' => " . features_var_export($dependee['options'], '    ') . ',';
          $code[] = '  );';

          $delta[$option]++;
        }
      }
    }
  }
  if (empty($code)) {
    return array();
  }

  array_unshift($code, '  $items = array();');
  $code[] = '';
  $code[] = '  return $items;';
  $output = implode("\n", $code);

  return array('conditional_fields_default_fields' => $output);
}

/**
 * Implements hook_features_rebuild().
 */
function conditional_fields_features_rebuild($module) {
  $defaults = features_get_default('conditional_fields', $module);

  if (!empty($defaults)) {
    $dependencies = conditional_fields_load_dependencies();
    $instances = field_info_instances();
    foreach ($defaults as $field) {
      if (isset($dependencies[$field['entity']][$field['bundle']])) {
        foreach ($dependencies[$field['entity']][$field['bundle']] as $dependancy_type => $field_dep_settings) {
          if ($dependancy_type == 'dependees' && !empty($field_dep_settings)) {
            foreach ($field_dep_settings as $dep_setting) {
              foreach ($dep_setting as $id => $dep_settings) {
                $deps_to_remove[$id] = $id;
              }
            }
          }
        }
        if (!empty($deps_to_remove)) {
          conditional_fields_dependency_delete($deps_to_remove);
        }
      }
      $entity_instances = $instances[$field['entity']][$field['bundle']];
      $dependee_id = $entity_instances[$field['dependee']]['id'];
      $dependent_id = $entity_instances[$field['dependent']]['id'];
      conditional_fields_dependency_insert($dependee_id, $dependent_id, $field['options']);
    }
  }
}

/**
 * Implements hook_features_revert().
 */
function conditional_fields_features_revert($module) {
  return conditional_fields_features_rebuild($module);
}
