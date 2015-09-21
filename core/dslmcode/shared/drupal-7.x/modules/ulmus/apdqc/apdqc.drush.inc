<?php

/**
 * @file
 * Drush integration for APDQC module.
 */

/**
 * Implements hook_drush_command().
 */
function apdqc_drush_command() {
  $items['apdqc'] = array(
    'description' => dt('Apply the enhacements described on the project page'),
    'examples' => array(
      'drush apdqc' => dt('Takes site offline, runs the functions to process changes in the database, brings it back online.'),
    ),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 */
function apdqc_drush_help($section) {
  switch ($section) {
    case 'drush:apdqc':
      return dt('Run this to automatically apply the database performance optimizations.');
  }
}

/**
 * Drush command to all all the apdqc functions
 */
function drush_apdqc() {
  $maintenance_mode = variable_get('maintenance_mode', 0);
  // Take site offline.
  if (empty($maintenance_mode)) {
    variable_set('maintenance_mode', TRUE);
  }

  // Ensure we have the admin form in order to submit it.
  module_load_include('inc', 'apdqc', 'apdqc.admin');

  // Apply semaphore modifications if needed.
  $conversion = apdqc_semaphore_conversion();
  if ($conversion == 1) {
    apdqc_admin_convert_table_to_memory();
  }
  elseif ($conversion == 2) {
    apdqc_admin_convert_table_to_innodb();
  }

  // Collation of tables.
  apdqc_admin_convert_table_collations_to_utf8_bin();

  // Convert cache table indexes.
  apdqc_admin_convert_tables_indexes();

  // Bring site back online if it was online before.
  if (empty($maintenance_mode)) {
    variable_del('maintenance_mode');
  }
}
