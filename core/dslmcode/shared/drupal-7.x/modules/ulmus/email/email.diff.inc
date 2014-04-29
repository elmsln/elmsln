<?php

/**
 * @file
 * Provide diff field functions for the Email module.
 */

/**
 * Diff field callback for parsing email fields comparative values.
 */
function email_field_diff_view($items, $context) {
  $diff_items = array();
  foreach ($items as $delta => $item) {
    $diff_items[$delta] = $item['email'];
  }
  return $diff_items;
}
