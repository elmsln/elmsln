<?php

/**
 * @file
 * Support for the Migrate API.
 *
 * Your field collection migration should be run after the host entity
 * migration. For example, if the collection is attached to nodes via a field
 * named 'field_attached_data', and if the nodes are being imported by
 * ArticleMigration, your collection migration class constructor should look
 * like:
 *
 * @code
 *   $this->dependencies = array('Article');
 *
 *   $this->destination = new MigrateDestinationFieldCollection(
 *     'field_attached_data',
 *     array('host_entity_type' => 'node')
 *   );
 *
 *   $this->addFieldMapping('host_entity_id', 'source_article_id')
 *     ->sourceMigration('Article');
 * @endcode
 *
 * @see http://drupal.org/node/1900640
 */

/**
 * Destination class implementing migration into field_collection.
 */
class MigrateDestinationFieldCollection extends MigrateDestinationEntity {
  /**
   * The type of entity hosting this collection field (e.g., node).
   *
   * @var string
   */
  protected $hostEntityType;

  static public function getKeySchema() {
    return array(
      'item_id' => array(
        'type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'ID of field collection item',
      ),
    );
  }

  /**
   * Basic initialization.
   *
   * @param string $bundle
   *   Bundle name.
   * @param array $options
   *   (optional) Options applied to collections.
   */
  public function __construct($bundle, array $options = array()) {
    parent::__construct('field_collection_item', $bundle, $options);
    $this->hostEntityType = $options['host_entity_type'];
  }

  /**
   * Returns a list of fields available to be mapped for this collection
   * (bundle).
   *
   * @return array
   *   Keys: machine names of the fields (to be passed to addFieldMapping).
   *   Values: Human-friendly descriptions of the fields.
   */
  public function fields() {
    $fields = migrate_handler_invoke_all('Entity', 'fields', $this->entityType, $this->bundle);
    $fields['host_entity_id'] = t('Field collection host ID');
    return $fields;
  }

  /**
   * Import a single field collection item.
   *
   * @param $collection
   *   Collection object to build. Pre-filled with any fields mapped in the
   *   migration.
   * @param $row
   *   Raw source data object - passed through to prepare/complete handlers.
   *
   * @return array|false
   *   Array of key fields (item_id only in this case) of the collection that
   *   was saved or FALSE on failure.
   */
  public function import(stdClass $collection, stdClass $row) {
    if (isset($row->migrate_map_destid1)) {
      // We're updated an existing entity - start from the previous data.
      // entity_load() returns an array, so we get the field collection entity
      // with array_shift().
      $entity = array_shift(entity_load('field_collection_item', array($row->migrate_map_destid1), array(), TRUE));
      $entity_old = clone $entity;
      $updating = TRUE;
    }
    else {
      // Skip the collection if it has no host.
      if (empty($collection->host_entity_id)) {
        throw new MigrateException('Could not find host entity of the field collection to import.');
      }
      $entity = entity_create('field_collection_item', array('field_name' => $this->bundle));
      $updating = FALSE;
      $host_entity = entity_load_single($this->hostEntityType, $collection->host_entity_id);
      entity_get_controller($this->hostEntityType)->resetCache();
      $entity->setHostEntity($this->hostEntityType, $host_entity);
    }

    unset($collection->host_entity_id);

    foreach ((array) $collection as $field => $value) {
      $entity->{$field} = $value;
    }

    $this->prepare($entity, $row);

    // Restore fields from original field_collection_item if updating
    if ($updating) {
      foreach ($entity as $field => $value) {
        if ('field_' != substr($field, 0, 6)) {
          continue;
        }
        elseif (property_exists($entity_old, $field) && !property_exists($collection, $field)) {
          $entity->$field = $entity_old->$field;
        }
      }
    }

    migrate_instrument_start('field_collection_save');
    $status = entity_save('field_collection_item', $entity);
    migrate_instrument_stop('field_collection_save');

    if (in_array($this->hostEntityType, array('node', 'field_collection_item')) || ($status !== FALSE)) {
      $this->complete($entity, $row);
      if ($updating) {
        $this->numUpdated++;
      }
      else {
        $this->numCreated++;
      }
      return array($entity->item_id);
    }
    else {
      return FALSE;
    }
  }

  /**
   * Delete a migrated collection.
   *
   * @param $key
   *   Array of fields representing the key.
   */
  public function rollback(array $key) {
    $item_id = reset($key);

    $this->prepareRollback($item_id);
    $field_collection_item = field_collection_item_load($item_id);
    // If the collection wasn't imported then we can't roll it back, so check if
    // the loaded object is an instance of the FieldCollectionItemEntity class.
    if ($field_collection_item instanceof FieldCollectionItemEntity) {
      $field_collection_item->delete();
    }

    $this->completeRollback($item_id);
    return TRUE;
  }
}

/**
 * Implements migrate hook_migrate_api().
 */
function field_collection_migrate_api() {
  $api = array(
    'api' => 2,
  );
  return $api;
}
