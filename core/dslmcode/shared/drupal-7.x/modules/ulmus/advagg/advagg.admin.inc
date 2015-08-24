<?php

/**
 * @file
 * Admin page callbacks for the advanced CSS/JS aggregation module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function advagg_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: Configuration'));
  $config_path = advagg_admin_config_root_path();

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
  $form['global']['advagg_browser_dns_prefetch'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use DNS Prefetch for external CSS/JS.'),
    '#default_value' => variable_get('advagg_browser_dns_prefetch', ADVAGG_BROWSER_DNS_PREFETCH),
    '#description' => t('Start the DNS lookup for external CSS and JavaScript files as soon as possible.'),
  );

  $aggressive_cache_conflicts = advagg_aggressive_cache_conflicts();
  if (empty($aggressive_cache_conflicts)) {
    $description = t('It appears that there are no incompatible modules, so you should be able to safely use the Aggressive cache.');
  }
  else {
    $description = t('It appears that there might be some incompatible modules. I would test these out before setting the cache to aggressive: %modules', array('%modules' => implode(', ', $aggressive_cache_conflicts)));
  }
  $options = array(
    -1 => t('Development ~ 300ms'),
    1 => t('Normal ~ 60ms'),
    3 => t('Render Cache ~ 30ms'),
    5 => t('Aggressive Render Cache ~ 10ms'),
  );
  $form['global']['advagg_cache_level'] = array(
    '#type' => 'radios',
    '#title' => t('AdvAgg Cache Settings'),
    '#default_value' => variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL),
    '#options' => $options,
    '#description' => t("As a reference, core takes about 25 ms to run. Development will scan all files for a change on every page load. Normal and the render cache is fine for all use cases. Aggressive should be fine for most use cases. If your inline css/js changes based off of a variable then the cache hit ratio will be low; if that is the case consider using Drupal.settings for a better cache hit ratio when using the render cache. The aggressive render cache will cache the output from js_alter and css_alter.", array(
      '@information' => url($config_path . '/advagg/info', array(
        'fragment' => 'edit-hooks-implemented',
      )),
    )) . ' ' . $description,
  );

  $form['global']['dev_container'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_cache_level"]' => array('value' => '-1'),
      ),
    ),
  );
  // Show msg about advagg css compress.
  if (module_exists('advagg_css_compress') && (variable_get('advagg_css_compressor', ADVAGG_CSS_COMPRESSOR) > 0 || variable_get('advagg_css_compress_inline', ADVAGG_CSS_COMPRESS_INLINE))) {
    $form['global']['dev_container']['advagg_css_compress_msg'] = array(
      '#markup' => '<p>' . t('The <a href="@css">AdvAgg CSS Compression module</a> is disabled when in development mode.', array('@css' => url($config_path . '/advagg/css-compress'))) . '</p>',
    );
  }
  // Show msg about advagg js compress.
  if (module_exists('advagg_js_compress') && (variable_get('advagg_js_compressor', ADVAGG_JS_COMPRESSOR) || variable_get('advagg_js_compress_inline', ADVAGG_JS_COMPRESS_INLINE))) {
    $form['global']['dev_container']['advagg_js_compress_msg'] = array(
      '#markup' => '<p>' . t('The <a href="@js">AdvAgg JS Compression module</a> is disabled when in development mode.', array('@js' => url($config_path . '/advagg/js-compress'))) . '</p>',
    );
  }

  // Show msg about the jquery update compression setting.
  if (module_exists('jquery_update')) {
    if (variable_get('jquery_update_compression_type', 'min') === 'min') {
      $form['global']['dev_container']['advagg_jquery_update_development'] = array(
        '#markup' => '<p>' . t('You might want to change the <a href="!url">jQuery update compression level</a> to "Development" as well.', array(
          '!url' => url('admin/config/development/jquery_update'),
        )) . '</p>',
      );
    }
    else {
      $form['global']['prod_container'] = array(
        '#type' => 'container',
        '#states' => array(
          'visible' => array(
            ':input[name="advagg_cache_level"]' => array('!value' => '-1'),
          ),
        ),
      );
      $form['global']['prod_container']['advagg_jquery_update_development'] = array(
        '#markup' => '<p>' . t('You might want to change the <a href="!url">jQuery update compression level</a> to "Production" as well.', array(
          '!url' => url('admin/config/development/jquery_update'),
        )) . '</p>',
      );
    }
  }

  $form['global']['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Unless you have a good reason to adjust these values you should leave them alone.'),
  );
  // @ignore sniffer_squiz_commenting_poststatementcomment_found:27
  $short_times = drupal_map_assoc(array(
    60 * 15, // 15 min.
    60 * 30, // 30 min.
    60 * 45, // 45 min.
    60 * 60, // 1 hour.
    60 * 60 * 2, // 2 hours.
    60 * 60 * 4, // 4 hours.
    60 * 60 * 6, // 6 hours.
    60 * 60 * 8, // 8 hours.
    60 * 60 * 10, // 10 hours.
    60 * 60 * 12, // 12 hours.
    60 * 60 * 18, // 18 hours.
    60 * 60 * 24, // 1 day.
    60 * 60 * 24 * 2, // 2 days.
  ), 'format_interval');
  $long_times = drupal_map_assoc(array(
    60 * 60 * 24 * 2, // 2 days.
    60 * 60 * 24 * 3, // 3 days.
    60 * 60 * 24 * 4, // 4 days.
    60 * 60 * 24 * 5, // 5 days.
    60 * 60 * 24 * 6, // 6 days.
    60 * 60 * 24 * 7, // 1 week.
    60 * 60 * 24 * 7 * 2, // 2 weeks.
    60 * 60 * 24 * 7 * 3, // 3 weeks.
    60 * 60 * 24 * 30, // 1 month.
    60 * 60 * 24 * 45, // 1 month 2 weeks.
    60 * 60 * 24 * 60, // 2 months.
  ), 'format_interval');
  $last_ran = variable_get('advagg_cron_timestamp', 0);
  if (!empty($last_ran)) {
    $last_ran = t('@time ago', array('@time' => format_interval(REQUEST_TIME - $last_ran)));
  }
  else {
    $last_ran = t('never');
  }
  $form['global']['cron']['advagg_cron_frequency'] = array(
    '#type' => 'select',
    '#options' => $short_times,
    '#title' => 'Minimum amount of time between advagg_cron() runs.',
    '#default_value' => variable_get('advagg_cron_frequency', ADVAGG_CRON_FREQUENCY),
    '#description' => t('The default value for this is %value. The last time advagg_cron was ran is %time.', array(
      '%value' => format_interval(ADVAGG_CRON_FREQUENCY),
      '%time' => $last_ran,
    )),
  );
  $form['global']['cron']['drupal_stale_file_threshold'] = array(
    '#type' => 'select',
    '#options' => $long_times,
    '#title' => 'Delete aggregates accessed/modified more than a set time ago.',
    '#default_value' => variable_get('drupal_stale_file_threshold', 2592000),
    '#description' => t('The default value for this is %value.', array('%value' => format_interval(2592000))),
  );
  $form['global']['cron']['advagg_remove_missing_files_from_db_time'] = array(
    '#type' => 'select',
    '#options' => $long_times,
    '#title' => 'How long to wait until unaccessed aggregates with missing files are removed from the database.',
    '#default_value' => variable_get('advagg_remove_missing_files_from_db_time', ADVAGG_REMOVE_MISSING_FILES_FROM_DB_TIME),
    '#description' => t('The default value for this is %value.', array('%value' => format_interval(ADVAGG_REMOVE_MISSING_FILES_FROM_DB_TIME))),
  );
  $form['global']['cron']['advagg_remove_old_unused_aggregates_time'] = array(
    '#type' => 'select',
    '#options' => $long_times,
    '#title' => 'How long to wait until unaccessed aggregates are removed from the database.',
    '#default_value' => variable_get('advagg_remove_old_unused_aggregates_time', ADVAGG_REMOVE_OLD_UNUSED_AGGREGATES_TIME),
    '#description' => t('The default value for this is %value.', array('%value' => format_interval(ADVAGG_REMOVE_OLD_UNUSED_AGGREGATES_TIME))),
  );

  $form['global']['obscure'] = array(
    '#type' => 'fieldset',
    '#title' => t('Obscure Options'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Some of the more obscure AdvAgg settings. Odds are you do not need to change anything in here.'),
  );
  $form['global']['obscure']['advagg_gzip'] = array(
    '#type' => 'checkbox',
    '#title' => t('Create .gz files'),
    '#default_value' => variable_get('advagg_gzip', ADVAGG_GZIP),
    '#description' => t('All aggregated files can be pre-compressed into a .gz file and
   served from Apache. This is faster then gzipping the file on each request.'),
  );
  $form['global']['obscure']['advagg_ajax_render_alter'] = array(
    '#type' => 'checkbox',
    '#title' => t('Run advagg_ajax_render_alter()'),
    '#default_value' => variable_get('advagg_ajax_render_alter', ADVAGG_AJAX_RENDER_ALTER),
    '#description' => t('If disabled, AdvAgg will not alter the aggregates returned by ajax requests.'),
  );
  $form['global']['obscure']['advagg_include_base_url'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include the base_url variable in the hooks hash array.'),
    '#default_value' => variable_get('advagg_include_base_url', ADVAGG_INCLUDE_BASE_URL),
    '#description' => t('If you would like a unique set of aggregates for every permutation of the base_url (current value: %value) then enable this setting. <a href="@issue">Read more</a>.', array(
      '%value' => $GLOBALS['base_url'],
      '@issue' => 'https://www.drupal.org/node/2353811',
    )),
  );
  $form['global']['obscure']['advagg_convert_absolute_to_relative_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert absolute paths to be self references.'),
    '#default_value' => variable_get('advagg_convert_absolute_to_relative_path', ADVAGG_CONVERT_ABSOLUTE_TO_RELATIVE_PATH),
    '#description' => t('If the src to a CSS/JS file points to this domain, convert the absolute path to a relative path. Will also convert url() references inside of css files. This is generally safe unless the drupal page will be embedded, like it is when used as an iframe.'),
  );
  $form['global']['obscure']['advagg_convert_absolute_to_protocol_relative_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert absolute paths to be protocol relative paths.'),
    '#default_value' => variable_get('advagg_convert_absolute_to_protocol_relative_path', ADVAGG_CONVERT_ABSOLUTE_TO_PROTOCOL_RELATIVE_PATH),
    '#description' => t('If the src to a CSS/JS file points starts with http:// or https://, convert it to use a protocol relative path //. Will also convert url() references inside of css files. This is incompatible with IE6 and might cause extra bandwidth usage in IE7 and IE8 in regards to url() statements inside css files. According to <a href="@url">current web browser market share</a> IE 6 is less than 0.2% of the total number of browsers in use and IE 7+8 make up under 5% of browsers in use.', array(
      '@url' => 'http://www.w3counter.com/trends',
    )),
    '#states' => array(
      'enabled' => array(
        '#edit-advagg-force-https-path' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global']['obscure']['advagg_force_https_path'] = array(
    '#type' => 'checkbox',
    '#title' => t('Convert http:// to https://.'),
    '#default_value' => variable_get('advagg_force_https_path', ADVAGG_FORCE_HTTPS_PATH),
    '#description' => t('If the src to a CSS/JS file starts with http:// convert it https://. Will also convert url() references inside of css files.'),
    '#states' => array(
      'enabled' => array(
        '#edit-advagg-convert-absolute-to-protocol-relative-path' => array('checked' => FALSE),
      ),
    ),
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
    '#title' => t('Prevent more than %limit CSS selectors in an aggregated CSS file', array('%limit' => variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE))),
    '#default_value' => variable_get('advagg_ie_css_selector_limiter', ADVAGG_IE_CSS_SELECTOR_LIMITER),
    '#description' => t('Internet Explorer before version 10; IE9, IE8, IE7, and IE6 all have 4095 as the limit for the maximum number of css selectors that can be in a file. Enabling this will prevent CSS aggregates from being created that exceed this limit. <a href="@link">More info</a>. Use cores grouping logic needs to be unchecked in order for this to work.', array('@link' => 'http://blogs.msdn.com/b/ieinternals/archive/2011/05/14/10164546.aspx')),
    '#states' => array(
      'disabled' => array(
        '#edit-advagg-core-groups' => array('checked' => TRUE),
      ),
    ),
  );
  $form['css']['advagg_ie_css_selector_limiter_value'] = array(
    '#type' => 'textfield',
    '#title' => t('The selector count the IE CSS limiter should use'),
    '#default_value' => variable_get('advagg_ie_css_selector_limiter_value', ADVAGG_IE_CSS_SELECTOR_LIMITER_VALUE),
    '#description' => t('Internet Explorer before version 10; IE9, IE8, IE7, and IE6 all have 4095 as the limit for the maximum number of css selectors that can be in a file. Use this field to modify the value used; 4095 sometimes may be still be too many with media queries.'),
    '#states' => array(
      'visible' => array(
        '#edit-advagg-ie-css-selector-limiter' => array('checked' => TRUE),
      ),
      'disabled' => array(
        '#edit-advagg-ie-css-selector-limiter' => array('checked' => FALSE),
      ),
    ),
  );
  $form['css']['advagg_css_fix_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix improperly set type'),
    '#default_value' => variable_get('advagg_css_fix_type', ADVAGG_CSS_FIX_TYPE),
    '#description' => t('If type is external but does not start with http, https, or // change it to be type file. If type is file but it starts with http, https, or // change type to be external. Note that if this is causing issues, odds are you have a double slash when there should be a single; see <a href="@link">this issue</a>', array(
      '@link' => 'https://www.drupal.org/node/2336217',
    )),
  );

  $form['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Options'),
  );
  $form['js']['advagg_js_fix_type'] = array(
    '#type' => 'checkbox',
    '#title' => t('Fix improperly set type'),
    '#default_value' => variable_get('advagg_js_fix_type', ADVAGG_JS_FIX_TYPE),
    '#description' => t('If type is external but does not start with http, https, or // change it to be type file. If type is file but it starts with http, https, or // change type to be external. Note that if this is causing issues, odds are you have a double slash when there should be a single; see <a href="@link">this issue</a>', array(
      '@link' => 'https://www.drupal.org/node/2336217',
    )),
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

  // Explain what can be done on this page.
  $form['tip'] = array(
    '#markup' => '<p>' . t('This is a collection of commands to control the cache and to manage testing of this module. In general this page is useful when troubleshooting some aggregation issues. For normal operations, you do not need to do anything on this page below the Smart Cache Flush. There are no configuration options here.') . '</p>',
  );

  // Buttons to do stuff.
  // AdvAgg smart cache flushing.
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

  // Set/Remove Bypass Cookie.
  $form['bypass'] = array(
    '#type' => 'fieldset',
    '#title' => t('Aggregation Bypass Cookie'),
    '#description' => t('This will set or remove a cookie that disables aggregation for a set period of time.'),
  );
  $bypass_length = drupal_map_assoc(array(
    60 * 60 * 6,
    60 * 60 * 12,
    60 * 60 * 24,
    60 * 60 * 24 * 2,
    60 * 60 * 24 * 7,
    60 * 60 * 24 * 30,
    60 * 60 * 24 * 365,
  ), 'format_interval');
  $form['bypass']['timespan'] = array(
    '#type' => 'select',
    '#title' => 'Bypass length',
    '#options' => $bypass_length,
  );
  $form['bypass']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Toggle The "aggregation bypass cookie" For This Browser'),
    '#attributes' => array('onclick' => 'javascript:return advagg_toggle_cookie()'),
    '#submit' => array('advagg_admin_toggle_bypass_cookie'),
  );
  // Add in aggregation bypass cookie javascript.
  $form['#attached']['js'][] = array(
    'data' => array('advagg' => array('key' => drupal_hash_base64(drupal_get_private_key()))),
    'type' => 'setting',
  );
  $form['#attached']['js'][] = drupal_get_path('module', 'advagg') . '/advagg.admin.js';

  // Tasks run by cron.
  $form['cron'] = array(
    '#type' => 'fieldset',
    '#title' => t('Cron Maintenance Tasks'),
    '#description' => t('The following 4 operations are ran on cron but you can run them manually here.'),
  );
  $form['cron']['smart_file_flush'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear All Stale Files'),
    '#description' => t('Remove all stale files. Scan all files in the advagg_css/js directories and remove the ones that have not been accessed in the last 30 days.'),
  );
  $form['cron']['smart_file_flush']['advagg_flush_stale_files'] = array(
    '#type' => 'submit',
    '#value' => t('Remove All Stale Files'),
    '#submit' => array('advagg_admin_flush_stale_files_button'),
  );
  $form['cron']['remove_missing_files'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear Missing Files From Database'),
    '#description' => t('Scan for missing files and remove the associated entries in the database.'),
  );
  $form['cron']['remove_missing_files']['advagg_remove_missing_files_from_db'] = array(
    '#type' => 'submit',
    '#value' => t('Clear Missing Files From Database'),
    '#submit' => array('advagg_admin_remove_missing_files_from_db_button'),
  );
  $form['cron']['remove_old_aggregates'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Delete Unused Aggregates From Database'),
    '#description' => t('Delete aggregates that have not been accessed in the last 6 weeks.'),
  );
  $form['cron']['remove_old_aggregates']['advagg_remove_old_unused_aggregates'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Unused Aggregates From Database'),
    '#submit' => array('advagg_admin_remove_old_unused_aggregates_button'),
  );
  $form['cron']['cleanup_semaphore_table'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Delete Orphaned Semaphore Locks'),
    '#description' => t('Delete orphaned/expired advagg locks from the semaphore database table.'),
  );
  $form['cron']['cleanup_semaphore_table']['advagg_cleanup_semaphore_table'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Unused Aggregates From Database'),
    '#submit' => array('advagg_admin_cleanup_semaphore_table_button'),
  );

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
 *
 * @see system_settings_form()
 */
function advagg_admin_info_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: Information'));

  // Explain what can be done on this page.
  $form['tip'] = array(
    '#markup' => '<p>' . t('This page provides debugging information. There are no configuration options here.') . '</p>',
  );

  // Get all hooks and variables.
  drupal_theme_initialize();
  $core_hooks = theme_get_registry();
  $advagg_hooks = advagg_hooks_implemented();
  list(, $js_path) = advagg_get_root_files_dir();

  // Output html process functions hooks.
  $form['theme_info'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Hook Theme Info'),
  );
  $data = implode("\n", $core_hooks['html']['process functions']);
  $form['theme_info']['advagg_theme_info'] = array(
    '#markup' => '<pre>' . $data . '</pre>',
  );

  $form['render_info'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Hook Render Info'),
  );
  $element_info = array();
  $element_info['scripts'] = element_info('scripts');
  $element_info['styles'] = element_info('styles');
  $output = '';
  foreach ($element_info as $type => &$values) {
    $output .= $type . ":\n";
    foreach ($values as $key => &$value) {
      if ($key === '#items' || $key === '#type') {
        continue;
      }
      if (empty($value)) {
        $output .= '  ' . $key . ' - ' . str_replace(array("\r", "\n"), '', (string) var_export($value, TRUE)) . "\n";
      }
      elseif (is_array($value)) {
        $output .= '  ' . $key . ' - ' . implode(', ', $value) . "\n";
      }
      else {
        $output .= '  ' . $key . ' - ' . print_r($value, TRUE) . "\n";
      }
    }
  }
  $form['render_info']['advagg_render_info'] = array(
    '#markup' => '<pre>' . $output . '</pre>',
  );

  // Get all parent css and js files.
  $types = array('css', 'js');
  $css_file = '';
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
      if (empty($css_file) && $type === 'css') {
        $css_file = basename($row['filename']);
      }

      $form[$type][$row['filename_hash']] = array(
        '#markup' => '<div>' . format_plural($row['changes'], 'changed 1 time - %file<br />', 'changed %changes times - %file<br /></div>', array(
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
    // @ignore production_php
    '#markup' => '<pre>' . print_r(advagg_current_hooks_hash_array(), TRUE) . '</pre>',
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
    '#ajax' => array(
      'callback' => 'advagg_admin_get_file_info_callback',
      'wrapper' => 'advagg-file-info-ajax',
      'effect' => 'fade',
    ),
  );
  module_load_include('install', 'advagg', 'advagg');
  $form['get_info_about_agg']['tip'] = array(
    '#markup' => '<p>' . t('Takes input like "@css_file" or a full aggregate name like "@advagg_js"', array(
      '@css_file' => $css_file,
      '@advagg_js' => advagg_install_get_first_advagg_file($js_path[1]),
    )) . '</p>',
  );
  $form['get_info_about_agg']['wrapper'] = array(
    '#markup' => "<div id='advagg-file-info-ajax'></div>",
  );

  return $form;
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 */
function advagg_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();
}

// Callbacks for buttons.
/**
 * Set or remove the AdvAggDisabled cookie.
 */
function advagg_admin_toggle_bypass_cookie($form, &$form_state) {
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
    setcookie($cookie_name, $key, REQUEST_TIME + $form_state['values']['timespan'], $GLOBALS['base_path'], '.' . $_SERVER['HTTP_HOST']);
    $_COOKIE[$cookie_name] = $key;
    drupal_set_message(t('AdvAgg Bypass Cookie Set for %time.', array('%time' => format_interval($form_state['values']['timespan']))));
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
  // @ignore security_dsm
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
    form_set_error('filename', t('Please input a valid aggregate filename.'));
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
    form_set_error('filename', t('Please input an aggregate filename.'));
    $form_state['values']['error'] = TRUE;
  }
}

/**
 * Get detailed info about the given filename.
 *
 * @param string $filename
 *   Name of file to lookup.
 *
 * @return array
 *   Returns an array of detailed info about this file.
 */
function advagg_admin_get_file_info($filename) {
  module_load_include('inc', 'advagg', 'advagg.missing');
  module_load_include('inc', 'advagg', 'advagg');

  // Strip quotes and trim.
  $filename = trim(str_replace(array('"', "'"), '', $filename));

  $data = advagg_get_hashes_from_filename(basename($filename));
  $output = array();
  if (is_array($data)) {
    list($type, $aggregate_filenames_hash, $aggregate_contents_hash) = $data;

    // Get a list of files.
    $files = advagg_get_files_from_hashes($type, $aggregate_filenames_hash, $aggregate_contents_hash);
    if (empty($files)) {
      list($css_path, $js_path) = advagg_get_root_files_dir();
      // Skip if the file exists.
      if ($type === 'css') {
        $uri = $css_path[0] . '/' . $filename;
      }
      elseif ($type === 'js') {
        $uri = $js_path[0] . '/' . $filename;
      }
      if (file_exists($uri)) {
        $atime = advagg_get_atime($aggregate_filenames_hash, $aggregate_contents_hash, $uri);
        if (REQUEST_TIME - $atime > variable_get('drupal_stale_file_threshold', 2592000)) {
          $files = t('This is an old aggregate, it should be deleted on the next cron run.');
        }
        else {
          $files = t('This is an old aggregate, it should be deleted on the cron run after !time.', array('!time' => format_interval(variable_get('drupal_stale_file_threshold', 2592000) - (REQUEST_TIME - $atime))));
        }
      }
      else {
        $files = t('This aggregate file no longer exists.');
      }
    }
    $data['files'] = $files;

    // Get detailed info on each file.
    $files_info_filenames = array();
    foreach ($data['files'] as $filename => &$info) {
      $files_info_filenames[] = $filename;
    }
    unset($info);

    // Get filesystem data.
    $files_info = advagg_get_info_on_files($files_info_filenames);

    foreach ($data['files'] as $filename => &$info) {
      $info += $files_info[$filename];
      if (module_exists('advagg_bundler')) {
        $bundler = advagg_bundler_analysis($filename);
        $info['group_hash'] = $bundler['group_hash'];
      }
    }
    unset($info);
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

  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) >= 0) {
    // Display a simple message if not in Development mode.
    drupal_set_message(t('Advagg Cache Cleared'));
  }
  else {
    list($css_path) = advagg_get_root_files_dir();
    $parts_uri = $css_path[1] . '/parts';

    // Report back the results.
    foreach ($flushed as $filename => $data) {
      if (strpos($filename, $parts_uri) === 0) {
        // Do not report on css files manged in the parts directory.
        unset($flushed[$filename]);
        continue;
      }
      $ext = pathinfo($filename, PATHINFO_EXTENSION);
      drupal_set_message(t('The file %filename has changed. %db_usage aggregates are using this file. %db_count db cache entries and all %type full cache entries have been flushed from the cache bins.', array(
        '%filename' => $filename,
        '%db_usage' => $data[0],
        '%db_count' => $data[1],
        '%type' => $ext,
      )));
    }

    if (empty($flushed)) {
      drupal_set_message(t('No changes found. Nothing was cleared.'));
      return;
    }
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
  // Clear it again at the end of the request to be sure.
  drupal_register_shutdown_function('advagg_flush_all_cache_bins', FALSE);
  drupal_register_shutdown_function('advagg_push_new_changes');
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
 * Scan for missing files and remove the associated entries in the database.
 */
function advagg_admin_remove_missing_files_from_db_button() {
  module_load_include('inc', 'advagg', 'advagg.cache');

  // Remove aggregates that include missing files.
  $deleted = advagg_remove_missing_files_from_db();
  if (empty($deleted)) {
    drupal_set_message(t('No missing files found or they could not be safely cleared out of the database.'));
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

/**
 * Delete orphaned/expired advagg locks from the semaphore database table.
 */
function advagg_admin_cleanup_semaphore_table_button() {
  module_load_include('inc', 'advagg', 'advagg.cache');

  // Delete orphaned/expired advagg locks from the semaphore database table.
  $count = advagg_cleanup_semaphore_table();
  if (empty($count)) {
    drupal_set_message(t('No orphaned advagg semaphore database table locks discovered. Nothing was deleted.'));
  }
  else {
    drupal_set_message(t('Some orphaned advagg semaphore database table locks discovered were found. A total of %count database entries were removed.', array('%count' => $count)));
  }
}
