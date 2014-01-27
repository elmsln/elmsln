<?php
/**
 * @file
 * Provides constants and utility functions used during the conversion process.
 *
 * Copyright 2008-11 by Jim Berry ("solotandem", http://drupal.org/user/240748)
 */

/*
 * The following functions are declared to allow the code to be executed as a
 * separate process outside of Drupal.
 */

if (!function_exists('drupal_get_path')) {
  function drupal_get_path($type, $name) {
    global $_coder_upgrade_libraries_base, $_coder_upgrade_modules_base;
    return $type == 'library' ? $_coder_upgrade_libraries_base . "/$name" : $_coder_upgrade_modules_base . "/$name";
  }
}

if (!function_exists('module_load_include')) {
  // Create a function that could be in core.
  // Rename parameters to more accurately reflect use. Add type parameter.
  function drupal_load_include($ext, $project, $name = NULL, $type = 'module') {
    if (empty($name)) {
      $name = $project;
    }

    if (function_exists('drupal_get_path')) {
      $file = DRUPAL_ROOT . '/' . drupal_get_path($type, $project) . "/$name.$ext";
      if (is_file($file)) {
        require_once $file;
        return $file;
      }
    }
    return FALSE;
  }

  function module_load_include($ext, $module, $name = NULL) {
    return drupal_load_include($ext, $module, $name);
  }
}

if (!function_exists('libraries_load')) {
  function libraries_load($name, $variant = NULL) {
    if (!isset($name) || $name != 'grammar_parser') {
      return FALSE;
    }

    $library = $name;
    $ext = 'inc';
    foreach (array('parser', 'reader', 'writer', 'editor', 'list', 'object') as $name) {
      drupal_load_include($ext, $library, "engine/$name", 'library');
    }
    return TRUE;
  }
}

if (!function_exists('drupal_alter')) {
  function drupal_alter($type, &$data, &$context1 = NULL, &$context2 = NULL) {
    global $_coder_upgrade_upgrade_modules;

    $hook = $type . '_alter';
    foreach ($_coder_upgrade_upgrade_modules as $module) {
      $function = $module . '_' . $hook;
      cdp($function, '$function');
      if (function_exists($function)) {
        $function($data, $context1, $context2);
      }
    }
  }
}

if (!function_exists('file_unmanaged_delete')) {
  function file_unmanaged_delete($path) {
    if (is_dir($path)) {
      return FALSE;
    }
    if (is_file($path)) {
      return unlink($path);
    }
  }
}

if (!function_exists('variable_get')) {
  function variable_get($name, $default = NULL) {
    global $_coder_upgrade_variables;

    return isset($_coder_upgrade_variables[$name]) ? $_coder_upgrade_variables[$name] : $default;
  }
}
