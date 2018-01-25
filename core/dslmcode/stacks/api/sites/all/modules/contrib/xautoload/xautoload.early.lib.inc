<?php

use Drupal\xautoload\ClassFinder\ClassFinderInterface;
use Drupal\xautoload\ClassFinder\InjectedApi\LoadClassGetFileInjectedApi;
use Drupal\xautoload\ClassFinder\InjectedApi\LoadClassInjectedAPI;
use Drupal\xautoload\DIC\ServiceContainer;
use Drupal\xautoload\DIC\ServiceFactory;
use Drupal\xautoload\Main;

define('XAUTOLOAD_LIB_DIR', __DIR__ . '/lib');
define('XAUTOLOAD_SRC_DIR', __DIR__ . '/src');
define('XAUTOLOAD_VARNAME_CACHE_TYPES', 'xautoload_cache_types');
define('XAUTOLOAD_VARNAME_CACHE_LAZY', 'xautoload_cache_lazy');
define('XAUTOLOAD_VARNAME_REPLACE_CORE', 'xautoload_replace_core');
define('XAUTOLOAD_VARNAME_CACHE_PREFIX', 'xautoload_cache_prefix');
define('XAUTOLOAD_CACHENAME_LIBRARIES_INFO', 'xautoload_libraries_info');


// Public API functions.
// -----------------------------------------------------------------------------

/**
 * Get the class finder object.
 * This is the public version of _xautoload_finder().
 *
 * @return ClassFinderInterface
 */
function xautoload_get_finder() {
  // Get it from the registry.
  return xautoload()->classFinder;
}

/**
 * Get a service object from the registry.
 * Services are lazy-created first time you need them.
 *
 * @param string $key
 *   Identifier of the service within the registry.
 *   The xautoload_ServiceFactory should have a method with the same name.
 *   The recommended way (esp if you ask your IDE) is to omit this parameter and
 *   use xautoload()->$key instead.
 *
 * @return Main|object
 */
function xautoload($key = 'main') {
  static $service_registry;
  static $main;
  if (!isset($service_registry)) {
    $service_factory = new ServiceFactory();
    $service_registry = new ServiceContainer($service_factory);
    $main = $service_registry->main;
  }
  switch ($key) {
    case 'main':
      return $main;
    default:
      // Legacy..
      return $service_registry->get($key);
  }
}


// "Private" functions.
// -----------------------------------------------------------------------------

/**
 * Creates and registers the xautoload class loader.
 *
 * Registers the xautoload_ prefix and the Drupal\xautoload\\ namespace, but
 * does not register any other Drupal-specific stuff yet. This is because this
 * might be called from settings.php, while some parts of Drupal are not fully
 * initialized yet.
 */
function _xautoload_register() {

  // Check that this runs only once.
  static $_first_run = TRUE;
  if (!$_first_run) {
    return;
  }
  $_first_run = FALSE;

  // Register a temporary loader.
  spl_autoload_register('_xautoload_autoload_temp', TRUE, TRUE);

  // Some classes need to be loaded manually. Believe it!
  LoadClassInjectedAPI::forceAutoload();
  LoadClassGetFileInjectedApi::forceAutoload();
  \Drupal\xautoload\Util::forceAutoload();

  $finder = xautoload()->finder;
  $finder->register();

  // Register the 'Drupal\xautoload\\' namespace.
  $finder->addPsr4('Drupal\xautoload\\', XAUTOLOAD_SRC_DIR . '/');

  // Register the "xautoload_" prefix for legacy classes.
  $finder->addPearFlat('xautoload_', __DIR__ . '/legacy/lib/');

  // Unregister the temporary loader.
  spl_autoload_unregister('_xautoload_autoload_temp');
}

/**
 * Temporary loader callback, to avoid any module_load_include()
 * while building the real autoloader.
 *
 * @param string $name
 *   Name of the class or interface we want to load.
 *
 * @throws \Exception
 */
function _xautoload_autoload_temp($name) {

  if ('Drupal\xautoload\\' === substr($name, 0, 17)) {
    // PSR-4 case
    $file = XAUTOLOAD_SRC_DIR . '/' . str_replace('\\', '/', substr($name, 17)) . '.php';
    require_once $file;
  }
  elseif ('xautoload_' === substr($name, 0, 10) && FALSE === strpos($name, '\\')) {
    // Legacy case
    $file = XAUTOLOAD_LIB_DIR . '/' . str_replace('_', '/', substr($name, 10)) . '.php';
    require_once $file;
  }
}
