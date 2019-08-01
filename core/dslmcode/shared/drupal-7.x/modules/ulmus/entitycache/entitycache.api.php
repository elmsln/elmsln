<?php

/**
 * @file
 * Hooks provided by the Entity cache module.
 */

/**
 * Act on entities being loaded from the entitycache.
 *
 * @param $entities
 *   Array with entity objects.
 * @param $entity_type
 */
function hook_entitycache_load($entities, $entity_type) {

}

/**
 * Act on entites of a specific entity type being loaded from the entitycache.
 *
 * @param $entities
 *   Array with entity objects.
 */
function hook_entitycache_ENTITY_TYPE_load($entities) {

}

/**
 * Act on entities being removed from the entitycache.
 *
 * @param array|null $entity_ids
 *   Array with the ids of the entities, or NULL for all entities of this type.
 * @param string $entity_type
 */
function hook_entitycache_reset($entity_ids = NULL, $entity_type) {

}

/**
 * Act on entites of a specific entity type being removed from the entitycache.
 *
 * @param array|null $entity_ids
 *   Array with the ids of the entities, or NULL for all entities of this type.
 */
function hook_entitycache_ENTITY_TYPE_reset($entity_ids = NULL) {

}

/**
 * Act on entity ids before loading from cache.
 *
 * @param array $ids
 *   Array with entity ids.
 * @param array $conditions
 *   Array with conditions how to load the entities.
 * @param string $entity_type
 */
function hook_entitycache_pre_cache_get_alter(&$ids, &$conditions, $entity_type) {
  if ($entity_type == 'foo' && some_condition()) {
    // Do not load any entities for 'foo' from cache while some_condition() is
    // active.
    $ids = array();
  }
}

/**
 * Act on entities before storing them into cache.
 *
 * @param array $entities
 *   Array with entity objects.
 * @param string $entity_type
 */
function hook_entitycache_pre_cache_set_alter(&$entities, $entity_type) {
  if ($entity_type == 'foo' && some_condition()) {
    // Do not store any entities for 'foo' into cache while some_condition() is
    // active.
    $entities = array();
  }

  if ($entity_type == 'bar') {
    foreach ($entities as $entity) {
      if (isset($entity->old_value)) {
        // Make old_value available when loading from cache.
        $entity->old_value = $entity->value;
        $entity->value = some_function($entity->value);
      }
    }
  }
}

/**
 * Act on entities after storing them into cache.
 *
 * @param array $entities
 *   Array with entity objects.
 * @param string $entity_type
 */
function hook_entitycache_post_cache_set_alter(&$entities, $entity_type) {
  // Restore changes from hook_entitycache_pre_cache_set_alter().
  foreach ($entities as $entity) {
    if (isset($entity->old_value)) {
      $entity->value = $entity->old_value;
      unset($entity->old_value);
    }
  }
}


/**
 * Act on the ids to clear before resetting the cache.
 *
 * Set $ids to FALSE to disable the cache clearing.
 *
 * @param array|NULL $ids
 *   Array with entity ids or NULL for clearing the whole cache.
 * @param $entity_type
 */
function hook_entitycache_pre_reset_cache_alter(&$ids, $entity_type) {
  if (some_other_condition()) {
    // Disable cache clearing while some_other_condition() is active.
    $ids = FALSE;
  }
}
