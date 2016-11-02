<?php

/**
 * @file
 * Plugin to provide a yandex geocoder.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t("Yandex (Яндекс.Карт)"),
  'description' => t('Geocodes addresses via Yandex (Яндекс.Карт)'),
  'callback' => 'geocoder_yandex',
  'field_types' => array('text','text_long','addressfield', 'location','text_with_summary','computed', 'taxonomy_term_reference'),
  'field_callback' => 'geocoder_yandex_field',
  'terms_of_service' => 'http://api.yandex.ru/maps/geocoder/doc/desc/concepts/About.xml',
);

/**
 * Process Address
 */
function geocoder_yandex($address, $options = array()) {
  global $base_path;
  $geocoder_settings = variable_get("geocoder_settings", array());

  if (!empty($geocoder_settings["geocoder_apikey_yandex"])) {
    $consumer_key = $geocoder_settings["geocoder_apikey_yandex"];
  }
  else {
    drupal_set_message(t('You must set up your Yandex API key. Click !config', array('!config' => l(t('here'), $base_path .'admin/config/content/geocoder'))),'error');
    return;
  }

  $params = array (
    'format' => 'json',
    'results' => 1,
    'key' => $consumer_key,
    'geocode' => $address,
  );
  $request = drupal_http_request("http://geocode-maps.yandex.ru/1.x/?" . http_build_query($params));
  $data = json_decode($request->data);

  return _geocoder_yandex_geometry($data);
}

function geocoder_yandex_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'text_with_summary' || $field['type'] == 'computed') {
    return geocoder_yandex($field_item['value']);
  }
  if ($field['type'] == 'addressfield' && module_exists('addressfield') && !addressfield_field_is_empty($field_item, $field)) {
    $address = geocoder_widget_parse_addressfield($field_item);
    return geocoder_yandex($address);
  }
  if ($field['type'] == 'location') {
    $address = geocoder_widget_parse_locationfield($field_item);
    return geocoder_google($address);
  }
  if ($field['type'] == 'taxonomy_term_reference') {
    $term = taxonomy_term_load($field_item['tid']);
    return geocoder_yandex($term->name);
  }
}

function _geocoder_yandex_geometry(&$data) {
  try {
    geophp_load();

    if (isset($data->error)) {
      $args = array(
        '@status' => $data->error->status,
        '@error' => $data->error->message,
      );
      $msg = t('Yandex API has reported an error.\nStatus: @status\nError: @error', $args);
      throw new Exception($msg, WATCHDOG_WARNING);
    }

    if($data->response->GeoObjectCollection->metaDataProperty->GeocoderResponseMetaData->found == 0) {
      return NULL;
    }

    $loc = explode(' ', $data->response->GeoObjectCollection->featureMember[0]->GeoObject->Point->pos);
    return new Point ($loc[0], $loc[1]);
  } catch (Exception $e) {
    watchdog_exception('geocoder', $e, $e->getMessage(), array(), $e->getCode());
  }
}