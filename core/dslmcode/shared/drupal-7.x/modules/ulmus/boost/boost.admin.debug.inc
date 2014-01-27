<?php

/**
 * @file
 * Admin page callbacks for the boost module.
 */

/**
 * Form builder; Configure boost settings.
 *
 * @ingroup forms
 * @see system_settings_form()
 */
function boost_admin_debug_settings() {

  $form['boost_message_debug'] = array(
    '#type' => 'checkbox',
    '#title' => t('Send debug info for each request to watchdog.'),
    '#default_value' => variable_get('boost_message_debug', BOOST_MESSAGE_DEBUG),
    '#description' => t('Only use for debugging purposes as this can fill up watchdog fairly quickly.'),
  );

  // reset htaccess on submit;
  $form['#submit'][] = 'boost_form_submit_handler';
  return system_settings_form($form);
}
