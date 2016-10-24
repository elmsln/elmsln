<?php
/**
 * @file
 * APDQC Database interface code for MySQL database servers.
 */

/**
 * Output a lot of extra info in the devel output.
 */
if (!defined('APDQC_VERBOSE_DEVEL_OUTPUT')) {
  define('APDQC_VERBOSE_DEVEL_OUTPUT', TRUE);
}

/**
 * Max number of connections a thread can use.
 */
if (!defined('APDQC_MAX_CONNECTIONS_PER_THREAD')) {
  define('APDQC_MAX_CONNECTIONS_PER_THREAD', 10);
}

/**
 * Max number of connections a thread can use before mysql max is checked.
 */
if (!defined('APDQC_MAX_CONNECTIONS_BEFORE_CHECK')) {
  define('APDQC_MAX_CONNECTIONS_BEFORE_CHECK', 5);
}

/**
 * Used to get & parse async cached data.
 *
 * @param mixed $mysqli_result
 *   Empty or an instance of mysqli_result.
 * @param string $table
 *   Table name of the cache bin.
 * @param array $cids
 *   Array of cache ids that you're looking for.
 *
 * @return mixed
 *   The cached data if found.
 */
function apdqc_async_data($mysqli_result = FALSE, $table = FALSE, $cids = array(), $log = TRUE) {
  // Get database query logger.
  if (!empty($log) && variable_get('devel_query_display', 0) && variable_get('apdqc_verbose_devel_output', APDQC_VERBOSE_DEVEL_OUTPUT)) {
    $logger = Database::getConnection()->getLogger();
  }

  // Start timer if DB logger is enabled.
  if (!empty($logger)) {
    $query_start = microtime(TRUE);
  }

  // Use the advanced drupal_static() pattern, since this is called very often.
  static $local_storage;
  if (!isset($local_storage)) {
    $local_storage = &drupal_static('apdqc_async_data');
  }
  static $get_count;
  static $use_async_data;
  if (!isset($use_async_data)) {
    $do_not_use_async_data = &drupal_static('apdqc_async_data_do_not_use_async', array());
  }
  if (is_array($table)) {
    foreach ($table as $t) {
      if (is_array($do_not_use_async_data) && array_key_exists($t, $do_not_use_async_data) && !empty($do_not_use_async_data[$t])) {
        return array();
      }
    }
  }
  else {
    if (is_array($do_not_use_async_data) && array_key_exists($table, $do_not_use_async_data) && !empty($do_not_use_async_data[$table])) {
      return array();
    }
  }

  $output = array();
  if (!empty($mysqli_result) && ($mysqli_result instanceof mysqli_result)) {
    $rows = $mysqli_result->fetch_all(MYSQLI_ASSOC);
    if (!is_array($cids) && !isset($cids['*'])) {
      $cids = array_flip($cids);
    }
    foreach ($rows as $row) {
      $local_storage[$row['bin']][$row['cid']] = $row;
      unset($cids[$row['cid']]);
    }

    // Save cache misses. This needs to be improved.
    if (!empty($cids) && !isset($cids['*'])) {
      if (!is_array($cids)) {
        $cids = array_flip($cids);
      }
      foreach ($cids as $key => $cid) {
        if (strpos($cid, '%') !== FALSE) {
          unset($cids[$key]);
        }
      }
      if (!empty($cids)) {
        foreach ($cids as $cid) {
          foreach ($table as $bin) {
            if (!isset($local_storage[$bin][$cid])) {
              $local_storage[$bin][$cid] = FALSE;
            }
          }
        }
      }
    }
    $logger = FALSE;
  }
  elseif (!empty($table) && !empty($cids) && !empty($local_storage) && is_array($local_storage)) {
    if (!isset($get_count)) {
      $get_count = 0;
    }
    ++$get_count;
    // This is the first run.
    // No session cookie.
    // The cache is enabled.
    // This page is cacheable.
    if ($get_count == 1
      && !isset($_COOKIE[session_name()])
      && variable_get('cache')
      && drupal_page_is_cacheable()
      ) {
      // Check if blocked_ips var is not an array. If not, check if the
      // blocked_ips table is empty. If empty set the blocked_ips variable to an
      // empty array.
      $blocked_ips = variable_get('blocked_ips');
      if (!isset($blocked_ips) || !is_array($blocked_ips)) {
        // If the blocked_ips table is empty set the blocked_ips variable to
        // an empty array.
        $result = apdqc_query(array('blocked_ips'), array(), "SELECT 1 FROM " . apdqc_fast_prefix_tables('{' . apdqc_fast_escape_table('blocked_ips') . '}') . " LIMIT 1", array('log' => FALSE));
        if (!empty($result) && ($result instanceof mysqli_result)) {
          $blocked_ips = $result->fetch_row();
        }
        if (empty($result) || empty($blocked_ips)) {
          $GLOBALS['conf']['blocked_ips'] = array();
        }
      }
      // Prefetch the page cache.
      if (variable_get('cache_bootstrap_prefetch', CACHE_BOOTSTRAP_PREFETCH)) {
        if (apdqc_get_bin_class_name('cache_page') === 'APDQCache') {
          // Add in the page cache.
          $cid = apdqc_escape_string($GLOBALS['base_root'] . request_uri(), 'cache_page');
          $table_keys_cache_prefetch['cache_page'][] = $cid;

          // Run async query.
          apdqc_run_prefetch_array($table_keys_cache_prefetch, TRUE, FALSE);
        }
      }
    }
    if (is_string($table) && isset($local_storage[$table])) {
      foreach ($cids as $cid) {
        if (isset($local_storage[$table][$cid])) {
          $output[$cid] = $local_storage[$table][$cid];
          unset($output[$cid]['bin']);
        }
      }
    }
    if (empty($output)) {
      if (is_string($table)) {
        $new_data = apdqc_get_db_object(array($table), $cids, array('reap' => TRUE));
      }
      else {
        $new_data = apdqc_get_db_object($table, $cids, array('reap' => TRUE));
      }
      if ($new_data) {
        $output = apdqc_async_data(FALSE, $table, $cids, FALSE);
      }
    }
  }

  // Stop timer & write to the log if DB logger is enabled.
  if (!empty($logger) && is_object($logger)) {
    $query_end = microtime(TRUE);
    $data = '';
    if (!empty($output)) {
      $hits = 0;
      $empty = 0;
      foreach ($output as $key => $value) {
        if ($value === FALSE) {
          $empty++;
        }
        else {
          $hits++;
        }
      }
      if (!empty($hits)) {
        $data .= "Prefetch: Hit $hits times. ";
      }
      if (!empty($empty)) {
        $data .= "Prefetch: empty hit $empty times. ";
      }
    }
    if (empty($data) && !empty($cids)) {
      $data .= "Prefetch: Miss. ";
    }
    $data .= ' ' . implode(', ', $cids);

    $data = trim($data);
    if (!empty($data)) {
      require_once 'apdqc.log.inc';
      $statement = new ApdqcFakeDatabaseStatement($data);
      $logger->log($statement, array(), $query_end - $query_start);
    }
  }

  return $output;
}

/**
 * Return a mysqli object that is ready to be used.
 *
 * @param array $tables
 *   An array of table names.
 * @param array $cids
 *   An array of cache IDs.
 * @param array $options
 *   An array of options controlling this function.
 *   reap: Wait for all async queries to finish.
 *   fast_get: Skip most checks and just return a mysqli object.
 *   async: If TRUE then this connection is being used for an async query.
 *
 * @return mysqli
 *   returns a mysqli object on success or FALSE on failure.
 */
function apdqc_get_db_object(array $tables = array(), array $cids = array(), array $options = array()) {
  $options += array(
    'reap' => FALSE,
    'fast_get' => FALSE,
    'async' => TRUE,
  );

  // Bail out if not mysql that is async capable.
  $mysqli = FALSE;
  if (!function_exists('mysqli_init')
    || !defined('MYSQLI_ASYNC')
    ) {
    return $mysqli;
  }

  // Use the advanced drupal_static() pattern for $db_info.
  static $db_info;
  if (!isset($db_info)) {
    $db_info = &drupal_static(__FUNCTION__);

    // 'var' stores variables about the mysql database.
    if (!isset($db_info['var'])) {
      $db_info['var'] = array();
    }
    $db_info['var'] += array(
      'max_connections' => 90,
      'wait_timeout' => 90,
      'connect_timeout' => 2,
      'innodb_lock_wait_timeout' => 10,
      // 33554432 = 32MB.
      'max_allowed_packet' => 33554432,
    );

    // 'connection' stores the info needed to make a new connection to mysql.
    if (!isset($db_info['connection'])) {
      // Use default connection info.
      if (class_exists('Database')) {
        $connection_info = Database::getConnectionInfo();
        $db_info['connection'] = reset($connection_info);
      }
      else {
        $db_info['connection'] = $GLOBALS['databases']['default']['default'];
      }
      if (empty($db_info['connection']['port'])) {
        $db_info['connection']['port'] = NULL;
      }
      else {
        $db_info['connection']['port'] = (int) $db_info['connection']['port'];
      }
      if (empty($db_info['connection']['unix_socket'])) {
        $db_info['connection']['unix_socket'] = NULL;
      }
      if (empty($db_info['connection']['password'])) {
        $db_info['connection']['password'] = NULL;
      }

      $mysql_db_type = &drupal_static('apdqc_mysql_db_type');
      if (!isset($mysql_db_type)) {
        // Default to MySQL.
        $mysql_db_type = 'MySQL';
        if (isset($GLOBALS['databases']['default']['default']['mysql_db_type'])) {
          $mysql_db_type = $GLOBALS['databases']['default']['default']['mysql_db_type'];
        }
      }

    }

    // 'pool' stores a collection of open mysql connections.
    if (!isset($db_info['pool'])) {
      $db_info['pool'] = array();
    }
  }

  if (!empty($options['fast_get']) && !empty($db_info['pool'])) {
    $values = reset($db_info['pool']);
    return $values[0];
  }

  // Make sure a table/cid pair is used by the same connection in order to avoid
  // record level deadlocks with async queries.
  if (!empty($db_info['pool']) && !empty($tables) && !empty($cids)) {
    $match = FALSE;
    $new_data = FALSE;
    foreach ($db_info['pool'] as $key => $values) {
      // Skip if not an async query.
      if (empty($values[3])) {
        continue;
      }

      // Match the table.
      $intersect = array_intersect($tables, $values[1]);
      if (!empty($intersect)) {
        $intersect = array();
        // Match the cache id.
        $done = FALSE;
        if (isset($cids['*'])) {
          // Whole table query.
          $intersect = array(TRUE);
          $done = TRUE;
        }
        elseif (isset($values[2]['*'])) {
          // Whole table query.
          $not_intersect = array_intersect($values[2]['*'], $cids);
          $missing_cids = array_diff($not_intersect, $values[2]['*']);
          if (!empty($missing_cids)) {
            $intersect = array(TRUE);
          }
          $done = TRUE;
        }
        if (!$done) {
          // Check for like queries.
          foreach ($values[2] as $old_cid) {
            $like_pos = strpos($old_cid, '%');
            if ($like_pos !== FALSE) {
              foreach ($cids as $new_cid) {
                if (substr($old_cid, 0, $like_pos) === substr($new_cid, 0, $like_pos)) {
                  $intersect = array(TRUE);
                  $done = TRUE;
                  break 2;
                }
              }
            }
          }
        }
        if (!$done) {
          // Match cids.
          $intersect = array_intersect($cids, $values[2]);
        }

        // If the cache id is matched.
        if (!empty($intersect)) {
          // Wait for the query to finish.
          apdqc_reap_async_query($db_info, $values[0], $cids, $tables);
          $new_data = TRUE;
          $match = $values[0];
          // Report that the connection is ready.
          $db_info['pool'][$key][3] = FALSE;
        }
      }
    }
    if (!empty($options['reap'])) {
      return $new_data;
    }
    if (!empty($match)) {
      apdqc_mysqli_ping($match, $db_info, $tables, $cids, $options['async']);
      return $match;
    }
  }

  // Try to reuse an old connection.
  if (!empty($db_info['pool'])) {
    $mysqli_pool = array();
    foreach ($db_info['pool'] as $values) {
      $mysqli_pool[] = $values[0];
      // If query was not async, use it.
      if (empty($values[3])) {
        $mysqli = $values[0];
        apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async']);
        return $mysqli;
      }
    }
    $links = $errors = $reject = $mysqli_pool;
    $ready = @mysqli_poll($links, $errors, $reject, 0, 1);
    if (!empty($reject)) {
      // A non async connection is ready; use the first one.
      $mysqli = reset($reject);
      apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async']);
      return $mysqli;
    }
    if (!empty($links)) {
      // An async connection is ready; use the ready one.
      if (isset($links[$ready - 1])) {
        $mysqli = $links[$ready - 1];
      }
      else {
        $mysqli = reset($links);
      }
      apdqc_reap_async_query($db_info, $mysqli, $cids, $tables);
      apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async']);
      return $mysqli;
    }

    // All current connections are in use.
    if (count($db_info['pool']) < variable_get('apdqc_max_connections_per_thread', APDQC_MAX_CONNECTIONS_PER_THREAD)) {
      // Create a new DB connection.
      if (count($db_info['pool']) < variable_get('apdqc_max_connections_before_check', APDQC_MAX_CONNECTIONS_BEFORE_CHECK)) {
        $mysqli = apdqc_mysqli_new_connection($db_info);
      }
      else {
        $mysqli = apdqc_mysqli_new_connection($db_info, TRUE);
      }
      if (!empty($mysqli)) {
        $db_info['pool'][$mysqli->thread_id] = array(
          $mysqli,
          $tables,
          $cids,
          $options['async'],
        );
      }
      return $mysqli;
    }
    else {
      // Wait for a db connection to be ready.
      $ready = FALSE;
      while (!$ready) {
        $mysqli_pool = array();
        foreach ($db_info['pool'] as $values) {
          $mysqli_pool[] = $values[0];
        }
        $links = $errors = $reject = $mysqli_pool;
        $ready = @mysqli_poll($links, $errors, $reject, 0, 5000);
        if (!$ready && !empty($reject)) {
          $ready = TRUE;
        }
      }
      if (!empty($reject)) {
        // A non async connection is ready; use the first one.
        $mysqli = reset($reject);
        apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async']);
        return $mysqli;
      }
      if (!empty($links)) {
        // An async connection is ready; use the ready one.
        if (isset($links[$ready - 1])) {
          $mysqli = $links[$ready - 1];
        }
        else {
          $mysqli = reset($links);
        }
        apdqc_reap_async_query($db_info, $mysqli, $cids, $tables);
        apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async']);
        return $mysqli;
      }
    }
  }

  if (empty($db_info['pool'])) {
    $mysqli = apdqc_mysqli_new_connection($db_info);
    if (!empty($mysqli)) {
      $db_info['pool'][$mysqli->thread_id] = array(
        $mysqli,
        $tables,
        $cids,
        $options['async'],
      );
    }
  }
  return $mysqli;
}

/**
 * Create a new MySQLi connection.
 *
 * @param array $db_info
 *   Static var from 'apdqc_get_db_object'.
 * @param mysqli $mysqli
 *   mysqlnd connection object. Passed by reference.
 * @param array $new_cids
 *   An array of cache IDs.
 * @param array $new_tables
 *   An array of table names.
 */
function apdqc_reap_async_query(array $db_info, mysqli &$mysqli, array $new_cids = array(), array $new_tables = array()) {
  // Get database query logger.
  if (variable_get('devel_query_display', 0) && variable_get('apdqc_verbose_devel_output', APDQC_VERBOSE_DEVEL_OUTPUT)) {
    $logger = Database::getConnection()->getLogger();
    // Start timer if DB logger is enabled.
    if (!empty($logger)) {
      $query_start = microtime(TRUE);
    }
  }

  // Wait for the query to finish.
  $old_tables = $db_info['pool'][$mysqli->thread_id][1];
  $old_cids = $db_info['pool'][$mysqli->thread_id][2];
  $query_result = @$mysqli->reap_async_query();
  if (!empty($query_result)) {
    apdqc_async_data($query_result, $old_tables, $old_cids);
  }

  // Stop timer & write to the log if DB logger is enabled.
  if (!empty($logger) && is_object($logger)) {
    $logit = FALSE;
    $query_end = microtime(TRUE);
    $data = 'Waiting for ASYNC READ to finish. ';
    if (isset($old_cids['*'])) {
      $old_cids = $old_cids['*'];
    }
    $intersect = array_intersect($old_tables, $new_tables);
    $extra_data = '';
    if (!empty($intersect)) {
      $extra_data .= ' TABLE INTERSECTION on the ' . implode(', ', $intersect) . ' table(s).';
      $extra_data .= ' OLD TABLES ' . implode(', ', $old_tables) . '.';
      $logit = TRUE;
    }
    $intersect = array_intersect($old_cids, $new_cids);
    if (!empty($intersect)) {
      $extra_data .= ' CID INTERSECTION on these cids: ' . implode(', ', $intersect) . '.';
      $extra_data .= ' OLD CID ' . implode(', ', $old_cids) . '.';
      $logit = TRUE;
    }

    $extra_data .= ' Next query lists what closed this query out; a prefetch hit is good.';

    $data .= $extra_data;
    $data = trim($data);

    $extra_data = 'thread_id:' . $mysqli->thread_id . ' ';
    if ($logit) {
      require_once 'apdqc.log.inc';
      $statement = new ApdqcFakeDatabaseStatement($data, $extra_data);
      $logger->log($statement, array(), $query_end - $query_start);
    }
  }
}

/**
 * Create a new MySQLi connection.
 *
 * @param array $db_info
 *   Static var from 'apdqc_get_db_object'.
 *
 * @return mysqli
 *   Returns a mysqli object on success or FALSE on failure.
 */
function apdqc_mysqli_new_connection(array $db_info, $check_max = FALSE) {
  // Create new MySQL connection.
  $mysqli = new mysqli();
  $mysqli->options(MYSQLI_OPT_CONNECT_TIMEOUT, $db_info['var']['connect_timeout']);
  if (isset($db_info['connection']['pdo'])) {
    $pdo = $db_info['connection']['pdo'];
    $key = isset($pdo[PDO::MYSQL_ATTR_SSL_KEY]) ? $pdo[PDO::MYSQL_ATTR_SSL_KEY] : NULL;
    $cert = isset($pdo[PDO::MYSQL_ATTR_SSL_CERT]) ? $pdo[PDO::MYSQL_ATTR_SSL_CERT] : NULL;
    $ca = isset($pdo[PDO::MYSQL_ATTR_SSL_CA]) ? $pdo[PDO::MYSQL_ATTR_SSL_CA] : NULL;
    $capath = isset($pdo[PDO::MYSQL_ATTR_SSL_CAPATH]) ? $pdo[PDO::MYSQL_ATTR_SSL_CAPATH] : NULL;
    $cipher = isset($pdo[PDO::MYSQL_ATTR_SSL_CIPHER]) ? $pdo[PDO::MYSQL_ATTR_SSL_CIPHER] : NULL;
  }
  if (!empty($key) && !empty($cert) && !empty($ca)) {
    $mysqli->ssl_set($key, $cert, $ca, $capath, $cipher);
    @$mysqli->real_connect($db_info['connection']['host'], $db_info['connection']['username'], $db_info['connection']['password'], $db_info['connection']['database'], $db_info['connection']['port'], $db_info['connection']['unix_socket'], MYSQLI_CLIENT_SSL);
  }
  else {
    @$mysqli->real_connect($db_info['connection']['host'], $db_info['connection']['username'], $db_info['connection']['password'], $db_info['connection']['database'], $db_info['connection']['port'], $db_info['connection']['unix_socket']);
  }

  if (empty($mysqli) || !empty($mysqli->connect_errno) || empty($mysqli->host_info)) {
    // Bail out if the DB didn't connect.
    return FALSE;
  }
  if (!empty($mysqli)) {
    // Break connection if we are within 80% of the max connections for MySQL.
    if ($check_max) {
      // @ignore sql_curly
      $max_connections_query = "SELECT IF (FLOOR(LEAST(" . $db_info['var']['max_connections'] . ", @@global.max_connections * 0.8)) > COUNT(ID), 1, 0) AS Keep_Connection FROM information_schema.processlist";
      $result = $mysqli->query($max_connections_query)->fetch_row();
      if ($result[0] == 0) {
        // Close the connection and return FALSE.
        $mysqli->close();
        unset($mysqli);
        $mysqli = FALSE;
        return $mysqli;
      }
    }

    // Get connection ready for usage.
    $mysqli->set_charset('utf8');

    // Setup MySQL.
    $init_query = "
      SET sql_mode = 'ANSI,STRICT_TRANS_TABLES,STRICT_ALL_TABLES,NO_ZERO_IN_DATE,NO_ZERO_DATE,ERROR_FOR_DIVISION_BY_ZERO,NO_AUTO_CREATE_USER',
      SESSION group_concat_max_len = 65535,
      SESSION tx_isolation='READ-COMMITTED',
      SESSION wait_timeout = LEAST(@@global.wait_timeout, {$db_info['var']['wait_timeout']}),
      SESSION join_buffer_size = 131072
    ";
    // Set innodb_lock_wait_timeout if MySQL 5.5 or higher.
    if ($mysqli->server_version >= 50500) {
      $init_query .= ", SESSION innodb_lock_wait_timeout = " . $db_info['var']['innodb_lock_wait_timeout'];
    }
    if (!empty($db_info['connection']['mysql_db_type']) && stripos($db_info['connection']['mysql_db_type'], 'mariadb') !== FALSE) {
      $init_query .= ", SESSION mrr_buffer_size = 262144";
    }
    else {
      $init_query .= ", SESSION read_rnd_buffer_size = 262144";
    }
    $mysqli->query($init_query);
  }
  return $mysqli;
}

/**
 * Reconnect to the MySQL database if the connection has been lost.
 *
 * Will also record the table and cache ID used.
 *
 * @param mysqli $mysqli
 *   mysqlnd connection object. Passed by reference.
 * @param array $db_info
 *   static var from 'apdqc_get_db_object'. Passed by reference.
 * @param array $tables
 *   An array of table names.
 * @param array $cids
 *   An array of cache IDs.
 * @param bool $async
 *   If TRUE then this connection is being used for an async query.
 * @param bool $force_check
 *   If TRUE then this connection will be checked.
 */
function apdqc_mysqli_ping(mysqli &$mysqli, array &$db_info, array $tables, array $cids, $async, $force_check = FALSE) {
  $timeout_check = max(3, $db_info['var']['wait_timeout'] - 5);
  $runtime = microtime(TRUE) - REQUEST_TIME;
  if ($runtime > $timeout_check || $force_check) {
    if (empty($mysqli) || !@$mysqli->ping()) {
      unset($db_info['pool'][$mysqli->thread_id]);
      $mysqli = apdqc_mysqli_new_connection($db_info, TRUE);
      if (empty($mysqli) || !@$mysqli->ping()) {
        $mysqli = FALSE;
      }
    }
  }
  if (!empty($mysqli)) {
    $db_info['pool'][$mysqli->thread_id] = array(
      $mysqli,
      $tables,
      $cids,
      $async,
    );
  }
}

/**
 * Prepare input for use in a database query, preventing SQL injection attacks.
 *
 * @param string $string
 *   String that needs to be sanitized.
 *
 * @return string
 *   Sanitized version of the input string.
 */
function apdqc_escape_string($string) {
  static $mysqli;
  if (empty($mysqli) || !($mysqli instanceof mysqli)) {
    $mysqli = apdqc_get_db_object(array(), array(), array('fast_get' => TRUE));
  }
  if (empty($mysqli)) {
    unset($mysqli);
    return FALSE;
  }
  return $mysqli->real_escape_string($string);
}

/**
 * Runs a query in the database.
 *
 * @param array $tables
 *   Array of tables accessed in this query.
 * @param array $cids
 *   Array of cache ids used in this query.
 * @param string $query
 *   The query to run.
 * @param array $options
 *   Various options to control how this query is ran.
 *   async: TRUE to make query be asynchronous & non blocking.
 *   fetch_all: TRUE to return fetch_all(MYSQLI_ASSOC) on the query result.
 *   log: FALSE to not log this query inside of devel.
 *   get_affected_rows: TRUE returns the affected rows.
 *   get_mysqli: TRUE returns the $mysqli object.
 *
 * @return mixed
 *   Returns the string "NO DB" when it can't connect to the database.
 *   Returns an int when get_affected_rows is set to TRUE.
 *   Returns the mysqli object when get_mysqli is set to TRUE.
 *   Returns the result array when fetch_all is set to TRUE.
 *   Returns -1 when async is set to TRUE.
 */
function apdqc_query(array $tables, array $cids, $query, array $options = array()) {
  // Add in defaults.
  $options += array(
    'async' => FALSE,
    'fetch_all' => FALSE,
    'log' => TRUE,
    'get_affected_rows' => FALSE,
    'get_mysqli' => FALSE,
  );

  if (!empty($options['log']) && variable_get('devel_query_display', 0)) {
    $logger = Database::getConnection()->getLogger();
  }

  // Start timer if DB logger is enabled.
  if (!empty($logger)) {
    $query_start = microtime(TRUE);
  }

  $mysqli = apdqc_get_db_object($tables, $cids, $options);
  if (empty($mysqli)) {
    return "NO DB";
  }

  if (strpos($query, 'SELECT ') === 0) {
    // Get the mysql database type.
    static $mysql_db_type;
    if (!isset($mysql_db_type)) {
      $mysql_db_type = &drupal_static('apdqc_mysql_db_type');
      if (stripos($mysql_db_type, 'mariadb') !== FALSE) {
        static $version_alt;
        $version_alt = $mysqli->server_info;
        $pos_a = stripos($version_alt, 'mariadb') - 7;
        $pos_b = stripos($version_alt, '-');
        if ($pos_a !== FALSE && $pos_b !== FALSE && $pos_a > $pos_b) {
          $version_alt = substr($version_alt, $pos_b + 1, $pos_a);
        }
      }
    }

    // Use a SELECT statement timeout if this is MySQL 5.7.4 or higher.
    $alter_select = FALSE;
    if ($mysqli->server_version >= 50704 && $mysqli->server_version < 50708) {
      $alter_select = TRUE;
    }
    // Use a SELECT statement timeout if this is Percona 5.6.14 or higher.
    elseif ($mysqli->server_version >= 50614) {
      if (stripos($mysql_db_type, 'percona') !== FALSE) {
        $alter_select = TRUE;
      }
    }
    if ($alter_select) {
      $query = str_replace('SELECT ', 'SELECT MAX_STATEMENT_TIME=2000 ', $query);
    }
    else {
      if ($mysqli->server_version >= 50708) {
        $query = str_replace('SELECT ', 'SELECT /*+ MAX_EXECUTION_TIME(2000) */ ', $query);
      }
      elseif (stripos($mysql_db_type, 'mariadb') !== FALSE && version_compare($version_alt, '10.1.2', '>=')) {
        $query = str_replace('SELECT ', 'SET STATEMENT max_statement_time=2 FOR SELECT ', $query);
      }
    }
  }

  // Clear static cache on insert or delete & disable function for the rest of
  // this request.
  if (strpos($query, 'INSERT ') === 0 || strpos($query, 'DELETE ') === 0 || strpos($query, 'TRUNCATE ') === 0) {
    $apdqc_async_data = &drupal_static('apdqc_async_data');
    $do_not_use_async_data = &drupal_static('apdqc_async_data_do_not_use_async');
    $do_not_run_prefetch_array = &drupal_static('apdqc_run_prefetch_array');
    foreach ($tables as $table) {
      $apdqc_async_data[$table] = array();
      $do_not_use_async_data[$table] = TRUE;
      $do_not_run_prefetch_array[$table] = TRUE;
    }
  }

  // Catch mysql disconnect errors with our own error handler.
  drupal_static_reset('_apdqc_query_error_handler');
  set_error_handler('_apdqc_query_error_handler');

  // About to query the semaphore table, set tx_isolation to READ-UNCOMMITTED.
  if ($tables[0] == 'semaphore' || $tables[0] == 'sessions') {
    $mysqli->query("SET SESSION tx_isolation='READ-UNCOMMITTED'");
  }

  // Run query.
  if ($options['async']) {
    $results = $mysqli->query($query, MYSQLI_ASYNC);
  }
  else {
    $results = $mysqli->query($query);
  }

  // Recover if query failed.
  $apdqc_errormsg = &drupal_static('_apdqc_query_error_handler');
  if (!empty($apdqc_errormsg)) {
    // Restore the Drupal error handler.
    restore_error_handler();

    $db_info = &drupal_static('apdqc_get_db_object');
    // Check this connection.
    $mysqli = apdqc_mysqli_ping($mysqli, $db_info, $tables, $cids, $options['async'], TRUE);
    if (empty($mysqli)) {
      $mysqli = apdqc_get_db_object($tables, $cids, $options);
    }
    if (!empty($mysqli)) {
      // Run query again.
      if ($options['async']) {
        $results = $mysqli->query($query, MYSQLI_ASYNC);
      }
      else {
        $results = $mysqli->query($query);
      }
    }
    else {
      watchdog('apdqc', 'This query failed: @query', array('@query' => $query));
    }
  }
  // Restore the Drupal error handler.
  restore_error_handler();

  // Get affected_rows if requested to do so.
  if (!$options['async'] && $options['get_affected_rows']) {
    $results = $mysqli->affected_rows;
  }

  // Stop timer & write to the log if DB logger is enabled.
  if (!empty($logger)) {
    $query_end = microtime(TRUE);
    $affected_rows = $mysqli->affected_rows;
    $extra_data = '';
    if ($options['async']) {
      $extra_data .= 'ASYNC ';
    }
    else {
      if ($affected_rows == -1) {
        $extra_data .= 'ERROR ';
      }
      elseif (empty($affected_rows)) {
        $extra_data .= 'MISS ';
      }
      else {
        $extra_data .= 'HIT ';
      }
    }
    if (variable_get('apdqc_verbose_devel_output', APDQC_VERBOSE_DEVEL_OUTPUT) || !$options['async']) {
      $extra_data .= implode(', ', $tables) . ' Rows affected: ' . $affected_rows . ' Error code: ' . $mysqli->sqlstate . ' ';
      require_once 'apdqc.log.inc';
      $extra_data .= 'thread_id:' . $mysqli->thread_id . ' ';
      $statement = new ApdqcFakeDatabaseStatement($query, $extra_data);
      $logger->log($statement, array(), $query_end - $query_start);
    }
  }
  if ($options['get_mysqli']) {
    $return = $mysqli;
  }

  if (empty($return)) {
    if (!$options['get_affected_rows'] && $options['fetch_all']) {
      $result = array();
      if (!empty($results) && ($results instanceof mysqli_result)) {
        $result = $results->fetch_all(MYSQLI_ASSOC);
      }
      $return = $result;
    }
    else {
      $return = $results;
    }
  }
  // Done quering the semaphore table, set tx_isolation back to READ-COMMITTED.
  if ($tables[0] == 'semaphore' || $tables[0] == 'sessions') {
    $mysqli->query("SET SESSION tx_isolation='READ-COMMITTED'");
  }
  return $return;

}

/**
 * A temporary error handler which keeps track of the most recent error.
 */
function _apdqc_query_error_handler($errno, $errstr) {
  $apdqc_errormsg = &drupal_static(__FUNCTION__);
  $apdqc_errormsg = $errstr;
  return TRUE;
}

/**
 * Empties out a database table in a non metadata locking fashion.
 *
 * @param string $table
 *   Name of the table you wish to truncate.
 */
function apdqc_truncate_table($table) {
  // Make sure the $mysqli object is available.
  $mysqli = apdqc_get_db_object(array($table), array('*'));
  if (empty($mysqli)) {
    return db_truncate($table)->execute();
  }

  // TRUNCATE is not a transaction safe statement if the table being cleared was
  // used in any query inside of a transaction since it is a DDL statement which
  // results in a metadata lock. Always use the slower, but non locking
  // transactional, DELETE on the cache_field table.
  if (Database::getConnection()->inTransaction() || variable_get('cache_no_truncate', CACHE_NO_TRUNCATE) || $table === 'cache_field') {
    $query = Database::getConnection()->prefixTables("DELETE FROM {" . db_escape_table($table) . "}");
    $result = apdqc_query(array($table), array('*'), $query);
    if (is_string($result) && $result === 'NO DB') {
      return db_truncate($table)->execute();
    }
    return;
  }

  // No Op if table is empty.
  $real_table_name = Database::getConnection()->prefixTables("{" . db_escape_table($table) . "}");
  $results = $mysqli->query("SELECT 1 FROM $real_table_name LIMIT 1");
  if (!empty($results) && ($results instanceof mysqli_result)) {
    $empty_table = $results->fetch_row();
  }
  if (empty($results) || empty($empty_table)) {
    return;
  }
  // Renaming tables is a lot faster than truncate. Rename and then do an
  // async Truncate so we don't get stalled.
  // Make sure truncated table exists before trying to use it.
  $real_table_name_truncated = Database::getConnection()->prefixTables("{" . db_escape_table($table) . "__truncated_table}");

  // Remove any values from the *__truncated_table if needed.
  $results = $mysqli->query("SELECT 1 FROM $real_table_name_truncated LIMIT 1");
  if ($results === FALSE) {
    // Create truncated table if it does not exist.
    $mysqli->query("CREATE TABLE IF NOT EXISTS $real_table_name_truncated LIKE $real_table_name");
    // Set to empty since this table was just created.
    $db_row = NULL;
  }
  else {
    // mysqli_result::fetch_row returns NULL when there are no more rows.
    $db_row = $results->fetch_row();
  }
  if (!is_null($db_row)) {
    // Empty the truncated_table since it is not empty.
    $result = apdqc_query(array($real_table_name_truncated), array('*'), "TRUNCATE $real_table_name_truncated");
    if (is_string($result) && $result === 'NO DB') {
      return db_truncate($table)->execute();
    }
  }

  // Use rename so the truncate happens at the end of this request.
  $real_table_name_temp = Database::getConnection()->prefixTables("{" . db_escape_table($table) . "__temp_table}");
  $query = "
    RENAME TABLE $real_table_name TO $real_table_name_temp,
    $real_table_name_truncated TO $real_table_name,
    $real_table_name_temp TO $real_table_name_truncated
  ";
  $mysqli->query($query, MYSQLI_ASYNC);

  if (apdqc_kill_metadata_lock($mysqli->thread_id)) {
    // Use DELETE FROM syntax, as TRUNCATE is locking the database.
    $query = "DELETE FROM " . $real_table_name . "";
    $result = apdqc_query(array($table), array('*'), $query);
    if (is_string($result) && $result === 'NO DB') {
      return db_truncate($table)->execute();
    }
    // Return here as the table has been emptied.
    return;
  }

  // Run an async TRUNCATE.
  apdqc_query(array($real_table_name_truncated), array('*'), "TRUNCATE $real_table_name_truncated", array('async' => TRUE));
}

/**
 * Checks db processlist for metadata lock & kills query if waiting over 1s.
 *
 * @param string $thread_id
 *   Name thread to check for the metadata lock.
 *
 * @return bool
 *   TRUE if it did kill the query. FALSE if no killing was done.
 */
function apdqc_kill_metadata_lock($thread_id) {
  $lock_found = TRUE;
  while ($lock_found) {
    // Check for a Metadata lock.
    // @ignore sql_curly
    $result = db_query("SELECT * FROM information_schema.processlist WHERE ID = :pid AND STATE LIKE 'Waiting for table metadata lock' LIMIT 1", array(":pid" => $thread_id));
    foreach ($result as $record) {
      // Rename should not take over 1 second.
      if ($record->TIME >= 1) {
        // Kill query that is in a metadata lock state.
        db_query("KILL QUERY :pid", array(":pid" => $thread_id));
        return TRUE;
      }
      // Wait 250ms.
      usleep(250000);
      // Goto top of while loop.
      continue 2;
    }
    // Metadata lock cleared.
    $lock_found = FALSE;
  }
  return FALSE;
}

/**
 * Given a list of database fields; outputs a string for use in db queries.
 *
 * @param array $fields
 *   An array of database columns.
 *
 * @return string
 *   String for use in db queries.
 */
function apdqc_create_key_sql(array $fields) {
  $return = array();
  foreach ($fields as $field) {
    if (is_array($field)) {
      $return[] = '`' . $field[0] . '`(' . $field[1] . ')';
    }
    else {
      $return[] = '`' . $field . '`';
    }
  }
  return implode(', ', $return);
}
