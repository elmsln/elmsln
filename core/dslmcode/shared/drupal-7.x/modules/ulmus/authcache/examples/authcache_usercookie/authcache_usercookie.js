(function (Drupal, $) {
  "use strict";

  Drupal.behaviors.authcacheUsercookie = {
    attach: function (context, settings) {
      // Display logged-in username
      $(".authcache-user", context).once('authcache-user').html($.cookie("aceuser"));

      // Display username linked to profile
      // Example usage: <a href="" class="authcache-user-link">Welcome, !username</a>
      $("a.authcache-user-link", context).once('authcache-user-link', function() {
        $(this).html($(this).html().replace('!username', $.cookie("aceuser")))
        .attr("href", Drupal.settings.basePath + 'user');
      });
    }
  };
}(Drupal, jQuery));
