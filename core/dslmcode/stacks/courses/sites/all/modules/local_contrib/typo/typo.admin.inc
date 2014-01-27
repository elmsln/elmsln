<?php
/**
 * @file
 * Admin settings form for vk_openapi module
 */

/**
 * Typo settings form.
 */
function typo_admin_settings() {
  global $base_url;

  $form['typo_reports_ttl'] = array(
    '#type' => 'select',
    '#title' => t('Delete old typo reports'),
    '#description' => t('Delete typo reports older than N days'),
    '#default_value' => variable_get('typo_reports_ttl', 4320),
    '#options' => array(
      1440 => t('1 day'),
      4320 => t('3 days'),
      10080 => t('1 week'),
      0 => t('Never'),
    ),
  );

  $form['typo_max_chars'] = array(
    '#type' => 'textfield',
    '#title' => t('Maximum characters in selection'),
    '#default_value' => variable_get('typo_max_chars', 20),
  );

  return system_settings_form($form);
}

/**
 * Typo settings form validator.
 */
function typo_admin_settings_validate($form, &$form_state) {
  if(!is_numeric($form_state['values']['typo_max_chars'])) {
    form_set_error('typo_max_chars', t('Maximum characters in selection should be an integer.'));
  }
  else {
    $form_state['values']['typo_max_chars'] = (int) $form_state['values']['typo_max_chars'];
  }
}
