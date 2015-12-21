<?php

/**
 * @file
 * Drupal core lock.inc replacement.
 *
 * Do not use this file directly, it will be included by the backend specific
 * implementation when added to settings.php file.
 *
 * See README.txt file for details.
 */

/**
 * Initialize the locking system.
 */
function _apdqc_lock_initialize() {
}

/**
 * Generate a unique identifier for locks generated during this request.
 */
function _apdqc_lock_id() {
  return Redis_Lock::getBackend()->getLockId();
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
function _apdqc_lock_acquire($name, $timeout = 30.0) {
  return Redis_Lock::getBackend()->lockAcquire($name, $timeout);
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
  return Redis_Lock::getBackend()->lockMayBeAvailable($name);
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
  return Redis_Lock::getBackend()->lockWait($name, $delay);
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
  return Redis_Lock::getBackend()->lockRelease($name);
}

/**
 * Release all locks acquired by this request.
 */
function _apdqc_lock_release_all($lock_id = NULL) {
  return Redis_Lock::getBackend()->lockReleaseAll($lock_id);
}
