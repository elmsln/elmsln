(function (Drupal, $) {
  "use strict";

  function updateCount(elem, count) {
    if (count) {
      $(elem).html(Drupal.t('@count new', {'@count': count}));

      // Update icon.
      var icon = $(elem).closest('tr').find('td > div').get(0);
      if (icon) {
        icon.className = icon.className.replace('status-default', 'status-new').replace('status-hot', 'status-hot-new');
      }
    }
  }

  Drupal.behaviors.authcacheForum = {
    attach: function (context, settings) {
      if (settings.authcacheCommentNumNew) {
        $('.authcache-forum-topic-num-new', context).once('authcache-forum-topic-num-new', function() {
          var nid = $(this).data('p13n-nid');
          updateCount(this, settings.authcacheCommentNumNew[nid]);
        });
      }

      if (settings.authcacheForumNumNew) {
        $('.authcache-forum-num-new', context).once('authcache-forum-num-new', function() {
          var tid = $(this).data('p13n-tid');
          updateCount(this, settings.authcacheForumNumNew[tid]);
        });
      }
    }
  };
}(Drupal, jQuery));
