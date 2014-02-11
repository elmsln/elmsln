// $Id: mfw.js,v 1.6 2010/11/23 05:51:16 webchick Exp $

/**
 * @file
 * Provides JavaScript additions to the managed file field type.
 *
 * This file provides progress bar support (if available), popup windows for
 * file previews, and disabling of other file fields during AJAX uploads (which
 * prevents separate file fields from accidentally uploading files).
 */

(function ($) {

/**
 * Attach behaviors to managed file element upload fields.
 */
Drupal.behaviors.fileValidateMultipleAutoAttach = {
  attach: function (context, settings) {
    if (settings.mfw && settings.mfw.elements) {
      $.each(settings.mfw.elements, function(selector) {
        var extensions = settings.mfw.elements[selector];
        $(selector, context).bind('change', {extensions: extensions}, Drupal.mfw.validateMultipleExtensions);
      });
    }
  },
  detach: function (context, settings) {
    if (settings.mfw && settings.mfw.elements) {
      $.each(settings.mfw.elements, function(selector) {
        $(selector, context).unbind('change', Drupal.mfw.validateMultipleExtensions);
      });
    }
  }
};

/**
 * File upload utility functions.
 */
Drupal.mfw = Drupal.mfw || {
  /**
   * Client-side file input validation of file extensions.
   */
  validateMultipleExtensions: function (event) {
    // Remove any previous errors.
    $('.file-upload-js-error').remove();

    // Add client side validation for the input[type=file].
    var extensionPattern = event.data.extensions.replace(/,\s*/g, '|');
    if (extensionPattern.length > 1 && this.value.length > 0) {
      // Instead of the original 'ig' ending we have just 'i' otherwise test()
      // evaluates to 'false' after the second call.
      var acceptableMatch = new RegExp('\\.(' + extensionPattern + ')$', 'i');
      if (typeof(this.files) == 'object') {
        for (i = 0; i < this.files.length; i++) {
          var fileName = this.files[i].name;
          var match = acceptableMatch.test(fileName);
          if (!match) {
            var error = Drupal.t("The selected file %filename cannot be uploaded. Only files with the following extensions are allowed: %extensions.", {
              '%filename': fileName,
              '%extensions': extensionPattern.replace(/\|/g, ', ')
            });
            $(this).parents('div.form-managed-file').prepend('<div class="messages error file-upload-js-error">' + error + '</div>');
            this.value = '';
            return false;
          }
        }
      }
    }
  },
};

})(jQuery);
