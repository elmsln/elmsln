<?php

/**
 * @file
 * EntityCacheControllerHelper cache helper.
 */

/**
 * Entity cache helper.
 *
 * Note: while this class is not a real entity controller it needs to extend
 * DrupalDefaultEntityController to get access to protected properties.
 */
class EntityCacheControllerHelper extends DrupalDefaultEntityController {

  public static function resetEntityCache($controller, array $ids = NULL) {
    // Reset the persistent cache.
    if (!empty($ids)) {
      cache_clear_all($ids, 'cache_entity_' . $controller->entityType);
    }
    else {
      // Force all cached entries to be deleted.
      cache_clear_all('*', 'cache_entity_' . $controller->entityType, TRUE);
    }

    // Give modules the chance to act on any entity.
    foreach (module_implements('entitycache_reset') as $module) {
      $function = $module . '_entitycache_reset';
      $function($ids, $controller->entityType);
    }
    // Give modules the chance to act on a specific entity type.
    foreach (module_implements('entitycache_' . $controller->entityType . '_reset') as $module) {
      $function = $module . '_entitycache_' . $controller->entityType . '_reset';
      $function($ids);
    }
  }

  /**
   * Loads entities by IDs/conditions, which are potentially cached.
   *
   * @param \DrupalDefaultEntityController $controller
   *   The entity (storage) controller.
   *
   * @param array $ids
   *   (optional) entity IDs to load.
   * @param array $conditions
   *   (options) An array of conditions to be used when loading. Note: It is
   *   possible to pass conditions with and without IDs.
   *
   * @return array
   *   An array of loaded entities keyed by ID.
   */
  public static function entityCacheLoad($controller, $ids = array(), $conditions = array()) {
    $entities = array();
    $cached_entities = array();
    $queried_entities = array();

    // Revisions are not statically cached, and require a different query to
    // other conditions, so separate the revision id into its own variable.
    if ($controller->revisionKey && isset($conditions[$controller->revisionKey])) {
      $revision_id = $conditions[$controller->revisionKey];
      unset($conditions[$controller->revisionKey]);
    }
    else {
      $revision_id = FALSE;
    }

    // Create a new variable which is either a prepared version of the $ids
    // array for later comparison with the entity cache, or FALSE if no $ids
    // were passed. The $ids array is reduced as items are loaded from cache,
    // and we need to know if it's empty for this reason to avoid querying the
    // database when all requested entities are loaded from cache.
    $passed_ids = !empty($ids) ? array_flip($ids) : FALSE;

    // Use an entity field query to transform the list of conditions into
    // the set of entity IDs which the conditions admit, then re-enter this
    // method with that set as the $ids constraint.
    if ($conditions) {
      $query = new EntityFieldQuery();
      $query->entityCondition('entity_type', $controller->entityType);
      foreach ($conditions as $property_name => $condition) {
        // Note $condition might be multiple values, which are treated as OR
        // by default.
        $query->propertyCondition($property_name, $condition);
      }

      // Limit the result set also by the passed in IDs.
      if ($passed_ids) {
        $query->propertyCondition($controller->idKey, array_keys($passed_ids));
      }

      $result = $query->execute();
      if (isset($result[$controller->entityType])) {
        $entity_ids = array_keys($result[$controller->entityType]);
        if ($revision_id) {
          return static::entityCacheLoad($controller, $entity_ids, array($controller->revisionKey => $revision_id));
        } else {
          return static::entityCacheLoad($controller, $entity_ids);
        }
      }
      else {
        // No results found.
        return array();
      }
    }

    // Try to load entities from the static cache, if the entity type supports
    // static caching.
    if ($controller->cache && !$revision_id) {
      $entities += $controller->cacheGet($ids, $conditions);
      // If any entities were loaded, remove them from the ids still to load.
      if ($passed_ids) {
        $ids = array_keys(array_diff_key($passed_ids, $entities));
      }
    }

    if (!empty($controller->entityInfo['entity cache']) && !$revision_id && $ids && !$conditions) {
      $entities += $cached_entities = self::entityCacheGet($controller, $ids, $conditions);
      // If any entities were loaded, remove them from the ids still to load.
      $ids = array_diff($ids, array_keys($cached_entities));

      if ($controller->cache) {
        // Add entities to the cache if we are not loading a revision.
        if (!empty($cached_entities) && !$revision_id) {
          $controller->cacheSet($cached_entities);
        }
      }
    }

    // Ensure integer entity IDs are valid.
    if (!empty($ids)) {
      static::entityCacheCleanIds($controller, $ids);
    }

    // Load any remaining entities from the database. This is the case if $ids
    // is set to FALSE (so we load all entities), if there are any ids left to
    // load, if loading a revision, or if $conditions was passed without $ids.
    if ($ids === FALSE || $ids || $revision_id || ($conditions && !$passed_ids)) {
      // Build the query.
      $query = $controller->buildQuery($ids, $conditions, $revision_id);
      $queried_entities = $query
        ->execute()
        ->fetchAllAssoc($controller->idKey);
    }

    // Pass all entities loaded from the database through $controller->attachLoad(),
    // which attaches fields (if supported by the entity type) and calls the
    // entity type specific load callback, for example hook_node_load().
    if (!empty($queried_entities)) {
      $controller->attachLoad($queried_entities, $revision_id);
      $entities += $queried_entities;
    }

    if (!empty($controller->entityInfo['entity cache'])) {
      // Add entities to the entity cache if we are not loading a revision.
      if (!empty($queried_entities) && !$revision_id) {
        // Only cache the entities which were loaded by ID. Entities that were
        // loaded based on conditions will never be found via cacheGet() and we
        // would keep on caching them.
        if ($passed_ids) {
          $queried_entities_by_id = array_intersect_key($queried_entities, $passed_ids);
          if (!empty($queried_entities_by_id)) {
            self::entityCacheSet($controller, $queried_entities_by_id);
          }
        }
      }
    }

    if ($controller->cache) {
      // Add entities to the cache if we are not loading a revision.
      if (!empty($queried_entities) && !$revision_id) {
        $controller->cacheSet($queried_entities);
      }
    }

    // Ensure that the returned array is ordered the same as the original
    // $ids array if this was passed in and remove any invalid ids.
    if ($passed_ids) {
      // Remove any invalid ids from the array.
      $passed_ids = array_intersect_key($passed_ids, $entities);
      foreach ($entities as $entity) {
        $passed_ids[$entity->{$controller->idKey}] = $entity;
      }
      $entities = $passed_ids;
    }

    return $entities;
  }

  /**
   * Ensures integer entity IDs are valid.
   *
   * The identifier sanitization provided by this method has been introduced
   * as Drupal used to rely on the database to facilitate this, which worked
   * correctly with MySQL but led to errors with other DBMS such as PostgreSQL.
   *
   * @param array $ids
   *   The entity IDs to verify.
   *
   * @return array
   *   The sanitized list of entity IDs.
   */
  protected static function entityCacheCleanIds($controller, &$ids) {
    $entity_info = entity_get_info($controller->entityType);
    if (isset($entity_info['base table field types'])) {
      $id_type = $entity_info['base table field types'][$controller->idKey];
      if ($id_type == 'serial' || $id_type == 'int') {
        $ids = array_filter($ids, array(__CLASS__, 'entityCacheFilterId'));
        $ids = array_map('intval', $ids);
      }
    }
  }

  /**
   * Callback for array_filter that removes non-integer IDs.
   */
  public static function entityCacheFilterId($id) {
    return is_numeric($id) && $id == (int) $id;
  }

  public static function entityCacheGet($controller, $ids, $conditions = array()) {
    $cached_entities = array();
    if ($ids && !$conditions) {
      $cached = cache_get_multiple($ids, 'cache_entity_' . $controller->entityType);
      if ($cached) {
        foreach ($cached as $item) {
          $cached_entities[$item->cid] = $item->data;
        }
        self::entityCacheAttachLoad($controller, $cached_entities);
      }
    }
    return $cached_entities;
  }

  public static function entityCacheSet($controller, $entities) {
    foreach ($entities as $id => $item) {
      cache_set($id, $item, 'cache_entity_' . $controller->entityType);
    }
  }

  /**
   * Allow modules to implement uncached entity hooks.
   *
   * Perform two additional hook invocations for modules needing to add
   * uncacheable data to objects while serving the request.
   *
   * @see entitycache_entitycache_node_load()
   */
  public static function entityCacheAttachLoad($controller, $entities) {
    // Give modules the chance to act on any entity.
    foreach (module_implements('entitycache_load') as $module) {
      $function = $module . '_entitycache_load';
      $function($entities, $controller->entityType);
    }
    // Give modules the chance to act on a specific entity type.
    foreach (module_implements('entitycache_' . $controller->entityType . '_load') as $module) {
      $function = $module . '_entitycache_' . $controller->entityType . '_load';
      $function($entities);
    }
  }
}
