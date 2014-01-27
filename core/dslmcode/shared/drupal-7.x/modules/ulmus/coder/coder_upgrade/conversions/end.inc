<?php
/**
 * @file
 * Provides conversion routines applied to the directory after routines are applied to the files.
 *
 * These routines use the grammar parser.
 *
 * The functions in this conversion routine file correspond to topics in the
 * category roadmap at http://drupal.org/node/394070 that are marked with a
 * green check mark in the Upgrade column.
 *
 * Copyright 2009-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/**
 * Implements hook_upgrade_end_alter().
 *
 * Processes the directory after upgrade routines are applied to the files.
 *
 * @param string $dirname
 *   The name of the directory with the converted files.
 */
function coder_upgrade_upgrade_end_alter($dirname) {
  global $_coder_upgrade_dirname, $_coder_upgrade_class_files;

  if (empty($_coder_upgrade_class_files)) {
    return;
  }

  $_coder_upgrade_dirname = $dirname;
  // Get list of files.
  $files = coder_upgrade_scan_directory_2($dirname, 'files');
  // In 6.x, add one hook_theme registry entry in each module.
  // In 7.x, add files entries to each .info file.
  coder_upgrade_add_file_entries($dirname, $files);
}

/**
 * Scans a directory and finds all files and/or directories beneath it.
 *
 * @todo Move to .inc file in parent directory.
 *
 * @param string $dirname
 *   Directory path to scan.
 *
 * @return array
 *   Array of file and/or directory names.
 */
function coder_upgrade_scan_directory_2($dirname, $retrieve = 'dirs') {
  $dirs = array();
  if (!is_dir($dirname)) {
    return $dirs;
  }

  static $ignore = array(/*'.', '..', '.bzr', '.git', '.svn',*/ 'CVS');
  $files = scandir($dirname);
  $dirname .= '/';

  foreach ($files as $key => $file) {
    $file_path = $dirname . $file;
    if (substr(basename($file_path), 0, 1) == '.' || in_array(basename($file_path), $ignore)) {
      // Ignore all hidden directories and CVS directory.
      unset($files[$key]);
    }
    elseif (is_dir($file_path)) {
      unset($files[$key]);
      $files[$key]['dir'] = $file;
      $files[$key]['entries'] = coder_upgrade_scan_directory_2($file_path, $retrieve);
      $dirs[] = $file;
    }
  }
  return $retrieve == 'dirs' ? $dirs : $files;
}

/**
 * Adds file entries to .info files.
 *
 * Module .info files must now specify all loadable code files explicitly.
 * http://drupal.org/node/224333#registry
 *
 * @param string $dirname
 *   Module directory path.
 * @param array $files
 *   Contents of directory $dirname.
 * @param array $items
 *   List of registry files.
 * @param string $path
 *   Subdirectory whose parent directory contains a module.
 */
function coder_upgrade_add_file_entries($dirname = '', $files = array(), &$items = array(), $path = '') {
  if (empty($files)) {
    return;
  }

  global $_coder_upgrade_dirname, $_coder_upgrade_class_files;

  // Extensions that indicate a module is present.
  $extensions = array('info', 'module');
  $info_file = '';

  if ($path != 'new' && ($path != '' || $dirname != $_coder_upgrade_dirname)) {
    // Scan subdirectory for .info file indicating presence of another module.
    foreach ($files as $file) {
      if (!is_array($file)) {
        $extension = pathinfo($file, PATHINFO_EXTENSION);
        if (in_array($extension, $extensions)) {
          // This subdirectory contains a module - so recurse.
          $dirname .= $path != '' ? '/' . $path : '';
          $path = 'new';
          $items2 = array();
          coder_upgrade_add_file_entries($dirname, $files, $items2, $path);
          return;
        }
      }
    }
  }
  // Clear path if we are starting another module.
  $path = $path == 'new' ? '' : $path;

  // Create list of files for registry.
  // TODO Allow for custom extensions!!!
  $extensions = array('inc', 'install', 'module', 'php', 'profile', 'test', 'theme', 'upgrade');
  $dirname .= $path != '' ? '/' . $path : '';
  $path = $path != '' ? $path . '/' : $path;
  foreach ($files as $file) {
    if (is_array($file)) {
      coder_upgrade_add_file_entries($dirname, $file['entries'], $items, $file['dir']);
    }
    else {
      $extension = pathinfo($file, PATHINFO_EXTENSION);
      if ($extension == 'php' && substr($file, -8) == '.tpl.php') {
        // Exclude template files.
      }
      elseif (in_array($extension, $extensions) && in_array($dirname . '/' . $file, $_coder_upgrade_class_files)) {
        $items[] = $dirname . '/' . $file;
      }
      elseif ($extension == 'info') {
        // Save the name of the .info file.
        $info_file = $dirname . '/' . $file;
      }
    }
  }

  if ($info_file != '') {
    $new = file_get_contents($info_file);
    // Remove any file entries from .info file.
    $from = "/^\s*files\[\]\s*=.*?$/m";
    $to = '';
    $new = preg_replace($from, $to, $new);
    // Add sorted entries to .info file.
    $new .= "\n";
    foreach ($items as $item) {
      $item = str_replace($dirname . '/', '', $item);
      $new .= "files[] = $item\n";
    }
    if (file_put_contents($info_file, $new) === FALSE) {
      clp(t('File could not be written: @file', array('@file' => $info_file)));
    }
  }
}
