<?php

$plugin = array(
  'title' => 'Default',
  'schema' => 'geofield_backend_default_schema',
  'save' => 'geofield_backend_default_save',
  'load' => 'geofield_backend_default_load',
  'types' => array('Point','LineString','Polygon','MultiPoint','MultiLineString','MultiPolygon','GeometryCollection'),
  'validate' => NULL,     // Additional validation callback. Takes a GeoPHP Geometry object.
  'update_field' => NULL,  // Callback after installing a new field. Could be used for adding additional geospatial indexes
  'delete_field' => NULL,   // Callback after deleting field. Could be used for removing indexes and other cleanup.
  'requirements' => NULL, // Callback to check system requirements
  'settings' => NULL,     // Callback for plugin-specific settings.
);

function geofield_backend_default_schema($fielddef) {
  return array(
    'type' => 'blob',
    'size' => 'big',
    'not null' => FALSE,
  );
}

function geofield_backend_default_save($geometry) {
  $geom = geoPHP::load($geometry);
  return $geom->out('wkb');
}

function geofield_backend_default_load($value) {
  return geoPHP::load($value);
}
