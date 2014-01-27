<?php

/**
 * @file
 * Schema module enhancements to DatabaseSchema_mysql
 */

class SchemaDatabaseSchema_mysql extends DatabaseSchema_mysql {
  /**
   * Retrieve generated SQL to create a new table from a Drupal schema definition.
   *
   * @param $name
   *   The name of the table to create.
   * @param $table
   *   A Schema API table definition array.
   * @return
   *   An array of SQL statements to create the table.
   */
  public function getCreateTableSql($name, $table) {
    return parent::createTableSql($name, $table);
  }

  public function schema_type_map() {
    static $map;
    if (!isset($map)) {
      $map = array_flip(array_map('strtolower', $this->getFieldTypeMap()));
    }
    return $map;
  }

  public function inspect($connection = NULL, $table_name = NULL) {
    // Support the deprecated connection parameter.
    if (isset($connection) && $connection != $this->connection->getKey()) {
      $this->connection = Database::getConnection('default', $connection);
    }

    // Get the current database name
    $info = $this->connection->getConnectionOptions();
    $database = $info['database'];

    $tables = array();
    $args = array(':database' => $database);
    $sql = 'SELECT table_name, table_comment
            FROM information_schema.tables
            WHERE table_schema=:database ';
    if (isset($table_name)) {
      $sql .= 'AND table_name = :table ';
      $args[':table'] = $table_name;
    }
    $res = $this->connection->query($sql, $args);
    foreach ($res as $r) {
      $tables[$r->table_name]['description'] = $r->table_comment;
    }

    $sql = 'SELECT table_name, column_type, column_name, column_default,
                   extra, is_nullable, numeric_scale, column_comment
            FROM information_schema.columns
            WHERE table_schema=:database ';
    if (isset($table_name)) {
      $sql .= 'AND table_name = :table ';
    }
    $sql .= 'ORDER BY table_name, ordinal_position';

    $res = $this->connection->query($sql, $args);
    foreach ($res as $r) {
      $r->new_table_name = schema_unprefix_table($r->table_name);

      $numeric = !is_null($r->numeric_scale);
      $col = array();
      $col['type'] = $r->column_type;
      if (preg_match('@([a-z]+)(?:\((\d+)(?:,(\d+))?\))?\s*(unsigned)?@', $col['type'], $matches)) {
        list($col['type'], $col['size']) = schema_schema_type($matches[1], $r->table_name, $r->column_name, 'mysql');
        if (isset($matches[2])) {
          if ($col['type'] == 'numeric' || $col['type'] == 'float' || $col['type'] == 'double') {
            $col['precision'] = $matches[2];
            $col['scale'] = $matches[3];
          }
          elseif (!$numeric) {
            $col['length'] = $matches[2];
          }
        }
        if (isset($matches[4])) {
          $col['unsigned'] = TRUE;
        }
      }
      if ($col['type'] == 'int' && isset($r->extra) &&
          $r->extra == 'auto_increment') {
        $col['type'] = 'serial';
      }
      $col['not null'] = ($r->is_nullable == 'YES' ? FALSE : TRUE);
      if (! is_null($r->column_default)) {
        if ($numeric) {
          // XXX floats!
          $col['default'] = intval($r->column_default);
        }
        else {
          $col['default'] = $r->column_default;
        }
      }
      $col['description'] = $r->column_comment;
      $tables[$r->table_name]['fields'][$r->column_name] = $col;
      // At this point, $tables is indexed by the raw db table name - save the unprefixed
      // name for later use
      $tables[$r->table_name]['name'] = $r->new_table_name;
    }

    $sql = 'SELECT table_name, column_name, index_name, sub_part, non_unique
            FROM information_schema.statistics
            WHERE table_schema=:database ';
    if (isset($table_name)) {
      $sql .= 'AND table_name = :table ';
    }
    $sql .= 'ORDER BY table_name, index_name, seq_in_index';

    $res = $this->connection->query($sql, $args);
    foreach ($res as $r) {
      if (isset($r->sub_part) && !is_null($r->sub_part)) {
        $col = array($r->column_name, intval($r->sub_part));
      }
      else {
        $col = $r->column_name;
      }
      if ($r->index_name == 'PRIMARY') {
        $type = 'primary key';
        $tables[$r->table_name][$type][] = $col;
        continue;
      }
      elseif ($r->non_unique == 0) {
        $type = 'unique keys';
      }
      else {
        $type = 'indexes';
      }
      $tables[$r->table_name][$type][$r->index_name][] = $col;
    }

    // Now, for tables which we have unprefixed, index $tables by the unprefixed name
    foreach ($tables as $tablename => $table) {
      $newname = $tables[$tablename]['name'];
      if ($tablename != $newname) {
        $tables[$newname] = $table;
        unset($tables[$tablename]);
      }
    }

    return $tables;
  }

}
