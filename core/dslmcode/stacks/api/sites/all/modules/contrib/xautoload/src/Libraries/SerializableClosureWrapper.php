<?php


namespace Drupal\xautoload\Libraries;

/**
 * A wrapper that allows serialization of closures from hook_libraries_info().
 */
class SerializableClosureWrapper {

  /**
   * The closure
   *
   * @var \Closure
   */
  private $closure;

  /**
   * Module that implements hook_libraries_info()
   *
   * @var string
   */
  private $moduleName;

  /**
   * Name of the library that has this closure for xautoload.
   *
   * @var string
   */
  private $libraryName;

  /**
   * @param \Closure $closure
   * @param string $moduleName
   * @param string $libraryName
   */
  public function __construct($closure, $moduleName, $libraryName) {
    $this->closure = $closure;
    $this->moduleName = $moduleName;
    $this->libraryName = $libraryName;
  }

  public function __sleep() {
    return array('moduleName', 'libraryName');
  }

  /**
   * @param \Drupal\xautoload\Adapter\LocalDirectoryAdapter $adapter
   */
  public function __invoke($adapter) {
    $closure = $this->lazyGetClosure();
    if ($closure instanceof \Closure) {
      $closure($adapter);
    }
  }

  /**
   * @return \Closure|FALSE
   */
  private function lazyGetClosure() {
    return isset($this->closure)
      ? $this->closure
      : $this->closure = $this->loadClosure();
  }

  /**
   * @return \Closure|FALSE
   */
  private function loadClosure() {
    $source_function = $this->moduleName . '_libraries_info';
    if (!function_exists($source_function)) {
      return FALSE;
    }
    $module_libraries = $source_function();
    if (!isset($module_libraries[$this->libraryName]['xautoload'])) {
      return FALSE;
    }
    $closure_candidate = $module_libraries[$this->libraryName]['xautoload'];
    if (!$closure_candidate instanceof \Closure) {
      return FALSE;
    }
    return $closure_candidate;
  }

}
