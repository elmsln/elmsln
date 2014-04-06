<?php

/**
 * @file
 * Admin page callbacks for the speedreader module.
 */
function speedreader_settings() {
  // default selector for speedreader to target what to read
  $form['speedreader_selector'] = array(
    '#type' => 'text',
    '#title' => t('Selector'),
    '#description' => t('jQuery selector for text to apply speed reading to.'),
    '#options' => $window,
    '#default_value' => variable_get('speedreader_selector', SPEEDREADER_SELECTOR),
    '#required' => TRUE,
  );
  return system_settings_form($form);
}
