<?php
/**
 * @file
 * Implementation of post_date (created, changed) as date source for TimelineJS.
 */

$plugin = array(
  'name' => t('Post Date'),
  'callback' => 'views_timelinejs_date_source_post_date_conversion',
  'handler_name' => 'views_handler_field_date',
  'field_type' => 'date',
);

/**
 * Converts post date formats, forces TimelineJS to ignore browser TZ.
 *
 * Converts different expected date formats to one global date format to be used
 * in TimelineJS. Uses Drupal's TZ, not field TZ. Adds Z to ISODate to force
 * TimelineJS to ignore browser timezone.
 *
 * @return string
 *   Formatted date.
 */
function views_timelinejs_date_source_post_date_conversion($date, $output_format, $options = array()) {
  $input_format = 'timestamp';
  $timezone = views_timelinejs_get_timezone();
  $db_timezone = 'UTC';
  switch ($output_format) {
    case 'csv':
      return views_timelinejs_convert_to_csv($date, $input_format, $timezone, $db_timezone, $options['field']['granularity']);

    case 'timestamp':
      return views_timelinejs_convert_to_timestamp($date, $input_format, $timezone, $db_timezone, $options['field']['granularity']);

  }
}
