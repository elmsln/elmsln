<?php

/**
 * This file is used both in drupal and in callback files.
 */

// prepare variables
if (!defined("DRUPAL_ROOT")) {
  // We're not in drupal but we need 'some' functionality so...
  _radioactivity_light_initialization();
}
else {
  // We're in drupal, setup necessary vars
  define("VAR_RADIOACTIVITY_CHECKSUM_SALT", variable_get("radioactivity_checksum_salt", "undefined"));
  define("VAR_RADIOACTIVITY_TEMP_DIR", variable_get('radioactivity_temp_dir', sys_get_temp_dir()));
  if (class_exists('Memcache') || class_exists("Memcached")) {
    define("VAR_RADIOACTIVITY_MEMCACHED_HOST", variable_get("radioactivity_memcached_host", "localhost"));
    define("VAR_RADIOACTIVITY_MEMCACHED_PORT", variable_get("radioactivity_memcached_port", "11211"));
  }
}

/**
 * Get the config file path of R
 */
function _radioactivity_get_config_file_path() {
  $dir = dirname(__FILE__);
  $config_file = $dir . "/radioactivity-bootstrap.cfg.inc";
  return $config_file;
}

/**
 * Do a light system initialization
 */
function _radioactivity_light_initialization() {
  if (!defined("RADIOACTIVITY_BOOTSTRAPPED")) {

    $config_file = _radioactivity_get_config_file_path();

    if (file_exists($config_file)) {

      include ($config_file);

    }
    else {

      _radioactivity_require_bootstrapping();
      // Grab the checksum variable
      $var = variable_get('radioactivity_checksum_salt', 'undefined');
      define("VAR_RADIOACTIVITY_CHECKSUM_SALT", $var);
      define("VAR_RADIOACTIVITY_TEMP_DIR", variable_get('radioactivity_temp_dir', sys_get_temp_dir()));
      variable_set("radioactivity_config_warning", TRUE);
      if (class_exists('Memcache') || class_exists("Memcached")) {
        define("VAR_RADIOACTIVITY_MEMCACHED_HOST", variable_get("radioactivity_memcached_host", "localhost"));
        define("VAR_RADIOACTIVITY_MEMCACHED_PORT", variable_get("radioactivity_memcached_port", "11211"));
      }
    }

    define("RADIOACTIVITY_BOOTSTRAPPED", TRUE);
  }
}

/**
 * Do a light boostrap
 */
function _radioactivity_require_bootstrapping() {
  // use the VERSION to figure out if we've done bootstrapping already
  if (!defined("VERSION")) {

    include "radioactivity.module";

    if (!defined("VAR_RADIOACTIVITY_DRUPAL_ROOT")) {
      define("VAR_RADIOACTIVITY_DRUPAL_ROOT", $_SERVER['DOCUMENT_ROOT']);
    }
    define('DRUPAL_ROOT', VAR_RADIOACTIVITY_DRUPAL_ROOT);
    chdir(DRUPAL_ROOT);

    if (!file_exists('./includes/bootstrap.inc')) {
      die("Unable to figure out bootstrapping directory!");
    }

    require_once './includes/bootstrap.inc';
    drupal_bootstrap(DRUPAL_BOOTSTRAP_VARIABLES);
    variable_set("radioactivity_bootstrap_warning", TRUE);
  }
}

/**
 * Generate a checksum for given data
 */
function _radioactivity_checksum_generate($data) {
  $temp = $data;
  unset($temp['checksum']);
  ksort($temp);
  $temp = join(',', $temp);
  return md5(VAR_RADIOACTIVITY_CHECKSUM_SALT . $temp);
}

/**
 * Validate checksum against given data
 */
function _radioactivity_checksum_validate($data, $checksum) {
  return strcmp(_radioactivity_checksum_generate($data), $checksum) === 0;
}

/**
 * Validate (and filter) a payload
 */
function _radioactivity_validate_incident($incident) {
  return _radioactivity_checksum_validate($incident, $incident['checksum']);
}

/**
 * Prepare payload
 */
function _radioactivity_prepare_incident($incident) {
  ksort($incident);
  $incident['checksum'] = _radioactivity_checksum_generate($incident);
  return $incident;
}
