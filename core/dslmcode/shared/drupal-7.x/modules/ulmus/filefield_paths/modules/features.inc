<?php
/**
 * @file
 * Features module integration.
 */

/**
 * Implements hook_features_pipe_field_instance_alter().
 *
 * This determines whether exported fields contain File (Field) Paths settings
 * and if so adds File (Field) Paths as a dependency.
 */
function filefield_paths_features_pipe_field_instance_alter(&$pipe, $data, &$export) {
  foreach ($data as $field_identifier) {
    list($entity_type, $bundle_name, $field_name) = explode('-', $field_identifier);
    $instance = field_info_instance($entity_type, $field_name, $bundle_name);
    if (isset($instance['settings']['filefield_paths'])) {
      $export['dependencies']['filefield_paths'] = 'filefield_paths';
    }
  }
}

/**
 * Implements hook_features_pipe_field_alter().
 *
 * @todo - Remove this in a future release.
 */
function filefield_paths_features_pipe_field_alter(&$pipe, $data, &$export) {
  filefield_paths_features_pipe_field_instance_alter($pipe, $data, $export);
}
