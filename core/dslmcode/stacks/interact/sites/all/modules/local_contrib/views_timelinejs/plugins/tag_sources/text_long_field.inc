<?php
/**
 * @file
 * Long Text field as a tag source for TimelineJS.
 */

$plugin = array(
  'name' => t('Long Text field for TimelineJS'),
  'handler_name' => 'views_handler_field_field',
  'field_type' => 'text_long',
  'callback' => 'views_timelinejs_text_long_tag',
);

/**
 * Parses long text fields and returns full value as tag.
 *
 * @param array $value
 *   Long text field value.
 * @param array $options
 *   Optional configuration; not used.
 *
 * @return string|boolean
 *   String containing tag or boolean FALSE if not found.
 */
function views_timelinejs_text_long_tag($value, $options = array()) {
  if (isset($value) && $value != '') {
    return $value['value'];
  }
  else {
    return FALSE;
  }
}
