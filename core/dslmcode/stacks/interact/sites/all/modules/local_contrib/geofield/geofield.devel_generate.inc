<?php
/**
 * @file
 * Create random data to populate geofields.
 */

/**
 * Implements hook_devel_generate().
 */
function geofield_devel_generate($object, $field, $instance, $bundle) {
  if (field_behaviors_widget('multiple values', $instance) == FIELD_BEHAVIOR_CUSTOM) {
    return devel_generate_multiple('_geofield_devel_generate', $object, $field, $instance, $bundle);
  }
  else {
    return _geofield_devel_generate($object, $field, $instance, $bundle);
  }
}

function _geofield_devel_generate($object, $field, $instance, $bundle) {
  include_once(drupal_get_path('module', 'geofield') . '/includes/GeoGenerator.php');
  $generator = new GeoGenerator(); // @TODO: Make this static.
  $input = array();

  // Depending on the widget, we should assume limits on what kind of data to generate.
  switch ($instance['widget']['type']) {
    case 'geofield_latlon':
      $input['geom'] = array();
      list($input['geom']['lon'], $input['geom']['lat']) = $generator->random_point();
      $input['input_format'] = GEOFIELD_INPUT_LAT_LON;
      break;
    case 'geofield_bounds':
      // Instead of calculating 4 separate points, calculate a center point and
      // distance from it.
      list($lon, $lat) = $generator->random_point();
      $lat_diff = $generator->dd_generate(2, 10) / 100;
      $lon_diff = $generator->dd_generate(2, 10) / 100;
      $input = array(
        'left' => $lon - $lon_diff,
        'right' => $lon + $lon_diff,
        'top' => $lat - $lat_diff,
        'bottom' => $lat + $lat_diff,
        'input_format' => GEOFIELD_INPUT_BOUNDS,
      );
      break;
    default:
      $input = array(
        'geom' => $generator->wkt_generate(),
        'input_format' => GEOFIELD_INPUT_WKT,
      );
  }

  return $input;
}
