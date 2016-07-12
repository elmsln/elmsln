<?php

/**
 * @file
 * Settings administration UI.
 */


//----------------------------------------------------------------------------
// Form API callbacks.

/**
 * Form definition; general settings.
 */
function elmsln_cdn_admin_general_settings_form($form, &$form_state) {
  $form = array();

  $form['CDN_CHOICE'] = array(
    '#type' => 'radios',
    '#title' => t('CDN Choice'),
    '#description' => "This needs to be populated with a description.",
    '#required' => TRUE,
    '#options' => array(
      'CDN_JSDELIVR'  => t('jsDelivr (Supported in China)'),
      'CDN_CDNJS'  => t('CDNJS (No China Support)'),
      'CDN_DISABLED' => t('Disabled (i.e. Served Locally)'),
    ),
    '#default_value' => variable_get('CDN_CHOICE', 'CDN_JSDELIVR'),
  );

  return system_settings_form($form);
}
