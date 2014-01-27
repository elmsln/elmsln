<?php

/**
 * @file
 * Admin page callbacks for the advanced CSS/JS aggregation module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function advagg_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: Configuration'));

  // Simple checkbox settings.
  $form['global'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Options'),
  );
  $form['global']['advagg_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable advanced aggregation'),
    '#default_value' => variable_get('advagg_enabled', ADVAGG_ENABLED),
    '#description' => t('Uncheck this box to completely disable AdvAgg functionality.'),
  );
  $form['global']['advagg_gzip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create .gz files'),
    '#default_value' => variable_get('advagg_gzip', ADVAGG_GZIP),
    '#description' => t('All aggregated files can be pre-compressed into a .gz file and
   served from Apache. This is faster then gzipping the file on each request.'),
  );
  $form['global']['advagg_core_groups'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use cores grouping logic'),
    '#default_value' => variable_get('advagg_combine_css_media', ADVAGG_COMBINE_CSS_MEDIA) || variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER) ? FALSE : variable_get('advagg_core_groups', ADVAGG_CORE_GROUPS),
    '#description' => t('Will group files just like core does.'),
    '#states' => array(
      'enabled' => array(
        '#edit-advagg-combine-css-media' => array('checked' => FALSE),
        '#edit-advagg-ie-css-selector-limiter' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global']['advagg_use_httprl'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use HTTPRL to generate aggregates.'),
    '#default_value' => module_exists('httprl') ? variable_get('advagg_use_httprl', ADVAGG_USE_HTTPRL) : FALSE,
    '#disabled' => module_exists('httprl') ? FALSE : TRUE,
    '#description' => t('If <a href="@link">HTTPRL</a> is installed, advagg will use it to generate aggregates on the fly in a background parallel process.', array('@link' => 'http://drupal.org/project/httprl')),
  );
  $options = array(
    -1 => t('Development ~ 100ms'),
    0 => t('Disabled ~ 70ms'),
    1 => t('Normal ~ 10ms'),
    3 => t('Aggressive ~ 4ms'),
  );
  $form['global']['advagg_cache_level'] = array(
    '#type' => 'radios',
    '#title' => t('AdvAgg Cache Settings'),
    '#default_value' => variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL),
    '#options' => $options,
    '#description' => t('Development will scan all files for a change on every page load. Disabled is useful for testing hook_alters for CSS/JS. Normal is should be fine for all use cases. Aggressive might break depending on how various hook_alter for CSS/JS are implemented. As a reference, core takes about 7 ms to run.'),
  );

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Options'),
  );
  $form['css']['advagg_combine_css_media'] = array(
    '#type' => 'checkbox',
    '#title' => t('Combine CSS files by using media queries'),
    '#default_value' => variable_get('advagg_combine_css_media', ADVAGG_COMBINE_CSS_MEDIA),
    '#description' => t('Will combine more CSS files together because different CSS media types can be used in the same file by using media queries. Use cores grouping logic needs to be unchecked in order for this to work. Also noted is that due to an issue with IE9, compatibility mode is forced off if this is enabled.'),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-core-groups' => array('checked' => TRUE),
      ),
    ),
  );
  $form['css']['advagg_ie_css_selector_limiter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Prevent more than 4095 CSS selectors in an aggregated CSS file'),
    '#default_value' => variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER),
    '#description' => t('Internet Explorer before version 10; IE9, IE8, IE7, & IE6 all have 4095 as the limit for the maximum number of css selectors that can be in a file. Enabling this will prevent CSS aggregates from being created that exceed this limit. <a href="@link">More info</a>. Use cores grouping logic needs to be unchecked in order for this to work.', array('@link' => 'http://blogs.msdn.com/b/ieinternals/archive/2011/05/14/10164546.aspx')),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-core-groups' => array('checked' => TRUE),
      ),
    ),
  );
  $form['css']['advagg_css_fix_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix improperly set type'),
    '#default_value' => variable_get('advagg_css_fix_type', ADVAGG_CSS_FIX_TYPE),
    '#description' => t('If type is external but does not start with http, https, or // change it to be type file. If type is file but it starts with http, https, or // change type to be external.'),
  );
  $form['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Options'),
  );
  $form['js']['advagg_js_fix_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix improperly set type'),
    '#default_value' => variable_get('advagg_js_fix_type', ADVAGG_JS_FIX_TYPE),
    '#description' => t('If type is external but does not start with http, https, or // change it to be type file. If type is file but it starts with http, https, or // change type to be external.'),
  );

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Form builder; Do advagg operations.
 *
 * @ingroup forms
 */
function advagg_admin_operations_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: Operations'));

  // Buttons to do stuff.
  // Smart flushing.
  $form['smart_flush'] = array(
    '#type' => 'fieldset',
    '#title' => t('Smart Cache Flush'),
    '#description' => t('Scan all files referenced in aggregated files. If any of them have changed, clear that cache so the changes will go out.'),
  );
  $form['smart_flush']['advagg_flush'] = array(
    '#type' => 'submit',
    '#value' => t('Flush AdvAgg Cache'),
    '#submit' => array('advagg_admin_flush_cache_button'),
  );
  $form['smart_flush']['output'] = array(
    '#markup' => '<p>' . t('The following 3 functions get ran on cron but you can run them manually here.') . '</p>',
  );
  $form['smart_flush']['smart_file_flush'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear All Stale Files'),
    '#description' => t('Remove all stale files. Scan all files in the advagg_css/js directories and remove the ones that have not been accessed in the last 30 days.'),
  );
  $form['smart_flush']['smart_file_flush']['advagg_flush_stale_files'] = array(
    '#type' => 'submit',
    '#value' => t('Remove All Stale Files'),
    '#submit' => array('advagg_admin_flush_stale_files_button'),
  );
  $form['smart_flush']['remove_missing_files'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear Missing Files From Database'),
    '#description' => t('Scan for missing files and remove the associated entries in the database.'),
  );
  $form['smart_flush']['remove_missing_files']['advagg_remove_missing_files_from_db'] = array(
    '#type' => 'submit',
    '#value' => t('Clear Missing Files From Database'),
    '#submit' => array('advagg_admin_remove_missing_files_from_db_button'),
  );
  $form['smart_flush']['remove_old_aggregates'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Delete Unused Aggregates From Database'),
    '#description' => t('Delete aggregates that have not been accessed in the last 6 weeks.'),
  );
  $form['smart_flush']['remove_old_aggregates']['advagg_remove_old_unused_aggregates'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Unused Aggregates From Database'),
    '#submit' => array('advagg_admin_remove_old_unused_aggregates_button'),
  );

  // Set/Remove Bypass Cookie.
  $form['bypass'] = array(
    '#type' => 'fieldset',
    '#title' => t('Aggregation Bypass Cookie'),
    '#description' => t('This will set or remove a cookie that disables aggregation for the remainder of the browser session.'),
  );
  $form['bypass']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Toggle the "aggregation bypass cookie" for this browser'),
    '#attributes' => array('onclick' => 'javascript:return advagg_toggle_cookie()'),
    '#submit' => array('advagg_admin_toggle_bypass_cookie'),
  );
  // Add in aggregation bypass cookie javascript.
  $form['#attached']['js'][] = array(
    'data' => array('advagg' => array('key' => drupal_hash_base64(drupal_get_private_key()))),
    'type' => 'setting',
  );
  $form['#attached']['js'][] = drupal_get_path('module', 'advagg') . '/advagg.admin.js';

  // Hide drastic measures as they should not be done unless you really need it.
  $form['drastic_measures'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Drastic Measures'),
    '#description' => t('The options below should normally never need to be done.'),
  );
  $form['drastic_measures']['dumb_cache_flush'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear All Caches'),
    '#description' => t('Remove all entries from the advagg cache bins. Useful if you suspect a cache is not getting cleared.'),
  );
  $form['drastic_measures']['dumb_cache_flush']['advagg_flush_all_caches'] = array(
    '#type' => 'submit',
    '#value' => t('Clear All Caches'),
    '#submit' => array('advagg_admin_clear_all_caches_button'),
  );
  $form['drastic_measures']['dumb_file_flush'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear All Files'),
    '#description' => t('Remove all generated files. Useful if you think some of the generated files got corrupted and thus need to be deleted.'),
  );
  $form['drastic_measures']['dumb_file_flush']['advagg_flush_all_files'] = array(
    '#type' => 'submit',
    '#value' => t('Remove All Generated Files'),
    '#submit' => array('advagg_admin_clear_all_files_button'),
  );
  $form['drastic_measures']['force_change'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Force new aggregates'),
    '#description' => t('Force the creation of all new aggregates by incrementing a global counter. Current value of counter: %value. This is useful if a CDN has cached an aggregate incorrectly as it will force new ones to be used even if nothing else has changed.', array('%value' => advagg_get_global_counter())),
  );
  $form['drastic_measures']['force_change']['increment_global_counter'] = array(
    '#type' => 'submit',
    '#value' => t('Increment Global Counter'),
    '#submit' => array('advagg_admin_increment_global_counter'),
  );

  return $form;
}

/**
 * Form builder; Show info about advagg and advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function advagg_admin_info_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: Information'));

  // Get all hooks.
  drupal_theme_initialize();
  $core_hooks = theme_get_registry();
  $advagg_hooks = advagg_hooks_implemented();

  // Output html process functions hooks.
  $form['info'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Hook Theme Info'),
  );
  $data = implode("\n", $core_hooks['html']['process functions']);
  $form['info']['advagg_debug_info'] = array(
    '#markup' => '<pre>' . $data . '</pre>',
  );

  // Get all parent css and js files.
  $types = array('css', 'js');
  foreach ($types as $type) {
    $form[$type] = array(
      '#type' => 'fieldset',
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#title' => t('@type files', array('@type' => drupal_strtoupper($type))),
    );
    // Get filename, filename_hash, and changes.
    $results = db_select('advagg_files', 'af')
      ->fields('af', array('filename', 'filename_hash', 'changes'))
      ->condition('filetype', $type)
      ->execute();
    while ($row = $results->fetchAssoc()) {
      $form[$type][$row['filename_hash']] = array(
        '#markup' => '<div>' . format_plural($row['changes'], 'changed 1 time - %file<br />', 'changed %changes times - %file<br /></div>',    array(
          '%changes' => $row['changes'],
          '%file' => $row['filename'],
        )),
      );
    }
  }

  // Display as module -> hook instead of hook -> module.
  ksort($advagg_hooks);
  $module_hooks = array();
  foreach ($advagg_hooks as $hook => $values) {
    if (!empty($values)) {
      foreach ($values as $module_name) {
        if (!isset($module_hooks[$module_name])) {
          $module_hooks[$module_name] = array();
        }
        $module_hooks[$module_name][] = $hook;
      }
    }
    else {
      $module_hooks['not in use'][] = $hook;
    }
  }
  ksort($module_hooks);

  // Output all advagg hooks implemented.
  foreach ($module_hooks as $hook => $values) {
    if (empty($values)) {
      $form['modules_implementing_advagg'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> 0</div>',
      );
    }
    else {
      $form['modules_implementing_advagg'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> ' . count($values) . '<br />&nbsp;&nbsp;' . filter_xss(implode('<br />&nbsp;&nbsp;', $values), array('br')) . '</div>',
      );
    }
  }
  $form['modules_implementing_advagg'] += array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Modules implementing AdvAgg CSS/JS hooks'),
  );

  // Output all advagg hooks implemented.
  foreach ($advagg_hooks as $hook => $values) {
    if (empty($values)) {
      $form['hooks_implemented'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> 0</div>',
      );
    }
    else {
      $form['hooks_implemented'][$hook] = array(
        '#markup' => '<div><strong>' . check_plain($hook) . ':</strong> ' . count($values) . '<br />&nbsp;&nbsp;' . filter_xss(implode('<br />&nbsp;&nbsp;', $values), array('br')) . '</div>',
      );
    }
  }
  $form['hooks_implemented'] += array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('AdvAgg CSS/JS hooks implemented by modules'),
  );

  // Output what is used inside of the advagg_get_current_hooks_hash() function.
  $form['hooks_variables_hash'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Hooks And Variables Used In Hash'),
  );
  $form['hooks_variables_hash']['description'] = array(
    '#markup' => t('Current Value: %value. Below is the listing of variables and hooks used to generate the 3rd hash of an aggregates filename.', array('%value' => advagg_get_current_hooks_hash())),
  );
  $form['hooks_variables_hash']['output'] = array(
    '#markup' => '<pre>' . print_r(advagg_current_hooks_hash_array(), TRUE) . '</pre>'
  );

  // Get info about a file.
  $form['get_info_about_agg'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#title' => t('Get detailed info about an aggregate file'),
  );
  $form['get_info_about_agg']['filename'] = array(
    '#type' => 'textfield',
    '#size' => 170,
    '#maxlength' => 256,
    '#default_value' => '',
    '#title' => t('Filename'),
  );
  $form['get_info_about_agg']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Lookup Details'),
    '#submit' => array('advagg_admin_get_file_info_submit'),
    '#validate' => array('advagg_admin_get_file_info_validate'),
    "#ajax" => array(
      "callback" => "advagg_admin_get_file_info_callback",
      "wrapper" => "advagg-file-info-ajax",
      "effect" => "fade",
    ),
  );
  $form['get_info_about_agg']["wrapper"] = array(
    "#markup" => "<div id='advagg-file-info-ajax'></div>",
  );

  return $form;
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 */
function advagg_admin_settings_form_submit($form, &$form_state) {
  $cache_bins = advagg_flush_caches();
  foreach ($cache_bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
  }
}

// Callbacks for buttons.
/**
 * Set or remove the AdvAggDisabled cookie.
 */
function advagg_admin_toggle_bypass_cookie() {
  $cookie_name = 'AdvAggDisabled';
  $key = drupal_hash_base64(drupal_get_private_key());

  // If the cookie does exist then remove it.
  if (!empty($_COOKIE[$cookie_name]) && $_COOKIE[$cookie_name] == $key) {
    setcookie($cookie_name, '', -1, $GLOBALS['base_path'], '.' . $_SERVER['HTTP_HOST']);
    unset($_COOKIE[$cookie_name]);
    drupal_set_message(t('AdvAgg Bypass Cookie Removed.'));
  }
  // If the cookie does not exist then set it.
  else {
    // Cookie will last for 12 hours.
    setcookie($cookie_name, $key, REQUEST_TIME+60*60*12, $GLOBALS['base_path'], '.' . $_SERVER['HTTP_HOST']);
    $_COOKIE[$cookie_name] = $key;
    drupal_set_message(t('AdvAgg Bypass Cookie Set.'));
  }
}

/**
 * Display file info in a drupal message.
 */
function advagg_admin_get_file_info_submit($form, &$form_state) {
  if (!empty($form_state['input']['ajax_page_state'])) {
    return;
  }
  $info = advagg_admin_get_file_info($form_state['values']['filename']);
  if (module_exists('httprl')) {
    $output = httprl_pr($info);
  }
  else {
    $output = '<pre>' . check_plain(print_r($info, TRUE)) . '</pre>';
  }
  drupal_set_message($output);
}

/**
 * Display file info via ajax callback.
 */
function advagg_admin_get_file_info_callback($form, &$form_state) {
  if (!empty($form_state['values']['error'])) {
    return '<div id="advagg-file-info-ajax"></div>';
  }
  $info = advagg_admin_get_file_info($form_state['values']['filename']);
  if (empty($info)) {
    form_set_error('filename', 'Please input a valid aggregate filename.');
    return '<div id="advagg-file-info-ajax"></div>';
  }
  else {
    if (module_exists('httprl')) {
      $output = httprl_pr($info);
    }
    else {
      $output = '<pre>' . print_r($info, TRUE) . '</pre>';
    }
    return '<div id="advagg-file-info-ajax">' . $output . '</div>';
  }
}

/**
 * Verify that the filename is correct.
 */
function advagg_admin_get_file_info_validate($form, &$form_state) {
  if (empty($form_state['values']['filename'])) {
    form_set_error('filename', 'Please input an aggregate filename.');
    $form_state['values']['error'] = TRUE;
  }
}

/**
 * Get detailed info about the given filename.
 *
 * @param $filename
 *   Name of file to lookup.
 * @return array
 *   Returns an array of detailed info about this file.
 */
function advagg_admin_get_file_info($filename) {
  module_load_include('inc', 'advagg', 'advagg.missing');
  module_load_include('inc', 'advagg', 'advagg');

  $data = advagg_get_hashes_from_filename($filename);
  $output = array();
  if (is_array($data)) {
    list($type, $aggregate_filenames_hash, $aggregate_contents_hash, $aggregate_settings) = $data;

    // Get a list of files.
    $files = advagg_get_files_from_hashes($type, $aggregate_filenames_hash, $aggregate_contents_hash);
    $data['files'] = $files;

    // Get detailed info on each file.
    foreach ($data['files'] as $filename => &$info) {
      $info += advagg_get_info_on_file($filename);
      if (module_exists('advagg_bundler')) {
        $bundler = advagg_bundler_analysis($filename);
        $info['group_hash'] = $bundler['group_hash'];
      }
    }
    $output = $data;
  }
  else {
    $results = db_select('advagg_files', 'af')
      ->fields('af')
      ->condition('filename', '%' . db_like($filename), 'LIKE')
      ->execute();
    while ($row = $results->fetchAssoc()) {
      $row += advagg_get_info_on_file($row['filename']);
      if (module_exists('advagg_bundler')) {
        $bundler = advagg_bundler_analysis($row['filename']);
        $row['group_hash'] = $bundler['group_hash'];
      }
      $output[] = $row;
    }
  }
  return $output;
}

/**
 * Perform a smart flush.
 */
function advagg_admin_flush_cache_button() {
  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  $flushed = advagg_push_new_changes();

  // Report back the results.
  if (empty($flushed)) {
    drupal_set_message(t('No changes found. Nothing was cleared.'));
    return;
  }
  foreach ($flushed as $filename => $data) {
    $ext = pathinfo($filename, PATHINFO_EXTENSION);
    drupal_set_message(t('The file %filename has changed. %db_usage aggregates are using this file. %db_count db cache entries and all %type full cache entries have been flushed from the cache bins.', array(
      '%filename' => $filename,
      '%db_usage' => count($data[0]),
      '%db_count' => count($data[1]),
      '%type' => $ext,
    )));
  }
}

/**
 * Clear out all advagg cache bins.
 */
function advagg_admin_clear_all_caches_button() {
  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  advagg_flush_all_cache_bins();

  // Report back the results.
  drupal_set_message(t('All AdvAgg cache bins have been cleared.'));
}

/**
 * Clear out all advagg cache bins and clear out all advagg aggregated files.
 */
function advagg_admin_clear_all_files_button() {
  // Clear out the cache.
  advagg_admin_clear_all_caches_button();

  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  list($css_files, $js_files) = advagg_remove_all_aggregated_files();

  // Report back the results.
  drupal_set_message(t('All AdvAgg files have been deleted. %css_count CSS files and %js_count JS files have been removed.', array(
    '%css_count' => count($css_files),
    '%js_count' => count($js_files),
  )));
}

/**
 * Clear out all stale advagg aggregated files.
 */
function advagg_admin_flush_stale_files_button() {
  // Run the command.
  module_load_include('inc', 'advagg', 'advagg.cache');
  list($css_files, $js_files) = advagg_delete_stale_aggregates();

  // Report back the results.
  if (count($css_files) > 0 || count($js_files) > 0) {
    drupal_set_message(t('All stale aggregates have been deleted. %css_count CSS files and %js_count JS files have been removed.', array(
      '%css_count' => count($css_files),
      '%js_count' => count($js_files),
    )));
  }
  else {
    drupal_set_message(t('No stale aggregates found. Nothing was deleted.'));
  }
}

/**
 * Clear out all advagg cache bins and increment the counter.
 */
function advagg_admin_increment_global_counter() {
  // Clear out the cache.
  advagg_admin_clear_all_caches_button();

  // Increment counter.
  module_load_include('inc', 'advagg', 'advagg.cache');
  $new_value = advagg_increment_global_counter();
  drupal_set_message(t('Global counter is now set to %new_value', array('%new_value' => $new_value)));
}

/**
 *  Scan for missing files and remove the associated entries in the database.
 */
function advagg_admin_remove_missing_files_from_db_button() {
  module_load_include('inc', 'advagg', 'advagg.cache');

  // Remove aggregates that include missing files.
  $deleted = advagg_remove_missing_files_from_db();
  if (empty($deleted)) {
    drupal_set_message(t('No missing files found and/or could be safely cleared out of the database.'));
  }
  else {
    drupal_set_message(t('Some missing files were found and could be safely cleared out of the database. <pre> @raw </pre>', array('@raw' => print_r($deleted, TRUE))));
  }
}

/**
 * Delete aggregates that have not been accessed in the last 6 weeks.
 */
function advagg_admin_remove_old_unused_aggregates_button() {
  module_load_include('inc', 'advagg', 'advagg.cache');

  // Remove unused aggregates.
  $count = advagg_remove_old_unused_aggregates();
  if (empty($count)) {
    drupal_set_message(t('No old and unused aggregates found. Nothing was deleted.'));
  }
  else {
    drupal_set_message(t('Some old and unused aggregates were found. A total of %count database entries were removed.', array('%count' => $count)));
  }
}
