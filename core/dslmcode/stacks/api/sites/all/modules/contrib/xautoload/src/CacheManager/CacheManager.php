<?php

namespace Drupal\xautoload\CacheManager;

use Drupal\xautoload\DrupalSystem\DrupalSystemInterface;
use Drupal\xautoload\Util;

class CacheManager {

  /**
   * @var string
   */
  protected $prefix;

  /**
   * @var \Drupal\xautoload\DrupalSystem\DrupalSystemInterface
   */
  protected $system;

  /**
   * @var CacheManagerObserverInterface[]
   */
  protected $observers = array();

  /**
   * @param string $prefix
   * @param \Drupal\xautoload\DrupalSystem\DrupalSystemInterface $system
   */
  protected function __construct($prefix, DrupalSystemInterface $system) {
    $this->prefix = $prefix;
    $this->system = $system;
  }

  /**
   * This method has side effects, so it is not the constructor.
   *
   * @param \Drupal\xautoload\DrupalSystem\DrupalSystemInterface $system
   *
   * @return CacheManager
   */
  static function create(DrupalSystemInterface $system) {
    $prefix = $system->variableGet(XAUTOLOAD_VARNAME_CACHE_PREFIX, NULL);
    $manager = new self($prefix, $system);
    if (empty($prefix)) {
      $manager->renewCachePrefix();
    }
    return $manager;
  }

  /**
   * @param CacheManagerObserverInterface $observer
   */
  function observeCachePrefix($observer) {
    $observer->setCachePrefix($this->prefix);
    $this->observers[] = $observer;
  }

  /**
   * Renew the cache prefix, save it, and notify all observers.
   */
  function renewCachePrefix() {
    $this->prefix = Util::randomString();
    $this->system->variableSet(XAUTOLOAD_VARNAME_CACHE_PREFIX, $this->prefix);
    foreach ($this->observers as $observer) {
      $observer->setCachePrefix($this->prefix);
    }
  }
}
