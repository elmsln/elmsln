<?php

/**
 * @file
 * Entity related functions for UUID module.
 */

/**
 * Entity UUID exception class.
 */
class UuidEntityException extends Exception {}

/**
 * Returns entity info for all supported core entities.
 *
 * @see uuid_entity_info()
 * @see uuid_schema_alter()
 * @see uuid_install()
 * @see uuid_uninstall()
 */
function uuid_get_core_entity_info() {
  $info = array();
  $info['user'] = array(
    'base table' => 'users',
    'entity keys' => array(
      'uuid' => 'uuid',
    ),
  );
  $info['node'] = array(
    'base table' => 'node',
    'revision table' => 'node_revision',
    'entity keys' => array(
      'uuid' => 'uuid',
      'revision uuid' => 'vuuid',
    ),
  );
  if (module_exists('comment')) {
    $info['comment'] = array(
      'base table' => 'comment',
      'entity keys' => array(
        'uuid' => 'uuid',
      ),
    );
  }
  if (module_exists('file')) {
    $info['file'] = array(
      'base table' => 'file_managed',
      'entity keys' => array(
        'uuid' => 'uuid',
      ),
    );
  }
  if (module_exists('taxonomy')) {
    $info['taxonomy_term'] = array(
      'base table' => 'taxonomy_term_data',
      'entity keys' => array(
        'uuid' => 'uuid',
      ),
    );
  }
  if (module_exists('field_collection')) {
    $info['field_collection_item'] = array(
      'base table' => 'field_collection_item',
      'entity keys' => array(
        'uuid' => 'uuid',
      ),
    );
  }
  return $info;
}

/**
 * @defgroup uuid_entity_hooks UUID implementation of Entity API
 * @{
 */

/**
 * Implements hook_entity_info_alter().
 *
 * @see uuid_core_entity_info()
 */
function uuid_entity_info_alter(&$info) {
  foreach (uuid_get_core_entity_info() as $entity_type => $core_info) {
    $info[$entity_type]['uuid'] = TRUE;
    $info[$entity_type]['entity keys']['uuid'] = $core_info['entity keys']['uuid'];
    if (!empty($core_info['entity keys']['revision uuid'])) {
      $info[$entity_type]['entity keys']['revision uuid'] = $core_info['entity keys']['revision uuid'];
    }
  }
}

/**
 * Implements hook_entity_property_info_alter().
 *
 * This adds the UUID as an entity property for all UUID-enabled entities
 * which automatically gives us token and Rules integration.
 */
function uuid_entity_property_info_alter(&$info) {
  foreach (entity_get_info() as $entity_type => $entity_info) {
    if (isset($entity_info['uuid']) && $entity_info['uuid'] == TRUE
      && !empty($entity_info['entity keys']['uuid'])
      && empty($info[$entity_type]['properties'][$entity_info['entity keys']['uuid']])) {
      $info[$entity_type]['properties'][$entity_info['entity keys']['uuid']] = array(
        'label' => t('UUID'),
        'type' => 'text',
        'description' => t('The universally unique ID.'),
        'schema field' => $entity_info['entity keys']['uuid'],
      );
      if (!empty($entity_info['entity keys']['revision uuid'])
        && empty($info[$entity_type]['properties'][$entity_info['entity keys']['revision uuid']])) {
        $info[$entity_type]['properties'][$entity_info['entity keys']['revision uuid']] = array(
          'label' => t('Revision UUID'),
          'type' => 'text',
          'description' => t("The revision's universally unique ID."),
          'schema field' => $entity_info['entity keys']['revision uuid'],
        );
      }
    }
  }
}

/**
 * Implements hook_entity_presave().
 *
 * This is where all UUID-enabled entities get their UUIDs.
 */
function uuid_entity_presave($entity, $entity_type) {
  $info = entity_get_info($entity_type);
  if (isset($info['uuid']) && $info['uuid'] == TRUE && !empty($info['entity keys']['uuid'])) {
    $uuid_key = $info['entity keys']['uuid'];
    if (empty($entity->{$uuid_key})) {
      $entity->{$uuid_key} = uuid_generate();
    }
    if (!empty($info['entity keys']['revision uuid'])) {
      $vuuid_key = $info['entity keys']['revision uuid'];
      // If this entity comes from a remote environment and have a revision UUID
      // that exists locally we should not create a new revision. Because
      // otherwise revisions won't be tracked universally.
      // TODO: Move code dependent on the uuid_services module into it's own
      // implementation of hook_entity_presave().
      if (!empty($entity->uuid_services) && isset($entity->{$vuuid_key})) {
        $vuuid_exists = (bool) entity_get_id_by_uuid($entity_type, array($entity->{$vuuid_key}), TRUE);
        if ($vuuid_exists) {
          $entity->revision = FALSE;
        }
      }

      if ((isset($entity->revision) && $entity->revision == TRUE && empty($entity->uuid_services)) || empty($entity->{$vuuid_key})) {
        $entity->{$vuuid_key} = uuid_generate();
      }
    }
  }
}

/**
 * @} End of "UUID implementation of Entity API"
 */

/**
 * @defgroup uuid_entity_support UUID support for Entity API
 * @{
 * Functions that extends the Entity API with UUID support.
 */

/**
 * Load entities by their UUID, that only should containing UUID references.
 *
 * Optionally load revisions by their VUUID by passing it into $conditions.
 * Ex. $conditions['vuuid'][$vuuid]
 *
 * This function is mostly useful if you want to load an entity from the local
 * database that only should contain UUID references.
 *
 * @see entity_load()
 */
function entity_uuid_load($entity_type, $uuids = array(), $conditions = array(), $reset = FALSE) {
  // Allow Revision UUID to be passed in $conditions and translate.
  $entity_info[$entity_type] = entity_get_info($entity_type);
  $revision_key = $entity_info[$entity_type]['entity keys']['revision'];
  if (isset($entity_info[$entity_type]['entity keys']['revision uuid'])) {
    $revision_uuid_key = $entity_info[$entity_type]['entity keys']['revision uuid'];
  }
  if (isset($revision_uuid_key) && isset($conditions[$revision_uuid_key])) {
    $revision_id = entity_get_id_by_uuid($entity_type, array($conditions[$revision_uuid_key]), TRUE);
    $conditions[$revision_key] = $revision_id[$conditions[$revision_uuid_key]];
    unset($conditions[$revision_uuid_key]);
  }
  $ids = entity_get_id_by_uuid($entity_type, $uuids);
  $results = entity_load($entity_type, $ids, $conditions, $reset);
  $entities = array();

  // We need to do this little magic here, because objects are passed by
  // reference. And because hook_entity_uuid_load() has the intention changing
  // primary properties and fields from local IDs to UUIDs it will also change
  // DrupalDefaultEntityController::entityCache by reference which is a static
  // cache of entities. And that is not something we want.
  foreach ($results as $key => $entity) {
    // This will avoid passing our loaded entities by reference.
    $entities[$key] = clone $entity;
  }

  entity_make_entity_universal($entity_type, $entities);

  return $entities;
}

/**
 * Helper function to make an entity universal (i.e. only global references).
 */
function entity_make_entity_universal($entity_type, $entities) {
  // Let other modules transform local ID references to UUID references.
  if (!empty($entities)) {
    $hook = 'entity_uuid_load';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        $function($entities, $entity_type);
      }
    }
  }
}

/**
 * Permanently saves an entity by its UUID.
 *
 * This function depends on the Entity API module to provide the
 * 'entity_save()' function.
 *
 * This function is mostly useful if you want to save an entity into the local
 * database that only contains UUID references.
 *
 * @see entity_save()
 */
function entity_uuid_save($entity_type, $entity) {
  // This function, and this function only, depends on the entity module.
  if (!module_exists('entity')) {
    throw new UuidEntityException(t('Calling %function requires the Entity API module (!link).', array('%function' => __FUNCTION__, '!link' => 'http://drupal.org/project/entity')));
  }

  $info = entity_get_info($entity_type);
  $uuid_key = $info['entity keys']['uuid'];
  if (empty($entity->{$uuid_key}) || !uuid_is_valid($entity->{$uuid_key})) {
    watchdog('Entity UUID', 'Attempted to save an entity with an invalid UUID', array(), WATCHDOG_ERROR);
    return FALSE;
  }

  // Falling back on the variable node_options_[type] is not something an API
  // function should take care of. With normal (non UUID) nodes this is dealt
  // with in the form submit handler, i.e. not in node_save().
  // But since using entity_uuid_save() usually means you're trying to manage
  // entities remotely we do respect this variable here to make it work as the
  // node form, but only if we explicitly haven't set $node->revision already.
  if ($entity_type == 'node' && !isset($entity->revision) && in_array('revision', variable_get('node_options_' . $entity->type, array()))) {
    $entity->revision = 1;
  }

  entity_make_entity_local($entity_type, $entity);

  // Save the entity.
  $result = entity_save($entity_type, $entity);

  $hook = 'entity_uuid_save';
  foreach (module_implements($hook) as $module) {
    $function = $module . '_' . $hook;
    if (function_exists($function)) {
      $function($entity, $entity_type);
    }
  }
  return $result;
}

/**
 * Helper function to make an entity local (i.e. only local references).
 */
function entity_make_entity_local($entity_type, $entity) {
  $info = entity_get_info($entity_type);
  if (isset($info['uuid']) && $info['uuid'] == TRUE && !empty($info['entity keys']['uuid'])) {
    // Get the keys for local ID and UUID.
    $id_key = $info['entity keys']['id'];
    $uuid_key = $info['entity keys']['uuid'];

    // UUID entites must always provide a valid UUID when saving in order to do
    // the correct mapping between local and global IDs.
    if (empty($entity->{$uuid_key}) || !uuid_is_valid($entity->{$uuid_key})) {
      throw new UuidEntityException(t('Trying to save a @type entity with empty or invalid UUID.', array('@type' => $info['label'])));
    }

    // Fetch the local ID by its UUID.
    $ids = entity_get_id_by_uuid($entity_type, array($entity->{$uuid_key}));
    $id = reset($ids);
    // Set the correct local ID.
    if (empty($id)) {
      unset($entity->{$id_key});
      $entity->is_new = TRUE;
    }
    else {
      $entity->{$id_key} = $id;
      $entity->is_new = FALSE;
    }

    if (!empty($info['entity keys']['revision uuid'])) {
      // Get the keys for local revison ID and revision UUID.
      $vid_key = $info['entity keys']['revision'];
      $vuuid_key = $info['entity keys']['revision uuid'];
      $vid = NULL;
      // Fetch the local revision ID by its UUID.
      if (isset($entity->{$vuuid_key})) {
        // It's important to note that the revision UUID might be set here but
        // there might not exist a correspondant local revision ID in which case
        // we should unset the assigned revision ID to not confuse anyone with
        // revision IDs that might come from other environments.
        $vids = entity_get_id_by_uuid($entity_type, array($entity->{$vuuid_key}), TRUE);
        $vid = reset($vids);
      }
      if (empty($vid) && isset($entity->{$vid_key})) {
        unset($entity->{$vid_key});
      }
      elseif (!empty($vid)) {
        $entity->{$vid_key} = $vid;
      }
      // If the revision ID was unset before this (or just missing for some
      // reason) we fetch the current revision ID to build a better
      // representation of the node object we're working with.
      if ($entity_type == 'node' && !isset($entity->vid) && !$entity->is_new) {
        $entity->vid = db_select('node', 'n')
          ->condition('n.nid', $entity->nid)
          ->fields('n', array('vid'))
          ->execute()
          ->fetchField();
      }
    }

    // Let other modules transform UUID references to local ID references.
    $hook = 'entity_uuid_presave';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        $function($entity, $entity_type);
      }
    }
  }
  else {
    throw new UuidEntityException(t("Trying to operate on a @type entity, which doesn\'t support UUIDs.", array('@type' => $info['label'])));
  }
}

/**
 * Permanently delete the given entity by its UUID.
 *
 * This function depends on the Entity API module to provide the
 * 'entity_delete()' function.
 *
 * @see entity_delete()
 */
function entity_uuid_delete($entity_type, $uuid) {
  // This function, and this function only, depends on the entity module.
  if (!module_exists('entity')) {
    throw new UuidEntityException(t('Calling %function requires the Entity API module (!link).', array('%function' => __FUNCTION__, '!link' => 'http://drupal.org/project/entity')));
  }

  $info = entity_get_info($entity_type);
  if (isset($info['uuid']) && $info['uuid'] == TRUE) {
    // Fetch the local ID by its UUID.
    $ids = entity_get_id_by_uuid($entity_type, array($uuid));
    $id = reset($ids);
    $entity = entity_load($entity_type, array($id));

    // Let other modules transform UUID references to local ID references.
    $hook = 'entity_uuid_delete';
    foreach (module_implements($hook) as $module) {
      $function = $module . '_' . $hook;
      if (function_exists($function)) {
        $function($entity, $entity_type);
      }
    }

    if (empty($entity)) {
      return FALSE;
    }
    // Delete the entity.
    return entity_delete($entity_type, $id);
  }
  else {
    throw new UuidEntityException(t("Trying to delete a @type entity, which doesn\'t support UUIDs.", array('@type' => $info['label'])));
  }
}

/**
 * Helper function that retrieves entity IDs by their UUIDs.
 *
 * @todo
 *   Limit the query.
 *
 * @param string $entity_type
 *   The entity type we should be dealing with.
 * @param array $uuids
 *   List of UUIDs for which we should find their entity IDs. If $revision
 *   is TRUE this should be revision UUIDs instead.
 * @param bool $revision
 *   If TRUE the revision IDs is returned instead.
 *
 * @return array
 *   List of entity IDs keyed by their UUIDs. If $revision is TRUE revision
 *   IDs and UUIDs are returned instead.
 */
function entity_get_id_by_uuid($entity_type, $uuids, $revision = FALSE) {
  if (empty($uuids)) {
    return array();
  }
  $cached_ids = entity_uuid_id_cache($entity_type, $uuids, $revision);
  if (count($cached_ids) == count($uuids)) {
    return $cached_ids;
  }
  $uuids = array_diff($uuids, $cached_ids);
  $info = entity_get_info($entity_type);
  // Some contrib entities has no support for UUID, let's skip them.
  if (empty($info['uuid'])) {
    return array();
  }
  // Find out what entity keys to use.
  if (!$revision) {
    $table = $info['base table'];
    $id_key = $info['entity keys']['id'];
    $uuid_key = $info['entity keys']['uuid'];
  }
  elseif (isset($info['revision table'])) {
    $table = $info['revision table'];
    $id_key = $info['entity keys']['revision'];
    $uuid_key = $info['entity keys']['revision uuid'];
  }
  // If we want revision IDs, but the entity doesn't support it. Return empty.
  else {
    return array();
  }

  // Get all UUIDs in one query.
  $result = db_select($table, 't')
    ->fields('t', array($uuid_key, $id_key))
    ->condition($uuid_key, array_values($uuids), 'IN')
    ->execute()
    ->fetchAllKeyed();
  $cache = &drupal_static('entity_uuid_id_cache', array());
  $cache[$entity_type][(int) $revision] += $result;
  return $result + $cached_ids;
}

/**
 * Helper caching function.
 */
function entity_uuid_id_cache($entity_type, $ids, $revision) {
  $cache = &drupal_static(__FUNCTION__, array());
  if (empty($cache[$entity_type][(int) $revision])) {
    $cache[$entity_type][(int) $revision] = array();
  }
  $cached_ids = $cache[$entity_type][(int) $revision];
  return array_intersect_key($cached_ids, array_flip($ids));
}

/**
 * Helper function that retrieves UUIDs by their entity IDs.
 *
 * @todo
 *   Limit the query.
 *
 * @param string $entity_type
 *   The entity type we should be dealing with.
 * @param array $ids
 *   List of entity IDs for which we should find their UUIDs. If $revision
 *   is TRUE this should be revision IDs instead.
 * @param bool $revision
 *   If TRUE the revision UUIDs is returned instead.
 *
 * @return array
 *   List of entity UUIDs keyed by their IDs. If $revision is TRUE revision
 *   IDs and UUIDs are returned instead.
 */
function entity_get_uuid_by_id($entity_type, $ids, $revision = FALSE) {
  if (empty($ids)) {
    return array();
  }
  $cached_ids = array_flip(entity_uuid_id_cache($entity_type, $ids, $revision));
  if (count($cached_ids) == count($ids)) {
    return $cached_ids;
  }
  $ids = array_diff($ids, $cached_ids);

  $info = entity_get_info($entity_type);
  // Some contrib entities has no support for UUID, let's skip them.
  if (empty($info['uuid'])) {
    return array();
  }
  // Find out what entity keys to use.
  if (!$revision) {
    $table = $info['base table'];
    $id_key = $info['entity keys']['id'];
    $uuid_key = $info['entity keys']['uuid'];
  }
  elseif (isset($info['revision table'])) {
    $table = $info['revision table'];
    $id_key = $info['entity keys']['revision'];
    $uuid_key = $info['entity keys']['revision uuid'];
  }
  // If we want revision UUIDs, but the entity doesn't support it. Return empty.
  else {
    return array();
  }

  // Get all UUIDs in one query.
  $result = db_select($table, 't')
    ->fields('t', array($id_key, $uuid_key))
    ->condition($id_key, array_values($ids), 'IN')
    ->execute()
    ->fetchAllKeyed();
  $cache = &drupal_static('entity_uuid_id_cache', array());
  $cache[$entity_type][(int) $revision] += array_flip($result);
  return $result + $cached_ids;
}

/**
 * Helper function to change entity properties from ID to UUID.
 *
 * We never change user UID 0 or 1 to UUIDs. Those are low level user accounts
 * ("anonymous" and "root") that needs to be identified consistently across
 * any system.
 *
 * @todo
 *   Add tests for this function.
 *
 * @param array $objects
 *   List of objects that should get $properties changed. Can be either an
 *   entity object or a field items array.
 * @param string $entity_type
 *   The type of entity that all $properties refers to.
 * @param array $properties
 *   An array of properties that should be changed. All properties must refer to
 *   the same type of entity (the one referenced in $entity_type).
 */
function entity_property_id_to_uuid(&$objects, $entity_type, $properties) {
  if (!is_array($objects)) {
    $things = array(&$objects);
  }
  else {
    $things = &$objects;
  }
  if (!is_array($properties)) {
    $properties = array($properties);
  }
  $ids = array();
  $values = array();
  $i = 0;
  foreach ($things as &$object) {
    foreach ($properties as $property) {
      // This is probably an entity object.
      if (is_object($object) && isset($object->{$property})) {
        $values[$i] = &$object->{$property};
      }
      // This is probably a field items array.
      elseif (is_array($object) && isset($object[$property])) {
        $values[$i] = &$object[$property];
      }
      else {
        $i++;
        continue;
      }
      if (!($entity_type == 'user' && ($values[$i] == 0 || $values[$i] == 1))) {
        $ids[] = $values[$i];
      }
      $i++;
    }
  }
  $uuids = entity_get_uuid_by_id($entity_type, $ids);
  foreach ($values as $i => $value) {
    if (isset($uuids[$value])) {
      $values[$i] = $uuids[$value];
    }
  }
}

/**
 * Helper function to change entity properties from UUID to ID.
 *
 * @todo
 *   Add tests for this function.
 *
 * @param array $objects
 *   List of objects that should get $properties changed. Can be either an
 *   entity object or a field items array.
 * @param string $entity_type
 *   The type of entity that all $properties refers to.
 * @param array $properties
 *   An array of properties that should be changed. All properties must refer to
 *   the same type of entity (the one referenced in $entity_type).
 */
function entity_property_uuid_to_id(&$objects, $entity_type, $properties) {
  if (!is_array($objects)) {
    $things = array(&$objects);
  }
  else {
    $things = &$objects;
  }
  if (!is_array($properties)) {
    $properties = array($properties);
  }
  $uuids = array();
  $values = array();
  $i = 0;
  foreach ($things as &$object) {
    foreach ($properties as $property) {
      // This is probably an entity object.
      if (is_object($object) && isset($object->{$property})) {
        $values[$i] = &$object->{$property};
      }
      // This is probably a field items array.
      elseif (is_array($object) && isset($object[$property])) {
        $values[$i] = &$object[$property];
      }
      else {
        $i++;
        continue;
      }
      if (uuid_is_valid($values[$i])) {
        $uuids[] = $values[$i];
      }
      $i++;
    }
  }
  $ids = entity_get_id_by_uuid($entity_type, $uuids);
  foreach ($values as $i => $value) {
    if (isset($ids[$value])) {
      $values[$i] = $ids[$value];
    }
  }
}

/**
 * @} End of "UUID support for Entity API"
 */
