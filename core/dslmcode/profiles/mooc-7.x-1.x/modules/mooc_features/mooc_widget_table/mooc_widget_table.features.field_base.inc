<?php
/**
 * @file
 * mooc_widget_table.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function mooc_widget_table_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_table_data'
  $field_bases['field_table_data'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_table_data',
    'foreign keys' => array(),
    'indexes' => array(),
    'locked' => 0,
    'module' => 'tablefield',
    'settings' => array(
      'cell_processing' => 0,
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
      'export' => 1,
      'lock_values' => 0,
      'restrict_rebuild' => 0,
    ),
    'translatable' => 0,
    'type' => 'tablefield',
  );

  return $field_bases;
}
