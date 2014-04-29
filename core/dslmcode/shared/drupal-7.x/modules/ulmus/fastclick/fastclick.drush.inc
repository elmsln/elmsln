<?php

/**
 * @file
 * Drush integration for FastClick.
 */

// URL to download the FastClick JavaScript file.
define('FASTCLICK_URL', 'https://raw.github.com/ftlabs/fastclick/master/lib/fastclick.js');

/**
 * Implements hook_drush_command().
 */
function fastclick_drush_command() {

  $items['fastclick-download'] = array(
    'description' => dt('Downloads the required fastclick.js file.'),
    'options' => array(
      'force' => dt('Downloads the library even if it already exists.'),
    ),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function fastclick_drush_help($section) {

  switch ($section) {
    case 'drush:fastclick-download':
      return dt("Downloads the required JavaScript file for FastClick. Use with '--force' to overwrite existing file.");
  }
}

/**
 * Downloads fastclick.js file.
 */
function drush_fastclick_download() {

  if (!function_exists('libraries_get_path')) {
    drush_log(dt('Libraries module is required.'), 'error');
    return FALSE;
  }

  $path = libraries_get_path('fastclick');
  if (!$path) {
    $path = 'sites/all/libraries/fastclick';
  }

  // Create the path if it does not exist yet.
  if (!is_dir($path)) {
    drush_mkdir($path);
  }

  // Download the file.
  if (is_file($path . '/fastclick.js') && !drush_get_option('force')) {
    drush_log(dt('fastclick.js file already exists. No download required. Use --force to overwrite.'), 'ok');
    return TRUE;
  }
  elseif (drush_op('chdir', $path) && (drush_shell_exec('curl -O ' . FASTCLICK_URL) || drush_shell_exec('wget --no-check-certificate ' . FASTCLICK_URL))) {
    drush_log(dt('Latest fastclick.js file has been downloaded to @path', array('@path' => $path)), 'success');
    return TRUE;
  }
  else {
    drush_log(dt('Drush was unable to download fastclick.js file to @path', array('@path' => $path)), 'error');
    return FALSE;
  }
}

/**
 * Implements drush_MODULE_post_COMMAND().
 *
 * When enabling the module Drush will try to download fastclick.js file.
 */
function drush_fastclick_post_pm_enable() {

  $extensions = func_get_args();

  // Deal with comma delimited extension list.
  if (strpos($extensions[0], ',') !== FALSE) {
    $extensions = explode(',', $extensions[0]);
  }

  if (in_array('fastclick', $extensions) && !drush_get_option('skip')) {

    // Download the library.
    drush_fastclick_download();
  }
}
