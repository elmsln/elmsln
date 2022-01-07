<?php

/**
 * @file
 * Helper for https://www.drupal.org/node/2488180
 * Credit: joelpittet, stefan.r
 */

/**
 * Allows for converting all databases to another charset.
 */
class DrupalCharsetConverter {

  /**
   * Character set.
   * @var string
   */
  protected $charset = 'utf8mb4';

  /**
   * Collation.
   * @var string
   */
  protected $collation = 'utf8mb4_general_ci';

  /**
   * The current database connection for all actions.
   *
   * @var DatabaseConnection
   */
  protected $connection;

  public function __construct($charset = NULL, $collation = NULL) {
    if ($charset) {
      $this->charset = $charset;
    }
    if ($collation) {
      $this->collation = $collation;
    }
  }

  /**
   * Set the active database connection.
   *
   * @param DatabaseConnection $connection
   *   The database connection as retrieved by Database::getConnection().
   */
  public function setConnection(DatabaseConnection $connection) {
    $this->connection = $connection;
  }

  /**
   * Query the active connection, logging in verbose mode.
   *
   * The normal values are returned, use the connection directly if the return
   * value is needed.
   *
   * @param string $query
   *   The query to execute.
   * @param array $args
   *   An array of arguments for the prepared statement.
   *
   * @see DatabaseConnection::query()
   */
  public function query($query, array $args = array()) {
    $string = $this->connection->query($query, $args, array('return' => Database::RETURN_STATEMENT))->getQueryString();
    $quoted = array();
    foreach ($args as $key => $val) {
      $quoted[$key] = $this->connection->quote($val);
    }
    drush_log('Executed query: ' . strtr($string, $quoted) . ';');
  }

  /**
   * Convert the MySQL drupal databases character set and collation.
   *
   * @param array $databases
   *   The Drupal 7 database info array.
   */
  public function convert(array $databases) {
    $success = FALSE;
    foreach ($databases as $database_key => $database_values) {
      foreach ($database_values as $target => $database) {
        // Skip slave databases, multiple databases within a single target,
        // and any non-MySQL databases.
        if ($target === 'slave' || !isset($database['driver']) || strpos($database['driver'], 'mysql') !== 0) {
          continue;
        }

        drush_print('Target MySQL database: ' . $database['database'] . '@' . $database['host'] . ' (' . $database_key . ':' . $target  . ')' );
        // Connect to next database.
        $connection = Database::getConnection($target, $database_key);
        $this->setConnection($connection);
        // Check the database type is mysql.
        $db_type = $connection->databaseType();
        // Skip if not MySQL.
        if ($db_type !== 'mysql') {
          continue;
        }
        if ($this->charset == 'utf8mb4' && !$connection->utf8mb4IsSupported()) {
          drush_print('The ' . $database_key . ':' . $target . ' MySQL database does not support UTF8MB4! Ensure that the conditions listed in settings.php related to innodb_large_prefix, the server version, and the MySQL driver version are met. See https://www.drupal.org/node/2754539 for more information.');
          continue;
        }
        // For each database:
        $this->convertDatabase($database['database']);
        // For each table in the database.
        $this->convertTables();
        $success = TRUE;
        drush_print('Finished converting the ' . $database_key . ':' . $target . ' MySQL database!');
      }
    }

    return $success;
  }

  /**
   * @param string
   *   Database name.
   * @param string $charset
   *   (Optional) The character set.
   * @param string $collation
   *   (Optional) The collation.
   *
   * @return bool
   *   success|failure.
   */
  public function convertDatabase($database_name, $charset = NULL, $collation = NULL) {
    drush_print('Converting database: ' . $database_name);
    $sql = "ALTER DATABASE `" . $database_name . "` CHARACTER SET = :charset COLLATE = :collation;";
    return $this->query($sql, array(
      ':charset' => $charset ? $charset : $this->charset,
      ':collation' => $collation ? $collation : $this->collation,
    ));
  }

  /**
   * Converts all the tables defined by drupal_get_schema().
   *
   * @param string $charset
   *   (Optional) The character set.
   * @param string $collation
   *   (Optional) The collation.
   *
   * @return bool
   *   success|failure.
   */
  public function convertTables($charset = NULL, $collation = NULL) {
    // For each table:
    // Deal only with Drupal managed tables.
    $schema = drupal_get_schema();
    $table_names = array_keys($schema);

    if ($exclude = drush_get_option('exclude', '')) {
      $table_names = array_diff($table_names, explode(',', $exclude));
    }

    sort($table_names);
    foreach ($table_names as $table_name) {
      if (!$this->connection->schema()->tableExists($table_name)) {
        continue;
      }
      $this->convertTable($table_name, $charset, $collation);
    }
  }

  /**
   * Converts a table to a desired character set and collation.
   *
   * @param string $table_name
   *  The database table name.
   * @param string $charset
   *   (Optional) The character set.
   * @param string $collation
   *   (Optional) The collation.
   *
   * @return bool
   *   success|failure.
   */
  public function convertTable($table_name, $charset = NULL, $collation = NULL) {
    $this->query("ALTER TABLE {" . $table_name . "} ROW_FORMAT=DYNAMIC ENGINE=INNODB");
    $sql = "ALTER TABLE {" . $table_name . "} CHARACTER SET = :charset COLLATE = :collation";
    drush_print('Converting table: ' . $table_name);
    $result = $this->query($sql, array(
      ':charset' => $charset ? $charset : $this->charset,
      ':collation' => $collation ? $collation : $this->collation,
    ));
    $this->convertTableFields($table_name, $charset, $collation);
    $this->query("OPTIMIZE TABLE {" . $table_name . "}");
    return $result;
  }

  /**
   * Converts a table's field to a desired character set and collation.
   *
   * @param string $table_name
   *  The database table name.
   * @param string $charset
   *   (Optional) The character set.
   * @param string $collation
   *   (Optional) The collation.
   *
   * @return bool
   *   success|failure.
   */
  public function convertTableFields($table_name, $charset = NULL, $collation = NULL) {
    $results = $this->connection->query("SHOW FULL FIELDS FROM {" . $table_name . "}")->fetchAllAssoc('Field');
    $charset = $charset ? $charset : $this->charset;
    $collation = $collation ? $collation : $this->collation;
    foreach ($results as $row) {
      // Skip fields that don't have collation, as they are probably int or similar.
      // or if we are using that collation for this field already save a query
      // or is not binary.
      if (!$row->Collation || $row->Collation === $collation) {
        continue;
      }
      // Skip fields that have non-utf8 collation.
      if (strpos($row->Collation, 'utf8') !== 0) {
        continue;
      }
      drush_print('Converting field: ' . $table_name . '.' . $row->Field);

      // Detect the BINARY option from hook_schema.
      if (strpos($row->Collation, '_bin') !== FALSE) {
        $collation = 'utf8mb4_bin';
      }

      $default = '';
      if ($row->Default !== NULL) {
        $default = 'DEFAULT ' . ($row->Default == "CURRENT_TIMESTAMP" ? "CURRENT_TIMESTAMP" : ":default");
      }
      elseif ($row->Null == 'YES' && $row->Key == '') {
        if ($row->Type == 'timestamp') {
          $default = 'NULL ';
        }
        $default .= 'DEFAULT NULL';
      }

      $sql = "ALTER TABLE {" . $table_name . "}
              MODIFY `" . $row->Field . "` " .
              $row->Type . " " .
              "CHARACTER SET :charset COLLATE :collation " .
              ($row->Null == "YES" ? "" : "NOT NULL ") .
              $default . " " .
              $row->Extra . " " .
              "COMMENT :comment";

      $params = array(
        ':charset' => $charset,
        ':collation' => $collation,
        ':comment' => $row->Comment,
      );
      if (strstr($default, ':default')) {
        $params[':default'] = $row->Default;
      }
      $this->query($sql, $params);
    }
  }
}

function utf8mb4_convert_drush_command() {
  $items = array();

  $items['utf8mb4-convert-databases'] = array(
    'description' => "Converts all databases defined in settings.php to utf8mb4.",
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
    'arguments' => array(
      'connections' => 'A space separated list of connections. Default is default connection.',
    ),
    'options' => array(
      'collation' => 'Specify a collation. Default is "utf8mb4_general_ci", sites with content that is outside of Latin 1 characters may want to use "utf8mb4_unicode_ci".',
      'charset' => 'Specify a charset. Default is "utf8mb4".',
      'exclude' => 'Specify tables to exclude, comma separated.'
    ),
    'examples' => array(
      'drush utf8mb4-convert-databases' => 'Convert the default database.',
      'drush utf8mb4-convert-databases default' => 'Convert the default database (same as no argument).',
      'drush utf8mb4-convert-databases default site2 site3' => 'Convert all specified databases.',
      'drush utf8mb4-convert-databases --exclude=users,sessions' => 'Convert the default database, skipping the users and sessions tables.'
    ),
  );

  $items['utf8mb4-convert-fix'] = array(
    'description' => "Fixes inconsistent NOT NULL, DEFAULT and COMMENT definitions caused by the utf8mb4-convert-databases command in versions prior to 7.x-1.0-beta2.",
    'bootstrap' => DRUSH_BOOTSTRAP_DRUPAL_FULL,
  );

  return $items;
}

function drush_utf8mb4_convert_databases($connections_input = NULL) {
  $charset = drush_get_option('charset', 'utf8mb4');
  $collation = drush_get_option('collation', 'utf8mb4_general_ci');
  global $databases;
  if (version_compare(VERSION, '7.50', '<')) {
    drush_print('Please install Drupal 7.50 or above prior to running this script.');
    return;
  }

  // Default to the default DB connection, else use the user input.
  if (empty($connections_input)) {
    $connections['default'] = $databases['default'];
  }
  else {
    $connections_list = array();
    // Dump the module name in the first position.
    drush_shift();
    // Get the rest, array_intersect_key needs an associative array for the keys.
    while ($arg = drush_shift()) {
      $connections_list[$arg] = '';
    }
    $connections = array_intersect_key($databases, $connections_list);
  }

  drush_print(dt('This will convert the following databases to utf8mb4: !connections', array('!connections' => implode(', ', array_keys($connections)))));
  if (!drush_confirm('Back up your databases before continuing! Continue?')) {
    return;
  }

  $converter = new DrupalCharsetConverter($charset, $collation);
  $success = $converter->convert($connections);
  // Prevent the hook_requirements() check from telling us to convert the
  // database to utf8mb4.
  if ($success) {
    variable_set('drupal_all_databases_are_utf8mb4', TRUE);
  }
}

function drush_utf8mb4_convert_fix() {
  if (version_compare(VERSION, '7.50', '<')) {
    drush_print('Please install Drupal 7.50 or above prior to running this script.');
    return;
  }
  if (!module_exists('schema')) {
    drush_print('Please install the schema module (https://www.drupal.org/project/schema) prior to running this command.');
    return;
  }
  if (!drush_confirm('This will update any database field definitions where NOT NULL, DEFAULT or COMMENT do not match the original schema. Back up your databases before continuing! Continue?')) {
    return;
  }

  // Initialise schema for array_merge().
  $schema = array();

  // Include all module install files.
  module_list(TRUE);
  module_load_all_includes('install');

  // Get complete schema from all hook_schema() implementations.
  foreach (module_implements('schema') as $module) {
    $current = (array) module_invoke($module, 'schema');
    _drupal_schema_initialize($current, $module, FALSE);
    $schema = array_merge($schema, $current);
  }

  // Apply schema alterations.
  drupal_alter('schema', $schema);

  // Get the current database schema.
  $db_schema = schema_dbobject()->inspect();

  // Loop through each declared schema table.
  foreach ($schema as $table_name => $schema_table) {
    $db_table = $db_schema[$table_name];

    // Loop through each column.
    foreach ($schema_table['fields'] as $colname => $col) {
      $db_col = $db_table['fields'][$colname];

      // Ignore columns which are not varchar, char, or text.
      if (!in_array($col['type'], array('varchar', 'char', 'text'))) {
        continue;
      }

      if (
        // NOT NULL is set in schema but not in database, or vice versa.
        (isset($col['not null']) != isset($db_col['not null'])) ||

        // NOT NULL is set in schema and in database, but does not match.
        (isset($col['not null']) && isset($db_col['not null']) && $col['not null'] != $db_col['not null']) ||

        // DEFAULT is set in schema but not in database, or vice versa.
        (isset($col['default']) != isset($db_col['default'])) ||

        // DEFAULT is set in schema and in database, but does not match.
        (isset($col['default']) && isset($db_col['default']) && $col['default'] != $db_col['default']) ||

        // COMMENT is set in schema but not in database, or vice versa.
        (isset($col['description']) != isset($db_col['description'])) ||

        // COMMENT is set in schema and in database, but does not match.
        (isset($col['description']) && isset($db_col['description']) && $col['description'] != $db_col['description'])
      ) {
        // If NOT NULL and DEFAULT are both set, replace any NULL values in the
        // column with the DEFAULT value to prevent errors.
        if (isset($col['not null']) && $col['not null'] && isset($col['default'])) {
          db_update($table_name)
            ->fields(array(
              $colname => $col['default'],
            ))
            ->isNull($colname)
            ->execute();
        }

        // Fix field definition in database.
        db_change_field($table_name, $colname, $colname, $col);
      }
    }
  }

  drush_print('Finished repairing database field definitions!');
}
