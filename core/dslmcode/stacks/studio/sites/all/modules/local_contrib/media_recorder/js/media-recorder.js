/**
 * @file
 * Loads correct javascript files based on browser features. We do this because of namespace conflicts with external
 * libraries.
 */

(function($) {
  'use strict';

  // Add mediaRecorder object to Drupal.
  Drupal.mediaRecorder = Drupal.mediaRecorder || {};
  Drupal.mediaRecorder.settings = Drupal.settings.mediaRecorder.settings;

  // Normalize features.
  navigator.getUserMedia = navigator.getUserMedia || navigator.webkitGetUserMedia || navigator.mozGetUserMedia;
  window.AudioContext = window.AudioContext || window.webkitAudioContext || window.mozAudioContext;
  window.URL = window.URL || window.webkitURL;
  Drupal.mediaRecorder.origin = window.location.origin || window.location.protocol + "//" + window.location.hostname + (window.location.port ? ':' + window.location.port: '');

  // Feature detection.
  var getUserMediaCheck = typeof(navigator.getUserMedia) === 'function';
  var mediaRecorderCheck = typeof(window.MediaRecorder) === 'function';
  var webAudioCheck = typeof(window.AudioContext) === 'function';
  var swfobjectCheck = typeof(window.swfobject) === 'object';
  var flashVersionCheck = swfobjectCheck ? (swfobject.getFlashPlayerVersion().major >= 10) : false;

  // Check to see that browser can use the recorder.
  if ((getUserMediaCheck && webAudioCheck) || (flashVersionCheck && swfobjectCheck)) {

    // Use the MediaRecorder API. Currently only works in firefox.
    if (getUserMediaCheck && webAudioCheck && mediaRecorderCheck) {
      $.ajax({
        url: Drupal.settings.basePath + Drupal.settings.mediaRecorder.modulePath + '/media-recorder-api.js',
        async: false,
        dataType: 'script'
      });
    }

    // Use HTML5 features (Web Audio API).
    else if (getUserMediaCheck && webAudioCheck && !mediaRecorderCheck) {
      $.ajax({
        url: Drupal.settings.basePath + Drupal.settings.mediaRecorder.html5url + '/recorder.js',
        async: false,
        dataType: 'script'
      });
      $.ajax({
        url: Drupal.settings.basePath + Drupal.settings.mediaRecorder.modulePath + '/media-recorder-html5.js',
        async: false,
        dataType: 'script'
      });
    }

    // Use Flash.
    else if (flashVersionCheck) {
      $.ajax({
        url: Drupal.settings.basePath + Drupal.settings.mediaRecorder.swfurl + '/recorder.js',
        async: false,
        dataType: 'script'
      });
      $.ajax({
        url: Drupal.settings.basePath + Drupal.settings.mediaRecorder.modulePath + '/media-recorder-flash.js',
        async: false,
        dataType: 'script'
      });
    }
  }

  // Otherwise just use the basic file field.
  else {
    $('.field-widget-media-recorder').find('.media-recorder-wrapper').hide();
  }

})(jQuery);
