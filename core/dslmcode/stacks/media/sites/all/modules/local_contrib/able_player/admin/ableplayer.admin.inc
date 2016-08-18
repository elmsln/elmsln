<?php

/**
 * @file
 * Administration callbacks for Able Player.
 */

/**
 * Form constructor for the Able Player administration form.
 */
function ableplayer_form() {
  $form = array();

  $form['ableplayer_fieldset'] = array(
    '#type' => 'fieldset',
    '#title' => t('Able Player'),
    '#collapsible' => FALSE,
  );

  $form['ableplayer_fieldset']['ableplayer_compression_level'] = array(
    '#type' => 'radios',
    '#title' => t('Compression level'),
    '#description' => t(
      'Development provides a human-readable version of JavaScript and CSS.
      Production combines and minifies both to conserve bandwidth.'),
    '#default_value' => variable_get('ableplayer_compression_level', 1),
    '#options' => array(
      0 => t('Development'),
      1 => t('Production'),
    ),
  );

  $form['ableplayer_fieldset']['ableplayer_test_fallback'] = array(
    '#type' => 'checkbox',
    '#title' => t('Test Fallback'),
    '#description' => t(
      'Force Able Player to load the fallback player (jwplayer). This is recommended for testing purposes only.'),
    '#default_value' => variable_get('ableplayer_test_fallback', 0),
  );

  return system_settings_form($form);
}
