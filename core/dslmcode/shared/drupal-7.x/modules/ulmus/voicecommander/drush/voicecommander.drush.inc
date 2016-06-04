<?php

/**
 * @file
 * Drush integration for voicecommander.
 */

/**
 * Implements hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * See `drush topic docs-commands` for a list of recognized keys.
 */
function voicecommander_drush_command() {
  $items = array();

  // The key in the $items array is the name of the command.
  $items['voicecommander'] = array(
    'callback'    => 'drush_voicecommander',
    'description' => dt('Download and install the Annyang plugin.'),
    'bootstrap'   => DRUSH_BOOTSTRAP_DRUSH,
    'arguments'   => array(
      'path' => dt('Optional. A path where to install the Annyang plugin If omitted Drush will use the default location.'),
    ),
    'aliases'     => array('vcom', 'vc'),
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 */
function voicecommander_drush_help($section) {
  switch ($section) {
    case 'drush:voicecommander':
      return dt('Download and install the Annyang plugin for Voice Commander module, default location is sites/all/libraries.');
  }
}

/**
 * Command to download the Annyang plugin.
 */
function drush_voicecommander() {
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
  if ($filepath = drush_download_file(VOICECOMMANDER_ANNYANG_PLUGIN_URL)) {
    $filename = basename($filepath);
    $dirname = VOICECOMMANDER_ANNYANG_DOWNLOAD_PREFIX . basename($filepath, '.zip');

    // Remove any existing Annyang directory.
    if (is_dir($dirname) || is_dir(VOICECOMMANDER_ANNYANG_PLUGIN_NAME)) {
      drush_delete_dir($dirname, TRUE);
      drush_delete_dir(VOICECOMMANDER_ANNYANG_PLUGIN_NAME, TRUE);
      drush_log(dt('A existing Annyang plugin was deleted from @path', array('@path' => $path)), 'notice');
    }

    // Decompress the zip archive.
    drush_tarball_extract($filename);

    // Change the directory name to "annyang" if needed.
    if ($dirname != VOICECOMMANDER_ANNYANG_PLUGIN_NAME) {
      drush_move_dir($dirname, VOICECOMMANDER_ANNYANG_PLUGIN_NAME, TRUE);
      $dirname = VOICECOMMANDER_ANNYANG_PLUGIN_NAME;
    }
  }

  if (is_dir($dirname)) {
    drush_log(dt('Annyang plugin has been installed in @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to install the Annyang plugin to @path', array('@path' => $path)), 'error');
  }

  // Set working directory back to the previous working directory.
  chdir($olddir);
}

/**
 * Take action after a project has been downloaded.
 */
function drush_voicecommander_post_pm_enable() {
  drupal_flush_all_caches();
}
