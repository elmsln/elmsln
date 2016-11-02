<?php
/**
 * @file
 * API documentation of leaflet widget module for Geofield.
 */

/**
 * Allows developers to declare base layers to be used by the widget.
 *
 * Return an array of base layer names keyed by the layer's URL template string.
 */
function hook_leaflet_widget_base_layers() {
  return array(
    'http://{s}.tile.openstreetmap.org/{z}/{x}/{y}.png' => 'OSM Mapnik',
  );
}
