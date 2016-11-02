<?php

/**
 * @file
 * Plugin to provide a google geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Google Geocoder"),
  'description' => t('Geocodes via google geocoder'),
  'callback' => 'geocoder_google',
  'field_types' => array('text', 'text_long', 'addressfield', 'location', 'text_with_summary', 'computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_google_field',
  'settings_callback' => 'geocoder_google_form',
  'terms_of_service' => 'http://code.google.com/apis/maps/documentation/geocoding/#Limits',
);

/**
 * Process Markup
 */
function geocoder_google($address, $options = array()) {
  try {
    $delay_trigger = &drupal_static(__FUNCTION__);
    $delay = variable_get('geocoder_google_delay', 0);
    if ($delay > 0 && $delay_trigger) {
      usleep($delay * 1000);
    }

    geophp_load();

    $query = array('address' => $address);

    if (isset($options['extra_query']) && is_array($options['extra_query'])) {
      $query += $options['extra_query'];
    }

    // Add any given biasing.
    if (!empty($options['biasing']['bounds'])) {
      $query['bounds'] = $options['biasing']['bounds'];
    }
    if (!empty($options['biasing']['region'])) {
      $query['region'] = $options['biasing']['region'];
    }
    if (!empty($options['biasing']['components'])) {
      $query['components'] = $options['biasing']['components'];
    }

    // Add Google API authentication parameters.
    switch (variable_get('geocoder_google_auth_method')) {

      // Google Geocoding API Key.
      case GEOCODER_GOOGLE_AUTH_KEY:
        $geocoder_settings = variable_get("geocoder_settings", array());
        if (!empty($geocoder_settings['geocoder_apikey_google'])) {
          $query['key'] = $geocoder_settings['geocoder_apikey_google'];
        }
        break;

      // Google Maps for Work signature.
      case GEOCODER_GOOGLE_AUTH_WORK:
        $client_id   = variable_get('geocoder_google_client_id', FALSE);
        $private_key = variable_get('geocoder_google_private_key', FALSE);
        if (!empty($client_id) && !empty($private_key)) {
          $google_maps_for_work = TRUE;
          $query['client']      = $client_id;
        }
        break;
    }

    // Build the URL.
    $url = url("https://maps.googleapis.com/maps/api/geocode/json", array(
      'query' => $query,
    ));

    // If authenticating via Google Maps for Work, add signature.
    // @see https://developers.google.com/maps/documentation/business/webservices/auth#generating_valid_signatures
    if (!empty($google_maps_for_work)) {

      // Strip off the protocol and host for signing.
      $parsed      = parse_url($url);
      $url_to_sign = $parsed['path'] . '?' . $parsed['query'];

      // Decode the key in a URL-safe way (RFC 4648 Section 5).
      // @see https://www.ietf.org/rfc/rfc4648.txt
      $decoded_key = base64_decode(strtr($private_key, '-_', '+/'));

      // Use HMAC SHA1 to sign the URL with the decoded key.
      $signature = hash_hmac('sha1', $url_to_sign, $decoded_key, TRUE);

      // Append the signature to the URL's query parameters. Do this manually to
      // avoid URL encoding.
      $url .= '&signature=' . strtr(base64_encode($signature), '+/', '-_');
    }

    // Send the request.
    $result = drupal_http_request($url);
    $delay_trigger = TRUE;

    if (isset($result->error)) {
      $args = array(
        '@code' => $result->code,
        '@error' => $result->error,
      );
      $msg = t('HTTP request to google API failed.\nCode: @code\nError: @error', $args);
      throw new Exception($msg, WATCHDOG_ERROR);
    }

    $data = json_decode($result->data);

    if ($data->status == 'ZERO_RESULTS') {
      $args = array('@status' => $data->status, '@address' => $address);
      $msg = t('Google API returned zero results on @address status.\nStatus: @status', $args);
      throw new Exception($msg, WATCHDOG_NOTICE);
    }
    elseif ($data->status != 'OK') {
      $args = array('@status' => $data->status);
      $msg = t('Google API returned bad status.\nStatus: @status', $args);
      throw new Exception($msg, WATCHDOG_WARNING);
    }

    $geometries = array();

    foreach ($data->results as $item) {
      // Check if we should reject these results
      if (isset($options['reject_results'])) {
        if (in_array($item->geometry->location_type, $options['reject_results'], TRUE)) {
          continue;
        }
      }

      // Construct a geoPHP Geometry depending on what type of geometry we want returned (defaults to point)
      if (!isset($options['geometry_type']) || $options['geometry_type'] == 'point') {
        $geom = new Point($item->geometry->location->lng, $item->geometry->location->lat);
      }
      elseif ($options['geometry_type'] == 'bounds') {
        $points = array(
          new Point($item->geometry->bounds->southwest->lng, $item->geometry->bounds->southwest->lat),
          new Point($item->geometry->bounds->southwest->lng, $item->geometry->bounds->northeast->lat),
          new Point($item->geometry->bounds->northeast->lng, $item->geometry->bounds->northeast->lat),
          new Point($item->geometry->bounds->northeast->lng, $item->geometry->bounds->southwest->lat),
          new Point($item->geometry->bounds->southwest->lng, $item->geometry->bounds->southwest->lat),
        );
        $geom = new Polygon(array(new LineString($points)));
      }
      elseif ($options['geometry_type'] == 'viewport') {
        $points = array(
          new Point($item->geometry->viewport->southwest->lng, $item->geometry->viewport->southwest->lat),
          new Point($item->geometry->viewport->southwest->lng, $item->geometry->viewport->northeast->lat),
          new Point($item->geometry->viewport->northeast->lng, $item->geometry->viewport->northeast->lat),
          new Point($item->geometry->viewport->northeast->lng, $item->geometry->viewport->southwest->lat),
          new Point($item->geometry->viewport->southwest->lng, $item->geometry->viewport->southwest->lat),
        );
        $geom = new Polygon(array(new LineString($points)));
      }

      // Add additional metadata to the geometry - it might be useful!
      $geom->data = array();
      $geom->data['geocoder_accuracy'] = $item->geometry->location_type;
      $geom->data['geocoder_formatted_address'] = $item->formatted_address;
      $geom->data['geocoder_address_components'] = $item->address_components;

      $geometries[] = $geom;
    }

    if (empty($geometries)) {
      return;
    }

    // Check if we should return all results as a compound geometry
    if (isset($options['all_results'])) {
      if ($options['all_results']) {
        return geoPHP::geometryReduce($geometries);
      }
    }
    // The canonical geometry is the first result (best guess)
    $geometry = array_shift($geometries);

    // If there are any other geometries, these are auxiliary geometries that represent "alternatives"
    if (count($geometries)) {
      $geometry->data['geocoder_alternatives'] = $geometries;
    }

    return $geometry;
  } catch (Exception $e) {
    // Just rethrow the exception, the geocoder widget handles it.
    throw $e;
  }
}

function geocoder_google_field($field, $field_item, $options = array()) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_google($field_item['value'], $options);
  }
  if ($field['type'] == 'addressfield' && module_exists('addressfield') && !addressfield_field_is_empty($field_item, $field)) {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_google($address, $options);
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_google($address, $options);
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_google($term->name, $options);
  }
}

function geocoder_google_form($default_values = array()) {
  $form = array();

  $form['geometry_type'] = array(
    '#type' => 'select',
    '#title' => 'Geometry Type',
    '#options' => array(
      'point' => 'Point (default)',
      'bounds' => 'Bounding Box',
      'viewport' => 'Viewport',
    ),
    '#default_value' => isset($default_values['geometry_type']) ? $default_values['geometry_type'] : 'point',
  );

  $form['all_results'] = array(
    '#type' => 'checkbox',
    '#title' => 'Geocode all alternative results',
    '#default_value' => isset($default_values['all_results']) ? $default_values['all_results'] : FALSE,
    '#description' => 'Often an ambiguous address (such as "Springfield USA") can result in multiple hits. By default we only return the first (best guess) result. Check this to return all results as a Multi-Geometry (MultiPoint or MultiPolygon).',
  );

  $form['reject_results'] = array(
    '#type' => 'checkboxes',
    '#title' => 'Reject Results',
    '#options' => array(
      'APPROXIMATE' => 'APPROXIMATE:  indicates that the returned result is approximate.',
      'GEOMETRIC_CENTER'   => 'GEOMETRIC_CENTER: indicates that the returned result is the geometric center of a result such as a polyline (for example, a street) or polygon (region).',
      'RANGE_INTERPOLATED' => 'RANGE_INTERPOLATED: indicates that the returned result reflects an approximation (usually on a road) interpolated between two precise points (such as intersections). Interpolated results are generally returned when rooftop geocodes are unavailable for a street address.',
      'ROOFTOP' => 'ROOFTOP: indicates that the returned result is a precise geocode for which we have location information accurate down to street address precision.',
    ),
    '#default_value' => isset($default_values['reject_results']) ? $default_values['reject_results'] : array(),
    '#description' => 'Reject results that do not meet a certain level of quality or precision. Check all types of results to reject.',
  );

  $form['biasing'] = array(
    '#type' => 'fieldset',
    '#title' => t('Result biasing'),
    '#description' => t('To help reduce ambiguous results you can set give preference to or restrict results using viewports biasing, region biasing and component filtering. Please see !link for details on how to use these options.', array(
      '!link' => l(t('The Google Geocoding API'), 'https://developers.google.com/maps/documentation/geocoding/'),
    )),
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );
  $form['biasing']['bounds'] = array(
    '#type' => 'textfield',
    '#title' => t('Viewport biasing'),
    '#description' => t('Provide latitude/longitude coordinates of the southwest and northeast corners using a pipe (|) to separate the coordinates.'),
    '#default_value' => isset($default_values['biasing']['bounds']) ? $default_values['biasing']['bounds']: NULL,
  );
  $form['biasing']['region'] = array(
    '#type' => 'textfield',
    '#title' => t('Region biasing'),
    '#description' => t('Provide a ccTLD for the desired region.'),
    '#default_value' => isset($default_values['biasing']['region']) ? $default_values['biasing']['region']: NULL,
  );
  $form['biasing']['components'] = array(
    '#type' => 'textfield',
    '#title' => t('Component filtering'),
    '#description' => t('Provide a set of component:value pairs separated by a pipe (|) to filter results.'),
    '#default_value' => isset($default_values['biasing']['components']) ? $default_values['biasing']['components']: NULL,
  );

  return $form;
}
