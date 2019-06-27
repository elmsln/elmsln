<?php
/**
 * @file
 * cis_tokens.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function cis_tokens_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_cis_tokens'.
  $field_bases['field_cis_tokens'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_cis_tokens',
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
    ),
    'translatable' => 0,
    'type' => 'text_long',
  );

  return $field_bases;
}
