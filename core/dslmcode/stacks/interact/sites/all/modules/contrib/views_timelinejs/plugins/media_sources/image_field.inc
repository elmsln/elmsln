<?php
/**
 * @file
 * Image field as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('Image field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'image',
  'callback' => 'views_timelinejs_media_source_image_field_preparation',
);

/**
 * Parses image field to be passed as URL to TimelineJS.
 *
 * @param array $value
 *   Image field value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing full URL to file or boolean FALSE
 */
function views_timelinejs_media_source_image_field_preparation($value, $options = array()) {
  if (is_array($value) && isset($value['uri'])) {
    return file_create_url($value['uri']);
  }
  else {
    return FALSE;
  }
}
