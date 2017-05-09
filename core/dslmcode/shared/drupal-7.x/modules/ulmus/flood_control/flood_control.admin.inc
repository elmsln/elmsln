<?php

/**
 * @file
 * Admin page callbacks for the flood_control module.
 */

/**
 * Administration settings form.
 *
 * @see system_settings_form()
 */
function flood_control_settings_form() {
  // User module flood events.
  $form['login'] = array(
    '#type' => 'fieldset',
    '#title' => t('Login'),
    '#access' => user_access('administer users'),
  );
  $form['login']['user_failed_login_ip_limit'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (IP) limit'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => variable_get('user_failed_login_ip_limit', 50),
  );
  $form['login']['user_failed_login_ip_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (IP) window'),
    '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => variable_get('user_failed_login_ip_window', 3600),
  );
  $form['login']['user_failed_login_user_limit'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (username) limit'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => variable_get('user_failed_login_user_limit', 5),
  );
  $form['login']['user_failed_login_user_window'] = array(
    '#type' => 'select',
    '#title' => t('Failed login (username) window'),
    '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => variable_get('user_failed_login_user_window', 21600),
  );

  // Contact module flood events.
  $form['contact'] = array(
    '#type' => 'fieldset',
    '#title' => t('Contact forms'),
    '#access' => user_access('administer contact forms'),
  );
  $form['contact']['contact_threshold_limit'] = array(
    '#type' => 'select',
    '#title' => t('Sending e-mails limit'),
    '#options' => drupal_map_assoc(array(1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 20, 30, 40, 50, 75, 100, 125, 150, 200, 250, 500)),
    '#default_value' => variable_get('contact_threshold_limit', 5),
  );
  $form['contact']['contact_threshold_window'] = array(
    '#type' => 'select',
    '#title' => t('Sending e-mails window'),
    '#options' => array(0 => t('None (disabled)')) + drupal_map_assoc(array(60, 180, 300, 600, 900, 1800, 2700, 3600, 10800, 21600, 32400, 43200, 86400), 'format_interval'),
    '#default_value' => variable_get('contact_threshold_window', 3600),
  );

  // Show a message if the user does not have any access to any options.
  if (!element_get_visible_children($form)) {
    $form['nothing'] = array(
      '#markup' => '<p>' . t('Sorry, there are no flood control options for you to configure.') . '</p>',
    );
  }
  else {
    $form = system_settings_form($form);
  }

  return $form;
}
