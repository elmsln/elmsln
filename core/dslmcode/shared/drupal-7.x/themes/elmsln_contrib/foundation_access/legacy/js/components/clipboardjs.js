module.exports = function() {
  (function ($) {
    'use strict';
      // Replicate label if id exists with guid to match
      if (typeof Drupal.clipboard !== typeof undefined) {
        Drupal.clipboard.on('success', function (e) {
          var alertStyle = $(e.trigger).data('clipboardAlert');
          var alertText = $(e.trigger).data('clipboardAlertText');
          var target = $(e.trigger).data('clipboardTarget');

          // Display as Materialize toast.
          if (alertStyle === 'toast') {
            Materialize.toast(alertText, 2000);
          }
        });
      }
  })(jQuery);
};
