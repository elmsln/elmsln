<?php

function cle_submission_progress_features_export($data, &$export, $module_name = '') {
  $pipe = array(); // formality as we're currently not adding any dependencies
  $map = features_get_default_map('cle_submission_progress');
  foreach ($data as $identifier) {
    list($entity_type, $bundle) = explode(':', $identifier);
    if ($settings = cle_submission_progress_cle_submission_progress_features_load($entity_type, $bundle)) {
      if (isset($map[$identifier]) && $map[$identifier] != $module_name) {
        if (isset($export['features']['cle_submission_progress'][$identifier])) {
          unset($export['features']['cle_submission_progress'][$identifier]);
        }
        $module = $map[$identifier];
        $export['dependencies'][$module] = $module;
      }
      else {
        $export['features']['cle_submission_progress'][$identifier] = $identifier;
      }
    }
  }
  return $pipe;
}

function cle_submission_progress_features_export_options() {
  $options = array();
  foreach (cle_submission_progress_cle_submission_progress_features_load() as $entity_type => $bundles) {
    foreach ($bundles as $bundle_name => $bundle_info) {
      $options["${entity_type}:${bundle_name}"] = "${entity_type}: ${bundle_name} extra fields";
    }
  }
  return $options;
}

function cle_submission_progress_features_export_render($module_name, $data, $export = NULL) {
  error_log(print_r($data, TRUE));
  $code = array();
  $code[] = ' $cle_submission_progress_info = array();';
  foreach ($data as $name) {
    list($entity_type, $bundle) = explode(':', $name);
    $code[] = "  \$cle_submission_progress_info['{$entity_type}']['{$bundle}']['cle_submission_progress'] = " . features_var_export(cle_submission_progress_cle_submission_progress_features_load($entity_type, $bundle)) .";";
  }
  $code[] = "return \$cle_submission_progress_info;";
  $code = implode("\n", $code);
  return array('cle_submission_progress_info' => $code);
}

function cle_submission_progress_features_revert($module) {
  if ($default_types = features_get_default('cle_submission_progress', $module)) {
    foreach ($default_types as $entity_type => $entity_info) {
      foreach ($entity_info as $bundle_name => $bundle_info) {
        $field_bundle_settings = field_bundle_settings($entity_type, $bundle_name);
        $field_bundle_settings['cle_submission_progress'] = $bundle_info['cle_submission_progress'];
        field_bundle_settings($entity_type, $bundle_name, $field_bundle_settings);
      }
    }
  }
}

function cle_submission_progress_cle_submission_progress_features_load($entity_type = NULL, $bundle = NULL) {
  $cle_submission_progress = array();
  if ($field_bundle_settings = variable_get('field_bundle_settings')) {
    foreach ($field_bundle_settings as $_entity_type => $bundle_info) {
      foreach ($bundle_info as $_bundle => $bundle_settings) {
        if (!empty($bundle_settings['cle_submission_progress'])) {
          $cle_submission_progress[$_entity_type][$_bundle]['cle_submission_progress'] = $bundle_settings['cle_submission_progress'];
        }
      }
    }
    // pull out the items that are already available in default
  /*  $map = features_get_default_map('cle_submission_progress');
    foreach ($map as $module) {
      $module_defaults = features_get_default('cle_submission_progress', $module);
      foreach ($module_defaults as $_entity_type => $entity_info) {
        foreach ($entity_info as $_bundle_name => $bundle_info) {
          // if these are default, we don't want to list them in the options
          // or allow them to be exported
          unset($cle_submission_progress[$_entity_type][$_bundle_name]);
        }
      }
    }*/
    if (!empty($entity_type) && !empty($bundle)) {
      return $cle_submission_progress[$entity_type][$bundle]['cle_submission_progress'];
    }
  }
  return $cle_submission_progress;
}
