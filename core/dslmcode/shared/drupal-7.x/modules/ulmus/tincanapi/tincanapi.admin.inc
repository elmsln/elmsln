<?php

/**
 * @file
 * Admin settings for the Tin Can API module.
 */

/**
 * Tin Can API Configuration form.
 *
 * @param array $form
 *   A structured FAPI $form array.
 * @param array $form_state
 *   The complete form state.
 *
 * @return array
 *   A structured FAPI array.
 */
function tincanapi_admin_form(array $form, array &$form_state) {
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('API Settings'),
  );

  $form['api']['tincanapi_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('Endpoint'),
    '#description' => t('The server endpoint.  Do not include a trailing slash.'),
    '#default_value' => variable_get('tincanapi_endpoint', ''),
    '#required' => TRUE,
  );

  $form['api']['tincanapi_auth_user'] = array(
    '#type' => 'textfield',
    '#title' => t('User'),
    '#description' => t('The basic authenication user.'),
    '#default_value' => variable_get('tincanapi_auth_user', ''),
    '#required' => TRUE,
  );
  $tincanapisend = module_invoke_all('tincan_request_fuction');
  $form['api']['tincanapi_function'] = array(
    '#type' => 'select',
    '#title' => t('Function'),
    '#description' => t('The function to use for calling xapi'),
    '#default_value' => variable_get('tincanapi_function', 'tincanapi_send'),
    '#required' => TRUE,
    '#options' => $tincanapisend,
  );

  $form['api']['tincanapi_auth_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#description' => t('The basic authenication password.'),
    '#default_value' => variable_get('tincanapi_auth_password', ''),
    '#required' => TRUE,
  );

  $form['api']['tincanapi_anonymous'] = array(
    '#type' => 'checkbox',
    '#title' => t('Track anonymous users.'),
    '#default_value' => variable_get('tincanapi_anonymous'),
  );

  $form['api']['tincanapi_watchdog'] = array(
    '#type' => 'checkbox',
    '#title' => t('Log server response.'),
    '#default_value' => variable_get('tincanapi_watchdog'),
  );

  $form['api']['tincanapi_simplify_id'] = array(
    '#type' => 'checkbox',
    '#title' => t('Simplify statements IDs (convert https urls to http)'),
    '#default_value' => variable_get('tincanapi_simplify_id'),
  );

  if (module_exists('token')) {
    $form['statements'] = array(
      '#type' => 'fieldset',
      '#title' => t('Statement Settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
    );

    $form['statements']['tincanapi_statement_actor'] = array(
      '#type' => 'textfield',
      '#title' => t('Statement Actor'),
      '#description' => t('The token replacements for the actor name in a statement.'),
      '#default_value' => variable_get('tincanapi_statement_actor'),
    );

    $form['statements']['token_help'] = array(
      '#theme' => 'token_tree',
      '#token_types' => array('user'),
    );
  }

  return system_settings_form($form);
}
