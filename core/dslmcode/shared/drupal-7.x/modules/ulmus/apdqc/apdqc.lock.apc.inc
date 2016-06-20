<?php

/**
 * @file
 * An APC based implementation of a locking mechanism.
 *
 * See includes/lock.inc for documenation.
 */

/**
 * Initialize the locking system.
 */
function _apdqc_lock_initialize() {
  global $locks;

  $locks = array();
}

/**
 * Acquire (or renew) a lock, but do not block if it fails.
 *
 * @param string $name
 *   The name of the lock.
 * @param int $timeout
 *   A number of seconds (int) before the lock expires (minimum of 1).
 *
 * @return bool
 *   TRUE if the lock was acquired, FALSE if it failed.
 */
function _apdqc_lock_acquire($name, $timeout = 30) {
  global $locks;

  // Ensure that the timeout is at least 1 sec. APC works with integer TTL.
  $timeout = (int) max($timeout, 1);

  $key = _apdqc_apc_get_lock_key($name);

  if (apc_add($key, _lock_id(), $timeout)) {
    $locks[$name] = _lock_id();
  }
  elseif (apc_fetch($key) && isset($locks[$name]) && $locks[$name] == _lock_id()) {
    // Only renew the lock if we already set it and it has not expired.
    apc_store($key, _lock_id(), $timeout);
  }
  else {
    // Failed to acquire the lock.  Unset the key from the $locks array even
    // if not set, PHP 5+ allows this without error or warning.
    unset($locks[$name]);
  }

  return isset($locks[$name]);
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
function _apdqc_lock_may_be_available($name) {
  return !apc_fetch(_apdqc_apc_get_lock_key($name));
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
function _apdqc_lock_wait($name, $delay = 30) {
  // Pause the process for short periods between calling
  // lock_may_be_available(). This prevents hitting the database with constant
  // database queries while waiting, which could lead to performance issues.
  // However, if the wait period is too long, there is the potential for a
  // large number of processes to be blocked waiting for a lock, especially
  // if the item being rebuilt is commonly requested. To address both of these
  // concerns, begin waiting for 25ms, then add 25ms to the wait period each
  // time until it reaches 500ms. After this point polling will continue every
  // 500ms until $delay is reached.
  // $delay is passed in seconds, but we will be using usleep(), which takes
  // microseconds as a parameter. Multiply it by 1 million so that all
  // further numbers are equivalent.
  $delay = (int) $delay * 1000000;

  // Begin sleeping at 25ms.
  $sleep = 25000;
  while ($delay > 0) {
    // This function should only be called by a request that failed to get a
    // lock, so we sleep first to give the parallel request a chance to finish
    // and release the lock.
    usleep($sleep);
    // After each sleep, increase the value of $sleep until it reaches
    // 500ms, to reduce the potential for a lock stampede.
    $delay = $delay - $sleep;
    $sleep = min(500000, $sleep + 25000, $delay);
    if (!apc_fetch(_apdqc_apc_get_lock_key($name))) {
      // No longer need to wait.
      return FALSE;
    }
  }
  // The caller must still wait longer to get the lock.
  return TRUE;
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
function _apdqc_lock_release($name) {
  global $locks;

  apc_delete(_apdqc_apc_get_lock_key($name));
  // We unset unconditionally since caller assumes lock is released anyway.
  unset($locks[$name]);
}

/**
 * Generate a unique identifier for locks generated during this request.
 *
 * @return string
 *   The name of the unique lock id for this request.
 */
function _apdqc_lock_id() {
  static $lock_id;
  if (!isset($lock_id)) {
    $lock_id = uniqid(mt_rand(), TRUE);
    // We only register a shutdown function if a lock is used.
    register_shutdown_function('lock_release_all', $lock_id);
  }
  return $lock_id;
}

/**
 * Release all locks acquired by this request.
 *
 * @param string $lock_id
 *   The lock ID for this request.
 */
function _apdqc_lock_release_all($lock_id = NULL) {
  global $locks;
  foreach ($locks as $name => $id) {
    $value = apc_fetch(_apdqc_apc_get_lock_key($name));

    if ($value == $id) {
      apc_delete(_apdqc_apc_get_lock_key($name));
    }
  }
}

/**
 * Helper function for getting a cache key for apc.
 *
 * @param string $name
 *   The name of the lock.
 *
 * @return string
 *   The name of the key.
 */
function _apdqc_apc_get_lock_key($name) {
  return "apc_lock:$name";
}
