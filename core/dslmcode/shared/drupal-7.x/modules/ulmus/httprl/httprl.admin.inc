<?php

/**
 * @file
 * Administrative page callbacks for the httprl module.
 */

/**
 * Form definition; general settings.
 */
function httprl_admin_settings_form() {
  $form['httprl_server_addr'] = array(
    '#type' => 'textfield',
    '#title' => t('IP Address to send all self server requests to'),
    '#default_value' => variable_get('httprl_server_addr', FALSE),
    '#description' => t('If left blank it will use the same server as the request. If set to -1 it will use the host name instead of an IP address. This controls the output of httprl_build_url_self()'),
  );
  $form['httprl_background_callback'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable background callbacks'),
    '#default_value' => variable_get('httprl_background_callback', HTTPRL_BACKGROUND_CALLBACK),
    '#description' => t('If disabled all background_callback keys will be turned into callback & httprl_queue_background_callback will return NULL and not queue up the request. Note that background callbacks will automatically be disabled if the site is in maintenance mode.'),
  );
  // Currently only available on D7.
  // http://drupal.org/node/1664784
  if (defined('VERSION') && substr(VERSION, 0, 1) >= 7) {
    $form['drupal_http_request_function'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use httprl to handle drupal_http_request.'),
      '#default_value' => variable_get('drupal_http_request_function', FALSE) === 'httprl_override_core' ? TRUE : FALSE,
      '#description' => t('Use httprl to handle all calls to drupal_http_request. Requires 7.22+'),
    );
  }
  $form['timeouts'] = array(
    '#type' => 'fieldset',
    '#title' => t('Default timeouts'),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#description' => t('Set the default timeouts. These will be overridden if a different timeout is set in the options array.'),
  );
  $form['timeouts']['httprl_dns_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('DNS timeout (<code>dns_timeout</code>)'),
    '#default_value' => variable_get('httprl_dns_timeout', HTTPRL_DNS_TIMEOUT),
    '#description' => t('Maximum number of seconds a DNS lookup request may take. Value can be a float. The default is %value seconds.', array('%value' => HTTPRL_DNS_TIMEOUT)),
    '#field_suffix' => t('seconds'),
    '#size' => 5,
  );
  $form['timeouts']['httprl_connect_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Connection timeout (<code>connect_timeout</code>)'),
    '#default_value' => variable_get('httprl_connect_timeout', HTTPRL_CONNECT_TIMEOUT),
    '#description' => t('Maximum number of seconds establishing the TCP connection may take. Value can be a float. The default is %value seconds.', array('%value' => HTTPRL_CONNECT_TIMEOUT)),
    '#field_suffix' => t('seconds'),
    '#size' => 5,
  );
  $form['timeouts']['httprl_ttfb_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Time to first byte (<code>ttfb_timeout</code>)'),
    '#default_value' => variable_get('httprl_ttfb_timeout', HTTPRL_TTFB_TIMEOUT),
    '#description' => t('Maximum number of seconds a connection may take to download the first byte. Value can be a float. The default is %value seconds.', array('%value' => HTTPRL_TTFB_TIMEOUT)),
    '#field_suffix' => t('seconds'),
    '#size' => 5,
  );
  $form['timeouts']['httprl_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Timeout (<code>timeout</code>)'),
    '#default_value' => variable_get('httprl_timeout', HTTPRL_TIMEOUT),
    '#description' => t('Maximum number of seconds the request may take. Value can be a float. The default is %value seconds.', array('%value' => HTTPRL_TIMEOUT)),
    '#field_suffix' => t('seconds'),
    '#size' => 5,
  );
  $form['timeouts']['httprl_global_timeout'] = array(
    '#type' => 'textfield',
    '#title' => t('Global timeout (<code>global_timeout</code>)'),
    '#default_value' => variable_get('httprl_global_timeout', HTTPRL_GLOBAL_TIMEOUT),
    '#description' => t('Maximum number of seconds httprl_send_request() may take. Value can be a float. The default is %value seconds.', array('%value' => HTTPRL_GLOBAL_TIMEOUT)),
    '#field_suffix' => t('seconds'),
    '#size' => 5,
  );

  return system_settings_form($form);
}

/**
 * Validate form values.
 */
function httprl_admin_settings_form_validate($form, &$form_state) {
  // Skip validation if we are resting to defaults.
  if (isset($form_state['clicked_button']['#post']['op']) && $form_state['clicked_button']['#post']['op'] == 'Reset to defaults') {
    return;
  }

  // Get form values.
  $values = &$form_state['values'];

  // If the IP field is not blank, check that it is a valid address.
  if (   !empty($values['httprl_server_addr'])
      && $values['httprl_server_addr'] != -1
      && ip2long($values['httprl_server_addr']) === FALSE
        ) {
    form_set_error('httprl_server_addr', t('Must be a valid IP address.'));
  }

  // Make sure the timeouts are positive numbers.
  $positive_values = array(
    'httprl_dns_timeout',
    'httprl_connect_timeout',
    'httprl_ttfb_timeout',
    'httprl_timeout',
    'httprl_global_timeout',
  );
  foreach ($positive_values as $name) {
    if (empty($values[$name])) {
      form_set_error($name, t('Must not be empty or zero.'));
      continue;
    }
    if (!is_numeric($values[$name])) {
      form_set_error($name, t('Must be numeric.'));
      continue;
    }
    if ($values[$name] <= 0) {
      form_set_error($name, t('Must be a positive number.'));
      continue;
    }
  }

  // Change checkbox value to string.
  if (!empty($values['drupal_http_request_function'])) {
    $values['drupal_http_request_function'] = 'httprl_override_core';
  }

}
