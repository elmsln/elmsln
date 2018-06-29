<?php

namespace Drupal\xautoload\ClassLoader;

/**
 * Behaves mostly like the Symfony ClassLoader classes.
 */
interface ClassLoaderInterface {

  /**
   * Registers this instance as an autoloader.
   *
   * @param boolean $prepend
   *   If TRUE, the loader will be prepended. Otherwise, it will be appended.
   */
  function register($prepend = FALSE);

  /**
   * Unregister this instance as an autoloader.
   */
  function unregister();

  /**
   * Callback for class loading. This will include ("require") the file found.
   *
   * @param string $class
   *   The class to load.
   */
  function loadClass($class);
}
