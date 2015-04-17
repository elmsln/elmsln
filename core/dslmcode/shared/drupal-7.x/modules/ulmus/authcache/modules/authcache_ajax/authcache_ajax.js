(function (Drupal, $) {
  "use strict";

  var cache = {};
  var pending = {};

  function authcacheGet(url, callback, type) {
    if (cache.hasOwnProperty(url)) {
      callback(cache[url]);
    }
    else if (pending.hasOwnProperty(url)) {
      pending[url].push(callback);
    }
    else {
      pending[url] = [callback];

      $.ajax({
        url: url,
        data: {v: $.cookie('aucp13n')},
        dataType: type,
        // Custom header to help prevent cross-site forgery requests.
        beforeSend: function(xhr) {
          xhr.setRequestHeader('X-Authcache','1');
        },
        success: function(data, status, xhr) {
          cache[url] = data;
          $.each(pending[url], function() {
            this(data);
          });
          delete pending[url];
        }
      });
    }
  }

  function authcacheGetJSON(url, callback) {
    return authcacheGet(url, callback, 'json');
  }

  // Simple Ajax fragment
  Drupal.behaviors.authcacheP13nAjaxFragments = {
    attach: function (context, settings) {
      $('span.authcache-ajax-frag', context).once('authcache-ajax-frag', function() {
        var $tarauthcacheGet = $(this);
        var url = $tarauthcacheGet.data('authcache-ajax-src');
        authcacheGet(url, function(data) {
          $tarauthcacheGet.authcacheP13nReplaceWith(data);
        });
      });
    }
  };

  // Ajax settings
  Drupal.behaviors.authcacheP13nAjaxSettings = {
    attach: function (context, settings) {
      if (settings.authcacheP13nAjaxSettings) {
        $.each(settings.authcacheP13nAjaxSettings, function() {
          var url = this;
          authcacheGetJSON(url, function(data) {
            $.authcacheP13nMergeSetting(data);
          });
        });

        // Remove the urls we processed
        settings.authcacheP13nAjaxSettings = [];
      }
    }
  };

  // Ajax fragment assembly
  Drupal.behaviors.authcacheP13nAjaxAssemblies = {
    attach: function (context, settings) {
      if (settings.authcacheP13nAjaxAssemblies) {
        $.each(settings.authcacheP13nAjaxAssemblies, function(selector) {
          var tarauthcacheGets = $(selector, context);
          var url = this;
          if (tarauthcacheGets.length) {
            authcacheGetJSON(url, function(data) {
              var response = {};
              response[selector] = data;

              $(context).authcacheP13nEachElementInSettings(response, function(markup) {
                $(this).authcacheP13nReplaceWith(markup);
              });
            });
          }
        });
      }
    }
  };
}(Drupal, jQuery));
