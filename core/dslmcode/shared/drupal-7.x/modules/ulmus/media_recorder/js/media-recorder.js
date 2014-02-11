/**
 * @file
 * Adds an interface between the media recorder jQuery plugin and the drupal media module.
 */

(function($) {
  Drupal.behaviors.mediaRecorder = {
    attach: function(context, settings) {
      $('.media-recorder-wrapper').mediaRecorder({
        'recordingPath': Drupal.settings.mediaRecorder.recordingPath,
        'filePath': Drupal.settings.mediaRecorder.filePath,
        'fileName': Drupal.settings.mediaRecorder.fileName,
        'timeLimit': Drupal.settings.mediaRecorder.timeLimit,
        'width': Drupal.settings.mediaRecorder.width,
        'height': Drupal.settings.mediaRecorder.height,
        'swfurl': Drupal.settings.basePath + 'sites/all/libraries/wami/Wami.swf',
      });
    }
  };
})(jQuery);
