<?php

/**
 * @file
 * Admin page callbacks for the advagg JS compression module.
 */

/**
 * Form builder; Configure advagg settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function advagg_js_compress_admin_settings_form($form, $form_state) {
  drupal_set_title(t('AdvAgg: JS Compression'));
  $config_path = advagg_admin_config_root_path();

  $form = array();
  if (variable_get('advagg_cache_level', ADVAGG_CACHE_LEVEL) < 0) {
    $form['advagg_devel_msg'] = array(
      '#markup' => '<p>' . t('The settings below will not have any effect because AdvAgg is currently in <a href="@devel">development mode</a>. Once the cache settings have been set to normal or agressive, JS minification will take place.', array('@devel' => url($config_path . '/advagg', array('fragment' => 'edit-advagg-cache-level')))) . '</p>',
    );
  }

  $description = '';
  $options = array(
    0 => t('Disabled'),
    1 => t('JSMin+'),
    // 2 => t('Packer'),
  );
  if (function_exists('jsmin')) {
    $options[3] = t('JSMin');
    $description .= t('JSMin is the C complied version and is about 25 times faster. Recommend using it.');
  }
  else {
    if (!defined('PHP_VERSION_ID') || PHP_VERSION_ID < 50310) {
      $link = 'http://www.ypass.net/software/php_jsmin/';
    }
    else {
      $link = 'https://github.com/sqmk/pecl-jsmin/';
    }
    $description .= t('You can use the much faster C version of JSMin by installing the <a href="@php_jsmin">JSMin PHP Extension</a> on this server.', array('@php_jsmin' => $link));
  }
  $form['advagg_js_compressor'] = array(
    '#type' => 'radios',
    '#title' => t('File Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_js_compressor', ADVAGG_JS_COMPRESSOR),
    '#options' => $options,
    '#description' => filter_xss($description),
  );

  $form['advagg_js_inline_compressor'] = array(
    '#type' => 'radios',
    '#title' => t('Inline Compression: Select a Compressor'),
    '#default_value' => variable_get('advagg_js_inline_compressor', ADVAGG_JS_INLINE_COMPRESSOR),
    '#options' => $options,
    '#description' => filter_xss($description),
  );
  $form['advagg_js_inline_compress_if_not_cacheable'] = array(
    '#type' => 'checkbox',
    '#title' => t('Inline Compression: Use even if this page is not cacheable'),
    '#default_value' => variable_get('advagg_js_inline_compress_if_not_cacheable', ADVAGG_JS_INLINE_COMPRESS_IF_NOT_CACHEABLE),
    '#description' => t('By checking this box, all Inline JavaScript will be compressed regardless of the state of <a href="@link">drupal_page_is_cacheable()</a>. If the C complied version of JSMin is enabled, this option should not slow down page generation that much; if you are using JSMin+ I recommend keeping this disabled.', array('@link' => 'http://api.drupal.org/api/drupal/includes!bootstrap.inc/function/drupal_page_is_cacheable/7')),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_js_inline_compressor"]' => array('value' => "0"),
      ),
    ),
  );

  $form['advagg_js_compress_packer'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Packer on non GZip JS Aggregates'),
    '#default_value' => variable_get('advagg_js_compress_packer', ADVAGG_JS_COMPRESS_PACKER),
    '#description' => t('If enabled the non gzip version of JS files will be compressed using the JS Packer. Packer works similar to gzip, thus using packer on a gzipped file does not give a big improvement in terms of bytes transfered over the wire. WARNING: This has a high chance of breaking your JS. Only Enable on production after testing the non gzipped version locally.'),
    '#states' => array(
      'disabled' => array(
        ':input[name="advagg_js_compressor"]' => array('value' => "0"),
      ),
    ),
  );

  $options[-1] = t('Default');
  ksort($options);

  $form['per_file_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Per File Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  // Get filename & filename_hash.
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
  $cache_bins = advagg_flush_caches();
  foreach ($cache_bins as $bin) {
    cache_clear_all('*', $bin, TRUE);
  }

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
