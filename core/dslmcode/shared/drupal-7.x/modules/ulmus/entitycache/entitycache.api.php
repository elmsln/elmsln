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
