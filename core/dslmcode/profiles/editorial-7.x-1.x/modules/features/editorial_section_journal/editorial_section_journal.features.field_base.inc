<?php
/**
 * @file
 * editorial_section_journal.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function editorial_section_journal_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_editorial_exercises'
  $field_bases['field_editorial_exercises'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_editorial_exercises',
    'indexes' => array(
      'tid' => array(
        0 => 'tid',
      ),
    ),
    'locked' => 0,
    'module' => 'taxonomy',
    'settings' => array(
      'allowed_values' => array(
        0 => array(
          'vocabulary' => 'editorial_exercise',
          'parent' => 0,
        ),
      ),
      'cis_connector_access' => FALSE,
      'cis_connector_disable' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'taxonomy_term_reference',
  );

  return $field_bases;
}
