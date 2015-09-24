<?php

/**
 * @file
 * Drush integration for default config.
 */

/**
 * Implements hook_drush_command().
 */
function defaultconfig_drush_command() {
  $items['defaultconfig-rebuild-all'] = array(
    'description' => "Rebuild all default configurations.",
    'drupal dependencies' => array('defaultconfig'),
    'aliases' => array('dra'),
  );

  $items['defaultconfig-rebuild-modules'] = array(
    'description' => "Revert a defaultconfig module or module.component pair on your site.",
    'arguments' => array(
      'modules' => 'A space delimited list of modules or module.component pairs.',
    ),
    'examples' => array(
      'drush drm foo.views_view foo.variable bar' => 'Revert views_view and variable components of module "foo", and revert all components of module "bar".',
    ),
    'drupal dependencies' => array('defaultconfig'),
    'aliases' => array('drm'),
  );

  return $items;
}

/**
 * Command callback for defaultconfig-rebuild-all.
 */
function drush_defaultconfig_rebuild_all() {
  if (drush_confirm(dt('All configuration will be rebuilt. Do you want to continue?'))) {
    defaultconfig_rebuild_all();
    drush_log(dt('All components have been rebuilt.'), 'ok');
  }
}

/**
 * Command callback for defaultconfig-rebuild-modules.
 */
function drush_defaultconfig_rebuild_modules() {
  $input_list = func_get_args();
  drush_confirm(dt('Are you sure you want to rebuild: @list', array('@list' => implode(' ', $input_list))));

  $list = array();
  foreach ($input_list as $rebuild) {
    $rebuild = explode('.', $rebuild);
    $module = $rebuild[0];
    if (!empty($rebuild[1])) {
      $component = $rebuild[1];
    }
    else {
      $component = 'all';
    }

    $list[$module][] = $component;
  }

  $defaultconfig_components = defaultconfig_get_components();

  foreach ($list as $module => $components) {
    if (($feature = features_load_feature($module, TRUE)) && module_exists($module)) {
      $features_components = $feature->info['features'];

      if (!empty($features_components['defaultconfig'])) {
        $module_components = array();
        foreach ($features_components['defaultconfig'] as $module_component) {
          $module_component = explode(':', $module_component);
          $module_components[$module_component[0]] = $module_component[0];
        }

        if (in_array('all', $components)) {
          foreach ($module_components as $module_component) {
            if (!empty($defaultconfig_components[$module_component])) {
              defaultconfig_component_rebuild($defaultconfig_components[$module_component], $module);
              drush_print(dt('Rebuilt: @module:@component', array('@module' => $module, '@component' => $module_component)));
            }
          }
        }
        else {
          foreach ($components as $component) {
            if (!empty($module_components[$component]) && !empty($defaultconfig_components[$component])) {
              defaultconfig_component_rebuild($defaultconfig_components[$component], $module);
              drush_print(dt('Rebuilt: @module:@component', array('@module' => $module, '@component' => $component)));
            }
            else {
              drush_log(dt('The module %module% does not contain the defaultconfig component %component%.', array('%module%' => $module, '%component%' => $component)));
            }
          }
        }
      }
      else {
        drush_log(dt('The module %module% does not contain any defaultconfig components.', array('%module%' => $module)));
      }
    }
  }
}
