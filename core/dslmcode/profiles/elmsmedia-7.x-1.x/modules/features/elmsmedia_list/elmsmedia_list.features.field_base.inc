<?php
/**
 * @file
 * elmsmedia_list.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function elmsmedia_list_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_elmsmedia_items'.
  $field_bases['field_elmsmedia_items'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_elmsmedia_items',
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
          'audio' => 'audio',
          'document' => 'document',
          'elmsmedia_image' => 'elmsmedia_image',
          'elmsmedia_list' => 'elmsmedia_list',
          'external_video' => 'external_video',
          'figurelabel' => 'figurelabel',
          'h5p_content' => 'h5p_content',
          'image_gallery' => 'image_gallery',
          'static_content' => 'static_content',
          'svg' => 'svg',
          'video' => 'video',
        ),
      ),
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  // Exported field_base: 'field_elmsmedia_list_type'.
  $field_bases['field_elmsmedia_list_type'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_elmsmedia_list_type',
    'indexes' => array(
      'value' => array(
        0 => 'value',
      ),
    ),
    'locked' => 0,
    'module' => 'list',
    'settings' => array(
      'allowed_values' => array(
        'list' => 'List',
        'random' => 'Random',
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
