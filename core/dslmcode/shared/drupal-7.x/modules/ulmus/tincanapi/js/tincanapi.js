/**
 * @file
 * Handles creating statements using JS.
 */

(function ($) {

  Drupal.tincanapi = {
    history: [],
    track: function(data, callback) {
      if (!Drupal.settings.tincanapi) {
        return;
      }

      data.token = Drupal.settings.tincanapi.token;

      $.ajax({
        type: 'POST',
        url: Drupal.settings.basePath + 'ajax/tincanapi/track',
        data: data,
        complete: callback
      });
    }
  };

  Drupal.behaviors.tincanapi = {
    attach: function (context, settings) {
      if (Drupal.settings.tincanapi) {
        if (Drupal.tincanapi.history.length == 0 || Drupal.tincanapi.history[Drupal.tincanapi.history.length - 1] != Drupal.settings.tincanapi.currentPage) {
          Drupal.tincanapi.history.push(Drupal.settings.tincanapi.currentPage);
        }
      }
    }
  };

})(jQuery);
