<?php
/**
 * @file
 * mooc_random_content.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mooc_random_content_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_random_type'
  $field_bases['field_random_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_random_type',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'area1' => 'Area 1',
        'area2' => 'Area 2',
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
