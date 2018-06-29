<?php

namespace Drupal\xautoload\ClassLoader;

use Drupal\xautoload\CacheManager\CacheManagerObserverInterface;
use Drupal\xautoload\ClassFinder\ClassFinderInterface;
use Drupal\xautoload\CacheManager\CacheManager;

abstract class AbstractCachedClassLoader
  extends AbstractClassLoaderDecorator
  implements CacheManagerObserverInterface {

  /**
   * @var string
   */
  protected $prefix;

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
    if (!$loader->checkRequirements()) {
      $class = get_class($loader);
      throw new CacheNotSupportedException("Unable to use $class, because the respetive PHP extension is not enabled.");
    }
    $cacheManager->observeCachePrefix($loader);

    return $loader;
  }

  /**
   * @return bool
   */
  protected abstract function checkRequirements();

  /**
   * {@inheritdoc}
   */
  function setCachePrefix($prefix) {
    $this->prefix = $prefix;
  }
}
