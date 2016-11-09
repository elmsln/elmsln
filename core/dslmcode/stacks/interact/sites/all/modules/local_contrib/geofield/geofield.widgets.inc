<?php

/**
 * @file
 * Provides field widget hooks for geofield module.
 */

/**
 * Geofield Input format - auto-discover.
 */
define('GEOFIELD_INPUT_AUTO_DISCOVER', 'auto-discover');

/**
 * Geofield Input format - WKT.
 */
define('GEOFIELD_INPUT_WKT', 'wkt');

/**
 * Geofield Input format - GeoJSON.
 */
define('GEOFIELD_INPUT_GEOJSON', 'json');

/**
 * Geofield Input format - lat/lon.
 */
define('GEOFIELD_INPUT_LAT_LON', 'lat/lon');

/**
 * Geofield Input format - bounds.
 */
define('GEOFIELD_INPUT_BOUNDS', 'bounds');

// If we have the Openlayers module installed, include their widget code.

if (module_exists('openlayers')) {
  module_load_include('inc', 'geofield', 'geofield.widgets.openlayers');
}

/**
 * Implements hook_field_widget_info().
 */
function geofield_field_widget_info() {
  $widgets = array();

  // OpenLayers dependant widget
  if (module_exists('openlayers')) {
    $widgets['geofield_openlayers'] = array(
      'label' => t('Openlayers Map'),
      'field types' => array('geofield'),
    );
  }

  $widgets['geofield_wkt'] = array(
    'label' => t('Well Known Text (WKT)'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_geojson'] = array(
    'label' => t('GeoJSON'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_latlon'] = array(
    'label' => t('Latitude / Longitude'),
    'field types' => array('geofield'),
  );
  $widgets['geofield_bounds'] = array(
    'label' => t('Bounds'),
    'field types' => array('geofield'),
  );

  return $widgets;
}

/**
 * Implements hook_field_widget_settings_form().
 */
function geofield_field_widget_settings_form($field, $instance) {
  $widget = $instance['widget'];
  $settings = $widget['settings'];

  $form = array();

  if ($widget['type'] == 'geofield_latlon') {
    $form['html5_geolocation'] = array(
      '#type' => 'checkbox',
      '#title' => 'Use HTML5 Geolocation to set default values',
      '#default_value' => (!empty($settings['html5_geolocation'])) ? $settings['html5_geolocation'] : FALSE,
    );
  }

  return $form;
}


/**
 * Implements hook_field_widget_form().
 */
function geofield_field_widget_form(&$form, &$form_state, $field, $instance,
  $langcode, $items, $delta, $base) {
  $element = $base;

  $widget = $instance['widget'];
  $settings = $widget['settings'];

  // $element['input_format'] is not a db field, but we use it determine how to parse/calculate values in our widget.
  $element['input_format'] = array(
    '#type' => 'value',
    '#attributes' => array('class' => array('geofield_input_format')),
    '#value' => GEOFIELD_INPUT_AUTO_DISCOVER,
  );

  // All of our widgets are keyed to 'geom,' we calculate proper field values in geofield_field_presave().
  switch ($widget['type']) {
    case 'geofield_wkt':
      $default_value = '';
      if (!empty($items[$delta]['geom'])) {
        geophp_load();
        $geometry = geoPHP::load($items[$delta]['geom']);
        $default_value = $geometry->out('wkt');
      }
      $element['geom'] = array(
        '#type' => 'textarea',
        '#title' => check_plain($instance['label']),
        '#description' => t($instance['description']),
        '#default_value' => $default_value,
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_WKT;
      break;
    case 'geofield_geojson':
      $default_value = '';
      if (!empty($items[$delta]['geom'])) {
        geophp_load();
        $geometry = geoPHP::load($items[$delta]['geom']);
        $default_value = $geometry->out('json');
      }

      $element['geom'] = array(
        '#type' => 'textarea',
        '#title' => check_plain($instance['label']),
        '#description' => t($instance['description']),
        '#default_value' => $default_value,
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_GEOJSON;
      break;
    case 'geofield_latlon':
      $latlon_value = array(
        'lat' => '',
        'lon' => '',
      );
      if (isset($items[$delta]['lat'])) {
        $latlon_value['lat'] = floatval($items[$delta]['lat']);
      }
      if (isset($items[$delta]['lon'])) {
        $latlon_value['lon'] = floatval($items[$delta]['lon']);
      }
      $element['geom'] = array(
        '#type' => 'geofield_latlon',
        '#title' => check_plain($instance['label']),
        '#description' => t($instance['description']),
        '#default_value' => $latlon_value,
        '#required' => $instance['required'],
        '#geolocation' => (!empty($instance['widget']['settings']['html5_geolocation'])) ? $instance['widget']['settings']['html5_geolocation'] : FALSE,
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_LAT_LON;
      break;
    case 'geofield_bounds':
      $bounds_value = array(
        'top' => '',
        'right' => '',
        'bottom' => '',
        'left' => '',
      );
      if (isset($items[$delta]['top'])) {
        $bounds_value['top'] = floatval($items[$delta]['top']);
      }
      if (isset($items[$delta]['right'])) {
        $bounds_value['right'] = floatval($items[$delta]['right']);
      }
      if (isset($items[$delta]['bottom'])) {
        $bounds_value['bottom'] = floatval($items[$delta]['bottom']);
      }
      if (isset($items[$delta]['left'])) {
        $bounds_value['left'] = floatval($items[$delta]['left']);
      }
      $element['geom'] = array(
        '#type' => 'geofield_bounds',
        '#title' => check_plain($instance['label']),
        '#description' => t($instance['description']),
        '#default_value' => $bounds_value,
        '#required' => $instance['required'],
      );

      $element['input_format']['#value'] = GEOFIELD_INPUT_BOUNDS;
      break;
  }
  return $element;
}
