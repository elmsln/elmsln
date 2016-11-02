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
  'title' => t("Latitude / Longitude"),
  'description' => t('Parse location from freeform latitude and longitude string'),
  'callback' => 'geocoder_latlon',
  'field_types' => array('text', 'text_long', 'text_with_summary', 'computed'),
  'field_callback' => 'geocoder_latlon_field',
);

/**
 * Process Markup
 */
function geocoder_latlon($latlon_string, $options = array()) {
  geophp_load();

  $delims = array("," , "/" , " " , "\t");

  foreach ($delims as $delim) {
    $parts = explode($delim, $latlon_string);
    if (count($parts) == 2) {
      $lat = geocoder_latlon_DMStoDEC(trim($parts[0]));
      $lon = geocoder_latlon_DMStoDEC(trim($parts[1]));
      return new Point($lon, $lat);
    }
  }

  // Failed to parse
  return FALSE;
}

function geocoder_latlon_DMStoDEC($dms) {
  if (is_numeric($dms)) {
    // It's already decimal degrees, just return it
    return $dms;
  }

  // If it contains both an H and M, then it's an angular hours
  if (stripos($dms, 'H') !== FALSE && stripos($dms, 'M') !== FALSE) {
    $dms = strtr($dms, "'\"HOURSMINTECNDAhoursmintecnda", "  ");
    $dms = preg_replace('/\s\s+/', ' ', $dms);

    $dms = explode(" ", $dms);
    $deg = $dms[0];
    $min = $dms[1];
    $sec = $dms[2];

    $dec = floatval(($deg*15) + ($min/4) + ($sec/240));

    return $dec;
  }

  // If it contains an S or a W, then it's a negative
  if (stripos($dms, 'S') !== FALSE || stripos($dms, 'W') !== FALSE) {
    $direction = -1;
  }
  else {
    $direction = 1;
  }

  // Strip all characters and replace them with empty space
  $dms = strtr($dms, "�'\"NORTHSEAWnorthseaw'", " ");
  $dms = preg_replace('/\s\s+/', ' ', $dms);

  $dms = explode(" ", $dms);
  $deg = $dms[0];
  $min = $dms[1];
  $sec = $dms[2];

  // Direction should be checked only for nonnegative coordinates
  $dec = floatval($deg+((($min*60)+($sec))/3600));
  if ($dec > 0) {
    $dec = $direction * $dec;
  }
  return $dec;
}


function geocoder_latlon_field($field, $field_item) {
  return geocoder_latlon($field_item['value']);
}
