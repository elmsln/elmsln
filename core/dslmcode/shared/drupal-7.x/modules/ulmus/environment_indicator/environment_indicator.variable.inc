<?php
/**
 * @file
 * Variables module integration.
 */

/**
 * Implements hook_variable_info().
 */
function environment_indicator_variable_info() {
  $variables['environment_indicator_overwrite'] = array(
    'type' => 'boolean',
    'title' => t('Overwritten'),
    'description' => t('Should the Environment Indicator be overwritten?'),
    'default' => FALSE,
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_overwritten_color'] = array(
    'title' => t('Color'),
    'description' => t('Color for the indicator. Ex: #d0d0d0.'),
    'default' => '#aa3333',
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_overwritten_text_color'] = array(
    'title' => t('Color'),
    'description' => t('Text color for the indicator. Ex: #ffffff.'),
    'default' => '#ffffff',
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_overwritten_fixed'] = array(
    'type' => 'boolean',
    'title' => t('Fixed'),
    'default' => TRUE,
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_overwritten_position'] = array(
    'type' => 'select',
    'title' => t('Position'),
    'options' => array(
      'top' => t('Top'),
      'bottom' => t('Bottom'),
    ),
    'default' => 'top',
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_overwritten_name'] = array(
    'title' => t('Name'),
    'description' => t('Name for this environment.'),
    'default' => 'Default environment',
    'group' => 'environment_indicator',
  );

  $variables['environment_indicator_suppress_pages'] = array(
    'type' => 'text',
    'title' => t('Turn off Environment Indicator on these pages'),
    'description' => t("Enter one page per line as Drupal paths. The '*' character is a wildcard. Example paths are 'blog' for the blog page and 'blog/*' for every personal blog. '<front>' is the front page."),
    'default' => '',
    'group' => 'environment_indicator',
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function environment_indicator_variable_group_info() {
  $groups['environment_indicator'] = array(
    'title' => t('Environment Indicator'),
    'description' => t('Environment Indicator variables'),
    'access' => 'administer environment indicator settings',
  );

  return $groups;
}
