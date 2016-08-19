/**
 * @file
 * Handles statement creation for link clicks.
 */

(function ($) {

  // check for links once the document is loaded
  $(document).ready(function(){
    $('a').on('click', function(e) {
      // Do not track links that are tracked elsewhere or ignored.
      if ($(this).hasClass('tincanapi-ignore') || $(this).hasClass('tincanapi-links-ignore')) {
        return;
      }

      // Track external clicks.
      if (Drupal.settings.tincanapi_links.external && Drupal.tincanapi.links.isExternal(this.href)) {
        Drupal.tincanapi.links.track($(this), 'visited');
      }

      // Track file extensions.
      if (Drupal.tincanapi.links.isTracked(this.href)) {
        Drupal.tincanapi.links.track($(this), 'downloaded');
      }
    });
  });

  Drupal.tincanapi.links = {
    isExternal: function(href) {
      if (Drupal.tincanapi.links.isRelative(href)) {
        return false;
      }

      var internalRegExp = new RegExp('/' + window.location.host + '/');
      return !internalRegExp.test(href);
    },
    isRelative: function(href) {
      var relativeRegExp = new RegExp('^(?:[a-z]+:)?//', 'i');
      return !relativeRegExp.test(href);
    },
    isTracked: function(href) {
      if (Drupal.settings.tincanapi_links.extensions) {
        var ext = href.split('.').pop();

        if ($.inArray(ext, Drupal.settings.tincanapi_links.extensions) >= 0) {
          return true;
        }
      }

      return false;
    },
    formatData: function(anchor, verb) {
      var id = $(anchor).attr('href');
      var title = '';

      if (Drupal.tincanapi.links.isRelative(id)) {
        if (id.charAt(0) == '/') {
          id = window.location.origin + id;
        }
        else {
          id = window.location.origin + '/' + id;
        }
      }

      if ($(anchor).attr('title')) {
        title = $(anchor).attr('title');
      }
      else {
        title = $(anchor).text();
      }

      return {
        module: 'links',
        verb: verb,
        id: id,
        title: title,
        referrer: Drupal.settings.tincanapi.currentPage
      };
    },
    track: function(anchor, verb) {
      var data = Drupal.tincanapi.links.formatData(anchor, verb);
      Drupal.tincanapi.track(data);
    }
  };

})(jQuery);
