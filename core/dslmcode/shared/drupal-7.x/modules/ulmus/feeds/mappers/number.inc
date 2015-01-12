<?php

/**
 * @file
 * On behalf implementation of Feeds mapping API for number.module.
 */

/**
 * Implements hook_feeds_processor_targets_alter().
 *
 * @see FeedsProcessor::getMappingTargets()
 */
function number_feeds_processor_targets_alter(&$targets, $entity_type, $bundle_name) {
  $numeric_types = array(
    'list_integer',
    'list_float',
    'list_boolean',
    'number_integer',
    'number_decimal',
    'number_float',
  );
  foreach (field_info_instances($entity_type, $bundle_name) as $name => $instance) {
    $info = field_info_field($name);

    if (in_array($info['type'], $numeric_types)) {
      $targets[$name] = array(
        'name' => check_plain($instance['label']),
        'callback' => 'number_feeds_set_target',
        'description' => t('The @label field of the entity.', array('@label' => $instance['label'])),
      );
    }
  }
}

/**
 * Callback for mapping numerics.
 *
 * Ensure that $value is a numeric to avoid database errors.
 */
function number_feeds_set_target($source, $entity, $target, array $values) {
  // Iterate over all values.
  $field = isset($entity->$target) ? $entity->$target : array('und' => array());

  foreach ($values as $value) {

    if (is_object($value) && ($value instanceof FeedsElement)) {
      $value = $value->getValue();
    }

    if (is_numeric($value)) {
      $field['und'][] = array('value' => $value);
    }
  }

  $entity->$target = $field;
}
