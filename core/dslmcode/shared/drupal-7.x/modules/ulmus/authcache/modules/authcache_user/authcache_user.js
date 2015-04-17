(function (Drupal, $) {
  "use strict";

  Drupal.behaviors.authcacheUser = {
    attach: function (context, settings) {
      if (settings.authcacheUser) {
        $('.authcache-user', context).once('authcache-user', function() {
          var $elem = $(this);
          var prop = $elem.data('p13n-user-prop');
          if (prop && settings.authcacheUser.hasOwnProperty(prop)) {
            if ($elem.is('input')) {
              $elem.val(settings.authcacheUser[prop]);
            }
            else {
              $elem.authcacheP13nReplaceWith(settings.authcacheUser[prop]);
            }
          }
        });
      }
    }
  };

}(Drupal, jQuery));
