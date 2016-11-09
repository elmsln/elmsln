
Download the leaflet library from: http://leafletjs.com/download.html

Alternatively, you can build the library from source. If so, follow the
instructions at: http://leafletjs.com/download.html#leaflet-source-code

Maps can be rendered via the included field formatter for Geofield, by using the
API directly, or by taking advantage of an additional module, like
http://drupal.org/project/ip_geoloc


Installation
------------

1. Install the Drupal Leaflet module as per normal.

2. Download the Leaflet library from http://leafletjs.com. Leaflet 0.7.5 or later
   is recommended. Extract it to your drupal root /sites/all/libraries/leaflet.
   The file 'leaflet.js' must reside at /sites/all/libraries/leaflet/leaflet.js.
   All other files and folder(s) that come with the library are also needed.

3. Enable leaflet_views for using Views and Leaflet (see below), or use the
   display formatters for fields display.


API Usage
---------
Building a map is as simple as calling a single method, leaflet_build_map(),
which takes 3 parameters.

$map (array)
An associative array defining a map. See hook_leaflet_map_info(). The module
defines a default map with a OpenStreet Maps base layer.

$features (array)
This is the tricky part. This is an associative array of all the features you
want to plot on the map. A feature can be a point, linestring, polygon,
multilinestring, multipolygon, or json object. Additionally, features can be
grouped into layer groups so they can be controlled together,
http://leaflet.cloudmade.com/reference.html#layergroup. A feature will look
something like:

$features = array(
  array(
    'type' => 'point',
    'lat' => 12.32,
    'lon' => 123.45,
    'icon' => array(
      'iconUrl' => 'sites/default/files/mymarker.png'
    ),
    'popup' => l($node->title, 'node/' . $node->nid),
    'leaflet_id' => 'some unique ID'
  ),
  array(
    'type' => 'linestring',
    'points' => array(
      0 => array('lat' => 13.24, 'lon' => 123.2),
      1 => array('lat' => 13.24, 'lon' => 123.2),
      2 => array('lat' => 13.24, 'lon' => 123.2),
      3 => array('lat' => 13.24, 'lon' => 123.2),
      4 => array('lat' => 13.24, 'lon' => 123.2),
    ),
    'popup' => l($node->title, 'node/' . $node->nid),
    'leaflet_id' => 'some unique ID'
  ),
  array(
    'type' => 'json',
    'json' => [JSON OBJECT],
    'properties' = array(
      'style' => [style settings],
      'leaflet_id' => 'some unique ID'
    )
  )
);

$height (string)
Height of the map expressed in pixels. Append 'px'. Default: '400px'.

Views integration
-----------------

To render a map using Views, enable the module leaflet_views.

You need to add at least one geofield to the Fields list, and select the Leaflet Map style
in Format.

In the settings of the style, select the geofield as the Data Source and select a field for Title
and Description (which will be rendered in the popup).

As a more powerful alternative, you can use node view modes to be rendered in the popup.
In the Description field, select "<entire node>" and then select a View mode.

For a tutorial, please read http://marzeelabs.org/blog/2012/09/24/building-maps-in-drupal-using-leaflet-views/

Roadmap
-------

* UI for managing maps
* Better documentation


Authors/Credits
---------------

* [levelos](http://drupal.org/user/54135)
* [pvhee](http://drupal.org/user/108811)
