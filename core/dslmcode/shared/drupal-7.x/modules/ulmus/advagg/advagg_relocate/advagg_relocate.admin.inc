<?php

/**
 * @file
 * Admin page callbacks for the advagg relocate module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup advagg_forms
 *
 * @see system_settings_form()
 */
function advagg_relocate_admin_settings_form() {
  drupal_set_title(t('AdvAgg: Relocate'));
  advagg_display_message_if_requirements_not_met();

  $form = array();
  $times[0] = 'No Limit';
  // @codingStandardsIgnoreStart
  $times += drupal_map_assoc(array(
    60 * 60 * 12, // 12 hours.
    60 * 60 * 24, // 1 day.
    60 * 60 * 24 * 4, // 4 days.
    60 * 60 * 24 * 7, // 1 week.
    60 * 60 * 24 * 7 * 2, // 2 weeks.
    60 * 60 * 24 * 7 * 3, // 3 weeks.
    60 * 60 * 24 * 30, // 1 month.
  ), 'format_interval');
  // @codingStandardsIgnoreEnd

  $options = array(
    0 => t('Use default (safe) settings'),
    2 => t('Use recommended (optimized) settings'),
    4 => t('Use customized settings'),
  );
  $form['advagg_relocate_admin_mode'] = array(
    '#type' => 'radios',
    '#title' => t('AdvAgg Settings'),
    '#default_value' => variable_get('advagg_relocate_admin_mode', ADVAGG_RELOCATE_ADMIN_MODE),
    '#options' => $options,
    '#description' => t("Default settings will mirror core as closely as possible. <br>Recommended settings are optimized for speed."),
  );
  $form['global_container'] = array(
    '#type' => 'container',
    '#hidden' => TRUE,
    '#states' => array(
      'visible' => array(
        ':input[name="advagg_relocate_admin_mode"]' => array('value' => '4'),
      ),
    ),
  );

  $form['global_container']['js'] = array(
    '#type' => 'fieldset',
    '#title' => t('JS Settings'),
  );
  $form['global_container']['js']['advagg_relocate_js'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move external JS files to a local JS file'),
    '#default_value' => variable_get('advagg_relocate_js', ADVAGG_RELOCATE_JS),
    '#description' => t('External JS will be moved to a JS file that will be included in the aggregated JS output.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['js']['advagg_relocate_js_ttl'] = array(
    '#type' => 'select',
    '#title' => t('Only cache external JavaScript files if the browser cache TTL is under this amount.'),
    '#options' => $times,
    '#default_value' => variable_get('advagg_relocate_js_ttl', ADVAGG_RELOCATE_JS_TTL),
    '#description' => t('As an example the Minimum needed to not get penalized by Google PageSpeed Insights is <a href="@url">1 week</a>.', array('@url' => 'https://developers.google.com/speed/docs/insights/LeverageBrowserCaching')),
  );
  $form['global_container']['js']['advagg_relocate_js_ga_local'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move inline google analytics inline analytics.js loader code to drupal_add_js'),
    '#default_value' => variable_get('advagg_relocate_js_ga_local', ADVAGG_RELOCATE_JS_GA_LOCAL),
    '#description' => t('If the inline loader code is included in the drupal_add_js array it can then be loaded locally if the above checkbox is checked.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['js']['advagg_relocate_js_piwik_local'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move inline piwik.js loader code to drupal_add_js'),
    '#default_value' => variable_get('advagg_relocate_js_piwik_local', ADVAGG_RELOCATE_JS_PIWIK_LOCAL),
    '#description' => t('If the inline loader code is included in the drupal_add_js array it can then be loaded locally if the above checkbox is checked.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['js']['advagg_relocate_js_gtm_local'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move inline google tag manager inline gtm.js loader code to drupal_add_js'),
    '#default_value' => variable_get('advagg_relocate_js_gtm_local', ADVAGG_RELOCATE_JS_GTM_LOCAL),
    '#description' => t('If the inline loader code is included in the drupal_add_js array it can then be loaded locally if the above checkbox is checked.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['js']['advagg_relocate_js_fbds_local'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move inline fbds.js loader code to drupal_add_js'),
    '#default_value' => variable_get('advagg_relocate_js_fbds_local', ADVAGG_RELOCATE_JS_FBDS_LOCAL),
    '#description' => t('If the inline loader code is included in the drupal_add_js array it can then be loaded locally if the above checkbox is checked.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['js']['advagg_relocate_js_fbevents_local'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move inline fbevents.js loader code to drupal_add_js'),
    '#default_value' => variable_get('advagg_relocate_js_fbevents_local', ADVAGG_RELOCATE_JS_FBEVENTS_LOCAL),
    '#description' => t('If the inline loader code is included in the drupal_add_js array it can then be loaded locally if the above checkbox is checked.'),
    '#recommended_value' => TRUE,
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['js']['advagg_relocate_js_fbevents_local_ids'] = array(
    '#type' => 'textarea',
    '#title' => t('List of Facebook Pixel IDs that will be used.'),
    '#default_value' => variable_get('advagg_relocate_js_fbevents_local_ids', ADVAGG_RELOCATE_JS_FBEVENTS_LOCAL_IDS),
    '#description' => t('New line separated.'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js-fbevents-local' => array('checked' => FALSE),
      ),
    ),
  );
  $advagg_relocate_js_files_blacklist = variable_get('advagg_relocate_js_files_blacklist', ADVAGG_RELOCATE_JS_FILES_BLACKLIST);
  $form['global_container']['js']['advagg_relocate_js_files_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('External JS files blacklist'),
    '#default_value' => $advagg_relocate_js_files_blacklist,
    '#description' => t('New line separated; hostname, path, and filename. Example: <br><code>ajax.googleapis.com/ajax/libs/jquery/1.2.6/jquery.min.js</code><br><code>ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js</code>'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );
  $advagg_relocate_js_domains_blacklist = variable_get('advagg_relocate_js_domains_blacklist', ADVAGG_RELOCATE_JS_DOMAINS_BLACKLIST);
  $form['global_container']['js']['advagg_relocate_js_domains_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('External JS domains blacklist'),
    '#default_value' => $advagg_relocate_js_domains_blacklist,
    '#description' => t('New line separated; hostname only. Example:<br><code>code.jquery.com</code><br><code>maxcdn.bootstrapcdn.com</code>'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-js' => array('checked' => FALSE),
      ),
    ),
  );

  $form['global_container']['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Settings'),
  );
  $form['global_container']['css']['advagg_relocate_css'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move external CSS files to a local CSS file'),
    '#default_value' => variable_get('advagg_relocate_css', ADVAGG_RELOCATE_CSS),
    '#description' => t('External CSS will be moved to a CSS file that will be included in the aggregated CSS output.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['advagg_relocate_css_ttl'] = array(
    '#type' => 'select',
    '#title' => t('Only cache external CSS files if the browser cache TTL is under this amount.'),
    '#options' => $times,
    '#default_value' => variable_get('advagg_relocate_css_ttl', ADVAGG_RELOCATE_CSS_TTL),
    '#description' => t('As an example the Minimum needed to not get penalized by Google PageSpeed Insights is <a href="@url">1 week</a>.', array('@url' => 'https://developers.google.com/speed/docs/insights/LeverageBrowserCaching')),
  );
  $advagg_relocate_css_files_blacklist = variable_get('advagg_relocate_css_files_blacklist', ADVAGG_RELOCATE_CSS_FILES_BLACKLIST);
  $form['global_container']['css']['advagg_relocate_css_files_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('External CSS files blacklist'),
    '#default_value' => $advagg_relocate_css_files_blacklist,
    '#description' => t('New line separated; hostname, path, and filename. Example: <br><code>ajax.googleapis.com/ajax/libs/jqueryui/1.12.1/themes/smoothness/jquery-ui.css</code><br><code>ajax.googleapis.com/ajax/libs/jqueryui/1.9.2/themes/smoothness/jquery-ui.css</code>'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-css' => array('checked' => FALSE),
      ),
    ),
  );
  $advagg_relocate_css_domains_blacklist = variable_get('advagg_relocate_css_domains_blacklist', ADVAGG_RELOCATE_CSS_DOMAINS_BLACKLIST);
  $form['global_container']['css']['advagg_relocate_css_domains_blacklist'] = array(
    '#type' => 'textarea',
    '#title' => t('External CSS domains blacklist'),
    '#default_value' => $advagg_relocate_css_domains_blacklist,
    '#description' => t('New line separated; hostname only. Example:<br><code>code.jquery.com</code><br><code>maxcdn.bootstrapcdn.com</code>'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-css' => array('checked' => FALSE),
      ),
    ),
  );

  $form['global_container']['css']['fonts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Font CSS Settings'),
  );
  $form['global_container']['css']['fonts']['advagg_relocate_css_inline_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Move external CSS font files to inline CSS'),
    '#default_value' => variable_get('advagg_relocate_css_inline_import', ADVAGG_RELOCATE_CSS_INLINE_IMPORT),
    '#description' => t('External font CSS will be moved to inline style tags.'),
    '#recommended_value' => TRUE,
  );
  $form['global_container']['css']['fonts']['advagg_relocate_css_inline_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline @import CSS font files in local .css files'),
    '#default_value' => variable_get('advagg_relocate_css_inline_external', ADVAGG_RELOCATE_CSS_INLINE_EXTERNAL),
    '#description' => t('External font CSS will be put in the aggregated CSS output.'),
    '#recommended_value' => TRUE,
  );

  $options = array(
    'woff2' => t('<a href="@url">woff2</a> - Edge 14+, FF 39+, Chrome 36+, Opera 23+, iOS 10.1+, Android 5+', array('@url' => 'http://caniuse.com/#feat=woff2')),
    'woff' => t('<a href="@url">woff</a> - IE 9+, FF 3.6+, Chrome 5+, Safari 5.1+, Opera 11.5+, iOS 5.1+, Android 4.4+', array('@url' => 'http://caniuse.com/#feat=woff')),
    'ttf' => t('<a href="@url">ttf</a> - Older Safari, Android, iOS.', array('@url' => 'http://caniuse.com/#feat=ttf')),
    'eot' => t('<a href="@url">eot</a> - IE6, IE7, IE8 and IE9 in compatibility mode.', array('@url' => 'http://caniuse.com/#feat=eot')),
    'svg' => t('<a href="@url">svg</a> - Legacy iOS (4.0 and lower).', array('@url' => 'http://caniuse.com/#feat=svg')),
  );
  $defaults = array(
    'woff2' => 'woff2',
    'woff' => 'woff',
    'ttf' => 'ttf',
  );
  $form['global_container']['css']['fonts']['advagg_relocate_css_inline_import_browsers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Browser support for fonts'),
    '#options' => $options,
    '#default_value' => variable_get('advagg_relocate_css_inline_import_browsers', $defaults),
    '#description' => t('<a href="@url">Read more</a>.', array('@url' => 'https://css-tricks.com/snippets/css/using-font-face/')),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-css-inline-import' => array('checked' => FALSE),
        '#edit-advagg-relocate-css-inline-external' => array('checked' => FALSE),
      ),
    ),
  );
  $form['global_container']['css']['fonts']['per_file_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('What import statements should be inlined?'),
    '#states' => array(
      'invisible' => array(
        '#edit-advagg-relocate-css-inline-import' => array('checked' => FALSE),
        '#edit-advagg-relocate-css-inline-external' => array('checked' => FALSE),
      ),
    ),
  );
  $advagg_relocate_css_font_domains = variable_get('advagg_relocate_css_font_domains', ADVAGG_RELOCATE_CSS_FONT_DOMAINS);
  $form['global_container']['css']['fonts']['per_file_settings']['advagg_relocate_css_font_domains'] = array(
    '#type' => 'textarea',
    '#title' => t('What external domains are supported'),
    '#default_value' => $advagg_relocate_css_font_domains,
    '#description' => t('Currently Only fonts.googleapis.com has been tested. Please <a href="@url">open an issue</a> if you want to inline import statements for other domains.', array('@url' => 'https://www.drupal.org/project/issues/advagg')),
    '#disabled' => TRUE,
  );

  $advagg_relocate_css_file_settings = variable_get('advagg_relocate_css_file_settings', array());
  $files_with_import = advagg_relocate_admin_list_files_with_import();
  if (!empty($files_with_import)) {
    $domains = explode("\n", $advagg_relocate_css_font_domains);
    foreach ($files_with_import as $filename => $references) {
      // Convert filename to form api friendly name.
      $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $filename);

      // Settings for the all in filename checkbox.
      $default_value = TRUE;
      if (isset($advagg_relocate_css_file_settings['all:' . $form_api_filename])) {
        $default_value = $advagg_relocate_css_file_settings['all:' . $form_api_filename];
      }
      $form['global_container']['css']['fonts']['per_file_settings']['advagg_relocate_css_file_settings_all_' . $form_api_filename] = array(
        '#type' => 'checkbox',
        '#default_value' => $default_value,
        '#title' => t('All in @filename', array('@filename' => $filename)),
      );
      $form_api_html_filename = str_replace(array('__', '--', '_'), '-', $form_api_filename);

      // Fieldset for the checkboxes.
      $form['global_container']['css']['fonts']['per_file_settings'][$form_api_filename] = array(
        '#type' => 'fieldset',
        '#title' => t('@filename', array('@filename' => $filename)),
        '#states' => array(
          'disabled' => array(
            '#edit-advagg-relocate-css-file-settings-all-' . $form_api_html_filename => array('checked' => TRUE),
          ),
        ),
      );

      // Build options and the default enabled settings.
      $default_values = array();
      $options = array();
      foreach ($references[0] as $key => $value) {
        $include = FALSE;
        foreach ($domains as $domain) {
          if (strpos($value, $domain) !== FALSE) {
            $include = TRUE;
            break;
          }
        }
        if ($include) {
          $options[$references[1][$key]] = $value;
          $default_values[$references[1][$key]] = $references[1][$key];
        }
      }

      // Apply saved settings to the checkboxes.
      if (isset($advagg_relocate_css_file_settings[$form_api_filename])
        && is_array($advagg_relocate_css_file_settings[$form_api_filename])
      ) {
        $default_values = $advagg_relocate_css_file_settings[$form_api_filename];
      }
      $form['global_container']['css']['fonts']['per_file_settings'][$form_api_filename]['advagg_relocate_css_file_settings_' . $form_api_filename] = array(
        '#type' => 'checkboxes',
        '#options' => $options,
        '#default_value' => $default_values,
      );

      // No viable options for this file; remove fieldset and checkboxes.
      if (empty($options)) {
        unset($form['global_container']['css']['fonts']['per_file_settings'][$form_api_filename]);
        unset($form['global_container']['css']['fonts']['per_file_settings']['advagg_relocate_css_file_settings_all_' . $form_api_filename]);
      }
    }
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_relocate_admin_settings_form_submit';

  return system_settings_form($form);
}

/**
 * Submit callback, clear out the advagg cache bin.
 *
 * Also process the advagg_relocate_css_file_settings variable.
 *
 * @ingroup advagg_forms_callback
 */
function advagg_relocate_admin_settings_form_submit($form, &$form_state) {

  // Reset this form to defaults or recommended values; also show what changed.
  advagg_set_admin_form_defaults_recommended($form_state, 'advagg_relocate_admin_mode');

  // Get settings that start with advagg_relocate_css_file_settings.
  if (defined('PHP_VERSION_ID') && PHP_VERSION_ID >= 50600) {
    $vars = array_filter($form_state['values'], '_advagg_relocate_admin_is_file_settings', ARRAY_FILTER_USE_KEY);
  }
  else {
    $vars = array_intersect_key($form_state['values'], array_flip(array_filter(array_keys($form_state['values']), '_advagg_relocate_admin_is_file_settings')));
  }
  // Unset found values.
  foreach ($vars as $key => $value) {
    if (isset($form_state['values'][$key])) {
      unset($form_state['values'][$key]);
    }
    // If all is set, remove sub options for that file.
    if (strpos($key, 'advagg_relocate_css_file_settings_all_') === 0 && !empty($value)) {
      $sub_key = str_replace('advagg_relocate_css_file_settings_all_', 'advagg_relocate_css_file_settings_', $key);
      if (isset($vars[$sub_key])) {
        unset($vars[$sub_key]);
      }
    }
  }

  $saved_values = array();
  foreach ($vars as $key => $value) {
    $key = str_replace('advagg_relocate_css_file_settings_all_', 'all:', $key);
    $key = str_replace('advagg_relocate_css_file_settings_', '', $key);
    $saved_values[$key] = $value;
  }

  // Save under one variable.
  $form_state['values']['advagg_relocate_css_file_settings'] = $saved_values;

  // Clear caches.
  advagg_cache_clear_admin_submit();
}

/**
 * See if the key starts with 'advagg_relocate_css_file_settings'.
 *
 * @param string $key
 *   They array key as a string.
 *
 * @return bool
 *   TRUE if the input string starts with 'advagg_relocate_css_file_settings'.
 */
function _advagg_relocate_admin_is_file_settings($key) {
  return strpos($key, 'advagg_relocate_css_file_settings') === 0;
}

/**
 * Check all CSS files, see if any contains an @import that is external.
 *
 * @param array $files
 *   An array of filenames to check.
 *
 * @return array
 *   An array of filenames that contain an @import that is external.
 */
function advagg_relocate_admin_list_files_with_import(array $files = array()) {
  if (empty($files)) {
    // Get filename.
    $results = db_select('advagg_files', 'af')
      ->fields('af', array('filename'))
      ->condition('filetype', 'css')
      ->orderBy('filename', 'ASC')
      ->execute();
    while ($row = $results->fetchAssoc()) {
      $files[] = $row['filename'];
    }
  }
  $files_with_import_statements = array();
  if (empty($files)) {
    return $files_with_import_statements;
  }

  module_load_include('inc', 'advagg', 'advagg');
  foreach ($files as $file) {
    if (!file_exists($file)) {
      continue;
    }
    // Get the file contents.
    $file_contents = advagg_load_css_stylesheet($file, FALSE);
    if (strpos($file_contents, '@import') !== FALSE) {
      $matches = array();
      preg_match_all('%@import\s*+(?:url\(\s*+)?+[\'"]?+((?:http:\/\/|https:\/\/|\/\/)(?:[^\'"()\s]++))[\'"]?+\s*+\)?+\s*+;%i', $file_contents, $matches);
      if (!empty($matches[0])) {
        $files_with_import_statements[$file] = $matches;
      }
    }
  }
  return $files_with_import_statements;
}

/**
 * Add a cache clear button to the advagg operations form.
 */
function advagg_relocate_admin_form_advagg_admin_operations_form(&$form, &$form_state) {
  $form['drastic_measures']['flush_relocate_cache'] = array(
    '#type' => 'fieldset',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#title' => t('Clear the advagg relocate cache'),
    '#description' => t('Rarely needed but useful if a download was corrupted.'),
  );
  $form['drastic_measures']['flush_relocate_cache']['advagg_flush'] = array(
    '#type' => 'submit',
    '#value' => t('Flush AdvAgg Relocate Cache'),
    '#submit' => array('advagg_relocate_flush_cache_button'),
  );
}
