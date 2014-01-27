<?php

/**
 * FAPI definition for the Shadowbox login settings form.
 *
 * @ingroup forms
 * @see login_shadowbox_settings_validate()
 */
function login_shadowbox_settings() {

  $form['login_shadowbox_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable shadowbox login'),
    '#description' => t('Enable this option if you want to be able to open your login form in shadowbox.'),
    '#default_value' => variable_get('login_shadowbox_enabled', FALSE),
  );

  $form['login_shadowbox_login'] = array(
    '#type' => 'fieldset',
    '#title' => 'Login Dimensions',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login_shadowbox_login']['login_shadowbox_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox login width'),
    '#description' => t('The width (in pixels) of shadowbox login form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_width', 500),
  );

  $form['login_shadowbox_login']['login_shadowbox_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox login height'),
    '#description' => t('The height (in pixels) of shadowbox login form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_height', 380),
  );

  $form['login_shadowbox_register'] = array(
    '#type' => 'fieldset',
    '#title' => 'Registration Dimensions',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login_shadowbox_register']['login_shadowbox_register_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox registration width'),
    '#description' => t('The width (in pixels) of shadowbox containing the registration form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_register_width', 500),
  );

  $form['login_shadowbox_register']['login_shadowbox_register_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox registration height'),
    '#description' => t('The height (in pixels) of shadowbox containing the registration form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_register_height', 440),
  );

  $form['login_shadowbox_password'] = array(
    '#type' => 'fieldset',
    '#title' => 'Reset Password Dimensions',
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['login_shadowbox_password']['login_shadowbox_password_width'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox reset password width'),
    '#description' => t('The width (in pixels) of shadowbox containing the reset password form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_password_width', 500),
  );

  $form['login_shadowbox_password']['login_shadowbox_password_height'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox reset password height'),
    '#description' => t('The height (in pixels) of shadowbox containing the reset password form when it appears on screen.'),
    '#size' => 5,
    '#maxlength' => 4,
    '#default_value' => variable_get('login_shadowbox_password_height', 240),
  );

  $form['login_shadowbox_modal'] = array(
    '#type' => 'checkbox',
    '#title' => t('Shadowbox modal'),
    '#description' => t('Check this box to prevent mouse clicks on the overlay from closing Shadowbox.'),
    '#default_value' => variable_get('login_shadowbox_modal', FALSE),
  );

  $form['login_shadowbox_css'] = array(
    '#type' => 'textfield',
    '#title' => t('Shadowbox login css file'),
    '#description' => t('The css file to stylize the shadowbox login dialog.'),
    '#size' => 60,
    '#maxlength' => 255,
    '#default_value' => variable_get('login_shadowbox_css', drupal_get_path('module', 'login_shadowbox') . '/css/login_shadowbox.css'),
  );

  return system_settings_form($form);
}

/**
 * Validate shadowbox login settings form inputs.
 */
function login_shadowbox_settings_validate($form, &$form_state) {

  $width = $form_state['values']['login_shadowbox_width'];
  $height = $form_state['values']['login_shadowbox_height'];

  if (!is_numeric($width) || $width < 0) {
    form_set_error('login_shadowbox_width', t('You must enter a positive number.'));
  }

  if (!is_numeric($height) || $height < 0) {
    form_set_error('login_shadowbox_height', t('You must enter a positive number.'));
  }

}
