<?php
/**
 * @file
 * Provide Drush integration for release building and dependency building.
 */

/**
 * Use variable to force cache clear, where required,
 * even if no-cache-clear option is used. Defaults to false.
 */
$force_all_cache_clear = FALSE;

/**
 * Implements hook_drush_help().
 */
function registry_rebuild_drush_help($section) {
  switch ($section) {
    case 'drush:registry-rebuild':
      return dt('Rebuild the registry or module cache in a Drupal install.');
  }
}

/**
 * Implements hook_drush_command().
 */
function registry_rebuild_drush_command() {
  $items = array();

  $items['registry-rebuild'] = array(
    'description' => 'Rebuild the registry table (for classes) and the system table (for module locations) in a Drupal install.',
    'callback' => 'drush_registry_rebuild',
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
    'options' => array(
      'no-cache-clear' => 'Rebuild the registry only, do not clear caches, unless --fire-bazooka is also used.',
      'fire-bazooka' => 'Truncate registry and registry_file tables and build them from scratch. Forces all caches clear.',
    ),
    'examples' => array(
      'drush rr --no-cache-clear' => 'Rebuild the registry only, do not clear caches, unless --fire-bazooka is also used.',
      'drush rr --fire-bazooka' => 'Truncate registry and registry_file tables and build them from scratch. Forces all caches clear.',
    ),
    'aliases' => array('rr'),
  );

  return $items;
}

/**
 * Rebuild the registry.
 *
 * Before calling this we need to be bootstrapped to DRUPAL_BOOTSTRAP_DATABASE.
 */
function drush_registry_rebuild() {
  define('MAINTENANCE_MODE', 'update');
  ini_set('memory_limit', -1);
  if (!drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_DATABASE)) {
    return drush_set_error('DRUPAL_SITE_NOT_FOUND', dt('You need to specify an alias or run this command within a drupal site.'));
  }
  $include_dir = DRUPAL_ROOT . '/includes';
  $module_dir = DRUPAL_ROOT . '/modules';
  // Use core directory if it exists.
  if (file_exists(DRUPAL_ROOT . '/core/includes/bootstrap.inc')) {
    $include_dir = DRUPAL_ROOT . '/core/includes';
    $module_dir = DRUPAL_ROOT . '/core/modules';
  }

  $includes = array(
    $include_dir . '/bootstrap.inc',
    $include_dir . '/common.inc',
    $include_dir . '/database.inc',
    $include_dir . '/schema.inc',
    $include_dir . '/actions.inc',
    $include_dir . '/entity.inc',
    $module_dir  . '/system/system.module',
    $include_dir . '/database/query.inc',
    $include_dir . '/database/select.inc',
    $include_dir . '/registry.inc',
    $include_dir . '/module.inc',
    $include_dir . '/menu.inc',
    $include_dir . '/file.inc',
    $include_dir . '/theme.inc',
  );

  if (drush_drupal_major_version() == 7) {
    $cache_lock_path_absolute = variable_get('lock_inc');
    if (!empty($cache_lock_path_absolute)) {
      $cache_lock_path_relative = DRUPAL_ROOT . '/'. variable_get('lock_inc');
      // Ensure that the configured lock.inc really exists at that location and
      // is accessible. Otherwise we use the core lock.inc as fallback.
      if (is_readable($cache_lock_path_relative) && is_file($cache_lock_path_relative)) {
        $includes[] = $cache_lock_path_relative;
        drush_log(dt("We will use relative variant of lock.inc: @lock", array('@lock' => $cache_lock_path_relative)));
      }
      elseif (is_readable($cache_lock_path_absolute) && is_file($cache_lock_path_absolute)) {
        $includes[] = $cache_lock_path_absolute;
        drush_log(dt("We will use absolute variant of lock.inc: @lock", array('@lock' => $cache_lock_path_absolute)));
      }
      else {
        drush_log(dt('We will use core implementation of lock.inc as fallback.'));
        $includes[] = DRUPAL_ROOT . '/includes/lock.inc';
      }
    }
    else {
      $includes[] = DRUPAL_ROOT . '/includes/lock.inc';
    }
  }
  elseif (drush_drupal_major_version() > 7) {
    // TODO
    // http://api.drupal.org/api/drupal/namespace/Drupal!Core!Lock/8
    $includes[] = $module_dir . '/entity/entity.module';
    $includes[] = $module_dir . '/entity/entity.controller.inc';
  }
  // In Drupal 6 the configured lock.inc is already loaded during
  // DRUSH_BOOTSTRAP_DRUPAL_DATABASE

  foreach ($includes as $include) {
    if (file_exists($include)) {
      require_once($include);
    }
  }

  // We may need to clear also Drush 5+ internal cache first.
  drush_log(dt("This DRUSH_MAJOR_VERSION is: @ver", array('@ver' => DRUSH_MAJOR_VERSION)));
  if (DRUSH_MAJOR_VERSION > 4) {
    drush_cache_clear_drush();
    drush_log(dt('Internal Drush cache cleared with drush_cache_clear_drush (1).'));
  }

  // This section is not functionally important. It's just using the
  // registry_get_parsed_files() so that it can report the change. Drupal 7 only.
  if (drush_drupal_major_version() == 7) {
    $connection_info = Database::getConnectionInfo();
    $driver = $connection_info['default']['driver'];
    require_once $include_dir . '/database/' . $driver . '/query.inc';
    $parsed_before = registry_get_parsed_files();
  }

  // Separate bootstrap cache exists only in Drupal 7 or newer.
  // They are cleared later again via drupal_flush_all_caches().
  if (drush_drupal_major_version() == 7) {
    cache_clear_all('lookup_cache', 'cache_bootstrap');
    cache_clear_all('variables', 'cache_bootstrap');
    cache_clear_all('module_implements', 'cache_bootstrap');
    drush_log(dt('Bootstrap caches have been cleared in DRUSH_BOOTSTRAP_DRUPAL_DATABASE.'));
  }
  elseif (drush_drupal_major_version() >= 8) {
    cache('bootstrap')->deleteAll();
    drush_log(dt('Bootstrap caches have been cleared in DRUSH_BOOTSTRAP_DRUPAL_DATABASE.'));
  }

  // We later run system_rebuild_module_data() and registry_update() on Drupal 7 via
  // D7-only registry_rebuild() wrapper, which is run inside drupal_flush_all_caches().
  // It is an equivalent of module_rebuild_cache() in D5-D6 and is normally run via
  // our universal wrapper registry_rebuild_cc_all() -- see further below.
  // However, we are still on the DRUPAL_BOOTSTRAP_SESSION level here,
  // and we want to make the initial rebuild as atomic as possible, so we can't
  // run everything from registry_rebuild_cc_all() yet, so we run an absolute
  // minimum we can at this stage, core specific.
  drush_log(dt('We are on the DRUSH_BOOTSTRAP_DRUPAL_DATABASE level still.'));
  if (drush_drupal_major_version() == 7) {
    registry_rebuild(); // D7 only
    drush_log(dt('The registry has been rebuilt via registry_rebuild (A).'), 'success');
  }
  elseif (drush_drupal_major_version() > 7) {
    system_rebuild_module_data(); // D8+
    drush_log(dt('The registry has been rebuilt via system_rebuild_module_data (A).'), 'success');
  }
  else { // D5-D6
    module_list(TRUE, FALSE);
    module_rebuild_cache();
    drush_log(dt('The registry has been rebuilt via module_rebuild_cache (A).'), 'success');
  }

  // We may need to clear also Drush 5+ internal cache at this point again.
  if (DRUSH_MAJOR_VERSION > 4) {
    drush_cache_clear_drush();
    drush_log(dt('Internal Drush cache cleared with drush_cache_clear_drush (2).'));
  }

  drush_log(dt('Bootstrapping to DRUPAL_BOOTSTRAP_FULL.'));
  drush_bootstrap_to_phase(DRUSH_BOOTSTRAP_DRUPAL_FULL);
  // We can run our wrapper now, since we are in a full bootstrap already.
  // Note that the wrapper normally honors the --no-cache-clear option if used.
  drush_registry_rebuild_cc_all();
  drush_log(dt('The registry has been rebuilt via drush_registry_rebuild_cc_all (B).'), 'success');

  if (drush_get_option('fire-bazooka') && drush_drupal_major_version() == 7) {
    $force_all_cache_clear = TRUE;
    if (drush_get_option('no-cache-clear')) {
      // Force all caches clear before rebuilding tables from scratch,
      // but only if --no-cache-clear is used, since otherwise
      // it already has been done above.
      drush_registry_rebuild_cc_all();
      drush_log(dt('Forced pre-fire-bazooka extra all caches clear.'));
    }
    db_truncate('registry')->execute();
    db_truncate('registry_file')->execute();
    drush_log(dt('The registry_file and registry tables truncated with --fire-bazooka.'));
    // We have to force API-based rebuild integrated with cache clears
    // directly after truncating registry tables.
    drush_registry_rebuild_cc_all();
    drush_log(dt('The registry has been rebuilt via drush_registry_rebuild_cc_all (C).'), 'success');
  }

  // Extra cleanup available for D7 only.
  if (drush_drupal_major_version() == 7) {
    $parsed_after = registry_get_parsed_files();
    // Remove files which don't exist anymore.
    $filenames = array();
    foreach ($parsed_after as $filename => $file) {
      if (!file_exists($filename)) {
        $filenames[] = $filename;
      }
    }
    if (!empty($filenames)) {
      db_delete('registry_file')
        ->condition('filename', $filenames)
        ->execute();
      db_delete('registry')
        ->condition('filename', $filenames)
        ->execute();
      $dt_args = array(
        '@files' => implode(', ', $filenames),
      );
      $singular = 'Manually deleted 1 stale file from the registry.';
      $plural   = 'Manually deleted @count stale files from the registry.';
      drush_log(format_plural(count($filenames), $singular, $plural), 'success');
      $singular = "A file has been declared in a module's .info, but could not be found. This is probably indicative of a bug. The missing file is @files.";
      $plural   = "@count files were declared in a module's .info, but could not be found. This is probably indicative of a bug. The missing files are @files.";
      drush_log(format_plural(count($filenames), $singular, $plural, $dt_args), 'warning');
    }
    $parsed_after = registry_get_parsed_files();
    $message = 'There were @parsed_before files in the registry before and @parsed_after files now.';
    $dt_args = array(
      '@parsed_before' => count($parsed_before),
      '@parsed_after'  => count($parsed_after),
    );
    drush_log(dt($message, $dt_args));
    drush_registry_rebuild_cc_all();
  }

  // Everything done.
  drush_log(dt('All registry rebuilds have been completed.'), 'success');
}

/**
 * Registry Rebuild needs to aggressively clear all caches,
 * not just some bins (at least to attempt it) also *before*
 * attempting to rebuild registry, or it may not be able
 * to fix the problem at all, if it relies on some cached
 * and no longer valid data/paths etc. This problem has been
 * confirmed and reproduced many times with option --fire-bazooka
 * which is available only in the Drush variant, but it confirms
 * the importance of starting with real, raw and not cached
 * in any way site state. While the --no-cache-clear option
 * still disables this procedure, --fire-bazooka takes precedence
 * and forces all caches clear action. All caches are cleared
 * by default in the PHP script variant.
 */
function drush_registry_rebuild_cc_all() {
  if (!drush_get_option('no-cache-clear') || $force_all_cache_clear) {
    if (function_exists('cache_clear_all') || drush_drupal_major_version() < 8) {
      cache_clear_all('*', 'cache', TRUE);
      cache_clear_all('*', 'cache_form', TRUE);
    }
    else {
      cache('cache')->deleteAll();
      cache('cache_form')->deleteAll();
    }

    if (function_exists('module_rebuild_cache') || (drush_drupal_major_version() >= 5 && drush_drupal_major_version() < 7)) { // D5-D6
      module_list(TRUE, FALSE);
      module_rebuild_cache();
    }

    if (function_exists('drupal_flush_all_caches') || drush_drupal_major_version() >= 6) { // D6+
      drupal_flush_all_caches();
    }
    else { // D5
      cache_clear_all();
      system_theme_data();
      node_types_rebuild();
      menu_rebuild();
    }
    drush_log(dt('All caches have been cleared with drush_registry_rebuild_cc_all.'), 'success');
  }
  else {
    if (drush_drupal_major_version() == 7) {
      registry_rebuild(); // D7 only
      drush_log(dt('The registry has been rebuilt via registry_rebuild (no-cache-clear).'), 'success');
    }
    elseif (drush_drupal_major_version() > 7) {
      system_rebuild_module_data(); // D8+
      drush_log(dt('The registry has been rebuilt via system_rebuild_module_data (no-cache-clear).'), 'success');
    }
    else { // D5-D6
      module_list(TRUE, FALSE);
      module_rebuild_cache();
      drush_log(dt('The registry has been rebuilt via module_rebuild_cache (no-cache-clear).'), 'success');
    }
    drush_log(dt('The Drupal caches have NOT been cleared after all registry rebuilds.'), 'warning');
    drush_log(dt('It is highly recommended you clear the Drupal caches as soon as possible.'), 'warning');
  }
}
