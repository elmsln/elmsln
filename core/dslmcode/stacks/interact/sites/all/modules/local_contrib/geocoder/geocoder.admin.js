(function ($) {

  Drupal.behaviors.geocoderWidgetSettings = {
    attach: function (context, settings) {
      $(':input[name="instance[widget][settings][geocoder_field]"]', context).once('geofield_widget_settings', function () {
        // When the geocoder_field field is changed, update the geocoder_handler options.
        $(this).change(function() {
          var field = $(this).val();
          var field_type = settings.geocoder_widget_settings.types[field];
          var valid_handlers = settings.geocoder_widget_settings.handlers[field_type];
          $(':input[name="instance[widget][settings][geocoder_handler]"] option', context).each(function () {
            var handler_type = $(this).val();
            if (geocoder_admin_handler_in_array(handler_type, valid_handlers)) {
              $(this).removeAttr('disabled').show();
            }
            else {
              $(this).attr('disabled', 'disabled').hide();
            }
          });

          // If the currently selected handler is not valid, set it to the first valid handler.
          // Trigger a change event so that depdendent fields will update.
          if (!geocoder_admin_handler_in_array($(':input[name="instance[widget][settings][geocoder_handler]"]').val(), valid_handlers)) {
            $('#:input[name="instance[widget][settings][geocoder_handler]"]').val(valid_handlers[0]).trigger('change');
          }
        });

        function geocoder_admin_handler_in_array(needle, haystack) {
          var length = haystack.length;
          for(var i = 0; i < length; i++) {
            if(haystack[i] == needle) return true;
          }
          return false;
        }
      });
      // Trigger an initial change event to initialize the dependent field.
      $(this).trigger('change');
    }
  };

})(jQuery);

