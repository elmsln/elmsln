/**
 * @file
 * Adds an interface between the Youtube upload widget and the Drupal media recorder module.
 */

(function($) {
  Drupal.behaviors.mediaRecorderYoutube = {
    attach: function(context, settings) {

      // Load Youtube Upload Widget library.
      $.ajax({
        url: 'https://s.ytimg.com/yts/jsbin/www-widgetapi-vflop0WbJ.js',
        async: false,
        dataType: "script",
      });
      $.ajax({
        url: 'https://www.youtube.com/iframe_api',
        async: false,
        dataType: "script",
      });

      var widget;
      var element = $('#youtube-upload-widget');
      var input = element.parent().children('input.media-recorder-youtube');

      // Hide specific file related elements.
      element.parent().children('span.file, span.file-size, input.media-recorder-upload, input.media-recorder-upload-button').hide();

      // Attaches upload widget to upload div.
      function onYouTubeIframeAPIReady() {
        var statusInterval = window.setInterval(function() {
          console.log(YT);
          if (YT != 'undefined') {
            widget = new YT.UploadWidget('youtube-upload', {
              width: 500,
              events: {
                'onUploadSuccess': onUploadSuccess,
              }
            });
            clearInterval(statusInterval);
          }  
        }, 1000);


      }

      // Callback fired when video is successfully uploaded.
      function onUploadSuccess(event) {
        // Set input value.
        input.val(event.data.videoId);
        // Refresh the media recorder form.
        element.parent().children('input.media-recorder-refresh').trigger('mousedown');
      }

      // Create widget.
      onYouTubeIframeAPIReady();
    }
  };
})(jQuery);
