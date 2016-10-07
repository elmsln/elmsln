<?php
/**
 * @file
 * elmsmedia_static_content.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function elmsmedia_static_content_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_accessible_fallback'.
  $field_bases['field_accessible_fallback'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_accessible_fallback',
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
          'static_content' => 'static_content',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
