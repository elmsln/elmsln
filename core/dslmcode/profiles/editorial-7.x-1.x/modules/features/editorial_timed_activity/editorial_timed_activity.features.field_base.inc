<?php
/**
 * @file
 * editorial_timed_activity.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function editorial_timed_activity_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_timed_exercise'
  $field_bases['field_timed_exercise'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_timed_exercise',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        1 => '1 minute',
        5 => '5 minutes',
        10 => '10 minutes',
        15 => '15 minutes',
        20 => '20 minutes',
        25 => '25 minutes',
        30 => '30 minutes',
        0 => 'Disabled',
      ),
      'allowed_values_function' => '',
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'list_text',
  );

  return $field_bases;
}
