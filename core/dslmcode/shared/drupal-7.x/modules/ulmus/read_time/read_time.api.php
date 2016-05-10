<?php
/**
 * @file
 * API functions for read_time module
 */

/**
 * Implements hook_read_time_defaults_alter().
 * Allows people to change the defaults
 * @param  [type] &$defaults [description]
 * @return [type]            [description]
 */
function hook_read_time_defaults_alter(&$defaults) {
  $defaults['wpm'] = 300;
}
