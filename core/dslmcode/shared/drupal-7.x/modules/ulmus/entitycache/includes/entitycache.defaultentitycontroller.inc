<?php

/**
 * @file
 * Default entity controller with persistent cache.
 */

/**
 * Default entity controller with persistent cache.
 */
class EntityCacheDefaultEntityController extends DrupalDefaultEntityController {

  /**
   * {@inheritdoc}
   */
  public function resetCache(array $ids = NULL) {
    EntityCacheControllerHelper::resetEntityCache($this, $ids);
    parent::resetCache($ids);
  }

  /**
   * {@inheritdoc}
   */
  public function load($ids = array(), $conditions = array()) {
    return EntityCacheControllerHelper::entityCacheLoad($this, $ids, $conditions);
  }

}
