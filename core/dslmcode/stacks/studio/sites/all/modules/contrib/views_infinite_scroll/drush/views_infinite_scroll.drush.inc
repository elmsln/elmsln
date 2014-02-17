<?php

/**
 * @file
 *   drush integration for views_infinite_scroll.
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
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function views_infinite_scroll_drush_command() {
  $items = array();

  $items['dl-autopager'] = array(
    'callback' => 'views_infinite_scroll_drush_autopager_download',
    'description' => dt('Downloads the required autopager jquery plugin.'),
  );
  return $items;
}

/**
 * Implements hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'
 *
 * @param
 *   A string with the help section (prepend with 'drush:')
 *
 * @return
 *   A string with the help text for your command.
 */
function views_infinite_scroll_drush_help($section) {
  switch ($section) {
    case 'drush:dl-autopager':
      return dt("Downloads the required autopager jquery plugin.");
  }
}

/**
 * Example drush command callback.
 *
 * This is where the action takes place.
 *
 * In this function, all of Drupals API is (usually) available, including
 * any functions you have added in your own modules/themes.
 *
 * To print something to the terminal window, use drush_print().
 *
 */
function views_infinite_scroll_drush_autopager_download() {
  if (module_exists('libraries')) {
    $path = 'sites/all/libraries/autopager';

    // Create the path if it does not exist.
    if (!is_dir($path)) {
      drush_op('mkdir', $path);
      drush_log(dt('Directory @path was created', array('@path' => $path)), 'notice');
    }
  }
  else {
    $path = drupal_get_path('module', 'views_infinite_scroll') . '/js';
  }
  drush_op('chdir', $path);
  // Download the plugin.
  if (drush_shell_exec('wget http://jquery-autopager.googlecode.com/files/jquery.autopager-1.0.0.js')) {
    drush_log(dt('jquery.autopager-1.0.0.js has been downloaded to @path', array('@path' => $path)), 'success');
  }
  else {
    drush_log(dt('Drush was unable to download jquery.autopager-1.0.0.js to @path', array('@path' => $path)), 'error');
  }
}
