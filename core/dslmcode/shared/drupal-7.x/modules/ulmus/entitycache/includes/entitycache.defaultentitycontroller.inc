<?php

/**
 * @file
 * Default entity controller with persistent cache.
 */

/**
 * Default entity controller with persistent cache.
 */
class EntityCacheDefaultEntityController extends DrupalDefaultEntityController implements EntityCacheEntityControllerInterface {

  /**
   * {@inheritdoc}
   */
  public function resetCache(array $ids = NULL) {
    EntityCacheControllerHelper::resetEntityCache($this, $ids);
    $this->resetStaticCache($ids);
  }

  /**
   * {@inheritdoc}
   */
  public function resetStaticCache(array $ids = NULL) {
    parent::resetCache($ids);
  }

  /**
   * {@inheritdoc}
   */
  public function load($ids = array(), $conditions = array()) {
    return EntityCacheControllerHelper::entityCacheLoad($this, $ids, $conditions);
  }

}
