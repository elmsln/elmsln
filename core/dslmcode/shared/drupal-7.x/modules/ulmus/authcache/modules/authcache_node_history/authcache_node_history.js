(function (Drupal, $) {
  "use strict";

  Drupal.behaviors.authcacheNodeHistory = {
    attach: function (context, settings) {
      if (settings.authcacheNodeHistory) {
        $('.authcache-node-history', context).once('authcache-node-history', function() {
          var $elem = $(this);
          $.each(settings.authcacheNodeHistory, function() {
            if (this.nid == $elem.data('p13n-nid') && this.ts < $elem.data('p13n-ts')) {
              $elem.html(Drupal.t('new'));
            }
          });
        });
      }
    }
  };

}(Drupal, jQuery));
