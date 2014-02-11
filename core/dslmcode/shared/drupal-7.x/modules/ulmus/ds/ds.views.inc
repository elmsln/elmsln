<?php

/**
 * @file
 * Views hooks file.
 */

/**
 * Implements hook_views_plugins().
 */
function ds_views_plugins() {
  $path = drupal_get_path('module', 'ds');
  $views_plugins = array(
    'module' => 'ds',
    'row' => array(
      'ds' => array(
        'title' => t('Display Suite'),
        'help' => t('Display the entity with the Display Suite module.'),
        'handler' => 'views_plugin_ds_entity_view',
        'path' => $path . '/views',
        'base' => array('node', 'comment', 'users', 'apachesolr', 'taxonomy_term_data', 'file_managed', 'micro'),
        'theme' => 'ds_row_entity',
        'uses options' => TRUE,
        'type' => 'normal',
      ),
    ),
  );

  if (module_exists('ds_extras') && variable_get('ds_extras_vd')) {
    $views_plugins['row']['ds_fields'] = array(
      'uses fields' => TRUE,
      'title' => t('Display Suite fields'),
      'help' => t('Display fields through the Display Suite module.'),
      'handler' => 'views_plugin_ds_fields_view',
      'path' => $path . '/views',
      'theme' => 'ds_row_fields',
      'theme path' => $path . '/views',
      'theme file' => 'views_plugin_ds_fields_view.inc',
      'uses options' => TRUE,
      'type' => 'normal',
    );
  }

  return $views_plugins;
}
