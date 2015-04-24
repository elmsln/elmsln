<?php

/**
 * @file
 * Admin page callbacks for the mespeak module.
 */
function mespeak_settings() {
  // default selector for mespeak to target what to read
  $form['mespeak_selector'] = array(
  	'#type' => 'textfield',
    '#title' => t('Selector'),
    '#description' => t('jQuery selector for text to apply mespeak reading to.'),
    '#default_value' => variable_get('mespeak_selector', MESPEAK_SELECTOR),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
