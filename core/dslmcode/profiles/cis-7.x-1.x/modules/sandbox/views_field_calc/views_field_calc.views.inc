<?php
/**
 * @file
 * Views plugin.
 */

/**
 * Implements hook_views_plugins().
 */
function views_field_calc_views_plugins() {
  $path = drupal_get_path('module', 'views_field_calc');
  $views_path = drupal_get_path('module', 'views');
  require_once DRUPAL_ROOT . '/' . $path . '/views_field_calc.theme.inc';

  $data = array(
    'module' => 'views_field_calc', // This just tells our themes are elsewhere.
    'style' => array(
      // Style plugin for the navigation.
      'views_field_calc' => array(
        'title' => t('Views field calc table'),
        'help' => t('Creates a table with column calculations using fields.'),
        'handler' => 'views_field_calc_table',
        'path' => $path,
        'parent' => 'table',
        'theme' => 'views_field_calc_table',
        'theme file' => 'views_field_calc.theme.inc',
        'theme path' => "$path",
        'uses row plugin' => FALSE,
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
    ),
  );
  return $data;
}
