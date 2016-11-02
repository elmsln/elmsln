<?php

/**
 * @file
 * Plugin to provide a yahoo geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Yahoo Placefinder"),
  'description' => t('Geocodes via Yahoo Placefinder'),
  'callback' => 'geocoder_yahoo',
  'field_types' => array('text', 'text_long', 'addressfield', 'location', 'text_with_summary', 'computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_yahoo_field',
  'terms_of_service' => 'http://developer.yahoo.com/geo/placefinder/',
);

/**
 * Process Markup
 */
function geocoder_yahoo($address, $options = array()) {
  global $base_path;
  $geocoder_settings = variable_get("geocoder_settings", array());

  if (!empty($geocoder_settings["geocoder_apikey_yahoo"])) {
    $consumer_key = $geocoder_settings["geocoder_apikey_yahoo"];
  }
  else {
    drupal_set_message(t('You must set up your Yahoo API key. Click !config', array('!config' => l(t('here'), $base_path .'admin/config/content/geocoder'))),'error');
    return;
  }

  $request = drupal_http_request("http://where.yahooapis.com/geocode?location=" . urlencode($address) . "&flags=J&appid={$consumer_key}");
  $data = json_decode($request->data);

  geophp_load();
  return _geocoder_yahoo_geometry($data);
}

function geocoder_yahoo_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_yahoo($field_item['value']);
  }
  if ($field['type'] == 'addressfield' && module_exists('addressfield') && !addressfield_field_is_empty($field_item, $field)) {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_yahoo($address);
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_yahoo($address);
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_yahoo($term->name);
  }
}

function _geocoder_yahoo_geometry(&$data) {
  if (!isset($data->ResultSet)) {
    return NULL;
  }
  // Yahoo Placefinder API v2.
  elseif (isset($data->ResultSet->Result->longitude)) {
    return new Point($data->ResultSet->Result->longitude, $data->ResultSet->Result->latitude);
  }
  // Yahoo Placefinder API v1.
  elseif (isset($data->ResultSet->Results[0]->longitude)) {
    return new Point($data->ResultSet->Results[0]->longitude, $data->ResultSet->Results[0]->latitude);
  }
}

