(function($) {

Drupal.plupload = Drupal.plupload || {};
// Add Plupload events for autoupload and autosubmit.
Drupal.plupload.filesAddedCallback = function (up, files) {
  setTimeout(function(){up.start()}, 100);
};
Drupal.plupload.uploadCompleteCallback = function(up, files) {
  var $this = $("#"+up.settings.container);
  // If there is submit_element trigger it.
  var submit_element = window.Drupal.settings.plupload[$this.attr('id')].submit_element;
  if (submit_element) {
    $(submit_element).click();
  }
  // Otherwise submit default form.
  else {
    var $form = $this.parents('form');
      $($form[0]).submit();
  }
};
/**
 * Attaches the Plupload behavior to each Plupload form element.
 */
Drupal.behaviors.plupload = {
  attach: function (context, settings) {
    $(".plupload-element", context).once('plupload-init', function () {
      var $this = $(this);

      // Merge the default settings and the element settings to get a full
      // settings object to pass to the Plupload library for this element.
      var id = $this.attr('id');
      var defaultSettings = settings.plupload['_default'] ? settings.plupload['_default'] : {};
      var elementSettings = (id && settings.plupload[id]) ? settings.plupload[id] : {};
      var pluploadSettings = $.extend({}, defaultSettings, elementSettings);

      // Process Plupload events.
      if (elementSettings['init'] || false) {
        if (!pluploadSettings.init) {
          pluploadSettings.init = {};
        }
        for (var key in elementSettings['init']) {
          var callback = elementSettings['init'][key].split('.');
          var fn = window;
          for (var j = 0; j < callback.length; j++) {
            fn = fn[callback[j]];
          }
          if (typeof fn === 'function') {
            pluploadSettings.init[key] = fn;
          }
        }
      }
      // Initialize Plupload for this element.
      $this.pluploadQueue(pluploadSettings);

    });
  }
};

 /**
  * Attaches the Plupload behavior to each Plupload form element.
  */
Drupal.behaviors.pluploadform = {
  attach: function(context, settings) {
    $('form', context).once('plupload-form', function() {
      if (0 < $(this).find('.plupload-element').length) {
        var $form = $(this);
        var originalFormAttributes = {
            'method': $form.attr('method'),
            'enctype': $form.attr('enctype'),
            'action': $form.attr('action'),
            'target': $form.attr('target')
        };

        $(this).submit(function(e) {
          var completedPluploaders = 0;
          var totalPluploaders = $(this).find('.plupload-element').length;
          var errors = '';

          $(this).find('.plupload-element').each( function(index){
            var uploader = $(this).pluploadQueue();

            var id = $(this).attr('id');
            var defaultSettings = settings.plupload['_default'] ? settings.plupload['_default'] : {};
            var elementSettings = (id && settings.plupload[id]) ? settings.plupload[id] : {};
            var pluploadSettings = $.extend({}, defaultSettings, elementSettings);

            //Only allow the submit to proceed if there are files and they've all
            //completed uploading.
            //TODO: Implement a setting for whether the field is required, rather
            //than assuming that all are.
            if (uploader.state == plupload.STARTED) {
              errors += Drupal.t("Please wait while your files are being uploaded.");
            }
            else if (uploader.files.length == 0 && !pluploadSettings.required) {
              completedPluploaders++;
            }

            else if (uploader.files.length == 0) {
              errors += Drupal.t("@index: You must upload at least one file.\n",{'@index': (index + 1)});
            }

            else if (uploader.files.length > 0 && uploader.total.uploaded == uploader.files.length) {
              completedPluploaders++;
            }

            else {
              var stateChangedHandler = function() {
                if (uploader.total.uploaded == uploader.files.length) {
                  uploader.unbind('StateChanged', stateChangedHandler);
                  completedPluploaders++;
                  if (completedPluploaders == totalPluploaders ) {
                    //Plupload's html4 runtime has a bug where it changes the
                    //attributes of the form to handle the file upload, but then
                    //fails to change them back after the upload is finished.
                    for (var attr in originalFormAttributes) {
                      $form.attr(attr, originalFormAttributes[attr]);
                    }
                    // Click a specific element if one is specified.
                    if (settings.plupload[id].submit_element) {
                      $(settings.plupload[id].submit_element).click();
                    }
                    else {
                      $form.submit();
                    }
                    return true;
                  }
                }
              };
              uploader.bind('StateChanged', stateChangedHandler);
              uploader.start();
            }

          });
          if (completedPluploaders == totalPluploaders) {
            //Plupload's html4 runtime has a bug where it changes the
            //attributes of the form to handle the file upload, but then
            //fails to change them back after the upload is finished.
            for (var attr in originalFormAttributes) {
              $form.attr(attr, originalFormAttributes[attr]);
            }
            return true;
          }
          else if (0 < errors.length){
            alert(errors);
          }

          return false;
        });
      }
    });
  }
};


/**
 * Helper function to compare version strings.
 *
 * Returns one of:
 *   - A negative integer if a < b.
 *   - A positive integer if a > b.
 *   - 0 if a == b.
 */
Drupal.plupload.compareVersions = function (a, b) {
  a = a.split('.');
  b = b.split('.');
  // Return the most significant difference, if there is one.
  for (var i=0; i < Math.min(a.length, b.length); i++) {
    var compare = parseInt(a[i]) - parseInt(b[i]);
    if (compare != 0) {
      return compare;
    }
  }
  // If the common parts of the two version strings are equal, the greater
  // version number is the one with the most sections.
  return a.length - b.length;
}

})(jQuery);
