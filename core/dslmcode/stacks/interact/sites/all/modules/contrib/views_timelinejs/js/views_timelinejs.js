var embed_path;

(function ($) {
  Drupal.behaviors.timelineJS = {
    attach: function(context, settings) {
      $.each(Drupal.settings.timelineJS, function(key, timeline) {
        embed_path = timeline['embed_path'];

        if (timeline['processed'] != true) {
          createStoryJS(timeline);
        }
        timeline['processed'] = true;
      });
    }
  }
})(jQuery);
