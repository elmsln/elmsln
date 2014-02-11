<?php
/**
 * @file
 * Custom Formatters Administration functionality.
 */

/**
 *
 */
function custom_formatters_settings_form($form, $form_state) {
  $settings = variable_get('custom_formatters_settings', array('label_prefix' => TRUE, 'label_prefix_value' => t('Custom')));

  $form['settings'] = array(
    '#type' => 'container',
    '#tree' => TRUE,
  );

  $form['settings']['label_prefix'] = array(
    '#type' => 'checkbox',
    '#title' => t('Use Label prefix?'),
    '#description' => t('If checked, all Custom Formatters labels will be prefixed with a set value.'),
    '#default_value' => $settings['label_prefix'],
  );

  $form['settings']['label_prefix_value'] = array(
    '#type' => 'textfield',
    '#title' => t('Label prefix'),
    '#default_value' => $settings['label_prefix_value'],
    '#states' => array(
      'invisible' => array(
        'input[name="settings[label_prefix]"]' => array('checked' => FALSE),
      ),
    ),
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );

  return $form;
}

/**
 *
 */
function custom_formatters_settings_form_validate($form, $form_state) {
  if ($form_state['values']['settings']['label_prefix'] && empty($form_state['values']['settings']['label_prefix_value'])) {
    form_set_error('settings][label_prefix_value', t('A label prefix must be defined if you wish to use the prefix.'));
  }
}

/**
 *
 */
function custom_formatters_settings_form_submit($form, $form_state) {
  drupal_set_message(t('Custom Formatters settings have been updated.'));
  variable_set('custom_formatters_settings', $form_state['values']['settings']);
  field_cache_clear();
}
