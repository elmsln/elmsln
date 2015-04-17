<?php
/**
 * @file
 * Defines database based implementation of a key-value store.
 */

/**
 * Database based implementation of key-value store.
 */
class AuthcacheP13nDatabaseKeyValueStore implements AuthcacheP13nKeyValueStoreInterface {
  protected static $tableName = 'authcache_p13n_key_value';

  protected $collectionName;

  /**
   * Construct new key-value store operating on the given table-name.
   */
  public function __construct($collection_name) {
    $this->collectionName = $collection_name;
  }

  /**
   * {@inheritdoc}
   */
  public function set($key, $value) {
    db_merge(static::$tableName)
      ->key(array(
        'name' => $key,
        'collection' => $this->collectionName,
      ))
      ->fields(array('value' => serialize($value)))
      ->execute();
  }

  /**
   * {@inheritdoc}
   */
  public function get($keys = NULL) {
    if ($keys === array()) {
      return array();
    }

    $query = db_select(static::$tableName, 'kv')
      ->fields('kv', array('name', 'value'))
      ->condition('collection', $this->collectionName);

    if ($keys !== NULL) {
      $query->condition('name', $keys);
    }

    return array_map('unserialize', $query->execute()->fetchAllKeyed());
  }

  /**
   * {@inheritdoc}
   */
  public function getOne($key) {
    $result = $this->get(array($key));
    if (count($result) > 0) {
      return reset($result);
    }
  }

  /**
   * {@inheritdoc}
   */
  public function getKeys($keys = NULL) {
    if ($keys === array()) {
      return array();
    }

    $query = db_select(static::$tableName, 'kv')
      ->fields('kv', array('name'))
      ->condition('collection', $this->collectionName);

    if ($keys !== NULL) {
      $query->condition('name', $keys);
    }

    return $query->execute()->fetchCol();
  }

  /**
   * {@inheritdoc}
   */
  public function delete($keys = NULL) {
    if ($keys === array()) {
      return 0;
    }

    $query = db_delete(static::$tableName)
      ->condition('collection', $this->collectionName);

    if ($keys !== NULL) {
      $query->condition('name', $keys);
    }

    return $query->execute();
  }
}
