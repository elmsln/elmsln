<?php

/**
 * Admin form for users to define paths for automated accessibility testing.
 */
function accessibility_testswarm_admin_form() {
  $form = array();
  
  $form['accessibility_testswarm_paths'] = array(
    '#type' => 'textarea',
    '#title' => t('Enter a list of Drupal paths to test using testswarm'),
    '#default_value' => variable_get('accessibility_testswarm_paths', ''),
  );
  
  return system_settings_form($form);
}