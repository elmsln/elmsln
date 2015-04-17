(function (Drupal, $) {
  "use strict";

  Drupal.behaviors.authcacheComment = {
    attach: function (context, settings) {
      if (settings.authcacheCommentNumNew) {
        $('.authcache-comment-num-new', context).once('authcache-comment-num-new', function() {
          var elem = $(this);
          var nid = elem.data('p13n-nid');
          if (settings.authcacheCommentNumNew[nid]) {
            elem.html(Drupal.formatPlural(settings.authcacheCommentNumNew[nid], '1 new comment', '@count new comments'));
          }
          else {
            elem.parent('li').hide();
          }
        });
      }

      if (settings.authcacheUser && settings.authcacheUser.uid) {
        $('.authcache-comment-edit', context).once('authcache-comment-edit', function() {
          var elem = $(this);
          if (elem.data('p13n-uid') == settings.authcacheUser.uid) {
            elem.show();
          }
        });
      }
    }
  };

}(Drupal, jQuery));
