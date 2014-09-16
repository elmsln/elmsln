<?php
/**
 * @file
 * Text field as a tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Text field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'text',
  'callback' => 'views_timelinejs_text_tag',
);

/**
 * Parses text fields and returns value as tag.
 *
 * @param array $value
 *   Text field value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing tag or boolean FALSE if not found.
 */
function views_timelinejs_text_tag($value, $options = array()) {
  if (isset($value) && $value != '') {
    return $value['value'];
  }
  else {
    return FALSE;
  }
}
