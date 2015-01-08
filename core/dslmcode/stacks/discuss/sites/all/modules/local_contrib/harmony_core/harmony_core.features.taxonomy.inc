<?php
/**
 * @file
 * harmony_core.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function harmony_core_taxonomy_default_vocabularies() {
  return array(
    'harmony_category' => array(
      'name' => 'Category',
      'machine_name' => 'harmony_category',
      'description' => '',
      'hierarchy' => 1,
      'module' => 'taxonomy',
      'weight' => -10,
    ),
  );
}
