<?php

/**
 * Schema.org format.
 *
 * Formats shapes for output in metadata using Schema.org format. This is
 * different from the WKT format provided by GeoGenerator, so just use a one
 * off function.
 */
function geofield_schemaorg_shape($item) {
  $output = '';
  $bottom = $item['bottom'];
  $left = $item['left'];
  $right = $item['right'];
  $top = $item['top'];

  switch ($item['geo_type']) {
    case 'polygon':
      $output  = $bottom . ',' . $left . ' ';
      $output .= $bottom . ',' . $right . ' ';
      $output .= $top . ',' . $right . ' ';
      $output .= $top . ',' . $left . ' ';
      $output .= $bottom . ',' . $left;
      break;
    case 'linestring':
      $output  = $bottom . ',' . $left . ' ';
      $output .= $bottom . ',' . $right . ' ';
      $output .= $top . ',' . $right . ' ';
      $output .= $top . ',' . $left;
      break;
  }

  return $output;
}

/**
 * Callback to alter the property info of geofield fields.
 *
 * @see geofield_field_info()
 */
function geofield_property_info_callback(&$info, $entity_type, $field, $instance, $field_type) {
  $name = $field['field_name'];
  $property = &$info[$entity_type]['bundles'][$instance['bundle']]['properties'][$name];

  $property['type'] = ($field['cardinality'] != 1) ? 'list<geofield>' : 'geofield';
  $property['getter callback'] = 'entity_metadata_field_verbatim_get';
  $property['setter callback'] = 'entity_metadata_field_verbatim_set';
//  $property['auto creation'] = 'geofield_default_values';
  $property['property info'] = geofield_data_property_info('Geofield');
  unset($property['query callback']);
}

/**
 * Defines info for the properties of the geofield field data structure.
 */
function geofield_data_property_info($name = NULL) {
  // Build an array of basic property information for the geofield field.

  // If any of these should have individual options to set microdata
  // properties is not clear. Lat, Lon work fine. Other data is more
  // complicated. Geo_type relates (not 1:1) with the itemprop within
  // a GeoShape, with an alternate representation of the wkt for the content
  // (at its simplest).
  $properties = array(
    'geom' => array(
      'label' => 'Well-known text',
      'type' => 'text',
      'microdata' => FALSE,
    ),
    'geo_type' => array(
      'label' => 'Geo Type',
      'options list' => '_geofield_geo_types_options_callback',
      'required' => TRUE,
      'microdata' => FALSE,
    ),
    'lat' => array(
      'label' => 'Latitude',
      'type' => 'decimal',
      'required' => TRUE,
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => TRUE,
    ),
    'lon' => array(
      'label' => 'Longitude',
      'type' => 'decimal',
      'required' => TRUE,
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => TRUE,
    ),
    'left' => array(
      'label' => 'Left Latitude',
      'type' => 'decimal',
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => FALSE,
    ),
    'top' => array(
      'label' =>  'Top Longitude',
      'type' => 'decimal',
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => FALSE,
    ),
    'right' => array(
      'label' => 'Right Latitude',
      'type' => 'decimal',
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => FALSE,
    ),
    'bottom' => array(
      'label' => 'Bottom Longitude',
      'type' => 'decimal',
      'setter callback' => 'entity_property_verbatim_set',
      'microdata' => FALSE,
    ),
    'srid' => array(
      'label' => 'Projection (SRID)',
      'type' => 'integer',
      'microdata' => FALSE,
    ),
    'latlon' => array(
      'label' => 'LatLong Pair',
      'type'  => 'string',
      'getter callback' => 'geofield_return_latlon',
      'microdata' => FALSE,
    ),
    'schemaorg_shape' => array(
      'label' => 'Schema.org Shape',
      'type' => 'string',
      'getter callback' => 'geofield_return_schemaorg_shape',
      'microdata' => TRUE,
    ),
  );

  // Add the default values for each of the geofield properties.
  foreach ($properties as $key => &$value) {
    $value += array(
      'description' => !empty($name) ? t('!label of field %name', array('!label' => $value['label'], '%name' => $name)) : '',
      'getter callback' => 'entity_property_verbatim_get',
    );
  }

  return $properties;
}


function _geofield_geo_types_options_callback() {
  $geophp = geophp_load();
  if (!$geophp) {
    return;
  }
  return geoPHP::geometryList();
}

/**
 * Gets the a latlong property.
 */
function geofield_return_latlon($data, array $options, $name) {
  if ((is_array($data) || (is_object($data) && $data instanceof ArrayAccess)) && !is_null($data['lat']) && !is_null($data['lon'])) {
    return $data['lat'] . ',' . $data['lon'];
  }
  return NULL;
}

/**
 * Gets the Schema.org formatted shape value.
 */
function geofield_return_schemaorg_shape($data, array $options, $name) {
  if ((is_array($data) || (is_object($data) && $data instanceof ArrayAccess))) {
    return geofield_schemaorg_shape($data);
  }
  return NULL;
}
