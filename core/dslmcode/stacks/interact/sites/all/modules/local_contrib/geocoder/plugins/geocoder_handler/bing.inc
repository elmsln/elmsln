<?php
// $Id$

/**
 * @file
 * Plugin to provide a bing geocoder.
 */

/**
 * Plugin for Bing.
 */
$plugin = array(
  'title' => t("Bing"),
  'description' => t('Geocodes via Bing'),
  'callback' => 'geocoder_bing',
  'field_types' => array('text', 'text_long', 'addressfield', 'location', 'text_with_summary', 'computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_bing_field',
  'terms_of_service' => 'http://msdn.microsoft.com/en-us/library/ff701714.aspx',
);

/**
 * Geocode an address.
 */
function geocoder_bing($address, $options = array()) {
  try {
    geophp_load();
    $geocoder_settings = variable_get('geocoder_settings', array());

    if (!empty($geocoder_settings['geocoder_apikey_bing'])) {
      $consumer_key = $geocoder_settings['geocoder_apikey_bing'];
    }
    else {
      throw new Exception('You must specify a key.');
    }

    if (isset($options['address']) && is_array($options['address'])) {
      $query = array(
        'countryRegion' => (isset($options['address']['country']) ? $options['address']['country'] : ''),
        'adminDistrict' => (isset($options['address']['administrative_area']) ? $options['address']['administrative_area'] : ''),
        'locality' => (isset($options['address']['locality']) ? $options['address']['locality'] : ''),
        'postalCode' => (isset($options['address']['postal_code']) ? $options['address']['postal_code'] : ''),
        'addressLine' => (isset($options['address']['thoroughfare']) ? $options['address']['thoroughfare'] : ''),
        'userIp' => '127.0.0.1',
        'includeNeighborhood' => 0,
        'maxResults' => 1,
        'key' => $consumer_key,
      );
    }
    else {
      $query = array(
        'q' => $address,
        'key' => $consumer_key,
      );
    }

    // Extra options
    if (!empty($options['userLocation'])) {
      $query['userLocation'] = $options['userLocation'];
    }
    if (!empty($options['userIp'])) {
      $query['userIp'] = $options['userIp'];
    }
    if (!empty($options['includeNeighborhood'])) {
      $query['includeNeighborhood'] = $options['includeNeighborhood'];
    }
    if (!empty($options['maxResults'])) {
      $query['maxResults'] = $options['maxResults'];
    }

    $url = url('http://dev.virtualearth.net/REST/v1/Locations', array('query' => $query));
    $result = drupal_http_request($url);

    if (isset($result->error)) {
      $args = array(
        '@code' => $result->code,
        '@error' => $result->error,
      );
      $msg = t('HTTP request to Bing API failed.\nCode: @code\nError: @error', $args);
      throw new Exception($msg);
    }

    $data = json_decode($result->data);

    if ($data->statusCode != 200) {
      $msg = t('Bing API returned bad status.\nStatus: @status\n@description', array(
        '@status' => $data->statusCode,
        '@description' => $data->statusDescription,
      ));
      throw new Exception($msg);
    }

    $geometries = array();

    foreach ($data->resourceSets as $resourceSet) {
      foreach ($resourceSet->resources as $resource) {
        $geom = new Point($resource->point->coordinates[1], $resource->point->coordinates[0]);
        $geom->data = $resource;
        $geometries[] = $geom;
      }
    }

    if (empty($geometries)) {
      return;
    }

    // The canonical geometry is the first result (best guess)
    $geometry = array_shift($geometries);

    // If there are any other geometries, these are auxiliary geometries that represent "alternatives"
    if (count($geometries)) {
      $geometry->data->geocoder_alternatives = $geometries;
    }

    return $geometry;
  } catch (Exception $e) {
    watchdog_exception('geocoder', $e);
    return FALSE;
  }
}

function geocoder_bing_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_bing($field_item['value']);
  }
  if ($field['type'] == 'addressfield' && module_exists('addressfield') && !addressfield_field_is_empty($field_item, $field)) {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_bing($address, array('address' => $address));
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_bing($address, array('address' => $address));
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_bing($term->name);
  }
}
