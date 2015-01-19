(function ($) {
  Drupal.behaviors.timeago = {
    attach: function (context) {
      $.extend($.timeago.settings, Drupal.settings.timeago);
      $('abbr.timeago, span.timeago, time.timeago', context).timeago();
    }
  };
})(jQuery);
