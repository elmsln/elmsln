<?php
/**
 * @file
 * File field as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('File field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'file',
  'callback' => 'views_timelinejs_media_source_file_field_preparation',
);

/**
 * Parses file field to be passed as URL to TimelineJS.
 *
 * @param array $value
 *   File field value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing full URL to file or boolean FALSE
 */
function views_timelinejs_media_source_file_field_preparation($value, $options = array()) {
  if (is_array($value)) {
    return file_create_url($value['uri']);
  }
  else {
    return FALSE;
  }
}
