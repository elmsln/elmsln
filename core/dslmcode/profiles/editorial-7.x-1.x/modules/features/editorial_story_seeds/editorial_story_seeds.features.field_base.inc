<?php
/**
 * @file
 * editorial_story_seeds.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function editorial_story_seeds_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_seed'
  $field_bases['field_seed'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_seed',
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

  return $field_bases;
}
