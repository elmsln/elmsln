<?php
/**
 * @file
 * Features module integration.
 */

/**
 * Implements hook_features_pipe_component_alter().
 */
function custom_formatters_features_pipe_field_alter(&$pipe, $data, $export) {
  foreach ($data as $id) {
    list($entity_type, $bundle_name, $field_name) = explode('-', $id);
    $field = field_info_instance($entity_type, $field_name, $bundle_name);
    foreach ($field['display'] as $display) {
      if (isset($display['module']) && $display['module'] == 'custom_formatters') {
        $formatter = custom_formatters_crud_load(drupal_substr($display['type'], 18));
        if ($formatter->export_type == EXPORT_IN_DATABASE) {
          $pipe['formatters'][$formatter->name] = $formatter->name;
        }
      }
    }
  }
}
