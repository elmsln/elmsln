<?php
/**
  * @file
  *   drush integration for imagesloaded.
  */

 /**
  * The URI to the imagesloaded.js library.
  */
define('IL_MIN_DOWNLOAD_URI', 'https://raw.github.com/desandro/imagesloaded/v2.1.2/jquery.imagesloaded.min.js');
define('IL_SOURCE_DOWNLOAD_URI', 'https://raw.github.com/desandro/imagesloaded/v2.1.2/jquery.imagesloaded.js');
/*
 * Implements hook_drush_command().
 *
 * @return
 *  An associative array describing your command(s).
 */
function equalheights_drush_command() {
  $items = array();
  $items['eqheights-download'] = array(
    'callback' => 'equalheights_drush_imagesloaded_download',
    'description' => dt('Downloads the required imagesloaded.js library from https://github.com/desandro/imagesloaded.'),
    'aliases' => array('ehdl'),
    'arguments' => array(

    ),
  );
  return $items;
}

/*
 * Defining drush command implementation.
 */
function equalheights_drush_imagesloaded_download(){
  if (function_exists('libraries_get_path')) {
    $path = libraries_get_path('imagesloaded');
    if ($path === FALSE) {
      $path = 'sites/all/libraries/imagesloaded';
    }
  }
  else {
    drupal_set_message(t('Please download and install Libraries API 2.x'));
  }

  // Create the path if it does not exist yet.
  if (!is_dir($path)) {
    drush_mkdir($path);
  }

  // Download the file and report back
  if (is_file($path . '/jquery.imagesloaded.min.js')) {
    drush_log('Imagesloaded.js already present. No download required.', 'ok');
    return TRUE;
  }
  elseif (drush_op('chdir', $path) && (drush_shell_exec('curl -O '. IL_MIN_DOWNLOAD_URI) || drush_shell_exec('wget --no-check-certificate ' . IL_MIN_DOWNLOAD_URI))
    && (drush_shell_exec('curl -O '. IL_SOURCE_DOWNLOAD_URI) || drush_shell_exec('wget --no-check-certificate ' . IL_SOURCE_DOWNLOAD_URI))) {
    drush_log(dt('The latest imagesloaded.js library has been downloaded to @path', array('@path' => $path)), 'success');
    return TRUE;
  }
  else {
    drush_log(dt('Drush was unable to download the imagesloaded.js library to @path', array('@path' => $path)), 'error');
    return FALSE;
  }
}

/*
 * Implements drush_module_post_command().
 */
function drush_equalheights_post_pm_enable() {
  $extensions = func_get_args();
  // Deal with comma delimited extension list.
  if (strpos($extensions[0], ',') !== FALSE) {
    $extensions = explode(',', $extensions[0]);
  }

  if (in_array('equalheights', $extensions) && !drush_get_option('skip')) {
    // First attempt to download the JS library.
    equalheights_drush_imagesloaded_download();
  }
}

/*
 * Implements hook_drush_help().
 *
 * @param
 *  A string with the help section (prepend with 'drush:')
 * @return
 *  A string with the help text for your command.
 */
function equalheights_drush_help($section) {
  switch ($section) {
    case 'drush:eqheights-download':
      return dt("Downloads the required imagesloaded.js library from https://github.com/desandro/imagesloaded. Takes an optional path argument.");
  }
}
