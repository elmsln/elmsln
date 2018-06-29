<?php
/**
 * @file xautoload.emulate.inc
 *
 * This file contains code to copy+paste and adapt, if you want to use PSR-0 or
 * xautoload-style autoloading, without making xautoload an explicit dependency.
 */


/**
 * Register a dedicated class loader only for this module.
 *
 * You want to rename this function as something like mymodule_include(),
 * and call it any time to initialize xautoloading for a specific module.
 */
function _MYMODULE_include() {
  static $first_run = TRUE;
  if (!$first_run) {
    return;
  }
  $first_run = FALSE;

  if (!module_exists('xautoload')) {
    spl_autoload_register('_MYMODULE_autoload');
  }
  // This could be the place for some procedural includes.
  // ..
}


/**
 * The autoload callback for this specific module, used if xautoload is not
 * present.
 *
 * You want to replace any "MYMODULE" with your module name.
 *
 * @param string $class
 *   The class we want to load.
 */
function _MYMODULE_autoload($class) {

  static $lib_dir;
  if (!isset($lib_dir)) {
    $lib_dir = __DIR__ . '/lib/';
  }

  // Replace MYMODULE with your module name.
  $module = 'MYMODULE';
  $l = strlen($module);

  if (FALSE !== $nspos = strrpos($class, '\\')) {
    // PSR-0 mode. Omit this if you use only the PHP 5.2 compatibility mode.
    if ("Drupal\\$module\\" === substr($class, 0, $l + 8)) {
      $namespace = substr($class, 0, $nspos);
      $classname = substr($class, $nspos + 1);
      $path = $lib_dir . str_replace('\\', '/', $namespace) . '/' . str_replace('_', '/', $classname) . '.php';
      if (is_file($path)) {
        include $path;
      }
    }
  }
  else {
    // PHP 5.2 compatibility mode. Omit this if you use only PSR-0.
    if ($module . '_' === substr($class, 0, $l + 1)) {
      $path = $lib_dir . str_replace('_', '/', $class) . '.php';
      if (is_file($path)) {
        include $path;
      }
    }
  }
}
