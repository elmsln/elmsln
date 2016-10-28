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
 * Form builder; perform apdqc operations.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function apdqc_admin_operations_form($form, $form_state) {
  apdqc_admin_set_message_if_needed();
  if (!empty($form) || !empty($form_state)) {
    drupal_set_title(t('APDQC: Operations'));
  }

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
      '#submit' => array('apdqc_admin_convert_semaphore_table_to_innodb'),
    );
  }

  $lock_inc = variable_get('lock_inc', 'includes/lock.inc');
  $semaphore_update = apdqc_admin_semaphore_table_need_update();
  if (stripos($lock_inc, 'apdqc.lock.inc') !== FALSE && $semaphore_update) {
    $form['convert_semaphore_table_schema'] = array(
      '#type' => 'fieldset',
      '#title' => t('Semaphore table schema update'),
      '#description' => t('Will make the primary key be name, value, expire; have the name and value columns use ascii_bin.'),
    );
    $form['convert_semaphore_table_schema']['semaphore_table_update_schema'] = array(
      '#type' => 'submit',
      '#value' => t('Semaphore table schema update'),
      '#submit' => array('apdqc_admin_semaphore_table_update_schema'),
    );
  }

  $session = variable_get('session_inc', 'includes/session.inc');
  $session_update = apdqc_admin_sessions_table_need_update();
  $session_update_duplicates = apdqc_admin_sessions_table_duplicates(FALSE, FALSE);
  if (stripos($session, 'apdqc.session.inc') !== FALSE && (!empty($session_update) || !empty($session_update_duplicates))) {
    $form['convert_sessions_table_schema'] = array(
      '#type' => 'fieldset',
      '#title' => t('Sessions table schema update'),
      '#description' => t('Will make sid and ssid be char(43); hostname varchar(45); sid, ssid, and hostname be ascii_bin. This can sometimes take a little while.'),
    );
    $form['convert_sessions_table_schema']['sessions_table_update_schema'] = array(
      '#type' => 'submit',
      '#value' => t('Sessions table schema update'),
      '#submit' => array('apdqc_admin_sessions_table_update_schema'),
    );
  }

  // Check collation.
  $results_utf8 = apdqc_admin_change_table_collation(FALSE, 'utf8_bin');
  $results_ascii = apdqc_admin_change_table_collation(FALSE, 'ascii_bin');
  $collation = variable_get('apdqc_table_collations', APDQC_TABLE_COLLATIONS);
  $cache_tables = apdqc_get_cache_tables(TRUE, FALSE);

  $charset = 'ASCII';
  $non_ascii_tables = array();
  foreach ($cache_tables as $table_name) {
    if (db_table_exists($table_name)) {
      $results = db_query("SELECT COUNT(*) AS bad_translation FROM {{$table_name}} WHERE cid <> CONVERT(cid USING $charset)")->fetchAssoc();
      if (!empty($results['bad_translation'])) {
        $non_ascii_tables[] = $table_name;
      }
    }
  }

  $cache_page = array();
  if (module_exists('locale')) {
    $cache_page = array('cache_page', 'cache_page__truncated_table');
  }
  $ascii_tables = array();
  foreach ($results_utf8 as $table => $values) {
    foreach ($values as $current_collation) {
      if ($current_collation === 'ascii_bin') {
        $ascii_tables[] = $table;
      }
    }
  }
  $utf8_tables = array();
  foreach ($results_ascii as $table => $values) {
    foreach ($values as $current_collation) {
      if ($current_collation === 'utf8_bin') {
        $utf8_tables[] = $table;
      }
    }
  }
  $not_using_ascii = array_diff($cache_tables, $ascii_tables, $cache_page, $non_ascii_tables);
  $not_using_utf8 = array_diff($cache_tables, $utf8_tables, $cache_page, $non_ascii_tables);
  if (!empty($results_utf8) && (empty($not_using_ascii) || $collation === 'utf8_bin')) {
    if (empty($results_ascii) || $collation === 'ascii_bin') {
      $form['convert_cache_tables_collation_utf8'] = array(
        '#type' => 'fieldset',
        '#title' => t('Convert cache tables collations to utf8 from ascii'),
        '#description' => t('You are currently using ascii_bin which is faster but may not be as accurate when matching cache ids. Using the utf8_bin collation can be more accurate when matching cache ids. In reality ascii_bin is usually ok and causes no issues, thus you should not convert these tables back to utf8_bin unless you have a reason to.'),
      );
      if ($collation === 'ascii_bin') {
        $form['convert_cache_tables_collation_utf8'] += array(
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#weight' => 100,
        );
      }
    }
    else {
      $form['convert_cache_tables_collation_utf8'] = array(
        '#type' => 'fieldset',
        '#title' => t('Convert cache tables collations to utf8'),
        '#description' => t('Using the utf8_bin collation is faster and more accurate when matching cache ids since no unicode normalization is done to cache queries. Tables not using utf8_bin: @tables', array(
          '@tables' => implode(', ', $not_using_utf8),
        )),
        '#raw_data' => $not_using_utf8,
      );
    }
    $form['convert_cache_tables_collation_utf8']['convert_table_collations_to_utf8_bin'] = array(
      '#type' => 'submit',
      '#value' => t('Convert cache tables collations'),
      '#submit' => array('apdqc_admin_convert_table_collations_to_utf8_bin'),
    );
  }
  if (!empty($results_ascii) && (empty($not_using_utf8) || $collation === 'ascii_bin')) {
    $description = t('No cache tables where found that contain non ascii characters; conversion should be safe.');
    if (!empty($non_ascii_tables)) {
      $description = t('The following tables contain non ascii characters and will not be converted: @tables.', array('@tables' => implode(', ', $non_ascii_tables)));
    }
    if (empty($results_utf8) || $collation === TRUE || $collation === 'utf8_bin') {
      $form['convert_cache_tables_collation_ascii'] = array(
        '#type' => 'fieldset',
        '#title' => t('Convert cache tables collations to ascii from utf8'),
        '#description' => t('You are currently using utf8_bin which is slightly slower but accurate when matching cache ids. Using the ascii_bin collation is faster but it could cause issues. @extra', array('@extra' => $description)),
      );
      if ($collation === 'utf8_bin') {
        $form['convert_cache_tables_collation_ascii'] += array(
          '#collapsible' => TRUE,
          '#collapsed' => TRUE,
          '#weight' => 100,
        );
      }
    }
    else {
      $form['convert_cache_tables_collation_ascii'] = array(
        '#type' => 'fieldset',
        '#title' => t('Convert cache tables collations to ascii'),
        '#description' => t('Using the ascii_bin collation is very fast but it could cause issues. Tables not using ascii_bin: @tables. @extra', array(
          '@tables' => implode(', ', $not_using_ascii),
          '@extra' => $description,
        )),
        '#raw_data' => $not_using_ascii,
      );
    }
    $form['convert_cache_tables_collation_ascii']['convert_table_collations_to_ascii_bin'] = array(
      '#type' => 'submit',
      '#value' => t('Convert cache tables collations'),
      '#submit' => array('apdqc_admin_convert_table_collations_to_ascii_bin'),
    );
  }

  // Check engine.
  $results = apdqc_admin_change_table_engine();
  if (!empty($results)) {
    $form['convert_cache_tables_engine'] = array(
      '#type' => 'fieldset',
      '#title' => t('Convert cache tables engine'),
      '#description' => t('Using the InnoDB engine is faster and recommended'),
    );
    $form['convert_cache_tables_collation']['convert_table_engine_to_innodb'] = array(
      '#type' => 'submit',
      '#value' => t('Convert cache tables engine'),
      '#submit' => array('apdqc_admin_convert_table_engine_to_innodb'),
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

  // Check if tables need to be put into individual files.
  $results = array();
  $results += db_query("SHOW GLOBAL VARIABLES LIKE 'innodb_file_per_table'")->fetchAllKeyed();
  if (variable_get('apdqc_innodb_file_per_table', APDQC_INNODB_FILE_PER_TABLE) === 'OFF' && $results['innodb_file_per_table'] === 'ON' || $results['innodb_file_per_table'] == 1) {
    $form['all_db_tables_own_file'] = array(
      '#type' => 'fieldset',
      '#title' => t('Make every database table a file'),
      '#description' => t('Once the innodb_file_per_table variable has been changed the tables need to be rebuilt so they live in their own file.'),
    );
    $form['all_db_tables_own_file']['convert_innodb_tables_to_files'] = array(
      '#type' => 'submit',
      '#value' => t('Make every database table a file'),
      '#submit' => array('apdqc_admin_convert_innodb_tables_to_files'),
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
        '#markup' => '<p>' . t('You need to put the site into <a href="@url">maintenance mode</a> in order to perform the operations below.', array('@url' => url('admin/config/development/maintenance'))) . '</p>',
        '#weight' => -9,
      );
    }
    // Explain what can be done on this page.
    $form['tip'] = array(
      '#markup' => '<p>' . t('This is a collection of commands to control the cache*, semaphore, and session tables and to manage testing of this module. There are no configuration options here.') . '</p>',
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
  $period = drupal_map_assoc(array(
    0,
    60,
    180,
    300,
    600,
    900,
    1800,
    2700,
    3600,
    10800,
    21600,
    32400,
    43200,
    86400,
  ), 'format_interval');
  // @codingStandardsIgnoreLine
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
    // @codingStandardsIgnoreLine
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
  // Allow for views_unpack prefetching to be enabled.
  $form['apdqc_prefetch_views_unpack'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prefetch views unpack data'),
    '#default_value' => variable_get('apdqc_prefetch_views_unpack', APDQC_PREFETCH_VIEWS_UNPACK),
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
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_table_to_memory($show_msg = TRUE) {
  $before = apdqc_semaphore_conversion();

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
  if ($show_msg !== FALSE) {
    $conversion = apdqc_semaphore_conversion();
    if ($before != 1) {
      drupal_set_message(t('APDQC: semaphore table is already using the MEMORY engine.'));
    }
    elseif ($conversion == 1) {
      drupal_set_message(t('APDQC: semaphore table was not converted to MEMORY engine. You need to do this manually by using a tool like phpmyadmin.'), 'error');
    }
    else {
      drupal_set_message(t('APDQC: semaphore table converted to MEMORY engine'));
    }
  }
  variable_set('apdqc_semaphore_memory', TRUE);
}

/**
 * Convert semaphore table to InnoDB.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_semaphore_table_to_innodb($show_msg = TRUE) {
  $before = apdqc_semaphore_conversion();
  // Run the command.
  db_query('ALTER TABLE {semaphore} ENGINE = InnoDB');

  // Let user know it worked.
  if ($show_msg !== FALSE) {
    $conversion = apdqc_semaphore_conversion();
    if ($before != 2) {
      drupal_set_message(t('APDQC: semaphore table is already using the InnoDB engine.'));
    }
    elseif ($conversion == 2) {
      drupal_set_message(t('APDQC: semaphore table was not converted to InnoDB engine. You need to do this manually by using a tool like phpmyadmin.'), 'error');
    }
    else {
      drupal_set_message(t('APDQC: semaphore table converted to InnoDB engine'));
    }
  }
}

/**
 * Convert cache table collations to utf8.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_table_collations_to_utf8_bin($show_msg = TRUE) {
  apdqc_admin_convert_table_collations_to($show_msg, 'utf8_bin');
}

/**
 * Convert cache table collations to ascii.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_table_collations_to_ascii_bin($show_msg = TRUE) {
  apdqc_admin_convert_table_collations_to($show_msg, 'ascii_bin');
}

/**
 * Convert cache table collations.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 * @param string $collation
 *   Database collation; default is utf8_bin, can also use ascii_bin.
 */
function apdqc_admin_convert_table_collations_to($show_msg = TRUE, $collation = 'utf8_bin') {
  $before = apdqc_admin_change_table_collation(FALSE, $collation);

  // Run the command.
  apdqc_admin_change_table_collation(TRUE, $collation);

  // Let user know it worked.
  if ($show_msg !== FALSE) {
    $after = apdqc_admin_change_table_collation(FALSE, $collation);
    if (empty($before)) {
      drupal_set_message(t('APDQC: All cache tables collations were already @collation', array('@collation' => $collation)));
    }
    elseif (!empty($after)) {
      drupal_set_message(t('APDQC: Cache tables collations were not converted to @collation. You need to do this manually by using a tool like phpmyadmin.', array('@collation' => $collation)), 'error');
    }
    else {
      drupal_set_message(t('APDQC: All cache tables collations converted to @collation', array('@collation' => $collation)));
    }
  }
  variable_set('apdqc_table_collations', $collation);
}

/**
 * Convert table engine to InnoDB.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_table_engine_to_innodb($show_msg = TRUE) {
  // Run the command.
  $return = apdqc_admin_change_table_engine(TRUE);

  // Let user know it worked.
  if ($return !== FALSE) {
    if ($show_msg !== FALSE) {
      if (!empty($return)) {
        drupal_set_message(t('APDQC: All cache tables engines converted to InnoDB'));
      }
      else {
        drupal_set_message(t('APDQC: All cache tables engines were already InnoDB'));
      }
    }
  }
  else {
    $tables = apdqc_admin_change_table_engine();
    drupal_set_message(t('APDQC: Cache tables could not be converted to InnoDB. Use a tool like phpmyadmin and convert these cache tables manually to InnoDB - @tables.', array('@tables' => implode(', ', $tables))), 'error');
  }
  variable_set('apdqc_innodb', TRUE);
}

/**
 * Convert innodb tables to be stored per file.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_innodb_tables_to_files($show_msg = TRUE) {
  $db_type = Database::getConnection()->databaseType();
  if ($db_type !== 'mysql') {
    return;
  }

  $db = Database::getConnection()->getConnectionOptions();
  $innodb_tables = db_query("
    SELECT
      table_name,
      engine
    FROM information_schema.tables
    WHERE TABLE_SCHEMA = :dbname
    AND TABLE_TYPE = 'BASE TABLE'
    AND ENGINE = 'InnoDB'
  ", array(
    ':dbname' => $db['database'],
  ))->fetchAllAssoc('table_name');
  foreach ($innodb_tables as $row) {
    db_query("ALTER TABLE `{$row->table_name}` DISABLE KEYS;");
    db_query("ALTER TABLE `{$row->table_name}` ENGINE = InnoDB;");
    db_query("ALTER TABLE `{$row->table_name}` ENABLE KEYS;");
  }
  // Let user know it worked.
  if ($show_msg !== FALSE) {
    drupal_set_message(t('APDQC: All InnoDB tables are file per table.'));
  }
  variable_del('apdqc_innodb_file_per_table');
}

/**
 * Convert table indexes to expire, created.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 */
function apdqc_admin_convert_tables_indexes($show_msg = TRUE) {
  $cache_table_indexes_before = apdqc_get_cache_table_indexes();
  $missing_expire_created_index_before = FALSE;
  foreach ($cache_table_indexes_before as $indexes) {
    if (!isset($indexes['expire_created'])) {
      $missing_expire_created_index_before = TRUE;
      break;
    }
  }

  // Drop the expire index; use expire_created.
  $before = array('expire');
  $after = array('expire', 'created');
  apdqc_convert_cache_index($before, $after);

  $cache_table_indexes_after = apdqc_get_cache_table_indexes();
  $missing_expire_created_index_after = FALSE;
  foreach ($cache_table_indexes_after as $indexes) {
    if (!isset($indexes['expire_created']) && isset($indexes['expire'])) {
      $missing_expire_created_index_after = TRUE;
      break;
    }
  }

  // Let user know it worked.
  if ($show_msg !== FALSE) {
    if ($missing_expire_created_index_before === FALSE) {
      drupal_set_message(t('APDQC: All cache tables indexes where already up to date.'));
    }
    elseif ($missing_expire_created_index_after === TRUE) {
      drupal_set_message(t('APDQC: All cache tables indexes where not updated. You need to do this manually by using a tool like phpmyadmin.'), 'error');
    }
    else {
      drupal_set_message(t('APDQC: All cache tables indexes where updated.'));
    }
  }
  variable_set('apdqc_table_indexes', TRUE);
}

/**
 * Convert cache tables engine to InnoDB.
 *
 * @param bool $perform_alter
 *   Set to TRUE to actually perform the alter.
 * @param array $cache_tables
 *   Pass in a set of tables if you do not wish to operate on all cache tables.
 *
 * @return mixed
 *   Returns an array of tables that need to be changed or that were changed.
 *   Will return FALSE if the alter failed.
 */
function apdqc_admin_change_table_engine($perform_alter = FALSE, array $cache_tables = array()) {
  if (empty($cache_tables)) {
    $cache_tables = apdqc_get_cache_tables();
  }
  $db_type = Database::getConnection()->databaseType();
  $db = Database::getConnection()->getConnectionOptions();
  $tables_altered = array();
  $results_after = array();
  if ($db_type === 'mysql') {
    // Get cache table engine.
    $results_before = db_query("
      SELECT
        table_name,
        engine
      FROM information_schema.tables
      WHERE TABLE_SCHEMA = :dbname
      AND ENGINE <> 'InnoDB'
      AND TABLE_NAME IN (:tables)
    ", array(
      ':dbname' => $db['database'],
      ':tables' => $cache_tables,
    ))->fetchAllAssoc('table_name');
    if ($perform_alter) {
      foreach ($results_before as $row) {
        $table_name = $row->table_name;
        db_query("ALTER TABLE $table_name ENGINE = InnoDB;");
        $tables_altered[] = $row->table_name;
      }
      $results_after = db_query("
        SELECT
          table_name,
          engine
        FROM information_schema.tables
        WHERE TABLE_SCHEMA = :dbname
        AND ENGINE <> 'InnoDB'
        AND TABLE_NAME IN (:tables)
      ", array(
        ':dbname' => $db['database'],
        ':tables' => $cache_tables,
      ))->fetchAllAssoc('table_name');
    }
  }
  if ($perform_alter) {
    if (empty($results_after)) {
      return $tables_altered;
    }
    else {
      return FALSE;
    }
  }
  else {
    return array_keys($results_before);
  }
}

/**
 * Convert cache tables collation to utf8_bin/ascii_bin.
 *
 * @param bool $perform_alter
 *   Set to TRUE to actually perform the alter.
 * @param string $collation
 *   The db collation to change to table columns to.
 * @param array $cache_tables
 *   Pass in a set of tables if you do not wish to operate on all cache tables.
 *
 * @return array
 *   Returns an array of tables and column names.
 */
function apdqc_admin_change_table_collation($perform_alter = FALSE, $collation = 'ascii_bin', array $cache_tables = array()) {
  if (empty($cache_tables)) {
    $cache_tables = apdqc_get_cache_tables(TRUE, TRUE);
  }
  $db_type = Database::getConnection()->databaseType();
  $tables_altered = array();
  if ($db_type === 'mysql') {
    $fields = array('cid');
    $charset = strtoupper(substr($collation, 0, strpos($collation, '_')));
    foreach ($cache_tables as $table_name => $schema) {
      // Skip cache_page if locale module is enabled and charset is ascii.
      if (strpos($table_name, 'cache_page') !== FALSE && module_exists('locale') && $charset === 'ASCII') {
        // Perform the operation, but use utf8_bin.
        $tables_altered += apdqc_admin_change_table_collation_queries($table_name, 'utf8_bin', $perform_alter, $fields, $schema['fields']);

        continue;
      }

      // Quick test to see if the charset will work without dataloss.
      // Only test if not UTF8.
      if ($charset !== 'UTF8' && db_table_exists($table_name)) {
        $results = db_query("SELECT COUNT(*) AS bad_translation FROM {{$table_name}} WHERE cid <> CONVERT(cid USING $charset)")->fetchAssoc();
        if (!empty($results['bad_translation'])) {
          continue;
        }
      }

      // Perform the operation.
      $tables_altered += apdqc_admin_change_table_collation_queries($table_name, $collation, $perform_alter, $fields, $schema['fields']);
    }
  }

  return $tables_altered;
}

/**
 * Convert the table to the specified collation.
 *
 * @param string $table_name
 *   Perform the operation on this table.
 * @param string $collation
 *   The db collation to change to table columns to.
 * @param bool $perform_alter
 *   Set to TRUE to actually perform the alter.
 * @param array $fields
 *   An array of field names.
 * @param array $schema_fields
 *   An array of field definitions.
 *
 * @return array
 *   Returns an array of tables and column names.
 */
function apdqc_admin_change_table_collation_queries($table_name, $collation, $perform_alter, $fields, $schema_fields = array()) {
  $db_type = Database::getConnection()->databaseType();
  $tables_altered = array();
  if ($db_type !== 'mysql' || !db_table_exists($table_name)) {
    return $tables_altered;
  }
  if (empty($schema_fields)) {
    $schema = apdqc_get_full_schema();
    if (isset($schema[$table_name])) {
      $schema_fields = $schema[$table_name]['fields'];
    }
    else {
      $perform_alter = FALSE;
    }
  }

  $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table_name) . '}');
  $results = db_query("SHOW FULL FIELDS FROM $table_name")->fetchAllAssoc('Field');
  $db_schema = Database::getConnection()->schema();
  foreach ($results as $row) {
    if (!in_array($row->Field, $fields) || $row->Collation === $collation) {
      continue;
    }
    if (!$perform_alter) {
      $tables_altered[$table_name][$row->Field] = $row->Collation;
    }
    else {
      $charset = strtolower(substr($collation, 0, strpos($collation, '_')));
      $query = "ALTER TABLE $table_name CHANGE `{$row->Field}` `{$row->Field}` {$row->Type}";
      $query .= " CHARACTER SET $charset COLLATE $collation";

      if (isset($schema_fields[$row->Field]['not null'])) {
        if ($schema_fields[$row->Field]['not null']) {
          $query .= ' NOT NULL';
        }
        else {
          $query .= ' NULL';
        }
      }

      // $schema_fields[$row->Field]['default'] can be NULL, so we explicitly
      // check for the key here.
      if (isset($schema_fields[$row->Field])
        && is_array($schema_fields[$row->Field])
        && array_key_exists('default', $schema_fields[$row->Field])
      ) {
        $default = $schema_fields[$row->Field]['default'];
        if (is_string($default)) {
          $default = "'" . $default . "'";
        }
        elseif (!isset($default)) {
          $default = 'NULL';
        }
        $query .= ' DEFAULT ' . $default;
      }

      if (empty($schema_fields[$row->Field]['not null']) && !isset($schema_fields[$row->Field]['default'])) {
        $query .= ' DEFAULT NULL';
      }

      // Add column comment.
      if (!empty($schema_fields[$row->Field]['description'])) {
        $query .= ' COMMENT ' . $db_schema->prepareComment($schema_fields[$row->Field]['description'], 255);
      }
      if (function_exists('apdqc_query')) {
        $mysqli = apdqc_query(array($table_name), array('*'), $query, array(
          'async' => TRUE,
          'log' => FALSE,
          'get_mysqli' => TRUE,
        ));
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
  }
  if (function_exists('apdqc_get_db_object')) {
    apdqc_get_db_object(array(), array(), array('async' => FALSE, 'reap' => TRUE));
  }
  return $tables_altered;
}

/**
 * Update the sessions table schema.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 * @param bool $reverse
 *   Undo all the changes made to the sessions table.
 *
 * @return bool
 *   Returns TRUE if changes where made.
 */
function apdqc_admin_sessions_table_update_schema($show_msg = TRUE, $reverse = FALSE) {
  $changed = FALSE;
  if ($reverse === TRUE) {
    variable_del('apdqc_sessions_schema');

    // Unmodify sessions table.
    $schema = drupal_get_schema_unprocessed('system', 'sessions');
    $table = 'sessions';
    $field = 'sid';
    db_change_field($table, $field, $field, $schema['fields'][$field]);
    $field = 'ssid';
    db_change_field($table, $field, $field, $schema['fields'][$field]);
    $field = 'hostname';
    db_change_field($table, $field, $field, $schema['fields'][$field]);

    $columns = array('sid', 'ssid', 'hostname');
    apdqc_admin_change_table_collation_queries('sessions', 'utf8_general_ci', TRUE, $columns);
    apdqc_admin_sessions_table_duplicates(TRUE, TRUE);
    variable_del('apdqc_sessions_schema');
    $changed = TRUE;
  }
  else {
    // Modify sessions table.
    $table = 'sessions';
    $schema = apdqc_get_full_schema();
    $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table) . '}');
    $results = db_query("SHOW FULL FIELDS FROM $table_name")->fetchAllAssoc('Field');
    $field = 'sid';
    if ($results[$field]->Type !== 'char(43)') {
      db_change_field($table, $field, $field, $schema[$table]['fields'][$field]);
      $changed = TRUE;
    }
    $field = 'ssid';
    if ($results[$field]->Type !== 'char(43)') {
      db_change_field($table, $field, $field, $schema[$table]['fields'][$field]);
      $changed = TRUE;
    }
    $field = 'hostname';
    if ($results[$field]->Type !== 'varchar(45)') {
      db_change_field($table, $field, $field, $schema[$table]['fields'][$field]);
      $changed = TRUE;
    }

    $columns = array('sid', 'ssid', 'hostname');
    $collation_changed = apdqc_admin_change_table_collation_queries('sessions', 'ascii_bin', TRUE, $columns);
    if ($collation_changed) {
      $changed = TRUE;
    }
    $other_tables_changed = apdqc_admin_sessions_table_duplicates(TRUE, FALSE);
    if ($other_tables_changed) {
      $changed = TRUE;
    }
    if ($show_msg !== FALSE) {
      drupal_set_message(t('APDQC: sessions table schema has been updated.'));
    }
    variable_set('apdqc_sessions_schema', TRUE);
  }
  return $changed;
}

/**
 * Update the semaphore table schema.
 *
 * @param bool $show_msg
 *   Set to FALSE to not run drupal_set_message().
 * @param bool $reverse
 *   Undo all the changes made to the semaphore table.
 *
 * @return bool
 *   Returns TRUE if changes where made.
 */
function apdqc_admin_semaphore_table_update_schema($show_msg = TRUE, $reverse = FALSE) {
  $changed = FALSE;
  $table = 'semaphore';
  $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table) . '}');
  $field = 'value';

  if ($reverse === TRUE) {
    variable_del('apdqc_semaphore_schema');

    // Unmodify semaphore table.
    $schema = drupal_get_schema_unprocessed('system', $table);
    db_change_field($table, $field, $field, $schema['fields'][$field]);

    $results = db_query("SHOW KEYS FROM $table_name WHERE Key_name = 'PRIMARY'")->fetchAllAssoc('Column_name');
    if (count($results) == 3) {
      // Lock table and alter primary key.
      db_query("LOCK TABLES $table_name WRITE");
      db_query("ALTER TABLE $table_name DROP PRIMARY KEY, ADD PRIMARY KEY (name)");

      // Verify.
      $results = db_query("SHOW KEYS FROM $table_name WHERE Key_name = 'PRIMARY'")->fetchAllAssoc('Column_name');
      if (empty($results) || empty($results['name'])) {
        db_drop_primary_key($table);
        db_add_primary_key($table, array('name'));
      }

      // Unlock tables.
      db_query('UNLOCK TABLES');
    }

    apdqc_admin_change_table_collation_queries($table, 'utf8_general_ci', TRUE, array('name', 'value'));
    variable_del('apdqc_semaphore_schema');
    $changed = TRUE;
  }
  else {

    // Remove old junk.
    $results = db_delete($table)
      ->condition('expire', REQUEST_TIME - 600, '<')
      ->execute();

    // Modify semaphore table.
    $results = db_query("SELECT LENGTH(value) AS max_length FROM $table_name ORDER BY LENGTH(value) DESC LIMIT 1")->fetchAssoc();
    $schema = apdqc_get_full_schema();

    if ($results['max_length'] <= 20) {
      db_change_field($table, $field, $field, $schema[$table]['fields'][$field]);
      $changed = TRUE;
    }
    elseif ($results['max_length'] <= 33) {
      $schema[$table]['fields'][$field]['length'] = 33;
      db_change_field($table, $field, $field, $schema[$table]['fields'][$field]);
      $changed = TRUE;
    }

    $results = db_query("SHOW KEYS FROM $table_name WHERE Key_name = 'PRIMARY'")->fetchAllAssoc('Column_name');
    if (count($results) != 3) {
      // Lock table and alter primary key.
      db_query("LOCK TABLES $table_name WRITE");
      db_query("ALTER TABLE $table_name DROP PRIMARY KEY, ADD PRIMARY KEY (name, value, expire)");

      // Verify.
      $results = db_query("SHOW KEYS FROM $table_name WHERE Key_name = 'PRIMARY'")->fetchAllAssoc('Column_name');
      if (empty($results)
        || empty($results['name'])
        || empty($results['value'])
        || empty($results['expire'])
      ) {
        db_drop_primary_key($table);
        db_add_primary_key($table, array('name', 'value', 'expire'));
      }

      // Unlock tables.
      db_query('UNLOCK TABLES');
      $changed = TRUE;
    }

    $collation_changed = apdqc_admin_change_table_collation_queries($table, 'ascii_bin', TRUE, array('name', 'value'));
    if ($collation_changed) {
      $changed = TRUE;
    }
    if ($show_msg !== FALSE) {
      drupal_set_message(t('APDQC: semaphore table schema has been updated.'));
    }
    variable_set('apdqc_semaphore_schema', TRUE);
  }
  return $changed;
}

/**
 * See if the sessions table needs to be updated.
 *
 * @return bool
 *   Returns TRUE if the sessions table schema has not been updated.
 */
function apdqc_admin_sessions_table_need_update() {
  $table_name = 'sessions';
  $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table_name) . '}');
  $results = db_query("SHOW FULL FIELDS FROM $table_name")->fetchAllAssoc('Field');
  $needs_update = FALSE;
  foreach ($results as $row) {
    if (($row->Field === 'sid' || $row->Field === 'ssid') && ($row->Type !== 'char(43)' || $row->Collation !== 'ascii_bin')) {
      $needs_update = TRUE;
      break;
    }
    if ($row->Field === 'hostname' && ($row->Type !== 'varchar(45)' || $row->Collation !== 'ascii_bin')) {
      $needs_update = TRUE;
      break;
    }
  }
  return $needs_update;
}

/**
 * See if the sessions table needs to be updated.
 *
 * Can alter forwards and backwards as well.
 *
 * @param bool $perform_alter
 *   Set the TRUE to alter the database.
 * @param bool $reverse
 *   Set to TRUE to revert back to standard schema.
 * @param array $schema
 *   Array of schema.
 *
 * @return array
 *   Returns empty array if a perform alter was done. Otherwise returns the
 *   schema array for the table that needs to be altered.
 */
function apdqc_admin_sessions_table_duplicates($perform_alter = FALSE, $reverse = FALSE, $schema = array()) {
  if ($reverse) {
    if (empty($schema)) {
      $schema = apdqc_get_full_schema(FALSE);
    }
    $collation = 'utf8_general_ci';
  }
  else {
    if (empty($schema)) {
      $schema = apdqc_get_full_schema(TRUE);
    }
    $collation = 'ascii_bin';
  }
  $needs_conversion = array();
  foreach ($schema as $table => $values) {
    if ($table === 'sessions') {
      continue;
    }
    foreach ($values['fields'] as $column => $attributes) {
      // See if the schema looks very simalr to sessions table.
      if (($column === 'sid' || $column === 'ssid')
        && !empty($attributes['length'])
        && $attributes['length'] >= 43
        && !empty($attributes['type'])
        && stripos($attributes['type'], 'char') !== FALSE
        && !empty($attributes['description'])
        && stripos($attributes['description'], 'session') !== FALSE
      ) {
        $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table) . '}');
        $results = db_query("SHOW FULL FIELDS FROM $table_name WHERE Field = :column", array(':column' => $column))->fetchAllAssoc('Field');
        // If yes see if the Collation is not the target collation.
        if ($results[$column]->Collation !== $collation) {
          $needs_conversion[$table] = $values;
          if ($perform_alter) {
            $columns = array($column);
            apdqc_admin_change_table_collation_queries($table, $collation, TRUE, $columns);
          }
        }
        if ($results[$column]->Type !== $schema[$table]['fields'][$column]['type'] . '(' . $schema[$table]['fields'][$column]['length'] . ')') {
          $needs_conversion[$table] = $values;
          if ($perform_alter) {
            db_change_field($table, $column, $column, $schema[$table]['fields'][$column]);
          }
        }
      }
    }
  }
  return $needs_conversion;
}

/**
 * See if the semaphore table needs to be updated.
 *
 * @return bool
 *   Returns TRUE if the semaphore table schema has not been updated.
 */
function apdqc_admin_semaphore_table_need_update() {
  $table_name = 'semaphore';
  $table_name = Database::getConnection()->prefixTables('{' . db_escape_table($table_name) . '}');
  $results = db_query("SHOW FULL FIELDS FROM $table_name")->fetchAllAssoc('Field');
  $needs_update = FALSE;
  foreach ($results as $row) {
    if (($row->Field === 'name' || $row->Field === 'value') && $row->Collation !== 'ascii_bin') {
      $needs_update = TRUE;
      break;
    }
    if (function_exists('apdqc_lock_base85_encode') && $row->Field === 'value' && $row->Type !== 'varchar(20)') {
      $needs_update = TRUE;
      break;
    }
    if (!function_exists('apdqc_lock_base85_encode') && $row->Field === 'value' && $row->Type !== 'varchar(33)') {
      $needs_update = TRUE;
      break;
    }
  }
  $results = db_query("SHOW KEYS FROM $table_name WHERE Key_name = 'PRIMARY'")->fetchAllAssoc('Column_name');
  if (count($results) != 3) {
    $needs_update = TRUE;
  }
  return $needs_update;
}

/**
 * Get all database indexes for the cache tables.
 *
 * @return array
 *   Returns an array of tables and index names.
 */
function apdqc_get_cache_table_indexes(array $cache_tables = array()) {
  if (empty($cache_tables)) {
    $cache_tables = apdqc_get_cache_tables();
  }

  $results = array();
  foreach ($cache_tables as $table_name) {
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
 * Converts a database index from one form to another.
 *
 * @param array $before
 *   List of keys that need to be removed.
 * @param array $after
 *   List of keys that will be used in the new index.
 */
function apdqc_convert_cache_index(array $before, array $after, array $cache_tables = array()) {
  $table_indexes = apdqc_get_cache_table_indexes($cache_tables);
  $before_name = implode('_', $before);
  $after_name = implode('_', $after);
  foreach ($table_indexes as $table_name => $indexes) {
    if (isset($indexes[$before_name])) {
      if (function_exists('apdqc_query')) {
        $query = "ALTER TABLE $table_name DROP INDEX `$before_name`";
        $mysqli = apdqc_query(array($table_name), array('*'), $query, array(
          'async' => TRUE,
          'log' => FALSE,
          'get_mysqli' => TRUE,
        ));
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
        $mysqli = apdqc_query(array($table_name), array('*'), $query, array(
          'async' => TRUE,
          'log' => FALSE,
          'get_mysqli' => TRUE,
        ));
        if (isset($mysqli->thread_id)) {
          apdqc_kill_metadata_lock($mysqli->thread_id);
        }
      }
      else {
        db_add_index($table_name, $after_name, $after);
      }
    }
  }
  if (function_exists('apdqc_get_db_object')) {
    apdqc_get_db_object(array(), array(), array('async' => FALSE, 'reap' => TRUE));
  }
}

/**
 * Gets the schema definition of the whole database schema.
 *
 * @param bool $alter
 *   Set to FALSE to not run drupal_alter on schema.
 *
 * @return array
 *   Returns an array of table definitions.
 */
function apdqc_get_full_schema($alter = TRUE) {
  $schema = &drupal_static(__FUNCTION__, array());

  if (!isset($schema[$alter])) {
    $schema[$alter] = array();
    module_load_all_includes('install');
    foreach (module_implements('schema') as $module) {
      $current = (array) module_invoke($module, 'schema');
      $schema[$alter] = array_merge($schema[$alter], $current);
    }
    if ($alter) {
      drupal_alter('schema', $schema[$alter]);
    }
  }
  return $schema[$alter];
}

/**
 * Returns a list of all cache tables used.
 *
 * @param bool $get_truncated
 *   Set to FALSE to not include "__truncated_table" tables in the return array.
 * @param bool $get_full_schema
 *   Set to TRUE to get the schema with descriptions.
 *
 * @return array
 *   Returns an array of cache tables.
 */
function apdqc_get_cache_tables($get_truncated = TRUE, $get_full_schema = FALSE) {
  $cache_tables = &drupal_static(__FUNCTION__, array());
  if (!isset($cache_tables[$get_truncated][$get_full_schema])) {
    if ($get_full_schema) {
      $schema = apdqc_get_full_schema();
    }
    else {
      $schema = drupal_get_schema();
    }
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
    if ($get_full_schema) {
      // Add in the cache*__truncated_table tables.
      if ($get_truncated) {
        foreach ($schema as $table_name => $values) {
          if (!array_key_exists($table_name . '__truncated_table', $schema) && db_table_exists($table_name . '__truncated_table')) {
            $schema[$table_name . '__truncated_table'] = $schema[$table_name];
          }
        }
      }
      else {
        foreach ($schema as $table_name => $values) {
          if (strpos(strrev($table_name), strrev('__truncated_table')) === 0) {
            unset($schema[$table_name]);
          }
        }
      }
      $cache_tables[$get_truncated][$get_full_schema] = $schema;
    }
    else {
      $schema = array_keys($schema);
      // Add in the cache*__truncated_table tables.
      if ($get_truncated) {
        foreach ($schema as $table_name) {
          if (!in_array($table_name . '__truncated_table', $schema) && db_table_exists($table_name . '__truncated_table')) {
            $schema[] = $table_name . '__truncated_table';
          }
        }
      }
      else {
        foreach ($schema as $key => $table_name) {
          if (strpos(strrev($table_name), strrev('__truncated_table')) === 0) {
            unset($schema[$key]);
          }
        }
      }
      $cache_tables[$get_truncated][$get_full_schema] = $schema;
    }
  }
  return $cache_tables[$get_truncated][$get_full_schema];
}
