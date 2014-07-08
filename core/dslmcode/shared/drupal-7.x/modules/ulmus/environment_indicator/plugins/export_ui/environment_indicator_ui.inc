<?php

/**
 * Define this Export UI plugin.
 */
$plugin = array(
  'schema' => 'environment_indicator_environment',
  'access' => 'administer environment indicator settings',

  // Define the menu item.
  'menu' => array(
    'menu prefix' => 'admin/config/development',
    'menu item' => 'environment-indicator',
    'menu title' => 'Environment indicators',
    'menu description' => 'Administer environment indicators.',
  ),

  // Define user interface texts.
  'title singular' => t('environment'),
  'title plural' => t('environments'),
  'title singular proper' => t('Environment indicator'),
  'title plural proper' => t('Environment indicators'),

  // Define the names of the functions that provide the add/edit forms.
  'form' => array(
    'settings' => 'environment_indicator_ui_form',
    'validate' => 'environment_indicator_ui_validate',
    'submit' => 'environment_indicator_ui_form_submit',
  ),
  'handler' => array(
    'class' => 'ctools_export_ui_environment_indicator',
    'parent' => 'ctools_export_ui',
  ),
);
