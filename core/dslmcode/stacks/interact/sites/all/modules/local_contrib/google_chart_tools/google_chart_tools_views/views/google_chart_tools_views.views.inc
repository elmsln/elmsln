<?php
/**
 * @file
 * Chart views integration.
 */

/**
 * Implements hook_views_plugins().
 */
function google_chart_tools_views_views_plugins() {
  return array(
    'module' => 'google_chart_tools_views',
    'style'  => array(
      'google_chart_tools_views' => array(
        'handler' => 'google_chart_tools_views_plugin_style',
        'help' => t('Displays Views results as Google Chart Tools.'),
        'path' => drupal_get_path('module', 'google_chart_tools_views') . '/views',
//        'theme' => 'views_view_table',
        'title' => t('Google Chart Tools'),
        'type' => 'normal',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'uses row plugin' => FALSE,
        'uses row class' => TRUE,
      ),
    )
  );
}
