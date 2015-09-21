<?php

/**
 * @file
 * Admin page callbacks for the apdqc module.
 */

/**
 * Warn if apdqc.cache.inc is not included in the cache_backends array.
 */
function apdqc_admin_set_message_if_needed() {
  $apdqcache_found = FALSE;
  foreach (variable_get('cache_backends', array()) as $include) {
    if (stripos($include, '/apdqc/apdqc.cache.inc') !== FALSE) {
      $apdqcache_found = TRUE;
      break;
    }
  }
  if (!$apdqcache_found) {
    drupal_set_message(t('Be sure to go to the <a href="@url">status report page</a> and fix any issues under APDQC</a>', array('@url' => url('admin/reports/status'))), 'warning');
  }
}

/**
 * Add the apdqc_verbose_devel_output setting to the devel_admin_settings form.
 */
function apdqc_admin_devel_admin_settings_form(&$form, $form_state) {
  apdqc_admin_set_message_if_needed();
  $apdqc_form = apdqc_admin_get_settings();
  if (isset($apdqc_form['apdqc_verbose_devel_output'])) {
    $form['queries']['settings']['apdqc_verbose_devel_output'] = $apdqc_form['apdqc_verbose_devel_output'];
    $form['queries']['settings']['apdqc_verbose_devel_output']['#weight'] = -1;
  }
}

/**
 * Add various apdqc settings to the system_performance_settings form.
 */
function apdqc_admin_system_performance_settings_form(&$form, $form_state) {
  apdqc_admin_set_message_if_needed();
  // Add in additional times.
  $form['caching']['cache_lifetime']['#options'] += apdqc_admin_additional_times();
  ksort($form['caching']['cache_lifetime']['#options']);
  $form['caching']['page_cache_maximum_age']['#options'] += apdqc_admin_additional_times();
  ksort($form['caching']['page_cache_maximum_age']['#options']);

  // Give more detail about cache_lifetime.
  $form['caching']['cache_lifetime']['#description'] .= ' ' . t("When set to &lt;none&gt;, the entire block and page cache is cleared every time any content is saved.");
  // Recommend the expire module.
  if (!module_exists('expire')) {
    $form['caching']['cache_lifetime']['#description'] .= '<p> ' . t('If using something other than &lt;none&gt; the <a href="@expire">Cache Expiration</a> module is highly recommended.', array('@expire' => 'https://www.drupal.org/project/expire')) . '</p>';
  }
  else {
    // Get config page for expire module.
    $items = expire_menu();
    $link = '';
    foreach ($items as $url => $item) {
      if (in_array('expire_admin_settings_form', $item['page arguments'])) {
        $link = $url;
        break;
      }
    }
    if (empty($link)) {
      foreach ($items as $url => $item) {
        if (strpos($url, 'admin') && strpos($url, 'expire')) {
          $link = $url;
          break;
        }
      }
    }
    // Inform user they need to configure expire.
    $form['caching']['cache_lifetime']['#description'] .= '<p> ' . t('Be sure to <a href="@expire-admin">configure the expire module</a> correctly.', array('@expire-admin' => url($link))) . '</p>';
  }

  // Give more detail about page_cache_maximum_age.
  $form['caching']['page_cache_maximum_age']['#description'] .= ' ' . t('This not only affects reverse proxy caches like Varnish, but also how long browsers should keep cached versions of your pages. If your site changes often keep this value low.');

  $apdqc_form = apdqc_admin_get_settings();
  // Expose the cache_garbage_collection_frequency variable.
  $form['caching']['cache_garbage_collection_frequency'] = $apdqc_form['cache_garbage_collection_frequency'];
  // Allow for module level prefetching to be disabled.
  $form['caching']['apdqc_prefetch'] = $apdqc_form['apdqc_prefetch'];

  // Re-order cache fields.
  $form['caching']['cache_lifetime']['#weight'] = 10;
  $form['caching']['cache_garbage_collection_frequency']['#weight'] = 11;
  $form['caching']['page_cache_maximum_age']['#weight'] = 12;
  $form['caching']['apdqc_prefetch']['#weight'] = 2;
}

/**
 * Form builder; Configure apdqc settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function apdqc_admin_settings_form($form, $form_state) {
  apdqc_admin_set_message_if_needed();
  drupal_set_title(t('APDQC: Configuration'));
  $form = apdqc_admin_get_settings();
  return system_settings_form($form);
}

/**
 * Form builder; preform apdqc operations.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function apdqc_admin_operations_form($form, $form_state) {
  apdqc_admin_set_message_if_needed();
  drupal_set_title(t('APDQC: Operations'));

  // Check semaphore table.
  // Get MySQL version.
  $conversion = apdqc_semaphore_conversion();
  if ($conversion == 1) {
    $form['convert_semaphore_table'] = array(
      '#type' => 'fieldset',
      '#title' => t('Convert semaphore table'),
      '#description' => t('For older versions of MySQL (5.5 and lower) using the memory engine for the semaphore table is recommended.'),
    );
    $form['convert_semaphore_table']['convert_table_to_memory'] = array(
      '#type' => 'submit',
      '#value' => t('Convert semaphore table to MEMORY'),
      '#submit' => array('apdqc_admin_convert_table_to_memory'),
    );
  }
  elseif ($conversion == 2) {
    $form['convert_semaphore_table'] = array(
      '#type' => 'fieldset',
      '#title' => t('Convert semaphore table'),
      '#description' => t('For newer versions of MySQL (5.6 and higher) the InnoDB engine for the semaphore table is recommended.'),
    );
    $form['convert_semaphore_table']['convert_table_to_innodb'] = array(
      '#type' => 'submit',
      '#value' => t('Convert semaphore table to InnoDB'),
      '#submit' => array('apdqc_admin_convert_table_to_innodb'),
    );
  }

  // Check collation.
  $results = apdqc_admin_change_table_collation();
  if (!empty($results)) {
    $form['convert_cache_tables_collation'] = array(
      '#type' => 'fieldset',
      '#title' => t('Convert cache tables collations'),
      '#description' => t('Using the utf8_bin collation is faster and more accurate when matching cache ids since no unicode normalization is done to cache queries.'),
    );
    $form['convert_cache_tables_collation']['convert_table_collations_to_utf8_bin'] = array(
      '#type' => 'submit',
      '#value' => t('Convert cache tables collations'),
      '#submit' => array('apdqc_admin_convert_table_collations_to_utf8_bin'),
    );
  }

  // Check cache indexes.
  $cache_table_indexes = apdqc_get_cache_table_indexes();
  $missing_expire_created_index = FALSE;
  foreach ($cache_table_indexes as $indexes) {
    if (!isset($indexes['expire_created'])) {
      $missing_expire_created_index = TRUE;
      break;
    }
  }
  if (!empty($missing_expire_created_index)) {
    $form['convert_cache_tables_indexes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Convert cache tables indexes'),
      '#description' => t('Garbage collection of the cache bins use the created column. This allows for proper enforcement of the minimum cache lifetime. There needs to be an index on created otherwise garbage collection will be slow.'),
    );
    $form['convert_cache_tables_indexes']['convert_table_collations_to_utf8_bin'] = array(
      '#type' => 'submit',
      '#value' => t('Convert cache tables indexes'),
      '#submit' => array('apdqc_admin_convert_tables_indexes'),
    );
  }

  if (empty($form)) {
    // Explain what can be done on this page.
    $form['tip'] = array(
      '#markup' => '<p>' . t('Nothing needs to be done.') . '</p>',
      '#weight' => -10,
    );
  }
  else {
    if (!variable_get('maintenance_mode', 0)) {
      apdqc_disable_form($form);
      $form['maintenance-mode-tip'] = array(
        '#markup' => '<p>' . t('You need to put the site into <a href="@url">maintenance mode</a> in order to preform the operations below.', array('@url' => url('admin/config/development/maintenance'))) . '</p>',
        '#weight' => -9,
      );
    }
    // Explain what can be done on this page.
    $form['tip'] = array(
      '#markup' => '<p>' . t('This is a collection of commands to control the cache* & semaphore tables and to manage testing of this module. There are no configuration options here.') . '</p>',
      '#weight' => -10,
    );
  }

  return $form;
}

/**
 * Disable all form elements.
 *
 * @param array $form
 *   Array of form elements.
 */
function apdqc_disable_form(array &$form) {
  $keys = element_children($form);
  foreach ($keys as &$key) {
    $form[$key]['#disabled'] = TRUE;
    apdqc_disable_form($form[$key]);
  }
}

/**
 * Return the admin settings form for apdqc.
 *
 * @return array
 *   Array of form elements.
 */
function apdqc_admin_get_settings() {
  $period = drupal_map_assoc(array(0, 60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval');
  $period[0] = '<' . t('none') . '>';
  $period += apdqc_admin_additional_times();
  ksort($period);

  if (!defined('CACHE_GARBAGE_COLLECTION_FREQUENCY')) {
    module_load_include('cache.inc', 'apdqc');
  }

  // Set GC collection frequency.
  $form['cache_garbage_collection_frequency'] = array(
    '#type' => 'select',
    '#title' => t('Cache garbage collection frequency'),
    '#default_value' => variable_get('cache_garbage_collection_frequency', CACHE_GARBAGE_COLLECTION_FREQUENCY),
    '#options' => $period,
    '#description' => t('The frequency with which cache bins are cleared on cron. When ran from system_cron, garbage collection will use the max value of this field and minimum cache lifetime field: <code>max($min_cache_lifetime, $gc_frequency)</code>.'),
  );
  // Allow for module level prefetching to be disabled.
  $form['apdqc_prefetch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefetch cached data'),
    '#default_value' => variable_get('apdqc_prefetch', APDQC_PREFETCH),
  );
  // Adjust devel verbose output.
  if (module_exists('devel')) {
    $form['apdqc_verbose_devel_output'] = array(
      '#type' => 'checkbox',
      '#title' => t('Devel: Output prefetch info from apdqc'),
      '#default_value' => variable_get('apdqc_verbose_devel_output', APDQC_VERBOSE_DEVEL_OUTPUT),
    );
  }
  return $form;
}

/**
 * Return an array of times.
 *
 * @return array
 *   Array where key is in seconds and value is time in human form.
 */
function apdqc_admin_additional_times() {
  return array(
    120 => t('2 min'),
    240 => t('4 min'),
    1200 => t('20 min'),
    1500 => t('25 min'),
    2700 => t('45 min'),
    32400 => t('9 hours'),
    64800 => t('18 hours'),
    129600 => t('1.5 days'),
    172800 => t('2 days'),
    259200 => t('3 days'),
    345600 => t('4 days'),
    432000 => t('5 days'),
    518400 => t('6 days'),
    604800 => t('1 week'),
    907200 => t('1.5 weeks'),
    1209600 => t('2 weeks'),
  );
}

// Operation callbacks.
/**
 * Convert semaphore table to MEMORY.
 */
function apdqc_admin_convert_table_to_memory($show_msg = TRUE) {
  // Get current table indexes.
  $indexes = db_query('SHOW INDEX FROM {semaphore}')->fetchAllAssoc('Key_name');
  // Run the commands.
  db_query('ALTER TABLE {semaphore} ENGINE = MEMORY');
  db_query('ALTER TABLE {semaphore} DROP PRIMARY KEY');
  db_query('ALTER TABLE {semaphore} ADD PRIMARY KEY (name, value) USING BTREE');
  if (!empty($indexes['name'])) {
    db_query('ALTER TABLE {semaphore} DROP INDEX name');
  }
  db_query('ALTER TABLE {semaphore} ADD UNIQUE name (name) USING BTREE');
  db_query('ALTER TABLE {semaphore} DROP INDEX value');
  db_query('ALTER TABLE {semaphore} ADD INDEX value (value) USING BTREE');
  db_query('ALTER TABLE {semaphore} DROP INDEX expire');
  db_query('ALTER TABLE {semaphore} ADD INDEX expire (expire) USING BTREE');

  // Let user know it worked.
  if ($show_msg) {
    drupal_set_message(t('APDQC: semaphore table converted to MEMORY engine'));
  }
  variable_set('apdqc_semaphore_memory', TRUE);
}

/**
 * Convert semaphore table to InnoDB.
 */
function apdqc_admin_convert_table_to_innodb($show_msg = TRUE) {
  // Run the command.
  db_query('ALTER TABLE {semaphore} ENGINE = InnoDB');

  // Let user know it worked.
  if ($show_msg) {
    drupal_set_message(t('APDQC: semaphore table converted to InnoDB engine'));
  }
}

/**
 * Convert table collations to utf8.
 */
function apdqc_admin_convert_table_collations_to_utf8_bin($show_msg = TRUE) {
  // Run the command.
  apdqc_admin_change_table_collation(TRUE);

  // Let user know it worked.
  if ($show_msg) {
    drupal_set_message(t('APDQC: All cache tables collations converted to utf8_bin'));
  }
  variable_set('apdqc_table_collations', TRUE);
}

/**
 * Convert table indexes to expire, created.
 */
function apdqc_admin_convert_tables_indexes($show_msg = TRUE) {
  // Drop the expire index; use expire_created.
  $before = array('expire');
  $after = array('expire', 'created');
  apdqc_convert_cache_index($before, $after);

  // Let user know it worked.
  if ($show_msg) {
    drupal_set_message(t('APDQC: All cache tables indexes where updated.'));
  }
  variable_set('apdqc_table_indexes', TRUE);
}

/**
 * Convert cache tables collation to utf8_bin.
 *
 * @param bool $preform_alter
 *   Set to TRUE to actually preform the alter.
 * @param string $collation
 *   The db collation to change to table columns to.
 *
 * @return array
 *   Returns an array of tables and column names.
 */
function apdqc_admin_change_table_collation($preform_alter = FALSE, $collation = 'utf8_bin') {
  $cache_tables = apdqc_get_cache_tables();
  $db_type = Database::getConnection()->databaseType();
  $tables_altered = array();
  if ($db_type === 'mysql') {
    foreach ($cache_tables as $table_name) {
      $tables_altered += apdqc_admin_change_table_collation_queries($table_name, $collation, $preform_alter);
    }
  }

  return $tables_altered;
}

/**
 * Convert the table to the specified collation.
 *
 * @param string $table_name
 *   Preform the operation on this table.
 * @param string $collation
 *   The db collation to change to table columns to.
 * @param bool $preform_alter
 *   Set to TRUE to actually preform the alter.
 *
 * @return array
 *   Returns an array of tables and column names.
 */
function apdqc_admin_change_table_collation_queries($table_name, $collation, $preform_alter) {
  $db_type = Database::getConnection()->databaseType();
  $tables_altered = array();
  if ($db_type === 'mysql' && db_table_exists($table_name)) {
    $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table_name) . '}');
    $results = db_query("SHOW FULL FIELDS FROM $table_name")->fetchAllAssoc('Field');
    foreach ($results as $row) {
      if (stripos($row->Type, 'varchar') !== FALSE && $row->Collation !== $collation) {
        if ($preform_alter) {
          $query = "ALTER TABLE $table_name MODIFY {$row->Field} {$row->Type} CHARACTER SET utf8 COLLATE $collation";
          if (function_exists('apdqc_query')) {
            $mysqli = apdqc_query(array($table_name), array('*'), $query, array('async' => TRUE, 'log' => FALSE, 'get_mysqli' => TRUE));
            $good = TRUE;
            if (isset($mysqli->thread_id)) {
              if (apdqc_kill_metadata_lock($mysqli->thread_id)) {
                $tables_altered[$table_name][$row->Field] = 'metadata lock';
                $good = FALSE;
              }
            }
            if ($good) {
              $tables_altered[$table_name][$row->Field] = 'done';
            }
          }
          else {
            db_query($query);
            $tables_altered[$table_name][$row->Field] = 'done';
          }
        }
        else {
          $tables_altered[$table_name][$row->Field] = '';
        }
      }
    }
  }
  return $tables_altered;
}

/**
 * Get all database indexes for the cache tables.
 *
 * @return array
 *   Returns an array of tables and index names.
 */
function apdqc_get_cache_table_indexes() {
  $table_names = apdqc_get_cache_tables();

  $results = array();
  foreach ($table_names as &$table_name) {
    if (!db_table_exists($table_name)) {
      continue;
    }
    $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table_name) . '}');
    $result = db_query("SHOW INDEX IN $table_name")->fetchAll();
    foreach ($result as $row) {
      $results[$table_name][$row->Key_name][] = $row->Column_name;
    }
  }
  return $results;
}

/**
 * Converts a database index from one form to antoher.
 *
 * @param array $before
 *   List of keys that need to be removed.
 * @param array $after
 *   List of keys that will be used in the new index.
 */
function apdqc_convert_cache_index(array $before, array $after) {
  $table_indexes = apdqc_get_cache_table_indexes();
  $before_name = implode('_', $before);
  $after_name = implode('_', $after);
  foreach ($table_indexes as $table_name => $indexes) {
    if (isset($indexes[$before_name])) {
      if (function_exists('apdqc_query')) {
        $query = "ALTER TABLE $table_name DROP INDEX `$before_name`";
        $mysqli = apdqc_query(array($table_name), array('*'), $query, array('async' => TRUE, 'log' => FALSE, 'get_mysqli' => TRUE));
        if (isset($mysqli->thread_id)) {
          apdqc_kill_metadata_lock($mysqli->thread_id);
        }
      }
      else {
        db_drop_index($table_name, $before_name);
      }
    }
    if (!isset($indexes[$after_name])) {
      if (function_exists('apdqc_query')) {
        $columns = apdqc_create_key_sql($after);
        $query = "ALTER TABLE $table_name ADD INDEX `$after_name` ($columns)";
        $mysqli = apdqc_query(array($table_name), array('*'), $query, array('async' => TRUE, 'log' => FALSE, 'get_mysqli' => TRUE));
        if (isset($mysqli->thread_id)) {
          apdqc_kill_metadata_lock($mysqli->thread_id);
        }
      }
      else {
        db_add_index($table_name, $after_name, $after);
      }
    }
  }
}

/**
 * Returns a list of all cache tables used.
 *
 * @param bool $get_truncated
 *   Set to FALSE to not include "__truncated_table" tables in the return array.
 *
 * @return array
 *   Returns an array of cache tables.
 */
function apdqc_get_cache_tables($get_truncated = TRUE) {
  $cache_tables = &drupal_static(__FUNCTION__);
  if (!isset($cache_tables)) {
    $schema = drupal_get_schema();
    foreach ($schema as $table_name => &$values) {
      if (strpos($table_name, 'cache') !== 0) {
        // Remove if not a cache* table.
        unset($schema[$table_name]);
        continue;
      }
      if (empty($schema[$table_name]['fields']['cid'])) {
        // Remove if no cid field.
        unset($schema[$table_name]);
        continue;
      }
    }
    $schema = array_keys($schema);
    // Add in the cache*__truncated_table tables.
    if ($get_truncated) {
      foreach ($schema as $table_name) {
        if (db_table_exists($table_name . '__truncated_table')) {
          $schema[] = $table_name . '__truncated_table';
        }
      }
    }
    $cache_tables = $schema;
  }
  return $cache_tables;
}

