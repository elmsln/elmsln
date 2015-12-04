<?php
/**
 * @file
 * git_book.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function git_book_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_git_repo'
  $field_bases['field_git_repo'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_git_repo',
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
