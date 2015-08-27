<?php

/**
 * jQuery Countdown timer api
 */

/**
 * Implements hook_jquery_countdown_timer_date_alter().
 *
 * @param  [string] &$date   a string based representation of a date
 * @param  [mixed] $context optional value that can provide additional context
 *  an example of using this could be custom invoking the attachment of the timer
 *  to a node form, and passing the node in question into the invoking. This could
 *  allow the node to actually influence the time that's shown via fields.
 *
 *  Default for the context variable is NULL unless otherwise passed in.
 */
function hook_jquery_countdown_timer_date_alter(&$date, $context) {
  // example of using a node-field to dictate the time to show
  if ($context != NULL && isset($node->field_time)) {
    $date = $node->field_time['und'][0]['value'];
  }
}