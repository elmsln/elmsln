<?php

namespace Drupal\xautoload;

use Drupal\xautoload\DIC\ServiceContainer;
use Drupal\xautoload\DIC\ServiceContainerInterface;

class Main implements ServiceContainerInterface {

  /**
   * @var ServiceContainer
   *   The service container, similar to a DIC.
   */
  protected $services;

  /**
   * @param ServiceContainer $services
   */
  function __construct($services) {
    $this->services = $services;
  }

  /**
   * @return ServiceContainer
   */
  function getServiceContainer() {
    return $this->services;
  }

  /**
   * Invalidate all values stored in APC.
   */
  function flushCache() {
    $this->services->cacheManager->renewCachePrefix();
  }

  /**
   * Register a module in early bootstrap, or from modulename.install.
   *
   * This is only needed for modules that need autoloading very early in the
   * request, or e.g. during uninstall, or any situation that xautoload cannot
   * catch up with.
   *
   * The method will register all autoloading schemes for this module that are
   * supported by default:
   * - PSR-0: "Drupal\\$module\\Foo" => "$module_dir/lib/Drupal/$module/Foo.php"
   * - PEAR-FLAT: $module . "_Foo_Bar" => "$module_dir/lib/Foo/Bar.php"
   *
   * It will not register anything for PSR-4, since it is not clear whether this
   * will be in "/lib/" or "/src/" or elsewhere.
   *
   * Suggested usage: (in your $modulename.module, or $modulename.install):
   *
   *     xautoload()->registerModule(__FILE__);
   *
   * @param string $__FILE__
   *   File path to a *.module or *.install file.
   *   The basename of the file MUST be the module name.
   *   It is recommended to call this from the respective file itself, using the
   *   __FILE__ constant for this argument.
   */
  function registerModule($__FILE__) {
    $this->services->extensionNamespaces->registerExtension($__FILE__);
  }

  /**
   * Register a module as PSR-4, in early bootstrap or from modulename.install
   *
   * This can be used while Drupal 8 is still undecided whether PSR-4 class
   * files should live in "lib" or in "src" by default.
   *
   * Suggested usage: (in your $modulename.module, or $modulename.install):
   *
   *     // E.g. "Drupal\\$module\\Foo" => "$module_dir/lib/Foo.php"
   *     xautoload()->registerModulePsr4(__FILE__, 'lib');
   *
   * or
   *
   *     // E.g. "Drupal\\$module\\Foo" => "$module_dir/src/Foo.php"
   *     xautoload()->registerModulePsr4(__FILE__, 'src');
   *
   * or
   *
   *     // E.g. "Drupal\\$module\\Foo" => "$module_dir/psr4/Foo.php"
   *     xautoload()->registerModulePsr4(__FILE__, 'psr4');
   *
   * @param string $__FILE__
   *   File path to a *.module or *.install file.
   *   The basename of the file MUST be the module name.
   *   It is recommended to call this from the respective file itself, using the
   *   __FILE__ constant for this argument.
   * @param string $subdir
   *   The PSR-4 base directory for the module namespace, relative to the module
   *   directory. E.g. "src" or "lib".
   */
  function registerModulePsr4($__FILE__, $subdir) {
    $this->services->extensionNamespaces->registerExtensionPsr4($__FILE__, $subdir);
  }

  /**
   * Magic getter for service objects. This lets this class act as a proxy for
   * the service container.
   *
   * @param string $key
   * @return mixed
   */
  function __get($key) {
    return $this->services->__get($key);
  }
}
