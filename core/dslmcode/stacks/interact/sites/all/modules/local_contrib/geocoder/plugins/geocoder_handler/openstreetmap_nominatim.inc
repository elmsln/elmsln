<?php
// $Id$

/**
 * @file
 * Plugin to provide a OpenStreetMap Nominatim geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('OpenStreetMap Nominatim'),
  'description' => t('Geocodes via OpenStreetMap Nominatim'),
  'callback' => 'geocoder_openstreetmap_nominatim',
  'field_types' => array('text', 'text_long', 'addressfield', 'location', 'text_with_summary', 'computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_openstreetmap_nominatim_field',
  'terms_of_service' => 'http://www.openstreetmap.org/copyright',
);

/**
 * Process Markup
 */
function geocoder_openstreetmap_nominatim($address, $options = array()) {
  $api_url = 'http://nominatim.openstreetmap.org/';

  $params = array(
    'q' => str_replace(' ', '+', $address),
    'format' => 'json',
    'addressdetails' => 0,
    'limit' => 1,
    'osm_type' => 'N',
  );
  $request = drupal_http_request($api_url . '?' . urldecode(drupal_http_build_query($params)));
  $data = json_decode($request->data);
  return _geocoder_openstreetmap_nominatim_geometry($data);
}

function geocoder_openstreetmap_nominatim_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_openstreetmap_nominatim($field_item['value']);
  }
  if ($field['type'] == 'addressfield') {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_openstreetmap_nominatim($address);
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_openstreetmap_nominatim($address);
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_openstreetmap_nominatim($term->name);
  }
}

function _geocoder_openstreetmap_nominatim_geometry(&$data) {
  if (!isset($data[0]->lon)) {
    return NULL;
  }
  geophp_load();
  return new Point($data[0]->lon, $data[0]->lat);
}
