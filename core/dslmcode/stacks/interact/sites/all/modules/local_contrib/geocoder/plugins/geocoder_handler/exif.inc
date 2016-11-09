<?php

$plugin = array(
  'title' => t("Image/exif"),
  'description' => t('Get a location from an image that was taken with a GPS enabled phone or camera'),
  'callback' => 'geocoder_exif',
  'field_types' => array('file', 'image'),
  'field_callback' => 'geocoder_exif_field',
);

function geocoder_exif($uri, $options = array()) {
  // Invoke hook_file_download to check permissions
  // We are essentially duplicating the logic found in file.inc file_download()
  foreach (module_implements('file_download') as $module) {
    $function = $module . '_file_download';
    $result = $function($uri);
    if ($result == -1) {
      drupal_set_message(t('You do not have permission to access this file'), 'error');
      return FALSE;
    }
  }

  // The user has permission to access the file. Geocode it.
  geophp_load();
  if ($data = exif_read_data(drupal_realpath($uri))) {
    if (!isset($data['GPSLatitudeRef'])) return FALSE;
    $lat = geocoder_exif_from($data['GPSLatitudeRef'], $data['GPSLatitude']);
    $lon = geocoder_exif_from($data['GPSLongitudeRef'], $data['GPSLongitude']);
    $point = new Point($lon, $lat);
    return $point;
  }
  else return FALSE;
}

function geocoder_exif_field($field, $field_item) {
  if ($field_item['fid']) {
    $file = file_load($field_item['fid']);
    return geocoder_exif($file->uri);
  }
}

function geocoder_exif_from($dir, $data) {
  foreach ($data as $k => $item) {
    list($deg, $pct) = explode('/', $item);
    if ($pct) $data[$k] = $deg / $pct;
  }
  $point = (float) $data[0] + ($data[1] / 60) + ($data[2] / 3600);
  if (in_array($dir, array('S', 'W'))) $point = $point * -1;
  return $point;
}
