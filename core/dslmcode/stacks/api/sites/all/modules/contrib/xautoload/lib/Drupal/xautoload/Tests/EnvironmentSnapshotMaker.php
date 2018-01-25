<?php

namespace Drupal\xautoload\Tests;

use Drupal\xautoload\Util;

class EnvironmentSnapshotMaker {

  /**
   * @var array
   */
  protected static $snapshots = array();

  /**
   * @param string $module
   * @param string $phase
   * @param string[] $classes
   */
  static function takeSnapshot($module, $phase, $classes) {
    self::$snapshots[$module][$phase] = self::buildSnapshot($classes);
  }

  /**
   * @param string $module
   *
   * @return array
   */
  static function getSnapshots($module) {
    return isset(self::$snapshots[$module])
      ? self::$snapshots[$module]
      : array();
  }

  /**
   * @param string[] $classes
   *
   * @return array
   */
  protected static function buildSnapshot($classes) {

    $observations = array();

    // Test that all classes are available immediately at boot time.
    foreach ($classes as $class) {
      $observations['class_exists'][$class] = class_exists($class);
    }

    // Check variable_get().
    $observations[XAUTOLOAD_VARNAME_CACHE_TYPES] = variable_get(XAUTOLOAD_VARNAME_CACHE_TYPES);
    $observations[XAUTOLOAD_VARNAME_CACHE_LAZY] = variable_get(XAUTOLOAD_VARNAME_CACHE_LAZY);

    $observations['db_connection_info'] = \Database::getConnectionInfo();

    $spl_autoload_stack = array();
    foreach (spl_autoload_functions() as $callback) {
      $spl_autoload_stack[] = Util::callbackToString($callback);
    }
    $observations['spl_autoload_functions'] = $spl_autoload_stack;

    return $observations;
  }
}
