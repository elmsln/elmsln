module.exports = function() {
  (function ($) {
    'use strict';

      Drupal.clipboard.on('success', function (e) {
        var alertStyle = $(e.trigger).data('clipboardAlert');
        var alertText = $(e.trigger).data('clipboardAlertText');
        var target = $(e.trigger).data('clipboardTarget');

        // Display as alert.
        if (alertStyle === 'toast') {
          Materialize.toast(alertText, 2000);
        }
      });

  })(jQuery);
};
