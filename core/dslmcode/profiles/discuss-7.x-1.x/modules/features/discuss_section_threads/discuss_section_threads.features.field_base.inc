<?php
/**
 * @file
 * discuss_section_threads.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function discuss_section_threads_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_harmony_threads'
  $field_bases['field_harmony_threads'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_harmony_threads',
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
      'handler' => 'harmony_thread_selection_plugin',
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
          'harmony_thread' => 'harmony_thread',
        ),
      ),
      'target_type' => 'harmony_thread',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
