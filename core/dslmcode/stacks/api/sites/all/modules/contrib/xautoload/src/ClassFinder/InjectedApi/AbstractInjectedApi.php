<?php

namespace Drupal\xautoload\ClassFinder\InjectedApi;

/**
 * To help testability, we use an injected API instead of just a return value.
 * The injected API can be mocked to provide a mocked file_exists(), and to
 * monitor all suggested candidates, not just the correct return value.
 */
abstract class AbstractInjectedApi implements InjectedApiInterface {

  /**
   * @var string
   *   The class name to look for. Set in the constructor.
   */
  protected $className;

  /**
   * @param $class_name
   *   Name of the class or interface we are trying to load.
   */
  function __construct($class_name) {
    $this->className = $class_name;
  }

  /**
   * This is done in the injected api object, so we can easily provide a mock
   * implementation.
   */
  function is_dir($dir) {
    return is_dir($dir);
  }

  /**
   * Get the name of the class we are looking for.
   *
   * @return string
   *   The class we are looking for.
   */
  function getClass() {
    return $this->className;
  }

  /**
   * Dummy method to force autoloading this class (or an ancestor).
   */
  static function forceAutoload() {
    // Do nothing.
  }
}
