<?php

/**
 * @file
 * A basic database key-value store caching module derived from DX Cache (https://www.drupal.org/project/dx_cache).
 * Designed to emulate simpler caching systems like those included in modern PHP frameworks, there are four simple functions: set, get, has, and del (delete).
 * Simply set a value with dx_cache_set($key, $value, $time_to_live), for example you can set an item that will expire in 30 seconds like this: dx_cache_set("my.key", array('my' => 'value'), 30);
 * Then you can check if it exists (and is valid) using: dx_cache_has('my.key'); // Return true or false
 * You can retrieve the value using: $myvalue = dx_cache_get('my.key'); - Returns the value if valid, null if expired, and null if it does not exist.
 * You can also set a default value to return if the key is not set or expired: $myval = dx_cache_get('my.key', 'value to return if not found or expired');
 * And you can delete values using: dx_cache_del('my.key');
 * Cron will also periodically delete expired keys every time it runs.
 */

/**
 * Convenience method to check if a cache object exists.
 *
 * @param string $name
 *   the object name
 *
 * @return bool
 *   TRUE if exists, FALSE if not.
 */
function puzzler_cache_has($name) {
  $items = db_query("SELECT expires, value FROM {puzzler_cache} WHERE name = :name LIMIT 1", array(':name' => $name))->fetchAll();
  if (count($items) == 1) {
    // Make sure that this hasn't expired.
    $time = time();
    if (isset($items[0]->expires) && $items[0]->expires < $time) {
      puzzler_cache_del($name);
      return FALSE;
    }
    return TRUE;
  }
  else {
    return FALSE;
  }
}

/**
 * Set a value in the table, with an optional time to live.
 *
 * @param string $name
 *   The name of the object
 * @param mixed $value
 *   Value to serialize and store
 * @param int $ttl
 *   Time in seconds to expire
 *
 * @return bool
 *   True if a new record is written.
 */
function puzzler_cache_set($name, $value, $ttl = NULL) {

  $value = serialize($value);

  if (isset($ttl) && !is_int($ttl)) {
    return FALSE;
  }

  db_delete('puzzler_cache')->condition('name', $name)->execute();

  $time = time();

  $data = array(
    'name'       => $name,
    'value'      => $value,
    'expires'    => isset($ttl) ? ($time + $ttl) : NULL,
    'created_at' => $time,
  );

  return db_insert("puzzler_cache")->fields($data)->execute();

}

/**
 * Get a value from the DB.
 *
 * @param string $name
 *   The object name
 * @param mixed $default
 *   the optional value to return if it does not exist
 *
 * @return mixed
 *   The cached or default item
 */
function puzzler_cache_get($name, $default = NULL) {

  if (puzzler_cache_has($name)) {

    $value = db_query("SELECT * FROM {puzzler_cache} WHERE name = :name", array(':name' => $name))->fetchAll();
    $value = $value[0];

    $time = time();

    if (isset($value->expires) && ($value->expires < $time)) {
      db_delete('puzzler_cache')->condition('name', $name)->execute();
      return $default;
    }

    return unserialize($value->value);

  }
  else {
    // Doesn't exist.
    return $default;
  }

}

/**
 * Delete a cache item.
 *
 * @param string $name
 *   The key of the item to delete
 *
 * @return mixed
 *   The value stored in the DB.
 */
function puzzler_cache_del($name) {
  return db_delete('puzzler_cache')->condition('name', $name)->execute();
}

/**
 * Implements hook_cron().
 */
function puzzler_cache_cron() {
  $time = time();
  db_delete('puzzler_cache')->condition('expires', $time, '<')->execute();
}
