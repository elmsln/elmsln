<?php

namespace Drupal\xautoload\Discovery;

use Drupal\xautoload\Adapter\ClassFinderAdapter;

class ComposerJson {

  /**
   * @var array
   */
  protected $data;

  /**
   * @var string
   */
  protected $pathPrefix;

  /**
   * @param string $file
   *
   * @return self
   *
   * @throws \Exception
   */
  static function createFromFile($file) {
    if (!file_exists($file)) {
      throw new \Exception("File '$file' does not exist.");
    }
    $json = file_get_contents($file);
    $data = json_decode($json, TRUE);
    if (NULL === $data && JSON_ERROR_NONE !== json_last_error()) {
      throw new \Exception("Invalid json in '$file'.");
    }
    return self::createFromData($data, dirname($file) . '/');
  }

  /**
   * @param array $data
   * @param string $path_prefix
   *
   * @return self
   *
   * @throws \Exception
   */
  static function createFromData($data, $path_prefix) {
    return empty($data['target-dir'])
      ? new self($data, $path_prefix)
      : new ComposerJsonTargetDir($data, $path_prefix);
  }

  /**
   * @param array $data
   * @param string $path_prefix
   */
  protected function __construct(array $data, $path_prefix) {
    $this->data = $data;
    $this->pathPrefix = $path_prefix;
  }

  /**
   * @param ClassFinderAdapter $adapter
   */
  function writeToAdapter(ClassFinderAdapter $adapter) {

    $data = $this->data;

    if (!empty($data['include-path'])) {
      $this->addIncludePaths((array)$data['include-path']);
    }

    if (!empty($data['autoload']['psr-0'])) {
      $map = $this->transformMultiple($data['autoload']['psr-0']);
      $adapter->addMultiplePsr0($map);
    }

    if (!empty($data['autoload']['psr-4'])) {
      $map = $this->transformMultiple($data['autoload']['psr-4']);
      $adapter->addMultiplePsr4($map);
    }

    if (!empty($data['autoload']['classmap'])) {
      $this->addClassmapSources($adapter, (array)$data['autoload']['classmap']);
    }

    if (!empty($data['autoload']['files'])) {
      foreach ($data['autoload']['files'] as $file) {
        require $this->pathPrefix . $file;
      }
    }
  }

  /**
   * @param array $multiple
   *
   * @return array[]
   */
  protected function transformMultiple(array $multiple) {
    foreach ($multiple as &$paths) {
      $paths = (array)$paths;
      foreach ($paths as &$path) {
        if ('' === $path || '/' !== $path{0}) {
          $path = $this->pathPrefix . $path;
        }
      }
    }
    return $multiple;
  }

  /**
   * @param string[] $include_paths
   */
  protected function addIncludePaths(array $include_paths) {
    foreach ($include_paths as &$path) {
      $path = $this->pathPrefix . $path;
    }
    array_push($include_paths, get_include_path());
    set_include_path(join(PATH_SEPARATOR, $include_paths));
  }

  /**
   * @param ClassFinderAdapter $adapter
   * @param string[] $sources_raw
   *   Array of files and folders to scan for class implementations.
   */
  protected function addClassmapSources($adapter, array $sources_raw) {
    foreach ($sources_raw as &$path) {
      $path = $this->pathPrefix . $path;
    }
    $adapter->addClassmapSources($sources_raw);
  }
}
