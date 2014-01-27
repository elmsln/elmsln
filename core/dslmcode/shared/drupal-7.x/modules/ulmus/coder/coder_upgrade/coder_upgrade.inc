<?php
/**
 * @file
 * Provides constants and utility functions.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * The default directory to store modules to be converted.
 * Relative to public stream wrapper path.
 */
define('DEADWOOD_DIR', 'coder_upgrade');

/**
 * The default directory to store modules to be converted.
 * Relative to public stream wrapper path.
 */
define('DEADWOOD_OLD', 'coder_upgrade/old');

/**
 * The default directory to store converted modules.
 * Relative to public stream wrapper path.
 */
define('DEADWOOD_NEW', 'coder_upgrade/new');

/**
 * The default directory to store patch files.
 * Relative to public stream wrapper path.
 */
define('DEADWOOD_PATCH', 'coder_upgrade/patch');

/**
 * Passes a string through t() and wraps the result in html entity <p>.
 */
function tp($string, $args = array()) {
  return '<p>' . t($string, $args) . '</p>';
}

/**
 * Scans a directory and finds all first-level directories beneath it.
 *
 * TODO Replace this with a call to file_scan_directory in include/files.inc.
 *
 * @param string $path Directory path.
 *
 * @return Array of directory names.
 */
function coder_upgrade_scan_directory($path) {
  static $ignore = array('.', '..', '.svn');
  $dirs = array();

  $path = $path . '/';
  if (!is_dir($path)) {
    return $dirs;
  }
  $files = scandir($path);
  foreach ($files as $file) {
    $file_path = $path . $file;
    if (is_dir($file_path) && !in_array(basename($file_path), $ignore)) {
      $dirs[] = $file;
    }
  }
  return $dirs;
}

/**
 * Removes all files from a directory and optionally removes the directory.
 *
 * @param string $path Directory path.
 */
function coder_upgrade_clean_directory($path, $remove_me = FALSE) {
  $path = $path . '/';
  if (!is_dir($path)) {
    return;
  }
  $files = scandir($path);
  foreach ($files as $file) {
    if ($file != '.' && $file != '..') {
      $file_path = $path . $file;
      if (is_dir($file_path)) {
        coder_upgrade_clean_directory($file_path, TRUE);
      }
      else {
        file_unmanaged_delete($file_path);
      }
    }
  }
  if ($remove_me) {
    rmdir($path);
  }
}

/**
 * Returns full directory path relative to sites directory.
 *
 * @param string $name
 *   Name of the directory.
 * @param boolean $add_slash
 *   Indicates whether to add a trailing slash.
 * @param boolean $stream_format
 *   Indicates whether to use the actual path or a stream protocol.
 *
 * @return string
 *   A string of the directory path.
 */
function coder_upgrade_directory_path($name, $add_slash = TRUE, $stream_format = FALSE) {
  $slash = $add_slash ? '/' : '';
  $prefix_no_slash = $stream_format ? file_default_scheme() . ':/' : file_stream_path();
  $prefix = $prefix_no_slash . '/';

  switch ($name) {
    case 'base':
      return $prefix . variable_get('coder_upgrade_dir', DEADWOOD_DIR) . $slash;
    case 'old':
      return $prefix . variable_get('coder_upgrade_dir_old', DEADWOOD_OLD) . $slash;
    case 'new':
      return $prefix . variable_get('coder_upgrade_dir_new', DEADWOOD_NEW) . $slash;
    case 'patch':
      return $prefix . variable_get('coder_upgrade_dir_patch', DEADWOOD_PATCH) . $slash;
    case '':
      return $prefix_no_slash; // @todo Is this correct with a stream format?
    default:
      return $prefix . $name . $slash;
  }
}

/**
 * Returns path to file or files directory.
 *
 * @param string $type
 *   Type of file to return path to. If blank, return directory path.
 *
 * @return string
 *   Path to file or directory.
 */
function coder_upgrade_path($type = '') {
  static $path = '';

  if (!$path) {
    $path = coder_upgrade_directory_path('base', FALSE);
  }
  return $type ? $path . '/' . $type . '.txt' : $path;
}

/**
 * Returns the local public directory path.
 *
 * Adapted from function removed from core on 2010-09-01
 * (see http://drupal.org/cvs?commit=415020).
 *
 * @return string
 *   A string containing the directory path of a stream. FALSE is returned if
 *   the scheme is invalid or a wrapper could not be instantiated.
 */
function file_stream_path($scheme = 'public') {
  global $_coder_upgrade_files_base;

  if (isset($_coder_upgrade_files_base)) {
    // This is being run as a separate process outside of Drupal.
    return $_coder_upgrade_files_base;
  }
  elseif ($wrapper = file_stream_wrapper_get_instance_by_scheme($scheme)) {
    return $wrapper->getDirectoryPath();
  }
  else {
    return FALSE;
  }
}

/**
 * Checks for proper installation of required modules and library.
 *
 * @todo Remove this once everyone gets used to the library concept.
 * @deprecated No longer used.
 *
 * @return boolean
 *   TRUE if required modules and library are installed; FALSE otherwise.
 */
function coder_upgrade_library_checks() {
  $modules = system_list('module_enabled');
  $messages = array();
  if (isset($modules['grammar_parser'])) {
    $messages[] = 'Grammar Parser should NOT be installed and enabled as a module.';
    $messages[] = 'Grammar Parser should be installed as a library using a 2.x release of Libraries API module.';
  }
  if (isset($modules['libraries'])) {
    if (!isset($modules['libraries']->info['version']) || substr($modules['libraries']->info['version'], 0, 6) != '7.x-2.') {
      $messages[] = 'Coder Upgrade requires a 7.x-2.x release of the Libraries API module.';
    }
    if (function_exists('libraries_get_path') && libraries_get_path('grammar_parser') === FALSE) {
      $messages[] = 'Grammar Parser should be installed as a library using a 2.x release of Libraries API module.';
    }
  }
  else {
    $messages[] = 'Coder Upgrade requires a 7.x-2.x release of the Libraries API module.';
    $messages[] = 'Grammar Parser should be installed as a library using a 2.x release of Libraries API module.';
  }
  foreach ($messages as $message) {
    drupal_set_message(t($message), 'error');
  }
  return empty($messages);
}
