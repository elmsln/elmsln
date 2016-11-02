<?php

/**
 * @file
 * Hooks for Views integration.
 *
 * In addition to the usual views hooks, Geofield defines a set of classes that allows
 * us to break out the code needed to handle the wide variety of proximity searches 
 * the module supports. We define api functions here to allow for very basic autoloading.
 * 
 * Our mini-plugin system we're using here is not designed for external (non-geofield) use,
 * but as a programming convenience for the maintainers.
 */

/**
 * Implements hook_field_views_data().
 *
 * Views integration for geofields.
 *
 */
function geofield_field_views_data($field) {
  $data = field_views_field_default_views_data($field);
  $field_name = $field['field_name'];

  foreach ($data as $table_name => $table_data) {
    if (isset($table_data[$field_name])) {
      $group_name = $table_data[$field_name]['group'];
      $title = $table_data[$field_name]['title'] . " ($field_name) - proximity";
      $data[$table_name]['field_geofield_distance'] = array(
        'group' => $group_name,
        'title' => $title,
        'title short' => $title,
        'help' => $table_data[$field_name]['help'],
        'sort' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_sort',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
        'field' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_field',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
          'float' => TRUE,
          'click sortable' => TRUE,
        ),
        'filter' => array(
          'field' => 'field_geofield_distance',
          'table' => $table_name,
          'handler' => 'geofield_handler_filter',
          'field_name' => $field['field_name'],
          'real_field' => $table_name,
        ),
        'argument' => array(
          'handler' => 'geofield_handler_argument_proximity',
          'field_name' => $field['field_name'],
        ),
      );
    }
  }
  return $data;
}

/**
 * Implements hook proximity_views_handlers().
 *
 * Returns metainfo about each of the geofield proximity views classes.
 */

function geofield_proximity_views_handlers() {
  $handlers = array(
    'manual' => array(
      'name' => t('Manually Enter Point'),
      'class' => 'geofieldProximityManual',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
    'entity_from_url' => array(
      'name' => t('Entity From URL'),
      'class' => 'geofieldProximityEntityURL',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
    'current_user' => array(
      'name' => t('Current User'),
      'class' => 'geofieldProximityCurrentUser',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
    'other_geofield' => array(
      'name' => t('Other Geofield'),
      'class' => 'geofieldProximityOtherGeofield',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
    'exposed_geofield_filter' => array(
      'name' => t('Exposed Geofield Proximity Filter'),
      'class' => 'geofieldProximityExposedFilter',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
    'contextual_geofield_filter' => array(
      'name' => t('Contextual Geofield Proximity Filter'),
      'class' => 'geofieldProximityContextualFilter',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    ),
  );

  if (module_exists('geocoder')) {
    $handlers['geocoder'] = array(
      'name' => t('Geocoded Location'),
      'class' => 'geofieldProximityGeocoder',
      'module' => 'geofield',
      'path' => 'views/proximity_plugins',
    );
  }

  return $handlers;
}

/**
 * Loads an individual geofield proximity views class.
 * 
 * @return
 *   An instance of a class defined by $plugin (see keys for geofield_proximity_views_handlers), or FALSE
 *   if no such class exists.
 */

function geofield_proximity_load_plugin($plugin) {
  $handlers = module_invoke_all('proximity_views_handlers');
  //module_load_include('inc', 'geofield', 'views/proximity_plugins/geofieldProximityManual');
  module_load_include('inc', $handlers[$plugin]['module'], $handlers[$plugin]['path'] . '/' . $handlers[$plugin]['class']);
  if (class_exists($handlers[$plugin]['class'])) {
    return new $handlers[$plugin]['class'];
  }
  else {
    return FALSE;
  }
}
