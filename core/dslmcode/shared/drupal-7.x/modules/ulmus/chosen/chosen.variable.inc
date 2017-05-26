<?php
/**
 * @file
 * Definition of variables for Variable API module.
 */

/**
 * Implements hook_variable_info().
 */
function chosen_variable_info($options) {
  $variables['chosen_placeholder_text_multiple'] = array(
    'type' => 'string',
    'title' => t('Placeholder text of multiple selects'),
    'default' => 'Choose some options',
    'required' => TRUE,
    'group' => 'chosen',
    'localize' => TRUE,
  );

  $variables['chosen_placeholder_text_single'] = array(
    'type' => 'string',
    'title' => t('Placeholder text of single selects'),
    'default' => 'Choose an option',
    'required' => TRUE,
    'group' => 'chosen',
    'localize' => TRUE,
  );

  $variables['chosen_no_results_text'] = array(
    'type' => 'string',
    'title' => t('No results text'),
    'default' => 'No results match',
    'required' => TRUE,
    'group' => 'chosen',
    'localize' => TRUE,
  );

  return $variables;
}

/**
 * Implements hook_variable_group_info().
 */
function chosen_variable_group_info() {
  $groups['chosen'] = array(
    'title' => t('Chosen'),
    'description' => t('Chosen javascript library.'),
    'access' => 'administer site configuration',
    'path' => array('admin/config/user-interface/chosen'),
  );

  return $groups;
}
