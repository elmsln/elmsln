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
function advagg_js_compress_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: JS Compression'));
  $config_path = advagg_admin_config_root_path();

  $form = array();
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $form['advagg_devel_msg'] = array(
      '#markup' => '<p>' . t('The settings below will not have any effect because AdvAgg is currently in <a href="@devel">development mode</a>. Once the cache settings have been set to normal or aggressive, JS minification will take place.', array('@devel' => url($config_path . '/advagg', array('fragment' => 'edit-advagg-cache-level')))) . '</p>',
    );
  }

  list($options, $description) = advagg_js_compress_configuration();

  $form['advagg_js_compressor'] = array(
    '#type' => 'radios',
    '#title' => t('File Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_js_compressor', ADVAGG_JS_COMPRESSOR),
    '#options' => $options,
    '#description' => filter_xss($description),
  );

  $form['advagg_js_compress_inline'] = array(
    '#type' => 'radios',
    '#title' => t('Inline Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_js_compress_inline', ADVAGG_JS_COMPRESS_INLINE),
    '#options' => $options,
    '#description' => filter_xss($description),
  );
  $form['advagg_js_compress_inline_if_not_cacheable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline Compression: Use even if this page is not cacheable'),
    '#default_value' => variable_get('advagg_js_compress_inline_if_not_cacheable', ADVAGG_JS_COMPRESS_INLINE_IF_NOT_CACHEABLE),
    '#description' => t('By checking this box, all Inline JavaScript will be compressed regardless of the state of <a href="@link">drupal_page_is_cacheable()</a>. If the C complied version of JSMin is enabled, this option should not slow down page generation that much; if you are using JSMin+ I recommend keeping this disabled.', array('@link' => 'http://api.drupal.org/api/drupal/includes!bootstrap.inc/function/drupal_page_is_cacheable/7')),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_js_compress_inline"]' => array('value' => "0"),
      ),
    ),
  );

  $form['advagg_js_compress_packer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Packer on non GZip JS Aggregates'),
    '#default_value' => variable_get('advagg_js_compress_packer', ADVAGG_JS_COMPRESS_PACKER),
    '#description' => t('If enabled the non gzip version of JS files will be compressed using the JS Packer. Packer works similar to gzip, thus using packer on a gzipped file does not give a big improvement in terms of bytes transferred over the wire. WARNING: This has a high chance of breaking your JS. Only Enable on production after testing the non gzipped version locally.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_js_compressor"]' => array('value' => "0"),
      ),
    ),
  );
  $form['advagg_js_compress_add_license'] = array(
    '#type' => 'checkbox',
    '#title' => t('Add licensing comments'),
    '#default_value' => variable_get('advagg_js_compress_add_license', ADVAGG_JS_COMPRESS_ADD_LICENSE),
    '#description' => t("If unchecked, the Advanced Aggregation module's licensing comments
   will be omitted from the aggregated files. Omitting the comments will produce somewhat better scores in
   some automated security scans but otherwise should not affect your site. These are included by default in order to better follow the spirit of the GPL by providing the source for javascript files."),
  );

  $options[-1] = t('Default');
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
    ->condition('filetype', 'js')
    ->orderBy('af.filename', 'ASC')
    ->execute();
  $file_settings = variable_get('advagg_js_compressor_file_settings', array());
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
    $form['per_file_settings'][$dir]['advagg_js_compressor_file_settings_' . $form_api_filename] = array(
      '#type' => 'radios',
      '#title' => t('%filename: Select a Compressor', array('%filename' => $row->filename)),
      '#default_value' => isset($file_settings[$form_api_filename]) ? $file_settings[$form_api_filename] : ADVAGG_JS_COMPRESSOR_FILE_SETTINGS,
      '#options' => $options,
    );
    if ($form['per_file_settings'][$dir]['advagg_js_compressor_file_settings_' . $form_api_filename]['#default_value'] != ADVAGG_JS_COMPRESSOR_FILE_SETTINGS) {
      $form['per_file_settings'][$dir]['#collapsed'] = FALSE;
      $form['per_file_settings']['#collapsed'] = FALSE;
    }
  }

  // No js files are found.
  if (empty($results)) {
    $form['per_file_settings']['#description'] = t('No JS files have been aggregated. You need to enable aggregation. No js files where found in the advagg_files table.');
  }

  // Clear the cache bins on submit.
  $form['#submit'][] = 'advagg_js_compress_admin_settings_form_submit';

  return system_settings_form($form);
}

// Submit callback.
/**
 * Clear out the advagg cache bin when the save configuration button is pressed.
 *
 * Also remove default settings inside of the per_file_settings fieldgroup.
 */
function advagg_js_compress_admin_settings_form_submit($form, &$form_state) {
  advagg_cache_clear_admin_submit();

  // Get current defaults.
  $file_settings = variable_get('advagg_js_compressor_file_settings', array());

  // Save per file settings.
  $new_settings = array();
  foreach ($form_state['values'] as $key => $value) {
    // Skip if not advagg_js_compressor_file_settings
    if (strpos($key, 'advagg_js_compressor_file_settings_') === FALSE) {
      continue;
    }
    // Do not process default settings.
    if ($value == ADVAGG_JS_COMPRESSOR_FILE_SETTINGS) {
      unset($form_state['values'][$key]);
      continue;
    }
    $new_settings[substr($key, 35)] = $value;

    // Do not save this field into its own variable.
    unset($form_state['values'][$key]);
  }
  if (!empty($new_settings) || !empty($file_settings)) {
    if (empty($new_settings)) {
      variable_del('advagg_js_compressor_file_settings');
    }
    else {
      variable_set('advagg_js_compressor_file_settings', $new_settings);
    }
  }
}
