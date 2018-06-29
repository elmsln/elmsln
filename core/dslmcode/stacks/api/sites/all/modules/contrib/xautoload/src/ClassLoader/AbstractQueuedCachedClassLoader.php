<?php

namespace Drupal\xautoload\ClassLoader;

use Drupal\xautoload\CacheManager\CacheManager;
use Drupal\xautoload\CacheManager\CacheManagerObserverInterface;
use Drupal\xautoload\ClassFinder\ClassFinderInterface;
use Drupal\xautoload\ClassFinder\InjectedApi\LoadClassGetFileInjectedApi;

/**
 * Bass class for cached class loader decorators where cache entries cannot be
 * written one by one, but have to be written all at once instead.
 *
 * Saving the cache immediately on every cache miss would be too expensive. On
 * the other hand, saving only at the end of the request might fail if the
 * request does not end properly, or if some classes are still loaded after the
 * end-of-process callback.
 *
 * The solution is an exponentially growing queue. Cache writing happens not on
 * every cache miss, but only on the 1st, 3rd, 7th, 15th, 31st, 63rd etc.
 *
 * This will result in a "hot" cache after a limited number of requests, and
 * with a limited number of cache write operations.
 */
abstract class AbstractQueuedCachedClassLoader
  extends AbstractClassLoaderDecorator
  implements CacheManagerObserverInterface {

  /**
   * @var int
   */
  private $nMax = 1;

  /**
   * @var int
   */
  private $n = 0;

  /**
   * @var string[]
   */
  private $toBeDeleted = array();

  /**
   * @var string[]
   */
  private $toBeAdded = array();

  /**
   * @var string[]
   */
  private $classFiles;

  /**
   * This method has side effects, so it is not the constructor.
   *
   * @param ClassFinderInterface $finder
   * @param CacheManager $cacheManager
   *
   * @return self
   *
   * @throws \Exception
   */
  static function create($finder, $cacheManager) {
    /** @var self $loader */
    $loader = new static($finder);
    $cacheManager->observeCachePrefix($loader);

    return $loader;
  }

  /**
   * {@inheritdoc}
   */
  function loadClass($class) {

    // Look if the cache has anything for this class.
    if (isset($this->classFiles[$class])) {
      $file = $this->classFiles[$class];
      // The is_file() check may cost around 0.0045 ms per class file, but this
      // depends on your system of course.
      if (is_file($file)) {
        require $file;

        return;
      }
      $this->toBeDeleted[$class] = $file;
      unset($this->classFiles[$class]);
      ++$this->n;
    }

    // Resolve cache miss.
    $api = new LoadClassGetFileInjectedApi($class);
    if ($this->finder->apiFindFile($api, $class)) {
      // Queue the result for the cache.
      $this->toBeAdded[$class]
        = $this->classFiles[$class]
        = $api->getFile();
      ++$this->n;
    }

    // Save the cache if enough has been queued up.
    if ($this->n >= $this->nMax) {
      $this->classFiles = $this->updateClassFiles($this->toBeAdded, $this->toBeDeleted);
      $this->toBeDeleted = array();
      $this->toBeAdded = array();
      $this->nMax *= 2;
      $this->n = 0;
    }
  }

  /**
   * Set the new cache prefix after a flush cache.
   *
   * @param string $prefix
   *   A prefix for the storage key in APC.
   */
  function setCachePrefix($prefix) {
    $this->classFiles = $this->loadClassFiles($prefix);
  }

  /**
   * @param string $prefix
   *
   * @return string[]
   */
  abstract protected function loadClassFiles($prefix);

  /**
   * @param string[] $toBeAdded
   * @param string[] $toBeRemoved
   *
   * @return string[]
   */
  abstract protected function updateClassFiles($toBeAdded, $toBeRemoved);

}
