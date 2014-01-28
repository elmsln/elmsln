<?php

/**
 * @file
 * Admin page callbacks for the cis_service_activation_codes module.
 */
function cis_service_activation_codes_admin_settings() {
  // seconds in each value
  $window = array(
    604800 => '1 week',
    1209600 => '2 weeks',
    1814400 => '3 weeks',
  );
  // window of time to grant non-code access
  $form['cis_service_activation_codes_window'] = array(
    '#type' => 'select',
    '#title' => t('Window of "free" access'),
    '#description' => t('How long should users of the role to check be allowed to access after their initial login? After this time they will be required to enter a code'),
    '#options' => $window,
    '#default_value' => variable_get('cis_service_activation_codes_window', CIS_SERVICE_ACTIVATION_CODES_WINDOW),
    '#required' => TRUE,
  );
  // role to check for
  $form['cis_service_activation_codes_role_check'] = array(
    '#type' => 'select',
    '#title' => t('Role to check for'),
    '#description' => t('This is the role that requires an activation code be entered.'),
    '#options' => user_roles(TRUE),
    '#default_value' => variable_get('cis_service_activation_codes_role_check', array(2)),
    '#required' => TRUE,
    '#multiple' => TRUE,
  );
  // role to grant
  $form['cis_service_activation_codes_role_grant'] = array(
    '#type' => 'select',
    '#title' => t('Role to grant'),
    '#description' => t('This is the role granted if activation code is entered successfully.'),
    '#options' => user_roles(TRUE),
    '#default_value' => variable_get('cis_service_activation_codes_role_grant', 2),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
