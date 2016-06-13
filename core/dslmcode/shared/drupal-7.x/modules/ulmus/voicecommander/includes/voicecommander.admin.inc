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
    '#description'   => t('Enter command prefix. Use command for example: "Drupal home page". Where word "Drupal" is prefix.'),
  );
  $form['voicecommander_optional_prefix'] = array(
    '#title'         => t('Prefix is optional'),
    '#type'          => 'checkbox',
    '#default_value' => variable_get('voicecommander_optional_prefix', TRUE),
    '#description'   => t('If enabled, then the prefix won\'t be required for usage. This can allow for a more natural form of conversation.'),
  );
  $form['voicecommander_continuous'] = array(
    '#title'         => t('Allow continuous operation mode'),
    '#type'          => 'checkbox',
    '#default_value' => variable_get('voicecommander_continuous', FALSE),
    '#description'   => t('If enabled, then voice commander will be listening at all times for commands. This can cause performance issues potenitally as well as just be kinda creepy so use with caution. Currently this is only for administrator users. If this is active, it overrides the keypress and mobile methods.'),
  );
  $form['voicecommander_mobile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use commands on mobile devices'),
    '#default_value' => variable_get('voicecommander_mobile', 1),
  );

  return system_settings_form($form, TRUE);
}
