<?php

/**
 * @file
 * User entity controller with persistent cache.
 */

/**
 * User entity controller with persistent cache.
 */
class EntityCacheUserController extends UserController implements EntityCacheEntityControllerInterface {

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
