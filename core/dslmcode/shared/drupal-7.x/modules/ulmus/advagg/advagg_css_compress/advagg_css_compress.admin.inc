<?php

/**
 * @file
 * Admin page callbacks for the advagg JS compression module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 *
 * @see system_settings_form()
 */
function advagg_css_compress_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: CSS Compression Settings'));
  $config_path = advagg_admin_config_root_path();

  $form = array();
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $form['advagg_devel_msg'] = array(
      '#markup' => '<p>' . t('The settings below will not have any effect because AdvAgg is currently in <a href="@devel">development mode</a>. Once the cache settings have been set to normal or aggressive, CSS minification will take place.', array('@devel' => url($config_path . '/advagg', array('fragment' => 'edit-advagg-cache-level')))) . '</p>',
    );
  }

  list($options, $description) = advagg_css_compress_configuration();

  $form['advagg_css_compressor'] = array(
    '#type' => 'radios',
    '#title' => t('File Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_css_compressor', ADVAGG_CSS_COMPRESSOR),
    '#options' => $options,
    '#description' => filter_xss($description),
  );
  $inline_options = $options;
  unset($inline_options[-1]);
  $inline_options[0] = t('Disabled');
  $form['advagg_css_compress_inline'] = array(
    '#type' => 'radios',
    '#title' => t('Inline Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_css_compress_inline', ADVAGG_CSS_COMPRESS_INLINE),
    '#options' => $inline_options,
    '#description' => filter_xss($description),
  );
  $form['advagg_css_compress_inline_if_not_cacheable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline Compression: Use even if this page is not cacheable'),
    '#default_value' => variable_get('advagg_css_compress_inline_if_not_cacheable', ADVAGG_CSS_COMPRESS_INLINE_IF_NOT_CACHEABLE),
    '#description' => t('By checking this box, all Inline CSS will be compressed regardless of the state of <a href="@link">drupal_page_is_cacheable()</a>.', array('@link' => 'http://api.drupal.org/api/drupal/includes!bootstrap.inc/function/drupal_page_is_cacheable/7')),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_css_compress_inline"]' => array('value' => "0"),
      ),
    ),
  );

  $options[ADVAGG_CSS_COMPRESSOR_FILE_SETTINGS] = t('Default');
  ksort($options);

  $form['per_file_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Per File Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Get filename and filename_hash.
  $results = db_select('advagg_files', 'af')
    ->fields('af', array('filename'))
    ->condition('filetype', 'css')
    ->orderBy('af.filename', 'ASC')
    ->execute();
  $file_settings = variable_get('advagg_css_compressor_file_settings', array());
  foreach ($results as $row) {
    $dir = dirname($row->filename);
    if (!isset($form['per_file_settings'][$dir])) {
      $form['per_file_settings'][$dir] = array(
        '#type' => 'fieldset',
        '#title' => check_plain($dir),
        '#collapsible' => TRUE,
        '#collapsed' => TRUE,
      );
    }
    $form_api_filename = str_replace(array('/', '.'), array('__', '--'), $row->filename);
    $form['per_file_settings'][$dir]['advagg_css_compressor_file_settings_' . $form_api_filename] = array(
      '#type' => 'radios',
      '#title' => t('%filename: Select a Compressor', array('%filename' => $row->filename)),
      '#default_value' => isset($file_settings[$form_api_filename]) ? $file_settings[$form_api_filename] : ADVAGG_CSS_COMPRESSOR_FILE_SETTINGS,
      '#options' => $options,
    );
    if ($form['per_file_settings'][$dir]['advagg_css_compressor_file_settings_' . $form_api_filename]['#default_value'] != ADVAGG_CSS_COMPRESSOR_FILE_SETTINGS) {
      $form['per_file_settings'][$dir]['#collapsed'] = FALSE;
      $form['per_file_settings']['#collapsed'] = FALSE;
    }
  }

  // No css files are found.
  if (empty($results)) {
    $form['per_file_settings']['#description'] = t('No CSS files have been aggregated. You need to enable aggregation. No css files where found in the advagg_files table.');
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_css_compress_admin_settings_form_submit';

  return system_settings_form($form);
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 *
 * Also remove default settings inside of the per_file_settings fieldgroup.
 */
function advagg_css_compress_admin_settings_form_submit($form, &$form_state) {
  // Clear caches.
  advagg_cache_clear_admin_submit();

  // Get current defaults.
  $file_settings = variable_get('advagg_css_compressor_file_settings', array());

  // Save per file settings.
  $new_settings = array();
  foreach ($form_state['values'] as $key => $value) {
    // Skip if not advagg_css_compressor_file_settings
    if (strpos($key, 'advagg_css_compressor_file_settings_') === FALSE) {
      continue;
    }
    // Do not process default settings.
    if ($value == ADVAGG_CSS_COMPRESSOR_FILE_SETTINGS) {
      unset($form_state['values'][$key]);
      continue;
    }
    $new_settings[substr($key, 36)] = $value;

    // Do not save this field into its own variable.
    unset($form_state['values'][$key]);
  }
  if (!empty($new_settings) || !empty($file_settings)) {
    if (empty($new_settings)) {
      variable_del('advagg_css_compressor_file_settings');
    }
    else {
      variable_set('advagg_css_compressor_file_settings', $new_settings);
    }
  }
}
