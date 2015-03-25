<?php
/**
 * @file
 * Describes hooks provided by the views_load_more module.
 */

/**
 * Alter the options that are passed to the waypoints jQuery plugin.
 *
 * @param $waypoint_opts
 *   Array of key value pairs that are passed as options to jQuery.fn.waypoint
 */
function hook_views_load_more_waypoint_opts_alter(&$waypoint_opts, $view) {
  $waypoint_opts['context'] = '.view-id-' . $view->name . '.view-display-id-' . $view->current_display;
}
