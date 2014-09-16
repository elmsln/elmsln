<?php

/////////////////////////////////
// Date and time routines for use with quiz module.
// - Based on event module
// - All references to event variables should be optional
/////////////////////////////////

/**
 * @file
 * Handles the start and end times in a node form submission.
 * - Takes the array from form_date() and turns it into a timestamp
 * - Adjusts times for time zone offsets.
 * - Adapted from event.module
 *
 * @param $node The submitted node with form data.
 * @param $date The name of the date ('quiz_open' or 'quiz_close') to translate.
 */
function quiz_translate_form_date(&$node, $date) {
  $prefix = $node->$date;
  // If we have all the parameters, re-calculate $node->event_$date .
  if (is_array($prefix) && isset($prefix['year']) && isset($prefix['month']) && isset($prefix['day'])) {
    // Build a timestamp based on the date supplied and the configured timezone.
    $node->$date = _quiz_mktime(0, 0, 0, $prefix['month'], $prefix['day'], $prefix['year'], 0);
  }
  else {
    if (!_quiz_is_int($prefix, 1, 2147483647)) {
      form_set_error('quiz_open', t('Please supply a valid date.'));
    }
  }
}

/**
 * Formats local time values to GMT timestamp using time zone offset supplied.
 * All time values in the database are GMT and translated here prior to insertion.
 *
 * Time zone settings are applied in the following order:
 * 1. If supplied, time zone offset is applied
 * 2. If user time zones are enabled, user time zone offset is applied
 * 3. If neither 1 nor 2 apply, the site time zone offset is applied
 *
 * @param $hour
 * @param $minute
 * @param $second
 * @param $month
 * @param $day
 * @param $year
 * @param $offset
 *   Time zone offset to apply to the timestamp.
 * @return timestamp
 */
function _quiz_mktime($hour, $minute, $second, $month, $day, $year, $offset = NULL) {
  global $user;
  //print $user->timezone. " and ". variable_get('date_default_timezone', 0);
  $timestamp = gmmktime($hour, $minute, $second, $month, $day, $year);
  if (variable_get('configurable_timezones', 1) && $user->uid && strlen($user->timezone)) {
    return $timestamp - $user->timezone;
  }
  else {
    return $timestamp - variable_get('date_default_timezone', 0);
  }
}

/**
 * Formats a GMT timestamp to local date values using time zone offset supplied.
 * All timestamp values in event nodes are GMT and translated for display here.
 *
 * Pulled from event
 *
 * Time zone settings are applied in the following order
 * 1. If supplied, time zone offset is applied
 * 2. If user time zones are enabled, user time zone offset is applied
 * 3. If neither 1 nor 2 apply, the site time zone offset is applied
 *
 * @param $format
 *   The date() format to apply to the timestamp.
 * @param $timestamp
 *   The GMT timestamp value.
 * @param $offset
 *   Time zone offset to apply to the timestamp.
 * @return gmdate() formatted date value
 */
function _quiz_date($format, $timestamp, $offset = NULL) {
  global $user;

  if (isset($offset)) {
    $timestamp += $offset;
  }
  elseif (variable_get('configurable_timezones', 1) && $user->uid && strlen($user->timezone)) {
    $timestamp += $user->timezone;
  }
  else {
    $timestamp += variable_get('date_default_timezone', 0);
  }

  // make sure we apply the site first day of the week setting for dow requests
  $result = gmdate($format, $timestamp);
  return $result;
}
