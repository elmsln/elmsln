<?php
/**
 * @file
 * editorial_journal_entry.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function editorial_journal_entry_taxonomy_default_vocabularies() {
  return array(
    'editorial_exercise' => array(
      'name' => 'Exercise',
      'machine_name' => 'editorial_exercise',
      'description' => 'The exercise associated with this journal entry',
      'hierarchy' => 0,
      'module' => 'taxonomy',
      'weight' => 0,
    ),
  );
}
