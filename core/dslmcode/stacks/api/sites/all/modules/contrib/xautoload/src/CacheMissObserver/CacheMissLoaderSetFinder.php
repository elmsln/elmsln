<?php

namespace Drupal\xautoload\CacheMissObserver;

use Drupal\xautoload\ClassLoader\AbstractClassLoaderDecorator;

/**
 * Replaces the ProxyClassFinder in the ClassLoader with the real ClassLoader.
 *
 * xautoload has a number of cached class loaders, working with APC cache or
 * other key-value stores.
 *
 * The cached class loaders use the decorator pattern, and decorate a
 * ClassFinder object, that will only be consulted on a cache miss.
 *
 * xautoload will first give the ClassLoader a ProxyClassFinder that wraps the
 * real class loader. On the first cache miss, this ProxyClassFinder will
 * notify all subscribed CacheMissObserverInterface object.
 *
 * The job of this particular observer is to replace the ProxyClassFinder, once
 * it has done its job. Instead, the ClassLoader will get a reference ot the
 * real ClassLoader, saving the overhead of going through ProxyClassFinder each
 * time.
 *
 * @see ProxyClassFinder
 */
class CacheMissLoaderSetFinder implements CacheMissObserverInterface {

  /**
   * @var AbstractClassLoaderDecorator
   */
  protected $loader;

  /**
   * @param AbstractClassLoaderDecorator $loader
   */
  function __construct($loader) {
    $this->loader = $loader;
  }

  /**
   * {@inheritdoc}
   */
  function cacheMiss($finder) {
    $this->loader->setFinder($finder);
  }

}
