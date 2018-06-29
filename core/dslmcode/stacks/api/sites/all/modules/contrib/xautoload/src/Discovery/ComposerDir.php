<?php

namespace Drupal\xautoload\Discovery;

use Drupal\xautoload\Adapter\ClassFinderAdapter;

class ComposerDir {

  /**
   * @var string
   */
  protected $dir;

  /**
   * @param string $dir
   *
   * @return self
   *
   * @throws \Exception
   */
  static function create($dir) {
    if (!is_dir($dir)) {
      throw new \Exception("Composer directory '$dir' does not exist.");
    }
    return new self($dir);
  }

  /**
   * @param string $dir
   */
  protected function __construct($dir) {
    $this->dir = $dir;
  }

  /**
   * @param ClassFinderAdapter $adapter
   */
  function writeToAdapter($adapter) {

    // PSR-0 namespaces / prefixes
    if (is_file($this->dir . '/autoload_namespaces.php')) {
      $prefixes = require $this->dir . '/autoload_namespaces.php';
      if (!empty($prefixes)) {
        $adapter->addMultiplePsr0($prefixes);
      }
    }

    // PSR-4 namespaces
    if (is_file($this->dir . '/autoload_psr4.php')) {
      $map = require $this->dir . '/autoload_psr4.php';
      if (!empty($map)) {
        $adapter->addMultiplePsr4($map);
      }
    }

    // Class map
    if (is_file($this->dir . '/autoload_classmap.php')) {
      $class_map = require $this->dir . '/autoload_classmap.php';
      if (!empty($class_map)) {
        $adapter->addClassMap($class_map);
      }
    }

    // Include path
    if (is_file($this->dir . '/include_paths.php')) {
      $include_paths = require $this->dir . '/include_paths.php';
      if (!empty($include_paths)) {
        array_push($include_paths, get_include_path());
        set_include_path(join(PATH_SEPARATOR, $include_paths));
      }
    }

    // Include files
    if (is_file($this->dir . '/autoload_files.php')) {
      $include_files = require $this->dir . '/autoload_files.php';
      foreach ($include_files as $file) {
        require $file;
      }
    }
  }
} 