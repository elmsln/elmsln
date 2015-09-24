<?php

/**
 * @file
 * Front controller for testing the page cache handler.
 */

// Detect root directory of the Drupal installation.
$__file__ = isset($_SERVER['SCRIPT_FILENAME']) ? $_SERVER['SCRIPT_FILENAME'] : __FILE__;
if ($__file__[0] !== '/') {
  $__file__ = str_replace(DIRECTORY_SEPARATOR, '/', $__file__);
}
$drupalroot = preg_replace('#(/(sites|profiles)/([^/]+))?/modules(/.*)?/authcache_builtin/tests/frontcontroller/index.php$#', '', $__file__);

if ($drupalroot === $__file__) {
  trigger_error('Authcache builtin test front controller: failed to locate Drupal root directory', E_USER_ERROR);
  exit();
}

// Relocate contents of $_SERVER variable to DRUPAL_ROOT by removing path
// components pointing to the authcache front controller.
$preg = '|' . preg_quote(substr($__file__, strlen($drupalroot) + 1), '|') . '|';
foreach ($_SERVER as $key => $value) {
  $_SERVER[$key] = preg_replace($preg, 'index.php', $value);
}

// Change working directory and define the essential DRUPAL_ROOT constant.
chdir($drupalroot);
define('DRUPAL_ROOT', $drupalroot);
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';

// Make sure this file can only be used by simpletest.
drupal_bootstrap(DRUPAL_BOOTSTRAP_CONFIGURATION);
if (!drupal_valid_test_ua()) {
  header($_SERVER['SERVER_PROTOCOL'] . ' 403 Forbidden');
  exit;
}

// Inject conf-variables for testing.
global $conf;
if (!empty($_SERVER['HTTP_X_AUTHCACHE_BUILTIN_TEST_CACHE_BACKEND'])) {
  $module_root = dirname(dirname(dirname($__file__)));
  $authcache_root = dirname(dirname($module_root));
  $module_path = substr($module_root, strlen($drupalroot) + 1);
  $authcache_path = substr($authcache_root, strlen($drupalroot) + 1);
  $conf['cache_backends'][] = $authcache_path . '/authcache.cache.inc';
  $conf['cache_backends'][] = $module_path . '/authcache_builtin.cache.inc';
}

if (!empty($_SERVER['HTTP_X_AUTHCACHE_BUILTIN_TEST_MAX_AGE'])) {
  $conf['page_cache_maximum_age'] = $_SERVER['HTTP_X_AUTHCACHE_BUILTIN_TEST_MAX_AGE'];
}

drupal_bootstrap(DRUPAL_BOOTSTRAP_FULL);
menu_execute_active_handler();
