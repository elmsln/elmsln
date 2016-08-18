<?php
/**
 * @file
 * elmsmedia_external_video.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function elmsmedia_external_video_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_external_media'.
  $field_bases['field_external_media'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_external_media',
    'indexes' => array(),
    'locked' => 0,
    'module' => 'video_embed_field',
    'settings' => array(
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'video_embed_field',
  );

  return $field_bases;
}
