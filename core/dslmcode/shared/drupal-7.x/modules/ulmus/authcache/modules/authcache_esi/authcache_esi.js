(function (Drupal, $) {
  "use strict";

  // ESI assemblies
  Drupal.behaviors.authcacheEsiFragmentAssembly = {
    attach: function (context, settings) {
      $('iframe.authcache-esi-assembly', context).once('authcache-esi-assembly', function() {
        try {
          var selector = $(this).data('authcache-esi-target');
          var data = $.parseJSON($(this).text());
          var response = {};

          response[selector] = data;
          $(context).authcacheP13nEachElementInSettings(response, function(markup) {
            $(this).authcacheP13nReplaceWith(markup);
          });
        }
        catch (e) {
          // FIXME
        }
      }).remove();
    }
  };

  // ESI Settings
  Drupal.behaviors.authcacheP13nEsiSettings = {
    attach: function (context, settings) {
      $('iframe.authcache-esi-settings', context).once('authcache-esi-settings', function() {
        try {
          var data = $.parseJSON($(this).text());
          $.authcacheP13nMergeSetting(data);
        }
        catch (e) {
          // FIXME
        }
      }).remove();
    }
  };

}(Drupal, jQuery));
