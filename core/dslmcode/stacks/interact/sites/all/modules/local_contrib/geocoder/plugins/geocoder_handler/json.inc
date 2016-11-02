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
  'title' => t("GeoJSON"),
  'description' => t('Get the geometry of a GeoJSON string, file, or URL'),
  'callback' => 'geocoder_json',
  'field_types' => array('text', 'text_long', 'file', 'computed'),
  'field_callback' => 'geocoder_json_field',
);

/**
 * Process Markup
 */
function geocoder_json($json_string, $options = array()) {
  geophp_load();
  return geoPHP::load($json_string, 'json');
}

function geocoder_json_field($field, $field_item) {
  if ($field['type'] == 'text' || $field['type'] == 'text_long' || $field['type'] == 'computed') {
    return geocoder_json($field_item['value']);
  }
  if ($field['type'] == 'file') {
    if ($field_item['fid']) {
      $file = file_load($field_item['fid']);
      $json = file_get_contents($file->uri);
      return geocoder_json($json);
    }
  }
}
