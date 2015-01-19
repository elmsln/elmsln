/**
 * @file
 * Adds an interface between the media recorder jQuery plugin and the drupal media module.
 */

(function($) {
  'use strict';

  Drupal.behaviors.mediaRecorder = {
    attach: function(context, settings) {
      $('.field-widget-media-recorder').once().each(function (key, element) {

        // Store all data in the element, since we may very well have many recorders on a page.
        var $element = $(element);

        // Hide file field related markup.
        $element.find('span.file, span.file-size, .media-recorder-upload, .media-recorder-upload-button, .media-recorder-remove-button').hide();

        // Declare DOM elements.
        var $constraintsWrapper  = $element.find('.media-recorder-constraints');
        var $previewWrapper = $element.find('.media-recorder-preview');
        var $statusWrapper = $element.find('.media-recorder-status');
        var $controlsWrapper = $element.find('.media-recorder-controls');
        var $recordButton = $element.find('.media-recorder-record');
        var $stopButton = $element.find('.media-recorder-stop');
        var $settingsButton = $('<button class="media-recorder-settings">Settings</button>');

        // Initialize flash recorder.
        Recorder.initialize({
          swfSrc: settings.basePath + settings.mediaRecorder.swfurl + '/recorder.swf',
        });

        // Click handler for record button.
        $recordButton.bind('click', function (event) {
          event.preventDefault();
          Drupal.mediaRecorder.record();
        });

        // Click handler for stop button.
        $stopButton.bind('click', function (event) {
          event.preventDefault();
          Drupal.mediaRecorder.stop();
        });

        // Click handler for stop button.
        $settingsButton.bind('click', function (event) {
          event.preventDefault();
          Recorder.flashInterface().showFlash();
        });

        // Listen for the record event.
        $(Drupal.mediaRecorder).bind('recordStart', function (event, data) {
          $recordButton.hide();
          $stopButton.show();
        });

        // Listen for the progress event.
        $(Drupal.mediaRecorder).bind('progress', function (event, data) {
          function millisecondsToTime(milliSeconds) {
            // Format Current Time
            var milliSecondsDate = new Date(milliSeconds);
            var mm = milliSecondsDate.getMinutes();
            var ss = milliSecondsDate.getSeconds();
            if (mm < 10) {
              mm = "0" + mm;
            }
            if (ss < 10) {
              ss = "0" + ss;
            }
            return mm + ':' + ss;
          }
          var time = millisecondsToTime(data);
          var timeLimit = millisecondsToTime(new Date(parseInt(Drupal.mediaRecorder.settings.time_limit, 10) * 1000));

          $statusWrapper.html('Recording ' + time + ' (Time Limit: ' + timeLimit + ')');

          if (data / 1000 >= Drupal.mediaRecorder.settings.time_limit) {
            Drupal.mediaRecorder.stop();
          }
        });

        // Listen for the stop event.
        $(Drupal.mediaRecorder).bind('recordStop', function (event) {
          $recordButton.show();
          $stopButton.hide();
        });

        $(Drupal.mediaRecorder).bind('uploadStarted', function (event) {
          $statusWrapper.html('<div>Uploading, please wait...</div>');
        });

        $(Drupal.mediaRecorder).bind('uploadFinished', function (event, data) {
          $statusWrapper.html('<div>Press record to start recording.</div>');

          // Append file object data.
          $element.find('.media-recorder-fid').val(data.fid);
          $element.find('.media-recorder-refresh').trigger('mousedown');
        });

        // Initial state.
        $constraintsWrapper.hide();
        $previewWrapper.hide();
        $stopButton.hide();
        $statusWrapper.html('<div>Press record to start recording.</div>');
        $controlsWrapper.append($settingsButton);
      });

      /**
       * Start recording and trigger recording event.
       */
      Drupal.mediaRecorder.record = function () {

        Recorder.record({
          start: function(){

            // Trigger recording event.
            $(Drupal.mediaRecorder).trigger('recordStart');
          },
          progress: function (milliseconds) {

            // Trigger recording event.
            $(Drupal.mediaRecorder).trigger('progress', milliseconds);
          }
        });
      };

      /**
       * Stop recording and trigger stopped event.
       */
      Drupal.mediaRecorder.stop = function () {

        Recorder.stop();

        // Trigger uploading event.
        $(Drupal.mediaRecorder).trigger('uploadStarted');

        Recorder.upload({
          url: Drupal.mediaRecorder.origin + Drupal.settings.basePath + '/media_recorder/record/file',
          audioParam: 'mediaRecorder',
          success: function(response) {
            var file = JSON.parse(response);

            // Trigger stopped event.
            $(Drupal.mediaRecorder).trigger('uploadFinished', file);
          },
        });

        // Trigger stopped event.
        $(Drupal.mediaRecorder).trigger('recordStop');
      };

    },
  };
})(jQuery);
