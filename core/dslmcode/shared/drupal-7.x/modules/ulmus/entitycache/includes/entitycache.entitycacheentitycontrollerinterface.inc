<?php

/**
 * Common interface for entity controllers supporting entity cache.
 */
interface EntityCacheEntityControllerInterface extends DrupalEntityControllerInterface {

  /**
   * Resets the internal, static entity cache.
   *
   * @param string[] $ids
   *   (optional) If specified, the cache is reset for the entities with the
   *   given ids only.
   */
  public function resetStaticCache(array $ids = NULL);

}
