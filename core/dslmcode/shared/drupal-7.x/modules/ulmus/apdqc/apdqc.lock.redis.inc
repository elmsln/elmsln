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
namespace base_lock {
  // Include our own autoloader to ensure classes to be there.
  // We cannot rely on core in case of early bootstrap phases.
  require_once dirname(variable_get('base_lock_inc', BASE_LOCK_INC)) . '/redis.autoload.inc';

  /**
   * Foo function, keeping it for API consistency (Drupal 7).
   */
  function lock_initialize() {}

  /**
   * Foo function, keeping it for API consistency (Drupal 6).
   */
  function lock_init() {}

  /**
   * Foo function, keeping it for API consistency.
   * Some insane people may actually use it.
   */
  function _lock_id() {
    return Redis_Lock::getBackend()->getLockId();
  }

  function lock_acquire($name, $timeout = 30.0) {
    return Redis_Lock::getBackend()->lockAcquire($name, $timeout);
  }

  function lock_may_be_available($name) {
    return Redis_Lock::getBackend()->lockMayBeAvailable($name);
  }

  function lock_wait($name, $delay = 30) {
    return Redis_Lock::getBackend()->lockWait($name, $delay);
  }

  function lock_release($name) {
    return Redis_Lock::getBackend()->lockRelease($name);
  }

  function lock_release_all($lock_id = NULL) {
    return Redis_Lock::getBackend()->lockReleaseAll($lock_id);
  }

  // Since D6 doesn't have the drupal_register_shutdown_function
  // that is called in lib/Redis/Lock/Backend/Default.php define
  // the wrapper here.
  if (!function_exists('drupal_register_shutdown_function')) {
    function drupal_register_shutdown_function(){
      $args = func_get_args();
      call_user_func_array('register_shutdown_function', $args);
    }
  }
}