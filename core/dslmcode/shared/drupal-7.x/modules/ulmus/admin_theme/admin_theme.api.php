<?php
// $Id: admin_theme.api.php,v 1.1.2.1 2008/12/13 09:47:29 davyvandenbremt Exp $

/**
 * @file
 * Hooks provided by the Administration theme module.
 */

/**
 * @addtogroup hooks
 * @{
 */

/**
 * Add more options to the administration theme settings page.
 *
 * This hook allows modules to add more options to the administration theme 
 * settings page.
 *
 * @return
 *   A linear array of associative arrays. The keys of the linear array are 
 *   the identifiers for the "options" that will be check for in 
 *   hook_admin_theme_check. The associative arrays have keys:
 *   - "title": The title to display on the checkbox on the administration 
 *     theme settings page.
 *   - "description": The description to display on the checkbox on the 
 *     administration theme settings page.
 */
function hook_admin_theme_info() {
  $options = array();
  $options['batch'] = array(
    'title' => t('Use administration theme for batch processing'),
    'description' => t('Use the administration theme when executing batch operations.'),
  );
  if (module_exists('coder')) {
    $options['coder'] = array(
      'title' => t('Use administration theme for code reviews'),
      'description' => t('Use the administration theme when viewing Coder code reviews.'),
    );
  }
  if (module_exists('service_attachments')) {
    $options['service_attachments'] = array(
      'title' => t('Use administration theme for viewing the service attachments form on nodes.'),
      'description' => t('Use the administration theme when viewing service attachments on nodes.'),
    );
  }
  if (module_exists('webform')) {
    $options['webform_results'] = array(
      'title' => t('Use administration theme for viewing webform submissions.'),
      'description' => t('Use the administration theme when viewing webform submissions.'),
    );
  }
  if (module_exists('statistics')) {
    $options['statistics'] = array(
      'title' => t('Use administration theme for viewing pages of the statistics module.'),
      'description' => t('Use the administration theme when viewing pages of the statistics module.'),
    );
  }
  return $options;
}

/**
 * Check if an option is "on" for the current page.
 *
 * This hook allows modules to check for each option defined in 
 * hook_admin_theme_info if the option is "on".
 *
 * @param
 *   $option. The option to check.
 * @return
 *   TRUE or FALSE indicating if the administration theme should be used.
 */
function hook_admin_theme_check($option = NULL) {
  switch ($option) {
    case 'coder':
      return arg(0) == 'coder';
    case 'batch':
      return arg(0) == 'batch';
    case 'service_attachments':
      return arg(0) == 'node' && arg(2) == 'service_attachments';
    case 'webform_results':
      return arg(0) == 'node' && arg(2) == 'webform-results';
    case 'statistics':
      return (arg(0) == 'node' || arg(0) == 'user') && arg(2) == 'track';
  }
}

/**
 * @} End of "addtogroup hooks".
 */