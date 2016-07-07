/**
 * @file
 * Media browser JS integration for the Media Recorder module.
 */

(function($) {
  Drupal.behaviors.mediaRecorderBrowser = {
    attach: function (context, settings) {

      // Bind click handler to media recorder submit input.
      $('#media-tab-media_recorder input[type="submit"]').bind('click', function (event) {

        // Prevent regular form submit.
        event.preventDefault();

        // Get the fid value.
        var fid = $('#media-tab-media_recorder .media-recorder-fid').val();

        // Build file object.
        var file = {};
        file.fid = fid;
        file.preview = $('#media-tab-media_recorder .media-recorder-preview .content').html();

        // Add to selected media.
        var files = [];
        files.push(file);
        Drupal.media.browser.selectMedia(files);

        // Submit media browser form.
        Drupal.media.browser.submit();
      });
    }
  };
})(jQuery);
