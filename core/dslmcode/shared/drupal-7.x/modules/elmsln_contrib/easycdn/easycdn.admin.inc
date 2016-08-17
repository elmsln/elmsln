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
function easycdn_admin_general_settings_form($form, &$form_state) {
  $form = array();
  $rows = array();
  $header = array();

  $libraries = libraries_detect();
  foreach ($libraries as $machine_name => $library) {
    array_push($header, $libraries[$machine_name]['machine name']);
    // This is to specify the vertical tab holder.
    // One page can have two vertical tabs, but it's always one main tab with sub tabs.
    $form['easycdn']['explanation'] = array(
      '#title' => t('Choose from the libraries below and adjust its settings to choose to serve its files from a cdn or locally.'),
      );
    $form['easycdn'][$machine_name] = array(
      '#type' => 'fieldset',
      '#title' => t($machine_name),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
      );
      
    $form['easycdn'][$machine_name]['easycdn_cdn_' . $machine_name] = array(
      '#title' => t('CDN Choice'),
      '#type' => 'select',
      '#options' => array(
        'CDN_NONE' => t('Local'),
        'CDN_JSDELIVR' => t('jsDelivr (Supported in China)'),
        'CDN_CDNJS' => t('CDNJS (Limited China Support)'),
        ),
      '#default_value' => variable_get('easycdn_cdn_' . $machine_name, ''),

    );
    $form['easycdn'][$machine_name]['easycdn_version_' . $machine_name] = array(
      '#title' => t('Version'),
      '#type' => 'select',
      '#options' => array(
        $libraries[$machine_name]['version']
        ),
      '#default_value' => variable_get('easycdn_version_'. $machine_name, ''),
    );
  }
  return system_settings_form($form);
}
