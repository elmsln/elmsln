<?php
/**
 * @file
 * cis_unique_tag.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cis_unique_tag_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cis_tag'
  $field_bases['field_cis_tag'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cis_tag',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
      'max_length' => 30,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
