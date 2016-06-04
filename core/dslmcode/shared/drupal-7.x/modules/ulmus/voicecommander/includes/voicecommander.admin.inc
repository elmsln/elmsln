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

  $menus = menu_get_menus();
  unset($menus['management']);

  $form['voicecommander_menu'] = array(
    '#type'          => 'select',
    '#title'         => t('Select menu'),
    '#options'       => $menus,
    '#description'   => t('Menu items titles from selected menus will be use as voicecommaner commands.<br />
                        <em>*Management menu\'s items titles are using by default now with \'Administrator command prefix\'.</em>'),
    '#multiple'      => TRUE,
    '#default_value' => variable_get('voicecommander_menu', NULL),
  );

  $form['voicecommander_mobile'] = array(
    '#type'          => 'checkbox',
    '#title'         => t('Use commands on mobile devices'),
    '#default_value' => variable_get('voicecommander_mobile', 1),
  );

  return system_settings_form($form, TRUE);
}
