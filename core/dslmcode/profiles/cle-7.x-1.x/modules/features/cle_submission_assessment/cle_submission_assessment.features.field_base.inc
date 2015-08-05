<?php
/**
 * @file
 * cle_submission_assessment.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cle_submission_assessment_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cle_associated_submission'
  $field_bases['field_cle_associated_submission'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cle_associated_submission',
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
          'type' => 'none',
        ),
        'target_bundles' => array(
          'cle_submission' => 'cle_submission',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_cle_point_value'
  $field_bases['field_cle_point_value'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cle_point_value',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'number',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'number_integer',
  );

  // Exported field_base: 'field_cle_status'
  $field_bases['field_cle_status'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cle_status',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'assessment_started' => 'Assessment started',
        'assessment_complete' => 'Assessment complete',
        'assessment_available' => 'Available to student',
        'assessment_viewed' => 'Student viewed feedback',
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
