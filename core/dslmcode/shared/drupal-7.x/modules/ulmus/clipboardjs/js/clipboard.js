/**
 * @file
 * Javascript to integrate the clipboard.js library with Drupal.
 */

(function ($) {
  'use strict';

  Drupal.behaviors.clipboardjs = {
    attach: function (context, settings) {

      // Initialize clipboard.js.
      Drupal.clipboard = new Clipboard('a.clipboardjs-button, input.clipboardjs-button, button.clipboardjs-button');

      // Process successful copy.
      Drupal.clipboard.on('success', function (e) {
        var alertStyle = $(e.trigger).data('clipboardAlert');
        var alertText = $(e.trigger).data('clipboardAlertText');
        var target = $(e.trigger).data('clipboardTarget');

        // Display as alert.
        if (alertStyle === 'alert') {
          alert(alertText);
        }

        // Display as tooltip.
        else if (alertStyle === 'tooltip') {
          var $target = $(target);

          // Add title to target div.
          $target.prop('title', alertText);

          // Show tooltip.
          $target.tooltip({
            position: { my: "center", at: "center" }
          }).mouseover();

          // Destroy tooltip after delay.
          setTimeout(function () {
            $target.tooltip('destroy');
            $target.prop('title', '');
          }, 1500);
        }
      });

      // Process unsuccessful copy.
      Drupal.clipboard.on('error', function (e) {
        alert('This browser does not support the clipboard.js plugin, please copy manually.');
      });
    }
  };
}(jQuery));
