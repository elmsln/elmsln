<?php

/**
 * @file
 * Drush commands for Advanced CSS/JS Aggregation.
 */

/**
 * @addtogroup 3rd_party_hooks
 * @{
 */

/**
 * Implements hook_drush_cache_clear().
 */
function advagg_drush_cache_clear(&$types) {
  // Add in Advanced CSS/JS Aggregation.
  $types['advagg'] = 'drush_advagg_smart_cache_flush';
}

/**
 * Implements hook_drush_help().
 */
function advagg_drush_help($command) {
  switch ($command) {
    case 'drush:advagg-cron':
      return dt('Run the advagg cron hook. This will clear out all stale advagg aggregated files, remove aggregates that include missing files, and remove unused aggregates.');

    case 'drush:advagg-clear-db-cache':
      return dt('Remove all entries from the advagg cache bins. Useful if you suspect a cache is not getting cleared.');

    case 'drush:advagg-clear-all-files':
      return dt('Remove all generated files. Useful if you think some of the generated files got corrupted and thus need to be deleted.');

    case 'drush:advagg-force-new-aggregates':
      return dt('Force the creation of all new aggregates by incrementing a global counter. Current value of counter: @value. This is useful if a CDN has cached an aggregate incorrectly as it will force new ones to be used even if nothing else has changed.', array('@value' => advagg_get_global_counter()));
  }
}

/**
 * Implements hook_drush_command().
 */
function advagg_drush_command() {
  $items = array();
  $items['advagg-cron'] = array(
    'description' => dt('Run the advagg cron hook.'),
    'examples' => array(
      'Standard example' => 'drush advagg-cron',
    ),
    'aliases' => array('advagg-c'),
  );
  $items['advagg-clear-db-cache'] = array(
    'description' => dt('Remove all entries from the advagg cache bins.'),
    'examples' => array(
      'Standard example' => 'drush advagg-clear-db-cache',
    ),
    'aliases' => array('advagg-cdc'),
  );
  $items['advagg-clear-all-files'] = array(
    'description' => dt('Remove all generated files.'),
    'examples' => array(
      'Standard example' => 'drush advagg-clear-all-files',
    ),
    'aliases' => array('advagg-caf'),
  );
  $items['advagg-force-new-aggregates'] = array(
    'description' => dt('Force the creation of all new aggregates by incrementing a global counter.'),
    'examples' => array(
      'Standard example' => 'drush advagg-force-new-aggregates',
    ),
    'aliases' => array('advagg-fna'),
  );
  return $items;
}

/**
 * @} End of "addtogroup 3rd_party_hooks".
 */

/**
 * Callback function for drush advagg-force-new-aggregates.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 */
function drush_advagg_force_new_aggregates() {
  // Clear out the cache.
  drush_advagg_clear_db_cache();

  // Increment counter.
  module_load_include('inc', 'advagg', 'advagg.cache');
  $new_value = advagg_increment_global_counter();
  drush_log(dt('Global counter is now set to @new_value', array('@new_value' => $new_value)), 'ok');
}

/**
 * Callback function for drush advagg-clear-all-files.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 */
function drush_advagg_clear_all_files() {
  // Clear out the cache.
  drush_advagg_clear_db_cache();

  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  list($css_files, $js_files) = advagg_remove_all_aggregated_files();

  // Report back the results.
  drush_log(dt('All AdvAgg files have been deleted. @css_count CSS files and @js_count JS files have been removed.', array(
    '@css_count' => count($css_files),
    '@js_count' => count($js_files),
  )), 'ok');
}

/**
 * Callback function for drush advagg-clear-db-cache.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 */
function drush_advagg_clear_db_cache() {
  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  advagg_flush_all_cache_bins();

  // Report back the results.
  drush_log(dt('All AdvAgg cache bins have been cleared.'), 'ok');
}

/**
 * Callback function for drush advagg-cron.
 *
 * Callback is called by using drush_hook_command() where
 * hook is the name of the module (advagg) and command is the name of
 * the Drush command with all "-" characters converted to "_" characters.
 */
function drush_advagg_cron() {
  // Run AdvAgg cron job.
  $output = advagg_cron(TRUE);

  // Output results from running advagg_delete_stale_aggregates().
  list($css_files, $js_files) = $output[0];
  if (count($css_files) > 0 || count($js_files) > 0) {
    drush_log(dt('All stale aggregates have been deleted. @css_count CSS files and @js_count JS files have been removed.', array(
      '@css_count' => count($css_files),
      '@js_count' => count($js_files),
    )), 'ok');
  }
  else {
    drush_log(dt('No stale aggregates found. Nothing was deleted.'), 'ok');
  }

  // Output results from running advagg_delete_orphaned_aggregates().
  if (empty($output[1][0]) && empty($output[1][1])) {
    drush_log(dt('All files have an associated db record; nothing was deleted.'), 'ok');
  }
  else {
    drush_log(dt('Some files had no associated db record and could be safely deleted from the file system. @raw', array('@raw' => print_r($output[1], TRUE))), 'ok');
  }

  // Output results from running advagg_remove_missing_files_from_db().
  if (empty($output[2])) {
    drupal_set_message(dt('All source files where found, no database entries where pruned.'), 'ok');
  }
  else {
    // format_plural() not always available.
    drupal_set_message(dt('Some source files are missing and as a result some unused aggregates were found. A total of @count database entries were removed.', array('@count' => count($output[2]))), 'ok');
  }

  // Output results from running advagg_remove_old_unused_aggregates().
  if (empty($output[3])) {
    drupal_set_message(dt('No old and unused aggregates found. Nothing was deleted.'), 'ok');
  }
  else {
    // format_plural() not always available.
    drupal_set_message(dt('Some old and unused aggregates were found. A total of @count database entries were removed.', array('@count' => $output[3])), 'ok');
  }

  // Output results from running advagg_cleanup_semaphore_table().
  if (empty($output[4])) {
    drupal_set_message(dt('No old semaphore locks found.'), 'ok');
  }
  else {
    // format_plural() not always available.
    drupal_set_message(dt('A total of @count old semaphore entries were removed.', array('@count' => count($output[4]))), 'ok');
  }

  // Output results from running advagg_remove_temp_files().
  if (empty($output[5])) {
    drupal_set_message(dt('No leftover temporary files found. Nothing was deleted.'), 'ok');
  }
  else {
    // format_plural() not always available.
    drupal_set_message(dt('Some oleftover temporary files were found. A total of @count temporary files were removed.', array('@count' => $output[5])), 'ok');
  }

  // Output results from running advagg_refresh_all_locale_files().
  if (empty($output[6])) {
    drupal_set_message(dt('Locale did not translate anything in any JavaScript files.'), 'ok');
  }
  else {
    drupal_set_message(dt('Locale did translate some JavaScript files. Resulting locale js files: @files', array('@files' => print_r($output[6], TRUE))), 'ok');
  }
}

/**
 * Flush the correct caches so CSS/JS changes go live.
 */
function drush_advagg_smart_cache_flush() {
  // Clear the libraries cache.
  if (function_exists('libraries_flush_caches')) {
    $cache_tables = libraries_flush_caches();
    foreach ($cache_tables as $table) {
      cache_clear_all('*', $table, TRUE);
    }
  }

  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  $flushed = advagg_push_new_changes();

  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) >= 0) {
    // Display a simple message if not in Development mode.
    drush_log('Advagg Cache Cleared', 'ok');
  }
  else {
    list($css_path) = advagg_get_root_files_dir();
    $parts_uri = $css_path[1] . '/parts';

    // Report back the results.
    foreach ($flushed as $filename => $data) {
      if (strpos($filename, $parts_uri) === 0) {
        // Do not report on css files manged in the parts directory.
        unset($flushed[$filename]);
        continue;
      }
      $ext = pathinfo($filename, PATHINFO_EXTENSION);
      drush_log(dt('The file @filename has changed. @db_usage aggregates are using this file. @db_count db cache entries and all @type full cache entries have been flushed from the cache bins. Trigger: @changes', array(
        '@filename' => $filename,
        '@db_usage' => $data[0],
        '@db_count' => $data[1],
        '@changes' => print_r($data[2], TRUE),
        '@type' => $ext,
      )), 'ok');
    }

    if (empty($flushed)) {
      drush_log(dt('No changes found. Nothing was cleared.'), 'ok');
      return;
    }
  }
}
