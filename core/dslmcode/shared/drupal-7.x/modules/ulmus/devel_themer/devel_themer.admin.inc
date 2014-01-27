<?php
/**
 * @file
 * Module settings UI.
 */

/**
 * Theme developer admin settings form.
 */
function devel_themer_admin_settings() {
  $form['devel_themer_log'] = array(
    '#type' => 'checkbox',
    '#title' => t('Display theme log'),
    '#default_value' => variable_get('devel_themer_log', FALSE),
    '#description' => t('Display the list of theme templates and theme functions which could have been be used for a given page. The one that was actually used is bolded. This is the same data as the represented in the popup, but all calls are listed in chronological order and can alternately be sorted by time.'),
  );

  if (function_exists('gzcompress')) {
    $form['devel_themer_compress_temporary_files'] = array(
      '#type' => 'checkbox',
      '#title' => t('Compress temporary files'),
      '#default_value' => variable_get('devel_themer_compress_temporary_files', TRUE),
      '#description' => t('Compressing files will reduce disk usage but can increase script execution time and memory usage.'),
    );
  }
  return system_settings_form($form);
}
