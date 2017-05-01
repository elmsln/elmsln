<?php

/**
 * @file
 * Default front controller for user specific content fragments.
 *
 * Note: This script tries to detect the path to the Drupal root directory
 * automatically on every request and also rewrites values in the $_SERVER
 * variable. This process may fail in some server environments.
 *
 * On production systems it is therefore highly recommended to install and
 * configure the safe front controller by following the directions given in
 * authcache/modules/authcache_p13n/safe_frontcontroller/authcache.php
 */

// Detect root directory of the Drupal installation.
$__file__ = isset($_SERVER['SCRIPT_FILENAME']) ? $_SERVER['SCRIPT_FILENAME'] : __FILE__;
if ($__file__[0] !== '/') {
  $__file__ = str_replace(DIRECTORY_SEPARATOR, '/', $__file__);
}
$drupalroot = preg_replace('#(/(sites|profiles)/([^/]+))?/modules(/.*)?/authcache_p13n/frontcontroller/authcache.php$#', '', $__file__);

if ($drupalroot === $__file__) {
  trigger_error('Authcache P13n front controller: failed to locate Drupal root directory', E_USER_ERROR);
  exit();
}

// Relocate contents of $_SERVER variable to DRUPAL_ROOT by removing path
// components pointing to the authcache front controller.
$preg = '|' . preg_quote(substr($__file__, strlen($drupalroot) + 1), '|') . '|';
foreach ($_SERVER as $key => $value) {
  $_SERVER[$key] = preg_replace($preg, 'authcache.php', $value);
}

// Change working directory and define the essential DRUPAL_ROOT constant.
chdir($drupalroot);
define('DRUPAL_ROOT', $drupalroot);
define('AUTHCACHE_P13N_ROOT', dirname(dirname($__file__)));

// Load settings.php
require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once AUTHCACHE_P13N_ROOT . '/includes/frontcontroller.inc';
$req = authcache_p13n_frontcontroller_prepare_request();
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
authcache_p13n_frontcontroller_handle_request($req);
