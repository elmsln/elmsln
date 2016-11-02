<?php

/**
 * @file
 * Plugin to provide a MapQuest Nominatim geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("MapQuest Nominatim"),
  'description' => t('Geocodes via MapQuest Nominatim'),
  'callback' => 'geocoder_mapquest_nominatim',
  'field_types' => array('text', 'text_long', 'addressfield', 'location', 'text_with_summary', 'computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_mapquest_nominatim_field',
  'terms_of_service' => 'http://developer.mapquest.com/web/info/terms-of-use',
);

/**
 * Process Markup
 */
function geocoder_mapquest_nominatim($address, $options = array()) {
  $geocoder_settings = variable_get("geocoder_settings", array());
  $api_url = "http://open.mapquestapi.com/nominatim/v1/search";
  $params = array(
    'format' => 'json',
    'addressdetails' => 0,
    'limit' => 1,
    'osm_type' => 'N',
  );
  $request = drupal_http_request($api_url . '?q=' . urlencode($address) . '&' . drupal_http_build_query($params));
  $data = json_decode($request->data);
  return _geocoder_mapquest_nominatim_geometry($data);
}

function geocoder_mapquest_nominatim_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_mapquest_nominatim($field_item['value']);
  }
  if ($field['type'] == 'addressfield' && module_exists('addressfield') && !addressfield_field_is_empty($field_item, $field)) {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_mapquest_nominatim($address);
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_mapquest_nominatim($address);
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_mapquest_nominatim($term->name);
  }
}

function _geocoder_mapquest_nominatim_geometry(&$data) {
  if (!isset($data[0]->lon)) {
    return NULL;
  }
  geophp_load();
  return new Point($data[0]->lon, $data[0]->lat);
}
