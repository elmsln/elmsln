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
  $form = array();

  $form['css'] = array(
    '#type' => 'fieldset',
    '#title' => t('CSS Settings'),
  );
  $form['css']['advagg_relocate_css_inline_import'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Inlining CSS Import Statements'),
    '#default_value' => variable_get('advagg_relocate_css_inline_import', ADVAGG_RELOCATE_CSS_INLINE_IMPORT),
  );
  $form['css']['advagg_relocate_css_inline_external'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Inlining External CSS Files'),
    '#default_value' => variable_get('advagg_relocate_css_inline_external', ADVAGG_RELOCATE_CSS_INLINE_EXTERNAL),
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
  $form['css']['advagg_relocate_css_inline_import_browsers'] = array(
    '#type' => 'checkboxes',
    '#title' => t('Browser support for fonts'),
    '#options' => $options,
    '#default_value' => variable_get('advagg_relocate_css_inline_import_browsers', $defaults),
    '#description' => t('<a href="@url">Read more</a>.', array('@url' => 'https://css-tricks.com/snippets/css/using-font-face/')),
    '#states' => array(
      'visible' => array(
        '#edit-advagg-relocate-css-inline-import' => array('checked' => TRUE),
      ),
    ),
  );

  $files_with_import = advagg_relocate_admin_list_files_with_import();
  $form['css']['per_file_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('What import statements should be inlined?'),
    '#states' => array(
      'visible' => array(
        '#edit-advagg-relocate-css-inline-import' => array('checked' => TRUE),
      ),
    ),
  );
  $form['css']['per_file_settings']['advagg_relocate_css_file_domains'] = array(
    '#type' => 'textarea',
    '#title' => t('What external domains are supported'),
    '#default_value' => variable_get('advagg_relocate_css_file_domains', ADVAGG_RELOCATE_CSS_FILE_DOMAINS),
    '#description' => t('Currently Only fonts.googleapis.com has been tested. Please <a href="@url">open an issue</a> if you want to inline import statements for other domains.', array('@url' => 'https://www.drupal.org/project/issues/advagg')),
    '#disabled' => TRUE,
  );

  $advagg_relocate_css_file_settings = variable_get('advagg_relocate_css_file_settings', array());
  if (!empty($files_with_import)) {
    foreach ($files_with_import as $filename => $references) {
      $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $filename);
      $options = array();
      $default_values = array();
      foreach ($references[0] as $key => $value) {
        $options[$references[1][$key]] = $value;
        $default_values[$references[1][$key]] = $references[1][$key];
      }
      $form['css']['per_file_settings']['advagg_relocate_css_file_settings_all_' . $form_api_filename] = array(
        '#type' => 'checkbox',
        '#default_value' => isset($advagg_relocate_css_file_settings['all:' . $form_api_filename])
          ? $advagg_relocate_css_file_settings['all:' . $form_api_filename]
          : TRUE,
        '#title' => t('All in @filename', array('@filename' => $filename)),
      );
      $form_api_html_filename = str_replace(array('__', '--'), '-', $form_api_filename);

      $form['css']['per_file_settings'][$form_api_filename] = array(
        '#type' => 'fieldset',
        '#title' => t('@filename', array('@filename' => $filename)),
        '#states' => array(
          'disabled' => array(
            '#edit-advagg-relocate-css-file-settings-all-' . $form_api_html_filename => array('checked' => TRUE),
          ),
        ),
      );
      $form['css']['per_file_settings'][$form_api_filename]['advagg_relocate_css_file_settings_' . $form_api_filename] = array(
        '#type' => 'checkboxes',
        '#options' => $options,
        '#default_value' => isset($advagg_relocate_css_file_settings[$form_api_filename])
          ? $advagg_relocate_css_file_settings[$form_api_filename]
          : $default_values,
      );
    }
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_relocate_admin_settings_form_submit';

  return system_settings_form($form);
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 *
 * Also process the advagg_relocate_css_file_settings variable.
 */
function advagg_relocate_admin_settings_form_submit($form, &$form_state) {
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

// Helper functions.
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
