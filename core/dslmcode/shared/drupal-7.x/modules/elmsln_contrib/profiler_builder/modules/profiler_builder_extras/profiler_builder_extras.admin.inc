<?php
/**
 * @file
 * Administrative forms
 */

/**
 * Implements hook_settings().
 */
function _profiler_builder_extras_settings() {
  $form = array();
  $form['extras'] = array(
    '#description' => t('Some more crazy things you can do to extend profiler builder'),
    '#collapsed' => FALSE,
    '#type' => 'fieldset',
    '#collapsible' => FALSE,
    '#title' => t('Extra options'),
  );
  // optional support for features builder
  if (module_exists('features_builder')) {
    $form['extras']['features_builder'] = array(
      '#title' => t('Features Builder'),
      '#description' => t('Support for automated features_builder output if that module is enabled.'),
      '#type' => 'checkbox',
      '#default_value' => variable_get('profiler_builder_extras_fb', FALSE),
    );
  }
  // database query logging support, this is crazy
  $form['extras']['query_log'] = array(
    '#title' => t('Query logging'),
    '#description' => t('This uses a method similar to devel where it actively watches the queries that are writen to the database (or deleted) and then captures them. This can then be used to automatically author an update hook.'),
    '#type' => 'checkbox',
    '#default_value' => variable_get('profiler_builder_extras_ql', FALSE),
  );
  // start logging
  if (_profiler_builder_extras_query_enabled()) {
    $form['extras']['active_logging'] = array(
      '#title' => t('Query logging activated'),
      '#description' => t('Checking this box means profiler builder will be monitoring all queries made on the site and decide which to save for distribution reuse. Usage: check this box when you want to make a change, make the change, then come back to this page and disable this setting. This ensures that only the changes you want to capture are stored.'),
      '#type' => 'checkbox',
      '#default_value' => variable_get('profiler_builder_extras_aql', FALSE),
    );
  }
  $form['buttons']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
    '#weight' => 10,
    '#submit' => array('_profiler_builder_extras_settings_form_submit'),
  );
  // special debugging handler if devel is also installed, common
  if (module_exists('devel')) {
    $form['buttons']['devel_submit'] = array(
      '#type' => 'submit',
      '#value' => t('Review queries logged'),
      '#weight' => 11,
      '#submit' => array('_profiler_builder_extras_settings_devel_form_submit'),
    );
  }
  return $form;
}

/**
 * Form submit handler for extra settings
 */
function _profiler_builder_extras_settings_form_submit($form, &$form_state) {
  if (isset($form_state['values']['features_builder'])) {
    variable_set('profiler_builder_extras_fb', $form_state['values']['features_builder']);
  }
  if (isset($form_state['values']['query_log'])) {
    variable_set('profiler_builder_extras_ql', $form_state['values']['query_log']);
  }
  if (isset($form_state['values']['active_logging'])) {
    variable_set('profiler_builder_extras_aql', $form_state['values']['active_logging']);
  }
  drupal_set_message('Settings saved.');
}

/**
 * Form submit handler for viewing the current queries in the queue to be written
 */
function _profiler_builder_extras_settings_devel_form_submit($form, &$form_state) {
  drupal_set_message('The follow queries are what is planned to be written to your profile');
  dpm(_profiler_builder_extras_load_query_files(FALSE));
}
