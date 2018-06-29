<?php

namespace Drupal\xautoload\ClassFinder;

use Drupal\xautoload\ClassLoader\AbstractClassLoader;
use Drupal\xautoload\CacheMissObserver\CacheMissObserverInterface;

/**
 * A placeholder class finder. Used to postpone expensive operations until they
 * are actually needed.
 */
class ProxyClassFinder extends AbstractClassLoader implements ClassFinderInterface {

  /**
   * @var ExtendedClassFinderInterface
   *   The actual class finder.
   */
  protected $finder;

  /**
   * @var CacheMissObserverInterface[]
   *   Operations to run when the actual finder is initialized.
   */
  protected $cacheMissObservers = array();

  /**
   * @var bool
   */
  protected $initialized = FALSE;

  /**
   * @param ExtendedClassFinderInterface $finder
   *
   * @internal param \Drupal\xautoload\Adapter\DrupalExtensionAdapter $helper
   */
  function __construct($finder) {
    $this->finder = $finder;
  }

  /**
   * {@inheritdoc}
   */
  function loadClass($class) {
    $this->initFinder();
    $this->finder->loadClass($class);
  }

  /**
   * {@inheritdoc}
   */
  function apiFindFile($api, $class) {
    $this->initFinder();

    return $this->finder->apiFindFile($api, $class);
  }

  /**
   * @param CacheMissObserverInterface $observer
   */
  function observeFirstCacheMiss($observer) {
    if (!$this->initialized) {
      $this->cacheMissObservers[] = $observer;
    }
    else {
      $observer->cacheMiss($this->finder);
    }
  }

  /**
   * @return ClassFinderInterface
   */
  function getFinder() {
    $this->initFinder();

    return $this->finder;
  }

  /**
   * Initialize the finder and notify cache miss observers.
   */
  protected function initFinder() {
    if (!$this->initialized) {
      $this->initialized = TRUE;
      foreach ($this->cacheMissObservers as $operation) {
        $operation->cacheMiss($this->finder);
      }
    }
  }

}
