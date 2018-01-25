<?php

namespace Drupal\xautoload\CacheManager;

interface CacheManagerObserverInterface {

  /**
   * Set the APC prefix after a flush cache.
   *
   * @param string $prefix
   *   A prefix for the storage key in APC.
   */
  function setCachePrefix($prefix);
}