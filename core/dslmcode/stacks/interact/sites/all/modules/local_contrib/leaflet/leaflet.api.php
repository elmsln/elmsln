<?php

/**
 * @file
 * API documentation for Administration menu.
 */

/**
 * Define one or map definitions to be used when rendering a map.
 *
 * leaflet_map_get_info() will grab every defined map, and the returned
 * associative array is then passed to leaflet_render_map(), along with a
 * collection of features.
 *
 * The settings array maps to the settings available to leaflet map object,
 * http://leaflet.cloudmade.com/reference.html#map-properties
 *
 * Layers are the available base layers for the map and, if you enable the
 * layer control, can be toggled on the map.
 *
 * @return array
 *   Associative array containing a complete leaflet map definition.
 */
function hook_leaflet_map_info() {
  return array(
    'OSM Mapnik' => array(
      'label' => 'OSM Mapnik',
      'description' => t('Leaflet default map.'),
      'settings' => array(
        'dragging' => TRUE,
        'touchZoom' => TRUE,
        'scrollWheelZoom' => TRUE,
        'doubleClickZoom' => TRUE,
        'zoomControl' => TRUE,
        'attributionControl' => TRUE,
        'trackResize' => TRUE,
        'fadeAnimation' => TRUE,
        'zoomAnimation' => TRUE,
        'closePopupOnClick' => TRUE,
        'layerControl' => TRUE,
        // 'minZoom' => 10,
        // 'maxZoom' => 15,
        // 'zoom' => 15, // set the map zoom fixed to 15
      ),
      'layers' => array(
        'earth' => array(
          'urlTemplate' => '//{s}.tile.openstreetmap.org/{z}/{x}/{y}.png',
          'options' => array(
            'attribution' => 'OSM Mapnik',
            // The switchZoom controls require multiple layers, referencing one
            // another as "switchLayer".
            'switchZoomBelow' => 15,
            'switchLayer' => 'satellite',
          ),
        ),
        'satellite' => array(
          'urlTemplate' => '//otile{s}.mqcdn.com/tiles/1.0.0/sat/{z}/{x}/{y}.png',
          'options' => array(
            'attribution' => 'OSM Mapnik',
            'subdomains' => '1234',
            'switchZoomAbove' => 15,
            'switchLayer' => 'earth',
          ),
        ),
      ),
      // Uncomment the lines below to use a custom icon
      // 'icon' => array(
      //   'iconUrl'       => '/sites/default/files/icon.png',
      //   'iconSize'      => array('x' => '20', 'y' => '40'),
      //   'iconAnchor'    => array('x' => '20', 'y' => '40'),
      //   'popupAnchor'   => array('x' => '-8', 'y' => '-32'),
      //   'shadowUrl'     => '/sites/default/files/icon-shadow.png',
      //   'shadowSize'    => array('x' => '25', 'y' => '27'),
      //   'shadowAnchor'  => array('x' => '0', 'y' => '27'),
      // ),
    ),
  );
}

/**
 * Alters the js settings passed to the leaflet map.
 *
 * This hook is called when the leaflet map is being rendered and attaching the
 * client side javascript settings.
 *
 * @param $settings
 *  A javascript settings array used for building the leaflet map.
 *
 * @see leaflet_map_get_info()
 * @see hook_leaflet_map_info()
 */
function hook_leaflet_map_prebuild_alter(&$settings) {
  $settings['mapId'] = 'my-map-id';
  $settings['features']['icon'] = 'my-icon-url';
}