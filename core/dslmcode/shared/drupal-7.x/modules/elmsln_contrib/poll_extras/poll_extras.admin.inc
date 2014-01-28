<?php
/**
 * Implements admin settings form.
 */
function poll_extras_admin_settings($form, &$form_state) {
  $form['poll_default_message'] = array(
    '#type' => 'textfield',
    '#title' => t('Default Message'),
    '#default_value' => variable_get('poll_default_message', 'Thank you for taking the poll!'),
    '#description' => t("This is the message that all polls will default to for users that don't have access to view poll results."),
  );
  return system_settings_form($form);
}
