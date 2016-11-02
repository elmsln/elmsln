<?php

/**
 * @file
 * Leaflet maps views integration.
 */

/**
 * Define leaflet views style.
 *
 * Implements hook_views_plugins().
 */
function leaflet_views_views_plugins() {
  $plugins = array(
    'module' => 'leaflet_views',
    'style' => array(
      'leaflet' => array(
        'title' => t('Leaflet Map'),
        'help' => t('Displays a View as a Leaflet map.'),
        'path' => drupal_get_path('module', 'leaflet_views'),
        'handler' => 'leaflet_views_plugin_style',
        'theme' => 'leaflet_map',
        'uses fields' => TRUE,
        'uses row plugin' => FALSE,
        'uses options' => TRUE,
        'uses grouping' => FALSE,
        'type' => 'normal',
        'even empty' => FALSE,
      ),
    ),
  );

  return $plugins;
}
