(function ($) {

  Drupal.leaflet_widget = Drupal.leaflet_widget || {};

  Drupal.behaviors.geofield_widget = {
    attach: function (context, settings) {
      // Ensure we've set the default icon path to the leaflet library.
      L.Icon.Default.imagePath = Drupal.settings.leaflet_widget.defaultIconPath;

      $('.leaflet-widget').once().each(function (i, item) {
        var id = $(item).attr('id'),
          options = Drupal.settings.leaflet_widget_widget[id];

        L.Util.extend(options.map, {
          layers: [L.tileLayer(options.map.base_url)]
        });

        var map = L.map(id, options.map);
        map.widget.enable();

        // Serialize data and set input value on submit.
        $(item).parents('form')
          .bind('submit',
            $.proxy(map.widget.write, map.widget)
          );
        // Support for inline entity form. Event mousedown / click is to late.
        $(item).parents('.ief-form').find('.ief-entity-submit').bind(
          'mousedown.leaflet_widget',
          $.proxy(map.widget.write, map.widget)
        );
        // Try our best to provide generic support for forms without a submit
        // event e.g. inline entity forms.
        map.on('draw:marker-created draw:poly-created layerremove', function() {
          // Delay execution since we might rely on event handlers fired after
          // this one.
          // Unfortunately there aren't better events yet.
          // @TODO Add more events to Leaflet.widget.js
          if (Drupal.settings.leaflet_widget_widget[id].eventDelay) {
            window.clearTimeout(Drupal.settings.leaflet_widget_widget[id].eventDelay);
            Drupal.settings.leaflet_widget_widget[id].eventDelay = false;
          }
          Drupal.settings.leaflet_widget_widget[id].eventDelay = window.setTimeout($.proxy(map.widget.write, map.widget), 500);
        });

        Drupal.leaflet_widget[id] = map;

        // Geocoder handling.
        $('.field-widget-leaflet-widget-widget a.geocoder-submit', context).bind('click.leaflet_widget_geocoder', function (event) {
          event.preventDefault();
          Drupal.behaviors.geofield_widget.geocoder(id);
          return false;
        });
        $('.field-widget-leaflet-widget-widget :input.geocoder', context).bind('keydown.leaflet_widget_geocoder', function (event) {
          // React to Tab, Enter, Esc.
          if ($.inArray(event.keyCode, [9, 13, 27]) > -1) {
            event.preventDefault();
            event.stopPropagation();
            event.stopImmediatePropagation();
            Drupal.behaviors.geofield_widget.geocoder(id);
          }
        });
      });
    },

    geocoder: function (id) {
      var elem = $(':input.geocoder', $('#' + id ).parent());
      var handler = Drupal.settings.leaflet_widget_widget[id].geocoder.handler;
      var map = Drupal.leaflet_widget[id];
      var url = location.protocol + '//' + location.host + Drupal.settings.basePath + 'geocoder/service/' + handler+ '?output=json&data=' + Drupal.encodePath(elem.val());

      var throbber = $('<div class="ajax-progress ajax-progress-throbber"><div class="throbber">&nbsp;</div></div>');
      elem.after(throbber);

      $.ajax({
        url: url,
        type: 'GET',
        dataType: 'json',
        success: function (data, textStatus, jqXHR) {
          if (textStatus == 'success') {
            var latlng = [data.coordinates[1], data.coordinates[0]];
            var add = !map.widget._full;
            if (!add) {
              if((add = confirm(Drupal.t('The maximum cardinality is reached.\nDo you want to replace last item by the new one?')))) {
                map.removeLayer(map.widget.vectors.getLayers()[0]);
                add = !map.widget._full;
              }
            }
            if (add) {
              map.fire(
                'draw:marker-created',
                { marker: new L.Marker(latlng, { icon: map.drawControl.handlers.marker.options.icon }) }
              );
              map.fitBounds(map.widget.vectors.getBounds());
            }
          }
          else {
            alert(Drupal.t('No valid geo reference found.'));
          }
        },
        complete: function() {
          // Remove the progress element.
          if (throbber) {
            $(throbber).remove();
          }
        }
      });
    }
  }

}(jQuery));
