<?php

/**
 * @file
 * Taxonomy entity controllers with persistent cache.
 */

/**
 * Taxonomy term entity controller class with persistent cache.
 */
class EntityCacheTaxonomyTermController extends TaxonomyTermController {

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

/**
 * Taxonomy vocabulary entity controller class with persistent cache.
 */
class EntityCacheTaxonomyVocabularyController extends TaxonomyVocabularyController {

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
