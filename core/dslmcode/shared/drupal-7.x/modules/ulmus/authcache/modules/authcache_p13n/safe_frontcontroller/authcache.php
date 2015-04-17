<?php

/**
 * @file
 * Alternative front controller for user specific content fragments.
 *
 * In order to use this front-controller it is necessary to place it into the
 * drupal root directory and then add the following line to settings.php:
 *
 *     $conf['authcache_p13n_frontcontroller_path'] = 'authcache.php';
 *
 * Note: when authcache is not installed into sites/all/modules, the definition
 * of AUTHCACHE_P13N_ROOT below needs to be adapted also.
 */

/**
 * Root directory of Drupal installation.
 */
define('DRUPAL_ROOT', getcwd());

/**
 * Root directory of Authcache Personalization module.
 */
define('AUTHCACHE_P13N_ROOT', DRUPAL_ROOT . '/sites/all/modules/authcache/modules/authcache_p13n');

require_once DRUPAL_ROOT . '/includes/bootstrap.inc';
require_once AUTHCACHE_P13N_ROOT . '/includes/frontcontroller.inc';
$req = authcache_p13n_frontcontroller_prepare_request();
drupal_bootstrap(DRUPAL_BOOTSTRAP_SESSION);
authcache_p13n_frontcontroller_handle_request($req);
