<?php

namespace Drupal\xautoload\CacheMissObserver;

use Drupal\xautoload\ClassFinder\ExtendedClassFinderInterface;

/**
 * An operation that can be queued up to be performed on the class finder once
 * it is initialized.
 *
 * In an average request, with the APC cache or similar enabled, class-to-file
 * mappings will usually be loaded from the cache. The "real" class finder will
 * only be initialized if one of the classes is not in the cache.
 *
 * @see ProxyClassFinder
 */
interface CacheMissObserverInterface {

  /**
   * Executes the operation.
   *
   * This method will only be called if and when the "real" class finder is
   * initialized.
   *
   * @param ExtendedClassFinderInterface $finder
   *   The class finder.
   */
  function cacheMiss($finder);
}
