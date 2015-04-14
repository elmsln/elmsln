<?php

/**
 * @file
 *   drush integration for chosen.
 */

/**
 * The Chosen plugin URI.
 */
define('CHOSEN_DOWNLOAD_URI', 'https://github.com/harvesthq/chosen/releases/download/v1.1.0/chosen_v1.1.0.zip');

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function chosen_drush_command() {
  $items = array();

  // The key in the $items array is the name of the command.
  $items['chosen-plugin'] = array(
    'callback' => 'drush_chosen_plugin',
    'description' => dt('Download and install the Chosen plugin.'),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH, // No bootstrap.
    'arguments' => array(
      'path' => dt('Optional. A path where to install the Chosen plugin. If omitted Drush will use the default location.'),
    ),
    'aliases' => array('chosenplugin'),
  );

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'.
 *
 * @param
 *   A string with the help section (prepend with 'drush:').
 *
 * @return
 *   A string with the help text for your command.
 */
function chosen_drush_help($section) {
  switch ($section) {
    case 'drush:chosen-plugin':
      return dt('Download and install the Chosen plugin from http://harvesthq.github.com/chosen, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the Chosen plugin.
 */
function drush_chosen_plugin() {
  $args = func_get_args();
  if (!empty($args[0])) {
    $path = $args[0];
  }
  else {
    $path = 'sites/all/libraries';
  }

  // Create the path if it does not exist.
  if (!is_dir($path)) {
    drush_op('mkdir', $path);
    drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
  }

  // Set the directory to the download location.
  $olddir = getcwd();
  chdir($path);

  // Download the zip archive.
  if ($filepath = drush_download_file(CHOSEN_DOWNLOAD_URI)) {
    $filename = basename($filepath);
    $dirname =  basename($filepath, '.zip');

    // Remove any existing Chosen plugin directory.
    if (is_dir($dirname) || is_dir('chosen')) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir('chosen', TRUE);
      drush_log(dt('A existing Chosen plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename, $dirname);

    // Change the directory name to "chosen" if needed.
    if ($dirname != 'chosen') {
      drush_move_dir($dirname, 'chosen', TRUE);
      $dirname = 'chosen';
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('Chosen plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Chosen plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}
