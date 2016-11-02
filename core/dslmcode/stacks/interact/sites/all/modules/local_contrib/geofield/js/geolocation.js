// geo-location shim
// Source: https://gist.github.com/366184

// currentely only serves lat/long
// depends on jQuery

;(function(geolocation, $){
  if (geolocation) return;

  var cache;

  geolocation = window.navigator.geolocation = {};
  geolocation.getCurrentPosition = function(callback){

    if (cache) callback(cache);

    $.getScript('//www.google.com/jsapi',function(){

      cache = {
        coords : {
          "latitude": google.loader.ClientLocation.latitude,
          "longitude": google.loader.ClientLocation.longitude
        }
      };

      callback(cache);
    });

  };

  geolocation.watchPosition = geolocation.getCurrentPosition;

})(navigator.geolocation, jQuery);

;(function ($) {
  Drupal.behaviors.geofieldGeolocation = {
    attach: function (context, settings) {
      // callback for getCurrentPosition
      function updateLocation(position) {
        $fields.find('.auto-geocode .geofield-lat').val(position.coords.latitude);
        $fields.find('.auto-geocode .geofield-lon').val(position.coords.longitude);
      }
      // don't do anything if we're on field configuration
      if (!$(context).find("#edit-instance").length) {
        var $fields = $(context);
        // check that we have something to fill up
        // on muti values check only that the first one is empty
        if ($fields.find('.auto-geocode .geofield-lat').val() == '' && $fields.find('.auto-geocode .geofield-lon').val() == '') {
          // Check to see if we have geolocation support, either natively or through Google.
          if (navigator.geolocation) {
	          navigator.geolocation.getCurrentPosition(updateLocation);
          }
        }
      }
      $(':input[name="geofield-html5-geocode-button"]').once('geofield_geolocation').click(function(e) {
        e.preventDefault();
        $fields = $(this).parents('.auto-geocode').parent();
        if (navigator.geolocation) {
          navigator.geolocation.getCurrentPosition(updateLocation);
        }
      })

    }
  };
})(jQuery);
