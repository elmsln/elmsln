
/**
 *  @file
 *  This file handles the JS for Media Module functions.
 */

(function ($) {

/**
 * Loads media browsers and callbacks, specifically for media as a field.
 */
Drupal.behaviors.mediaElement = {
  attach: function (context, settings) {
    // Options set from media.fields.inc for the types, etc to show in the browser.

    // For each widget (in case of multi-entry)
    $('.media-widget', context).once('mediaBrowserLaunch', function () {
      var options = settings.media.elements[this.id];
      globalOptions = {};
      if (options.global != undefined) {
        var globalOptions = options.global;
      }
      //options = Drupal.settings.media.fields[this.id];
      var fidField = $('.fid', this);
      var previewField = $('.preview', this);
      var editButton = $('.edit', this);
      var removeButton = $('.remove', this);

      // Hide the edit and remove buttons if there is no file data yet.
      if (fidField.val() == 0) {
        if (editButton.length) {
          editButton.hide();
        }
        removeButton.hide();
      }

      // When someone clicks the link to pick media (or clicks on an existing thumbnail)
      $('.launcher', this).bind('click', function (e) {
        // Launch the browser, providing the following callback function
        // @TODO: This should not be an anomyous function.
        Drupal.media.popups.mediaBrowser(function (mediaFiles) {
          if (mediaFiles.length < 0) {
            return;
          }
          var mediaFile = mediaFiles[0];
          // Set the value of the filefield fid (hidden) and trigger a change.
          fidField.val(mediaFile.fid);
          fidField.trigger('change');
          // Set the preview field HTML.
          previewField.html(mediaFile.preview);
        }, globalOptions);
        e.preventDefault();
      });

      // When someone clicks the Remove button.
      $('.remove', this).bind('click', function (e) {
        // Set the value of the filefield fid (hidden) and trigger change.
        fidField.val(0);
        fidField.trigger('change');
        // Set the preview field HTML.
        previewField.html('');
        e.preventDefault();
      });

      // Show or hide the edit/remove buttons if the field has a file or not.
      $('.fid', this).bind('change', function() {
        if (fidField.val() == 0) {
          if (editButton.length) {
            editButton.hide();
          }
          removeButton.hide();
        }
        else {
          if (editButton.length) {
            var url = Drupal.settings.basePath + 'file/' + fidField.val() + '/edit';
            $.ajax({
              url: location.protocol + '//' + location.host + url,
              type: 'HEAD',
              success: function(data) {
                editButton.attr('href', editButton.attr('href').replace(/media\/\d+\/edit/, 'media/' + fidField.val() + '/edit'));
                // Re-process the edit link through CTools modal behaviors.
                editButton.unbind('click');
                editButton.removeClass('ctools-use-modal-processed');
                // @todo Maybe add support for Drupal.detachBehaviors in Drupal.behaviors.ZZCToolsModal?
                Drupal.attachBehaviors(editButton.parent(), Drupal.settings);
                editButton.show();
              }
            });
          }
          removeButton.show();
        }
      });
    });
  }
};

})(jQuery);
