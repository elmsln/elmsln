<?php

/**
 * Root directory of Drupal installation. Note that you can change this
 * if you need to. It just has to point to the actual root. This assumes
 * that the php file is being run in sites/all/modules/registry_rebuild.
 */

ini_set('memory_limit', -1);
define('DRUPAL_ROOT', define_drupal_root());
chdir(DRUPAL_ROOT);
print "DRUPAL_ROOT is " . DRUPAL_ROOT . ".<br/>\n";
define('MAINTENANCE_MODE', 'update');

global $_SERVER;
$_SERVER['REMOTE_ADDR'] = 'nothing';

global $include_dir;
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

if (function_exists('registry_rebuild')) { // == D7
  $cache_lock_path_absolute = variable_get('lock_inc');
  if (!empty($cache_lock_path_absolute)) {
    $cache_lock_path_relative = DRUPAL_ROOT . '/'. variable_get('lock_inc');
    // Ensure that the configured lock.inc really exists at that location and
    // is accessible. Otherwise we use the core lock.inc as fallback.
    if (is_readable($cache_lock_path_relative) && is_file($cache_lock_path_relative)) {
      $includes[] = $cache_lock_path_relative;
      print "We will use relative variant of lock.inc.<br/>\n";
    }
    elseif (is_readable($cache_lock_path_absolute) && is_file($cache_lock_path_absolute)) {
      $includes[] = $cache_lock_path_absolute;
      print "We will use absolute variant of lock.inc.<br/>\n";
    }
    else {
      print "We will use core implementation of lock.inc as fallback.<br/>\n";
      $includes[] = DRUPAL_ROOT . '/includes/lock.inc';
    }
  }
  else {
    $includes[] = DRUPAL_ROOT . '/includes/lock.inc';
  }
}
elseif (!function_exists('cache_clear_all')) { // D8+
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

print "Bootstrapping to DRUPAL_BOOTSTRAP_SESSION<br/>\n";
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);

registry_rebuild_rebuild();

/**
 * Find the drupal root directory by looking in parent directories.
 * If unable to discover it, fail and exit.
 */
function define_drupal_root() {
  // This is the smallest number of directories to go up: from /sites/all/modules/registry_rebuild.
  $parent_count = 4;
  // 8 seems reasonably far to go looking up.
  while ($parent_count < 8) {
    $dir = realpath(getcwd() . str_repeat('/..', $parent_count));
    if (file_exists($dir . '/index.php')) {
      return $dir;
    }
    $parent_count++;
  }
  print "Failure: Unable to discover DRUPAL_ROOT. You may want to explicitly define it near the top of registry_rebuild.php";
  exit(1);
}

/**
 * Before calling this we need to be bootstrapped to DRUPAL_BOOTSTRAP_SESSION.
 */
function registry_rebuild_rebuild() {
  // This section is not functionally important. It's just using the
  // registry_get_parsed_files() so that it can report the change. Drupal 7 only.
  if (function_exists('registry_rebuild')) {
    $connection_info = Database::getConnectionInfo();
    $driver = $connection_info['default']['driver'];
    global $include_dir;
    require_once $include_dir . '/database/' . $driver . '/query.inc';
    $parsed_before = registry_get_parsed_files();
  }

  // Separate bootstrap cache exists only in Drupal 7 or newer.
  // They are cleared later again via drupal_flush_all_caches().
  if (function_exists('registry_rebuild')) { // D7
    cache_clear_all('lookup_cache', 'cache_bootstrap');
    cache_clear_all('variables', 'cache_bootstrap');
    cache_clear_all('module_implements', 'cache_bootstrap');
    print "Bootstrap caches have been cleared in DRUPAL_BOOTSTRAP_SESSION<br/>\n";
  }
  elseif (!function_exists('cache_clear_all')) { // D8+
    cache('bootstrap')->deleteAll();
    print "Bootstrap caches have been cleared in DRUPAL_BOOTSTRAP_SESSION<br/>\n";
  }

  // We later run system_rebuild_module_data() and registry_update() on Drupal 7 via
  // D7-only registry_rebuild() wrapper, which is run inside drupal_flush_all_caches().
  // It is an equivalent of module_rebuild_cache() in D5-D6 and is normally run via
  // our universal wrapper registry_rebuild_cc_all() -- see further below.
  // However, we are still on the DRUPAL_BOOTSTRAP_SESSION level here,
  // and we want to make the initial rebuild as atomic as possible, so we can't
  // run everything from registry_rebuild_cc_all() yet, so we run an absolute
  // minimum we can at this stage, core specific.
  if (function_exists('registry_rebuild')) { // D7 only
    print "Doing registry_rebuild() in DRUPAL_BOOTSTRAP_SESSION<br/>\n";
    registry_rebuild();
  }
  elseif (!function_exists('registry_rebuild') && function_exists('system_rebuild_module_data')) { // D8+
    print "Doing system_rebuild_module_data() in DRUPAL_BOOTSTRAP_SESSION<br/>\n";
    system_rebuild_module_data();
  }
  else { // D5-D6
    print "Doing module_rebuild_cache() in DRUPAL_BOOTSTRAP_SESSION<br/>\n";
    module_list(TRUE, FALSE);
    module_rebuild_cache();
  }

  print "Bootstrapping to DRUPAL_BOOTSTRAP_FULL<br/>\n";
  drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
  // We can run our wrapper now, since we are in a full bootstrap already.
  print "Rebuilding registry via registry_rebuild_cc_all in DRUPAL_BOOTSTRAP_FULL<br/>\n";
  registry_rebuild_cc_all();

  // Extra cleanup available for D7 only.
  if (function_exists('registry_rebuild')) {
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
      print("Deleted " . count($filenames) . ' stale files from registry manually.');
    }
    $parsed_after = registry_get_parsed_files();
    print "There were " . count($parsed_before) . " files in the registry before and " . count($parsed_after) . " files now.<br/>\n";
    registry_rebuild_cc_all();
  }
  print "If you don't see any crazy fatal errors, your registry has been rebuilt.<br/>\n";
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
function registry_rebuild_cc_all() {
  if (function_exists('cache_clear_all')) {
    cache_clear_all('*', 'cache', TRUE);
    cache_clear_all('*', 'cache_form', TRUE);
  }
  else {
    cache('cache')->deleteAll();
    cache('cache_form')->deleteAll();
  }

  if (function_exists('module_rebuild_cache')) { // D5-D6
    module_list(TRUE, FALSE);
    module_rebuild_cache();
  }

  if (function_exists('drupal_flush_all_caches')) { // D6+
    drupal_flush_all_caches();
  }
  else { // D5
    cache_clear_all();
    system_theme_data();
    node_types_rebuild();
    menu_rebuild();
  }
  print "All caches have been cleared with registry_rebuild_cc_all.<br/>\n";
}
