<?php

/**
 * implements hook_microdata_value_types_alter().
 */
function geofield_microdata_value_types_alter(&$types) {
  $types['geofield'] = 'item_option';
}

/**
 * Implements hook_microdata_suggestions().
 */
function geofield_microdata_suggestions() {
  $suggestions = array();

  // Standard suggestion for co-ordinates.
  // http://schema.org/GeoCoordinates
  //
  // Output example:
  // <div itemprop="geo" itemscope itemtype="http://schema.org/GeoCoordinates">
  //   Latitude: 40 deg 44 min 54.36 sec N
  //   Longitude: 73 deg 59 min 8.5 dec W
  //   <meta itemprop="latitude" content="40.75" />
  //   <meta itemprop="longitude" content="73.98" />
  // </div>
  $suggestions['fields']['geofield']['schema.org/GeoCoordinates'] = array(
    '#itemprop' => array('geo'),
    '#is_item' => TRUE,
    '#itemtype' => array('http://schema.org/GeoCoordinates'),
    'wkt' => array(
      '#itemprop' => array('latitude', 'longitude'),
    ),
    'lat' => array(
      '#itemprop' => array('latitude'),
    ),
    'lon' => array(
      '#itemprop' => array('longitude'),
    ),
    'latlon' => array(
      '#itemprop' => array('latitude', 'longitude'),
    ),
  );

  // Suggestion for more complicated shapes.
  // http://schema.org/GeoShape
  //
  // Output example:
  // <div itemprop="geo" itemscope itemtype="http://schema.org/GeoShape">
  //   WKT: LINESTRING (30 10, 10 30, 40 40)
  //   <meta itemprop="line" content="30 10 10 30 40 40"/>
  // </div>
  $shape_base = array(
    '#itemprop' => array('geo'),
    '#is_item' => TRUE,
    '#itemtype' => array('http://schema.org/GeoShape'),
  );

  // Suggestion for a line.
  $suggestions['fields']['geofield']['schema.org/GeoShape line'] = $shape_base;
  $suggestions['fields']['geofield']['schema.org/GeoShape line']['schemaorg_shape']['#itemprop'] = array('line');

  // Suggestion for a polygon.
  $suggestions['fields']['geofield']['schema.org/GeoShape polygon'] = $shape_base;
  $suggestions['fields']['geofield']['schema.org/GeoShape polygon']['schemaorg_shape']['#itemprop'] = array('polygon');

  return $suggestions;
}