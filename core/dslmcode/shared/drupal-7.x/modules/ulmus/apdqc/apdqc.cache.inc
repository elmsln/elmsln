<?php
/**
 * @file
 * Extends Drupal's default database cache so async queries happen.
 */

/**
 * How long to wait until garbage collection is done on the cache bin.
 */
define('CACHE_GARBAGE_COLLECTION_FREQUENCY', 3600);

/**
 * Set to TRUE in order to run DELETE instead of TRUNCATE on all cache bins.
 */
define('CACHE_NO_TRUNCATE', FALSE);

/**
 * Set to FALSE in order to not prefetch all of the cache_bootstrap cache bin.
 */
define('CACHE_BOOTSTRAP_PREFETCH', TRUE);

/**
 * If TRUE call apdqc_cache_clear_alter() & apdqc_cache_clear() on cache clear.
 */
define('APDQC_CALL_HOOK_ON_CLEAR', FALSE);

/**
 * Prefetch data from a cache table.
 *
 * @param array $table_keys_cache_prefetch
 *   Array('table' => array(cache_ids)).
 * @param bool $reap_on_next_get
 *   Set to false to not block the next cache get call if query is still
 *   running.
 * @param bool $log
 *   Set to false to disable devel logging for this query.
 */
function apdqc_run_prefetch_array(array $table_keys_cache_prefetch, $reap_on_next_get = TRUE, $log = TRUE) {
  static $use_async_data;
  if (!isset($use_async_data)) {
    $do_not_use_async_data = &drupal_static(__FUNCTION__);
  }
  if ($do_not_use_async_data) {
    return;
  }
  if (defined('APDQC_PREFETCH')) {
    // Bail if apdqc_prefetch is disabled.
    if (!variable_get('apdqc_prefetch', APDQC_PREFETCH)) {
      return;
    }
  }

  // Process and run query.
  $query = '';
  $tables = array();
  $all_cids = array();
  foreach ($table_keys_cache_prefetch as $bin => $cids) {
    if (apdqc_get_bin_class_name($bin) !== 'APDQCache') {
      continue;
    }
    $tables[] = $bin;
    $all_cids = array_merge($all_cids, $cids);
    // Use a union query if hitting mutiple cache bins.
    if (!empty($query)) {
      $query .= "\nUNION ALL ";
    }

    if (isset($cids['*'])) {
      $query .= "SELECT '$bin' AS bin, cid, data, created, expire, serialized FROM " . apdqc_fast_prefix_tables('{' . apdqc_fast_escape_table($bin) . '}') . "";
      if (!empty($cids['*']) && is_array($cids['*'])) {
        $cids_string = "'" . implode("', '", $cids['*']) . "'";
        $query .= " WHERE cid NOT IN ({$cids_string})";
      }
    }
    else {
      $like_ids = array();
      foreach ($cids as $key => $cid) {
        if (strpos($cid, '%') !== FALSE) {
          unset($cids[$key]);
          $like_ids[] = $cid;
        }
      }
      // Build query string.
      $query .= "SELECT '$bin' AS bin, cid, data, created, expire, serialized FROM " . apdqc_fast_prefix_tables('{' . apdqc_fast_escape_table($bin) . '}');

      if (!empty($cids)) {
        // Concat array into strings.
        $cids_string = "'" . implode("', '", $cids) . "'";
        $query .= " WHERE cid IN ({$cids_string}) ";
      }
      if (!empty($like_ids)) {
        // Do the first LIKE.
        $cid = array_shift($like_ids);
        if (empty($cids)) {
          $query .= " WHERE ";
        }
        else {
          $query .= "OR ";
        }
        $query .= "cid LIKE '$cid' ";

        // Do the rest of the LIKEs.
        foreach ($like_ids as $cid) {
          $query .= "OR cid LIKE '$cid' ";
        }
      }
    }
  }

  // Prefetch cache.
  if (!empty($query)) {
    apdqc_query($tables, $all_cids, $query, array('async' => TRUE, 'log' => $log));
  }
}

/**
 * Append a database prefix to all tables in a query.
 *
 * Queries sent to Drupal should wrap all table names in curly brackets. This
 * function searches for this syntax and adds Drupal's table prefix to all
 * tables, allowing Drupal to coexist with other systems in the same database if
 * necessary.
 *
 * @param string $sql
 *   A string containing a partial or entire SQL query.
 *
 * @return string
 *   The properly-prefixed string.
 */
function apdqc_fast_prefix_tables($sql) {
  $db_prefix = isset($GLOBALS['databases']['default']['default']['prefix']) ? $GLOBALS['databases']['default']['default']['prefix'] : '';

  if (is_array($db_prefix)) {
    if (array_key_exists('default', $db_prefix)) {
      $tmp = $db_prefix;
      unset($tmp['default']);
      foreach ($tmp as $key => $val) {
        $sql = strtr($sql, array('{' . $key . '}' => $val . $key));
      }
      return strtr($sql, array('{' => $db_prefix['default'], '}' => ''));
    }
    else {
      foreach ($db_prefix as $key => $val) {
        $sql = strtr($sql, array('{' . $key . '}' => $val . $key));
      }
      return strtr($sql, array('{' => '', '}' => ''));
    }
  }
  else {
    return strtr($sql, array('{' => $db_prefix, '}' => ''));
  }
}

/**
 * Returns current database type. mysql is the only usable one currently.
 */
function apdqc_fast_get_db_type() {
  return $GLOBALS['databases']['default']['default']['driver'];
}

/**
 * Restrict a dynamic table, column or constraint name to safe characters.
 *
 * Only keeps alphanumeric and underscores.
 */
function apdqc_fast_escape_table($string) {
  return preg_replace('/[^A-Za-z0-9_]+/', '', $string);
}

/**
 * Gets the cache class name for a cache bin.
 *
 * @param string $bin
 *   The cache bin for which the cache class name should be returned.
 *
 * @return string
 *   The cache class name used for this specified bin.
 *
 * @see DrupalCacheInterface()
 * @see _cache_get_object()
 */
function apdqc_get_bin_class_name($bin) {
  // We do not use drupal_static() here because we do not want to change the
  // storage of a cache bin mid-request.
  static $cache_objects;
  if (!isset($cache_objects[$bin])) {
    $class = variable_get('cache_class_' . $bin);
    if (!isset($class)) {
      $class = variable_get('cache_default_class', 'DrupalDatabaseCache');
    }
    $cache_objects[$bin] = $class;
  }
  return $cache_objects[$bin];
}

/**
 * A pretty darn quick cache implementation of Drupal's default cache backend.
 *
 * This cache backend extends Drupal's default database cache implementation by
 * altering how drupal interacts with the database.
 *
 * @see http://drupal.org/node/891600
 */
class APDQCache extends DrupalDatabaseCache {

  /**
   * Constructs a DrupalDatabaseCache object.
   *
   * @param string $bin
   *   The cache bin for which the object is created.
   */
  public function __construct($bin) {
    // Load the correct database backend.
    $db_type = apdqc_fast_get_db_type();
    // Async queries are only available in PHP 5.3+.
    if ($db_type === 'mysql' && defined('PHP_VERSION_ID') && PHP_VERSION_ID >= 50300) {
      require_once 'apdqc.mysql.inc';
    }
    parent::__construct($bin);
  }

  /**
   * Implements DrupalCacheInterface::getMultiple().
   *
   * We handle garbage collection differently; this method is reimplemented only
   * to remove a call to the garbageCollection() method.
   */
  public function getMultiple(&$cids) {
    try {
      $gc_frequency = variable_get('cache_garbage_collection_frequency', CACHE_GARBAGE_COLLECTION_FREQUENCY);
      if (empty($gc_frequency)) {
        // Garbage collection necessary when enforcing a minimum cache lifetime.
        $this->garbageCollection($this->bin);
      }

      $query_cids = $cids;
      $prefetch = array();
      $result = array();
      if (variable_get('cache_bootstrap_prefetch', CACHE_BOOTSTRAP_PREFETCH) || (defined('APDQC_PREFETCH') && variable_get('apdqc_prefetch', APDQC_PREFETCH))) {
        $prefetch = apdqc_async_data(FALSE, $this->bin, $cids);
        $query_cids = array_diff($cids, array_keys($prefetch));
        $prefetch = array_values($prefetch);
      }

      $result = array();
      if (!empty($query_cids)) {
        // Build query.
        $query = Database::getConnection()->prefixTables("SELECT cid, data, created, expire, serialized FROM {" . db_escape_table($this->bin) . "}");
        // If this is the cache_bootstrap bin and the cid is variables, get
        // the bootstrap_modules & lookup_cache ids as well.
        if ($this->bin === 'cache_bootstrap' && $query_cids[0] === 'variables' && count($query_cids) == 1) {
          $query_cids[] = 'bootstrap_modules';
          $query_cids[] = 'lookup_cache';
          $query_cids[] = 'system_list';
          $query_cids[] = 'module_implements';
          $bootstrap = TRUE;
        }
        foreach ($query_cids as $cid) {
          $escaped_cids[] = apdqc_escape_string($cid);
        }
        $escaped_cids = "'" . implode("', '", $escaped_cids) . "'";
        $query .= " WHERE cid IN ({$escaped_cids})";
        // Run query.
        $result = apdqc_query(array($this->bin), $query_cids, $query, array('fetch_all' => TRUE));
      }
      if (is_string($result) && $result === 'NO DB') {
        // When serving cached pages, the overhead of using db_select() was
        // found to add around 30% overhead to the request. Since $this->bin is
        // a variable, this means the call to db_query() here uses a
        // concatenated string. This is highly discouraged under any other
        // circumstances, and is used here only due to the performance overhead
        // we would incur otherwise. When serving an uncached page, the overhead
        // of using db_select() is a much smaller proportion of the request.
        $result = db_query('SELECT cid, data, created, expire, serialized FROM {' . db_escape_table($this->bin) . '} WHERE cid IN (:cids)', array(':cids' => $cids));
      }
      else {
        $result = array_merge($result, $prefetch);
      }

      $cache = array();
      if (!empty($result)) {
        foreach ($result as $item) {
          // Skip empty items.
          if (empty($item)) {
            continue;
          }
          if (!empty($bootstrap) && is_array($item) && ($item['cid'] === 'bootstrap_modules' || $item['cid'] === 'lookup_cache' || $item['cid'] === 'system_list' || $item['cid'] === 'module_implements')) {
            $local_storage = &drupal_static('apdqc_async_data');
            $item['bin'] = $this->bin;
            $local_storage[$this->bin][$item['cid']] = $item;
            continue;
          }
          // Convert to an object to mirror db_query if needed.
          if (is_array($item)) {
            $item = (object) $item;
          }
          $item = $this->prepareItem($item);
          if ($item) {
            $cache[$item->cid] = $item;
          }
        }
      }
      $cids = array_diff($cids, array_keys($cache));
      return $cache;
    }
    catch (Exception $e) {
      // If the database is never going to be available, cache requests should
      // return FALSE in order to allow exception handling to occur.
      return array();
    }
  }

  /**
   * Generic garbage collection method.
   *
   * Rather than respecting minimum cache lifetime at the bin-level, we respect
   * it on an entry-by-entry basis.
   *
   * Additionally, we've moved session cache handling to a separate method.
   */
  protected function garbageCollection() {
    $cache_lifetime = variable_get('cache_lifetime', 0);
    $gc_frequency = variable_get('cache_garbage_collection_frequency', CACHE_GARBAGE_COLLECTION_FREQUENCY);

    if (empty($gc_frequency)) {
      $cache_lifetime = variable_get('cache_lifetime', 0);

      // Clean-up the per-user cache expiration session data, so that the
      // session handler can properly clean-up the session data for anonymous
      // users.
      if (isset($_SESSION['cache_expiration'])) {
        $expire = REQUEST_TIME - $cache_lifetime;
        foreach ($_SESSION['cache_expiration'] as $bin => $timestamp) {
          if ($timestamp < $expire) {
            unset($_SESSION['cache_expiration'][$bin]);
          }
        }
        if (!$_SESSION['cache_expiration']) {
          unset($_SESSION['cache_expiration']);
        }
      }

      // Garbage collection of temporary items is only necessary when enforcing
      // a minimum cache lifetime.
      if (!$cache_lifetime) {
        return;
      }
      // When cache lifetime is in force, avoid running garbage collection too
      // often since this will remove temporary cache items indiscriminately.
      $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
      if ($cache_flush && ($cache_flush + $cache_lifetime <= REQUEST_TIME)) {
        // Reset the variable immediately to prevent a meltdown in heavy load
        // situations.
        variable_set('cache_flush_' . $this->bin, 0);
        // Time to flush old cache data
        // Build query.
        $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");
        $query .= "WHERE (expire <> " . CACHE_PERMANENT . " AND expire <= " . $cache_flush . ")";

        // Run query.
        $result = apdqc_query(array($this->bin), array('*'), $query, array('async' => TRUE));
        if (is_string($result) && $result === 'NO DB') {
          // Use the DrupalDatabaseCache class.
          return parent::garbageCollection();
        }
      }
    }
    else {
      // Build query.
      $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");

      if (!empty($cache_lifetime)) {
        // Clear expired items from the cache.
        $query .= "WHERE (expire > " . CACHE_PERMANENT . " AND expire < " . REQUEST_TIME . ")";

        // Clear CACHE_TEMPORARY items that are older than cache_lifetime.
        $query .= "OR (expire = " . CACHE_TEMPORARY . " AND created < " . apdqc_escape_string(REQUEST_TIME - $cache_lifetime) . ")";
      }
      else {
        // No minimum lifetime. Flush all expired and temporary cache entries.
        $query .= "WHERE (expire <> " . CACHE_PERMANENT . " AND expire < " . REQUEST_TIME . ")";
      }

      // Run query.
      $result = apdqc_query(array($this->bin), array('*'), $query, array('async' => TRUE));
      if (is_string($result) && $result === 'NO DB') {
        if (!empty($cache_lifetime)) {
          // Clear expired items from the cache.
          db_delete($this->bin)
            ->condition('expire', CACHE_PERMANENT, '>')
            ->condition('expire', REQUEST_TIME, '<')
            ->execute();

          // Clear CACHE_TEMPORARY items that are older than cache_lifetime.
          db_delete($this->bin)
            ->condition('expire', CACHE_TEMPORARY)
            ->condition('created', REQUEST_TIME - $cache_lifetime, '<')
            ->execute();
        }
        else {
          // No minimum lifetime. Flush all expired and temporary cache entries.
          db_delete($this->bin)
            ->condition('expire', CACHE_PERMANENT, '<>')
            ->condition('expire', REQUEST_TIME, '<')
            ->execute();
        }
      }
    }
  }


  /**
   * Cleans up the per-session cache expiration data.
   */
  protected function cleanSession() {
    $cache_lifetime = variable_get('cache_lifetime', 0);
    if (isset($_SESSION['cache_expiration'])) {
      $expire = REQUEST_TIME - $cache_lifetime;
      foreach ($_SESSION['cache_expiration'] as $bin => $timestamp) {
        if ($timestamp < $expire) {
          unset($_SESSION['cache_expiration'][$bin]);
        }
      }
      if (!$_SESSION['cache_expiration']) {
        unset($_SESSION['cache_expiration']);
      }
    }
  }

  /**
   * Implements DrupalCacheInterface::set().
   */
  public function set($cid, $data, $expire = CACHE_PERMANENT) {
    // When setting cache items, clean up old session data in case it is stale.
    $gc_frequency = variable_get('cache_garbage_collection_frequency', CACHE_GARBAGE_COLLECTION_FREQUENCY);
    if (!empty($gc_frequency)) {
      $this->cleanSession();
    }

    $fields = array(
      'serialized' => 0,
      'created' => REQUEST_TIME,
      'expire' => $expire,
    );
    if (!is_string($data)) {
      $fields['data'] = serialize($data);
      $fields['serialized'] = 1;
    }
    else {
      $fields['data'] = $data;
      $fields['serialized'] = 0;
    }

    try {
      // Build query.
      $escaped_cid = apdqc_escape_string($cid);
      $escaped_data = apdqc_escape_string($fields['data']);
      $query = Database::getConnection()->prefixTables("INSERT INTO {" . db_escape_table($this->bin) . "}");
      $query .= " (cid, serialized, created, expire, data) VALUES ('$escaped_cid', '{$fields['serialized']}', '{$fields['created']}', '{$fields['expire']}', '$escaped_data')";
      $query .= " ON DUPLICATE KEY UPDATE serialized = '{$fields['serialized']}', created = '{$fields['created']}', expire = '{$fields['expire']}', data = '$escaped_data'";

      // Run query.
      $result = apdqc_query(array($this->bin), array($cid), $query, array('async' => TRUE));
      if (is_string($result) && $result === 'NO DB') {
        return parent::set($cid, $data, $expire);
      }
    }
    catch (Exception $e) {
      // The database may not be available, so we'll ignore cache_set requests.
    }
  }

  /**
   * Implements DrupalCacheInterface::clear().
   *
   * Here, we ensure that cron only runs cache garbage collection at a
   * configurable frequency, defaulting to 24 hours.
   */
  public function clear($cid = NULL, $wildcard = FALSE) {
    if (variable_get('apdqc_call_hook_on_clear', APDQC_CALL_HOOK_ON_CLEAR)) {
      $apdqc_cache_clear_alter = module_implements('apdqc_cache_clear_alter');
      if (!empty($apdqc_cache_clear_alter)) {
        $caller = $this->getCaller();
        // The bin variable is not alterable; use a copy.
        $bin = $this->bin;
        // Call hook_apdqc_cache_clear_alter().
        drupal_alter('apdqc_cache_clear', $cid, $wildcard, $bin, $caller);
      }
    }

    // Use default core logic for this cache clear if inside of a transaction.
    if (Database::getConnection()->inTransaction()) {
      // Do not use any prefectched data.
      drupal_static_reset('apdqc_async_data');
      $do_not_use_async_data = &drupal_static('apdqc_async_data_do_not_use_async');
      $do_not_use_async_data = TRUE;
      $do_not_use_async_data = &drupal_static('apdqc_run_prefetch_array');
      $do_not_use_async_data = TRUE;
      $output = parent::clear($cid, $wildcard);
      $this->callCacheClearHooks($cid, $wildcard);
      return $output;
    }

    $gc_frequency = variable_get('cache_garbage_collection_frequency', CACHE_GARBAGE_COLLECTION_FREQUENCY);
    $cids = array($cid);
    if ($wildcard || is_null($cid)) {
      $cids = array('*');
    }

    if (!empty($gc_frequency) && empty($cid)) {
      // Use backtrace to check that the clear came from system_cron.
      $backtrace = debug_backtrace();
      if ($backtrace[2]['function'] == 'system_cron') {
        $cache_lifetime = variable_get('cache_lifetime', 0);
        $name = 'cache_garbage_collect_' . $this->bin;
        $window = max($cache_lifetime, $gc_frequency);
        if (flood_is_allowed($name, 1, $window, 'cron')) {
          $this->garbageCollection();
          flood_register_event($name, $window, 'cron');
        }
      }
      // Otherwise, clear cache as usual.
      else {
        $this->garbageCollection();
      }
      $this->callCacheClearHooks($cid, $wildcard);
      return;
    }

    if (is_null($cid)) {
      // Build query.
      $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");

      if (variable_get('cache_lifetime', 0)) {
        // We store the time in the current user's session. We then simulate
        // that the cache was flushed for this user by not returning cached
        // data that was cached before the timestamp.
        $_SESSION['cache_expiration'][$this->bin] = REQUEST_TIME;

        $cache_flush = variable_get('cache_flush_' . $this->bin, 0);
        if ($cache_flush == 0) {
          // This is the first request to clear the cache, start a timer.
          variable_set('cache_flush_' . $this->bin, REQUEST_TIME);
        }
        elseif (REQUEST_TIME > ($cache_flush + variable_get('cache_lifetime', 0))) {
          // Clear the cache for everyone, cache_lifetime seconds have
          // passed since the first request to clear the cache.
          $query .= "WHERE (expire <> " . CACHE_PERMANENT . " AND expire < " . REQUEST_TIME . ")";
          $result = apdqc_query(array($this->bin), $cids, $query, array('async' => TRUE));
          if (is_string($result) && $result === 'NO DB') {
            // Use core connection if the additional connection to mysql fails.
            $output = parent::clear($cid, $wildcard);
            $this->callCacheClearHooks($cid, $wildcard);
            return $output;
          }
          variable_set('cache_flush_' . $this->bin, 0);
        }
      }
      else {
        // No minimum cache lifetime, flush all temporary cache entries now.
        $query .= "WHERE (expire <> " . CACHE_PERMANENT . " AND expire < " . REQUEST_TIME . ")";
        $result = apdqc_query(array($this->bin), $cids, $query, array('async' => TRUE));
        if (is_string($result) && $result === 'NO DB') {
          // Use core connection if an additional connection to mysql fails.
          $output = parent::clear($cid, $wildcard);
          $this->callCacheClearHooks($cid, $wildcard);
          return $output;
        }
      }
    }
    else {
      if ($wildcard) {
        if ($cid == '*') {
          // Check if $this->bin is a cache table before truncating. Other
          // cache_clear_all() operations throw a PDO error in this situation,
          // so we don't need to verify them first. This ensures that non-cache
          // tables cannot be truncated accidentally.
          if ($this->isValidBin()) {
            apdqc_truncate_table($this->bin);
          }
          else {
            throw new Exception(t('Invalid or missing cache bin specified: %bin', array('%bin' => $this->bin)));
          }
        }
        else {
          // Build query.
          $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");
          db_delete($this->bin)->condition('cid', db_like($cid) . '%', 'LIKE')->execute();
          $escaped_cid = apdqc_escape_string($cid);
          $query .= " WHERE cid LIKE '$escaped_cid%'";
          // Run an async query.
          $result = apdqc_query(array($this->bin), $cids, $query, array('async' => TRUE));
          if (is_string($result) && $result === 'NO DB') {
            // Use core connection if an additional connection to mysql fails.
            $output = parent::clear($cid, $wildcard);
            $this->callCacheClearHooks($cid, $wildcard);
            return $output;
          }
        }
      }
      elseif (is_array($cid)) {
        // Delete in chunks when a large array is passed.
        $chunks = array_chunk($cid, 2000);
        $last = array_pop($chunks);
        $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");
        foreach ($chunks as $cids) {
          $escaped_cids = array();
          foreach ($cids as $id) {
            $escaped_cids[] = apdqc_escape_string($id);
          }
          $escaped_cids = "'" . implode("', '", $escaped_cids) . "'";
          // Run query.
          $result = apdqc_query(array($this->bin), $cids, $query . " WHERE cid IN ({$escaped_cids})");
          if (is_string($result) && $result === 'NO DB') {
            // Use core connection if an additional connection to mysql fails.
            $output = parent::clear($cid, $wildcard);
            $this->callCacheClearHooks($cid, $wildcard);
            return $output;
          }
        }
        $escaped_cids = array();
        foreach ($last as $id) {
          $escaped_cids[] = apdqc_escape_string($id);
        }
        $escaped_cids = "'" . implode("', '", $escaped_cids) . "'";

        // Run last one as an async query.
        $result = apdqc_query(array($this->bin), $last, $query . " WHERE cid IN ({$escaped_cids})", array('async' => TRUE));
        if (is_string($result) && $result === 'NO DB') {
          // Use core connection if an additional connection to mysql fails.
          $output = parent::clear($cid, $wildcard);
          $this->callCacheClearHooks($cid, $wildcard);
          return $output;
        }
      }
      else {
        $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($this->bin) . "} ");
        $result = apdqc_query(array($this->bin), $cids, $query . " WHERE cid = '" . apdqc_escape_string($cid) . "'", array('async' => TRUE));
        if (is_string($result) && $result === 'NO DB') {
          // Use core connection if an additional connection to mysql fails.
          $output = parent::clear($cid, $wildcard);
          $this->callCacheClearHooks($cid, $wildcard);
          return $output;
        }
      }
    }
    $this->callCacheClearHooks($cid, $wildcard);
  }

  /**
   * Implements DrupalCacheInterface::isEmpty().
   */
  public function isEmpty() {
    $this->garbageCollection();

    $real_table_name = Database::getConnection()->prefixTables("{" . db_escape_table($this->bin) . "}");
    $result = apdqc_query(array($this->bin), array(), "SELECT TRUE FROM $real_table_name LIMIT 1");
    if (is_string($result) && $result === 'NO DB') {
      return parent::isEmpty();
    }

    if (!empty($result) && ($result instanceof mysqli_result)) {
      $empty_table = $result->fetch_row();
    }
    if (empty($result) || empty($empty_table)) {
      return FALSE;
    }
    return TRUE;
  }

  /**
   * Checks if $this->bin represents a valid cache table.
   *
   * This check is required to ensure that non-cache tables are not truncated
   * accidentally when calling cache_clear_all().
   *
   * @see https://www.drupal.org/node/2421253
   *
   * @return bool
   *   True if this is a valid bin; false if not.
   */
  public function isValidBin() {
    return parent::isValidBin();
  }

  /**
   * Allow for 3rd party modules to react to cache clear calls.
   *
   * @param string $cid
   *   Cache ID.
   * @param bool $wildcard
   *   If TRUE then anything after the CID is a match.
   */
  public function callCacheClearHooks($cid, $wildcard) {
    if (!variable_get('apdqc_call_hook_on_clear', APDQC_CALL_HOOK_ON_CLEAR)) {
      return;
    }
    $apdqc_cache_clear = module_implements('apdqc_cache_clear');
    if (empty($apdqc_cache_clear)) {
      // Bail out if no hooks will be called.
      return;
    }
    $caller = $this->getCaller();
    // Call hook_apdqc_cache_clear().
    module_invoke_all('apdqc_cache_clear', $cid, $wildcard, $this->bin, $caller);
  }

  /**
   * Get the last 3 items from debug_backtrace.
   *
   * @return array
   *   An array of items from debug_backtrace.
   */
  public function getCaller() {
    $bt = debug_backtrace();
    $caller = array();
    foreach ($bt as $key => $call) {
      if (!empty($call['class']) && $call['class'] == 'APDQCache') {
        continue;
      }
      if (empty($call['function']) || $call['function'] == 'cache_clear_all') {
        continue;
      }
      // Get this and the next 2 levels from the backtrace.
      $caller[$key] = $call;
      if (isset($bt[$key + 1])) {
        $caller[$key + 1] = $bt[$key + 1];
        if (isset($bt[$key + 2])) {
          $caller[$key + 2] = $bt[$key + 2];
        }
      }
      break;
    }
    return $caller;
  }

}
