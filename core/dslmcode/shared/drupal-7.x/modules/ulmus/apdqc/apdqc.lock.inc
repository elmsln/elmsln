<?php

/**
 * @file
 * A database-mediated implementation of a locking mechanism.
 */

/**
 * Location of the base lock file.
 */
define('BASE_LOCK_INC', 'includes/lock.inc');

// Get base lock file location.
$base_lock_location = variable_get('base_lock_inc', BASE_LOCK_INC);

// Namespaces are only available in PHP 5.3+.
if (!defined('PHP_VERSION_ID') || PHP_VERSION_ID < 50300) {
  // Fallback to the base locking include file.
  require_once $base_lock_location;
}
else {
  $lock_file_included = FALSE;
  $default_cache_class = variable_get('cache_default_class');
  // Memcache.
  if ($default_cache_class === 'MemCacheDrupal' || strpos($base_lock_location, '/memcache/memcache-lock.inc') !== FALSE) {
    require_once dirname($base_lock_location) . '/dmemcache.inc';

    // Use memcache locking if memcached is available.
    if (dmemcache_object('semaphore')) {
      $lock_file_included = TRUE;
      require_once 'apdqc.lock.memcache.inc';
    }
  }
  // Memcache storage.
  if ($default_cache_class === 'MemcacheStorage' || strpos($base_lock_location, '/memcache_storage/includes/lock.inc') !== FALSE) {
    // Use memcache storage locking if memcache storage is available.
    if (class_exists('MemcacheStorageAPI')) {
      $lock_file_included = TRUE;
      require_once 'apdqc.lock.memcache_storage.inc';
    }
  }
  // APCu.
  if ($default_cache_class === 'DrupalAPCCache' || strpos($base_lock_location, '/apc/drupal_apc_lock.inc') !== FALSE) {
    // Use apc locking if apc_fetch && apc_store are available.
    if (function_exists('apc_fetch') && function_exists('apc_store')) {
      $lock_file_included = TRUE;
      require_once 'apdqc.lock.apc.inc';
    }
  }
  // Redis.
  if ($default_cache_class === 'Redis_Cache' || strpos($base_lock_location, '/redis/redis.lock.inc') !== FALSE) {
    // Include our own autoloader to ensure classes to be there.
    // We cannot rely on core in case of early bootstrap phases.
    require_once dirname(variable_get('base_lock_inc', BASE_LOCK_INC)) . '/redis.autoload.inc';

    include_once REDIS_ROOT . '/Redis/Lock.php';
    include_once REDIS_ROOT . '/Redis/Client.php';

    // Use redis locking.
    $lock_file_included = TRUE;
    require_once 'apdqc.lock.redis.inc';
  }
  // Core.
  if (strpos($base_lock_location, 'includes/lock.inc') !== FALSE || !$lock_file_included) {
    // Make sure apdqc_fast_get_db_type() is available.
    require_once 'apdqc.cache.inc';
    // Load the correct database backend.
    $db_type = apdqc_fast_get_db_type();
    if ($db_type === 'mysql') {
      require_once 'apdqc.mysql.inc';
      $lock_file_included = TRUE;
      require_once 'apdqc.lock.db.inc';
    }
  }
  // Other.
  if (!$lock_file_included) {
    // Use eval fallback.
    // @ignore security_19
    eval('namespace base_lock {?>' . file_get_contents(DRUPAL_ROOT . '/' . $base_lock_location) . '}');
  }
  $GLOBALS['conf']['apdqc_lock_file_included'] = $lock_file_included;

  /**
   * Initialize the locking system.
   */
  function lock_initialize() {
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function();
    }
    else {
      return base_lock\lock_initialize();
    }
  }

  /**
   * Helper function to get this request's unique id.
   */
  function _lock_id() {
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc' . __FUNCTION__;
      return $function();
    }
    else {
      return base_lock\_lock_id();
    }
  }

  /**
   * Acquire (or renew) a lock, but do not block if it fails.
   *
   * @param string $name
   *   The name of the lock. Limit of name's length is 255 characters.
   * @param float $timeout
   *   A number of seconds (float) before the lock expires (minimum of 0.001).
   *
   * @return bool
   *   TRUE if the lock was acquired, FALSE if it failed.
   */
  function lock_acquire($name, $timeout = 30.0) {
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function($name, $timeout);
    }
    else {
      return base_lock\lock_acquire($name, $timeout);
    }
  }

  /**
   * Check if lock acquired by a different process may be available.
   *
   * If an existing lock has expired, it is removed.
   *
   * @param string $name
   *   The name of the lock.
   *
   * @return bool
   *   TRUE if there is no lock or it was removed, FALSE otherwise.
   */
  function lock_may_be_available($name) {
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function($name);
    }
    else {
      return base_lock\lock_may_be_available($name);
    }
  }

  /**
   * Wait for a lock to be available.
   *
   * This function may be called in a request that fails to acquire a desired
   * lock. This will block further execution until the lock is available or the
   * specified delay in seconds is reached. This should not be used with locks
   * that are acquired very frequently, since the lock is likely to be acquired
   * again by a different request while waiting.
   *
   * @param string $name
   *   The name of the lock.
   * @param int $delay
   *   The maximum number of seconds to wait, as an integer.
   *
   * @return bool
   *   TRUE if the lock holds, FALSE if it is available.
   */
  function lock_wait($name, $delay = 30) {
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function($name, $delay);
    }
    else {
      return base_lock\lock_wait($name, $delay);
    }
  }

  /**
   * Release a lock previously acquired by lock_acquire().
   *
   * This will release the named lock if it is still held by the current
   * request.
   *
   * @param string $name
   *   The name of the lock.
   */
  function lock_release($name) {
    apdqc_wait_for_all_async_queries();
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function($name);
    }
    else {
      return base_lock\lock_release($name);
    }
  }

  /**
   * Release all previously acquired locks.
   */
  function lock_release_all($lock_id = NULL) {
    apdqc_wait_for_all_async_queries();
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      return $function($lock_id);
    }
    else {
      return base_lock\lock_release_all($lock_id);
    }
  }

  /**
   * Wait for all async queries to finish.
   */
  function apdqc_wait_for_all_async_queries() {
    if (function_exists('apdqc_get_db_object')) {
      return apdqc_get_db_object(array(), array(), array('async' => FALSE, 'reap' => TRUE));
    }
  }

  /**
   * Change the lock id.
   *
   * @param string $name
   *   Name of the lock.
   * @param string $old_lock_id
   *   Value from _lock_id().
   * @param string $new_lock_id
   *   New value for the 'value' column in the database.
   */
  function lock_change_lock_id($name, $old_lock_id, $new_lock_id) {
    if (empty($old_lock_id)) {
      $old_lock_id = _lock_id();
    }
    if ($GLOBALS['conf']['apdqc_lock_file_included']) {
      $function = '_apdqc_' . __FUNCTION__;
      if (function_exists($function)) {
        return $function($name, $old_lock_id, $new_lock_id);
      }
    }
    else {
      if (function_exists('base_lock\lock_change_lock_id')) {
        return base_lock\lock_change_lock_id($name, $old_lock_id, $new_lock_id);
      }
    }
  }

  /**
   * Release a lock previously acquired by lock_acquire().
   *
   * This will release the named lock.
   *
   * @param string $name
   *   The name of the lock.
   */
  function lock_release_fuzzy($name) {
    $function = '_apdqc_' . __FUNCTION__;
    if ($GLOBALS['conf']['apdqc_lock_file_included'] && function_exists($function)) {
      apdqc_wait_for_all_async_queries();
      return $function($name);
    }
    elseif (function_exists('base_lock\lock_release_fuzzy')) {
      apdqc_wait_for_all_async_queries();
      return base_lock\lock_release_fuzzy($name);
    }
    else {
      return lock_release($name);
    }
  }
}
