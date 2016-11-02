                        (
 (  (    (               )\ )  (  (
 )\))(  ))\ (    (  (   (()/( ))\ )(
((_))\ /((_))\   )\ )\   ((_))((_|()\
 (()(_|_)) ((_) ((_|(_)  _| (_))  ((_)
/ _` |/ -_) _ \/ _/ _ \/ _` / -_)| '_|
\__, |\___\___/\__\___/\__,_\___||_|
|___/

CONTENTS OF THIS FILE
---------------------

 * About Geocoder
 * Install
 * Configure
 * Credits

ABOUT GEOCODER
--------------

Geocoder is a Drupal 7 module that will extract geographical data (geocode) from just about anything you throw at it such as addresses, GPX files, Geotags from EXIF data in photos, and KML files.

A convenient way to allow users to enter an address and have it automatically geocoded is to use it in combination with the Addressfield (http://drupal.org/project/addressfield) and Geofield (http://drupal.org/project/geofield) modules.

Geocoder uses the external geocoding services from Google, Yahoo and Yandex.

Here you find great documentation on Geocoder: http://drupal.org/node/1355780

INSTALL
-------

Install and enable the Geocoder module and its required modules geoPHP (http://drupal.org/project/geophp) and Chaos tool suite (http://drupal.org/project/ctools) in the usual way. Install and enable the optional modules Addressfield and Geofield.
Learn more about installing Drupal modules: http://drupal.org/documentation/install/modules-themes/modules-7

CONFIGURE
---------

Assign the necessary permissions at /admin/people/permissions#module-geocoder

If you have enabled the modules  Addressfield and Geofield you can start using Geocoder in a content type, e.g., an event.

Add a new address field by going to /admin/structure/types, choosing the desired content type and opening the "Manage fields" tab. Add a "Postal address" field and configure the field. Add a geofield and select "Geocode from another field" as widget. In the settings for the geofield you can now choose the source field to geocode from. You can also choose which geocoding service (Google et cetera) to use and configure these services.

Now you have a place where Geocoder can store its result (geofield) and the input to the geocode operation (addressfield). You can then use /project/openlayers">OpenLayers</a> to map the geofields.

Note: you can use Geocoder in any entity such as a user, a taxonomy term or a comment.

CREDITS
-------

Geocoder was crafted by cspiker, phayes, henryblyth, jeff h, Les Lim, mikeytown2, fago, patrickavella & michaelfavia

