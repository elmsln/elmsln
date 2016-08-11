<?php
/**
 * @file
 * API functions for read_time module
 */

/**
 * Implements hook_read_time_defaults_alter().
 * Allows you to change the defaults
 * @param  [type] &$defaults [description]
 * @return [type]            [description]
 */
function hook_read_time_defaults_alter(&$defaults) {
  $defaults['wpm'] = 300;
}

/**
 * Implements hook_read_time_criteria().
 *
 * Allows you to add new criteria for read time engagement.
 * This is an example of the core implementation.
 * key of the property to measure points to the function
 * to get the value from
 *
 * @return array array items
 */
function hook_read_time_criteria() {
  return array(
    'keyname' => 'user_callback_function',
    'text' => 'read_time_calculate',
    'images' => 'read_time_calculate',
    'video' => 'read_time_calculate',
  );
}

/**
 * Implements hook_read_time_criteria_alter().
 *
 * Modify criteria after assembly.
 */
function hook_read_time_criteria_alter(&$criteria) {

}

/**
 * Implements hook_process_read_time_alter().
 *
 * Allow other projects process read_time after it's been calculated
 * from all elements hitting their callbacks.
 *
 * @param  array  &$read_time  criteria and their associated counts
 * @param  object  $node       node object
 * @param  string  $criterion  optional criterion if acting on a single one
 *
 * @see  read_time_book_process_read_time_alter
 */
function hook_process_read_time_alter(&$read_time, $node, $criterion = NULL) {

}