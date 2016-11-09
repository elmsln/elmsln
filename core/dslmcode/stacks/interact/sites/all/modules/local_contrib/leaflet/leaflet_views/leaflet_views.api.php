<?php

/**
 * @file
 * API documentation for Leaflet views.
 */

/**
 * Allow modules to alter the points data while rendering a leaflet views row.
 */
function hook_leaflet_views_alter_points_data_alter($result, &$points) {
  if (isset($result->number)) {
    // Add number value to every points data entry, if present.
    array_walk($points, function(&$point, $key, $number) {
      $point['number'] = $number;
    }, $result->number);
  }
}
