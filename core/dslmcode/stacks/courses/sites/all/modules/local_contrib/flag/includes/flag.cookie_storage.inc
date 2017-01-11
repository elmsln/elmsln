<?php

/**
 * @file
 * Contains the FlagCookieStorage class.
 */

/**
 * Utility class to handle cookies.
 *
 * Cookies are used to record flaggings for anonymous users on cached pages.
 *
 * This class contains only two instance methods. Usage example:
 * @code
 *   $storage = FlagCookieStorage::factory($flag);
 *   $storage->flag(145);
 *   $storage->unflag(17);
 * @endcode
 *
 * You may delete all the cookies with <code>FlagCookieStorage::drop()</code>.
 */
abstract class FlagCookieStorage {

  /**
   * Returns the actual storage object compatible with the flag.
   */
  static function factory($flag) {
    if ($flag->global) {
      return new FlagGlobalCookieStorage($flag);
    }
    else {
      return new FlagNonGlobalCookieStorage($flag);
    }
  }

  function __construct($flag) {
    $this->flag = $flag;
  }

  /**
   * "Flags" an item.
   *
   * It just records this fact in a cookie.
   */
  abstract function flag($entity_id);

  /**
   * "Unflags" an item.
   *
   * It just records this fact in a cookie.
   */
  abstract function unflag($entity_id);

  /**
   * Deletes all the cookies.
   *
   * (Etymology: "drop" as in "drop database".)
   */
  static function drop() {
    FlagGlobalCookieStorage::drop();
    FlagNonGlobalCookieStorage::drop();
  }
}

/**
 * Storage handler for global flags.
 */
class FlagGlobalCookieStorage extends FlagCookieStorage {

  function flag($entity_id) {
    $cookie_key = $this->cookie_key($entity_id);
    setcookie($cookie_key, 1, REQUEST_TIME + $this->get_lifetime(), base_path());
    $_COOKIE[$cookie_key] = 1;
  }

  function unflag($entity_id) {
    $cookie_key = $this->cookie_key($entity_id);
    setcookie($cookie_key, 0, REQUEST_TIME + $this->get_lifetime(), base_path());
    $_COOKIE[$cookie_key] = 0;
  }

  // Global flags persist for the length of the minimum cache lifetime.
  protected function get_lifetime() {
    $cookie_lifetime = variable_get('cache', 0) ? variable_get('cache_lifetime', 0) : -1;
    // Do not let the cookie lifetime be 0 (which is the no cache limit on
    // anonymous page caching), since it would expire immediately. Usually
    // the no cache limit means caches are cleared on cron, which usually runs
    // at least once an hour.
    if ($cookie_lifetime == 0) {
      $cookie_lifetime = 3600;
    }
    return $cookie_lifetime;
  }

  protected function cookie_key($entity_id) {
    return 'flag_global_' . $this->flag->name . '_' . $entity_id;
  }

  /**
   * Deletes all the global cookies.
   */
  static function drop() {
    foreach ($_COOKIE as $key => $value) {
      if (strpos($key, 'flag_global_') === 0) {
        setcookie($key, FALSE, 0, base_path());
        unset($_COOKIE[$key]);
      }
    }
  }
}

/**
 * Storage handler for non-global flags.
 */
class FlagNonGlobalCookieStorage extends FlagCookieStorage {

  // The anonymous per-user flaggings are stored in a single cookie, so that
  // all of them persist as long as the Drupal cookie lifetime.

  function __construct($flag) {
    parent::__construct($flag);
    $this->flaggings = isset($_COOKIE['flags']) ? explode(' ', $_COOKIE['flags']) : array();
  }

  function flag($entity_id) {
    if (!$this->is_flagged($entity_id)) {
      $this->flaggings[] = $this->cookie_key($entity_id);
      $this->write();
    }
  }

  function unflag($entity_id) {
    if (($index = $this->index_of($entity_id)) !== FALSE) {
      unset($this->flaggings[$index]);
      $this->write();
    }
  }

  protected function get_lifetime() {
    return min((int) ini_get('session.cookie_lifetime'), (int) ini_get('session.gc_maxlifetime'));
  }

  protected function cookie_key($entity_id) {
    return $this->flag->name . '_' . $entity_id;
  }

  protected function write() {
    $serialized = implode(' ', array_filter($this->flaggings));
    setcookie('flags', $serialized, REQUEST_TIME + $this->get_lifetime(), base_path());
    $_COOKIE['flags'] = $serialized;
  }

  protected function is_flagged($entity_id) {
    return $this->index_of($entity_id) !== FALSE;
  }

  protected function index_of($entity_id) {
    return array_search($this->cookie_key($entity_id), $this->flaggings);
  }

  /**
   * Deletes the cookie.
   */
  static function drop() {
    if (isset($_COOKIE['flags'])) {
      setcookie('flags', FALSE, 0, base_path());
      unset($_COOKIE['flags']);
    }
  }
}
