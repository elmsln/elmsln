<?php

namespace Drupal\xautoload\ClassLoader;

class ApcuQueuedCachedClassLoader extends AbstractQueuedCachedClassLoader {

  /**
   * @var string
   */
  private $prefix;

  /**
   * @param string $prefix
   *
   * @return string[]
   */
  protected function loadClassFiles($prefix) {
    $this->prefix = $prefix;
    $cached = \apcu_fetch($this->prefix);

    return !empty($cached)
      ? $cached
      : array();
  }

  /**
   * @param string[] $toBeAdded
   * @param string[] $toBeRemoved
   *
   * @return string[]
   */
  protected function updateClassFiles($toBeAdded, $toBeRemoved) {

    $class_files = $toBeAdded;
    // Other requests may have already written to the cache, so we get an up to
    // date version.
    $cached = \apcu_fetch($this->prefix);
    if (!empty($cached)) {
      $class_files += $cached;
      foreach ($toBeRemoved as $class => $file) {
        if (isset($class_files[$class]) && $class_files[$class] === $file) {
          unset($class_files[$class]);
        }
      }
    }

    \apcu_store($this->prefix, $class_files);

    return $class_files;
  }

}
