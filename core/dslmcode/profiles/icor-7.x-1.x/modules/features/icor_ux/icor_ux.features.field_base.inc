<?php
/**
 * @file
 * icor_ux.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function icor_ux_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cis_course_ref'
  $field_bases['field_cis_course_ref'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cis_course_ref',
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 1,
          ),
        ),
        'sort' => array(
          'direction' => 'DESC',
          'property' => 'title',
          'type' => 'property',
        ),
        'target_bundles' => array(
          'cis_course' => 'cis_course',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
