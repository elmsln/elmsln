<?php
/**
 * @file
 * cle_section_assigmement.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cle_section_assigmement_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cle_assignments'.
  $field_bases['field_cle_assignments'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cle_assignments',
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
          'direction' => 'ASC',
          'field' => 'field_number:value',
          'type' => 'field',
        ),
        'target_bundles' => array(
          'cle_assignment' => 'cle_assignment',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
