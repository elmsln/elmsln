<?php
/**
 * @file
 * Settings interface.
 */

/**
 * Callback function for voicecommander_settings_form().
 */
function voicecommander_settings_form($form, &$form_state) {
  $form['voicecommander_prefix'] = array(
    '#title'         => t('Administartor command prefix'),
    '#type'          => 'textfield',
    '#required'      => TRUE,
    '#default_value' => variable_get('voicecommander_prefix', VOICECOMMANDER_DEFAULT_VALUE_PREFIX_NAME),
    '#description'   => t('Enter command prefix. Use command for example: "Drupal home page". Where word "Drupal" is prefix.<br />
                            <em>It use only for administrator permission</em>.'),
  );

  $form['voicecommander_mobile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use commands on mobile devices'),
    '#default_value' => variable_get('voicecommander_mobile', 1),
  );

  return system_settings_form($form, TRUE);
}
