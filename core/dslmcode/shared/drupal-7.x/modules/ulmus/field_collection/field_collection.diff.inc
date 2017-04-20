<?php

/**
 * @file
 * Provide diff field functions for the Field collection module.
 */

/**
 * Diff field callback for parsing Field collection fields comparative values.
 */
function field_collection_field_diff_view($items, $context) {
  $diff_items = array();
  foreach ($items as $delta => $item) {
    $diff_items[$delta] = field_collection_field_render_revision($item, $context);
  }
  return $diff_items;
}

/**
 * Renders a field collection fields revision.
 */
function field_collection_field_render_revision($item, $context) {
  $entity_type = 'field_collection_item';
  $bundle_name = $context['field']['field_name'];
  $view_mode = $context['view_mode'];
  $entity = entity_revision_load($entity_type, $item['revision_id']);

  $field_context = $context;
  $field_context['entity_type'] = $entity_type;
  $field_context['bundle'] = $bundle_name;
  $field_context['entity'] = $entity;

  // Some fields piggy back the display settings, so we need to fake these by
  // ensuring that the field mode is always set.
  if (empty($view_mode)) {
    $field_context['custom_settings'] = FALSE;
  }
  $view_mode_settings = field_view_mode_settings($entity_type, $bundle_name);
  $actual_mode = (!empty($view_mode_settings[$view_mode]['custom_settings'])) ? $view_mode : 'default';
  if (!isset($field_context['custom_settings'])) {
    $field_context['custom_settings'] = $actual_mode && $actual_mode == $view_mode;
  }

  $instances = field_info_instances($entity_type, $field_context['bundle']);
  usort($instances, '_field_collection_sort_items');

  $result = array();
  foreach ($instances as $instance) {
    // Any view mode is supported in relation to hiding fields, but only if selected.
    if ($actual_mode && $instance['display'][$actual_mode]['type'] == 'hidden') {
      continue;
    }

    $field_name = $instance['field_name'];
    $field = field_info_field($field_name);

    // We provide a loose check on the field access.
    if (field_access('view', $field, $entity_type) || field_access('edit', $field, $entity_type)) {
      $langcode = field_language($entity_type, $entity, $field_name);
      $field_context['language'] = $langcode;
      $field_context['field'] = $field;
      $field_context['instance'] = $instance;
      $field_context['settings'] = diff_get_field_settings($field_context);
      $field_context['display'] = $instance['display'][$actual_mode];

      $func = $field['module'] . '_field_diff_view';
      if (!function_exists($func)) {
        $func = 'diff_field_diff_view';
      }

      if (!empty($entity->{$field_name}[$langcode])) {
        $raw_values = $func($entity->{$field_name}[$langcode], $field_context);
        $values = array();
        foreach ($raw_values as $raw_value) {
          $values[] = is_array($raw_value) ? implode(", ", $raw_value) : $raw_value;
        }

        $result[] = check_plain($instance['label'] . ': ' . implode(", ", $values));
      }
    }
  }

  return $result;
}

/**
 * Sort function for items order.
 */
function _field_collection_sort_items($a, $b) {
  $a_weight = (!empty($a['widget']['weight']) ? $a['widget']['weight'] : 0);
  $b_weight = (!empty($b['widget']['weight']) ? $b['widget']['weight'] : 0);
  return $a_weight - $b_weight;
}
