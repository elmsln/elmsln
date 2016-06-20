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
    'callback' => 'drush_apdqc',
    'description' => dt('Apply the enhacements described on the apdqc project page.'),
    'core' => array('7+'),
    'arguments' => array(
      'collation' => 'What collation to use for the cid column of cache tables in MySQL.',
    ),
    'examples' => array(
      'drush apdqc' => dt('Takes site offline, runs the functions to process changes in the database, brings it back online.'),
      'drush apdqc utf8_bin' => dt('Takes site offline, runs the functions to process changes in the database, brings it back online. Will use utf8 collation instead of ascii for cid.'),
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
 * Drush command to all all the apdqc functions.
 */
function drush_apdqc($collation = 'ascii_bin') {
  $maintenance_mode = variable_get('maintenance_mode', 0);
  // Take site offline.
  if (empty($maintenance_mode)) {
    variable_set('maintenance_mode', TRUE);
  }

  // Ensure we have the admin form functions.
  module_load_include('inc', 'apdqc', 'apdqc.admin');

  // Apply semaphore modifications if needed.
  $conversion = apdqc_semaphore_conversion();
  if ($conversion == 1) {
    apdqc_admin_convert_table_to_memory();
  }
  elseif ($conversion == 2) {
    apdqc_admin_convert_semaphore_table_to_innodb();
  }

  // Collation of tables.
  apdqc_admin_convert_table_collations_to(FALSE, $collation);

  // Convert cache table indexes.
  apdqc_admin_convert_tables_indexes();

  // Convert sessions table.
  apdqc_admin_sessions_table_update_schema();

  // Convert sessions table.
  apdqc_admin_semaphore_table_update_schema();

  // Bring site back online if it was online before.
  if (empty($maintenance_mode)) {
    variable_del('maintenance_mode');
  }
}
