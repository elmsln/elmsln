<?php


/**
 * @file
 * Functions to handle the direct to database destination.
 */

/**
 * A destination type for saving to a database server.
 *
 * @ingroup backup_migrate_destinations
 */
class backup_migrate_source_db extends backup_migrate_source_remote {
  var $supported_ops = array('configure', 'source');
  var $db_target = 'default';
  var $connection = null;


  function type_name() {
    return t("Database");
  }

  /**
   * Save the info by importing it into the database.
   */
  function save_file($file, $settings) {
    backup_migrate_include('files');

    // Set the source_id to the destination_id in the settings since for a restore, the source_id is the 
    // database that gets restored to.
    $settings->set_source($this->get_id());

    // Restore the file to the source database.
    $file = backup_migrate_perform_restore($this->get_id(), $file, $settings);

    return $file;
  }

  /**
   * Destination configuration callback.
   */
  function edit_form() {
    $form = parent::edit_form();
    $form['scheme']['#default_value'] = $this->default_scheme();
    $form['scheme']['#access'] = FALSE;
    $form['path']['#title'] = t('Database name');
    $form['path']['#description'] = t('The name of the database. The database must exist, it will not be created for you.');
    $form['user']['#description'] = t('Enter the name of a user who has write access to the database.');
    return $form;
  }

  /**
   * Validate the configuration form. Make sure the db info is valid.
   */
  function edit_form_validate($form, &$form_state) {
    if (!preg_match('/[a-zA-Z0-9_\$]+/', $form_state['values']['path'])) {
      form_set_error('path', t('The database name is not valid.'));
    }
    parent::edit_form_validate($form, $form_state);
  }

  /**
   * Get the form for the settings for this destination.
   *
   * Return the default tables whose data can be ignored. These tables mostly contain
   *  info which can be easily reproducted (such as cache or search index)
   *  but also tables which can become quite bloated but are not necessarily extremely
   *  important to back up or migrate during development (such ass access log and watchdog)
   */
  function backup_settings_default() {
    $core = array(
        'cache',
        'cache_admin_menu',
        'cache_browscap',
        'cache_content',
        'cache_filter',
        'cache_calendar_ical',
        'cache_location',
        'cache_menu',
        'cache_page',
        'cache_reptag',
        'cache_views',
        'cache_views_data',
        'cache_block',
        'cache_update',
        'cache_form',
        'cache_bootstrap',
        'cache_field',
        'cache_image',
        'cache_path',
        'sessions',
        'search_dataset',
        'search_index',
        'search_keywords_log',
        'search_total',
        'watchdog',
        'accesslog',
        'devel_queries',
        'devel_times',
      );
    $nodata_tables = array_merge($core, module_invoke_all('devel_caches'));
     return array(
      'nodata_tables' => $nodata_tables,
      'exclude_tables' => array(),
      'utils_lock_tables' => FALSE,
   );
  }

  /**
   * Get the form for the backup settings for this destination.
   */
  function backup_settings_form($settings) {
    $objects  = $this->get_object_names();
    $form['#description'] = t("You may omit specific tables, or specific table data from the backup file. Only omit data that you know you will not need such as cache data, or tables from other applications. Excluding tables can break your Drupal install, so <strong>do not change these settings unless you know what you're doing</strong>.");
    $form['exclude_tables'] = array(
      "#type" => "select",
      "#multiple" => TRUE,
      "#title" => t("Exclude the following tables altogether"),
      "#options" => $objects,
      "#default_value" => $settings['exclude_tables'],
      "#description" => t("The selected tables will not be added to the backup file."),
    );
    $form['nodata_tables'] = array(
      "#type" => "select",
      "#multiple" => TRUE,
      "#title" => t("Exclude the data from the following tables"),
      "#options" => $objects,
      "#default_value" => $settings['nodata_tables'],
      "#description" => t("The selected tables will have their structure backed up but not their contents. This is useful for excluding cache data to reduce file size."),
    );
    $form['utils_lock_tables'] = array(
      '#type' => 'checkbox',
      '#title' => t('Lock tables during backup'),
      '#default_value' => !empty($settings['utils_lock_tables']) ? $settings['utils_lock_tables'] : NULL,
      '#description' => t('This can help reduce data corruption, but will make your site unresponsive.'),
    );
    return $form;
  }

  /**
   * Backup from this source.
   */
  function backup_to_file($file, $settings) {
    $file->push_type($this->get_file_type_id());

    //$this->lock_tables($settings);

    // Switch to a different db if specified.
    $success = $this->_backup_db_to_file($file, $settings);

    //$this->unlock_tables($settings);

    return $success ? $file : FALSE;
  }

  /**
   * Restore to this source.
   */
  function restore_from_file($file, &$settings) {
    $num = 0;
    $type = $this->get_file_type_id();
    // Open the file using the file wrapper. Check that the dump is of the right type (allow .sql for legacy reasons).
    if ($file->type_id() !== $this->get_file_type_id() && $file->type_id() !== 'sql') {
      _backup_migrate_message("Unable to restore from file %file because a %type file can't be restored to this database.", array("%file" => $file->filepath(), '%type' => $file->type_id()), 'error');
    }
    else {
      backup_migrate_filters_invoke_all('pre_restore', $file, $settings);

      // Restore the database.
      $num = $this->_restore_db_from_file($file, $settings);
      $settings->performed_action = $num ? t('%num SQL commands executed.', array('%num' => $num)) : '';

      backup_migrate_filters_invoke_all('post_restore', $file, $settings, $num);
    }
    return $num;
  }

  /**
   * Get the db connection for the specified db.
   */
  function _get_db_connection() {
    if (!$this->connection) {
      $target = $key = '';
      $parts = explode(':', $this->get_id());
      // One of the predefined databases (set in settings.php)
      if ($parts[0] == 'db') {
        $key    = empty($parts[1]) ? 'default' : $parts[1];
        $target = empty($parts[2]) ? 'default' : $parts[2];
      }
      // Another db url.
      else {
        // If the url is specified build it into a connection info array.
        if (!empty($this->dest_url)) {
          $info = array(
            'driver'    => empty($this->dest_url['scheme'])   ? NULL : $this->dest_url['scheme'],
            'host'      => empty($this->dest_url['host'])     ? NULL : $this->dest_url['host'],
            'port'      => empty($this->dest_url['port'])     ? NULL : $this->dest_url['port'],
            'username'  => empty($this->dest_url['user'])     ? NULL : $this->dest_url['user'],
            'password'  => empty($this->dest_url['pass'])     ? NULL : $this->dest_url['pass'],
            'database'  => empty($this->dest_url['path'])     ? NULL : $this->dest_url['path'], 
          );
          $key    = uniqid('backup_migrate_tmp_');
          $target = 'default';
          Database::addConnectionInfo($key, $target, $info);
        }
        // No database selected. Assume the default.
        else {
          $key = $target = 'default';
        }
      }
      if ($target && $key) {
        $this->connection = Database::getConnection($target, $key);
      }
    }
    return $this->connection;
  }

  /**
   * Backup the databases to a file.
   */
  function _backup_db_to_file($file, $settings) {
    // Must be overridden.
  }

  /**
   * Backup the databases to a file.
   */
  function _restore_db_from_file($file, $settings) {
    // Must be overridden.
  }

  /**
   * Get a list of objects in the database.
   */
  function get_object_names() {
    // Must be overridden.
    $out = $this->_get_table_names();
    if (method_exists($this, '_get_view_names')) {
      $out += $this->_get_view_names();
    }
    return $out;
  }

  /**
   * Get a list of tables in the database.
   */
  function get_table_names() {
    // Must be overridden.
    $out = $this->_get_table_names();
    return $out;
  }

  /**
   * Get a list of tables in the database.
   */
  function _get_table_names() {
    // Must be overridden.
    return array();
  }

  /**
   * Lock the database in anticipation of a backup.
   */
  function lock_tables($settings) {
    if ($settings->filters['utils_lock_tables']) {
      $tables = array();
      foreach ($this->get_table_names() as $table) {
        // There's no need to lock excluded or structure only tables because it doesn't matter if they change.
        if (empty($settings->filters['exclude_tables']) || !in_array($table, (array)$settings->filters['exclude_tables'])) {
          $tables[] = $table;
        }
      }
      $this->_lock_tables($tables);
    }
  }

  /**
   * Lock the list of given tables in the database.
   */
  function _lock_tables($tables) {
    // Must be overridden.
  }

  /**
   * Unlock any tables that have been locked.
   */
  function unlock_tables($settings) {
    if ($settings->filters['utils_lock_tables']) {
      $this->_unlock_tables();
    }
  }

  /**
   * Unlock the list of given tables in the database.
   */
  function _unlock_tables($tables) {
    // Must be overridden.
  }

  /**
   * Get the file type for to backup this destination to.
   */
  function get_file_type_id() {
    return 'sql';
  }

  /**
   * Get the version info for the given DB.
   */
  function _db_info() {
    return array(
      'type' => FALSE,
      'version' => t('Unknown'),
    );
  }

}
