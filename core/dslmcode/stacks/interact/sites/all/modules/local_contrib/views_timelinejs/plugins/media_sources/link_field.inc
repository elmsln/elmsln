<?php
/**
 * @file
 * Link field as a media source for TimelineJS.
 */

$plugin = array(
  'name' => t('Twitter field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'link_field',
  'callback' => 'views_timelinejs_media_source_link_field_preparation',
);

/**
 * Parses link field to be passed as URL to TimelineJS.
 *
 * @param array $value
 *   Link field value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing full URL to file or boolean FALSE
 */
function views_timelinejs_media_source_link_field_preparation($value, $options = array()) {
  if (is_array($value) && isset($value['url'])) {
    return $value['url'];
  }
  else {
    return FALSE;
  }
}
