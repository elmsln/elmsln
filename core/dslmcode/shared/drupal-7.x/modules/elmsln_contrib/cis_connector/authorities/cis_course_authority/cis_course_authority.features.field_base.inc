<?php
/**
 * @file
 * cis_course_authority.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cis_course_authority_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cis_course_uuid'
  $field_bases['field_cis_course_uuid'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cis_course_uuid',
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
      'max_length' => 255,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  // Exported field_base: 'field_course_machine_name'
  $field_bases['field_course_machine_name'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_course_machine_name',
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
      'max_length' => 40,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
