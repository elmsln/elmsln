<?php

/**
 * @file
 * Definition of variables for Variable API module.
 */

/**
 * Implements hook_variable_info().
 */
function piwik_variable_info($options) {
  $variables['piwik_site_id'] = array(
    'type' => 'string',
    'title' => t('Piwik site ID', array(), $options),
    'default' => '',
    'description' => t('The user account number is unique to the websites domain. Click the <strong>Settings</strong> link in your Piwik account, then the <strong>Websites</strong> tab and enter the appropriate site <strong>ID</strong> into this field.'),
    'required' => TRUE,
    'group' => 'piwik',
    'localize' => TRUE,
    'multidomain' => TRUE,
    'validate callback' => 'piwik_validate_piwik_site_id',
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function piwik_variable_group_info() {
  $groups['piwik'] = array(
    'title' => t('Piwik'),
    'description' => t('Configure tracking behavior to get insights into your website traffic and marketing effectiveness.'),
    'access' => 'administer piwik',
    'path' => array('admin/config/system/piwik'),
  );

  return $groups;
}

/**
 * Validate Piwik site ID variable.
 *
 * @param array $variable
 *
 * @return string
 */
function piwik_validate_piwik_site_id($variable) {
  if (!preg_match('/^\d{1,}$/', $variable['value'])) {
    return t('A valid Piwik site ID is an integer only.');
  }
}
