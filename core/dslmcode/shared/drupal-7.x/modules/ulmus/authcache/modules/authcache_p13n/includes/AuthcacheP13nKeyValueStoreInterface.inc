<?php
/**
 * @file
 * Defines an interface for key-value stores.
 */

/**
 * Interface for key-value store implementations.
 */
interface AuthcacheP13nKeyValueStoreInterface {
  /**
   * Set a value in the collection with the given key.
   *
   * @param string $key
   *   A key.
   */
  public function set($key, $value);

  /**
   * Return an associative array of entries for the given keys.
   *
   * @param array $keys
   *   A list of strings.
   */
  public function get($keys = NULL);

  /**
   * Return the value from the collection for the given key.
   *
   * @param string $key
   *   A key.
   */
  public function getOne($key);

  /**
   * Return a list of existing keys.
   *
   * @param array|NULL $keys
   *   A list of keys which should be checked.
   */
  public function getKeys($keys = NULL);

  /**
   * Remove entries with the given key. If keys is omitted, delete all entries.
   *
   * @param array $keys
   *   A list of strings.
   */
  public function delete($keys = NULL);
}
