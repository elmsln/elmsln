<?php

/**
 * @file
 * Page callback for features override pages.
 */

module_load_include('inc', 'features_override', 'features_override.export');

/**
 * Implements hook_features_export_options().
 */
function features_override_items_features_export_options() {
  $options = $links = array();
  $overrides = features_override_get_overrides();
  foreach ($overrides as $component => $elements) {
    foreach ($elements as $key => $element) {
      $options["{$component}.{$key}"] =  "{$component} {$key} ";
    }
  }
  return $options;
}

/**
 * Implements hook_features_export_options().
 */
function features_overrides_features_export_options() {
  $options = $sub_links = $main_links = array();
  drupal_add_js(drupal_get_path('module', 'features_override') . '/features_override_form.js');
  drupal_add_css(drupal_get_path('module', 'features_override') . '/features_override.css');

  $overrides = features_override_get_overrides();
  foreach ($overrides as $component => $elements) {
    foreach ($elements as $key => $element) {
      $identifier = "{$component}.{$key}";
      $identifier_spaced = "{$component} {$key} ";
      $main_links[features_override_encode_string($identifier)] = url('admin/structure/features/features_override/' . $component . '/' . $key);
      if (!empty($element['additions'])) {
        foreach ($element['additions'] as $change_key => $changes) {
          $options[$identifier . '.' . $change_key] = $identifier_spaced . ' addition: of ' . features_override_export_keys($changes['keys']);
          $sub_links[features_override_encode_string($identifier . '.' . $change_key)] = url('admin/structure/features/features_override/' . $component . '/' . $key, array('query' => array('key' => $change_key)));
        }
      }
      if (!empty($element['deletions'])) {
        foreach ($element['deletions'] as $change_key => $changes) {
          $options[$identifier . '.' . $change_key] = $identifier_spaced . ' deletion of ' . features_override_export_keys($changes['keys']);
          $sub_links[features_override_encode_string($identifier . '.' . $change_key)] = url('admin/structure/features/features_override/' . $component . '/' . $key, array('query' => array('key' => $change_key)));
        }
      }
    }
  }
  drupal_add_js(array('features_override_links' => array('main' => $main_links, 'sub' => $sub_links)), 'setting');

  return $options;
}

/**
 * Implements hook_features_export().
 */
function features_override_items_features_export($data, &$export, $module_name = '') {
  $pipe = array('features_overrides' => array());
  $map = features_get_default_map('features_override_items');
  $map_overrides = features_get_default_map('features_overrides');
  static $options;
  if (!isset($options)) {
    $options = features_overrides_features_export_options();
  }

  foreach ($data as $identifier) {
    // If this override bundle is already provided by another module, remove the field
    // and add the other module as a dependency.
    if (isset($map[$identifier]) && $map[$identifier] != $module_name) {
      if (isset($export['features']['features_override_items'][$identifier])) {
        unset($export['features']['features_override_items'][$identifier]);
      }
      $module = $map[$identifier];
      $export['dependencies'][$module] = $module;
    }
    // If the field has not yet been exported, add it
    else {
      $export['features']['features_override_items'][$identifier] = $identifier;
      list($component, $element) = features_override_parse_identifier($identifier);

      // Add in all current overrides to import.
      foreach ($options as $option_key => $option_name) {
        list($options_component, $options_element, $options_keys) = features_override_parse_identifier($option_key);
        if ($options_element == $element && empty($map_overrides[$option_key])) {
          $pipe['features_overrides'][] = $option_key;
        }
      }

      // Add in depedency to module that defines this item.
      $component_map = features_get_default_map($component);
      if (!empty($component_map[$element])) {
        $export['dependencies'][$component_map[$element]] = $component_map[$element];
      }
    }
  }
  return $pipe;
}


/**
 * Implements hook_features_export().
 */
function features_overrides_features_export($data, &$export, $module_name = '') {
  $pipe = array('features_overrides' => array());
  $map = features_get_default_map('features_overrides');
  static $options;

  foreach ($data as $identifier) {
    // If this override bundle is already provided by another module, remove the field
    // and add the other module as a dependency.
    if (isset($map[$identifier]) && $map[$identifier] != $module_name) {
      if (isset($export['features']['features_overrides'][$identifier])) {
        unset($export['features']['features_overrides'][$identifier]);
      }
      $module = $map[$identifier];
      $export['dependencies'][$module] = $module;
    }
    // If the field has not yet been exported, add it
    else {
      $export['features']['features_overrides'][$identifier] = $identifier;
    }
  }
  return $pipe;
}

/**
 * Implements hook_features_export_render().
 */
function features_override_items_features_export_render($module, $data, $export = NULL) {
  // no code is needed for this exportable.  Details are stored via features_overrides_features_export_render
  $list = array();

/*
  // Go through all data collecting the items exports to create.
  $features_override_code = array(
    '  // This code is only used to work nicely with features UI.',
    '  $overrides = array();',
  );
  foreach ($data as $identifier) {
    $features_override_code[] = '';
    $features_override_code[] = "  // Exported overrides for: $identifier";
    $features_override_code[] = '  $overrides[' . features_var_export($identifier) . '] =  1;';
  }

  // Create the default hook that defines all exported overrides.
  $features_override_code[] = '';
  $features_override_code[] = ' return $overrides;';
  $list['features_override_default_items'] = implode("\n", $features_override_code);
 */
  return $list;
}

/**
 * Implements hook_features_export_render().
 */
function features_overrides_features_export_render($module, $data, $export = NULL) {
  // Remember, the code exported here is just for the Features UI to keep track
  // of the overridden status.  All it needs to do is capture "changes".
  // The actual form of the output doesn't really matter.
  $list = $overrides_to_export = array();

  // Go through all data collecting the items exports to create.
  $features_override_code = array(
    '  // This code is only used for UI in features. Exported alters hooks do the magic.',
    '  $overrides = array();',
  );
  $last_component = '';
  foreach ($data as $identifier) {
    // Something is adding extra quote marks.
    list($component, $element, $keys) = features_override_parse_identifier($identifier);
    $component_code[$component] = isset($component_code[$component]) ? $component_code[$component] : array();
    $overrides_to_export[$component] = isset($overrides_to_export[$component]) ? $overrides_to_export[$component] : array();
    $overrides = features_override_get_overrides($component);
    $features_override_value = array(
      'additions' => array(),
      'deletions' => array()
    );
    // Just specific keys are being exported so add them if set.
    if (!empty($overrides[$element])) {
      if (isset($overrides[$element]['additions'][$keys])) {
        $overrides_to_export[$component][$element]['additions'][] = $overrides[$element]['additions'][$keys];
        $features_override_value['additions'][] = $overrides[$element]['additions'][$keys];
      }
      elseif (isset($overrides[$element]['deletions'][$keys])) {
        $overrides_to_export[$component][$element]['deletions'][] = $overrides[$element]['deletions'][$keys];
        $features_override_value['deletions'][] = $overrides[$element]['deletions'][$keys];
      }
    }
    if ($component != $last_component) {
      $features_override_code[] = '';
      $features_override_code[] = "  // Exported overrides for: $component";
    }
    $last_component = $component;
    if (count($features_override_value['additions'])) {
      $features_override_code[] = '  $overrides["' . $identifier . '"] = ' . features_override_var_export($features_override_value['additions'][0]['value'], '  ') . ';';
    }
    else if (count($features_override_value['deletions'])) {
      $features_override_code[] = '  $overrides["' . $identifier . '"]["DELETED"] = TRUE;';
    }
  }

  // Create the default hook that defines all exported overrides.
  $features_override_code[] = '';
  $features_override_code[] = ' return $overrides;';
  $list['features_override_default_overrides'] = implode("\n", $features_override_code);

  $component_code = array();
  foreach ($overrides_to_export as $component => $elements) {
    foreach ($elements as $element => $overrides) {
      $component_code[$component] = isset($component_code[$component]) ? $component_code[$component] : array();
      $component_code[$component][] = '  if (isset($data[' . var_export($element,TRUE) . '])) {';
      if (!empty($overrides['additions'])) {
        foreach ($overrides['additions'] as $alter) {
          $component_code[$component][] = implode("\n", features_override_features_export_render_addition($alter, $element, $component));
        }
      }
      if (!empty($overrides['deletions'])) {
        foreach ($overrides['deletions'] as $alter) {
          $component_code[$component][] = implode("\n", features_override_features_export_render_deletion($alter, $element, $component));
        }
      }
      $component_code[$component][] = '  }';
    }
  }

  $info = features_get_components();
  foreach ($component_code as $component => $code) {
    $list[features_get_default_alter_hook($component) . '_alter'] = array(
      'code' => implode("\n", $code),
      'args' => '&$data',
      'file' => 'features',
    );
  }

  return $list;
}

/**
 * Implements hook_features_revert().
 */
function features_override_items_features_revert($module) {
  features_override_items_features_rebuild($module);
}

/**
 * Implements of hook_features_rebuild().
 */
function features_override_items_features_rebuild($module) {
  _features_override_features_rebuild($module, 'features_override_items');
}

/**
 * Implements hook_features_revert().
 */
function features_overrides_features_revert($module) {
  features_overrides_features_rebuild($module);
}

/**
 * Implements of hook_features_rebuild().
 */
function features_overrides_features_rebuild($module) {
  _features_override_features_rebuild($module, 'features_overrides');
}

/**
 * Rebuilds fields from code defaults.
 *
 * FIXME This is reverting everything that has a change instead of this module.
 */
function _features_override_features_rebuild($module, $component_key = 'features_override_items') {
  // first build list of components we are overriding
  $parents = array();
  $data = features_get_component_map();
  foreach ($data[$component_key] as $identifier => $component_modules) {
    list($component, $element) = features_override_parse_identifier($identifier);
    if (isset($data[$component][$element])) {
      foreach ($data[$component][$element] as $module_name) {
        $parents[$module][$component] = $module_name;
      }
    }
  }
  // first, update get_default cache so rebuild will work on latest data
  foreach ($parents as $module => $element) {
    foreach ($element as $component) {
      features_get_default($component, $module, TRUE, TRUE);
    }
  }

  // rebuild those parent components
  //features_rebuild($parents);
}
