<?php

/**
 * @file
 * A memcached based implementation of a locking mechanism.
 *
 * See includes/lock.inc for documentation.
 */

/**
 * Initialize the locking system.
 */
function _apdqc_lock_initialize() {
  global $locks;

  $locks = array();
}

/**
 * Helper function to get this request's unique id.
 */
function _apdqc_lock_id() {
  // Do not use drupal_static(). This identifier refers to the current
  // client request, and must not be changed under any circumstances
  // else the shutdown handler may fail to release our locks.
  static $lock_id;

  if (!isset($lock_id)) {
    // Assign a unique id.
    $lock_id = uniqid(mt_rand(), TRUE);
    // We only register a shutdown function if a lock is used.
    drupal_register_shutdown_function('lock_release_all', $lock_id);
  }
  return $lock_id;
}

/**
 * Acquire (or renew) a lock, but do not block if it fails.
 *
 * @param string $name
 *   The name of the lock.
 * @param int $timeout
 *   A number of seconds (float) before the lock expires (minimum of 0.001).
 *
 * @return bool
 *   TRUE if the lock was acquired, FALSE if it failed.
 */
function _apdqc_lock_acquire($name, $timeout = 30.0) {
  global $locks;

  // Insure that the timeout is at least 1 second.
  $expire = (int) max($timeout, 1);

  if (isset($locks[$name])) {

    // Try to extend the expiration of a lock we already acquired.
    $success = MemcacheStorageAPI::replace($name, _lock_id(), $expire, 'semaphore');

    if (!$success) {
      // The lock was broken.
      unset($locks[$name]);
    }
  }
  else {

    // Add new lock.
    if (MemcacheStorageAPI::add($name, _lock_id(), $expire, 'semaphore')) {
      // We track all acquired locks in the global variable.
      $locks[$name] = TRUE;
    }
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
  $lock_exists = MemcacheStorageAPI::get($name, 'semaphore');
  return $lock_exists ? FALSE : TRUE;
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
    if (lock_may_be_available($name)) {
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

  // We unset unconditionally since caller assumes lock is released anyway.
  unset($locks[$name]);

  // Remove current lock from memcached pool.
  $lock = MemcacheStorageAPI::get($name, 'semaphore');
  if ($lock && $lock == _lock_id()) {
    MemcacheStorageAPI::delete($name, 'semaphore');
  }
}

/**
 * Release all previously acquired locks.
 */
function _apdqc_lock_release_all($lock_id = NULL) {
  global $locks;

  if (empty($lock_id)) {
    $lock_id = _lock_id();
  }

  // Remove all current locks from memcached pool.
  foreach ($locks as $name => $id) {
    $lock = MemcacheStorageAPI::get($name, 'semaphore');
    if ($lock && $lock == $lock_id) {
      MemcacheStorageAPI::delete($name, 'semaphore');
    }
  }

  // Clear global variable.
  $locks = array();
}
