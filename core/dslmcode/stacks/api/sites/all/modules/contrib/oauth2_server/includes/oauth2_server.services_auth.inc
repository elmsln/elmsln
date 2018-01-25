<?php

/**
 * @file
 * Provides an authentication method to Services.
 */

/**
 * Services authentication "authenticate_call" callback.
 *
 * @see _services_authenticate_user()
 *
 * @param array $auth_settings
 *   The auth settings provided by Services.
 *
 * @throws \Exception If no server is configured yet authentication is required.
 *
 * @return mixed
 *   A non-empty return value indicates an error has occurred.
 */
function oauth2_server_services_authenticate_call($auth_settings) {
  // No server specified: cannot proceed.
  if (empty($auth_settings['server'])) {
    watchdog('oauth2_server', 'No server configured for Services OAuth2 authentication.', array(), WATCHDOG_ERROR);
    return TRUE;
  }

  // Check access.
  $result = oauth2_server_check_access($auth_settings['server'], $auth_settings['scope']);
  if (is_array($result) && !empty($result['user_id'])) {
    // The check was successful. If it matches with a user account, then switch
    // the current user to it.
    global $user;
    $user = user_load($result['user_id']);
  }
  elseif ($result instanceof \OAuth2\Response) {
    // There was an authentication error, or the user did not attempt to
    // authenticate. If authentication is required for this resource, send an
    // error response and abort the request. Otherwise, move on without error.
    if (!empty($auth_settings['require_authentication'])) {
      oauth2_server_send_response($result);
    }
  }
}

/**
 * Services authentication "security_settings" callback.
 */
function oauth2_server_services_security_settings($settings, &$form_state) {
  if (isset($form_state['values']['oauth2']['server'])) {
    $settings['server'] = $form_state['values']['oauth2']['server'];
  }

  $options = array('' => t('- Select -'));
  $servers = entity_load('oauth2_server');
  foreach ($servers as $server) {
    $options[$server->name] = $server->label;
  }

  $form = array();
  $form['server'] = array(
    '#type' => 'select',
    '#options' => $options,
    '#default_value' => isset($settings['server']) ? $settings['server'] : '',
    '#title' => t('OAuth2 server'),
    '#required' => TRUE,
  );

  return $form;
}

/**
 * Services authentication "default_security_settings" callback.
 */
function oauth2_server_services_default_security_settings() {
  return array(
    'server' => '',
  );
}

/**
 * Services authentication "controller_settings" callback.
 */
function oauth2_server_services_controller_settings($settings, $controller, $endpoint, $class, $name) {
  $form = array();
  $form['require_authentication'] = array(
    '#type' => 'checkbox',
    '#title' => t('Require authentication'),
    '#default_value' => isset($settings['require_authentication']) ? $settings['require_authentication'] : FALSE,
  );
  $form['scope'] = array(
    '#type' => 'textfield',
    '#title' => t('Scope'),
    '#default_value' => isset($settings['scope']) ? $settings['scope'] : '',
    '#description' => t('A space-separated list of required scopes. Leave empty to ignore the check.'),
  );

  return $form;
}
