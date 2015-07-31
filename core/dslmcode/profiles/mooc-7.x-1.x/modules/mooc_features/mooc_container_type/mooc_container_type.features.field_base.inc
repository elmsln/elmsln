<?php
/**
 * @file
 * mooc_container_type.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mooc_container_type_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_mooc_container_type'
  $field_bases['field_mooc_container_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_mooc_container_type',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'folder' => 'Folder',
        'index' => 'Index',
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
